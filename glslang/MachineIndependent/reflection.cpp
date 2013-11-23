//
//Copyright (C) 2013 LunarG, Inc.
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

#include "../Include/Common.h"
#include "reflection.h"
#include "localintermediate.h"

#include "gl_types.h"

//
// Grow the reflection database through a friend traverser class of TReflection and a 
// collection of functions to do a liveness traversal that note what uniforms are used
// in semantically non-dead code.
//
// Can be used multiple times, once per stage, to grow a program reflection.
//
// High-level algorithm for one stage:
//
// 1. Put main() on list of live functions.
//
// 2. Traverse any live function, while skipping if-tests with a compile-time constant 
//    condition of false, and while adding any encountered function calls to the live 
//    function list.
//
//    Repeat until the live function list is empty.
//
// 3. Add any encountered uniform variables and blocks to the reflection database.
//
// Can be attempted with a failed link, but will return false if recursion had been detected, or 
// there wasn't exactly one main.
//

namespace glslang {

//
// The traverser: mostly pass through, except 
//  - processing function-call nodes to push live functions onto the stack of functions to process
//  - processing binary nodes to see if they are dereferences of an aggregates to track
//  - processing symbol nodes to see if they are non-aggregate objects to track
//  - processing selection nodes to trim semantically dead code
//
// This is in the glslang namespace directly so it can be a friend of TReflection.
//

class TLiveTraverser : public TIntermTraverser {
public:
    TLiveTraverser(const TIntermediate& i, TReflection& r) : intermediate(i), reflection(r) { }

    // Track live funtions as well as uniforms, so that we don't visit dead functions
    // and only visit each function once.
    void addFunctionCall(TIntermAggregate* call)
    {
        // just use the map to ensure we process each function at most once
        if (reflection.nameToIndex.find(call->getName()) == reflection.nameToIndex.end()) {
            reflection.nameToIndex[call->getName()] = -1;
            pushFunction(call->getName());
        }
    }

    // Add a simple reference to a uniform variable to the uniform database, no dereference involved.
    // However, no dereference doesn't mean simple... it could be a complex aggregate.
    void addUniform(const TIntermSymbol& base)
    {
        if (processedDerefs.find(&base) == processedDerefs.end()) {
            processedDerefs.insert(&base);

            // Use a degenerate (empty) set of dereferences to immediately put as at the end of
            // the dereference change expected by blowUpActiveAggregate.
            TList<TIntermBinary*> derefs;
            blowUpActiveAggregate(base.getType(), base.getName(), derefs, derefs.end(), -1, -1, 0);
        }
    }

    static const int baseAlignmentVec4Std140;

    // align a value:  if 'value' is not aligned to 'alignment', move it up to a multiple of alignment
    void align(int& value, int alignment)
    {
        int error = value % alignment;
        if (error)
            value += alignment - error;
    }

    // return the size and alignment of a scalar
    int getBaseAlignmentScalar(const TType& type, int& size)
    {
        switch (type.getBasicType()) {
        case EbtDouble:  size = 8; return 8;
        default:         size = 4; return 4;
        }
    }

    // Implement base-alignment and size rules from section 7.6.2.2 Standard Uniform Block Layout
    // Operates recursively.
    // If std140 is true, it does the rounding up to vec4 size required by std140, 
    // otherwise it does not, yielding std430 rules.
    //
    // Returns the size of the type.
    int getBaseAlignment(const TType& type, int& size, bool std140)
    {
        int alignment;

        // rules 4, 6, and 8
        if (type.isArray()) {
            TType derefType(type, 0);
            alignment = getBaseAlignment(derefType, size, std140);
            if (std140)
                alignment = std::max(baseAlignmentVec4Std140, alignment);
            align(size, alignment);
            size *= type.getArraySize();
            return alignment;
        }

        // rule 9
        if (type.getBasicType() == EbtStruct) {
            const TTypeList& memberList = *type.getStruct();

            size = 0;
            int maxAlignment = std140 ? baseAlignmentVec4Std140 : 0;
            for (size_t m = 0; m < memberList.size(); ++m) {
                int memberSize;
                int memberAlignment = getBaseAlignment(*memberList[m].type, memberSize, std140);
                maxAlignment = std::max(maxAlignment, memberAlignment);
                align(size, memberAlignment);         
                size += memberSize;
            }

            return maxAlignment;
        }

        // rule 1
        if (type.isScalar())
            return getBaseAlignmentScalar(type, size);

        // rules 2 and 3
        if (type.isVector()) {
            int scalarAlign = getBaseAlignmentScalar(type, size);
            switch (type.getVectorSize()) {
            case 2:
                size *= 2;
                return 2 * scalarAlign;
            default: 
                size *= type.getVectorSize();
                return 4 * scalarAlign;
            }
        }

        // rules 5 and 7
        if (type.isMatrix()) {
            TType derefType(type, 0);
            
            // rule 5: deref to row, not to column, meaning the size of vector is num columns instead of num rows
            if (type.getQualifier().layoutMatrix == ElmRowMajor)
                derefType.setElementType(derefType.getBasicType(), type.getMatrixCols(), 0, 0, 0);
            
            alignment = getBaseAlignment(derefType, size, std140);
            if (std140)
                alignment = std::max(baseAlignmentVec4Std140, alignment);
            align(size, alignment);
            if (type.getQualifier().layoutMatrix == ElmRowMajor)
                size *= type.getMatrixRows();
            else
                size *= type.getMatrixCols();

            return alignment;
        }

        assert(0);  // all cases should be covered above
        size = baseAlignmentVec4Std140;
        return baseAlignmentVec4Std140;
    }

