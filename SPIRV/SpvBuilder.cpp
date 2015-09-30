//
//Copyright (C) 2014 LunarG, Inc.
//
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
//FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
//COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//POSSIBILITY OF SUCH DAMAGE.

//
// Author: John Kessenich, LunarG
//

//
// Helper for making SPIR-V IR.  Generally, this is documented in the header
// SpvBuilder.h.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <unordered_set>

#include "SpvBuilder.h"

#ifndef _WIN32
    #include <cstdio>
#endif

namespace spv {

const int SpvBuilderMagic = 0xBB;

Builder::Builder(unsigned int userNumber) :
    source(SourceLanguageUnknown),
    sourceVersion(0),
    addressModel(AddressingModelLogical),
    memoryModel(MemoryModelGLSL450),
    builderNumber(userNumber << 16 | SpvBuilderMagic),
    buildPoint(0),
    uniqueId(0),
    mainFunction(0)
{
    clearAccessChain();
}

Builder::~Builder()
{
}

Id Builder::import(const char* name)
{
    Instruction* import = new Instruction(getUniqueId(), NoType, OpExtInstImport);
    import->addStringOperand(name);
    
    imports.push_back(import);
    return import->getResultId();
}

// For creating new groupedTypes (will return old type if the requested one was already made).
Id Builder::makeVoidType()
{
    Instruction* type;
    if (groupedTypes[OpTypeVoid].size() == 0) {
        type = new Instruction(getUniqueId(), NoType, OpTypeVoid);
        groupedTypes[OpTypeVoid].push_back(type);
        constantsTypesGlobals.push_back(type);
        module.mapInstruction(type);
    } else
        type = groupedTypes[OpTypeVoid].back();

    return type->getResultId();
}

Id Builder::makeBoolType()
{
    Instruction* type;
    if (groupedTypes[OpTypeBool].size() == 0) {
        type = new Instruction(getUniqueId(), NoType, OpTypeBool);
        groupedTypes[OpTypeBool].push_back(type);
        constantsTypesGlobals.push_back(type);
        module.mapInstruction(type);
    } else
        type = groupedTypes[OpTypeBool].back();

    return type->getResultId();
}

Id Builder::makePointer(StorageClass storageClass, Id pointee)
{
    // try to find it
    Instruction* type;
    for (int t = 0; t < (int)groupedTypes[OpTypePointer].size(); ++t) {
        type = groupedTypes[OpTypePointer][t];
        if (type->getImmediateOperand(0) == (unsigned)storageClass &&
            type->getIdOperand(1) == pointee)
            return type->getResultId();
    }

    // not found, make it
    type = new Instruction(getUniqueId(), NoType, OpTypePointer);
    type->addImmediateOperand(storageClass);
    type->addIdOperand(pointee);
    groupedTypes[OpTypePointer].push_back(type);
    constantsTypesGlobals.push_back(type);
    module.mapInstruction(type);

    return type->getResultId();
}

Id Builder::makeIntegerType(int width, bool hasSign)
{
    // try to find it
    Instruction* type;
    for (int t = 0; t < (int)groupedTypes[OpTypeInt].size(); ++t) {
        type = groupedTypes[OpTypeInt][t];
        if (type->getImmediateOperand(0) == (unsigned)width &&
            type->getImmediateOperand(1) == (hasSign ? 1u : 0u))
            return type->getResultId();
    }

    // not found, make it
    type = new Instruction(getUniqueId(), NoType, OpTypeInt);
    type->addImmediateOperand(width);
    type->addImmediateOperand(hasSign ? 1 : 0);
    groupedTypes[OpTypeInt].push_back(type);
    constantsTypesGlobals.push_back(type);
    module.mapInstruction(type);

    return type->getResultId();
}

Id Builder::makeFloatType(int width)
{
    // try to find it
    Instruction* type;
    for (int t = 0; t < (int)groupedTypes[OpTypeFloat].size(); ++t) {
        type = groupedTypes[OpTypeFloat][t];
        if (type->getImmediateOperand(0) == (unsigned)width)
            return type->getResultId();
    }

    // not found, make it
    type = new Instruction(getUniqueId(), NoType, OpTypeFloat);
    type->addImmediateOperand(width);
    groupedTypes[OpTypeFloat].push_back(type);
    constantsTypesGlobals.push_back(type);
    module.mapInstruction(type);

    return type->getResultId();
}

// Make a struct without checking for duplication.
// See makeStructResultType() for non-decorated structs
// needed as the result of some instructions, which does
// check for duplicates.
Id Builder::makeStructType(std::vector<Id>& members, const char* name)
{
    // Don't look for previous one, because in the general case,
    // structs can be duplicated except for decorations.

    // not found, make it
    Instruction* type = new Instruction(getUniqueId(), NoType, OpTypeStruct);
    for (int op = 0; op < (int)members.size(); ++op)
        type->addIdOperand(members[op]);
    groupedTypes[OpTypeStruct].push_back(type);
    constantsTypesGlobals.push_back(type);
    module.mapInstruction(type);
    addName(type->getResultId(), name);

    return type->getResultId();
}

// Make a struct for the simple results of several instructions,
// checking for duplication.
Id Builder::makeStructResultType(Id type0, Id type1)
{
    // try to find it
    Instruction* type;
    for (int t = 0; t < (int)groupedTypes[OpTypeStruct].size(); ++t) {
        type = groupedTypes[OpTypeStruct][t];
        if (type->getNumOperands() != 2)
            continue;
        if (type->getIdOperand(0) != type0 || 
            type->getIdOperand(1) != type1)
            continue;
        return type->getResultId();
    }

    // not found, make it
    std::vector<spv::Id> members;
    members.push_back(type0);
    members.push_back(type1);

    return makeStructType(members, "ResType");
}

Id Builder::makeVectorType(Id component, int size)
{
    // try to find it
    Instruction* type;
    for (int t = 0; t < (int)groupedTypes[OpTypeVector].size(); ++t) {
        type = groupedTypes[OpTypeVector][t];
        if (type->getIdOperand(0) == component &&
            type->getImmediateOperand(1) == (unsigned)size)
            return type->getResultId();
    }

    // not found, make it
    type = new Instruction(getUniqueId(), NoType, OpTypeVector);
    type->addIdOperand(component);
    type->addImmediateOperand(size);
    groupedTypes[OpTypeVector].push_back(type);
    constantsTypesGlobals.push_back(type);
    module.mapInstruction(type);

    return type->getResultId();
}

Id Builder::makeMatrixType(Id component, int cols, int rows)
{
    assert(cols <= maxMatrixSize && rows <= maxMatrixSize);

    Id column = makeVectorType(component, rows);

    // try to find it
    Instruction* type;
    for (int t = 0; t < (int)groupedTypes[OpTypeMatrix].size(); ++t) {
        type = groupedTypes[OpTypeMatrix][t];
        if (type->getIdOperand(0) == column &&
            type->getImmediateOperand(1) == (unsigned)cols)
            return type->getResultId();
    }

    // not found, make it
    type = new Instruction(getUniqueId(), NoType, OpTypeMatrix);
    type->addIdOperand(column);
    type->addImmediateOperand(cols);
    groupedTypes[OpTypeMatrix].push_back(type);
    constantsTypesGlobals.push_back(type);
    module.mapInstruction(type);

    return type->getResultId();
}

Id Builder::makeArrayType(Id element, unsigned size)
{
    // First, we need a constant instruction for the size
    Id sizeId = makeUintConstant(size);

    // try to find existing type
    Instruction* type;
    for (int t = 0; t < (int)groupedTypes[OpTypeArray].size(); ++t) {
        type = groupedTypes[OpTypeArray][t];
        if (type->getIdOperand(0) == element &&
            type->getIdOperand(1) == sizeId)
            return type->getResultId();
    }

    // not found, make it
    type = new Instruction(getUniqueId(), NoType, OpTypeArray);
    type->addIdOperand(element);
    type->addIdOperand(sizeId);
    groupedTypes[OpTypeArray].push_back(type);
    constantsTypesGlobals.push_back(type);
    module.mapInstruction(type);

    return type->getResultId();
}

Id Builder::makeRuntimeArray(Id element)
{
    Instruction* type = new Instruction(getUniqueId(), NoType, OpTypeRuntimeArray);
    type->addIdOperand(element);
    constantsTypesGlobals.push_back(type);
    module.mapInstruction(type);

    return type->getResultId();
}

Id Builder::makeFunctionType(Id returnType, std::vector<Id>& paramTypes)
{
    // try to find it
    Instruction* type;
    for (int t = 0; t < (int)groupedTypes[OpTypeFunction].size(); ++t) {
        type = groupedTypes[OpTypeFunction][t];
        if (type->getIdOperand(0) != returnType || (int)paramTypes.size() != type->getNumOperands() - 1)
            continue;
        bool mismatch = false;
        for (int p = 0; p < (int)paramTypes.size(); ++p) {
            if (paramTypes[p] != type->getIdOperand(p + 1)) {
                mismatch = true;
                break;
            }
        }
        if (! mismatch)
            return type->getResultId();
    }

    // not found, make it
    type = new Instruction(getUniqueId(), NoType, OpTypeFunction);
    type->addIdOperand(returnType);
    for (int p = 0; p < (int)paramTypes.size(); ++p)
        type->addIdOperand(paramTypes[p]);
    groupedTypes[OpTypeFunction].push_back(type);
    constantsTypesGlobals.push_back(type);
    module.mapInstruction(type);

    return type->getResultId();
}

Id Builder::makeImageType(Id sampledType, Dim dim, bool depth, bool arrayed, bool ms, unsigned sampled, ImageFormat format)
{
    // try to find it
    Instruction* type;
    for (int t = 0; t < (int)groupedTypes[OpTypeImage].size(); ++t) {
        type = groupedTypes[OpTypeImage][t];
        if (type->getIdOperand(0) == sampledType &&
            type->getImmediateOperand(1) == (unsigned int)dim &&
            type->getImmediateOperand(2) == (  depth ? 1u : 0u) &&
            type->getImmediateOperand(3) == (arrayed ? 1u : 0u) &&
            type->getImmediateOperand(4) == (     ms ? 1u : 0u) &&
            type->getImmediateOperand(5) == sampled &&
            type->getImmediateOperand(6) == (unsigned int)format)
            return type->getResultId();
    }

    // not found, make it
    type = new Instruction(getUniqueId(), NoType, OpTypeImage);
    type->addIdOperand(sampledType);
    type->addImmediateOperand(   dim);
    type->addImmediateOperand(  depth ? 1 : 0);
    type->addImmediateOperand(arrayed ? 1 : 0);
    type->addImmediateOperand(     ms ? 1 : 0);
    type->addImmediateOperand(sampled);
    type->addImmediateOperand((unsigned int)format);

    groupedTypes[OpTypeImage].push_back(type);
    constantsTypesGlobals.push_back(type);
    module.mapInstruction(type);

    return type->getResultId();
}

Id Builder::makeSampledImageType(Id imageType)
{
    // try to find it
    Instruction* type;
    for (int t = 0; t < (int)groupedTypes[OpTypeSampledImage].size(); ++t) {
        type = groupedTypes[OpTypeSampledImage][t];
        if (type->getIdOperand(0) == imageType)
            return type->getResultId();
    }

    // not found, make it
    type = new Instruction(getUniqueId(), NoType, OpTypeSampledImage);
    type->addIdOperand(imageType);

    groupedTypes[OpTypeSampledImage].push_back(type);
    constantsTypesGlobals.push_back(type);
    module.mapInstruction(type);

    return type->getResultId();
}

Id Builder::getDerefTypeId(Id resultId) const
{
    Id typeId = getTypeId(resultId);
    assert(isPointerType(typeId));

    return module.getInstruction(typeId)->getImmediateOperand(1);
}

Op Builder::getMostBasicTypeClass(Id typeId) const
{
    Instruction* instr = module.getInstruction(typeId);

    Op typeClass = instr->getOpCode();
    switch (typeClass)
    {
    case OpTypeVoid:
    case OpTypeBool:
    case OpTypeInt:
    case OpTypeFloat:
    case OpTypeStruct:
        return typeClass;
    case OpTypeVector:
    case OpTypeMatrix:
    case OpTypeArray:
    case OpTypeRuntimeArray:
        return getMostBasicTypeClass(instr->getIdOperand(0));
    case OpTypePointer:
        return getMostBasicTypeClass(instr->getIdOperand(1));
    default:
        assert(0);
        return OpTypeFloat;
    }
}

int Builder::getNumTypeComponents(Id typeId) const
{
    Instruction* instr = module.getInstruction(typeId);

    switch (instr->getOpCode())
    {
    case OpTypeBool:
    case OpTypeInt:
    case OpTypeFloat:
        return 1;
    case OpTypeVector:
    case OpTypeMatrix:
        return instr->getImmediateOperand(1);
    default:
        assert(0);
        return 1;
    }
}

// Return the lowest-level type of scalar that an homogeneous composite is made out of.
// Typically, this is just to find out if something is made out of ints or floats.
// However, it includes returning a structure, if say, it is an array of structure.
Id Builder::getScalarTypeId(Id typeId) const
{
    Instruction* instr = module.getInstruction(typeId);

    Op typeClass = instr->getOpCode();
    switch (typeClass)
    {
    case OpTypeVoid:
    case OpTypeBool:
    case OpTypeInt:
    case OpTypeFloat:
    case OpTypeStruct:
        return instr->getResultId();
    case OpTypeVector:
    case OpTypeMatrix:
    case OpTypeArray:
    case OpTypeRuntimeArray:
    case OpTypePointer:
        return getScalarTypeId(getContainedTypeId(typeId));
    default:
        assert(0);
        return NoResult;
    }
}

// Return the type of 'member' of a composite.
Id Builder::getContainedTypeId(Id typeId, int member) const
{
    Instruction* instr = module.getInstruction(typeId);

    Op typeClass = instr->getOpCode();
    switch (typeClass)
    {
    case OpTypeVector:
    case OpTypeMatrix:
    case OpTypeArray:
    case OpTypeRuntimeArray:
        return instr->getIdOperand(0);
    case OpTypePointer:
        return instr->getIdOperand(1);
    case OpTypeStruct:
        return instr->getIdOperand(member);
    default:
        assert(0);
        return NoResult;
    }
}

// Return the immediately contained type of a given composite type.
Id Builder::getContainedTypeId(Id typeId) const
{
    return getContainedTypeId(typeId, 0);
}

// See if a scalar constant of this type has already been created, so it
// can be reused rather than duplicated.  (Required by the specification).
Id Builder::findScalarConstant(Op typeClass, Id typeId, unsigned value) const
{
    Instruction* constant;
    for (int i = 0; i < (int)groupedConstants[typeClass].size(); ++i) {
        constant = groupedConstants[typeClass][i];
        if (constant->getNumOperands() == 1 &&
            constant->getTypeId() == typeId &&
            constant->getImmediateOperand(0) == value)
            return constant->getResultId();
    }

    return 0;
}

// Version of findScalarConstant (see above) for scalars that take two operands (e.g. a 'double').
Id Builder::findScalarConstant(Op typeClass, Id typeId, unsigned v1, unsigned v2) const
{
    Instruction* constant;
    for (int i = 0; i < (int)groupedConstants[typeClass].size(); ++i) {
        constant = groupedConstants[typeClass][i];
        if (constant->getNumOperands() == 2 &&
            constant->getTypeId() == typeId &&
            constant->getImmediateOperand(0) == v1 &&
            constant->getImmediateOperand(1) == v2)
            return constant->getResultId();
    }

    return 0;
}

Id Builder::makeBoolConstant(bool b)
{
    Id typeId = makeBoolType();
    Instruction* constant;

    // See if we already made it
    Id existing = 0;
    for (int i = 0; i < (int)groupedConstants[OpTypeBool].size(); ++i) {
        constant = groupedConstants[OpTypeBool][i];
        if (constant->getTypeId() == typeId &&
            (b ? (constant->getOpCode() == OpConstantTrue) : 
                 (constant->getOpCode() == OpConstantFalse)))
            existing = constant->getResultId();
    }

    if (existing)
        return existing;

    // Make it
    Instruction* c = new Instruction(getUniqueId(), typeId, b ? OpConstantTrue : OpConstantFalse);
    constantsTypesGlobals.push_back(c);
    groupedConstants[OpTypeBool].push_back(c);
    module.mapInstruction(c);

    return c->getResultId();
}

Id Builder::makeIntConstant(Id typeId, unsigned value)
{
    Id existing = findScalarConstant(OpTypeInt, typeId, value);
    if (existing)
        return existing;

    Instruction* c = new Instruction(getUniqueId(), typeId, OpConstant);
    c->addImmediateOperand(value);
    constantsTypesGlobals.push_back(c);
    groupedConstants[OpTypeInt].push_back(c);
    module.mapInstruction(c);

    return c->getResultId();
}

Id Builder::makeFloatConstant(float f)
{
    Id typeId = makeFloatType(32);
    unsigned value = *(unsigned int*)&f;
    Id existing = findScalarConstant(OpTypeFloat, typeId, value);
    if (existing)
        return existing;

    Instruction* c = new Instruction(getUniqueId(), typeId, OpConstant);
    c->addImmediateOperand(value);
    constantsTypesGlobals.push_back(c);
    groupedConstants[OpTypeFloat].push_back(c);
    module.mapInstruction(c);

    return c->getResultId();
}

Id Builder::makeDoubleConstant(double d)
{
    Id typeId = makeFloatType(64);
    unsigned long long value = *(unsigned long long*)&d;
    unsigned op1 = value & 0xFFFFFFFF;
    unsigned op2 = value >> 32;
    Id existing = findScalarConstant(OpTypeFloat, typeId, op1, op2);
    if (existing)
        return existing;

    Instruction* c = new Instruction(getUniqueId(), typeId, OpConstant);
    c->addImmediateOperand(op1);
    c->addImmediateOperand(op2);
    constantsTypesGlobals.push_back(c);
    groupedConstants[OpTypeFloat].push_back(c);
    module.mapInstruction(c);

    return c->getResultId();
}

Id Builder::findCompositeConstant(Op typeClass, std::vector<Id>& comps) const
{
    Instruction* constant = 0;
    bool found = false;
    for (int i = 0; i < (int)groupedConstants[typeClass].size(); ++i) {
        constant = groupedConstants[typeClass][i];

        // same shape?
        if (constant->getNumOperands() != (int)comps.size())
            continue;

        // same contents?
        bool mismatch = false;
        for (int op = 0; op < constant->getNumOperands(); ++op) {
            if (constant->getIdOperand(op) != comps[op]) {
                mismatch = true;
                break;
            }
        }
        if (! mismatch) {
            found = true;
            break;
        }
    }

    return found ? constant->getResultId() : NoResult;
}

// Comments in header
Id Builder::makeCompositeConstant(Id typeId, std::vector<Id>& members)
{
    assert(typeId);
    Op typeClass = getTypeClass(typeId);

    switch (typeClass) {
    case OpTypeVector:
    case OpTypeArray:
    case OpTypeStruct:
    case OpTypeMatrix:
        break;
    default:
        assert(0);
        return makeFloatConstant(0.0);
    }

    Id existing = findCompositeConstant(typeClass, members);
    if (existing)
        return existing;

    Instruction* c = new Instruction(getUniqueId(), typeId, OpConstantComposite);
    for (int op = 0; op < (int)members.size(); ++op)
        c->addIdOperand(members[op]);
    constantsTypesGlobals.push_back(c);
    groupedConstants[typeClass].push_back(c);
    module.mapInstruction(c);

    return c->getResultId();
}

void Builder::addEntryPoint(ExecutionModel model, Function* function, const char* name)
{
    Instruction* entryPoint = new Instruction(OpEntryPoint);
    entryPoint->addImmediateOperand(model);
    entryPoint->addIdOperand(function->getId());
    entryPoint->addStringOperand(name);

    entryPoints.push_back(entryPoint);
}

// Currently relying on the fact that all 'value' of interest are small non-negative values.
void Builder::addExecutionMode(Function* entryPoint, ExecutionMode mode, int value1, int value2, int value3)
{
    Instruction* instr = new Instruction(OpExecutionMode);
    instr->addIdOperand(entryPoint->getId());
    instr->addImmediateOperand(mode);
    if (value1 >= 0)
        instr->addImmediateOperand(value1);
    if (value2 >= 0)
        instr->addImmediateOperand(value2);
    if (value3 >= 0)
        instr->addImmediateOperand(value3);

    executionModes.push_back(instr);
}

void Builder::addName(Id id, const char* string)
{
    Instruction* name = new Instruction(OpName);
    name->addIdOperand(id);
    name->addStringOperand(string);

    names.push_back(name);
}

void Builder::addMemberName(Id id, int memberNumber, const char* string)
{
    Instruction* name = new Instruction(OpMemberName);
    name->addIdOperand(id);
    name->addImmediateOperand(memberNumber);
    name->addStringOperand(string);

    names.push_back(name);
}

void Builder::addLine(Id target, Id fileName, int lineNum, int column)
{
    Instruction* line = new Instruction(OpLine);
    line->addIdOperand(target);
    line->addIdOperand(fileName);
    line->addImmediateOperand(lineNum);
    line->addImmediateOperand(column);

    lines.push_back(line);
}

void Builder::addDecoration(Id id, Decoration decoration, int num)
{
    Instruction* dec = new Instruction(OpDecorate);
    dec->addIdOperand(id);
    dec->addImmediateOperand(decoration);
    if (num >= 0)
        dec->addImmediateOperand(num);

    decorations.push_back(dec);
}

void Builder::addMemberDecoration(Id id, unsigned int member, Decoration decoration, int num)
{
    Instruction* dec = new Instruction(OpMemberDecorate);
    dec->addIdOperand(id);
    dec->addImmediateOperand(member);
    dec->addImmediateOperand(decoration);
    if (num >= 0)
        dec->addImmediateOperand(num);

    decorations.push_back(dec);
}

// Comments in header
Function* Builder::makeMain()
{
    assert(! mainFunction);

    Block* entry;
    std::vector<Id> params;

    mainFunction = makeFunctionEntry(makeVoidType(), "main", params, &entry);

    return mainFunction;
}

// Comments in header
Function* Builder::makeFunctionEntry(Id returnType, const char* name, std::vector<Id>& paramTypes, Block **entry)
{
    Id typeId = makeFunctionType(returnType, paramTypes);
    Id firstParamId = paramTypes.size() == 0 ? 0 : getUniqueIds((int)paramTypes.size());
    Function* function = new Function(getUniqueId(), returnType, typeId, firstParamId, module);

    if (entry) {
        *entry = new Block(getUniqueId(), *function);
        function->addBlock(*entry);
        setBuildPoint(*entry);
    }

    if (name)
        addName(function->getId(), name);

    return function;
}

// Comments in header
void Builder::makeReturn(bool implicit, Id retVal)
{
    if (retVal) {
        Instruction* inst = new Instruction(NoResult, NoType, OpReturnValue);
        inst->addIdOperand(retVal);
        buildPoint->addInstruction(inst);
    } else
        buildPoint->addInstruction(new Instruction(NoResult, NoType, OpReturn));

    if (! implicit)
        createAndSetNoPredecessorBlock("post-return");
}

// Comments in header
void Builder::leaveFunction()
{
    Block* block = buildPoint;
    Function& function = buildPoint->getParent();
    assert(block);

    // If our function did not contain a return, add a return void now.
    if (! block->isTerminated()) {

        // Whether we're in an unreachable (non-entry) block.
        bool unreachable = function.getEntryBlock() != block && block->getNumPredecessors() == 0;

        if (unreachable) {
            // Given that this block is at the end of a function, it must be right after an
            // explicit return, just remove it.
            function.popBlock(block);
        } else {
            // We'll add a return instruction at the end of the current block,
            // which for a non-void function is really error recovery (?), as the source
            // being translated should have had an explicit return, which would have been
            // followed by an unreachable block, which was handled above.
            if (function.getReturnType() == makeVoidType())
                makeReturn(true);
            else {
                makeReturn(true, createUndefined(function.getReturnType()));
            }
        }
    }
}

// Comments in header
void Builder::makeDiscard()
{
    buildPoint->addInstruction(new Instruction(OpKill));
    createAndSetNoPredecessorBlock("post-discard");
}

// Comments in header
Id Builder::createVariable(StorageClass storageClass, Id type, const char* name)
{
    Id pointerType = makePointer(storageClass, type);
    Instruction* inst = new Instruction(getUniqueId(), pointerType, OpVariable);
    inst->addImmediateOperand(storageClass);

    switch (storageClass) {
    case StorageClassFunction:
        // Validation rules require the declaration in the entry block
        buildPoint->getParent().addLocalVariable(inst);
        break;

    default:
        constantsTypesGlobals.push_back(inst);
        module.mapInstruction(inst);
        break;
    }

    if (name)
        addName(inst->getResultId(), name);

    return inst->getResultId();
}

// Comments in header
Id Builder::createUndefined(Id type)
{
  Instruction* inst = new Instruction(getUniqueId(), type, OpUndef);
  buildPoint->addInstruction(inst);
  return inst->getResultId();
}

// Comments in header
void Builder::createStore(Id rValue, Id lValue)
{
    Instruction* store = new Instruction(OpStore);
    store->addIdOperand(lValue);
    store->addIdOperand(rValue);
    buildPoint->addInstruction(store);
}

// Comments in header
Id Builder::createLoad(Id lValue)
{
    Instruction* load = new Instruction(getUniqueId(), getDerefTypeId(lValue), OpLoad);
    load->addIdOperand(lValue);
    buildPoint->addInstruction(load);

    return load->getResultId();
}

// Comments in header
Id Builder::createAccessChain(StorageClass storageClass, Id base, std::vector<Id>& offsets)
{
    // Figure out the final resulting type.
    spv::Id typeId = getTypeId(base);
    assert(isPointerType(typeId) && offsets.size() > 0);
    typeId = getContainedTypeId(typeId);
    for (int i = 0; i < (int)offsets.size(); ++i) {
        if (isStructType(typeId)) {
            assert(isConstantScalar(offsets[i]));
            typeId = getContainedTypeId(typeId, getConstantScalar(offsets[i]));
        } else
            typeId = getContainedTypeId(typeId, offsets[i]);
    }
    typeId = makePointer(storageClass, typeId);

    // Make the instruction
    Instruction* chain = new Instruction(getUniqueId(), typeId, OpAccessChain);
    chain->addIdOperand(base);
    for (int i = 0; i < (int)offsets.size(); ++i)
        chain->addIdOperand(offsets[i]);
    buildPoint->addInstruction(chain);

    return chain->getResultId();
}

Id Builder::createArrayLength(Id base, unsigned int member)
{
    Instruction* length = new Instruction(getUniqueId(), makeIntType(32), OpArrayLength);
    length->addIdOperand(base);
    length->addImmediateOperand(member);
    buildPoint->addInstruction(length);

    return length->getResultId();
}

Id Builder::createCompositeExtract(Id composite, Id typeId, unsigned index)
{
    Instruction* extract = new Instruction(getUniqueId(), typeId, OpCompositeExtract);
    extract->addIdOperand(composite);
    extract->addImmediateOperand(index);
    buildPoint->addInstruction(extract);

    return extract->getResultId();
}

Id Builder::createCompositeExtract(Id composite, Id typeId, std::vector<unsigned>& indexes)
{
    Instruction* extract = new Instruction(getUniqueId(), typeId, OpCompositeExtract);
    extract->addIdOperand(composite);
    for (int i = 0; i < (int)indexes.size(); ++i)
        extract->addImmediateOperand(indexes[i]);
    buildPoint->addInstruction(extract);

    return extract->getResultId();
}

Id Builder::createCompositeInsert(Id object, Id composite, Id typeId, unsigned index)
{
    Instruction* insert = new Instruction(getUniqueId(), typeId, OpCompositeInsert);
    insert->addIdOperand(object);
    insert->addIdOperand(composite);
    insert->addImmediateOperand(index);
    buildPoint->addInstruction(insert);

    return insert->getResultId();
}

Id Builder::createCompositeInsert(Id object, Id composite, Id typeId, std::vector<unsigned>& indexes)
{
    Instruction* insert = new Instruction(getUniqueId(), typeId, OpCompositeInsert);
    insert->addIdOperand(object);
    insert->addIdOperand(composite);
    for (int i = 0; i < (int)indexes.size(); ++i)
        insert->addImmediateOperand(indexes[i]);
    buildPoint->addInstruction(insert);

    return insert->getResultId();
}

Id Builder::createVectorExtractDynamic(Id vector, Id typeId, Id componentIndex)
{
    Instruction* extract = new Instruction(getUniqueId(), typeId, OpVectorExtractDynamic);
    extract->addIdOperand(vector);
    extract->addIdOperand(componentIndex);
    buildPoint->addInstruction(extract);

    return extract->getResultId();
}

Id Builder::createVectorInsertDynamic(Id vector, Id typeId, Id component, Id componentIndex)
{
    Instruction* insert = new Instruction(getUniqueId(), typeId, OpVectorInsertDynamic);
    insert->addIdOperand(vector);
    insert->addIdOperand(component);
    insert->addIdOperand(componentIndex);
    buildPoint->addInstruction(insert);

    return insert->getResultId();
}

// An opcode that has no operands, no result id, and no type
void Builder::createNoResultOp(Op opCode)
{
    Instruction* op = new Instruction(opCode);
    buildPoint->addInstruction(op);
}

// An opcode that has one operand, no result id, and no type
void Builder::createNoResultOp(Op opCode, Id operand)
{
    Instruction* op = new Instruction(opCode);
    op->addIdOperand(operand);
    buildPoint->addInstruction(op);
}

// An opcode that has one operand, no result id, and no type
void Builder::createNoResultOp(Op opCode, const std::vector<Id>& operands)
{
    Instruction* op = new Instruction(opCode);
    for (auto operand : operands)
        op->addIdOperand(operand);
    buildPoint->addInstruction(op);
}

void Builder::createControlBarrier(Scope execution, Scope memory, MemorySemanticsMask semantics)
{
    Instruction* op = new Instruction(OpControlBarrier);
    op->addImmediateOperand(makeUintConstant(execution));
    op->addImmediateOperand(makeUintConstant(memory));
    op->addImmediateOperand(makeUintConstant(semantics));
    buildPoint->addInstruction(op);
}

void Builder::createMemoryBarrier(unsigned executionScope, unsigned memorySemantics)
{
    Instruction* op = new Instruction(OpMemoryBarrier);
    op->addImmediateOperand(makeUintConstant(executionScope));
    op->addImmediateOperand(makeUintConstant(memorySemantics));
    buildPoint->addInstruction(op);
}

// An opcode that has one operands, a result id, and a type
Id Builder::createUnaryOp(Op opCode, Id typeId, Id operand)
{
    Instruction* op = new Instruction(getUniqueId(), typeId, opCode);
    op->addIdOperand(operand);
    buildPoint->addInstruction(op);

    return op->getResultId();
}

Id Builder::createBinOp(Op opCode, Id typeId, Id left, Id right)
{
    Instruction* op = new Instruction(getUniqueId(), typeId, opCode);
    op->addIdOperand(left);
    op->addIdOperand(right);
    buildPoint->addInstruction(op);

    return op->getResultId();
}

Id Builder::createTriOp(Op opCode, Id typeId, Id op1, Id op2, Id op3)
{
    Instruction* op = new Instruction(getUniqueId(), typeId, opCode);
    op->addIdOperand(op1);
    op->addIdOperand(op2);
    op->addIdOperand(op3);
    buildPoint->addInstruction(op);

    return op->getResultId();
}

Id Builder::createOp(Op opCode, Id typeId, const std::vector<Id>& operands)
{
    Instruction* op = new Instruction(getUniqueId(), typeId, opCode);
    for (auto operand : operands)
        op->addIdOperand(operand);
    buildPoint->addInstruction(op);

    return op->getResultId();
}

Id Builder::createFunctionCall(spv::Function* function, std::vector<spv::Id>& args)
{
    Instruction* op = new Instruction(getUniqueId(), function->getReturnType(), OpFunctionCall);
    op->addIdOperand(function->getId());
    for (int a = 0; a < (int)args.size(); ++a)
        op->addIdOperand(args[a]);
    buildPoint->addInstruction(op);

    return op->getResultId();
}

// Comments in header
Id Builder::createRvalueSwizzle(Id typeId, Id source, std::vector<unsigned>& channels)
{
    if (channels.size() == 1)
        return createCompositeExtract(source, typeId, channels.front());

    Instruction* swizzle = new Instruction(getUniqueId(), typeId, OpVectorShuffle);
    assert(isVector(source));
    swizzle->addIdOperand(source);
    swizzle->addIdOperand(source);
    for (int i = 0; i < (int)channels.size(); ++i)
        swizzle->addImmediateOperand(channels[i]);
    buildPoint->addInstruction(swizzle);

    return swizzle->getResultId();
}

// Comments in header
Id Builder::createLvalueSwizzle(Id typeId, Id target, Id source, std::vector<unsigned>& channels)
{
    assert(getNumComponents(source) == (int)channels.size());
    if (channels.size() == 1 && getNumComponents(source) == 1)
        return createCompositeInsert(source, target, typeId, channels.front());

    Instruction* swizzle = new Instruction(getUniqueId(), typeId, OpVectorShuffle);
    assert(isVector(source));
    assert(isVector(target));
    swizzle->addIdOperand(target);
    swizzle->addIdOperand(source);

    // Set up an identity shuffle from the base value to the result value
    unsigned int components[4];
    int numTargetComponents = getNumComponents(target);
    for (int i = 0; i < numTargetComponents; ++i)
        components[i] = i;

    // Punch in the l-value swizzle
    for (int i = 0; i < (int)channels.size(); ++i)
        components[channels[i]] = numTargetComponents + i;

    // finish the instruction with these components selectors
    for (int i = 0; i < numTargetComponents; ++i)
        swizzle->addImmediateOperand(components[i]);
    buildPoint->addInstruction(swizzle);

    return swizzle->getResultId();
}

// Comments in header
void Builder::promoteScalar(Decoration precision, Id& left, Id& right)
{
    int direction = getNumComponents(right) - getNumComponents(left);

    if (direction > 0)
        left = smearScalar(precision, left, getTypeId(right));
    else if (direction < 0)
        right = smearScalar(precision, right, getTypeId(left));

    return;
}

// Comments in header
Id Builder::smearScalar(Decoration /*precision*/, Id scalar, Id vectorType)
{
    assert(getNumComponents(scalar) == 1);

    int numComponents = getNumTypeComponents(vectorType);
    if (numComponents == 1)
        return scalar;

    Instruction* smear = new Instruction(getUniqueId(), vectorType, OpCompositeConstruct);
    for (int c = 0; c < numComponents; ++c)
        smear->addIdOperand(scalar);
    buildPoint->addInstruction(smear);

    return smear->getResultId();
}

// Comments in header
Id Builder::createBuiltinCall(Decoration /*precision*/, Id resultType, Id builtins, int entryPoint, std::vector<Id>& args)
{
    Instruction* inst = new Instruction(getUniqueId(), resultType, OpExtInst);
    inst->addIdOperand(builtins);
    inst->addImmediateOperand(entryPoint);
    for (int arg = 0; arg < (int)args.size(); ++arg)
        inst->addIdOperand(args[arg]);

    buildPoint->addInstruction(inst);
    return inst->getResultId();
}

// Accept all parameters needed to create a texture instruction.
// Create the correct instruction based on the inputs, and make the call.
Id Builder::createTextureCall(Decoration precision, Id resultType, bool fetch, bool proj, bool gather, const TextureParameters& parameters)
{
    static const int maxTextureArgs = 10;
    Id texArgs[maxTextureArgs] = {};

    //
    // Set up the fixed arguments
    //
    int numArgs = 0;
    bool xplicit = false;
    texArgs[numArgs++] = parameters.sampler;
    texArgs[numArgs++] = parameters.coords;
    if (parameters.Dref)
        texArgs[numArgs++] = parameters.Dref;
    if (parameters.comp)
        texArgs[numArgs++] = parameters.comp;

    //
    // Set up the optional arguments
    //
    int optArgNum = numArgs;                        // track which operand, if it exists, is the mask of optional arguments
    ++numArgs;                                      // speculatively make room for the mask operand
    ImageOperandsMask mask = ImageOperandsMaskNone; // the mask operand
    if (parameters.bias) {
        mask = (ImageOperandsMask)(mask | ImageOperandsBiasMask);
        texArgs[numArgs++] = parameters.bias;
    }
    if (parameters.lod) {
        mask = (ImageOperandsMask)(mask | ImageOperandsLodMask);
        texArgs[numArgs++] = parameters.lod;
        xplicit = true;
    }
    if (parameters.gradX) {
        mask = (ImageOperandsMask)(mask | ImageOperandsGradMask);
        texArgs[numArgs++] = parameters.gradX;
        texArgs[numArgs++] = parameters.gradY;
        xplicit = true;
    }
    if (parameters.offset) {
        // TBD: if Offset is constant, use ImageOperandsConstOffsetMask
        mask = (ImageOperandsMask)(mask | ImageOperandsOffsetMask);
        texArgs[numArgs++] = parameters.offset;
    } else if (parameters.offsets) {
        mask = (ImageOperandsMask)(mask | ImageOperandsConstOffsetsMask);
        texArgs[numArgs++] = parameters.offsets;
    }
    if (parameters.sample) {
        mask = (ImageOperandsMask)(mask | ImageOperandsSampleMask);
        texArgs[numArgs++] = parameters.sample;
    }
    if (mask == ImageOperandsMaskNone)
        --numArgs;  // undo speculative reservation for the mask argument
    else
        texArgs[optArgNum] = mask;

    //
    // Set up the instruction
    //
    Op opCode;
    opCode = OpImageSampleImplicitLod;
    if (fetch) {
        opCode = OpImageFetch;
    } else if (gather) {
        if (parameters.Dref)
            opCode = OpImageDrefGather;
        else
            opCode = OpImageGather;
    } else if (xplicit) {
        if (parameters.Dref) {
            if (proj)
                opCode = OpImageSampleProjDrefExplicitLod;
            else
                opCode = OpImageSampleDrefExplicitLod;
        } else {
            if (proj)
                opCode = OpImageSampleProjExplicitLod;
            else
                opCode = OpImageSampleExplicitLod;
        }
    } else {
        if (parameters.Dref) {
            if (proj)
                opCode = OpImageSampleProjDrefImplicitLod;
            else
                opCode = OpImageSampleDrefImplicitLod;
        } else {
            if (proj)
                opCode = OpImageSampleProjImplicitLod;
            else
                opCode = OpImageSampleImplicitLod;
        }
    }

    // See if the result type is expecting a smeared result.
    // This happens when a legacy shadow*() call is made, which
    // gets a vec4 back instead of a float.
    Id smearedType = resultType;
    if (! isScalarType(resultType)) {
        switch (opCode) {
        case OpImageSampleDrefImplicitLod:
        case OpImageSampleDrefExplicitLod:
        case OpImageSampleProjDrefImplicitLod:
        case OpImageSampleProjDrefExplicitLod:
            resultType = getScalarTypeId(resultType);
            break;
        default:
            break;
        }
    }

    // Build the SPIR-V instruction
    Instruction* textureInst = new Instruction(getUniqueId(), resultType, opCode);
    for (int op = 0; op < optArgNum; ++op)
        textureInst->addIdOperand(texArgs[op]);
    if (optArgNum < numArgs)
        textureInst->addImmediateOperand(texArgs[optArgNum]);
    for (int op = optArgNum + 1; op < numArgs; ++op)
        textureInst->addIdOperand(texArgs[op]);
    setPrecision(textureInst->getResultId(), precision);
    buildPoint->addInstruction(textureInst);

    Id resultId = textureInst->getResultId();

    // When a smear is needed, do it, as per what was computed
    // above when resultType was changed to a scalar type.
    if (resultType != smearedType)
        resultId = smearScalar(precision, resultId, smearedType);

    return resultId;
}

// Comments in header
Id Builder::createTextureQueryCall(Op opCode, const TextureParameters& parameters)
{
    // Figure out the result type
    Id resultType = 0;
    switch (opCode) {
    case OpImageQuerySize:
    case OpImageQuerySizeLod:
    {
        int numComponents;
        switch (getTypeDimensionality(getImageType(parameters.sampler))) {
        case Dim1D:
        case DimBuffer:
            numComponents = 1;
            break;
        case Dim2D:
        case DimCube:
        case DimRect:
            numComponents = 2;
            break;
        case Dim3D:
            numComponents = 3;
            break;
        case DimInputTarget:
            MissingFunctionality("input-attachment dim");
            break;

        default:
            assert(0);
            break;
        }
        if (isArrayedImageType(getImageType(parameters.sampler)))
            ++numComponents;
        if (numComponents == 1)
            resultType = makeIntType(32);
        else
            resultType = makeVectorType(makeIntType(32), numComponents);

        break;
    }
    case OpImageQueryLod:
        resultType = makeVectorType(makeFloatType(32), 2);
        break;
    case OpImageQueryLevels:
    case OpImageQuerySamples:
        resultType = makeIntType(32);
        break;
    default:
        assert(0);
        break;
    }

    Instruction* query = new Instruction(getUniqueId(), resultType, opCode);
    query->addIdOperand(parameters.sampler);
    if (parameters.coords)
        query->addIdOperand(parameters.coords);
    if (parameters.lod)
        query->addIdOperand(parameters.lod);
    buildPoint->addInstruction(query);

    return query->getResultId();
}

// Comments in header
Id Builder::createCompare(Decoration precision, Id value1, Id value2, bool equal)
{
    Id boolType = makeBoolType();
    Id valueType = getTypeId(value1);

    assert(valueType == getTypeId(value2));
    assert(! isScalar(value1));

    // Vectors

    if (isVectorType(valueType)) {
        Id boolVectorType = makeVectorType(boolType, getNumTypeComponents(valueType));
        Id boolVector;
        Op op;
        if (getMostBasicTypeClass(valueType) == OpTypeFloat)
            op = equal ? OpFOrdEqual : OpFOrdNotEqual;
        else
            op = equal ? OpIEqual : OpINotEqual;

        boolVector = createBinOp(op, boolVectorType, value1, value2);
        setPrecision(boolVector, precision);

        // Reduce vector compares with any() and all().

        op = equal ? OpAll : OpAny;

        return createUnaryOp(op, boolType, boolVector);
    }

    spv::MissingFunctionality("Composite comparison of non-vectors");

    return NoResult;

    // Recursively handle aggregates, which include matrices, arrays, and structures
    // and accumulate the results.

    // Matrices

    // Arrays

    //int numElements;
    //const llvm::ArrayType* arrayType = llvm::dyn_cast<llvm::ArrayType>(value1->getType());
    //if (arrayType)
    //    numElements = (int)arrayType->getNumElements();
    //else {
    //    // better be structure
    //    const llvm::StructType* structType = llvm::dyn_cast<llvm::StructType>(value1->getType());
    //    assert(structType);
    //    numElements = structType->getNumElements();
    //}

    //assert(numElements > 0);

    //for (int element = 0; element < numElements; ++element) {
    //    // Get intermediate comparison values
    //    llvm::Value* element1 = builder.CreateExtractValue(value1, element, "element1");
    //    setInstructionPrecision(element1, precision);
    //    llvm::Value* element2 = builder.CreateExtractValue(value2, element, "element2");
    //    setInstructionPrecision(element2, precision);

    //    llvm::Value* subResult = createCompare(precision, element1, element2, equal, "comp");

    //    // Accumulate intermediate comparison
    //    if (element == 0)
    //        result = subResult;
    //    else {
    //        if (equal)
    //            result = builder.CreateAnd(result, subResult);
    //        else
    //            result = builder.CreateOr(result, subResult);
    //        setInstructionPrecision(result, precision);
    //    }
    //}

    //return result;
}

// OpCompositeConstruct
Id Builder::createCompositeConstruct(Id typeId, std::vector<Id>& constituents)
{
    assert(isAggregateType(typeId) || (getNumTypeComponents(typeId) > 1 && getNumTypeComponents(typeId) == (int)constituents.size()));

    Instruction* op = new Instruction(getUniqueId(), typeId, OpCompositeConstruct);
    for (int c = 0; c < (int)constituents.size(); ++c)
        op->addIdOperand(constituents[c]);
    buildPoint->addInstruction(op);

    return op->getResultId();
}

// Vector or scalar constructor
Id Builder::createConstructor(Decoration precision, const std::vector<Id>& sources, Id resultTypeId)
{
    Id result = 0;
    unsigned int numTargetComponents = getNumTypeComponents(resultTypeId);
    unsigned int targetComponent = 0;

    // Special case: when calling a vector constructor with a single scalar
    // argument, smear the scalar
    if (sources.size() == 1 && isScalar(sources[0]) && numTargetComponents > 1)
        return smearScalar(precision, sources[0], resultTypeId);

    Id scalarTypeId = getScalarTypeId(resultTypeId);
    std::vector<Id> constituents;  // accumulate the arguments for OpCompositeConstruct
    for (unsigned int i = 0; i < sources.size(); ++i) {
        assert(! isAggregate(sources[i]));
        unsigned int sourceSize = getNumComponents(sources[i]);
        unsigned int sourcesToUse = sourceSize;
        if (sourcesToUse + targetComponent > numTargetComponents)
            sourcesToUse = numTargetComponents - targetComponent;

        for (unsigned int s = 0; s < sourcesToUse; ++s) {
            Id arg = sources[i];
            if (sourceSize > 1) {
                std::vector<unsigned> swiz;
                swiz.push_back(s);
                arg = createRvalueSwizzle(scalarTypeId, arg, swiz);
            }

            if (numTargetComponents > 1)
                constituents.push_back(arg);
            else
                result = arg;
            ++targetComponent;
        }

        if (targetComponent >= numTargetComponents)
            break;
    }

    if (constituents.size() > 0)
        result = createCompositeConstruct(resultTypeId, constituents);

    setPrecision(result, precision);

    return result;
}

// Comments in header
Id Builder::createMatrixConstructor(Decoration precision, const std::vector<Id>& sources, Id resultTypeId)
{
    Id componentTypeId = getScalarTypeId(resultTypeId);
    int numCols = getTypeNumColumns(resultTypeId);
    int numRows = getTypeNumRows(resultTypeId);

    // Will use a two step process
    // 1. make a compile-time 2D array of values
    // 2. construct a matrix from that array

    // Step 1.

    // initialize the array to the identity matrix
    Id ids[maxMatrixSize][maxMatrixSize];
    Id  one = makeFloatConstant(1.0);
    Id zero = makeFloatConstant(0.0);
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            if (col == row)
                ids[col][row] = one;
            else
                ids[col][row] = zero;
        }
    }

    // modify components as dictated by the arguments
    if (sources.size() == 1 && isScalar(sources[0])) {
        // a single scalar; resets the diagonals
        for (int col = 0; col < 4; ++col)
            ids[col][col] = sources[0];
    } else if (isMatrix(sources[0])) {
        // constructing from another matrix; copy over the parts that exist in both the argument and constructee
        Id matrix = sources[0];
        int minCols = std::min(numCols, getNumColumns(matrix));
        int minRows = std::min(numRows, getNumRows(matrix));
        for (int col = 0; col < minCols; ++col) {
            std::vector<unsigned> indexes;
            indexes.push_back(col);
            for (int row = 0; row < minRows; ++row) {
                indexes.push_back(row);
                ids[col][row] = createCompositeExtract(matrix, componentTypeId, indexes);
                indexes.pop_back();
                setPrecision(ids[col][row], precision);
            }
        }
    } else {
        // fill in the matrix in column-major order with whatever argument components are available
        int row = 0;
        int col = 0;

        for (int arg = 0; arg < (int)sources.size(); ++arg) {
            Id argComp = sources[arg];
            for (int comp = 0; comp < getNumComponents(sources[arg]); ++comp) {
                if (getNumComponents(sources[arg]) > 1) {
                    argComp = createCompositeExtract(sources[arg], componentTypeId, comp);
                    setPrecision(argComp, precision);
                }
                ids[col][row++] = argComp;
                if (row == numRows) {
                    row = 0;
                    col++;
                }
            }
        }
    }


    // Step 2:  Construct a matrix from that array.
    // First make the column vectors, then make the matrix.

    // make the column vectors
    Id columnTypeId = getContainedTypeId(resultTypeId);
    std::vector<Id> matrixColumns;
    for (int col = 0; col < numCols; ++col) {
        std::vector<Id> vectorComponents;
        for (int row = 0; row < numRows; ++row)
            vectorComponents.push_back(ids[col][row]);
        matrixColumns.push_back(createCompositeConstruct(columnTypeId, vectorComponents));
    }

    // make the matrix
    return createCompositeConstruct(resultTypeId, matrixColumns);
}

