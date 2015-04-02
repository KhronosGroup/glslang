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
// 1) Programatically fill in instruction/operand information.
//    This can be used for disassembly, printing documentation, etc.
//
// 2) Print documentation from this parameterization.
//

#include "doc.h"

#include <stdio.h>
#include <string.h>
#include <algorithm>

namespace spv {

//
// Whole set of functions that translate enumerants to their text strings for
// the specification (or their sanitized versions for auto-generating the
// spirv.h header.
//
// Also, the ceilings are declared next to these, to help keep them in sync.
// Ceilings should be
//  - one more than the maximum value an enumerant takes on, for non-mask enumerants
//    (for non-sparse enums, this is the number of enumurants)
//  - the number of bits consumed by the set of masks
//    (for non-sparse mask enums, this is the number of enumurants)
//

const int SourceLanguageCeiling = 4;

const char* SourceString(int source)
{
    switch (source) {
    case 0:  return "Unknown";
    case 1:  return "ESSL";
    case 2:  return "GLSL";
    case 3:  return "OpenCL";

    case SourceLanguageCeiling:
    default: return "Bad";
    }
}

const int ExecutionModelCeiling = 7;

const char* ExecutionModelString(int model)
{
    switch (model) {
    case 0:  return "Vertex";
    case 1:  return "TessellationControl";
    case 2:  return "TessellationEvaluation";
    case 3:  return "Geometry";
    case 4:  return "Fragment";
    case 5:  return "GLCompute";
    case 6:  return "Kernel";

    case ExecutionModelCeiling:
    default: return "Bad";
    }
}

const int AddressingModelCeiling = 3;

const char* AddressingString(int addr)
{
    switch (addr) {
    case 0:  return "Logical";
    case 1:  return "Physical32";
    case 2:  return "Physical64";

    case AddressingModelCeiling:
    default: return "Bad";
    }
}

const int MemoryModelCeiling = 5;

const char* MemoryString(int mem)
{
    switch (mem) {
    case 0:  return "Simple";
    case 1:  return "GLSL450";
    case 2:  return "OpenCL1.2";
    case 3:  return "OpenCL2.0";
    case 4:  return "OpenCL2.1";

    case MemoryModelCeiling:
    default: return "Bad";
    }
}

const int ExecutionModeCeiling = 31;

const char* ExecutionModeString(int mode)
{
    switch (mode) {
    case 0:  return "Invocations";
    case 1:  return "SpacingEqual";
    case 2:  return "SpacingFractionalEven";
    case 3:  return "SpacingFractionalOdd";
    case 4:  return "VertexOrderCw";
    case 5:  return "VertexOrderCcw";
    case 6:  return "PixelCenterInteger";
    case 7:  return "OriginUpperLeft";
    case 8:  return "EarlyFragmentTests";
    case 9:  return "PointMode";
    case 10: return "Xfb";
    case 11: return "DepthReplacing";
    case 12: return "DepthAny";
    case 13: return "DepthGreater";
    case 14: return "DepthLess";
    case 15: return "DepthUnchanged";
    case 16: return "LocalSize";
    case 17: return "LocalSizeHint";
    case 18: return "InputPoints";
    case 19: return "InputLines";
    case 20: return "InputLinesAdjacency";
    case 21: return "InputTriangles";
    case 22: return "InputTrianglesAdjacency";
    case 23: return "InputQuads";
    case 24: return "InputIsolines";
    case 25: return "OutputVertices";
    case 26: return "OutputPoints";
    case 27: return "OutputLineStrip";
    case 28: return "OutputTriangleStrip";
    case 29: return "VecTypeHint";
    case 30: return "ContractionOff";

    case ExecutionModeCeiling:
    default: return "Bad";
    }
}

const int StorageClassCeiling = 11;

const char* StorageClassString(int StorageClass)
{
    switch (StorageClass) {
    case 0:  return "UniformConstant";
    case 1:  return "Input";
    case 2:  return "Uniform";
    case 3:  return "Output";
    case 4:  return "WorkgroupLocal";
    case 5:  return "WorkgroupGlobal";
    case 6:  return "PrivateGlobal";
    case 7:  return "Function";
    case 8:  return "Generic";
    case 9:  return "Private";
    case 10: return "AtomicCounter";

    case StorageClassCeiling:
    default: return "Bad";
    }
}

const int DecorationCeiling = 45;

const char* DecorationString(int decoration)
{
    switch (decoration) {
    case 0:  return "PrecisionLow";
    case 1:  return "PrecisionMedium";
    case 2:  return "PrecisionHigh";
    case 3:  return "Block";
    case 4:  return "BufferBlock";
    case 5:  return "RowMajor";
    case 6:  return "ColMajor";
    case 7:  return "GLSLShared";
    case 8:  return "GLSLStd140";
    case 9:  return "GLSLStd430";
    case 10: return "GLSLPacked";
    case 11: return "Smooth";
    case 12: return "Noperspective";
    case 13: return "Flat";
    case 14: return "Patch";
    case 15: return "Centroid";
    case 16: return "Sample";
    case 17: return "Invariant";
    case 18: return "Restrict";
    case 19: return "Aliased";
    case 20: return "Volatile";
    case 21: return "Constant";
    case 22: return "Coherent";
    case 23: return "Nonwritable";
    case 24: return "Nonreadable";
    case 25: return "Uniform";
    case 26: return "NoStaticUse";
    case 27: return "CPacked";
    case 28: return "SaturatedConversion";
    case 29: return "Stream";
    case 30: return "Location";
    case 31: return "Component";
    case 32: return "Index";
    case 33: return "Binding";
    case 34: return "DescriptorSet";
    case 35: return "Offset";
    case 36: return "Alignment";
    case 37: return "XfbBuffer";
    case 38: return "Stride";
    case 39: return "BuiltIn";
    case 40: return "FuncParamAttr";
    case 41: return "FP Rounding Mode";
    case 42: return "FP Fast Math Mode";
    case 43: return "Linkage Attributes";
    case 44: return "SpecId";

    case DecorationCeiling:
    default:  return "Bad";
    }
}

const int BuiltInCeiling = 42;

const char* BuiltInString(int builtIn)
{
    switch (builtIn) {
    case 0:  return "Position";
    case 1:  return "PointSize";
    case 2:  return "ClipVertex";
    case 3:  return "ClipDistance";
    case 4:  return "CullDistance";
    case 5:  return "VertexId";
    case 6:  return "InstanceId";
    case 7:  return "PrimitiveId";
    case 8:  return "InvocationId";
    case 9:  return "Layer";
    case 10: return "ViewportIndex";
    case 11: return "TessLevelOuter";
    case 12: return "TessLevelInner";
    case 13: return "TessCoord";
    case 14: return "PatchVertices";
    case 15: return "FragCoord";
    case 16: return "PointCoord";
    case 17: return "FrontFacing";
    case 18: return "SampleId";
    case 19: return "SamplePosition";
    case 20: return "SampleMask";
    case 21: return "FragColor";
    case 22: return "FragDepth";
    case 23: return "HelperInvocation";
    case 24: return "NumWorkgroups";
    case 25: return "WorkgroupSize";
    case 26: return "WorkgroupId";
    case 27: return "LocalInvocationId";
    case 28: return "GlobalInvocationId";
    case 29: return "LocalInvocationIndex";
    case 30: return "WorkDim";
    case 31: return "GlobalSize";
    case 32: return "EnqueuedWorkgroupSize";
    case 33: return "GlobalOffset";
    case 34: return "GlobalLinearId";
    case 35: return "WorkgroupLinearId";
    case 36: return "SubgroupSize";
    case 37: return "SubgroupMaxSize";
    case 38: return "NumSubgroups";
    case 39: return "NumEnqueuedSubgroups";
    case 40: return "SubgroupId";
    case 41: return "SubgroupLocalInvocationId";

    case BuiltInCeiling:
    default: return "Bad";
    }
}

const int DimensionCeiling = 6;

const char* DimensionString(int dim)
{
    switch (dim) {
    case 0:  return "1D";
    case 1:  return "2D";
    case 2:  return "3D";
    case 3:  return "Cube";
    case 4:  return "Rect";
    case 5:  return "Buffer";

    case DimensionCeiling:
    default: return "Bad";
    }
}

const int SamplerAddressingModeCeiling = 5;

const char* SamplerAddressingModeString(int mode)
{
    switch (mode) {
    case 0:  return "None";
    case 1:  return "ClampToEdge";
    case 2:  return "Clamp";
    case 3:  return "Repeat";
    case 4:  return "RepeatMirrored";

    case SamplerAddressingModeCeiling:
    default: return "Bad";
    }
}

const int SamplerFilterModeCeiling = 2;

const char* SamplerFilterModeString(int mode)
{
    switch (mode) {
    case 0: return "Nearest";
    case 1: return "Linear";

    case SamplerFilterModeCeiling:
    default: return "Bad";
    }
}

const int FPFastMathCeiling = 5;

const char* FPFastMathString(int mode)
{
    switch (mode) {
    case 0: return "NotNaN";
    case 1: return "NotInf";
    case 2: return "NSZ";
    case 3: return "AllowRecip";
    case 4: return "Fast";

    case FPFastMathCeiling:
    default:     return "Bad";
    }
}

const int FPRoundingModeCeiling = 4;

const char* FPRoundingModeString(int mode)
{
    switch (mode) {
    case 0:  return "RTE";
    case 1:  return "RTZ";
    case 2:  return "RTP";
    case 3:  return "RTN";

    case FPRoundingModeCeiling:
    default: return "Bad";
    }
}

const int LinkageTypeCeiling = 2;

const char* LinkageTypeString(int type)
{
    switch (type) {
    case 0:  return "Export";
    case 1:  return "Import";

    case LinkageTypeCeiling:
    default: return "Bad";
    }
}

const int FuncParamAttrCeiling = 9;

const char* FuncParamAttrString(int attr)
{
    switch (attr) {
    case 0:  return "Zext";
    case 1:  return "Sext";
    case 2:  return "ByVal";
    case 3:  return "Sret";
    case 4:  return "NoAlias";
    case 5:  return "NoCapture";
    case 6:  return "SVM";
    case 7:  return "NoWrite";
    case 8:  return "NoReadWrite";

    case FuncParamAttrCeiling:
    default: return "Bad";
    }
}

const int AccessQualifierCeiling = 3;

const char* AccessQualifierString(int attr)
{
    switch (attr) {
    case 0:  return "ReadOnly";
    case 1:  return "WriteOnly";
    case 2:  return "ReadWrite";

    case AccessQualifierCeiling:
    default: return "Bad";
    }
}

const int SelectControlCeiling = 2;

const char* SelectControlString(int cont)
{
    switch (cont) {
    case 0:  return "Flatten";
    case 1:  return "DontFlatten";

    case SelectControlCeiling:
    default:                       return "Bad";
    }
}

const int LoopControlCeiling = 2;

const char* LoopControlString(int cont)
{
    switch (cont) {
    case 0: return "Unroll";
    case 1: return "DontUnroll";

    case LoopControlCeiling:
    default:     return "Bad";
    }
}

const int FunctionControlCeiling = 4;

const char* FunctionControlString(int cont)
{
    switch (cont) {
    case 0:  return "Inline";
    case 1:  return "DontInline";
    case 2:  return "Pure";
    case 3:  return "Const";

    case FunctionControlCeiling:
    default: return "Bad";
    }
}

const int MemorySemanticsCeiling = 10;

const char* MemorySemanticsString(int mem)
{
    switch (mem) {
    case 0: return "Relaxed";
    case 1: return "SequentiallyConsistent";
    case 2: return "Acquire";
    case 3: return "Release";

    case 4: return "UniformMemory";
    case 5: return "SubgroupMemory";
    case 6: return "WorkgroupLocalMemory";
    case 7: return "WorkgroupGlobalMemory";
    case 8: return "AtomicCounterMemory";
    case 9: return "ImageMemory";

    case MemorySemanticsCeiling:
    default:     return "Bad";
    }
}

const int MemoryAccessCeiling = 2;

const char* MemoryAccessString(int mem)
{
    switch (mem) {
    case 0:  return "Volatile";
    case 1:  return "Aligned";

    case MemoryAccessCeiling:
    default: return "Bad";
    }
}

const int ExecutionScopeCeiling = 4;

const char* ExecutionScopeString(int mem)
{
    switch (mem) {
    case 0:  return "CrossDevice";
    case 1:  return "Device";
    case 2:  return "Workgroup";
    case 3:  return "Subgroup";

    case ExecutionScopeCeiling:
    default: return "Bad";
    }
}

const int GroupOperationCeiling = 3;

const char* GroupOperationString(int gop)
{

    switch (gop)
    {
    case 0:  return "Reduce";
    case 1:  return "InclusiveScan";
    case 2:  return "ExclusiveScan";

    case GroupOperationCeiling:
    default: return "Bad";
    }
}

const int KernelEnqueueFlagsCeiling = 3;

const char* KernelEnqueueFlagsString(int flag)
{
    switch (flag)
    {
    case 0:  return "NoWait";
    case 1:  return "WaitKernel";
    case 2:  return "WaitWorkGroup";

    case KernelEnqueueFlagsCeiling:
    default: return "Bad";
    }
}

const int KernelProfilingInfoCeiling = 1;

const char* KernelProfilingInfoString(int info)
{
    switch (info)
    {
    case 0:  return "CmdExecTime";

    case KernelProfilingInfoCeiling:
    default: return "Bad";
    }
}

const char* OpcodeString(int op)
{
    switch (op) {
    case 0:   return "OpNop";
    case 1:   return "OpSource";
    case 2:   return "OpSourceExtension";
    case 3:   return "OpExtension";
    case 4:   return "OpExtInstImport";
    case 5:   return "OpMemoryModel";
    case 6:   return "OpEntryPoint";
    case 7:   return "OpExecutionMode";
    case 8:   return "OpTypeVoid";
    case 9:   return "OpTypeBool";
    case 10:  return "OpTypeInt";
    case 11:  return "OpTypeFloat";
    case 12:  return "OpTypeVector";
    case 13:  return "OpTypeMatrix";
    case 14:  return "OpTypeSampler";
    case 15:  return "OpTypeFilter";
    case 16:  return "OpTypeArray";
    case 17:  return "OpTypeRuntimeArray";
    case 18:  return "OpTypeStruct";
    case 19:  return "OpTypeOpaque";
    case 20:  return "OpTypePointer";
    case 21:  return "OpTypeFunction";
    case 22:  return "OpTypeEvent";
    case 23:  return "OpTypeDeviceEvent";
    case 24:  return "OpTypeReserveId";
    case 25:  return "OpTypeQueue";
    case 26:  return "OpTypePipe";
    case 27:  return "OpConstantTrue";
    case 28:  return "OpConstantFalse";
    case 29:  return "OpConstant";
    case 30:  return "OpConstantComposite";
    case 31:  return "OpConstantSampler";
    case 32:  return "OpConstantNullPointer";
    case 33:  return "OpConstantNullObject";
    case 34:  return "OpSpecConstantTrue";
    case 35:  return "OpSpecConstantFalse";
    case 36:  return "OpSpecConstant";
    case 37:  return "OpSpecConstantComposite";
    case 38:  return "OpVariable";
    case 39:  return "OpVariableArray";
    case 40:  return "OpFunction";
    case 41:  return "OpFunctionParameter";
    case 42:  return "OpFunctionEnd";
    case 43:  return "OpFunctionCall";
    case 44:  return "OpExtInst";
    case 45:  return "OpUndef";
    case 46:  return "OpLoad";
    case 47:  return "OpStore";
    case 48:  return "OpPhi";
    case 49:  return "OpDecorationGroup";
    case 50:  return "OpDecorate";
    case 51:  return "OpMemberDecorate";
    case 52:  return "OpGroupDecorate";
    case 53:  return "OpGroupMemberDecorate";
    case 54:  return "OpName";
    case 55:  return "OpMemberName";
    case 56:  return "OpString";
    case 57:  return "OpLine";
    case 58:  return "OpVectorExtractDynamic";
    case 59:  return "OpVectorInsertDynamic";
    case 60:  return "OpVectorShuffle";
    case 61:  return "OpCompositeConstruct";
    case 62:  return "OpCompositeExtract";
    case 63:  return "OpCompositeInsert";
    case 64:  return "OpCopyObject";
    case 65:  return "OpCopyMemory";
    case 66:  return "OpCopyMemorySized";
    case 67:  return "OpSampler";
    case 68:  return "OpTextureSample";
    case 69:  return "OpTextureSampleDref";
    case 70:  return "OpTextureSampleLod";
    case 71:  return "OpTextureSampleProj";
    case 72:  return "OpTextureSampleGrad";
    case 73:  return "OpTextureSampleOffset";
    case 74:  return "OpTextureSampleProjLod";
    case 75:  return "OpTextureSampleProjGrad";
    case 76:  return "OpTextureSampleLodOffset";
    case 77:  return "OpTextureSampleProjOffset";
    case 78:  return "OpTextureSampleGradOffset";
    case 79:  return "OpTextureSampleProjLodOffset";
    case 80:  return "OpTextureSampleProjGradOffset";
    case 81:  return "OpTextureFetchTexelLod";
    case 82:  return "OpTextureFetchTexelOffset";
    case 83:  return "OpTextureFetchSample";
    case 84:  return "OpTextureFetchTexel";
    case 85:  return "OpTextureGather";
    case 86:  return "OpTextureGatherOffset";
    case 87:  return "OpTextureGatherOffsets";
    case 88:  return "OpTextureQuerySizeLod";
    case 89:  return "OpTextureQuerySize";
    case 90:  return "OpTextureQueryLod";
    case 91:  return "OpTextureQueryLevels";
    case 92:  return "OpTextureQuerySamples";
    case 93:  return "OpAccessChain";
    case 94:  return "OpInBoundsAccessChain";
    case 95:  return "OpSNegate";
    case 96:  return "OpFNegate";
    case 97:  return "OpNot";
    case 98:  return "OpAny";
    case 99:  return "OpAll";
    case 100: return "OpConvertFToU";
    case 101: return "OpConvertFToS";
    case 102: return "OpConvertSToF";
    case 103: return "OpConvertUToF";
    case 104: return "OpUConvert";
    case 105: return "OpSConvert";
    case 106: return "OpFConvert";
    case 107: return "OpConvertPtrToU";
    case 108: return "OpConvertUToPtr";
    case 109: return "OpPtrCastToGeneric";
    case 110: return "OpGenericCastToPtr";
    case 111: return "OpBitcast";
    case 112: return "OpTranspose";
    case 113: return "OpIsNan";
    case 114: return "OpIsInf";
    case 115: return "OpIsFinite";
    case 116: return "OpIsNormal";
    case 117: return "OpSignBitSet";
    case 118: return "OpLessOrGreater";
    case 119: return "OpOrdered";
    case 120: return "OpUnordered";
    case 121: return "OpArrayLength";
    case 122: return "OpIAdd";
    case 123: return "OpFAdd";
    case 124: return "OpISub";
    case 125: return "OpFSub";
    case 126: return "OpIMul";
    case 127: return "OpFMul";
    case 128: return "OpUDiv";
    case 129: return "OpSDiv";
    case 130: return "OpFDiv";
    case 131: return "OpUMod";
    case 132: return "OpSRem";
    case 133: return "OpSMod";
    case 134: return "OpFRem";
    case 135: return "OpFMod";
    case 136: return "OpVectorTimesScalar";
    case 137: return "OpMatrixTimesScalar";
    case 138: return "OpVectorTimesMatrix";
    case 139: return "OpMatrixTimesVector";
    case 140: return "OpMatrixTimesMatrix";
    case 141: return "OpOuterProduct";
    case 142: return "OpDot";
    case 143: return "OpShiftRightLogical";
    case 144: return "OpShiftRightArithmetic";
    case 145: return "OpShiftLeftLogical";
    case 146: return "OpLogicalOr";
    case 147: return "OpLogicalXor";
    case 148: return "OpLogicalAnd";
    case 149: return "OpBitwiseOr";
    case 150: return "OpBitwiseXor";
    case 151: return "OpBitwiseAnd";
    case 152: return "OpSelect";
    case 153: return "OpIEqual";
    case 154: return "OpFOrdEqual";
    case 155: return "OpFUnordEqual";
    case 156: return "OpINotEqual";
    case 157: return "OpFOrdNotEqual";
    case 158: return "OpFUnordNotEqual";
    case 159: return "OpULessThan";
    case 160: return "OpSLessThan";
    case 161: return "OpFOrdLessThan";
    case 162: return "OpFUnordLessThan";
    case 163: return "OpUGreaterThan";
    case 164: return "OpSGreaterThan";
    case 165: return "OpFOrdGreaterThan";
    case 166: return "OpFUnordGreaterThan";
    case 167: return "OpULessThanEqual";
    case 168: return "OpSLessThanEqual";
    case 169: return "OpFOrdLessThanEqual";
    case 170: return "OpFUnordLessThanEqual";
    case 171: return "OpUGreaterThanEqual";
    case 172: return "OpSGreaterThanEqual";
    case 173: return "OpFOrdGreaterThanEqual";
    case 174: return "OpFUnordGreaterThanEqual";
    case 175: return "OpDPdx";
    case 176: return "OpDPdy";
    case 177: return "OpFwidth";
    case 178: return "OpDPdxFine";
    case 179: return "OpDPdyFine";
    case 180: return "OpFwidthFine";
    case 181: return "OpDPdxCoarse";
    case 182: return "OpDPdyCoarse";
    case 183: return "OpFwidthCoarse";
    case 184: return "OpEmitVertex";
    case 185: return "OpEndPrimitive";
    case 186: return "OpEmitStreamVertex";
    case 187: return "OpEndStreamPrimitive";
    case 188: return "OpControlBarrier";
    case 189: return "OpMemoryBarrier";
    case 190: return "OpImagePointer";
    case 191: return "OpAtomicInit";
    case 192: return "OpAtomicLoad";
    case 193: return "OpAtomicStore";
    case 194: return "OpAtomicExchange";
    case 195: return "OpAtomicCompareExchange";
    case 196: return "OpAtomicCompareExchangeWeak";
    case 197: return "OpAtomicIIncrement";
    case 198: return "OpAtomicIDecrement";
    case 199: return "OpAtomicIAdd";
    case 200: return "OpAtomicISub";
    case 201: return "OpAtomicUMin";
    case 202: return "OpAtomicUMax";
    case 203: return "OpAtomicAnd";
    case 204: return "OpAtomicOr";
    case 205: return "OpAtomicXor";
    case 206: return "OpLoopMerge";
    case 207: return "OpSelectionMerge";
    case 208: return "OpLabel";
    case 209: return "OpBranch";
    case 210: return "OpBranchConditional";
    case 211: return "OpSwitch";
    case 212: return "OpKill";
    case 213: return "OpReturn";
    case 214: return "OpReturnValue";
    case 215: return "OpUnreachable";
    case 216: return "OpLifetimeStart";
    case 217: return "OpLifetimeStop";
    case 218: return "OpCompileFlag";
    case 219: return "OpAsyncGroupCopy";
    case 220: return "OpWaitGroupEvents";
    case 221: return "OpGroupAll";
    case 222: return "OpGroupAny";
    case 223: return "OpGroupBroadcast";
    case 224: return "OpGroupIAdd";
    case 225: return "OpGroupFAdd";
    case 226: return "OpGroupFMin";
    case 227: return "OpGroupUMin";
    case 228: return "OpGroupSMin";
    case 229: return "OpGroupFMax";
    case 230: return "OpGroupUMax";
    case 231: return "OpGroupSMax";
    case 232: return "OpGenericCastToPtrExplicit";
    case 233: return "OpGenericPtrMemSemantics";
    case 234: return "OpReadPipe";
    case 235: return "OpWritePipe";
    case 236: return "OpReservedReadPipe";
    case 237: return "OpReservedWritePipe";
    case 238: return "OpReserveReadPipePackets";
    case 239: return "OpReserveWritePipePackets";
    case 240: return "OpCommitReadPipe";
    case 241: return "OpCommitWritePipe";
    case 242: return "OpIsValidReserveId";
    case 243: return "OpGetNumPipePackets";
    case 244: return "OpGetMaxPipePackets";
    case 245: return "OpGroupReserveReadPipePackets";
    case 246: return "OpGroupReserveWritePipePackets";
    case 247: return "OpGroupCommitReadPipe";
    case 248: return "OpGroupCommitWritePipe";
    case 249: return "OpEnqueueMarker";
    case 250: return "OpEnqueueKernel";
    case 251: return "OpGetKernelNDrangeSubGroupCount";
    case 252: return "OpGetKernelNDrangeMaxSubGroupSize";
    case 253: return "OpGetKernelWorkGroupSize";
    case 254: return "OpGetKernelPreferredWorkGroupSizeMultiple";
    case 255: return "OpRetainEvent";
    case 256: return "OpReleaseEvent";
    case 257: return "OpCreateUserEvent";
    case 258: return "OpIsValidEvent";
    case 259: return "OpSetUserEventStatus";
    case 260: return "OpCaptureEventProfilingInfo";
    case 261: return "OpGetDefaultQueue";
    case 262: return "OpBuildNDRange";
    case 263: return "OpSatConvertSToU";
    case 264: return "OpSatConvertUToS";
    case 265: return "OpAtomicIMin";
    case 266: return "OpAtomicIMax";

    case OpcodeCeiling:
    default:
        return "Bad";
    }
}

// The set of objects that hold all the instruction/operand
// parameterization information.
InstructionParameters InstructionDesc[OpcodeCeiling];
OperandParameters ExecutionModeOperands[ExecutionModeCeiling];
OperandParameters DecorationOperands[DecorationCeiling];

EnumDefinition OperandClassParams[OperandCount];
EnumParameters ExecutionModelParams[ExecutionModelCeiling];
EnumParameters AddressingParams[AddressingModelCeiling];
EnumParameters MemoryParams[MemoryModelCeiling];
EnumParameters ExecutionModeParams[ExecutionModeCeiling];
EnumParameters StorageParams[StorageClassCeiling];
EnumParameters SamplerAddressingModeParams[SamplerAddressingModeCeiling];
EnumParameters SamplerFilterModeParams[SamplerFilterModeCeiling];
EnumParameters FPFastMathParams[FPFastMathCeiling];
EnumParameters FPRoundingModeParams[FPRoundingModeCeiling];
EnumParameters LinkageTypeParams[LinkageTypeCeiling];
EnumParameters DecorationParams[DecorationCeiling];
EnumParameters BuiltInParams[BuiltInCeiling];
EnumParameters DimensionalityParams[DimensionCeiling];
EnumParameters FuncParamAttrParams[FuncParamAttrCeiling];
EnumParameters AccessQualifierParams[AccessQualifierCeiling];
EnumParameters GroupOperationParams[GroupOperationCeiling];
EnumParameters LoopControlParams[FunctionControlCeiling];
EnumParameters SelectionControlParams[SelectControlCeiling];
EnumParameters FunctionControlParams[FunctionControlCeiling];
EnumParameters MemorySemanticsParams[MemorySemanticsCeiling];
EnumParameters MemoryAccessParams[MemoryAccessCeiling];
EnumParameters ExecutionScopeParams[ExecutionScopeCeiling];
EnumParameters KernelEnqueueFlagsParams[KernelEnqueueFlagsCeiling];
EnumParameters KernelProfilingInfoParams[KernelProfilingInfoCeiling];

// Set up all the parameterizing descriptions of the opcodes, operands, etc.
void Parameterize()
{
    // Exceptions to having a result <id> and a resulting type <id>.
    // (Everything is initialized to have both).

    InstructionDesc[OpNop].setResultAndType(false, false);
    InstructionDesc[OpSource].setResultAndType(false, false);
    InstructionDesc[OpSourceExtension].setResultAndType(false, false);
    InstructionDesc[OpExtension].setResultAndType(false, false);
    InstructionDesc[OpExtInstImport].setResultAndType(true, false);
    InstructionDesc[OpMemoryModel].setResultAndType(false, false);
    InstructionDesc[OpEntryPoint].setResultAndType(false, false);
    InstructionDesc[OpExecutionMode].setResultAndType(false, false);
    InstructionDesc[OpTypeVoid].setResultAndType(true, false);
    InstructionDesc[OpTypeBool].setResultAndType(true, false);
    InstructionDesc[OpTypeInt].setResultAndType(true, false);
    InstructionDesc[OpTypeFloat].setResultAndType(true, false);
    InstructionDesc[OpTypeVector].setResultAndType(true, false);
    InstructionDesc[OpTypeMatrix].setResultAndType(true, false);
    InstructionDesc[OpTypeSampler].setResultAndType(true, false);
    InstructionDesc[OpTypeFilter].setResultAndType(true, false);
    InstructionDesc[OpTypeArray].setResultAndType(true, false);
    InstructionDesc[OpTypeRuntimeArray].setResultAndType(true, false);
    InstructionDesc[OpTypeStruct].setResultAndType(true, false);
    InstructionDesc[OpTypeOpaque].setResultAndType(true, false);
    InstructionDesc[OpTypePointer].setResultAndType(true, false);
    InstructionDesc[OpTypeFunction].setResultAndType(true, false);
    InstructionDesc[OpTypeEvent].setResultAndType(true, false);
    InstructionDesc[OpTypeDeviceEvent].setResultAndType(true, false);
    InstructionDesc[OpTypeReserveId].setResultAndType(true, false);
    InstructionDesc[OpTypeQueue].setResultAndType(true, false);
    InstructionDesc[OpTypePipe].setResultAndType(true, false);
    InstructionDesc[OpFunctionEnd].setResultAndType(false, false);
    InstructionDesc[OpStore].setResultAndType(false, false);
    InstructionDesc[OpDecorationGroup].setResultAndType(true, false);
    InstructionDesc[OpDecorate].setResultAndType(false, false);
    InstructionDesc[OpMemberDecorate].setResultAndType(false, false);
    InstructionDesc[OpGroupDecorate].setResultAndType(false, false);
    InstructionDesc[OpGroupMemberDecorate].setResultAndType(false, false);
    InstructionDesc[OpName].setResultAndType(false, false);
    InstructionDesc[OpMemberName].setResultAndType(false, false);
    InstructionDesc[OpString].setResultAndType(true, false);
    InstructionDesc[OpLine].setResultAndType(false, false);
    InstructionDesc[OpCopyMemory].setResultAndType(false, false);
    InstructionDesc[OpCopyMemorySized].setResultAndType(false, false);
    InstructionDesc[OpEmitVertex].setResultAndType(false, false);
    InstructionDesc[OpEndPrimitive].setResultAndType(false, false);
    InstructionDesc[OpEmitStreamVertex].setResultAndType(false, false);
    InstructionDesc[OpEndStreamPrimitive].setResultAndType(false, false);
    InstructionDesc[OpControlBarrier].setResultAndType(false, false);
    InstructionDesc[OpMemoryBarrier].setResultAndType(false, false);
    InstructionDesc[OpAtomicInit].setResultAndType(false, false);
    InstructionDesc[OpAtomicStore].setResultAndType(false, false);
    InstructionDesc[OpLoopMerge].setResultAndType(false, false);
    InstructionDesc[OpSelectionMerge].setResultAndType(false, false);
    InstructionDesc[OpLabel].setResultAndType(true, false);
    InstructionDesc[OpBranch].setResultAndType(false, false);
    InstructionDesc[OpBranchConditional].setResultAndType(false, false);
    InstructionDesc[OpSwitch].setResultAndType(false, false);
    InstructionDesc[OpKill].setResultAndType(false, false);
    InstructionDesc[OpReturn].setResultAndType(false, false);
    InstructionDesc[OpReturnValue].setResultAndType(false, false);
    InstructionDesc[OpUnreachable].setResultAndType(false, false);
    InstructionDesc[OpLifetimeStart].setResultAndType(false, false);
    InstructionDesc[OpLifetimeStop].setResultAndType(false, false);
    InstructionDesc[OpCompileFlag].setResultAndType(false, false);
    InstructionDesc[OpCommitReadPipe].setResultAndType(false, false);
    InstructionDesc[OpCommitWritePipe].setResultAndType(false, false);
    InstructionDesc[OpGroupCommitWritePipe].setResultAndType(false, false);
    InstructionDesc[OpGroupCommitReadPipe].setResultAndType(false, false);
    InstructionDesc[OpCaptureEventProfilingInfo].setResultAndType(false, false);
    InstructionDesc[OpSetUserEventStatus].setResultAndType(false, false);
    InstructionDesc[OpRetainEvent].setResultAndType(false, false);
    InstructionDesc[OpReleaseEvent].setResultAndType(false, false);

    // Specific additional context-dependent operands

    ExecutionModeOperands[ExecutionModeInvocations].push(OperandLiteralNumber, "Number of invocations");

    ExecutionModeOperands[ExecutionModeLocalSize].push(OperandLiteralNumber, "'x size'");
    ExecutionModeOperands[ExecutionModeLocalSize].push(OperandLiteralNumber, "'y size'");
    ExecutionModeOperands[ExecutionModeLocalSize].push(OperandLiteralNumber, "'z size'");

    ExecutionModeOperands[ExecutionModeLocalSizeHint].push(OperandLiteralNumber, "'x size'");
    ExecutionModeOperands[ExecutionModeLocalSizeHint].push(OperandLiteralNumber, "'y size'");
    ExecutionModeOperands[ExecutionModeLocalSizeHint].push(OperandLiteralNumber, "'z size'");

    ExecutionModeOperands[ExecutionModeOutputVertices].push(OperandLiteralNumber, "Vertex count");
    ExecutionModeOperands[ExecutionModeVecTypeHint].push(OperandId, "Vector type");

    DecorationOperands[DecorationStream].push(OperandLiteralNumber, "Stream number");
    DecorationOperands[DecorationLocation].push(OperandLiteralNumber, "Location");
    DecorationOperands[DecorationComponent].push(OperandLiteralNumber, "Component within a vector");
    DecorationOperands[DecorationIndex].push(OperandLiteralNumber, "Index");
    DecorationOperands[DecorationBinding].push(OperandLiteralNumber, "Binding point");
    DecorationOperands[DecorationDescriptorSet].push(OperandLiteralNumber, "Descriptor set");
    DecorationOperands[DecorationOffset].push(OperandLiteralNumber, "Byte offset");
    DecorationOperands[DecorationAlignment].push(OperandLiteralNumber, "Declared alignment");
    DecorationOperands[DecorationXfbBuffer].push(OperandLiteralNumber, "XFB Buffer number");
    DecorationOperands[DecorationStride].push(OperandLiteralNumber, "Stride");
    DecorationOperands[DecorationBuiltIn].push(OperandLiteralNumber, "See <<BuiltIn,*BuiltIn*>>");
    DecorationOperands[DecorationFPRoundingMode].push(OperandFPRoundingMode, "floating-point rounding mode");
    DecorationOperands[DecorationFPFastMathMode].push(OperandFPFastMath, "fast-math mode");
    DecorationOperands[DecorationLinkageAttributes].push(OperandLiteralString, "name");
    DecorationOperands[DecorationLinkageAttributes].push(OperandLinkageType, "linkage type");
    DecorationOperands[DecorationFuncParamAttr].push(OperandFuncParamAttr, "function parameter attribute");
    DecorationOperands[DecorationSpecId].push(OperandLiteralNumber, "Specialization Constant ID");

    OperandClassParams[OperandSource].set(SourceLanguageCeiling, SourceString, 0);
    OperandClassParams[OperandExecutionModel].set(ExecutionModelCeiling, ExecutionModelString, ExecutionModelParams);
    OperandClassParams[OperandAddressing].set(AddressingModelCeiling, AddressingString, AddressingParams);
    OperandClassParams[OperandMemory].set(MemoryModelCeiling, MemoryString, MemoryParams);
    OperandClassParams[OperandExecutionMode].set(ExecutionModeCeiling, ExecutionModeString, ExecutionModeParams);
    OperandClassParams[OperandExecutionMode].setOperands(ExecutionModeOperands);
    OperandClassParams[OperandStorage].set(StorageClassCeiling, StorageClassString, StorageParams);
    OperandClassParams[OperandDimensionality].set(DimensionCeiling, DimensionString, DimensionalityParams);
    OperandClassParams[OperandSamplerAddressingMode].set(SamplerAddressingModeCeiling, SamplerAddressingModeString, SamplerAddressingModeParams);
    OperandClassParams[OperandSamplerFilterMode].set(SamplerFilterModeCeiling, SamplerFilterModeString, SamplerFilterModeParams);
    OperandClassParams[OperandFPFastMath].set(FPFastMathCeiling, FPFastMathString, FPFastMathParams, true);
    OperandClassParams[OperandFPRoundingMode].set(FPRoundingModeCeiling, FPRoundingModeString, FPRoundingModeParams);
    OperandClassParams[OperandLinkageType].set(LinkageTypeCeiling, LinkageTypeString, LinkageTypeParams);
    OperandClassParams[OperandFuncParamAttr].set(FuncParamAttrCeiling, FuncParamAttrString, FuncParamAttrParams);
    OperandClassParams[OperandAccessQualifier].set(AccessQualifierCeiling, AccessQualifierString, AccessQualifierParams);
    OperandClassParams[OperandDecoration].set(DecorationCeiling, DecorationString, DecorationParams);
    OperandClassParams[OperandDecoration].setOperands(DecorationOperands);
    OperandClassParams[OperandBuiltIn].set(BuiltInCeiling, BuiltInString, BuiltInParams);
    OperandClassParams[OperandSelect].set(SelectControlCeiling, SelectControlString, SelectionControlParams, true);
    OperandClassParams[OperandLoop].set(LoopControlCeiling, LoopControlString, LoopControlParams, true);
    OperandClassParams[OperandFunction].set(FunctionControlCeiling, FunctionControlString, FunctionControlParams, true);
    OperandClassParams[OperandMemorySemantics].set(MemorySemanticsCeiling, MemorySemanticsString, MemorySemanticsParams, true);
    OperandClassParams[OperandMemoryAccess].set(MemoryAccessCeiling, MemoryAccessString, MemoryAccessParams, true);
    OperandClassParams[OperandExecutionScope].set(ExecutionScopeCeiling, ExecutionScopeString, ExecutionScopeParams);
    OperandClassParams[OperandGroupOperation].set(GroupOperationCeiling, GroupOperationString, GroupOperationParams);
    OperandClassParams[OperandKernelEnqueueFlags].set(KernelEnqueueFlagsCeiling, KernelEnqueueFlagsString, KernelEnqueueFlagsParams);
    OperandClassParams[OperandKernelProfilingInfo].set(KernelProfilingInfoCeiling, KernelProfilingInfoString, KernelProfilingInfoParams, true);
    OperandClassParams[OperandOpcode].set(OpcodeCeiling, OpcodeString, 0);

    AddressingParams[AddressingModelPhysical32].caps.push_back(CapAddr);
    AddressingParams[AddressingModelPhysical64].caps.push_back(CapAddr);

    MemoryParams[MemoryModelSimple].caps.push_back(CapShader);
    MemoryParams[MemoryModelGLSL450].caps.push_back(CapShader);
    MemoryParams[MemoryModelOpenCL12].caps.push_back(CapKernel);
    MemoryParams[MemoryModelOpenCL20].caps.push_back(CapKernel);
    MemoryParams[MemoryModelOpenCL21].caps.push_back(CapKernel);

    ExecutionModelParams[ExecutionModelVertex].caps.push_back(CapShader);
    ExecutionModelParams[ExecutionModelTessellationControl].caps.push_back(CapTess);
    ExecutionModelParams[ExecutionModelTessellationEvaluation].caps.push_back(CapTess);
    ExecutionModelParams[ExecutionModelGeometry].caps.push_back(CapGeom);
    ExecutionModelParams[ExecutionModelFragment].caps.push_back(CapShader);
    ExecutionModelParams[ExecutionModelGLCompute].caps.push_back(CapShader);
    ExecutionModelParams[ExecutionModelKernel].caps.push_back(CapKernel);

    // Storage capabilites
    StorageParams[StorageClassInput].caps.push_back(CapShader);
    StorageParams[StorageClassUniform].caps.push_back(CapShader);
    StorageParams[StorageClassOutput].caps.push_back(CapShader);
    StorageParams[StorageClassPrivateGlobal].caps.push_back(CapShader);
    StorageParams[StorageClassFunction].caps.push_back(CapShader);
    StorageParams[StorageClassGeneric].caps.push_back(CapKernel);
    StorageParams[StorageClassPrivate].caps.push_back(CapKernel);
    StorageParams[StorageClassAtomicCounter].caps.push_back(CapShader);

    // Sampler Filter & Addressing mode capabilities
    SamplerAddressingModeParams[SamplerAddressingModeNone].caps.push_back(CapKernel);
    SamplerAddressingModeParams[SamplerAddressingModeClampToEdge].caps.push_back(CapKernel);
    SamplerAddressingModeParams[SamplerAddressingModeClamp].caps.push_back(CapKernel);
    SamplerAddressingModeParams[SamplerAddressingModeRepeat].caps.push_back(CapKernel);
    SamplerAddressingModeParams[SamplerAddressingModeRepeatMirrored].caps.push_back(CapKernel);

    SamplerFilterModeParams[SamplerFilterModeNearest].caps.push_back(CapKernel);
    SamplerFilterModeParams[SamplerFilterModeLinear].caps.push_back(CapKernel);

    // fast math flags capabilities
    for (int i = 0; i < FPFastMathCeiling; ++i) {
        FPFastMathParams[i].caps.push_back(CapKernel);
    }

    // fp rounding mode capabilities
    for (int i = 0; i < FPRoundingModeCeiling; ++i) {
        FPRoundingModeParams[i].caps.push_back(CapKernel);
    }

    // linkage types
    for (int i = 0; i < LinkageTypeCeiling; ++i) {
        LinkageTypeParams[i].caps.push_back(CapLink);
    }

    // function argument types
    for (int i = 0; i < FuncParamAttrCeiling; ++i) {
        FuncParamAttrParams[i].caps.push_back(CapKernel);
    }

    // function argument types
    for (int i = 0; i < AccessQualifierCeiling; ++i) {
        AccessQualifierParams[i].caps.push_back(CapKernel);
    }

    ExecutionModeParams[ExecutionModeInvocations].caps.push_back(CapGeom);
    ExecutionModeParams[ExecutionModeSpacingEqual].caps.push_back(CapTess);
    ExecutionModeParams[ExecutionModeSpacingFractionalEven].caps.push_back(CapTess);
    ExecutionModeParams[ExecutionModeSpacingFractionalOdd].caps.push_back(CapTess);
    ExecutionModeParams[ExecutionModeVertexOrderCw].caps.push_back(CapTess);
    ExecutionModeParams[ExecutionModeVertexOrderCcw].caps.push_back(CapTess);
    ExecutionModeParams[ExecutionModePixelCenterInteger].caps.push_back(CapShader);
    ExecutionModeParams[ExecutionModeOriginUpperLeft].caps.push_back(CapShader);
    ExecutionModeParams[ExecutionModeEarlyFragmentTests].caps.push_back(CapShader);
    ExecutionModeParams[ExecutionModePointMode].caps.push_back(CapTess);
    ExecutionModeParams[ExecutionModeXfb].caps.push_back(CapShader);
    ExecutionModeParams[ExecutionModeDepthReplacing].caps.push_back(CapShader);
    ExecutionModeParams[ExecutionModeDepthAny].caps.push_back(CapShader);
    ExecutionModeParams[ExecutionModeDepthGreater].caps.push_back(CapShader);
    ExecutionModeParams[ExecutionModeDepthLess].caps.push_back(CapShader);
    ExecutionModeParams[ExecutionModeDepthUnchanged].caps.push_back(CapShader);
    ExecutionModeParams[ExecutionModeLocalSizeHint].caps.push_back(CapKernel);
    ExecutionModeParams[ExecutionModeInputPoints].caps.push_back(CapGeom);
    ExecutionModeParams[ExecutionModeInputLines].caps.push_back(CapGeom);
    ExecutionModeParams[ExecutionModeInputLinesAdjacency].caps.push_back(CapGeom);
    ExecutionModeParams[ExecutionModeInputTriangles].caps.push_back(CapGeom);
    ExecutionModeParams[ExecutionModeInputTriangles].caps.push_back(CapTess);
    ExecutionModeParams[ExecutionModeInputTrianglesAdjacency].caps.push_back(CapGeom);
    ExecutionModeParams[ExecutionModeInputQuads].caps.push_back(CapTess);
    ExecutionModeParams[ExecutionModeInputIsolines].caps.push_back(CapTess);
    ExecutionModeParams[ExecutionModeOutputVertices].caps.push_back(CapGeom);
    ExecutionModeParams[ExecutionModeOutputVertices].caps.push_back(CapTess);
    ExecutionModeParams[ExecutionModeOutputPoints].caps.push_back(CapGeom);
    ExecutionModeParams[ExecutionModeOutputLineStrip].caps.push_back(CapGeom);
    ExecutionModeParams[ExecutionModeOutputTriangleStrip].caps.push_back(CapGeom);
    ExecutionModeParams[ExecutionModeVecTypeHint].caps.push_back(CapKernel);
    ExecutionModeParams[ExecutionModeContractionOff].caps.push_back(CapKernel);

    DecorationParams[DecorationPrecisionLow].caps.push_back(CapShader);
    DecorationParams[DecorationPrecisionMedium].caps.push_back(CapShader);
    DecorationParams[DecorationPrecisionHigh].caps.push_back(CapShader);
    DecorationParams[DecorationBlock].caps.push_back(CapShader);
    DecorationParams[DecorationBufferBlock].caps.push_back(CapShader);
    DecorationParams[DecorationRowMajor].caps.push_back(CapMatrix);
    DecorationParams[DecorationColMajor].caps.push_back(CapMatrix);
    DecorationParams[DecorationGLSLShared].caps.push_back(CapShader);
    DecorationParams[DecorationGLSLStd140].caps.push_back(CapShader);
    DecorationParams[DecorationGLSLStd430].caps.push_back(CapShader);
    DecorationParams[DecorationGLSLPacked].caps.push_back(CapShader);
    DecorationParams[DecorationSmooth].caps.push_back(CapShader);
    DecorationParams[DecorationNoperspective].caps.push_back(CapShader);
    DecorationParams[DecorationFlat].caps.push_back(CapShader);
    DecorationParams[DecorationPatch].caps.push_back(CapTess);
    DecorationParams[DecorationCentroid].caps.push_back(CapShader);
    DecorationParams[DecorationSample].caps.push_back(CapShader);
    DecorationParams[DecorationInvariant].caps.push_back(CapShader);
    DecorationParams[DecorationConstant].caps.push_back(CapKernel);
    DecorationParams[DecorationUniform].caps.push_back(CapShader);
    DecorationParams[DecorationCPacked].caps.push_back(CapKernel);
    DecorationParams[DecorationSaturatedConversion].caps.push_back(CapKernel);
    DecorationParams[DecorationStream].caps.push_back(CapGeom);
    DecorationParams[DecorationLocation].caps.push_back(CapShader);
    DecorationParams[DecorationComponent].caps.push_back(CapShader);
    DecorationParams[DecorationIndex].caps.push_back(CapShader);
    DecorationParams[DecorationBinding].caps.push_back(CapShader);
    DecorationParams[DecorationDescriptorSet].caps.push_back(CapShader);
    DecorationParams[DecorationXfbBuffer].caps.push_back(CapShader);
    DecorationParams[DecorationStride].caps.push_back(CapShader);
    DecorationParams[DecorationBuiltIn].caps.push_back(CapShader);
    DecorationParams[DecorationFuncParamAttr].caps.push_back(CapKernel);
    DecorationParams[DecorationFPRoundingMode].caps.push_back(CapKernel);
    DecorationParams[DecorationFPFastMathMode].caps.push_back(CapKernel);
    DecorationParams[DecorationLinkageAttributes].caps.push_back(CapLink);
    DecorationParams[DecorationSpecId].caps.push_back(CapShader);

    BuiltInParams[BuiltInPosition].caps.push_back(CapShader);
    BuiltInParams[BuiltInPointSize].caps.push_back(CapShader);
    BuiltInParams[BuiltInClipVertex].caps.push_back(CapShader);
    BuiltInParams[BuiltInClipDistance].caps.push_back(CapShader);
    BuiltInParams[BuiltInCullDistance].caps.push_back(CapShader);
    BuiltInParams[BuiltInVertexId].caps.push_back(CapShader);
    BuiltInParams[BuiltInInstanceId].caps.push_back(CapShader);
    BuiltInParams[BuiltInPrimitiveId].caps.push_back(CapGeom);
    BuiltInParams[BuiltInPrimitiveId].caps.push_back(CapTess);
    BuiltInParams[BuiltInInvocationId].caps.push_back(CapGeom);
    BuiltInParams[BuiltInInvocationId].caps.push_back(CapTess);
    BuiltInParams[BuiltInLayer].caps.push_back(CapGeom);
    BuiltInParams[BuiltInViewportIndex].caps.push_back(CapGeom);
    BuiltInParams[BuiltInTessLevelOuter].caps.push_back(CapTess);
    BuiltInParams[BuiltInTessLevelInner].caps.push_back(CapTess);
    BuiltInParams[BuiltInTessCoord].caps.push_back(CapTess);
    BuiltInParams[BuiltInPatchVertices].caps.push_back(CapTess);
    BuiltInParams[BuiltInFragCoord].caps.push_back(CapShader);
    BuiltInParams[BuiltInPointCoord].caps.push_back(CapShader);
    BuiltInParams[BuiltInFrontFacing].caps.push_back(CapShader);
    BuiltInParams[BuiltInSampleId].caps.push_back(CapShader);
    BuiltInParams[BuiltInSamplePosition].caps.push_back(CapShader);
    BuiltInParams[BuiltInSampleMask].caps.push_back(CapShader);
    BuiltInParams[BuiltInFragColor].caps.push_back(CapShader);
    BuiltInParams[BuiltInFragDepth].caps.push_back(CapShader);
    BuiltInParams[BuiltInHelperInvocation].caps.push_back(CapShader);
    BuiltInParams[BuiltInLocalInvocationIndex].caps.push_back(CapShader);
    BuiltInParams[BuiltInWorkDim].caps.push_back(CapKernel);
    BuiltInParams[BuiltInGlobalSize].caps.push_back(CapKernel);
    BuiltInParams[BuiltInEnqueuedWorkgroupSize].caps.push_back(CapKernel);
    BuiltInParams[BuiltInGlobalOffset].caps.push_back(CapKernel);
    BuiltInParams[BuiltInGlobalLinearId].caps.push_back(CapKernel);
    BuiltInParams[BuiltInWorkgroupLinearId].caps.push_back(CapKernel);

    BuiltInParams[BuiltInSubgroupSize].caps.push_back(CapKernel);
    BuiltInParams[BuiltInSubgroupMaxSize].caps.push_back(CapKernel);
    BuiltInParams[BuiltInNumSubgroups].caps.push_back(CapKernel);
    BuiltInParams[BuiltInNumEnqueuedSubgroups].caps.push_back(CapKernel);
    BuiltInParams[BuiltInSubgroupId].caps.push_back(CapKernel);
    BuiltInParams[BuiltInSubgroupLocalInvocationId].caps.push_back(CapKernel);

    DimensionalityParams[DimCube].caps.push_back(CapShader);
    DimensionalityParams[DimRect].caps.push_back(CapShader);

    // Group Operations
    for (int i = 0; i < GroupOperationCeiling; ++i) {
        GroupOperationParams[i].caps.push_back(CapKernel);
    }

    // Enqueue flags
    for (int i = 0; i < KernelEnqueueFlagsCeiling; ++i) {
        KernelEnqueueFlagsParams[i].caps.push_back(CapKernel);
    }

    // Profiling info
    KernelProfilingInfoParams[0].caps.push_back(CapKernel);

    // set name of operator, an initial set of <id> style operands, and the description

    InstructionDesc[OpSource].operands.push(OperandSource, "");
    InstructionDesc[OpSource].operands.push(OperandLiteralNumber, "'Version'");

    InstructionDesc[OpSourceExtension].operands.push(OperandLiteralString, "'Extension'");

    InstructionDesc[OpName].operands.push(OperandId, "'Target'");
    InstructionDesc[OpName].operands.push(OperandLiteralString, "'Name'");

    InstructionDesc[OpMemberName].operands.push(OperandId, "'Type'");
    InstructionDesc[OpMemberName].operands.push(OperandLiteralNumber, "'Member'");
    InstructionDesc[OpMemberName].operands.push(OperandLiteralString, "'Name'");

    InstructionDesc[OpString].operands.push(OperandLiteralString, "'String'");

    InstructionDesc[OpLine].operands.push(OperandId, "'Target'");
    InstructionDesc[OpLine].operands.push(OperandId, "'File'");
    InstructionDesc[OpLine].operands.push(OperandLiteralNumber, "'Line'");
    InstructionDesc[OpLine].operands.push(OperandLiteralNumber, "'Column'");

    InstructionDesc[OpExtension].operands.push(OperandLiteralString, "'Name'");

    InstructionDesc[OpExtInstImport].operands.push(OperandLiteralString, "'Name'");

    InstructionDesc[OpMemoryModel].operands.push(OperandAddressing, "");
    InstructionDesc[OpMemoryModel].operands.push(OperandMemory, "");

    InstructionDesc[OpEntryPoint].operands.push(OperandExecutionModel, "");
    InstructionDesc[OpEntryPoint].operands.push(OperandId, "'Entry Point'");

    InstructionDesc[OpExecutionMode].operands.push(OperandId, "'Entry Point'");
    InstructionDesc[OpExecutionMode].operands.push(OperandExecutionMode, "'Mode'");
    InstructionDesc[OpExecutionMode].operands.push(OperandVariableLiterals, "See <<Execution Mode,Execution Mode>>");

    InstructionDesc[OpTypeInt].operands.push(OperandLiteralNumber, "'Width'");
    InstructionDesc[OpTypeInt].operands.push(OperandLiteralNumber, "'Signedness'");

    InstructionDesc[OpTypeFloat].operands.push(OperandLiteralNumber, "'Width'");

    InstructionDesc[OpTypeVector].operands.push(OperandId, "'Component type'");
    InstructionDesc[OpTypeVector].operands.push(OperandLiteralNumber, "'Component count'");

    InstructionDesc[OpTypeMatrix].capabilities.push_back(CapMatrix);
    InstructionDesc[OpTypeMatrix].operands.push(OperandId, "'Column type'");
    InstructionDesc[OpTypeMatrix].operands.push(OperandLiteralNumber, "'Column count'");

    InstructionDesc[OpTypeSampler].operands.push(OperandId, "'Sampled Type'");
    InstructionDesc[OpTypeSampler].operands.push(OperandDimensionality, "");
    InstructionDesc[OpTypeSampler].operands.push(OperandLiteralNumber, "'Content'");
    InstructionDesc[OpTypeSampler].operands.push(OperandLiteralNumber, "'Arrayed'");
    InstructionDesc[OpTypeSampler].operands.push(OperandLiteralNumber, "'Compare'");
    InstructionDesc[OpTypeSampler].operands.push(OperandLiteralNumber, "'MS'");
    InstructionDesc[OpTypeSampler].operands.push(OperandOptionalId, "'Qualifier'");

    InstructionDesc[OpTypeArray].operands.push(OperandId, "'Element type'");
    InstructionDesc[OpTypeArray].operands.push(OperandId, "'Length'");

    InstructionDesc[OpTypeRuntimeArray].capabilities.push_back(CapShader);
    InstructionDesc[OpTypeRuntimeArray].operands.push(OperandId, "'Element type'");

    InstructionDesc[OpTypeStruct].operands.push(OperandVariableIds, "'Member 0 type', +\n'member 1 type', +\n...");

    InstructionDesc[OpTypeOpaque].capabilities.push_back(CapKernel);
    InstructionDesc[OpTypeOpaque].operands.push(OperandLiteralString, "The name of the opaque type.");

    InstructionDesc[OpTypePointer].operands.push(OperandStorage, "");
    InstructionDesc[OpTypePointer].operands.push(OperandId, "'Type'");

    InstructionDesc[OpTypeEvent].capabilities.push_back(CapKernel);

    InstructionDesc[OpTypeDeviceEvent].capabilities.push_back(CapKernel);

    InstructionDesc[OpTypeReserveId].capabilities.push_back(CapKernel);

    InstructionDesc[OpTypeQueue].capabilities.push_back(CapKernel);

    InstructionDesc[OpTypePipe].operands.push(OperandId, "'Type'");
    InstructionDesc[OpTypePipe].operands.push(OperandAccessQualifier, "'Qualifier'");
    InstructionDesc[OpTypePipe].capabilities.push_back(CapKernel);

    InstructionDesc[OpTypeFunction].operands.push(OperandId, "'Return Type'");
    InstructionDesc[OpTypeFunction].operands.push(OperandVariableIds, "'Parameter 0 Type', +\n'Parameter 1 Type', +\n...");

    InstructionDesc[OpConstant].operands.push(OperandVariableLiterals, "'Value'");

    InstructionDesc[OpConstantComposite].operands.push(OperandVariableIds, "'Constituents'");

    InstructionDesc[OpConstantNullPointer].capabilities.push_back(CapAddr);

    InstructionDesc[OpConstantNullObject].capabilities.push_back(CapKernel);

    InstructionDesc[OpConstantSampler].capabilities.push_back(CapKernel);
    InstructionDesc[OpConstantSampler].operands.push(OperandLiteralNumber, "'Mode'");
    InstructionDesc[OpConstantSampler].operands.push(OperandLiteralNumber, "'Param'");
    InstructionDesc[OpConstantSampler].operands.push(OperandLiteralNumber, "'Filter'");

    InstructionDesc[OpSpecConstantTrue].capabilities.push_back(CapShader);

    InstructionDesc[OpSpecConstantFalse].capabilities.push_back(CapShader);

    InstructionDesc[OpSpecConstant].operands.push(OperandVariableLiterals, "'Value'");
    InstructionDesc[OpSpecConstant].capabilities.push_back(CapShader);

    InstructionDesc[OpSpecConstantComposite].operands.push(OperandVariableIds, "'Constituents'");
    InstructionDesc[OpSpecConstantComposite].capabilities.push_back(CapShader);

    InstructionDesc[OpVariable].operands.push(OperandStorage, "");
    InstructionDesc[OpVariable].operands.push(OperandOptionalId, "'Initializer'");

    InstructionDesc[OpVariableArray].operands.push(OperandStorage, "");
    InstructionDesc[OpVariableArray].operands.push(OperandId, "'N'");
    InstructionDesc[OpVariableArray].capabilities.push_back(CapAddr);

    InstructionDesc[OpFunction].operands.push(OperandFunction, "");
    InstructionDesc[OpFunction].operands.push(OperandId, "'Function Type'");

    InstructionDesc[OpFunctionCall].operands.push(OperandId, "'Function'");
    InstructionDesc[OpFunctionCall].operands.push(OperandVariableIds, "'Argument 0', +\n'Argument 1', +\n...");

    InstructionDesc[OpExtInst].operands.push(OperandId, "'Set'");
    InstructionDesc[OpExtInst].operands.push(OperandLiteralNumber, "'Instruction'");
    InstructionDesc[OpExtInst].operands.push(OperandVariableIds, "'Operand 1', +\n'Operand 2', +\n...");

    InstructionDesc[OpLoad].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpLoad].operands.push(OperandVariableLiterals, "'Memory Access'");