    // Calculate the offset of a block member, using the recursively defined
    // block offset rules.
    int getBlockMemberOffset(const TType& blockType, int index)
    {
        // TODO: reflection performance: cache intermediate results instead of recomputing them

        int offset = 0;
        const TTypeList& memberList = *blockType.getStruct();        
        int memberSize;
        for (int m = 0; m < index; ++m) {
            int memberAlignment = getBaseAlignment(*memberList[m].type, memberSize, blockType.getQualifier().layoutPacking == ElpStd140);
            align(offset, memberAlignment);
            offset += memberSize;
        }
        int memberAlignment = getBaseAlignment(*memberList[index].type, memberSize, blockType.getQualifier().layoutPacking == ElpStd140);
        align(offset, memberAlignment);

        return offset;
    }

    // Calculate the block data size.
    // Arrayness is not taken into account, each element is backed by a separate buffer.
    int getBlockSize(const TType& blockType)
    {
        int size = 0;
        const TTypeList& memberList = *blockType.getStruct();        
        int memberSize;
        for (size_t m = 0; m < memberList.size(); ++m) {
            int memberAlignment = getBaseAlignment(*memberList[m].type, memberSize, blockType.getQualifier().layoutPacking == ElpStd140);
            align(size, memberAlignment);
            size += memberSize;
        }

        return size;
    }