// Comments in header
Builder::If::If(Id cond, Builder& gb) :
    builder(gb),
    condition(cond),
    elseBlock(0)
{
    function = &builder.getBuildPoint()->getParent();

    // make the blocks, but only put the then-block into the function,
    // the else-block and merge-block will be added later, in order, after
    // earlier code is emitted
    thenBlock = new Block(builder.getUniqueId(), *function);
    mergeBlock = new Block(builder.getUniqueId(), *function);

    // Save the current block, so that we can add in the flow control split when
    // makeEndIf is called.
    headerBlock = builder.getBuildPoint();

    function->addBlock(thenBlock);
    builder.setBuildPoint(thenBlock);
}

// Comments in header
void Builder::If::makeBeginElse()
{
    // Close out the "then" by having it jump to the mergeBlock
    builder.createBranch(mergeBlock);

    // Make the first else block and add it to the function
    elseBlock = new Block(builder.getUniqueId(), *function);
    function->addBlock(elseBlock);

    // Start building the else block
    builder.setBuildPoint(elseBlock);
}

// Comments in header
void Builder::If::makeEndIf()
{
    // jump to the merge block
    builder.createBranch(mergeBlock);

    // Go back to the headerBlock and make the flow control split
    builder.setBuildPoint(headerBlock);
    builder.createSelectionMerge(mergeBlock, SelectionControlMaskNone);
    if (elseBlock)
        builder.createConditionalBranch(condition, thenBlock, elseBlock);
    else
        builder.createConditionalBranch(condition, thenBlock, mergeBlock);

    // add the merge block to the function
    function->addBlock(mergeBlock);
    builder.setBuildPoint(mergeBlock);
}

