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
// Programmatically fill in instruction/operand information.
//

#include "spirv.h"

#include "doc.h"

#include <stdio.h>
#include <string.h>
#include <algorithm>

#define LINE_BREAK " +\n"
#define GAP " +\n +\n"
#define NOTE GAP "*Note:* "

namespace spv {

// The set of objects that hold all the instruction/operand
// parameterization information.
InstructionParameters InstructionDesc[spv::OpCount];

// Set up all the parameterizing descriptions of the opcodes, operands, etc.
void Parameterize()
{
    // Exceptions to having a result <id> and a resulting type <id>.
    // (Everything is initialized to have both).

    InstructionDesc[OpNop]            .setResultAndType(false, false);
    InstructionDesc[OpSource]         .setResultAndType(false, false);
    InstructionDesc[OpSourceExtension].setResultAndType(false, false);
    InstructionDesc[OpExtension]      .setResultAndType(false, false);
    InstructionDesc[OpExtInstImport]  .setResultAndType(true,  false);
    InstructionDesc[OpMemoryModel]    .setResultAndType(false, false);
    InstructionDesc[OpEntryPoint]     .setResultAndType(false, false);
    InstructionDesc[OpExecutionMode]  .setResultAndType(false, false);

    InstructionDesc[OpTypeVoid]        .setResultAndType(true,  false);
    InstructionDesc[OpTypeBool]        .setResultAndType(true,  false);
    InstructionDesc[OpTypeInt]         .setResultAndType(true,  false);
    InstructionDesc[OpTypeFloat]       .setResultAndType(true,  false);
    InstructionDesc[OpTypeVector]      .setResultAndType(true,  false);
    InstructionDesc[OpTypeMatrix]      .setResultAndType(true,  false);
    InstructionDesc[OpTypeSampler]     .setResultAndType(true,  false);
    InstructionDesc[OpTypeFilter]      .setResultAndType(true,  false);
    InstructionDesc[OpTypeArray]       .setResultAndType(true,  false);
    InstructionDesc[OpTypeRuntimeArray].setResultAndType(true,  false);
    InstructionDesc[OpTypeStruct]      .setResultAndType(true,  false);
    InstructionDesc[OpTypeOpaque]      .setResultAndType(true,  false);
    InstructionDesc[OpTypePointer]     .setResultAndType(true,  false);
    InstructionDesc[OpTypeFunction]    .setResultAndType(true,  false);

    InstructionDesc[OpTypeEvent]       .setResultAndType(true,  false);
    InstructionDesc[OpTypeDeviceEvent] .setResultAndType(true,  false);
    InstructionDesc[OpTypeReserveId]   .setResultAndType(true,  false);
    InstructionDesc[OpTypeQueue]       .setResultAndType(true,  false);
    InstructionDesc[OpTypePipe]        .setResultAndType(true,  false);
    InstructionDesc[OpFunctionEnd]        .setResultAndType(false, false);
    InstructionDesc[OpStore]              .setResultAndType(false, false);
    InstructionDesc[OpDecorationGroup]    .setResultAndType(true,  false);
    InstructionDesc[OpDecorate]           .setResultAndType(false, false);
    InstructionDesc[OpMemberDecorate]     .setResultAndType(false, false);
    InstructionDesc[OpGroupDecorate]      .setResultAndType(false, false);
    InstructionDesc[OpGroupMemberDecorate].setResultAndType(false, false);
    InstructionDesc[OpName]               .setResultAndType(false, false);
    InstructionDesc[OpMemberName]         .setResultAndType(false, false);
    InstructionDesc[OpString]             .setResultAndType(true,  false);
    InstructionDesc[OpLine]               .setResultAndType(false, false);

    InstructionDesc[OpCopyMemory]     .setResultAndType(false, false);
    InstructionDesc[OpCopyMemorySized].setResultAndType(false, false);

    InstructionDesc[OpEmitVertex]        .setResultAndType(false, false);
    InstructionDesc[OpEndPrimitive]      .setResultAndType(false, false);
    InstructionDesc[OpEmitStreamVertex]  .setResultAndType(false, false);
    InstructionDesc[OpEndStreamPrimitive].setResultAndType(false, false);

    InstructionDesc[OpControlBarrier].setResultAndType(false, false);
    InstructionDesc[OpMemoryBarrier] .setResultAndType(false, false);
    
    InstructionDesc[OpAtomicInit].setResultAndType(false, false);
    InstructionDesc[OpAtomicStore].setResultAndType(false, false);

    InstructionDesc[OpLoopMerge]        .setResultAndType(false, false);
    InstructionDesc[OpSelectionMerge]   .setResultAndType(false, false);
    InstructionDesc[OpLabel]            .setResultAndType(true,  false);
    InstructionDesc[OpBranch]           .setResultAndType(false, false);
    InstructionDesc[OpBranchConditional].setResultAndType(false, false);
    InstructionDesc[OpSwitch]           .setResultAndType(false, false);
    InstructionDesc[OpKill]             .setResultAndType(false, false);
    InstructionDesc[OpReturn]           .setResultAndType(false, false);
    InstructionDesc[OpReturnValue]      .setResultAndType(false, false);
    InstructionDesc[OpUnreachable]      .setResultAndType(false, false);

    InstructionDesc[OpLifetimeStart]    .setResultAndType(false, false);
    InstructionDesc[OpLifetimeStop]     .setResultAndType(false, false);

    InstructionDesc[OpCompileFlag]      .setResultAndType(false, false);
    InstructionDesc[OpCommitReadPipe]   .setResultAndType(false, false);
    InstructionDesc[OpCommitWritePipe].setResultAndType(false, false);
    InstructionDesc[OpGroupCommitWritePipe].setResultAndType(false, false);
    InstructionDesc[OpGroupCommitReadPipe].setResultAndType(false, false);
    InstructionDesc[OpCaptureEventProfilingInfo].setResultAndType(false, false);
    InstructionDesc[OpSetUserEventStatus].setResultAndType(false, false);
    InstructionDesc[OpRetainEvent].setResultAndType(false, false);
    InstructionDesc[OpReleaseEvent].setResultAndType(false, false);

    // set name of operator, an initial set of <id> style operands, and the description

    #define SET_OPNAME(index) InstructionDesc[index].opName = #index;

    SET_OPNAME(OpNop);
    SET_OPNAME(OpSource);
    SET_OPNAME(OpSourceExtension);
    SET_OPNAME(OpExtension);
    SET_OPNAME(OpExtInstImport);
    SET_OPNAME(OpMemoryModel);
    SET_OPNAME(OpEntryPoint);
    SET_OPNAME(OpExecutionMode);

    SET_OPNAME(OpTypeVoid);
    SET_OPNAME(OpTypeInt);
    SET_OPNAME(OpTypeBool);
    SET_OPNAME(OpTypeFloat);
    SET_OPNAME(OpTypeVector);
    SET_OPNAME(OpTypeMatrix);
    SET_OPNAME(OpTypeSampler);
    SET_OPNAME(OpTypeFilter);
    SET_OPNAME(OpTypeArray);
    SET_OPNAME(OpTypeRuntimeArray);
    SET_OPNAME(OpTypeStruct);
    SET_OPNAME(OpTypeOpaque);
    SET_OPNAME(OpTypePointer);
    SET_OPNAME(OpTypeFunction);

    SET_OPNAME(OpTypeEvent);
    SET_OPNAME(OpTypeDeviceEvent);
    SET_OPNAME(OpTypeReserveId);
    SET_OPNAME(OpTypeQueue);
    SET_OPNAME(OpTypePipe);

    SET_OPNAME(OpConstantTrue);
    SET_OPNAME(OpConstantFalse);
    SET_OPNAME(OpConstant);
    SET_OPNAME(OpConstantComposite);
    SET_OPNAME(OpConstantNullPointer);
    SET_OPNAME(OpConstantNullObject);
    SET_OPNAME(OpConstantSampler);

    SET_OPNAME(OpSpecConstantTrue);
    SET_OPNAME(OpSpecConstantFalse);
    SET_OPNAME(OpSpecConstant);
    SET_OPNAME(OpSpecConstantComposite);

    SET_OPNAME(OpVariable);
    SET_OPNAME(OpVariableArray);

    SET_OPNAME(OpFunction);
    SET_OPNAME(OpFunctionParameter);
    SET_OPNAME(OpFunctionEnd);
    SET_OPNAME(OpFunctionCall);

    SET_OPNAME(OpExtInst);

    SET_OPNAME(OpUndef);
    SET_OPNAME(OpLoad);
    SET_OPNAME(OpStore);
    SET_OPNAME(OpPhi);

    SET_OPNAME(OpDecorationGroup);
    SET_OPNAME(OpDecorate);
    SET_OPNAME(OpMemberDecorate);
    SET_OPNAME(OpGroupDecorate);
    SET_OPNAME(OpGroupMemberDecorate);
    SET_OPNAME(OpName);
    SET_OPNAME(OpMemberName);
    SET_OPNAME(OpString);
    SET_OPNAME(OpLine);

    SET_OPNAME(OpVectorExtractDynamic);
    SET_OPNAME(OpVectorInsertDynamic);
    SET_OPNAME(OpVectorShuffle);

    SET_OPNAME(OpCompositeConstruct);
    SET_OPNAME(OpCompositeExtract);
    SET_OPNAME(OpCompositeInsert);

    SET_OPNAME(OpCopyObject);
    SET_OPNAME(OpCopyMemory);
    SET_OPNAME(OpCopyMemorySized);

    SET_OPNAME(OpSampler);

    SET_OPNAME(OpTextureSample);
    SET_OPNAME(OpTextureSampleDref);
    SET_OPNAME(OpTextureSampleLod);
    SET_OPNAME(OpTextureSampleProj);
    SET_OPNAME(OpTextureSampleGrad);
    SET_OPNAME(OpTextureSampleOffset);
    SET_OPNAME(OpTextureSampleProjLod);
    SET_OPNAME(OpTextureSampleProjGrad);
    SET_OPNAME(OpTextureSampleLodOffset);
    SET_OPNAME(OpTextureSampleProjOffset);
    SET_OPNAME(OpTextureSampleGradOffset);
    SET_OPNAME(OpTextureSampleProjLodOffset);
    SET_OPNAME(OpTextureSampleProjGradOffset);
    SET_OPNAME(OpTextureFetchTexel);
    SET_OPNAME(OpTextureFetchTexelOffset);
    SET_OPNAME(OpTextureFetchSample);
    SET_OPNAME(OpTextureFetchBuffer);
    SET_OPNAME(OpTextureGather);
    SET_OPNAME(OpTextureGatherOffset);
    SET_OPNAME(OpTextureGatherOffsets);
    SET_OPNAME(OpTextureQuerySizeLod);
    SET_OPNAME(OpTextureQuerySize);
    SET_OPNAME(OpTextureQueryLod);
    SET_OPNAME(OpTextureQueryLevels);
    SET_OPNAME(OpTextureQuerySamples);

    SET_OPNAME(OpAccessChain);
    SET_OPNAME(OpInBoundsAccessChain);

    SET_OPNAME(OpSNegate);
    SET_OPNAME(OpFNegate);
    SET_OPNAME(OpNot);
    SET_OPNAME(OpAny);
    SET_OPNAME(OpAll);

    SET_OPNAME(OpConvertFToU);
    SET_OPNAME(OpConvertFToS);
    SET_OPNAME(OpConvertSToF);
    SET_OPNAME(OpConvertUToF);
    SET_OPNAME(OpFConvert);
    SET_OPNAME(OpSConvert);
    SET_OPNAME(OpUConvert);
    SET_OPNAME(OpConvertPtrToU);
    SET_OPNAME(OpConvertUToPtr);
    SET_OPNAME(OpPtrCastToGeneric);
    SET_OPNAME(OpGenericCastToPtr);
    SET_OPNAME(OpGenericCastToPtrExplicit);
    SET_OPNAME(OpGenericPtrMemSemantics);
    SET_OPNAME(OpBitcast);
    SET_OPNAME(OpTranspose);

    SET_OPNAME(OpIsNan);
    SET_OPNAME(OpIsInf);
    SET_OPNAME(OpIsFinite);
    SET_OPNAME(OpIsNormal);
    SET_OPNAME(OpSignBitSet);
    SET_OPNAME(OpLessOrGreater);
    SET_OPNAME(OpOrdered);
    SET_OPNAME(OpUnordered);

    SET_OPNAME(OpArrayLength);
    
    SET_OPNAME(OpIAdd);
    SET_OPNAME(OpFAdd);
    SET_OPNAME(OpISub);
    SET_OPNAME(OpFSub);
    SET_OPNAME(OpIMul);
    SET_OPNAME(OpFMul);
    SET_OPNAME(OpUDiv);
    SET_OPNAME(OpSDiv);
    SET_OPNAME(OpFDiv);
    SET_OPNAME(OpUMod);
    SET_OPNAME(OpSRem);
    SET_OPNAME(OpSMod);
    SET_OPNAME(OpFRem);
    SET_OPNAME(OpFMod);
    
    SET_OPNAME(OpVectorTimesScalar);
    SET_OPNAME(OpMatrixTimesScalar);
    SET_OPNAME(OpVectorTimesMatrix);
    SET_OPNAME(OpMatrixTimesVector);
    SET_OPNAME(OpMatrixTimesMatrix);
    SET_OPNAME(OpOuterProduct);
    SET_OPNAME(OpDot);

    SET_OPNAME(OpShiftRightLogical);
    SET_OPNAME(OpShiftRightArithmetic);
    SET_OPNAME(OpShiftLeftLogical);
    SET_OPNAME(OpLogicalOr);
    SET_OPNAME(OpLogicalXor);
    SET_OPNAME(OpLogicalAnd);

    SET_OPNAME(OpBitwiseOr);
    SET_OPNAME(OpBitwiseXor);
    SET_OPNAME(OpBitwiseAnd);

    SET_OPNAME(OpSelect);

    SET_OPNAME(OpIEqual);
    SET_OPNAME(OpFOrdEqual);
    SET_OPNAME(OpFUnordEqual);
    SET_OPNAME(OpINotEqual);
    SET_OPNAME(OpFOrdNotEqual);
    SET_OPNAME(OpFUnordNotEqual);
    SET_OPNAME(OpULessThan);
    SET_OPNAME(OpSLessThan);
    SET_OPNAME(OpFOrdLessThan);
    SET_OPNAME(OpFUnordLessThan);
    SET_OPNAME(OpUGreaterThan);
    SET_OPNAME(OpSGreaterThan);
    SET_OPNAME(OpFOrdGreaterThan);
    SET_OPNAME(OpFUnordGreaterThan);
    SET_OPNAME(OpULessThanEqual);
    SET_OPNAME(OpSLessThanEqual);
    SET_OPNAME(OpFOrdLessThanEqual);
    SET_OPNAME(OpFUnordLessThanEqual);
    SET_OPNAME(OpUGreaterThanEqual);
    SET_OPNAME(OpSGreaterThanEqual);
    SET_OPNAME(OpFOrdGreaterThanEqual);
    SET_OPNAME(OpFUnordGreaterThanEqual);

    SET_OPNAME(OpDPdx);
    SET_OPNAME(OpDPdy);
    SET_OPNAME(OpFwidth);
    SET_OPNAME(OpDPdxFine);
    SET_OPNAME(OpDPdyFine);
    SET_OPNAME(OpFwidthFine);
    SET_OPNAME(OpDPdxCoarse);
    SET_OPNAME(OpDPdyCoarse);
    SET_OPNAME(OpFwidthCoarse);
    SET_OPNAME(OpEmitVertex);
    SET_OPNAME(OpEndPrimitive);
    SET_OPNAME(OpEmitStreamVertex);
    SET_OPNAME(OpEndStreamPrimitive);
    SET_OPNAME(OpControlBarrier);
    SET_OPNAME(OpMemoryBarrier);

    SET_OPNAME(OpImagePointer);

    SET_OPNAME(OpAtomicInit);
    SET_OPNAME(OpAtomicLoad);
    SET_OPNAME(OpAtomicStore);
    SET_OPNAME(OpAtomicExchange);
    SET_OPNAME(OpAtomicCompareExchange);
    SET_OPNAME(OpAtomicCompareExchangeWeak);
    SET_OPNAME(OpAtomicIIncrement);
    SET_OPNAME(OpAtomicIDecrement);
    SET_OPNAME(OpAtomicIAdd);
    SET_OPNAME(OpAtomicISub);
    SET_OPNAME(OpAtomicUMin);
    SET_OPNAME(OpAtomicUMax);
    SET_OPNAME(OpAtomicAnd);
    SET_OPNAME(OpAtomicOr);
    SET_OPNAME(OpAtomicXor);

    SET_OPNAME(OpLoopMerge);
    SET_OPNAME(OpSelectionMerge);
    SET_OPNAME(OpLabel);
    SET_OPNAME(OpBranch);
    SET_OPNAME(OpBranchConditional);
    SET_OPNAME(OpSwitch);
    SET_OPNAME(OpKill);
    SET_OPNAME(OpReturn);
    SET_OPNAME(OpReturnValue);
    SET_OPNAME(OpUnreachable);    

    SET_OPNAME(OpLifetimeStart);
    SET_OPNAME(OpLifetimeStop);    
    SET_OPNAME(OpCompileFlag);
    
    SET_OPNAME(OpAsyncGroupCopy);
    SET_OPNAME(OpWaitGroupEvents);

    SET_OPNAME(OpGroupAll);
    SET_OPNAME(OpGroupAny);
    SET_OPNAME(OpGroupBroadcast);
    SET_OPNAME(OpGroupIAdd);
    SET_OPNAME(OpGroupFAdd);
    SET_OPNAME(OpGroupFMin);
    SET_OPNAME(OpGroupUMin);
    SET_OPNAME(OpGroupSMin);
    SET_OPNAME(OpGroupFMax);
    SET_OPNAME(OpGroupUMax);
    SET_OPNAME(OpGroupSMax);

    SET_OPNAME(OpReadPipe);
    SET_OPNAME(OpWritePipe);
    SET_OPNAME(OpReservedReadPipe);
    SET_OPNAME(OpReservedWritePipe);
    SET_OPNAME(OpReserveReadPipePackets);
    SET_OPNAME(OpReserveWritePipePackets);
    SET_OPNAME(OpCommitReadPipe);
    SET_OPNAME(OpCommitWritePipe);
    SET_OPNAME(OpIsValidReserveId);
    SET_OPNAME(OpGetNumPipePackets);
    SET_OPNAME(OpGetMaxPipePackets);
    SET_OPNAME(OpGroupReserveReadPipePackets);
    SET_OPNAME(OpGroupReserveWritePipePackets);
    SET_OPNAME(OpGroupCommitReadPipe);
    SET_OPNAME(OpGroupCommitWritePipe);

    // Device-side enqueueing of kernels 
    SET_OPNAME(OpBuildNDRange);
    SET_OPNAME(OpGetDefaultQueue);
    SET_OPNAME(OpCaptureEventProfilingInfo);
    SET_OPNAME(OpSetUserEventStatus);
    SET_OPNAME(OpIsValidEvent);
    SET_OPNAME(OpCreateUserEvent);
    SET_OPNAME(OpRetainEvent);
    SET_OPNAME(OpReleaseEvent);
    SET_OPNAME(OpGetKernelWorkGroupSize);
    SET_OPNAME(OpGetKernelPreferredWorkGroupSizeMultiple);
    SET_OPNAME(OpGetKernelNDrangeMaxSubGroupSize);
    SET_OPNAME(OpGetKernelNDrangeSubGroupCount);
    SET_OPNAME(OpEnqueueKernel);
    SET_OPNAME(OpEnqueueMarker);

    InstructionDesc[OpSource].operands.push(OperandSource);
    InstructionDesc[OpSource].operands.push(OperandLiteralNumber);
    InstructionDesc[OpSourceExtension].operands.push(OperandLiteralString);
    InstructionDesc[OpName].operands.push(OperandId);
    InstructionDesc[OpName].operands.push(OperandLiteralString);
    InstructionDesc[OpMemberName].operands.push(OperandId);
    InstructionDesc[OpMemberName].operands.push(OperandLiteralNumber);
    InstructionDesc[OpMemberName].operands.push(OperandLiteralString);
    InstructionDesc[OpString].operands.push(OperandLiteralString);
    InstructionDesc[OpLine].operands.push(OperandId);
    InstructionDesc[OpLine].operands.push(OperandId);
    InstructionDesc[OpLine].operands.push(OperandLiteralNumber);
    InstructionDesc[OpLine].operands.push(OperandLiteralNumber);
    InstructionDesc[OpExtension].operands.push(OperandLiteralString);
    InstructionDesc[OpExtInstImport].operands.push(OperandLiteralString);
    InstructionDesc[OpMemoryModel].operands.push(OperandAddressing);
    InstructionDesc[OpMemoryModel].operands.push(OperandMemory);
    InstructionDesc[OpEntryPoint].operands.push(OperandExecutionModel);
    InstructionDesc[OpEntryPoint].operands.push(OperandId);
    InstructionDesc[OpExecutionMode].operands.push(OperandId);
    InstructionDesc[OpExecutionMode].operands.push(OperandExecutionMode);
    InstructionDesc[OpExecutionMode].operands.push(OperandVariableLiterals);
    InstructionDesc[OpTypeInt].operands.push(OperandLiteralNumber);
    InstructionDesc[OpTypeInt].operands.push(OperandLiteralNumber);
    InstructionDesc[OpTypeFloat].operands.push(OperandLiteralNumber);
    InstructionDesc[OpTypeVector].operands.push(OperandId);
    InstructionDesc[OpTypeVector].operands.push(OperandLiteralNumber);
    InstructionDesc[OpTypeMatrix].operands.push(OperandId);
    InstructionDesc[OpTypeMatrix].operands.push(OperandLiteralNumber);
    InstructionDesc[OpTypeSampler].operands.push(OperandId);
    InstructionDesc[OpTypeSampler].operands.push(OperandDimensionality);
    InstructionDesc[OpTypeSampler].operands.push(OperandLiteralNumber);
    InstructionDesc[OpTypeSampler].operands.push(OperandLiteralNumber);
    InstructionDesc[OpTypeSampler].operands.push(OperandLiteralNumber);
    InstructionDesc[OpTypeSampler].operands.push(OperandLiteralNumber);
    InstructionDesc[OpTypeSampler].operands.push(OperandOptionalId);
    InstructionDesc[OpTypeArray].operands.push(OperandId);
    InstructionDesc[OpTypeArray].operands.push(OperandId);
    InstructionDesc[OpTypeRuntimeArray].operands.push(OperandId);
    InstructionDesc[OpTypeStruct].operands.push(OperandVariableIds);
    InstructionDesc[OpTypeOpaque].operands.push(OperandLiteralString);
    InstructionDesc[OpTypePointer].operands.push(OperandStorage);
    InstructionDesc[OpTypePointer].operands.push(OperandId);
    InstructionDesc[OpTypePipe].operands.push(OperandId);
    InstructionDesc[OpTypePipe].operands.push(OperandAccessQualifier);
    InstructionDesc[OpTypeFunction].operands.push(OperandId);
    InstructionDesc[OpTypeFunction].operands.push(OperandVariableIds);
    InstructionDesc[OpConstant].operands.push(OperandVariableLiterals);
    InstructionDesc[OpConstantComposite].operands.push(OperandVariableIds);
    InstructionDesc[OpConstantSampler].operands.push(OperandLiteralNumber);
    InstructionDesc[OpConstantSampler].operands.push(OperandLiteralNumber);
    InstructionDesc[OpConstantSampler].operands.push(OperandLiteralNumber);
    InstructionDesc[OpSpecConstant].operands.push(OperandVariableLiterals);
    InstructionDesc[OpSpecConstantComposite].operands.push(OperandVariableIds);
    InstructionDesc[OpVariable].operands.push(OperandStorage);
    InstructionDesc[OpVariable].operands.push(OperandOptionalId);
    InstructionDesc[OpVariableArray].operands.push(OperandStorage);
    InstructionDesc[OpVariableArray].operands.push(OperandId);
    InstructionDesc[OpFunction].operands.push(OperandFunction);
    InstructionDesc[OpFunction].operands.push(OperandId);
    InstructionDesc[OpFunctionCall].operands.push(OperandId);
    InstructionDesc[OpFunctionCall].operands.push(OperandVariableIds);
    InstructionDesc[OpExtInst].operands.push(OperandId);
    InstructionDesc[OpExtInst].operands.push(OperandLiteralNumber);
    InstructionDesc[OpExtInst].operands.push(OperandVariableIds);
    InstructionDesc[OpLoad].operands.push(OperandId);
    InstructionDesc[OpLoad].operands.push(OperandVariableLiterals);
    InstructionDesc[OpStore].operands.push(OperandId);
    InstructionDesc[OpStore].operands.push(OperandId);
    InstructionDesc[OpStore].operands.push(OperandVariableLiterals);
    InstructionDesc[OpPhi].operands.push(OperandVariableIds);
    InstructionDesc[OpDecorate].operands.push(OperandId);
    InstructionDesc[OpDecorate].operands.push(OperandDecoration);
    InstructionDesc[OpDecorate].operands.push(OperandVariableLiterals);
    InstructionDesc[OpMemberDecorate].operands.push(OperandId);
    InstructionDesc[OpMemberDecorate].operands.push(OperandLiteralNumber);
    InstructionDesc[OpMemberDecorate].operands.push(OperandDecoration);
    InstructionDesc[OpMemberDecorate].operands.push(OperandVariableLiterals);
    InstructionDesc[OpGroupDecorate].operands.push(OperandId);
    InstructionDesc[OpGroupDecorate].operands.push(OperandVariableIds);
    InstructionDesc[OpGroupMemberDecorate].operands.push(OperandId);
    InstructionDesc[OpGroupMemberDecorate].operands.push(OperandVariableIds);
    InstructionDesc[OpVectorExtractDynamic].operands.push(OperandId);
    InstructionDesc[OpVectorExtractDynamic].operands.push(OperandId);
    InstructionDesc[OpVectorInsertDynamic].operands.push(OperandId);
    InstructionDesc[OpVectorInsertDynamic].operands.push(OperandId);
    InstructionDesc[OpVectorInsertDynamic].operands.push(OperandId);
    InstructionDesc[OpVectorShuffle].operands.push(OperandId);
    InstructionDesc[OpVectorShuffle].operands.push(OperandId);
    InstructionDesc[OpVectorShuffle].operands.push(OperandVariableLiterals);
    InstructionDesc[OpCompositeConstruct].operands.push(OperandVariableIds);
    InstructionDesc[OpCompositeExtract].operands.push(OperandId);
    InstructionDesc[OpCompositeExtract].operands.push(OperandVariableLiterals);
    InstructionDesc[OpCompositeInsert].operands.push(OperandId);
    InstructionDesc[OpCompositeInsert].operands.push(OperandId);
    InstructionDesc[OpCompositeInsert].operands.push(OperandVariableLiterals);
    InstructionDesc[OpCopyObject].operands.push(OperandId);
    InstructionDesc[OpCopyMemory].operands.push(OperandId);
    InstructionDesc[OpCopyMemory].operands.push(OperandId);
    InstructionDesc[OpCopyMemory].operands.push(OperandVariableLiterals);
    InstructionDesc[OpCopyMemorySized].operands.push(OperandId);
    InstructionDesc[OpCopyMemorySized].operands.push(OperandId);
    InstructionDesc[OpCopyMemorySized].operands.push(OperandId);
    InstructionDesc[OpCopyMemorySized].operands.push(OperandVariableLiterals);
    InstructionDesc[OpSampler].operands.push(OperandId);
    InstructionDesc[OpSampler].operands.push(OperandId);
    InstructionDesc[OpTextureSample].operands.push(OperandId);
    InstructionDesc[OpTextureSample].operands.push(OperandId);
    InstructionDesc[OpTextureSample].operands.push(OperandOptionalId);
    InstructionDesc[OpTextureSampleDref].operands.push(OperandId);
    InstructionDesc[OpTextureSampleDref].operands.push(OperandId);
    InstructionDesc[OpTextureSampleDref].operands.push(OperandId);
    InstructionDesc[OpTextureSampleLod].operands.push(OperandId);
    InstructionDesc[OpTextureSampleLod].operands.push(OperandId);
    InstructionDesc[OpTextureSampleLod].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProj].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProj].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProj].operands.push(OperandOptionalId);
    InstructionDesc[OpTextureSampleGrad].operands.push(OperandId);
    InstructionDesc[OpTextureSampleGrad].operands.push(OperandId);
    InstructionDesc[OpTextureSampleGrad].operands.push(OperandId);
    InstructionDesc[OpTextureSampleGrad].operands.push(OperandId);
    InstructionDesc[OpTextureSampleOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleOffset].operands.push(OperandOptionalId);
    InstructionDesc[OpTextureSampleProjLod].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjLod].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjLod].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjGrad].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjGrad].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjGrad].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjGrad].operands.push(OperandId);
    InstructionDesc[OpTextureSampleLodOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleLodOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleLodOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleLodOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjOffset].operands.push(OperandOptionalId);
    InstructionDesc[OpTextureSampleGradOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleGradOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleGradOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleGradOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleGradOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjLodOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjLodOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjLodOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjLodOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjGradOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjGradOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjGradOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjGradOffset].operands.push(OperandId);
    InstructionDesc[OpTextureSampleProjGradOffset].operands.push(OperandId);
    InstructionDesc[OpTextureFetchTexel].operands.push(OperandId);
    InstructionDesc[OpTextureFetchTexel].operands.push(OperandId);
    InstructionDesc[OpTextureFetchTexel].operands.push(OperandId);
    InstructionDesc[OpTextureFetchTexelOffset].operands.push(OperandId);
    InstructionDesc[OpTextureFetchTexelOffset].operands.push(OperandId);
    InstructionDesc[OpTextureFetchTexelOffset].operands.push(OperandId);
    InstructionDesc[OpTextureFetchSample].operands.push(OperandId);
    InstructionDesc[OpTextureFetchSample].operands.push(OperandId);
    InstructionDesc[OpTextureFetchSample].operands.push(OperandId);
    InstructionDesc[OpTextureFetchBuffer].operands.push(OperandId);
    InstructionDesc[OpTextureFetchBuffer].operands.push(OperandId);
    InstructionDesc[OpTextureGather].operands.push(OperandId);
    InstructionDesc[OpTextureGather].operands.push(OperandId);
    InstructionDesc[OpTextureGather].operands.push(OperandId);
    InstructionDesc[OpTextureGatherOffset].operands.push(OperandId);
    InstructionDesc[OpTextureGatherOffset].operands.push(OperandId);
    InstructionDesc[OpTextureGatherOffset].operands.push(OperandId);
    InstructionDesc[OpTextureGatherOffset].operands.push(OperandId);
    InstructionDesc[OpTextureGatherOffsets].operands.push(OperandId);
    InstructionDesc[OpTextureGatherOffsets].operands.push(OperandId);
    InstructionDesc[OpTextureGatherOffsets].operands.push(OperandId);
    InstructionDesc[OpTextureGatherOffsets].operands.push(OperandId);
    InstructionDesc[OpTextureQuerySizeLod].operands.push(OperandId);
    InstructionDesc[OpTextureQuerySizeLod].operands.push(OperandId);
    InstructionDesc[OpTextureQuerySize].operands.push(OperandId);
    InstructionDesc[OpTextureQueryLod].operands.push(OperandId);
    InstructionDesc[OpTextureQueryLod].operands.push(OperandId);
    InstructionDesc[OpTextureQueryLevels].operands.push(OperandId);
    InstructionDesc[OpTextureQuerySamples].operands.push(OperandId);
    InstructionDesc[OpAccessChain].operands.push(OperandId);
    InstructionDesc[OpAccessChain].operands.push(OperandVariableIds);
    InstructionDesc[OpInBoundsAccessChain].operands.push(OperandId);
    InstructionDesc[OpInBoundsAccessChain].operands.push(OperandVariableIds);
    InstructionDesc[OpSNegate].operands.push(OperandId);
    InstructionDesc[OpFNegate].operands.push(OperandId);
    InstructionDesc[OpNot].operands.push(OperandId);
    InstructionDesc[OpAny].operands.push(OperandId);
    InstructionDesc[OpAll].operands.push(OperandId);
    InstructionDesc[OpConvertFToU].operands.push(OperandId);
    InstructionDesc[OpConvertFToS].operands.push(OperandId);
    InstructionDesc[OpConvertSToF].operands.push(OperandId);
    InstructionDesc[OpConvertUToF].operands.push(OperandId);
    InstructionDesc[OpUConvert].operands.push(OperandId);
    InstructionDesc[OpSConvert].operands.push(OperandId);
    InstructionDesc[OpFConvert].operands.push(OperandId);
    InstructionDesc[OpConvertPtrToU].operands.push(OperandId);
    InstructionDesc[OpConvertUToPtr].operands.push(OperandId);
    InstructionDesc[OpPtrCastToGeneric].operands.push(OperandId);
    InstructionDesc[OpGenericCastToPtr].operands.push(OperandId);
    InstructionDesc[OpGenericCastToPtrExplicit].operands.push(OperandId);
    InstructionDesc[OpGenericCastToPtrExplicit].operands.push(OperandStorage);
    InstructionDesc[OpGenericPtrMemSemantics].operands.push(OperandId);
    InstructionDesc[OpBitcast].operands.push(OperandId);
    InstructionDesc[OpTranspose].operands.push(OperandId);
    InstructionDesc[OpIsNan].operands.push(OperandId);
    InstructionDesc[OpIsInf].operands.push(OperandId);
    InstructionDesc[OpIsFinite].operands.push(OperandId);
    InstructionDesc[OpIsNormal].operands.push(OperandId);
    InstructionDesc[OpSignBitSet].operands.push(OperandId);
    InstructionDesc[OpLessOrGreater].operands.push(OperandId);
    InstructionDesc[OpLessOrGreater].operands.push(OperandId);
    InstructionDesc[OpOrdered].operands.push(OperandId);
    InstructionDesc[OpOrdered].operands.push(OperandId);
    InstructionDesc[OpUnordered].operands.push(OperandId);
    InstructionDesc[OpUnordered].operands.push(OperandId);
    InstructionDesc[OpArrayLength].operands.push(OperandId);
    InstructionDesc[OpArrayLength].operands.push(OperandLiteralNumber);
    InstructionDesc[OpIAdd].operands.push(OperandId);
    InstructionDesc[OpIAdd].operands.push(OperandId);
    InstructionDesc[OpFAdd].operands.push(OperandId);
    InstructionDesc[OpFAdd].operands.push(OperandId);
    InstructionDesc[OpISub].operands.push(OperandId);
    InstructionDesc[OpISub].operands.push(OperandId);
    InstructionDesc[OpFSub].operands.push(OperandId);
    InstructionDesc[OpFSub].operands.push(OperandId);
    InstructionDesc[OpIMul].operands.push(OperandId);
    InstructionDesc[OpIMul].operands.push(OperandId);
    InstructionDesc[OpFMul].operands.push(OperandId);
    InstructionDesc[OpFMul].operands.push(OperandId);
    InstructionDesc[OpUDiv].operands.push(OperandId);
    InstructionDesc[OpUDiv].operands.push(OperandId);
    InstructionDesc[OpSDiv].operands.push(OperandId);
    InstructionDesc[OpSDiv].operands.push(OperandId);
    InstructionDesc[OpFDiv].operands.push(OperandId);
    InstructionDesc[OpFDiv].operands.push(OperandId);
    InstructionDesc[OpUMod].operands.push(OperandId);
    InstructionDesc[OpUMod].operands.push(OperandId);
    InstructionDesc[OpSRem].operands.push(OperandId);
    InstructionDesc[OpSRem].operands.push(OperandId);
    InstructionDesc[OpSMod].operands.push(OperandId);
    InstructionDesc[OpSMod].operands.push(OperandId);
    InstructionDesc[OpFRem].operands.push(OperandId);
    InstructionDesc[OpFRem].operands.push(OperandId);
    InstructionDesc[OpFMod].operands.push(OperandId);
    InstructionDesc[OpFMod].operands.push(OperandId);
    InstructionDesc[OpVectorTimesScalar].operands.push(OperandId);
    InstructionDesc[OpVectorTimesScalar].operands.push(OperandId);
    InstructionDesc[OpMatrixTimesScalar].operands.push(OperandId);
    InstructionDesc[OpMatrixTimesScalar].operands.push(OperandId);
    InstructionDesc[OpVectorTimesMatrix].operands.push(OperandId);
    InstructionDesc[OpVectorTimesMatrix].operands.push(OperandId);
    InstructionDesc[OpMatrixTimesVector].operands.push(OperandId);
    InstructionDesc[OpMatrixTimesVector].operands.push(OperandId);
    InstructionDesc[OpMatrixTimesMatrix].operands.push(OperandId);
    InstructionDesc[OpMatrixTimesMatrix].operands.push(OperandId);
    InstructionDesc[OpOuterProduct].operands.push(OperandId);
    InstructionDesc[OpOuterProduct].operands.push(OperandId);
    InstructionDesc[OpDot].operands.push(OperandId);
    InstructionDesc[OpDot].operands.push(OperandId);
    InstructionDesc[OpShiftRightLogical].operands.push(OperandId);
    InstructionDesc[OpShiftRightLogical].operands.push(OperandId);
    InstructionDesc[OpShiftRightArithmetic].operands.push(OperandId);
    InstructionDesc[OpShiftRightArithmetic].operands.push(OperandId);
    InstructionDesc[OpShiftLeftLogical].operands.push(OperandId);
    InstructionDesc[OpShiftLeftLogical].operands.push(OperandId);
    InstructionDesc[OpLogicalOr].operands.push(OperandId);
    InstructionDesc[OpLogicalOr].operands.push(OperandId);
    InstructionDesc[OpLogicalXor].operands.push(OperandId);
    InstructionDesc[OpLogicalXor].operands.push(OperandId);
    InstructionDesc[OpLogicalAnd].operands.push(OperandId);
    InstructionDesc[OpLogicalAnd].operands.push(OperandId);
    InstructionDesc[OpBitwiseOr].operands.push(OperandId);
    InstructionDesc[OpBitwiseOr].operands.push(OperandId);
    InstructionDesc[OpBitwiseXor].operands.push(OperandId);
    InstructionDesc[OpBitwiseXor].operands.push(OperandId);
    InstructionDesc[OpBitwiseAnd].operands.push(OperandId);
    InstructionDesc[OpBitwiseAnd].operands.push(OperandId);
    InstructionDesc[OpSelect].operands.push(OperandId);
    InstructionDesc[OpSelect].operands.push(OperandId);
    InstructionDesc[OpSelect].operands.push(OperandId);
    InstructionDesc[OpIEqual].operands.push(OperandId);
    InstructionDesc[OpIEqual].operands.push(OperandId);
    InstructionDesc[OpFOrdEqual].operands.push(OperandId);
    InstructionDesc[OpFOrdEqual].operands.push(OperandId);
    InstructionDesc[OpFUnordEqual].operands.push(OperandId);
    InstructionDesc[OpFUnordEqual].operands.push(OperandId);
    InstructionDesc[OpINotEqual].operands.push(OperandId);
    InstructionDesc[OpINotEqual].operands.push(OperandId);
    InstructionDesc[OpFOrdNotEqual].operands.push(OperandId);
    InstructionDesc[OpFOrdNotEqual].operands.push(OperandId);
    InstructionDesc[OpFUnordNotEqual].operands.push(OperandId);
    InstructionDesc[OpFUnordNotEqual].operands.push(OperandId);
    InstructionDesc[OpULessThan].operands.push(OperandId);
    InstructionDesc[OpULessThan].operands.push(OperandId);
    InstructionDesc[OpSLessThan].operands.push(OperandId);
    InstructionDesc[OpSLessThan].operands.push(OperandId);
    InstructionDesc[OpFOrdLessThan].operands.push(OperandId);
    InstructionDesc[OpFOrdLessThan].operands.push(OperandId);
    InstructionDesc[OpFUnordLessThan].operands.push(OperandId);
    InstructionDesc[OpFUnordLessThan].operands.push(OperandId);
    InstructionDesc[OpUGreaterThan].operands.push(OperandId);
    InstructionDesc[OpUGreaterThan].operands.push(OperandId);
    InstructionDesc[OpSGreaterThan].operands.push(OperandId);
    InstructionDesc[OpSGreaterThan].operands.push(OperandId);
    InstructionDesc[OpFOrdGreaterThan].operands.push(OperandId);
    InstructionDesc[OpFOrdGreaterThan].operands.push(OperandId);
    InstructionDesc[OpFUnordGreaterThan].operands.push(OperandId);
    InstructionDesc[OpFUnordGreaterThan].operands.push(OperandId);
    InstructionDesc[OpULessThanEqual].operands.push(OperandId);
    InstructionDesc[OpULessThanEqual].operands.push(OperandId);
    InstructionDesc[OpSLessThanEqual].operands.push(OperandId);
    InstructionDesc[OpSLessThanEqual].operands.push(OperandId);
    InstructionDesc[OpFOrdLessThanEqual].operands.push(OperandId);
    InstructionDesc[OpFOrdLessThanEqual].operands.push(OperandId);
    InstructionDesc[OpFUnordLessThanEqual].operands.push(OperandId);
    InstructionDesc[OpFUnordLessThanEqual].operands.push(OperandId);
    InstructionDesc[OpUGreaterThanEqual].operands.push(OperandId);
    InstructionDesc[OpUGreaterThanEqual].operands.push(OperandId);
    InstructionDesc[OpSGreaterThanEqual].operands.push(OperandId);
    InstructionDesc[OpSGreaterThanEqual].operands.push(OperandId);
    InstructionDesc[OpFOrdGreaterThanEqual].operands.push(OperandId);
    InstructionDesc[OpFOrdGreaterThanEqual].operands.push(OperandId);
    InstructionDesc[OpFUnordGreaterThanEqual].operands.push(OperandId);
    InstructionDesc[OpFUnordGreaterThanEqual].operands.push(OperandId);
    InstructionDesc[OpDPdx].operands.push(OperandId);
    InstructionDesc[OpDPdy].operands.push(OperandId);
    InstructionDesc[OpFwidth].operands.push(OperandId);
    InstructionDesc[OpDPdxFine].operands.push(OperandId);
    InstructionDesc[OpDPdyFine].operands.push(OperandId);
    InstructionDesc[OpFwidthFine].operands.push(OperandId);
    InstructionDesc[OpDPdxCoarse].operands.push(OperandId);
    InstructionDesc[OpDPdyCoarse].operands.push(OperandId);
    InstructionDesc[OpFwidthCoarse].operands.push(OperandId);
    InstructionDesc[OpEmitStreamVertex].operands.push(OperandId);
    InstructionDesc[OpEndStreamPrimitive].operands.push(OperandId);
    InstructionDesc[OpControlBarrier].operands.push(OperandExecutionScope);
    InstructionDesc[OpMemoryBarrier].operands.push(OperandExecutionScope);
    InstructionDesc[OpMemoryBarrier].operands.push(OperandMemorySemantics);
    InstructionDesc[OpImagePointer].operands.push(OperandId);
    InstructionDesc[OpImagePointer].operands.push(OperandId);
    InstructionDesc[OpImagePointer].operands.push(OperandId);
    InstructionDesc[OpAtomicInit].operands.push(OperandId);
    InstructionDesc[OpAtomicInit].operands.push(OperandId);
    InstructionDesc[OpAtomicLoad].operands.push(OperandId);
    InstructionDesc[OpAtomicLoad].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicLoad].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicStore].operands.push(OperandId);
    InstructionDesc[OpAtomicStore].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicStore].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicStore].operands.push(OperandId);
    InstructionDesc[OpAtomicExchange].operands.push(OperandId);
    InstructionDesc[OpAtomicExchange].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicExchange].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicExchange].operands.push(OperandId);
    InstructionDesc[OpAtomicCompareExchange].operands.push(OperandId);
    InstructionDesc[OpAtomicCompareExchange].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicCompareExchange].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicCompareExchange].operands.push(OperandId);
    InstructionDesc[OpAtomicCompareExchange].operands.push(OperandId);
    InstructionDesc[OpAtomicCompareExchangeWeak].operands.push(OperandId);
    InstructionDesc[OpAtomicCompareExchangeWeak].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicCompareExchangeWeak].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicCompareExchangeWeak].operands.push(OperandId);
    InstructionDesc[OpAtomicCompareExchangeWeak].operands.push(OperandId);
    InstructionDesc[OpAtomicIIncrement].operands.push(OperandId);
    InstructionDesc[OpAtomicIIncrement].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicIIncrement].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicIDecrement].operands.push(OperandId);
    InstructionDesc[OpAtomicIDecrement].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicIDecrement].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicIAdd].operands.push(OperandId);
    InstructionDesc[OpAtomicIAdd].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicIAdd].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicIAdd].operands.push(OperandId);
    InstructionDesc[OpAtomicISub].operands.push(OperandId);
    InstructionDesc[OpAtomicISub].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicISub].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicISub].operands.push(OperandId);
    InstructionDesc[OpAtomicUMin].operands.push(OperandId);
    InstructionDesc[OpAtomicUMin].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicUMin].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicUMin].operands.push(OperandId);
    InstructionDesc[OpAtomicUMax].operands.push(OperandId);
    InstructionDesc[OpAtomicUMax].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicUMax].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicUMax].operands.push(OperandId);
    InstructionDesc[OpAtomicAnd].operands.push(OperandId);
    InstructionDesc[OpAtomicAnd].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicAnd].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicAnd].operands.push(OperandId);
    InstructionDesc[OpAtomicOr].operands.push(OperandId);
    InstructionDesc[OpAtomicOr].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicOr].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicOr].operands.push(OperandId);
    InstructionDesc[OpAtomicXor].operands.push(OperandId);
    InstructionDesc[OpAtomicXor].operands.push(OperandExecutionScope);
    InstructionDesc[OpAtomicXor].operands.push(OperandMemorySemantics);
    InstructionDesc[OpAtomicXor].operands.push(OperandId);
    InstructionDesc[OpLoopMerge].operands.push(OperandId);
    InstructionDesc[OpLoopMerge].operands.push(OperandLoop);
    InstructionDesc[OpSelectionMerge].operands.push(OperandId);
    InstructionDesc[OpSelectionMerge].operands.push(OperandSelect);
    InstructionDesc[OpBranch].operands.push(OperandId);
    InstructionDesc[OpBranchConditional].operands.push(OperandId);
    InstructionDesc[OpBranchConditional].operands.push(OperandId);
    InstructionDesc[OpBranchConditional].operands.push(OperandId);
    InstructionDesc[OpBranchConditional].operands.push(OperandVariableLiterals);
    InstructionDesc[OpSwitch].operands.push(OperandId);
    InstructionDesc[OpSwitch].operands.push(OperandId);
    InstructionDesc[OpSwitch].operands.push(OperandVariableLiteralId);
    InstructionDesc[OpReturnValue].operands.push(OperandId);
    InstructionDesc[OpLifetimeStart].operands.push(OperandId);
    InstructionDesc[OpLifetimeStart].operands.push(OperandLiteralNumber);
    InstructionDesc[OpLifetimeStop].operands.push(OperandId);
    InstructionDesc[OpLifetimeStop].operands.push(OperandLiteralNumber);
    InstructionDesc[OpCompileFlag].operands.push(OperandLiteralString);
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandExecutionScope);
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandId);
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandId);
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandId);
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandId);
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandId);
    InstructionDesc[OpWaitGroupEvents].operands.push(OperandExecutionScope);
    InstructionDesc[OpWaitGroupEvents].operands.push(OperandId);
    InstructionDesc[OpWaitGroupEvents].operands.push(OperandId);
    InstructionDesc[OpGroupAll].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupAll].operands.push(OperandId);
    InstructionDesc[OpGroupAny].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupAny].operands.push(OperandId);
    InstructionDesc[OpGroupBroadcast].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupBroadcast].operands.push(OperandId);
    InstructionDesc[OpGroupBroadcast].operands.push(OperandId);
    InstructionDesc[OpGroupIAdd].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupIAdd].operands.push(OperandGroupOperation);
    InstructionDesc[OpGroupIAdd].operands.push(OperandId);
    InstructionDesc[OpGroupFAdd].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupFAdd].operands.push(OperandGroupOperation);
    InstructionDesc[OpGroupFAdd].operands.push(OperandId);
    InstructionDesc[OpGroupUMin].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupUMin].operands.push(OperandGroupOperation);
    InstructionDesc[OpGroupUMin].operands.push(OperandId);
    InstructionDesc[OpGroupSMin].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupSMin].operands.push(OperandGroupOperation);
    InstructionDesc[OpGroupSMin].operands.push(OperandId);
    InstructionDesc[OpGroupFMin].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupFMin].operands.push(OperandGroupOperation);
    InstructionDesc[OpGroupFMin].operands.push(OperandId);
    InstructionDesc[OpGroupUMax].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupUMax].operands.push(OperandGroupOperation);
    InstructionDesc[OpGroupUMax].operands.push(OperandId);
    InstructionDesc[OpGroupSMax].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupSMax].operands.push(OperandGroupOperation);
    InstructionDesc[OpGroupSMax].operands.push(OperandId);
    InstructionDesc[OpGroupFMax].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupFMax].operands.push(OperandGroupOperation);
    InstructionDesc[OpGroupFMax].operands.push(OperandId);
    InstructionDesc[OpReadPipe].operands.push(OperandId);
    InstructionDesc[OpReadPipe].operands.push(OperandId);
    InstructionDesc[OpWritePipe].operands.push(OperandId);
    InstructionDesc[OpWritePipe].operands.push(OperandId);
    InstructionDesc[OpReservedReadPipe].operands.push(OperandId);
    InstructionDesc[OpReservedReadPipe].operands.push(OperandId);
    InstructionDesc[OpReservedReadPipe].operands.push(OperandId);
    InstructionDesc[OpReservedReadPipe].operands.push(OperandId);
    InstructionDesc[OpReservedWritePipe].operands.push(OperandId);
    InstructionDesc[OpReservedWritePipe].operands.push(OperandId);
    InstructionDesc[OpReservedWritePipe].operands.push(OperandId);
    InstructionDesc[OpReservedWritePipe].operands.push(OperandId);
    InstructionDesc[OpReserveReadPipePackets].operands.push(OperandId);
    InstructionDesc[OpReserveReadPipePackets].operands.push(OperandId);
    InstructionDesc[OpReserveWritePipePackets].operands.push(OperandId);
    InstructionDesc[OpReserveWritePipePackets].operands.push(OperandId);
    InstructionDesc[OpCommitReadPipe].operands.push(OperandId);
    InstructionDesc[OpCommitReadPipe].operands.push(OperandId);
    InstructionDesc[OpCommitWritePipe].operands.push(OperandId);
    InstructionDesc[OpCommitWritePipe].operands.push(OperandId);
    InstructionDesc[OpIsValidReserveId].operands.push(OperandId);
    InstructionDesc[OpGetNumPipePackets].operands.push(OperandId);
    InstructionDesc[OpGetMaxPipePackets].operands.push(OperandId);
    InstructionDesc[OpGroupReserveReadPipePackets].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupReserveReadPipePackets].operands.push(OperandId);
    InstructionDesc[OpGroupReserveReadPipePackets].operands.push(OperandId);
    InstructionDesc[OpGroupReserveWritePipePackets].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupReserveWritePipePackets].operands.push(OperandId);
    InstructionDesc[OpGroupReserveWritePipePackets].operands.push(OperandId);
    InstructionDesc[OpGroupCommitReadPipe].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupCommitReadPipe].operands.push(OperandId);
    InstructionDesc[OpGroupCommitReadPipe].operands.push(OperandId);
    InstructionDesc[OpGroupCommitWritePipe].operands.push(OperandExecutionScope);
    InstructionDesc[OpGroupCommitWritePipe].operands.push(OperandId);
    InstructionDesc[OpGroupCommitWritePipe].operands.push(OperandId);
    InstructionDesc[OpBuildNDRange].operands.push(OperandId);
    InstructionDesc[OpBuildNDRange].operands.push(OperandId);
    InstructionDesc[OpBuildNDRange].operands.push(OperandId);
    InstructionDesc[OpCaptureEventProfilingInfo].operands.push(OperandId);
    InstructionDesc[OpCaptureEventProfilingInfo].operands.push(OperandKernelProfilingInfo);
    InstructionDesc[OpCaptureEventProfilingInfo].operands.push(OperandId);
    InstructionDesc[OpSetUserEventStatus].operands.push(OperandId);
    InstructionDesc[OpSetUserEventStatus].operands.push(OperandId);
    InstructionDesc[OpIsValidEvent].operands.push(OperandId);
    InstructionDesc[OpRetainEvent].operands.push(OperandId);
    InstructionDesc[OpReleaseEvent].operands.push(OperandId);
    InstructionDesc[OpGetKernelWorkGroupSize].operands.push(OperandId);
    InstructionDesc[OpGetKernelPreferredWorkGroupSizeMultiple].operands.push(OperandId);
    InstructionDesc[OpGetKernelNDrangeSubGroupCount].operands.push(OperandId);
    InstructionDesc[OpGetKernelNDrangeSubGroupCount].operands.push(OperandId);
    InstructionDesc[OpGetKernelNDrangeMaxSubGroupSize].operands.push(OperandId);
    InstructionDesc[OpGetKernelNDrangeMaxSubGroupSize].operands.push(OperandId);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandKernelEnqueueFlags);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandVariableIds);
    InstructionDesc[OpEnqueueMarker].operands.push(OperandId);
    InstructionDesc[OpEnqueueMarker].operands.push(OperandId);
    InstructionDesc[OpEnqueueMarker].operands.push(OperandId);
    InstructionDesc[OpEnqueueMarker].operands.push(OperandId);
}