    // Traverse the provided deref chain, including the base, and
    // - build a full reflection-granularity name, array size, etc. entry out of it, if it goes down to that granularity
    // - recursively expand any variable array index in the middle of that traversal
    // - recursively expand what's left at the end if the deref chain did not reach down to reflection granularity
    //
    // arraySize tracks, just for the final dereference in the chain, if there was a specific known size.
    // A value of 0 for arraySize will mean to use the full array's size.
    void blowUpActiveAggregate(const TType& baseType, const TString& baseName, const TList<TIntermBinary*>& derefs, 
                               TList<TIntermBinary*>::const_iterator deref, int offset, int blockIndex, int arraySize)
    {
        // process the part of the derefence chain that was explicit in the shader
        TString name = baseName;
        const TType* terminalType = &baseType;
        for (; deref != derefs.end(); ++deref) {
            TIntermBinary* visitNode = *deref;
            terminalType = &visitNode->getType();
            int index;
            switch (visitNode->getOp()) {
            case EOpIndexIndirect:
                // Visit all the indices of this array, and for each one add on the remaining dereferencing
                for (int i = 0; i < visitNode->getLeft()->getType().getArraySize(); ++i) {
                    TString newBaseName = name;
                    if (baseType.getBasicType() != EbtBlock)
                        newBaseName.append(TString("[") + String(i) + "]");
                    TList<TIntermBinary*>::const_iterator nextDeref = deref;
                    ++nextDeref;
                    TType derefType(*terminalType, 0);
                    blowUpActiveAggregate(derefType, newBaseName, derefs, nextDeref, offset, blockIndex, arraySize);
                }

                // it was all completed in the recursive calls above
                return;
            case EOpIndexDirect:
                index = visitNode->getRight()->getAsConstantUnion()->getConstArray()[0].getIConst();
                if (baseType.getBasicType() != EbtBlock)
                    name.append(TString("[") + String(index) + "]");
                break;
            case EOpIndexDirectStruct:
                index = visitNode->getRight()->getAsConstantUnion()->getConstArray()[0].getIConst();
                if (offset >= 0)
                    offset += getBlockMemberOffset(visitNode->getLeft()->getType(), index);
                if (name.size() > 0)
                    name.append(".");
                name.append((*visitNode->getLeft()->getType().getStruct())[index].type->getFieldName());
                break;
            default:
                break;
            }
        }
        
        // if the terminalType is still too coarse a granularity, this is still an aggregate to expand, expand it...
        if (! isReflectionGranularity(*terminalType)) {
            if (terminalType->isArray()) {
                // Visit all the indices of this array, and for each one, 
                // fully explode the remaining aggregate to dereference
                for (int i = 0; i < terminalType->getArraySize(); ++i) {
                    TString newBaseName = name;
                    newBaseName.append(TString("[") + String(i) + "]");
                    TType derefType(*terminalType, 0);
                    blowUpActiveAggregate(derefType, newBaseName, derefs, derefs.end(), offset, blockIndex, 0);
                }
            } else {
                // Visit all members of this aggregate, and for each one, 
                // fully explode the remaining aggregate to dereference
                const TTypeList& typeList = *terminalType->getStruct();
                for (size_t i = 0; i < typeList.size(); ++i) {
                    TString newBaseName = name;
                    newBaseName.append(TString(".") + typeList[i].type->getFieldName());
                    TType derefType(*terminalType, i);
                    blowUpActiveAggregate(derefType, newBaseName, derefs, derefs.end(), offset, blockIndex, 0);
                }
            }

            // it was all completed in the recursive calls above
            return;
        }

        // Finally, add a full string to the reflection database, and update the array size if necessary.
        // If the derefenced entity to record is an array, compute the size and update the maximum size.

        // there might not be a final array dereference, it could have been copied as an array object
        if (arraySize == 0)
            arraySize = mapToGlArraySize(*terminalType);

        TReflection::TNameToIndex::const_iterator it = reflection.nameToIndex.find(name);
        if (it == reflection.nameToIndex.end()) {
            reflection.nameToIndex[name] = reflection.indexToUniform.size();                        
            reflection.indexToUniform.push_back(TObjectReflection(name, offset, mapToGlType(*terminalType), arraySize, blockIndex));
        } else if (arraySize > 1) {
            int& reflectedArraySize = reflection.indexToUniform[it->second].size;
            reflectedArraySize = std::max(arraySize, reflectedArraySize);
        }
    }

    // Add a uniform dereference where blocks/struct/arrays are involved in the access.
    // Handles the situation where the left node is at the correct or too coarse a
    // granularity for reflection.  (That is, further dereferences up the tree will be 
    // skipped.) Earlier dereferences, down the tree, will be handled
    // at the same time, and logged to prevent reprocessing as the tree is traversed.
    //
    // Note: Other things like the following must be caught elsewhere:
    //  - a simple non-array, non-struct variable (no dereference even conceivable)
    //  - an aggregrate consumed en masse, without a dereference
    //
    // So, this code is for cases like 
    //   - a struct/block dereferencing a member (whether the member is array or not)
    //   - an array of struct
    //   - structs/arrays containing the above
    //
    void addDereferencedUniform(TIntermBinary* topNode)
    {
        // See if too fine-grained to process (wait to get further down the tree)
        const TType& leftType = topNode->getLeft()->getType();
        if ((leftType.isVector() || leftType.isMatrix()) && ! leftType.isArray())
            return;

        // We have an array or structure or block dereference, see if it's a uniform 
        // based dereference (if not, skip it).
        TIntermSymbol* base = findBase(topNode);
        if (! base || base->getQualifier().storage != EvqUniform)
            return;
            
        // See if we've already processed this (e.g., in the middle of something 
        // we did earlier), and if so skip it
        if (processedDerefs.find(topNode) != processedDerefs.end())
            return;

        // Process this uniform dereference

        int offset = -1;
        int blockIndex = -1;
        bool anonymous = false;

        // See if we need to record the block itself
        bool block = base->getBasicType() == EbtBlock;
        if (block) {
            offset = 0;
            anonymous = base->getName().compare(0, 6, "__anon") == 0;
            if (base->getType().isArray()) {
                assert(! anonymous);
                for (int e = 0; e < base->getType().getArraySize(); ++e)
                    blockIndex = addBlockName(base->getType().getTypeName() + "[" + String(e) + "]", getBlockSize(base->getType()));
            } else
                blockIndex = addBlockName(base->getType().getTypeName(), getBlockSize(base->getType()));
        }

        // Process the dereference chain, backward, accumulating the pieces for later forward traversal.
        // If the topNode is a reflection-granularity-array dereference, don't include that last dereference.
        TList<TIntermBinary*> derefs;
        for (TIntermBinary* visitNode = topNode; visitNode; visitNode = visitNode->getLeft()->getAsBinaryNode()) {
            if (isReflectionGranularity(visitNode->getLeft()->getType()))
                continue;

            derefs.push_front(visitNode);
            processedDerefs.insert(visitNode);
        }
        processedDerefs.insert(base);

        // See if we have a specific array size to stick to while enumerating the explosion of the aggregate
        int arraySize = 0;
        if (isReflectionGranularity(topNode->getLeft()->getType()) && topNode->getLeft()->isArray()) {
            if (topNode->getOp() == EOpIndexDirect)
                arraySize = topNode->getRight()->getAsConstantUnion()->getConstArray()[0].getIConst() + 1;
        }

        // Put the dereference chain together, forward
        TString baseName;
        if (! anonymous) {
            if (block)
                baseName = base->getType().getTypeName();
            else
                baseName = base->getName();
        }
        blowUpActiveAggregate(base->getType(), baseName, derefs, derefs.begin(), offset, blockIndex, arraySize);
    }