// Comments in header
void Builder::makeSwitch(Id selector, int numSegments, std::vector<int>& caseValues, std::vector<int>& valueIndexToSegment, int defaultSegment,
                         std::vector<Block*>& segmentBlocks)
{
    Function& function = buildPoint->getParent();

    // make all the blocks
    for (int s = 0; s < numSegments; ++s)
        segmentBlocks.push_back(new Block(getUniqueId(), function));

    Block* mergeBlock = new Block(getUniqueId(), function);

    // make and insert the switch's selection-merge instruction
    createSelectionMerge(mergeBlock, SelectionControlMaskNone);

    // make the switch instruction
    Instruction* switchInst = new Instruction(NoResult, NoType, OpSwitch);
    switchInst->addIdOperand(selector);
    switchInst->addIdOperand(defaultSegment >= 0 ? segmentBlocks[defaultSegment]->getId() : mergeBlock->getId());
    for (int i = 0; i < (int)caseValues.size(); ++i) {
        switchInst->addImmediateOperand(caseValues[i]);
        switchInst->addIdOperand(segmentBlocks[valueIndexToSegment[i]]->getId());
    }
    buildPoint->addInstruction(switchInst);

    // push the merge block
    switchMerges.push(mergeBlock);
}

// Comments in header
void Builder::addSwitchBreak()
{
    // branch to the top of the merge block stack
    createBranch(switchMerges.top());
    createAndSetNoPredecessorBlock("post-switch-break");
}