//
// A whole set of functions that translate enums to English.
//

const char* CapabilityString(int cap)
{
    switch (cap) {
    case CapMatrix: return "Matrix";
    case CapShader: return "Shader";
    case CapGeom:   return "Geom";
    case CapTess:   return "Tess";
    case CapAddr:   return "Addr";
    case CapLink:   return "Link";
    case CapKernel: return "Kernel";

    default:        return "unknown";

    }
}

const char* SourceString(int source)
{
    switch (source) {
    case LangESSL:    return "ESSL";
    case LangGLSL:    return "GLSL";
    case LangOpenCL:  return "OpenCL";

    default:          return "unknown";
    }
}

const char* ExecutionModelString(int model)
{
    switch (model) {
    case ModelVertex:                  return "Vertex";
    case ModelTessellationControl:     return "TessellationControl";
    case ModelTessellationEvaluation:  return "TessellationEvaluation";
    case ModelGeometry:                return "Geometry";
    case ModelFragment:                return "Fragment";
    case ModelGLCompute:               return "GLCompute";
    case ModelKernel:                  return "Kernel";

    default:                           return "BadModel";
    }
}

const char* AddressingString(int addr)
{
    switch (addr) {
    case AddressingLogical:    return "Logical";
    case AddressingPhysical32: return "Physical32";
    case AddressingPhysical64: return "Physical64";

    default:                   return "BadAddressModel";
    }
}