    int addBlockName(const TString& name, int size)
    {
        int blockIndex;
        TReflection::TNameToIndex::const_iterator it = reflection.nameToIndex.find(name);
        if (reflection.nameToIndex.find(name) == reflection.nameToIndex.end()) {
            blockIndex = reflection.indexToUniformBlock.size();
            reflection.nameToIndex[name] = blockIndex;
            reflection.indexToUniformBlock.push_back(TObjectReflection(name, -1, -1, size, -1));
        } else
            blockIndex = it->second;

        return blockIndex;
    }

    //
    // Given a function name, find its subroot in the tree, and push it onto the stack of 
    // functions left to process.
    //
    void pushFunction(const TString& name)
    {
        TIntermSequence& globals = intermediate.getTreeRoot()->getAsAggregate()->getSequence();
        for (unsigned int f = 0; f < globals.size(); ++f) {
            TIntermAggregate* candidate = globals[f]->getAsAggregate();
            if (candidate && candidate->getOp() == EOpFunction && candidate->getName() == name) {
                functions.push_back(candidate);
                break;
            }
        }
    }

    // Are we at a level in a dereference chain at which individual active uniform queries are made?
    bool isReflectionGranularity(const TType& type)
    {
        return type.getBasicType() != EbtBlock && type.getBasicType() != EbtStruct;
    }

    // For a binary operation indexing into an aggregate, chase down the base of the aggregate.
    // Return 0 if the topology does not fit this situation.
    TIntermSymbol* findBase(const TIntermBinary* node)
    {
        TIntermSymbol *base = node->getLeft()->getAsSymbolNode();
        if (base)
            return base;
        TIntermBinary* left = node->getLeft()->getAsBinaryNode();
        if (! left)
            return 0;

        return findBase(left);
    }