// Comments in header
void Builder::nextSwitchSegment(std::vector<Block*>& segmentBlock, int nextSegment)
{
    int lastSegment = nextSegment - 1;
    if (lastSegment >= 0) {
        // Close out previous segment by jumping, if necessary, to next segment
        if (! buildPoint->isTerminated())
            createBranch(segmentBlock[nextSegment]);
    }
    Block* block = segmentBlock[nextSegment];
    block->getParent().addBlock(block);
    setBuildPoint(block);
}

// Comments in header
void Builder::endSwitch(std::vector<Block*>& /*segmentBlock*/)
{
    // Close out previous segment by jumping, if necessary, to next segment
    if (! buildPoint->isTerminated())
        addSwitchBreak();

    switchMerges.top()->getParent().addBlock(switchMerges.top());
    setBuildPoint(switchMerges.top());

    switchMerges.pop();
}

// Comments in header
void Builder::makeNewLoop(bool loopTestFirst)
{
    loops.push(Loop(*this, loopTestFirst));
    const Loop& loop = loops.top();

    // The loop test is always emitted before the loop body.
    // But if the loop test executes at the bottom of the loop, then
    // execute the test only on the second and subsequent iterations.

    // Remember the block that branches to the loop header.  This
    // is required for the test-after-body case.
    Block* preheader = getBuildPoint();

    // Branch into the loop
    createBranch(loop.header);

    // Set ourselves inside the loop
    loop.function->addBlock(loop.header);
    setBuildPoint(loop.header);

    if (!loopTestFirst) {
        // Generate code to defer the loop test until the second and
        // subsequent iterations.

        // It's always the first iteration when coming from the preheader.
        // All other branches to this loop header will need to indicate "false",
        // but we don't yet know where they will come from.
        loop.isFirstIteration->addIdOperand(makeBoolConstant(true));
        loop.isFirstIteration->addIdOperand(preheader->getId());
        getBuildPoint()->addInstruction(loop.isFirstIteration);

        // Mark the end of the structured loop. This must exist in the loop header block.
        createLoopMerge(loop.merge, loop.header, LoopControlMaskNone);

        // Generate code to see if this is the first iteration of the loop.
        // It needs to be in its own block, since the loop merge and
        // the selection merge instructions can't both be in the same
        // (header) block.
        Block* firstIterationCheck = new Block(getUniqueId(), *loop.function);
        createBranch(firstIterationCheck);
        loop.function->addBlock(firstIterationCheck);
        setBuildPoint(firstIterationCheck);

        // Control flow after this "if" normally reconverges at the loop body.
        // However, the loop test has a "break branch" out of this selection
        // construct because it can transfer control to the loop merge block.
        createSelectionMerge(loop.body, SelectionControlMaskNone);

        Block* loopTest = new Block(getUniqueId(), *loop.function);
        createConditionalBranch(loop.isFirstIteration->getResultId(), loop.body, loopTest);

        loop.function->addBlock(loopTest);
        setBuildPoint(loopTest);
    }
}