const char* AddressingDesc(int addr)
{
    switch (addr) {
    case AddressingLogical:    return "No variables that are pointers or other physical pointers.  No arithmetic or casting on pointers.";
    case AddressingPhysical32: return "";
    case AddressingPhysical64: return "";

    default:                   return "BadAddressModel";
    }
}

const char* MemoryString(int mem)
{
    switch (mem) {
    case MemorySimple:   return "Simple";
    case MemoryGLSL450:  return "GLSL450";
    case MemoryOCL12:    return "OpenCL1.2";
    case MemoryOCL20:    return "OpenCL2.0";
    case MemoryOCL21:    return "OpenCL2.1";
    default:             return "BadMemoryModel";
    }
}

const char* ExecutionModeString(int mode)
{
    switch (mode) {
    case ExecutionInvocations:           return "Invocations";
    case ExecutionSpacingEqual:          return "SpacingEqual";
    case ExecutionSpacingFractionalEven: return "SpacingFractionalEven";
    case ExecutionSpacingFractionalOdd:  return "SpacingFractionalOdd";
    case ExecutionVertexOrderCw:         return "VertexOrderCw";
    case ExecutionVertexOrderCcw:        return "VertexOrderCcw";
    case ExecutionPixelCenterInteger:    return "PixelCenterInteger";
    case ExecutionOriginUpperLeft:       return "OriginUpperLeft";
    case ExecutionEarlyFragmentTests:    return "EarlyFragmentTests";
    case ExecutionPointMode:             return "PointMode";
    case ExecutionLocalSize:             return "LocalSize";
    case ExecutionLocalSizeHint:         return "LocalSizeHint";
    case ExecutionVecTypeHint:           return "VecTypeHint";
    case ExecutionContractionOff:        return "ContractionOff";
    case ExecutionXfb:                   return "Xfb";
    case ExecutionDepthReplacing:        return "DepthReplacing";
    case ExecutionDepthAny:              return "DepthAny";
    case ExecutionDepthGreater:          return "DepthGreater";
    case ExecutionDepthLess:             return "DepthLess";
    case ExecutionDepthUnchanged:        return "DepthUnchanged";

    case ExecutionInputPoints:              return "InputPoints";
    case ExecutionInputLines:               return "InputLines";
    case ExecutionInputLinesAdjacency:      return "InputLinesAdjacency";
    case ExecutionInputTriangles:           return "InputTriangles";
    case ExecutionInputTrianglesAdjacency:  return "InputTrianglesAdjacency";
    case ExecutionInputQuads:               return "InputQuads";
    case ExecutionInputIsolines:            return "InputIsolines";

    case ExecutionOutputVertices:      return "OutputVertices";
    case ExecutionOutputPoints:        return "OutputPoints";
    case ExecutionOutputLineStrip:     return "OutputLineStrip";
    case ExecutionOutputTriangleStrip: return "OutputTriangleStrip";

    default:                    return "BadMode";
    }
}