    //
    // Translate a glslang sampler type into the GL API #define number.
    //
    int mapSamplerToGlType(TSampler sampler)
    {
        if (! sampler.image) {
            // a sampler...
            switch (sampler.type) {
            case EbtFloat:
                switch (sampler.dim) {
                case Esd1D:
                    switch (sampler.shadow) {
                    case false: return sampler.arrayed ? GL_SAMPLER_1D_ARRAY : GL_SAMPLER_1D;
                    case true:  return sampler.arrayed ? GL_SAMPLER_1D_ARRAY_SHADOW : GL_SAMPLER_1D_SHADOW;
                    }
                case Esd2D:
                    switch (sampler.ms) {
                    case false:
                        switch (sampler.shadow) {
                        case false: return sampler.arrayed ? GL_SAMPLER_2D_ARRAY : GL_SAMPLER_2D;
                        case true:  return sampler.arrayed ? GL_SAMPLER_2D_ARRAY_SHADOW : GL_SAMPLER_2D_SHADOW;
                        }
                    case true:      return sampler.arrayed ? GL_SAMPLER_2D_MULTISAMPLE_ARRAY : GL_SAMPLER_2D_MULTISAMPLE;
                    }
                case Esd3D:
                    return GL_SAMPLER_3D;
                case EsdCube:
                    switch (sampler.shadow) {
                    case false: return sampler.arrayed ? GL_SAMPLER_CUBE_MAP_ARRAY : GL_SAMPLER_CUBE;
                    case true:  return sampler.arrayed ? GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW : GL_SAMPLER_CUBE_SHADOW;
                    }
                case EsdRect:
                    return sampler.shadow ? GL_SAMPLER_2D_RECT_SHADOW : GL_SAMPLER_2D_RECT;
                case EsdBuffer:
                    return GL_SAMPLER_BUFFER;
                }
            case EbtInt:
                switch (sampler.dim) {
                case Esd1D:
                    return sampler.arrayed ? GL_INT_SAMPLER_1D_ARRAY : GL_INT_SAMPLER_1D;
                case Esd2D:
                    switch (sampler.ms) {
                    case false:  return sampler.arrayed ? GL_INT_SAMPLER_2D_ARRAY : GL_INT_SAMPLER_2D;
                    case true:   return sampler.arrayed ? GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY : GL_INT_SAMPLER_2D_MULTISAMPLE;
                    }
                case Esd3D:
                    return GL_INT_SAMPLER_3D;
                case EsdCube:
                    return sampler.arrayed ? GL_INT_SAMPLER_CUBE_MAP_ARRAY : GL_INT_SAMPLER_CUBE;
                case EsdRect:
                    return GL_INT_SAMPLER_2D_RECT;
                case EsdBuffer:
                    return GL_INT_SAMPLER_BUFFER;
                }
            case EbtUint:
                switch (sampler.dim) {
                case Esd1D:
                    return sampler.arrayed ? GL_UNSIGNED_INT_SAMPLER_1D_ARRAY : GL_UNSIGNED_INT_SAMPLER_1D;
                case Esd2D:
                    switch (sampler.ms) {
                    case false:  return sampler.arrayed ? GL_UNSIGNED_INT_SAMPLER_2D_ARRAY : GL_UNSIGNED_INT_SAMPLER_2D;
                    case true:   return sampler.arrayed ? GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY : GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE;
                    }
                case Esd3D:
                    return GL_UNSIGNED_INT_SAMPLER_3D;
                case EsdCube:
                    return sampler.arrayed ? GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY : GL_UNSIGNED_INT_SAMPLER_CUBE;
                case EsdRect:
                    return GL_UNSIGNED_INT_SAMPLER_2D_RECT;
                case EsdBuffer:
                    return GL_UNSIGNED_INT_SAMPLER_BUFFER;
                }
            default:
                return 0;
            }
        } else { 
            // an image...
            switch (sampler.type) {
            case EbtFloat:
                switch (sampler.dim) {
                case Esd1D:
                    return sampler.arrayed ? GL_IMAGE_1D_ARRAY : GL_IMAGE_1D;
                case Esd2D:
                    switch (sampler.ms) {
                    case false:     return sampler.arrayed ? GL_IMAGE_2D_ARRAY : GL_IMAGE_2D;
                    case true:      return sampler.arrayed ? GL_IMAGE_2D_MULTISAMPLE_ARRAY : GL_IMAGE_2D_MULTISAMPLE;
                    }
                case Esd3D:
                    return GL_IMAGE_3D;
                case EsdCube:
                    return sampler.arrayed ? GL_IMAGE_CUBE_MAP_ARRAY : GL_IMAGE_CUBE;
                case EsdRect:
                    return GL_IMAGE_2D_RECT;
                case EsdBuffer:
                    return GL_IMAGE_BUFFER;
                }
            case EbtInt:
                switch (sampler.dim) {
                case Esd1D:
                    return sampler.arrayed ? GL_INT_IMAGE_1D_ARRAY : GL_INT_IMAGE_1D;
                case Esd2D:
                    switch (sampler.ms) {
                    case false:  return sampler.arrayed ? GL_INT_IMAGE_2D_ARRAY : GL_INT_IMAGE_2D;
                    case true:   return sampler.arrayed ? GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY : GL_INT_IMAGE_2D_MULTISAMPLE;
                    }
                case Esd3D:
                    return GL_INT_IMAGE_3D;
                case EsdCube:
                    return sampler.arrayed ? GL_INT_IMAGE_CUBE_MAP_ARRAY : GL_INT_IMAGE_CUBE;
                case EsdRect:
                    return GL_INT_IMAGE_2D_RECT;
                case EsdBuffer:
                    return GL_INT_IMAGE_BUFFER;
                }
            case EbtUint:
                switch (sampler.dim) {
                case Esd1D:
                    return sampler.arrayed ? GL_UNSIGNED_INT_IMAGE_1D_ARRAY : GL_UNSIGNED_INT_IMAGE_1D;
                case Esd2D:
                    switch (sampler.ms) {
                    case false:  return sampler.arrayed ? GL_UNSIGNED_INT_IMAGE_2D_ARRAY : GL_UNSIGNED_INT_IMAGE_2D;
                    case true:   return sampler.arrayed ? GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY : GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE;
                    }
                case Esd3D:
                    return GL_UNSIGNED_INT_IMAGE_3D;
                case EsdCube:
                    return sampler.arrayed ? GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY : GL_UNSIGNED_INT_IMAGE_CUBE;
                case EsdRect:
                    return GL_UNSIGNED_INT_IMAGE_2D_RECT;
                case EsdBuffer:
                    return GL_UNSIGNED_INT_IMAGE_BUFFER;
                }
            default:
                return 0;
            }
        }
    }