void Builder::createLoopTestBranch(Id condition)
{
    const Loop& loop = loops.top();

    // Generate the merge instruction. If the loop test executes before
    // the body, then this is a loop merge.  Otherwise the loop merge
    // has already been generated and this is a conditional merge.
    if (loop.testFirst) {
        createLoopMerge(loop.merge, loop.header, LoopControlMaskNone);
        // Branching to the "body" block will keep control inside
        // the loop.
        createConditionalBranch(condition, loop.body, loop.merge);
        loop.function->addBlock(loop.body);
        setBuildPoint(loop.body);
    } else {
        // The branch to the loop merge block is the allowed exception
        // to the structured control flow.  Otherwise, control flow will
        // continue to loop.body block.  Since that is already the target
        // of a merge instruction, and a block can't be the target of more
        // than one merge instruction, we need to make an intermediate block.
        Block* stayInLoopBlock = new Block(getUniqueId(), *loop.function);
        createSelectionMerge(stayInLoopBlock, SelectionControlMaskNone);

        // This is the loop test.
        createConditionalBranch(condition, stayInLoopBlock, loop.merge);

        // The dummy block just branches to the real loop body.
        loop.function->addBlock(stayInLoopBlock);
        setBuildPoint(stayInLoopBlock);
        createBranchToBody();
    }
}