const char* StorageClassString(int StorageClass)
{
    switch (StorageClass) {
    //case StorageLowertime:       return "Lowertime";      // TODO: finish removing when sure they are gone.
    case StorageConstantUniform: return "UniformConstant";
    case StorageUniform:         return "Uniform";
    case StorageInput:           return "Input";
    case StorageOutput:          return "Output";
    case StorageWorkgroupLocal:  return "WorkgroupLocal";
    case StoragePrivateGlobal:   return "PrivateGlobal";
    case StorageWorkgroupGlobal: return "WorkgroupGlobal";
    case StorageFunction:        return "Function";
    case StoragePrivate:         return "Private";
    case StorageAtomicCounter:   return "AtomicCounter";
    case StorageGeneric:         return "Generic";        
        
    default:                     return 0;
    }
}

const char* DecorationString(int decoration)
{
    switch (decoration) {
    case DecPrecisionLow:      return "PrecisionLow";
    case DecPrecisionMedium:   return "PrecisionMedium";
    case DecPrecisionHigh:     return "PrecisionHigh";
    case DecBlock:             return "Block";
    case DecBufferBlock:       return "BufferBlock";
    case DecRowMajor:          return "RowMajor";
    case DecColMajor:          return "ColMajor";
    case DecGLSLShared:        return "GLSLShared";
    case DecGLSLStd140:        return "GLSLStd140";
    case DecGLSLStd430:        return "GLSLStd430";
    case DecGLSLPacked:        return "GLSLPacked";
    case DecSmooth:            return "Smooth";
    case DecNoperspective:     return "Noperspective";
    case DecFlat:              return "Flat";
    case DecPatch:             return "Patch";
    case DecCentroid:          return "Centroid";
    case DecSample:            return "Sample";
    case DecInvariant:         return "Invariant";
    case DecRestrict:          return "Restrict";
    case DecAliased:           return "Aliased";
    case DecVolatile:          return "Volatile";
    case DecConstant:          return "Constant";
    case DecCoherent:          return "Coherent";
    case DecNonwritable:       return "Nonwritable";
    case DecNonreadable:       return "Nonreadable";
    case DecUniform:           return "Uniform";
    case DecNoStaticUse:       return "NoStaticUse";
    case DecCPacked:           return "CPacked";
    case DecFuncParamAttr:     return "FuncParamAttr";
    case DecFPSaturatedConv:   return "FPSaturatedConversion";
    case DecFPRoundingMode:    return "FP Rounding Mode";
    case DecFPFastMathMode:    return "FP Fast Math Mode";
    case DecLinkageType:       return "Linkage Type";
    case DecStream:            return "Stream";
    case DecLocation:          return "Location";
    case DecComponent:         return "Component";
    case DecIndex:             return "Index";
    case DecBinding:           return "Binding";
    case DecDescriptorSet:     return "DescriptorSet";
    case DecOffset:            return "Offset";
    case DecAlignment:         return "Alignment";
    case DecXfbBuffer:         return "XfbBuffer";
    case DecStride:            return "Stride";
    case DecBuiltIn:           return "Built-In";
    case DecSpecId:            return "SpecId";

    default:                   return "BadDecoration";
    }
}