    //
    // Translate a glslang type into the GL API #define number.
    // Ignores arrayness.
    //
    int mapToGlType(const TType& type)
    {
        switch (type.getBasicType()) {
        case EbtSampler:
            return mapSamplerToGlType(type.getSampler());
        case EbtStruct:
        case EbtBlock:
        case EbtVoid:
            return 0;
        default:
            break;
        }

        if (type.isVector()) {
            int offset = type.getVectorSize() - 2;
            switch (type.getBasicType()) {
            case EbtFloat:     return GL_FLOAT_VEC2        + offset;
            case EbtDouble:    return GL_DOUBLE_VEC2       + offset;
            case EbtInt:       return GL_INT_VEC2          + offset;
            case EbtUint:      return GL_UNSIGNED_INT_VEC2 + offset;
            case EbtBool:      return GL_BOOL_VEC2         + offset;
            default:           return 0;
            }
        }
        if (type.isMatrix()) {
            switch (type.getBasicType()) {
            case EbtFloat:
                switch (type.getMatrixCols()) {
                case 2:
                    switch (type.getMatrixRows()) {
                    case 2:    return GL_FLOAT_MAT2;
                    case 3:    return GL_FLOAT_MAT2x3;
                    case 4:    return GL_FLOAT_MAT2x4;
                    default:   return 0;
                    }
                case 3:
                    switch (type.getMatrixRows()) {
                    case 2:    return GL_FLOAT_MAT3x2;
                    case 3:    return GL_FLOAT_MAT3;
                    case 4:    return GL_FLOAT_MAT3x4;
                    default:   return 0;
                    }
                case 4:
                    switch (type.getMatrixRows()) {
                    case 2:    return GL_FLOAT_MAT4x2;
                    case 3:    return GL_FLOAT_MAT4x3;
                    case 4:    return GL_FLOAT_MAT4;
                    default:   return 0;
                    }
                }
            case EbtDouble:
                switch (type.getMatrixCols()) {
                case 2:
                    switch (type.getMatrixRows()) {
                    case 2:    return GL_DOUBLE_MAT2;
                    case 3:    return GL_DOUBLE_MAT2x3;
                    case 4:    return GL_DOUBLE_MAT2x4;
                    default:   return 0;
                    }
                case 3:
                    switch (type.getMatrixRows()) {
                    case 2:    return GL_DOUBLE_MAT3x2;
                    case 3:    return GL_DOUBLE_MAT3;
                    case 4:    return GL_DOUBLE_MAT3x4;
                    default:   return 0;
                    }
                case 4:
                    switch (type.getMatrixRows()) {
                    case 2:    return GL_DOUBLE_MAT4x2;
                    case 3:    return GL_DOUBLE_MAT4x3;
                    case 4:    return GL_DOUBLE_MAT4;
                    default:   return 0;
                    }
                }
            default:
                return 0;
            }
        }
        if (type.getVectorSize() == 1) {
            switch (type.getBasicType()) {
            case EbtFloat:     return GL_FLOAT;
            case EbtDouble:    return GL_DOUBLE;
            case EbtInt:       return GL_INT;
            case EbtUint:      return GL_UNSIGNED_INT;
            case EbtBool:      return GL_BOOL;
            default:           return 0;
            }
        }

        return 0;
    }

