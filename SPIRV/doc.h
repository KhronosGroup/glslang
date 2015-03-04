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
// Return English versions of instruction/operand information.
// This can be used for disassembly, printing documentation, etc.
//

#include "spirv.h"

#include <vector>

namespace spv {

// Fill in all the parameters of the instruction set
void Parameterize();

// Return the English names of all the enums.
const char* SourceString(int);
const char* AddressingString(int);
const char* MemoryString(int);
const char* ExecutionModelString(int);
const char* ExecutionModeString(int);
const char* StorageClassString(int);
const char* DecorationString(int);
const char* BuiltInString(int);
const char* DimensionString(int);
const char* SelectControlString(int);
const char* LoopControlString(int);
const char* FunctionControlString(int);
const char* SamplerAddressingModeString(int);
const char* SamplerFilterModeString(int);
const char* FPFastMathString(int);
const char* FPRoundingModeString(int);
const char* LinkageTypeString(int);
const char* FuncParamAttrString(int);
const char* AccessQualifierString(int);
const char* MemorySemanticsString(int);
const char* MemoryAccessString(int);
const char* ExecutionScopeString(int);
const char* GroupOperationString(int);
const char* KernelEnqueueFlagsString(int);
const char* KernelProfilingInfoString(int);

// For parameterizing operands.
enum OperandClass {
    OperandNone,
    OperandId,
    OperandOptionalId,
    OperandVariableIds,
    OperandVariableLiterals,
    OperandVariableLiteralId,
    OperandLiteralNumber,
    OperandLiteralString,
    OperandSource,
    OperandExecutionModel,
    OperandAddressing,
    OperandMemory,
    OperandExecutionMode,
    OperandStorage,
    OperandDimensionality,
    OperandSamplerAddressingMode,
    OperandSamplerFilterMode,
    OperandFPFastMath,
    OperandFPRoundingMode,
    OperandLinkageType,
    OperandFuncParamAttr,
    OperandDecoration,
    OperandBuiltIn,
    OperandSelect,
    OperandLoop,
    OperandFunction,
    OperandAccessQualifier,
    OperandMemorySemantics,
    OperandMemoryAccess,
    OperandExecutionScope,
	OperandGroupOperation,
    OperandKernelEnqueueFlags,
    OperandKernelProfilingInfo,
    OperandCount
};

// Parameterize a set of operands with their OperandClass(es) and descriptions.
class OperandParameters {
public:
    OperandParameters() { }
    void push(OperandClass oc)
    {
        opClass.push_back(oc);
    }
    OperandClass getClass(int op) const { return opClass[op]; }
    int getNum() const { return (int)opClass.size(); }

protected:
    std::vector<OperandClass> opClass;
};

// Parameterize an instruction's logical format, including its known set of operands,
// per OperandParameters above.
class InstructionParameters {
public:
    InstructionParameters() :
        typePresent(true),         // most normal, only exceptions have to be spelled out
        resultPresent(true),       // most normal, only exceptions have to be spelled out
        opName(0)
    { }

    void setResultAndType(bool r, bool t)
    {
        resultPresent = r;
        typePresent = t;
    }

    bool hasResult() const { return resultPresent != 0; }
    bool hasType()   const { return typePresent != 0; }

    const char* opName;
    OperandParameters operands;

protected:
    int typePresent   : 1;
    int resultPresent : 1;
};

// The set of objects that hold all the instruction/operand
// parameterization information.
extern InstructionParameters InstructionDesc[spv::OpCount];

};  // end namespace spv