const char* BuiltInString(int builtIn)
{
    switch (builtIn) {
    case BuiltInPosition:                  return "Position";
    case BuiltInPointSize:                 return "PointSize";
    case BuiltInClipVertex:                return "ClipVertex";
    case BuiltInClipDistance:              return "ClipDistance";
    case BuiltInCullDistance:              return "CullDistance";
    case BuiltInVertexId:                  return "VertexId";
    case BuiltInInstanceId:                return "InstanceId";
    case BuiltInPrimitiveId:               return "PrimitiveId";
    case BuiltInInvocationId:              return "InvocationId";
    case BuiltInLayer:                     return "Layer";
    case BuiltInViewportIndex:             return "ViewportIndex";
    case BuiltInTessLevelOuter:            return "TessLevelOuter";
    case BuiltInTessLevelInner:            return "TessLevelInner";
    case BuiltInTessCoord:                 return "TessCoord";
    case BuiltInPatchVertices:             return "PatchVertices";
    case BuiltInFragCoord:                 return "FragCoord";
    case BuiltInPointCoord:                return "PointCoord";
    case BuiltInFrontFacing:               return "FrontFacing";
    case BuiltInSampleId:                  return "SampleId";
    case BuiltInSamplePosition:            return "SamplePosition";
    case BuiltInSampleMask:                return "SampleMask";
    case BuiltInFragColor:                 return "FragColor";
    case BuiltInFragDepth:                 return "FragDepth";
    case BuiltInHelperInvocation:          return "HelperInvocation";
    case BuiltInNumWorkgroups:             return "NumWorkgroups";
    case BuiltInWorkgroupSize:             return "WorkgroupSize";
    case BuiltInWorkgroupId:               return "WorkgroupId";
    case BuiltInLocalInvocationId:         return "LocalInvocationId";
    case BuiltInGlobalInvocationId:        return "GlobalInvocationId";
    case BuiltInLocalInvocationIndex:      return "LocalInvocationIndex";    
    case BuiltInWorkDim:                   return "WorkDim";
    case BuiltInGlobalSize:                return "GlobalSize";
    case BuiltInEnqueuedWorkgroupSize:     return "EnqueuedWorkgroupSize";
    case BuiltInGlobalOffset:              return "GlobalOffset";
    case BuiltInGlobalLinearId:            return "GlobalLinearId";
    case BuiltInWorkgroupLinearId:         return "WorkgroupLinearId";
    case BuiltInSubgroupSize:              return "SubgroupSize";
    case BuiltInSubgroupMaxSize:           return "SubgroupMaxSize";
    case BuiltInNumSubgroups:              return "NumSubgroups";
    case BuiltInNumEnqueuedSubgroups:      return "NumEnqueuedSubgroups";
    case BuiltInSubgroupId:                return "SubgroupId";
    case BuiltInSubgroupLocalInvocationId: return "SubgroupLocalInvocationId";
    default:                               return "BadBuiltIn";
    }
}