    int mapToGlArraySize(const TType& type)
    {
        return type.isArray() ? type.getArraySize() : 1;
    }
    
    typedef std::list<TIntermAggregate*> TFunctionStack;
    TFunctionStack functions;
    const TIntermediate& intermediate;
    TReflection& reflection;
    std::set<const TIntermNode*> processedDerefs;
};

const int TLiveTraverser::baseAlignmentVec4Std140 = 16;

namespace {

//
// Implement the traversal functions of interest.
//

// To catch which function calls are not dead, and hence which functions must be visited.
bool LiveAggregate(bool /* preVisit */, TIntermAggregate* node, TIntermTraverser* it)
{
    TLiveTraverser* oit = static_cast<TLiveTraverser*>(it);

    if (node->getOp() == EOpFunctionCall)
        oit->addFunctionCall(node);

    return true; // traverse this subtree
}

// To catch dereferenced aggregates that must be reflected.
// This catches them at the highest level possible in the tree.
bool LiveBinary(bool /* preVisit */, TIntermBinary* node, TIntermTraverser* it)
{
    TLiveTraverser* oit = static_cast<TLiveTraverser*>(it);

    switch (node->getOp()) {
    case EOpIndexDirect:
    case EOpIndexIndirect:
    case EOpIndexDirectStruct:
        oit->addDereferencedUniform(node);
        break;
    default:
        break;
    }

    // still need to visit everything below, which could contain sub-expressions 
    // containing different uniforms
    return true;
}

// To reflect non-dereferenced objects.
void LiveSymbol(TIntermSymbol* base, TIntermTraverser* it)
{
    TLiveTraverser* oit = static_cast<TLiveTraverser*>(it);

    if (base->getQualifier().storage == EvqUniform)
        oit->addUniform(*base);
}

// To prune semantically dead paths.
bool LiveSelection(bool /* preVisit */,  TIntermSelection* node, TIntermTraverser* it)
{
    TLiveTraverser* oit = static_cast<TLiveTraverser*>(it);

    TIntermConstantUnion* constant = node->getCondition()->getAsConstantUnion();
    if (constant) {
        // cull the path that is dead
        if (constant->getConstArray()[0].getBConst() == true && node->getTrueBlock())
            node->getTrueBlock()->traverse(it);
        if (constant->getConstArray()[0].getBConst() == false && node->getFalseBlock())
            node->getFalseBlock()->traverse(it);

        return false; // don't traverse any more, we did it all above
    } else
        return true; // traverse the whole subtree
}

} // end anonymous namespace

//
// Implement TReflection methods.
//

// Merge live symbols from 'intermediate' into the existing reflection database.
//
// Returns false if the input is too malformed to do this.
bool TReflection::addStage(EShLanguage, const TIntermediate& intermediate)
{    
    if (intermediate.getNumMains() != 1 || intermediate.isRecursive())
        return false;

    TLiveTraverser it(intermediate, *this);
    it.visitSymbol = LiveSymbol;
    it.visitSelection = LiveSelection;
    it.visitBinary = LiveBinary;
    it.visitAggregate = LiveAggregate;

    // put main() on functions to process
    it.pushFunction("main(");

    // process all the functions
    while (! it.functions.empty()) {
        TIntermNode* function = it.functions.back();
        it.functions.pop_back();
        function->traverse(&it);
    }

    return true;
}

void TReflection::dump()
{
    printf("Uniform reflection:\n");
    for (size_t i = 0; i < indexToUniform.size(); ++i)
        indexToUniform[i].dump();
    printf("\n");

    printf("Uniform block reflection:\n");
    for (size_t i = 0; i < indexToUniformBlock.size(); ++i)
        indexToUniformBlock[i].dump();
    printf("\n");

    //printf("Live names\n");
    //for (TNameToIndex::const_iterator it = nameToIndex.begin(); it != nameToIndex.end(); ++it)
    //    printf("%s: %d\n", it->first.c_str(), it->second);
    //printf("\n");
}

} // end namespace glslang