void Builder::createBranchToBody()
{
    const Loop& loop = loops.top();
    assert(loop.body);

    // This is a reconvergence of control flow, so no merge instruction
    // is required.
    createBranch(loop.body);
    loop.function->addBlock(loop.body);
    setBuildPoint(loop.body);
}

void Builder::createLoopContinue()
{
    createBranchToLoopHeaderFromInside(loops.top());
    // Set up a block for dead code.
    createAndSetNoPredecessorBlock("post-loop-continue");
}

// Add an exit (e.g. "break") for the innermost loop that you're in
void Builder::createLoopExit()
{
    createBranch(loops.top().merge);
    // Set up a block for dead code.
    createAndSetNoPredecessorBlock("post-loop-break");
}

// Close the innermost loop
void Builder::closeLoop()
{
    const Loop& loop = loops.top();

    // Branch back to the top
    createBranchToLoopHeaderFromInside(loop);

    // Add the merge block and set the build point to it
    loop.function->addBlock(loop.merge);
    setBuildPoint(loop.merge);

    loops.pop();
}

// Create a branch to the header of the given loop, from inside
// the loop body.
// Adjusts the phi node for the first-iteration value if needeed.
void Builder::createBranchToLoopHeaderFromInside(const Loop& loop)
{
    createBranch(loop.header);
    if (loop.isFirstIteration) {
        loop.isFirstIteration->addIdOperand(makeBoolConstant(false));
        loop.isFirstIteration->addIdOperand(getBuildPoint()->getId());
    }
}