const char* DimensionString(int dim)
{
    switch (dim) {
    case Dim1D:     return "1D";
    case Dim2D:     return "2D";
    case Dim3D:     return "3D";
    case DimCube:   return "Cube";
    case DimRect:   return "Rect";
    case DimBuffer: return "Buffer";

    default:        return "BadDimensionality";
    }
}

const char* SamplerAddressingModeString(int mode)
{
    switch (mode) {
    case SamplerAddressingNone:           return "None";
    case SamplerAddressingClampToEdge:    return "ClampEdge";
    case SamplerAddressingClamp:          return "Clamp";
    case SamplerAddressingRepeat:         return "Repeat";
    case SamplerAddressingRepeatMirrored: return "RepeatMirrored";

    default:                              return "BadSamplerAddrMode";
    }
}

const char* SamplerFilterModeString(int mode)
{
    switch (mode) {
    case SamplerFilterNearest:   return "Nearest";
    case SamplerFilterLinear:    return "Linear";

    default:        return "BadSamplerFilterMode";
    }
}

const char* FPFastMathString(int mode)
{
    switch (mode) {
    case FPFastMathNNan:   return "NotNaN";
    case FPFastMathNInf:   return "NotInf";
    case FPFastMathNSZ:    return "NSZ";
    case FPFastMathARcp:   return "AllowRecip";
    case FPFastMathFast:   return "Fast";

    default:               return "BadFastMathMode";
    }
}

