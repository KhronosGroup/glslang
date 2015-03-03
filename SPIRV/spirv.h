/*
** Copyright (c) 2014-2015 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

//
// Enumeration tokens for SPIR V.
//

#pragma once
#ifndef spirv_H
#define spirv_H

#ifdef __cplusplus
namespace spv{
#endif

const int MagicNumber = 0x07230203;
const int Version = 99;

typedef unsigned int Id;

const Id NoResult = 0;
const Id NoType = 0;

const unsigned int OpCodeMask = 0xFFFF;
const unsigned int WordCountShift = 16;

// Set of capabilities.  Generally, something is assumed to be in core,
// if nothing else is said.  So, these are used to identify when something
// requires a specific capability to be declared.
enum Capability {
    CapMatrix,
    CapShader,
    CapGeom,
    CapTess,
    CapAddr,
    CapLink,
    CapKernel
};

// What language is the source code in?  Note the OpSource instruction has a separate
// operand for the version number, this is just the language name.  The GLSL
// compatibility profile will be indicated by using an OpSourceExtension string.
enum SourceLanguage {
    LangUnknown,
    LangESSL,
    LangGLSL,
    LangOpenCL,

    LangCount     // guard for validation, "default:" statements, etc.
};

// Used per entry point to communicate the "stage" or other model of
// execution used by that entry point.
// See OpEntryPoint.
enum ExecutionModel {
    ModelVertex,
    ModelTessellationControl,
    ModelTessellationEvaluation,
    ModelGeometry,
    ModelFragment,
    ModelGLCompute,
    ModelKernel,

    ModelCount    // guard for validation, "default:" statements, etc.
};

// Used as an argument to OpMemoryModel
enum AddressingModel {
    AddressingLogical,
    AddressingPhysical32,
    AddressingPhysical64,

    AddressingCount     // guard for validation, "default:" statements, etc.
};

// Used as an argment to OpMemoryModel
enum MemoryModel {
    MemorySimple,
    MemoryGLSL450,
    MemoryOCL12,
    MemoryOCL20,
    MemoryOCL21,

    MemoryCount         // guard for validation, "default:" statements, etc.
};

// Used per entry point to communicate modes related to input, output, and execution.
// See OpExecutionMode.
enum ExecutionMode {
    ExecutionInvocations,
    ExecutionSpacingEqual,
    ExecutionSpacingFractionalEven,
    ExecutionSpacingFractionalOdd,
    ExecutionVertexOrderCw,
    ExecutionVertexOrderCcw,
    ExecutionPixelCenterInteger,
    ExecutionOriginUpperLeft,
    ExecutionEarlyFragmentTests,
    ExecutionPointMode,
    ExecutionXfb,
    ExecutionDepthReplacing,
    ExecutionDepthAny,
    ExecutionDepthGreater,
    ExecutionDepthLess,
    ExecutionDepthUnchanged,
    ExecutionLocalSize,
    ExecutionLocalSizeHint,

    ExecutionInputPoints,
    ExecutionInputLines,
    ExecutionInputLinesAdjacency,
    ExecutionInputTriangles,
    ExecutionInputTrianglesAdjacency,
    ExecutionInputQuads,
    ExecutionInputIsolines,

    ExecutionOutputVertices,
    ExecutionOutputPoints,
    ExecutionOutputLineStrip,
    ExecutionOutputTriangleStrip,

    ExecutionVecTypeHint,
    ExecutionContractionOff,
    ExecutionModeCount    // guard for validation, "default:" statements, etc.
};

enum StorageClass {
    StorageConstantUniform,
    StorageInput,
    StorageUniform,
    StorageOutput,
    StorageWorkgroupLocal,
    StorageWorkgroupGlobal,
    StoragePrivateGlobal,
    StorageFunction,
    StorageGeneric,
    StoragePrivate,
    StorageAtomicCounter,
    StorageCount            // guard for validation, "default:" statements, etc.
};

// Dimensionalities currently used for sampling.
// See TypeSampler in TypeClass.
enum Dimensionality {
    Dim1D,
    Dim2D,
    Dim3D,
    DimCube,
    DimRect,
    DimBuffer,

    DimCount   // guard for validation, "default:" statements, etc.
};

// Sampler addressing mode.
enum SamplerAddressingMode {
    SamplerAddressingNone           = 0,
    SamplerAddressingClampToEdge    = 2,
    SamplerAddressingClamp          = 4,
    SamplerAddressingRepeat         = 6,
    SamplerAddressingRepeatMirrored = 8,
    SamplerAddressingModeLast,
};

// Sampler filter mode.
enum SamplerFilterMode {
    SamplerFilterNearest = 0x10,
    SamplerFilterLinear  = 0x20,
    SamplerFilterModeLast,
};

// FP Fast Math Mode.
enum FPFastMath {
    FPFastMathNNan =  0,      // assume parameters and result are not NaN.
    FPFastMathNInf =  0x02,   // assume parameters and result are not +/- Inf.
    FPFastMathNSZ  =  0x04,   // treat the sign of a zero parameter or result as insignificant.
    FPFastMathARcp =  0x08,   // allow the usage of reciprocal rather than perform a division.
    FPFastMathFast =  0x10,   // allow Algebraic transformations according to real number associative and distibutive algebra. This flag implies all the others.
    FPFastMathLast,
};

// FP Fast Math Mode.
enum FPRoundingMode {
    FPRoundRTE,    // round to nearest even.
    FPRoundRTZ,    // round towards zero.
    FPRoundRTP,    // round towards positive infinity.
    FPRoundRTN,    // round towards negative infinity.
    FPRoundLast,
};

// Global identifier linkage types (by default the linkage type of global identifiers is private. This means that they are only accessible to objects inside the module.)
enum LinkageType {
    LinkageExport,    // accessible by objects in other modules as well.
    LinkageImport,    // a forward declaration to a global identifier that exists in another module.
    LinkageLast,
};

// Access Qualifiers for OpenCL pipes and images
enum AccessQualifier {
    AccessQualReadOnly,
    AccessQualWriteOnly,
    AccessQualReadWrite,
    AccessQualLast,
};

// Function argument attributes
enum FunctionParameterAttribute {
    FuncParamAttrZext,  // value should be zero extended if needed
    FuncParamAttrSext,  // value should be sign extended if needed
    FuncParamAttrByval, // only valid for pointer parameters (not for ret value), this indicates that the pointer parameter should really be passed by value to the function.
    FuncParamAttrSret,  // indicates that the pointer parameter specifies the address of a structure that is the return value of the function in the source program. only applicable to the first parameter
    FuncParamAttrNoAlias,
    FuncParamAttrNoCapture,
    FuncParamAttrSVM,
    FuncParamAttrNoWrite,
    FuncParamAttrNoReadWrite,
    FuncParamAttrLast,       // guard for validation, "default:" statements, etc.
};


// Extra forms of "qualification" to add as needed.  See OpDecorate.
enum Decoration {
    // For legacy ES precision qualifiers; newer language
    // designs can use the "num-bits" feature in TypeClass.
    // The precision qualifiers may be decorated on type <id>s or instruction <id>s.
    DecPrecisionLow,
    DecPrecisionMedium,
    DecPrecisionHigh,

    DecBlock,            // basic in/out/uniform block, applied only to types of TypeStruct
    DecBufferBlock,      // shader storage buffer block
    DecRowMajor,
    DecColMajor,
    DecGLSLShared,
    DecGLSLStd140,
    DecGLSLStd430,
    DecGLSLPacked,
    DecSmooth,
    DecNoperspective,
    DecFlat,
    DecPatch,
    DecCentroid,
    DecSample,
    DecInvariant,
    DecRestrict,
    DecAliased,
    DecVolatile,
    DecConstant,
    DecCoherent,
    DecNonwritable,
    DecNonreadable,
    DecUniform,
    DecNoStaticUse,

    DecCPacked,
    DecFPSaturatedConv,

    // these all take one additional operand
    DecStream,
    DecLocation,
    DecComponent,
    DecIndex,
    DecBinding,
    DecDescriptorSet,
    DecOffset,
    DecAlignment,
    DecXfbBuffer,
    DecStride,
    DecBuiltIn,
    DecFuncParamAttr,
    DecFPRoundingMode,
    DecFPFastMathMode,
    DecLinkageType,
    DecSpecId,

    DecCount             // guard for validation, "default:" statements, etc.
};

enum BuiltIn {
    BuiltInPosition,
    BuiltInPointSize,
    BuiltInClipVertex,
    BuiltInClipDistance,
    BuiltInCullDistance,
    BuiltInVertexId,
    BuiltInInstanceId,
    BuiltInPrimitiveId,
    BuiltInInvocationId,
    BuiltInLayer,
    BuiltInViewportIndex,
    BuiltInTessLevelOuter,
    BuiltInTessLevelInner,
    BuiltInTessCoord,
    BuiltInPatchVertices,
    BuiltInFragCoord,
    BuiltInPointCoord,
    BuiltInFrontFacing,
    BuiltInSampleId,
    BuiltInSamplePosition,
    BuiltInSampleMask,
    BuiltInFragColor,
    BuiltInFragDepth,
    BuiltInHelperInvocation,

    // OpenGL compute stage, OpenCL work item built-ins
    BuiltInNumWorkgroups,       // number of work-groups that will execute a kernel
    BuiltInWorkgroupSize,      // OpenCL number of local work-items
    BuiltInWorkgroupId,        // OpenCL work group id
    BuiltInLocalInvocationId,  // OpenCL local work item id (decorates a vector3 i32/i64)
    BuiltInGlobalInvocationId, // OpenCL global work item id (decorates a vector3 i32/i64)
    BuiltInLocalInvocationIndex, // not in use in OpenCL
    BuiltInWorkDim, // OpenCL number of dimensions in use (decorates a scalar i32/i64)
    BuiltInGlobalSize, // OpenCL number of global work items, per dimension (decorates a vector3 i32/i64)
    BuiltInEnqueuedWorkgroupSize,      // OpenCL 2.0 only, get local size
    BuiltInGlobalOffset, // OpenCL offset values specified global_work_offset 
    BuiltInGlobalLinearId, // OpenCL 2.0 only, work items 1-dimensional global ID.
    BuiltInWorkgroupLinearId, // OpenCL 2.0 only work items 1-dimensional local ID.

    // OpenCL 2.0 subgroups
    BuiltInSubgroupSize, // Returns the number of work-items in the subgroup
    BuiltInSubgroupMaxSize, // Returns the maximum size of a subgroup within the dispatch
    BuiltInNumSubgroups, // Returns the maximum size of a subgroup within the dispatch
    BuiltInNumEnqueuedSubgroups, // Returns the maximum size of a subgroup within the dispatch
    BuiltInSubgroupId, // 
    BuiltInSubgroupLocalInvocationId, // Returns the unique work-item ID within the current subgroup

    BuiltInCount   // guard for validation, "default:" statements, etc.
};

enum SelectControl {
    SelectControlNone,
    SelectControlFlatten,
    SelectControlDontFlatten,

    SelectControlCount,       // guard for validation, "default:" statements, etc.
};

enum LoopControl {
    LoopControlNone,
    LoopControlUnroll,
    LoopControlDontUnroll,

    LoopControlCount,
};

enum FunctionControlMask {
    FunctionControlNone       = 0x0,
    FunctionControlInline     = 0x1,
    FunctionControlDontInline = 0x2,
    FunctionControlPure       = 0x4, 
    FunctionControlConst      = 0x8,

    FunctionControlCount      = 4,
};

enum MemorySemanticsMask {
    MemorySemanticsRelaxed                = 0x0001,
    MemorySemanticsSequentiallyConsistent = 0x0002,
    MemorySemanticsAcquire                = 0x0004,
    MemorySemanticsRelease                = 0x0008,

    MemorySemanticsUniform                = 0x0010,
    MemorySemanticsSubgroup               = 0x0020,
    MemorySemanticsWorkgroupLocal         = 0x0040,
    MemorySemanticsWorkgroupGlobal        = 0x0080,
    MemorySemanticsAtomicCounter          = 0x0100,
    MemorySemanticsImage                  = 0x0200,
    MemorySemanticsAllMemory              = 0x03FF,

    MemorySemanticsCount                  = 10
};

enum MemoryAccessMask {
    MemoryAccessVolatile                  = 0x0001,
    MemoryAccessAligned                   = 0x0002,

    MemoryAccessCount                     = 2
};

enum ExecutionScope {
    ExecutionScopeCrossDevice,
    ExecutionScopeDevice,
    ExecutionScopeWorkgroup,
    ExecutionScopeSubgroup,

    ExecutionScopeCount     // guard for validation, "default:" statements, etc.
};

enum GroupOperation {
    GroupOpReduce,
    GroupOpInclusiveScan,
    GroupOpExclusiveScan,

    GroupOpCount
};

enum KernelEnqueueFlags {
    EnqFlagNoWait,
    EnqFlagWaitKernel,
    EnqFlagWaitWaitWorgGroup,

    EnqFlagCount
};

enum KernelProfilingInfo {
    ProfInfoCmdExecTime = 0x01,
    ProfilingInfoCount = 1
};

enum OpCode {
    OpNop = 0,         // Not used.

    OpSource,
    OpSourceExtension,
    OpExtension,
    OpExtInstImport,

    OpMemoryModel,
    OpEntryPoint,
    OpExecutionMode,

    OpTypeVoid,
    OpTypeBool,
    OpTypeInt,
    OpTypeFloat,
    OpTypeVector,
    OpTypeMatrix,
    OpTypeSampler,
    OpTypeFilter,
    OpTypeArray,
    OpTypeRuntimeArray,
    OpTypeStruct,
    OpTypeOpaque,
    OpTypePointer,
    OpTypeFunction,
    OpTypeEvent,
    OpTypeDeviceEvent,
    OpTypeReserveId,
    OpTypeQueue,
    OpTypePipe,

    OpConstantTrue,
    OpConstantFalse,
    OpConstant,
    OpConstantComposite,
    OpConstantSampler,
    OpConstantNullPointer,
    OpConstantNullObject,

    OpSpecConstantTrue,
    OpSpecConstantFalse,
    OpSpecConstant,
    OpSpecConstantComposite,

    OpVariable,
    OpVariableArray,

    OpFunction,
    OpFunctionParameter,
    OpFunctionEnd,
    OpFunctionCall,

    OpExtInst,

    OpUndef,

    OpLoad,
    OpStore,

    OpPhi,

    OpDecorationGroup,
    OpDecorate,
    OpMemberDecorate,
    OpGroupDecorate,
    OpGroupMemberDecorate,

    OpName,
    OpMemberName,
    OpString,
    OpLine,

    OpVectorExtractDynamic,
    OpVectorInsertDynamic,
    OpVectorShuffle,
    
    OpCompositeConstruct,
    OpCompositeExtract,
    OpCompositeInsert,

    OpCopyObject,
    OpCopyMemory,
    OpCopyMemorySized,

    OpSampler,

    OpTextureSample,
    OpTextureSampleDref,
    OpTextureSampleLod,
    OpTextureSampleProj,
    OpTextureSampleGrad,
    OpTextureSampleOffset,
    OpTextureSampleProjLod,
    OpTextureSampleProjGrad,
    OpTextureSampleLodOffset,
    OpTextureSampleProjOffset,
    OpTextureSampleGradOffset,
    OpTextureSampleProjLodOffset,
    OpTextureSampleProjGradOffset,

    OpTextureFetchTexel,
    OpTextureFetchTexelOffset,
    OpTextureFetchSample,
    OpTextureFetchBuffer,
    OpTextureGather,
    OpTextureGatherOffset,
    OpTextureGatherOffsets,

    OpTextureQuerySizeLod,
    OpTextureQuerySize,
    OpTextureQueryLod,
    OpTextureQueryLevels,
    OpTextureQuerySamples,

    OpAccessChain,
    OpInBoundsAccessChain,

    OpSNegate,
    OpFNegate,

    OpNot,

    OpAny,
    OpAll,

    OpConvertFToU,
    OpConvertFToS,
    OpConvertSToF,
    OpConvertUToF,
    OpUConvert,
    OpSConvert,
    OpFConvert,
    OpConvertPtrToU,
    OpConvertUToPtr,
    OpPtrCastToGeneric,   // cast a pointer storage class to be in storage generic
    OpGenericCastToPtr,   // cast a pointer in the generic storage class generic to another storage class
    OpBitcast,

    OpTranspose,

    OpIsNan,
    OpIsInf,
    OpIsFinite,
    OpIsNormal,
    OpSignBitSet,
    OpLessOrGreater,
    OpOrdered,
    OpUnordered,

    OpArrayLength,

    OpIAdd,
    OpFAdd,
    OpISub,
    OpFSub,
    OpIMul,
    OpFMul,
    OpUDiv,
    OpSDiv,
    OpFDiv,

    OpUMod,
    OpSRem,
    OpSMod,
    OpFRem,
    OpFMod,

    OpVectorTimesScalar,
    OpMatrixTimesScalar,
    OpVectorTimesMatrix,
    OpMatrixTimesVector,
    OpMatrixTimesMatrix,
    OpOuterProduct,

    OpDot,

    OpShiftRightLogical,
    OpShiftRightArithmetic,
    OpShiftLeftLogical,
    OpLogicalOr,
    OpLogicalXor,
    OpLogicalAnd,
    
    OpBitwiseOr,
    OpBitwiseXor,
    OpBitwiseAnd,
    
    OpSelect,

    OpIEqual,
    OpFOrdEqual,
    OpFUnordEqual,

    OpINotEqual,
    OpFOrdNotEqual,
    OpFUnordNotEqual,

    OpULessThan,
    OpSLessThan,
    OpFOrdLessThan,
    OpFUnordLessThan,

    OpUGreaterThan,
    OpSGreaterThan,
    OpFOrdGreaterThan,
    OpFUnordGreaterThan,

    OpULessThanEqual,
    OpSLessThanEqual,
    OpFOrdLessThanEqual,
    OpFUnordLessThanEqual,

    OpUGreaterThanEqual,
    OpSGreaterThanEqual,
    OpFOrdGreaterThanEqual,
    OpFUnordGreaterThanEqual,

    OpDPdx,
    OpDPdy,
    OpFwidth,
    OpDPdxFine,
    OpDPdyFine,
    OpFwidthFine,
    OpDPdxCoarse,
    OpDPdyCoarse,
    OpFwidthCoarse,

    OpEmitVertex,
    OpEndPrimitive,
    OpEmitStreamVertex,
    OpEndStreamPrimitive,

    OpControlBarrier,
    OpMemoryBarrier,

    OpImagePointer,

    OpAtomicInit,
    OpAtomicLoad,
    OpAtomicStore,
    OpAtomicExchange,
    OpAtomicCompareExchange,
    OpAtomicCompareExchangeWeak,
    OpAtomicIIncrement,
    OpAtomicIDecrement,
    OpAtomicIAdd,
    OpAtomicISub,
    OpAtomicUMin,
    OpAtomicUMax,
    OpAtomicAnd,
    OpAtomicOr,
    OpAtomicXor,

    OpLoopMerge,
    OpSelectionMerge,
    OpLabel,
    OpBranch,
    OpBranchConditional,
    OpSwitch,
    OpKill,
    OpReturn,
    OpReturnValue,

    OpUnreachable,

    OpLifetimeStart,
    OpLifetimeStop,

    OpCompileFlag,
    
    OpAsyncGroupCopy,
    OpWaitGroupEvents,	

    OpGroupAll,
    OpGroupAny,
    OpGroupBroadcast,
    
    OpGroupIAdd,
    OpGroupFAdd,
    OpGroupFMin,
    OpGroupUMin,
    OpGroupSMin,
    OpGroupFMax,
    OpGroupUMax,
    OpGroupSMax,

    OpGenericCastToPtrExplicit,
    OpGenericPtrMemSemantics,

    OpReadPipe,
    OpWritePipe,
    OpReservedReadPipe,
    OpReservedWritePipe,
    OpReserveReadPipePackets,
    OpReserveWritePipePackets,
    OpCommitReadPipe,
    OpCommitWritePipe,
    OpIsValidReserveId,
    OpGetNumPipePackets,
    OpGetMaxPipePackets,
    OpGroupReserveReadPipePackets,
    OpGroupReserveWritePipePackets,
    OpGroupCommitReadPipe,
    OpGroupCommitWritePipe,    

    OpEnqueueMarker,
    OpEnqueueKernel,
    OpGetKernelNDrangeSubGroupCount,
    OpGetKernelNDrangeMaxSubGroupSize,

    OpGetKernelWorkGroupSize,
    OpGetKernelPreferredWorkGroupSizeMultiple,

    OpRetainEvent,
    OpReleaseEvent,

    OpCreateUserEvent,
    OpIsValidEvent,
    OpSetUserEventStatus,
    OpCaptureEventProfilingInfo,
    OpGetDefaultQueue,
    
    OpBuildNDRange,

    OpCount              // guard for validation, "default:" statements, etc.
};

#ifdef __cplusplus
};  // end namespace spv
#endif

#endif // spirv_H