void Builder::clearAccessChain()
{
    accessChain.base = NoResult;
    accessChain.indexChain.clear();
    accessChain.instr = NoResult;
    accessChain.swizzle.clear();
    accessChain.component = NoResult;
    accessChain.preSwizzleBaseType = NoType;
    accessChain.isRValue = false;
}

// Comments in header
void Builder::accessChainPushSwizzle(std::vector<unsigned>& swizzle, Id preSwizzleBaseType)
{
    // swizzles can be stacked in GLSL, but simplified to a single
    // one here; the base type doesn't change
    if (accessChain.preSwizzleBaseType == NoType)
        accessChain.preSwizzleBaseType = preSwizzleBaseType;

    // if needed, propagate the swizzle for the current access chain
    if (accessChain.swizzle.size()) {
        std::vector<unsigned> oldSwizzle = accessChain.swizzle;
        accessChain.swizzle.resize(0);
        for (unsigned int i = 0; i < swizzle.size(); ++i) {
            accessChain.swizzle.push_back(oldSwizzle[swizzle[i]]);
        }
    } else
        accessChain.swizzle = swizzle;

    // determine if we need to track this swizzle anymore
    simplifyAccessChainSwizzle();
}

// Comments in header
void Builder::accessChainStore(Id rvalue)
{
    assert(accessChain.isRValue == false);

    Id base = collapseAccessChain();

    if (accessChain.swizzle.size() && accessChain.component != NoResult)
        MissingFunctionality("simultaneous l-value swizzle and dynamic component selection");

    // If swizzle exists, it is out-of-order or not full, we must load the target vector,
    // extract and insert elements to perform writeMask and/or swizzle.
    Id source = NoResult;
    if (accessChain.swizzle.size()) {
        Id tempBaseId = createLoad(base);
        source = createLvalueSwizzle(getTypeId(tempBaseId), tempBaseId, rvalue, accessChain.swizzle);
    }

    // dynamic component selection
    if (accessChain.component != NoResult) {
        Id tempBaseId = (source == NoResult) ? createLoad(base) : source;
        source = createVectorInsertDynamic(tempBaseId, getTypeId(tempBaseId), rvalue, accessChain.component);
    }

    if (source == NoResult)
        source = rvalue;

    createStore(source, base);
}