const char* FPRoundingModeString(int mode)
{
    switch (mode) {
    case FPRoundRTE:   return "RTE";
    case FPRoundRTZ:   return "RTZ";
    case FPRoundRTP:   return "RTP";
    case FPRoundRTN:   return "RTN";

    default:           return "BadFPRoundingMode";
    }
}


const char* LinkageTypeString(int type)
{
    switch (type) {
    case LinkageExport:   return "Export";
    case LinkageImport:    return "Import";

    default:        return "BadLinkageType";
    }
}

const char* FuncParamAttrString(int attr)
{
    switch (attr) {
    case FuncParamAttrZext:         return "Zext";
    case FuncParamAttrSext:         return "Sext";
    case FuncParamAttrByval:        return "ByVal";
    case FuncParamAttrSret:         return "Sret";
    case FuncParamAttrNoAlias:      return "NoAlias";
    case FuncParamAttrNoCapture:    return "NoCapture";
    case FuncParamAttrSVM:          return "SVM";
    case FuncParamAttrNoWrite:      return "NoWrite";
    case FuncParamAttrNoReadWrite:  return "NoReadWrite";

    default:                     return "BadFunctionParameterAttribute";
    }
}

const char* AccessQualifierString(int attr)
{
    switch (attr) {
    case AccessQualReadOnly:   return "ReadOnly";
    case AccessQualWriteOnly:  return "WriteOnly";
    case AccessQualReadWrite:  return "ReadWrite";

    default:                   return "BadAccessQualifier";
    }
}