    InstructionDesc[OpStore].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpStore].operands.push(OperandId, "'Object'");
    InstructionDesc[OpStore].operands.push(OperandVariableLiterals, "'Memory Access'");

    InstructionDesc[OpPhi].operands.push(OperandVariableIds, "");

    InstructionDesc[OpDecorate].operands.push(OperandId, "'Target'");
    InstructionDesc[OpDecorate].operands.push(OperandDecoration, "");
    InstructionDesc[OpDecorate].operands.push(OperandVariableLiterals, "See <<Decoration,'Decoration'>>.");

    InstructionDesc[OpMemberDecorate].operands.push(OperandId, "'Structure type'");
    InstructionDesc[OpMemberDecorate].operands.push(OperandLiteralNumber, "'Member'");
    InstructionDesc[OpMemberDecorate].operands.push(OperandDecoration, "");
    InstructionDesc[OpMemberDecorate].operands.push(OperandVariableLiterals, "See <<Decoration,'Decoration'>>.");

    InstructionDesc[OpGroupDecorate].operands.push(OperandId, "'Decoration group'");
    InstructionDesc[OpGroupDecorate].operands.push(OperandVariableIds, "'Target', 'Target', ...");

    InstructionDesc[OpGroupMemberDecorate].operands.push(OperandId, "'Decoration group'");
    InstructionDesc[OpGroupMemberDecorate].operands.push(OperandVariableIds, "'Target', 'Target', ...");

    InstructionDesc[OpVectorExtractDynamic].operands.push(OperandId, "'Vector'");
    InstructionDesc[OpVectorExtractDynamic].operands.push(OperandId, "'Index'");

    InstructionDesc[OpVectorInsertDynamic].operands.push(OperandId, "'Vector'");
    InstructionDesc[OpVectorInsertDynamic].operands.push(OperandId, "'Component'");
    InstructionDesc[OpVectorInsertDynamic].operands.push(OperandId, "'Index'");

    InstructionDesc[OpVectorShuffle].operands.push(OperandId, "'Vector 1'");
    InstructionDesc[OpVectorShuffle].operands.push(OperandId, "'Vector 2'");
    InstructionDesc[OpVectorShuffle].operands.push(OperandVariableLiterals, "'Components'");

    InstructionDesc[OpCompositeConstruct].operands.push(OperandVariableIds, "'Constituents'");

    InstructionDesc[OpCompositeExtract].operands.push(OperandId, "'Composite'");
    InstructionDesc[OpCompositeExtract].operands.push(OperandVariableLiterals, "'Indexes'");

    InstructionDesc[OpCompositeInsert].operands.push(OperandId, "'Object'");
    InstructionDesc[OpCompositeInsert].operands.push(OperandId, "'Composite'");
    InstructionDesc[OpCompositeInsert].operands.push(OperandVariableLiterals, "'Indexes'");

    InstructionDesc[OpCopyObject].operands.push(OperandId, "'Operand'");

    InstructionDesc[OpCopyMemory].operands.push(OperandId, "'Target'");
    InstructionDesc[OpCopyMemory].operands.push(OperandId, "'Source'");
    InstructionDesc[OpCopyMemory].operands.push(OperandVariableLiterals, "'Memory Access'");

    InstructionDesc[OpCopyMemorySized].operands.push(OperandId, "'Target'");
    InstructionDesc[OpCopyMemorySized].operands.push(OperandId, "'Source'");
    InstructionDesc[OpCopyMemorySized].operands.push(OperandId, "'Size'");
    InstructionDesc[OpCopyMemorySized].operands.push(OperandVariableLiterals, "'Memory Access'");

    InstructionDesc[OpCopyMemorySized].capabilities.push_back(CapAddr);

    InstructionDesc[OpSampler].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpSampler].operands.push(OperandId, "'Filter'");

    InstructionDesc[OpTextureSample].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSample].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSample].operands.push(OperandOptionalId, "['Bias']");
    InstructionDesc[OpTextureSample].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleDref].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleDref].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleDref].operands.push(OperandId, "'D~ref~'");
    InstructionDesc[OpTextureSampleDref].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleLod].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleLod].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleLod].operands.push(OperandId, "'Level of Detail'");
    InstructionDesc[OpTextureSampleLod].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleProj].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleProj].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleProj].operands.push(OperandOptionalId, "['Bias']");
    InstructionDesc[OpTextureSampleProj].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleGrad].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleGrad].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleGrad].operands.push(OperandId, "'dx'");
    InstructionDesc[OpTextureSampleGrad].operands.push(OperandId, "'dy'");
    InstructionDesc[OpTextureSampleGrad].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleOffset].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleOffset].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleOffset].operands.push(OperandId, "'Offset'");
    InstructionDesc[OpTextureSampleOffset].operands.push(OperandOptionalId, "['Bias']");
    InstructionDesc[OpTextureSampleOffset].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleProjLod].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleProjLod].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleProjLod].operands.push(OperandId, "'Level of Detail'");
    InstructionDesc[OpTextureSampleProjLod].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleProjGrad].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleProjGrad].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleProjGrad].operands.push(OperandId, "'dx'");
    InstructionDesc[OpTextureSampleProjGrad].operands.push(OperandId, "'dy'");
    InstructionDesc[OpTextureSampleProjGrad].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleLodOffset].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleLodOffset].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleLodOffset].operands.push(OperandId, "'Level of Detail'");
    InstructionDesc[OpTextureSampleLodOffset].operands.push(OperandId, "'Offset'");
    InstructionDesc[OpTextureSampleLodOffset].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleProjOffset].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleProjOffset].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleProjOffset].operands.push(OperandId, "'Offset'");
    InstructionDesc[OpTextureSampleProjOffset].operands.push(OperandOptionalId, "['Bias']");
    InstructionDesc[OpTextureSampleProjOffset].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleGradOffset].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleGradOffset].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleGradOffset].operands.push(OperandId, "'dx'");
    InstructionDesc[OpTextureSampleGradOffset].operands.push(OperandId, "'dy'");
    InstructionDesc[OpTextureSampleGradOffset].operands.push(OperandId, "'Offset'");
    InstructionDesc[OpTextureSampleGradOffset].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleProjLodOffset].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleProjLodOffset].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleProjLodOffset].operands.push(OperandId, "'Level of Detail'");
    InstructionDesc[OpTextureSampleProjLodOffset].operands.push(OperandId, "'Offset'");
    InstructionDesc[OpTextureSampleProjLodOffset].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureSampleProjGradOffset].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureSampleProjGradOffset].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureSampleProjGradOffset].operands.push(OperandId, "'dx'");
    InstructionDesc[OpTextureSampleProjGradOffset].operands.push(OperandId, "'dy'");
    InstructionDesc[OpTextureSampleProjGradOffset].operands.push(OperandId, "'Offset'");
    InstructionDesc[OpTextureSampleProjGradOffset].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureFetchTexelLod].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureFetchTexelLod].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureFetchTexelLod].operands.push(OperandId, "'Level of Detail'");
    InstructionDesc[OpTextureFetchTexelLod].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureFetchTexelOffset].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureFetchTexelOffset].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureFetchTexelOffset].operands.push(OperandId, "'Offset'");
    InstructionDesc[OpTextureFetchTexelOffset].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureFetchSample].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureFetchSample].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureFetchSample].operands.push(OperandId, "'Sample'");
    InstructionDesc[OpTextureFetchSample].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureFetchTexel].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureFetchTexel].operands.push(OperandId, "'Element'");
    InstructionDesc[OpTextureFetchTexel].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureGather].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureGather].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureGather].operands.push(OperandId, "'Component'");
    InstructionDesc[OpTextureGather].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureGatherOffset].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureGatherOffset].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureGatherOffset].operands.push(OperandId, "'Component'");
    InstructionDesc[OpTextureGatherOffset].operands.push(OperandId, "'Offset'");
    InstructionDesc[OpTextureGatherOffset].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureGatherOffsets].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureGatherOffsets].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureGatherOffsets].operands.push(OperandId, "'Component'");
    InstructionDesc[OpTextureGatherOffsets].operands.push(OperandId, "'Offsets'");
    InstructionDesc[OpTextureGatherOffsets].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureQuerySizeLod].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureQuerySizeLod].operands.push(OperandId, "'Level of Detail'");
    InstructionDesc[OpTextureQuerySizeLod].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureQuerySize].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureQuerySize].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureQueryLod].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureQueryLod].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpTextureQueryLod].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureQueryLevels].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureQueryLevels].capabilities.push_back(CapShader);

    InstructionDesc[OpTextureQuerySamples].operands.push(OperandId, "'Sampler'");
    InstructionDesc[OpTextureQuerySamples].capabilities.push_back(CapShader);

    InstructionDesc[OpAccessChain].operands.push(OperandId, "'Base'");
    InstructionDesc[OpAccessChain].operands.push(OperandVariableIds, "'Indexes'");

    InstructionDesc[OpInBoundsAccessChain].operands.push(OperandId, "'Base'");
    InstructionDesc[OpInBoundsAccessChain].operands.push(OperandVariableIds, "'Indexes'");

    InstructionDesc[OpSNegate].operands.push(OperandId, "'Operand'");

    InstructionDesc[OpFNegate].operands.push(OperandId, "'Operand'");

    InstructionDesc[OpNot].operands.push(OperandId, "'Operand'");

    InstructionDesc[OpAny].operands.push(OperandId, "'Vector'");

    InstructionDesc[OpAll].operands.push(OperandId, "'Vector'");

    InstructionDesc[OpConvertFToU].operands.push(OperandId, "'Float Value'");

    InstructionDesc[OpConvertFToS].operands.push(OperandId, "'Float Value'");

    InstructionDesc[OpConvertSToF].operands.push(OperandId, "'Signed Value'");

    InstructionDesc[OpConvertUToF].operands.push(OperandId, "'Unsigned value'");

    InstructionDesc[OpUConvert].operands.push(OperandId, "'Unsigned value'");

    InstructionDesc[OpSConvert].operands.push(OperandId, "'Signed Value'");

    InstructionDesc[OpFConvert].operands.push(OperandId, "'Float Value'");

    InstructionDesc[OpSatConvertSToU].operands.push(OperandId, "'Signed Value'");
    InstructionDesc[OpSatConvertSToU].capabilities.push_back(CapKernel);

    InstructionDesc[OpSatConvertUToS].operands.push(OperandId, "'Unsigned Value'");
    InstructionDesc[OpSatConvertUToS].capabilities.push_back(CapKernel);

    InstructionDesc[OpConvertPtrToU].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpConvertPtrToU].capabilities.push_back(CapAddr);

    InstructionDesc[OpConvertUToPtr].operands.push(OperandId, "'Integer value'");
    InstructionDesc[OpConvertUToPtr].capabilities.push_back(CapAddr);

    InstructionDesc[OpPtrCastToGeneric].operands.push(OperandId, "'Source pointer'");
    InstructionDesc[OpPtrCastToGeneric].capabilities.push_back(CapKernel);


    InstructionDesc[OpGenericCastToPtr].operands.push(OperandId, "'Source pointer'");
    InstructionDesc[OpGenericCastToPtr].capabilities.push_back(CapKernel);

    InstructionDesc[OpGenericCastToPtrExplicit].operands.push(OperandId, "'Source pointer'");
    InstructionDesc[OpGenericCastToPtrExplicit].operands.push(OperandStorage, "'storage'");
    InstructionDesc[OpGenericCastToPtrExplicit].capabilities.push_back(CapKernel);

    InstructionDesc[OpGenericPtrMemSemantics].operands.push(OperandId, "'ptr'");
    InstructionDesc[OpGenericPtrMemSemantics].capabilities.push_back(CapKernel);

    InstructionDesc[OpBitcast].operands.push(OperandId, "'Operand'");

    InstructionDesc[OpTranspose].capabilities.push_back(CapMatrix);
    InstructionDesc[OpTranspose].operands.push(OperandId, "'Matrix'");

    InstructionDesc[OpIsNan].operands.push(OperandId, "'x'");

    InstructionDesc[OpIsInf].operands.push(OperandId, "'x'");

    InstructionDesc[OpIsFinite].capabilities.push_back(CapKernel);
    InstructionDesc[OpIsFinite].operands.push(OperandId, "'x'");

    InstructionDesc[OpIsNormal].capabilities.push_back(CapKernel);
    InstructionDesc[OpIsNormal].operands.push(OperandId, "'x'");

    InstructionDesc[OpSignBitSet].capabilities.push_back(CapKernel);
    InstructionDesc[OpSignBitSet].operands.push(OperandId, "'x'");

    InstructionDesc[OpLessOrGreater].capabilities.push_back(CapKernel);
    InstructionDesc[OpLessOrGreater].operands.push(OperandId, "'x'");
    InstructionDesc[OpLessOrGreater].operands.push(OperandId, "'y'");

    InstructionDesc[OpOrdered].capabilities.push_back(CapKernel);
    InstructionDesc[OpOrdered].operands.push(OperandId, "'x'");
    InstructionDesc[OpOrdered].operands.push(OperandId, "'y'");

    InstructionDesc[OpUnordered].capabilities.push_back(CapKernel);
    InstructionDesc[OpUnordered].operands.push(OperandId, "'x'");
    InstructionDesc[OpUnordered].operands.push(OperandId, "'y'");

    InstructionDesc[OpArrayLength].operands.push(OperandId, "'Structure'");
    InstructionDesc[OpArrayLength].operands.push(OperandLiteralNumber, "'Array member'");
    InstructionDesc[OpArrayLength].capabilities.push_back(CapShader);

    InstructionDesc[OpIAdd].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpIAdd].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFAdd].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFAdd].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpISub].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpISub].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFSub].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFSub].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpIMul].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpIMul].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFMul].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFMul].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpUDiv].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpUDiv].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpSDiv].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpSDiv].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFDiv].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFDiv].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpUMod].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpUMod].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpSRem].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpSRem].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpSMod].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpSMod].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFRem].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFRem].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFMod].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFMod].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpVectorTimesScalar].operands.push(OperandId, "'Vector'");
    InstructionDesc[OpVectorTimesScalar].operands.push(OperandId, "'Scalar'");

    InstructionDesc[OpMatrixTimesScalar].capabilities.push_back(CapMatrix);
    InstructionDesc[OpMatrixTimesScalar].operands.push(OperandId, "'Matrix'");
    InstructionDesc[OpMatrixTimesScalar].operands.push(OperandId, "'Scalar'");

    InstructionDesc[OpVectorTimesMatrix].capabilities.push_back(CapMatrix);
    InstructionDesc[OpVectorTimesMatrix].operands.push(OperandId, "'Vector'");
    InstructionDesc[OpVectorTimesMatrix].operands.push(OperandId, "'Matrix'");

    InstructionDesc[OpMatrixTimesVector].capabilities.push_back(CapMatrix);
    InstructionDesc[OpMatrixTimesVector].operands.push(OperandId, "'Matrix'");
    InstructionDesc[OpMatrixTimesVector].operands.push(OperandId, "'Vector'");

    InstructionDesc[OpMatrixTimesMatrix].capabilities.push_back(CapMatrix);
    InstructionDesc[OpMatrixTimesMatrix].operands.push(OperandId, "'LeftMatrix'");
    InstructionDesc[OpMatrixTimesMatrix].operands.push(OperandId, "'RightMatrix'");

    InstructionDesc[OpOuterProduct].capabilities.push_back(CapMatrix);
    InstructionDesc[OpOuterProduct].operands.push(OperandId, "'Vector 1'");
    InstructionDesc[OpOuterProduct].operands.push(OperandId, "'Vector 2'");

    InstructionDesc[OpDot].operands.push(OperandId, "'Vector 1'");
    InstructionDesc[OpDot].operands.push(OperandId, "'Vector 2'");

    InstructionDesc[OpShiftRightLogical].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpShiftRightLogical].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpShiftRightArithmetic].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpShiftRightArithmetic].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpShiftLeftLogical].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpShiftLeftLogical].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpLogicalOr].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpLogicalOr].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpLogicalXor].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpLogicalXor].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpLogicalAnd].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpLogicalAnd].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpBitwiseOr].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpBitwiseOr].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpBitwiseXor].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpBitwiseXor].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpBitwiseAnd].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpBitwiseAnd].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpSelect].operands.push(OperandId, "'Condition'");
    InstructionDesc[OpSelect].operands.push(OperandId, "'Object 1'");
    InstructionDesc[OpSelect].operands.push(OperandId, "'Object 2'");

    InstructionDesc[OpIEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpIEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFOrdEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFOrdEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFUnordEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFUnordEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpINotEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpINotEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFOrdNotEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFOrdNotEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFUnordNotEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFUnordNotEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpULessThan].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpULessThan].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpSLessThan].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpSLessThan].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFOrdLessThan].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFOrdLessThan].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFUnordLessThan].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFUnordLessThan].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpUGreaterThan].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpUGreaterThan].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpSGreaterThan].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpSGreaterThan].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFOrdGreaterThan].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFOrdGreaterThan].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFUnordGreaterThan].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFUnordGreaterThan].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpULessThanEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpULessThanEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpSLessThanEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpSLessThanEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFOrdLessThanEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFOrdLessThanEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFUnordLessThanEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFUnordLessThanEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpUGreaterThanEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpUGreaterThanEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpSGreaterThanEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpSGreaterThanEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFOrdGreaterThanEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFOrdGreaterThanEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpFUnordGreaterThanEqual].operands.push(OperandId, "'Operand 1'");
    InstructionDesc[OpFUnordGreaterThanEqual].operands.push(OperandId, "'Operand 2'");

    InstructionDesc[OpDPdx].capabilities.push_back(CapShader);
    InstructionDesc[OpDPdx].operands.push(OperandId, "'P'");

    InstructionDesc[OpDPdy].capabilities.push_back(CapShader);
    InstructionDesc[OpDPdy].operands.push(OperandId, "'P'");

    InstructionDesc[OpFwidth].capabilities.push_back(CapShader);
    InstructionDesc[OpFwidth].operands.push(OperandId, "'P'");

    InstructionDesc[OpDPdxFine].capabilities.push_back(CapShader);
    InstructionDesc[OpDPdxFine].operands.push(OperandId, "'P'");

    InstructionDesc[OpDPdyFine].capabilities.push_back(CapShader);
    InstructionDesc[OpDPdyFine].operands.push(OperandId, "'P'");

    InstructionDesc[OpFwidthFine].capabilities.push_back(CapShader);
    InstructionDesc[OpFwidthFine].operands.push(OperandId, "'P'");

    InstructionDesc[OpDPdxCoarse].capabilities.push_back(CapShader);
    InstructionDesc[OpDPdxCoarse].operands.push(OperandId, "'P'");

    InstructionDesc[OpDPdyCoarse].capabilities.push_back(CapShader);
    InstructionDesc[OpDPdyCoarse].operands.push(OperandId, "'P'");

    InstructionDesc[OpFwidthCoarse].capabilities.push_back(CapShader);
    InstructionDesc[OpFwidthCoarse].operands.push(OperandId, "'P'");

    InstructionDesc[OpEmitVertex].capabilities.push_back(CapGeom);

    InstructionDesc[OpEndPrimitive].capabilities.push_back(CapGeom);

    InstructionDesc[OpEmitStreamVertex].operands.push(OperandId, "'Stream'");
    InstructionDesc[OpEmitStreamVertex].capabilities.push_back(CapGeom);

    InstructionDesc[OpEndStreamPrimitive].operands.push(OperandId, "'Stream'");
    InstructionDesc[OpEndStreamPrimitive].capabilities.push_back(CapGeom);

    InstructionDesc[OpControlBarrier].operands.push(OperandExecutionScope, "'Scope'");

    InstructionDesc[OpMemoryBarrier].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpMemoryBarrier].operands.push(OperandMemorySemantics, "'Semantics'");

    InstructionDesc[OpImagePointer].operands.push(OperandId, "'Image'");
    InstructionDesc[OpImagePointer].operands.push(OperandId, "'Coordinate'");
    InstructionDesc[OpImagePointer].operands.push(OperandId, "'Sample'");

    InstructionDesc[OpAtomicInit].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicInit].operands.push(OperandId, "'Value'");

    InstructionDesc[OpAtomicLoad].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicLoad].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicLoad].operands.push(OperandMemorySemantics, "'Semantics'");

    InstructionDesc[OpAtomicStore].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicStore].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicStore].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicStore].operands.push(OperandId, "'Value'");

    InstructionDesc[OpAtomicExchange].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicExchange].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicExchange].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicExchange].operands.push(OperandId, "'Value'");

    InstructionDesc[OpAtomicCompareExchange].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicCompareExchange].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicCompareExchange].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicCompareExchange].operands.push(OperandId, "'Value'");
    InstructionDesc[OpAtomicCompareExchange].operands.push(OperandId, "'Comparator'");

    InstructionDesc[OpAtomicCompareExchangeWeak].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicCompareExchangeWeak].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicCompareExchangeWeak].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicCompareExchangeWeak].operands.push(OperandId, "'Value'");
    InstructionDesc[OpAtomicCompareExchangeWeak].operands.push(OperandId, "'Comparator'");

    InstructionDesc[OpAtomicIIncrement].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicIIncrement].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicIIncrement].operands.push(OperandMemorySemantics, "'Semantics'");

    InstructionDesc[OpAtomicIDecrement].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicIDecrement].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicIDecrement].operands.push(OperandMemorySemantics, "'Semantics'");

    InstructionDesc[OpAtomicIAdd].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicIAdd].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicIAdd].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicIAdd].operands.push(OperandId, "'Value'");

    InstructionDesc[OpAtomicISub].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicISub].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicISub].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicISub].operands.push(OperandId, "'Value'");

    InstructionDesc[OpAtomicUMin].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicUMin].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicUMin].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicUMin].operands.push(OperandId, "'Value'");

    InstructionDesc[OpAtomicUMax].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicUMax].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicUMax].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicUMax].operands.push(OperandId, "'Value'");

    InstructionDesc[OpAtomicIMin].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicIMin].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicIMin].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicIMin].operands.push(OperandId, "'Value'");

    InstructionDesc[OpAtomicIMax].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicIMax].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicIMax].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicIMax].operands.push(OperandId, "'Value'");

    InstructionDesc[OpAtomicAnd].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicAnd].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicAnd].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicAnd].operands.push(OperandId, "'Value'");

    InstructionDesc[OpAtomicOr].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicOr].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicOr].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicOr].operands.push(OperandId, "'Value'");

    InstructionDesc[OpAtomicXor].operands.push(OperandId, "'Pointer'");
    InstructionDesc[OpAtomicXor].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAtomicXor].operands.push(OperandMemorySemantics, "'Semantics'");
    InstructionDesc[OpAtomicXor].operands.push(OperandId, "'Value'");

    InstructionDesc[OpLoopMerge].operands.push(OperandId, "'Label'");
    InstructionDesc[OpLoopMerge].operands.push(OperandLoop, "");

    InstructionDesc[OpSelectionMerge].operands.push(OperandId, "'Label'");
    InstructionDesc[OpSelectionMerge].operands.push(OperandSelect, "");

    InstructionDesc[OpBranch].operands.push(OperandId, "'Target Label'");

    InstructionDesc[OpBranchConditional].operands.push(OperandId, "'Condition'");
    InstructionDesc[OpBranchConditional].operands.push(OperandId, "'True Label'");
    InstructionDesc[OpBranchConditional].operands.push(OperandId, "'False Label'");
    InstructionDesc[OpBranchConditional].operands.push(OperandVariableLiterals, "'Branch weights'");

    InstructionDesc[OpSwitch].operands.push(OperandId, "'Selector'");
    InstructionDesc[OpSwitch].operands.push(OperandId, "'Default'");
    InstructionDesc[OpSwitch].operands.push(OperandVariableLiteralId, "'Target'");

    InstructionDesc[OpKill].capabilities.push_back(CapShader);

    InstructionDesc[OpReturnValue].operands.push(OperandId, "'Value'");

    InstructionDesc[OpUnreachable].capabilities.push_back(CapKernel);

    InstructionDesc[OpLifetimeStart].operands.push(OperandId, "");
    InstructionDesc[OpLifetimeStart].operands.push(OperandLiteralNumber, "");

    InstructionDesc[OpLifetimeStop].operands.push(OperandId, "");
    InstructionDesc[OpLifetimeStop].operands.push(OperandLiteralNumber, "");

    InstructionDesc[OpCompileFlag].capabilities.push_back(CapKernel);
    InstructionDesc[OpCompileFlag].operands.push(OperandLiteralString, "'Flag'");

    InstructionDesc[OpAsyncGroupCopy].capabilities.push_back(CapKernel);
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandId, "'Destination'");
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandId, "'Source'");
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandId, "'Num Elements'");
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandId, "'Stride'");
    InstructionDesc[OpAsyncGroupCopy].operands.push(OperandId, "'Event'");

    InstructionDesc[OpWaitGroupEvents].capabilities.push_back(CapKernel);
    InstructionDesc[OpWaitGroupEvents].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpWaitGroupEvents].operands.push(OperandId, "'Num Events'");
    InstructionDesc[OpWaitGroupEvents].operands.push(OperandId, "'Events List'");

    InstructionDesc[OpGroupAll].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupAll].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupAll].operands.push(OperandId, "'Predicate'");

    InstructionDesc[OpGroupAny].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupAny].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupAny].operands.push(OperandId, "'Predicate'");

    InstructionDesc[OpGroupBroadcast].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupBroadcast].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupBroadcast].operands.push(OperandId, "'Value'");
    InstructionDesc[OpGroupBroadcast].operands.push(OperandId, "'LocalId'");

    InstructionDesc[OpGroupIAdd].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupIAdd].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupIAdd].operands.push(OperandGroupOperation, "'Operation'");
    InstructionDesc[OpGroupIAdd].operands.push(OperandId, "'X'");

    InstructionDesc[OpGroupFAdd].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupFAdd].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupFAdd].operands.push(OperandGroupOperation, "'Operation'");
    InstructionDesc[OpGroupFAdd].operands.push(OperandId, "'X'");

    InstructionDesc[OpGroupUMin].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupUMin].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupUMin].operands.push(OperandGroupOperation, "'Operation'");
    InstructionDesc[OpGroupUMin].operands.push(OperandId, "'X'");

    InstructionDesc[OpGroupSMin].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupSMin].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupSMin].operands.push(OperandGroupOperation, "'Operation'");
    InstructionDesc[OpGroupSMin].operands.push(OperandId, "X");

    InstructionDesc[OpGroupFMin].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupFMin].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupFMin].operands.push(OperandGroupOperation, "'Operation'");
    InstructionDesc[OpGroupFMin].operands.push(OperandId, "X");

    InstructionDesc[OpGroupUMax].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupUMax].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupUMax].operands.push(OperandGroupOperation, "'Operation'");
    InstructionDesc[OpGroupUMax].operands.push(OperandId, "X");

    InstructionDesc[OpGroupSMax].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupSMax].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupSMax].operands.push(OperandGroupOperation, "'Operation'");
    InstructionDesc[OpGroupSMax].operands.push(OperandId, "X");

    InstructionDesc[OpGroupFMax].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupFMax].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupFMax].operands.push(OperandGroupOperation, "'Operation'");
    InstructionDesc[OpGroupFMax].operands.push(OperandId, "X");

    InstructionDesc[OpReadPipe].capabilities.push_back(CapKernel);
    InstructionDesc[OpReadPipe].operands.push(OperandId, "'p'");
    InstructionDesc[OpReadPipe].operands.push(OperandId, "'ptr'");

    InstructionDesc[OpWritePipe].capabilities.push_back(CapKernel);
    InstructionDesc[OpWritePipe].operands.push(OperandId, "'p'");
    InstructionDesc[OpWritePipe].operands.push(OperandId, "'ptr'");

    InstructionDesc[OpReservedReadPipe].capabilities.push_back(CapKernel);
    InstructionDesc[OpReservedReadPipe].operands.push(OperandId, "'p'");
    InstructionDesc[OpReservedReadPipe].operands.push(OperandId, "'reserve_id'");
    InstructionDesc[OpReservedReadPipe].operands.push(OperandId, "'index'");
    InstructionDesc[OpReservedReadPipe].operands.push(OperandId, "'ptr'");

    InstructionDesc[OpReservedWritePipe].capabilities.push_back(CapKernel);
    InstructionDesc[OpReservedWritePipe].operands.push(OperandId, "'p'");
    InstructionDesc[OpReservedWritePipe].operands.push(OperandId, "'reserve_id'");
    InstructionDesc[OpReservedWritePipe].operands.push(OperandId, "'index'");
    InstructionDesc[OpReservedWritePipe].operands.push(OperandId, "'ptr'");

    InstructionDesc[OpReserveReadPipePackets].capabilities.push_back(CapKernel);
    InstructionDesc[OpReserveReadPipePackets].operands.push(OperandId, "'p'");
    InstructionDesc[OpReserveReadPipePackets].operands.push(OperandId, "'num_packets'");

    InstructionDesc[OpReserveWritePipePackets].capabilities.push_back(CapKernel);
    InstructionDesc[OpReserveWritePipePackets].operands.push(OperandId, "'p'");
    InstructionDesc[OpReserveWritePipePackets].operands.push(OperandId, "'num_packets'");

    InstructionDesc[OpCommitReadPipe].capabilities.push_back(CapKernel);
    InstructionDesc[OpCommitReadPipe].operands.push(OperandId, "'p'");
    InstructionDesc[OpCommitReadPipe].operands.push(OperandId, "'reserve_id'");

    InstructionDesc[OpCommitWritePipe].capabilities.push_back(CapKernel);
    InstructionDesc[OpCommitWritePipe].operands.push(OperandId, "'p'");
    InstructionDesc[OpCommitWritePipe].operands.push(OperandId, "'reserve_id'");

    InstructionDesc[OpIsValidReserveId].capabilities.push_back(CapKernel);
    InstructionDesc[OpIsValidReserveId].operands.push(OperandId, "'reserve_id'");

    InstructionDesc[OpGetNumPipePackets].capabilities.push_back(CapKernel);
    InstructionDesc[OpGetNumPipePackets].operands.push(OperandId, "'p'");

    InstructionDesc[OpGetMaxPipePackets].capabilities.push_back(CapKernel);
    InstructionDesc[OpGetMaxPipePackets].operands.push(OperandId, "'p'");

    InstructionDesc[OpGroupReserveReadPipePackets].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupReserveReadPipePackets].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupReserveReadPipePackets].operands.push(OperandId, "'p'");
    InstructionDesc[OpGroupReserveReadPipePackets].operands.push(OperandId, "'num_packets'");

    InstructionDesc[OpGroupReserveWritePipePackets].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupReserveWritePipePackets].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupReserveWritePipePackets].operands.push(OperandId, "'p'");
    InstructionDesc[OpGroupReserveWritePipePackets].operands.push(OperandId, "'num_packets'");

    InstructionDesc[OpGroupCommitReadPipe].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupCommitReadPipe].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupCommitReadPipe].operands.push(OperandId, "'p'");
    InstructionDesc[OpGroupCommitReadPipe].operands.push(OperandId, "'reserve_id'");

    InstructionDesc[OpGroupCommitWritePipe].capabilities.push_back(CapKernel);
    InstructionDesc[OpGroupCommitWritePipe].operands.push(OperandExecutionScope, "'Scope'");
    InstructionDesc[OpGroupCommitWritePipe].operands.push(OperandId, "'p'");
    InstructionDesc[OpGroupCommitWritePipe].operands.push(OperandId, "'reserve_id'");

    InstructionDesc[OpBuildNDRange].capabilities.push_back(CapKernel);
    InstructionDesc[OpBuildNDRange].operands.push(OperandId, "'GlobalWorkSize'");
    InstructionDesc[OpBuildNDRange].operands.push(OperandId, "'LocalWorkSize'");
    InstructionDesc[OpBuildNDRange].operands.push(OperandId, "'GlobalWorkOffset'");

    InstructionDesc[OpGetDefaultQueue].capabilities.push_back(CapKernel);

    InstructionDesc[OpCaptureEventProfilingInfo].capabilities.push_back(CapKernel);

    InstructionDesc[OpCaptureEventProfilingInfo].operands.push(OperandId, "'event'");
    InstructionDesc[OpCaptureEventProfilingInfo].operands.push(OperandKernelProfilingInfo, "'info'");
    InstructionDesc[OpCaptureEventProfilingInfo].operands.push(OperandId, "'value'");

    InstructionDesc[OpSetUserEventStatus].capabilities.push_back(CapKernel);

    InstructionDesc[OpSetUserEventStatus].operands.push(OperandId, "'event'");
    InstructionDesc[OpSetUserEventStatus].operands.push(OperandId, "'status'");

    InstructionDesc[OpIsValidEvent].capabilities.push_back(CapKernel);
    InstructionDesc[OpIsValidEvent].operands.push(OperandId, "'event'");

    InstructionDesc[OpCreateUserEvent].capabilities.push_back(CapKernel);

    InstructionDesc[OpRetainEvent].capabilities.push_back(CapKernel);
    InstructionDesc[OpRetainEvent].operands.push(OperandId, "'event'");

    InstructionDesc[OpReleaseEvent].capabilities.push_back(CapKernel);
    InstructionDesc[OpReleaseEvent].operands.push(OperandId, "'event'");

    InstructionDesc[OpGetKernelWorkGroupSize].capabilities.push_back(CapKernel);
    InstructionDesc[OpGetKernelWorkGroupSize].operands.push(OperandId, "'Invoke'");

    InstructionDesc[OpGetKernelPreferredWorkGroupSizeMultiple].capabilities.push_back(CapKernel);
    InstructionDesc[OpGetKernelPreferredWorkGroupSizeMultiple].operands.push(OperandId, "'Invoke'");

    InstructionDesc[OpGetKernelNDrangeSubGroupCount].capabilities.push_back(CapKernel);
    InstructionDesc[OpGetKernelNDrangeSubGroupCount].operands.push(OperandId, "'ND Range'");
    InstructionDesc[OpGetKernelNDrangeSubGroupCount].operands.push(OperandId, "'Invoke'");

    InstructionDesc[OpGetKernelNDrangeMaxSubGroupSize].capabilities.push_back(CapKernel);
    InstructionDesc[OpGetKernelNDrangeMaxSubGroupSize].operands.push(OperandId, "'ND Range'");
    InstructionDesc[OpGetKernelNDrangeMaxSubGroupSize].operands.push(OperandId, "'Invoke'");

    InstructionDesc[OpEnqueueKernel].capabilities.push_back(CapKernel);
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId, "'q'");
    InstructionDesc[OpEnqueueKernel].operands.push(OperandKernelEnqueueFlags, "'flags'");
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId, "'ND Range'");
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId, "'Num Events'");
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId, "'Wait Events'");
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId, "'Ret Event'");
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId, "'Invoke'");
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId, "'Param'");
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId, "'Param Size'");
    InstructionDesc[OpEnqueueKernel].operands.push(OperandId, "'Param Align'");
    InstructionDesc[OpEnqueueKernel].operands.push(OperandVariableIds, "'Local Size'");

    InstructionDesc[OpEnqueueMarker].capabilities.push_back(CapKernel);
    InstructionDesc[OpEnqueueMarker].operands.push(OperandId, "'q'");
    InstructionDesc[OpEnqueueMarker].operands.push(OperandId, "'Num Events'");
    InstructionDesc[OpEnqueueMarker].operands.push(OperandId, "'Wait Events'");
    InstructionDesc[OpEnqueueMarker].operands.push(OperandId, "'Ret Event'");
}

}; // end spv namespace