// Comments in header
Id Builder::accessChainLoad(Id resultType)
{
    Id id;

    if (accessChain.isRValue) {
        if (accessChain.indexChain.size() > 0) {
            mergeAccessChainSwizzle();  // TODO: optimization: look at applying this optimization more widely
            Id swizzleBase = accessChain.preSwizzleBaseType != NoType ? accessChain.preSwizzleBaseType : resultType;
        
            // if all the accesses are constants, we can use OpCompositeExtract
            std::vector<unsigned> indexes;
            bool constant = true;
            for (int i = 0; i < (int)accessChain.indexChain.size(); ++i) {
                if (isConstantScalar(accessChain.indexChain[i]))
                    indexes.push_back(getConstantScalar(accessChain.indexChain[i]));
                else {
                    constant = false;
                    break;
                }
            }

            if (constant)
                id = createCompositeExtract(accessChain.base, swizzleBase, indexes);
            else {
                // make a new function variable for this r-value
                Id lValue = createVariable(StorageClassFunction, getTypeId(accessChain.base), "indexable");

                // store into it
                createStore(accessChain.base, lValue);

                // move base to the new variable
                accessChain.base = lValue;
                accessChain.isRValue = false;

                // load through the access chain
                id = createLoad(collapseAccessChain());
            }
        } else
            id = accessChain.base;
    } else {
        // load through the access chain
        id = createLoad(collapseAccessChain());
    }

    // Done, unless there are swizzles to do
    if (accessChain.swizzle.size() == 0 && accessChain.component == NoResult)
        return id;

    // Do remaining swizzling
    // First, static swizzling
    if (accessChain.swizzle.size()) {
        // static swizzle
        Id swizzledType = getScalarTypeId(getTypeId(id));
        if (accessChain.swizzle.size() > 1)
            swizzledType = makeVectorType(swizzledType, (int)accessChain.swizzle.size());
        id = createRvalueSwizzle(swizzledType, id, accessChain.swizzle);
    }

    // dynamic single-component selection
    if (accessChain.component != NoResult)
        id = createVectorExtractDynamic(id, resultType, accessChain.component);

    return id;
}

Id Builder::accessChainGetLValue()
{
    assert(accessChain.isRValue == false);

    Id lvalue = collapseAccessChain();

    // If swizzle exists, it is out-of-order or not full, we must load the target vector,
    // extract and insert elements to perform writeMask and/or swizzle.  This does not
    // go with getting a direct l-value pointer.
    assert(accessChain.swizzle.size() == 0);
    assert(accessChain.component == NoResult);

    return lvalue;
}

void Builder::dump(std::vector<unsigned int>& out) const
{
    // Header, before first instructions:
    out.push_back(MagicNumber);
    out.push_back(Version);
    out.push_back(builderNumber);
    out.push_back(uniqueId + 1);
    out.push_back(0);

    // First instructions, some created on the spot here:
    if (source != SourceLanguageUnknown) {
        Instruction sourceInst(0, 0, OpSource);
        sourceInst.addImmediateOperand(source);
        sourceInst.addImmediateOperand(sourceVersion);
        sourceInst.dump(out);
    }
    for (int e = 0; e < (int)extensions.size(); ++e) {
        Instruction extInst(0, 0, OpSourceExtension);
        extInst.addStringOperand(extensions[e]);
        extInst.dump(out);
    }

    // TBD: OpExtension ...

    // Capabilities
    for (auto cap : capabilities) {
        Instruction capInst(0, 0, OpCapability);
        capInst.addImmediateOperand(cap);
        capInst.dump(out);
    }

    dumpInstructions(out, imports);
    Instruction memInst(0, 0, OpMemoryModel);
    memInst.addImmediateOperand(addressModel);
    memInst.addImmediateOperand(memoryModel);
    memInst.dump(out);

    // Instructions saved up while building:
    dumpInstructions(out, entryPoints);
    dumpInstructions(out, executionModes);
    dumpInstructions(out, names);
    dumpInstructions(out, lines);
    dumpInstructions(out, decorations);
    dumpInstructions(out, constantsTypesGlobals);
    dumpInstructions(out, externals);

    // The functions
    module.dump(out);
}

//
// Protected methods.
//

Id Builder::collapseAccessChain()
{
    // TODO: bring in an individual component swizzle here, so that a pointer 
    // all the way to the component level can be created.
    assert(accessChain.isRValue == false);

    if (accessChain.indexChain.size() > 0) {
        if (accessChain.instr == 0) {
            StorageClass storageClass = (StorageClass)module.getStorageClass(getTypeId(accessChain.base));
            accessChain.instr = createAccessChain(storageClass, accessChain.base, accessChain.indexChain);
        }

        return accessChain.instr;
    } else
        return accessChain.base;
}

// clear out swizzle if it is redundant
void Builder::simplifyAccessChainSwizzle()
{
    // If the swizzle has fewer components than the vector, it is subsetting, and must stay
    // to preserve that fact.
    if (getNumTypeComponents(accessChain.preSwizzleBaseType) > (int)accessChain.swizzle.size())
        return;

    // if components are out of order, it is a swizzle
    for (unsigned int i = 0; i < accessChain.swizzle.size(); ++i) {
        if (i != accessChain.swizzle[i])
            return;
    }

    // otherwise, there is no need to track this swizzle
    accessChain.swizzle.clear();
    if (accessChain.component == NoResult)
        accessChain.preSwizzleBaseType = NoType;
}

// clear out swizzle if it can become part of the indexes
void Builder::mergeAccessChainSwizzle()
{
    // is there even a chance of doing something?  Need a single-component swizzle
    if ((accessChain.swizzle.size() > 1) ||
        (accessChain.swizzle.size() == 0 && accessChain.component == NoResult))
        return;

    // TODO: optimization: remove this, but for now confine this to non-dynamic accesses
    // (the above test is correct when this is removed.)
    if (accessChain.component != NoResult)
        return;

    // move the swizzle over to the indexes
    if (accessChain.swizzle.size() == 1)
        accessChain.indexChain.push_back(makeUintConstant(accessChain.swizzle.front()));
    else
        accessChain.indexChain.push_back(accessChain.component);

    // now there is no need to track this swizzle
    accessChain.component = NoResult;
    accessChain.preSwizzleBaseType = NoType;
    accessChain.swizzle.clear();
}

// Utility method for creating a new block and setting the insert point to
// be in it. This is useful for flow-control operations that need a "dummy"
// block proceeding them (e.g. instructions after a discard, etc).
void Builder::createAndSetNoPredecessorBlock(const char* /*name*/)
{
    Block* block = new Block(getUniqueId(), buildPoint->getParent());
    block->setUnreachable();
    buildPoint->getParent().addBlock(block);
    setBuildPoint(block);

    //if (name)
    //    addName(block->getId(), name);
}

// Comments in header
void Builder::createBranch(Block* block)
{
    Instruction* branch = new Instruction(OpBranch);
    branch->addIdOperand(block->getId());
    buildPoint->addInstruction(branch);
    block->addPredecessor(buildPoint);
}

void Builder::createSelectionMerge(Block* mergeBlock, unsigned int control)
{
    Instruction* merge = new Instruction(OpSelectionMerge);
    merge->addIdOperand(mergeBlock->getId());
    merge->addImmediateOperand(control);
    buildPoint->addInstruction(merge);
}

void Builder::createLoopMerge(Block* mergeBlock, Block* continueBlock, unsigned int control)
{
    Instruction* merge = new Instruction(OpLoopMerge);
    merge->addIdOperand(mergeBlock->getId());
    merge->addIdOperand(continueBlock->getId());
    merge->addImmediateOperand(control);
    buildPoint->addInstruction(merge);
}

void Builder::createConditionalBranch(Id condition, Block* thenBlock, Block* elseBlock)
{
    Instruction* branch = new Instruction(OpBranchConditional);
    branch->addIdOperand(condition);
    branch->addIdOperand(thenBlock->getId());
    branch->addIdOperand(elseBlock->getId());
    buildPoint->addInstruction(branch);
    thenBlock->addPredecessor(buildPoint);
    elseBlock->addPredecessor(buildPoint);
}

void Builder::dumpInstructions(std::vector<unsigned int>& out, const std::vector<Instruction*>& instructions) const
{
    for (int i = 0; i < (int)instructions.size(); ++i) {
        instructions[i]->dump(out);
    }
}

void TbdFunctionality(const char* tbd)
{
    static std::unordered_set<const char*> issued;

    if (issued.find(tbd) == issued.end()) {
        printf("TBD functionality: %s\n", tbd);
        issued.insert(tbd);
    }
}

void MissingFunctionality(const char* fun)
{
    printf("Missing functionality: %s\n", fun);
    exit(1);
}

Builder::Loop::Loop(Builder& builder, bool testFirstArg)
  : function(&builder.getBuildPoint()->getParent()),
    header(new Block(builder.getUniqueId(), *function)),
    merge(new Block(builder.getUniqueId(), *function)),
    body(new Block(builder.getUniqueId(), *function)),
    testFirst(testFirstArg),
    isFirstIteration(nullptr)
{
    if (!testFirst)
    {
// You may be tempted to rewrite this as
// new Instruction(builder.getUniqueId(), builder.makeBoolType(), OpPhi);
// This will cause subtle test failures because builder.getUniqueId(),
// and builder.makeBoolType() can then get run in a compiler-specific
// order making tests fail for certain configurations.
        Id instructionId = builder.getUniqueId();
        isFirstIteration = new Instruction(instructionId, builder.makeBoolType(), OpPhi);
    }
}

}; // end spv namespace