const char* SelectControlString(int cont)
{
    switch (cont) {
    case SelectControlNone:        return "NoControl";
    case SelectControlFlatten:     return "Flatten";
    case SelectControlDontFlatten: return "DontFlatten";

    default:                       return "BadSelectControl";
    }
}

const char* FunctionControlString(int cont)
{
    switch (cont) {
    case FunctionControlNone:        return "NoControl";
    case FunctionControlInline:      return "InLine";
    case FunctionControlDontInline:  return "DontInline";
    case FunctionControlPure:        return "Pure";
    case FunctionControlConst:       return "Const";

    default:                         return "Bad-select-control";
    }
}

const char* LoopControlString(int cont)
{
    switch (cont) {
    case LoopControlNone:       return "NoControl";
    case LoopControlUnroll:     return "Unroll";
    case LoopControlDontUnroll: return "DontUnroll";

    default:                    return "Bad-loop-control";
    }
}

const char* MemorySemanticsString(int mem)
{
    switch (mem) {
    case MemorySemanticsRelaxed:                return "Relaxed";
    case MemorySemanticsSequentiallyConsistent: return "Sequentially-Consistent";
    case MemorySemanticsAcquire:                return "Acquire";
    case MemorySemanticsRelease:                return "Release";

    case MemorySemanticsUniform:                return "Uniform-memory";
    case MemorySemanticsSubgroup:               return "Subgroup-memory";
    case MemorySemanticsWorkgroupLocal:         return "Workgroup-local-memory";
    case MemorySemanticsWorkgroupGlobal:        return "Workgroup-global-memory";
    case MemorySemanticsAtomicCounter:          return "Atomic-counter-memory";
    case MemorySemanticsImage:                  return "Image-memory";

    default:                                    return "Bad-memory-semantic";
    }
}

const char* MemoryAccessString(int mem)
{
    switch (mem) {
    case MemoryAccessVolatile:               return "Volatile";
    case MemoryAccessAligned:                return "Aligned";

    default:                                 return "Bad-memory-access";
    }
}

const char* ExecutionScopeString(int mem)
{
    switch (mem) {
    case ExecutionScopeCrossDevice:             return "CrossDevice";
    case ExecutionScopeDevice:                  return "Device";
    case ExecutionScopeWorkgroup:               return "Workgroup";
    case ExecutionScopeSubgroup:                return "Subgroup";

    default:                                    return "Bad-execution-scope";
    }
}

const char* GroupOperationString(int gop) {

    switch (gop)
    {
    case GroupOpReduce:             return "Reduce";
    case GroupOpInclusiveScan:      return "InclusiveScan";
    case GroupOpExclusiveScan:      return "ExclusiveScan";

    default:                        return "Bad-execution-scope";
    }
}

const char* KernelEnqueueFlagsString(int flag) {
    switch (flag)
    {
    case spv::EnqFlagNoWait:            return "NoWait";
    case spv::EnqFlagWaitKernel:        return "WaitKernel";
    case spv::EnqFlagWaitWaitWorgGroup: return "WaitWorkGroup";

    default:                              return "Bad-enqueue-flag";
    }
}

const char* KernelProfilingInfoString(int info) {
    switch (info)
    {
    case spv::ProfInfoCmdExecTime: return "CmdExecTime";
    default:                         return "Bad-profiling-info";
    }
}

const char* GetOperandDesc(OperandClass operand)
{
    switch (operand) {
    case OperandId:                    return "<id>";
    case OperandOptionalId:            return "Optional <id>";
    case OperandVariableIds:           return "<id>, <id>, ...";
    case OperandVariableLiterals:      return "literal, literal, ...";
    case OperandVariableLiteralId:     return "literal, label <id>, +\nliteral, label <id>, +\n...";
    case OperandLiteralNumber:         return "Literal Number";
    case OperandLiteralString:         return "Literal String";
    case OperandSource:                return "Source Language";
    case OperandExecutionModel:        return "Execution Model";
    case OperandAddressing:            return "Addressing Model";
    case OperandMemory:                return "Memory Model";
    case OperandExecutionMode:         return "Execution Mode";
    case OperandStorage:               return "Storage Class";
    case OperandDimensionality:        return "Dim";
    case OperandDecoration:            return "Decoration";
    case OperandBuiltIn:               return "Built-In";
    case OperandSelect:                return "Selection Control";
    case OperandLoop:                  return "Loop Control";
    case OperandFunction:              return "Function Control Mask";
    case OperandSamplerAddressingMode: return "Sampler Addressing Mode";
    case OperandSamplerFilterMode:     return "Sampler Filter Mode";
    case OperandFPFastMath:            return "FP Fast Math Mode";
    case OperandFPRoundingMode:        return "FP Rounding Mode";
    case OperandLinkageType:           return "Linkage Type";
    case OperandFuncParamAttr:         return "Function Parameter Attribute";
    case OperandAccessQualifier:       return "Access Qualifier";
    case OperandMemorySemantics:       return "Memory Semantics";
    case OperandMemoryAccess:          return "Memory Access";
    case OperandExecutionScope:        return "Execution Scope";
    case OperandGroupOperation:        return "Group Operation";
    case OperandKernelEnqueueFlags:    return "Kernel Enqueue Flags";
    case OperandKernelProfilingInfo:   return "Kernel Profiling Info";
    default:                           return "Unknown";
    }
}

}; // end spv namespace
