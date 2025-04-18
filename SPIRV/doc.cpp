//
// Copyright (C) 2014-2015 LunarG, Inc.
// Copyright (C) 2022-2025 Arm Limited.
// Modifications Copyright (C) 2020 Advanced Micro Devices, Inc. All rights reserved.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
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
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

//
// 1) Programmatically fill in instruction/operand information.
//    This can be used for disassembly, printing documentation, etc.
//
// 2) Print documentation from this parameterization.
//

#include "doc.h"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <mutex>

namespace spv {
    extern "C" {
        // Include C-based headers that don't have a namespace
        #include "GLSL.ext.KHR.h"
        #include "GLSL.ext.EXT.h"
        #include "GLSL.ext.AMD.h"
        #include "GLSL.ext.NV.h"
        #include "GLSL.ext.ARM.h"
        #include "GLSL.ext.QCOM.h"
    }
}

namespace spv {

//
// Whole set of functions that translate enumerants to their text strings for
// the specification (or their sanitized versions for auto-generating the
// spirv headers.
//
// Also, for masks the ceilings are declared next to these, to help keep them in sync.
// Ceilings should be
//  - one more than the maximum value an enumerant takes on, for non-mask enumerants
//    (for non-sparse enums, this is the number of enumerants)
//  - the number of bits consumed by the set of masks
//    (for non-sparse mask enums, this is the number of enumerants)
//

const char* SourceString(int source)
{
    switch (source) {
    case 0:  return "Unknown";
    case 1:  return "ESSL";
    case 2:  return "GLSL";
    case 3:  return "OpenCL_C";
    case 4:  return "OpenCL_CPP";
    case 5:  return "HLSL";

    default: return "Bad";
    }
}

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
    case ExecutionModel::TaskNV: return "TaskNV";
    case ExecutionModel::MeshNV: return "MeshNV";
    case ExecutionModel::TaskEXT: return "TaskEXT";
    case ExecutionModel::MeshEXT: return "MeshEXT";

    default: return "Bad";

    case ExecutionModel::RayGenerationKHR: return "RayGenerationKHR";
    case ExecutionModel::IntersectionKHR:  return "IntersectionKHR";
    case ExecutionModel::AnyHitKHR:        return "AnyHitKHR";
    case ExecutionModel::ClosestHitKHR:    return "ClosestHitKHR";
    case ExecutionModel::MissKHR:          return "MissKHR";
    case ExecutionModel::CallableKHR:      return "CallableKHR";
    }
}

const char* AddressingString(int addr)
{
    switch (addr) {
    case 0:  return "Logical";
    case 1:  return "Physical32";
    case 2:  return "Physical64";

    case AddressingModel::PhysicalStorageBuffer64EXT: return "PhysicalStorageBuffer64EXT";

    default: return "Bad";
    }
}

const char* MemoryString(int mem)
{
    switch (mem) {
    case MemoryModel::Simple:     return "Simple";
    case MemoryModel::GLSL450:    return "GLSL450";
    case MemoryModel::OpenCL:
        return "OpenCL";
    case MemoryModel::VulkanKHR:
        return "VulkanKHR";

    default: return "Bad";
    }
}

const int ExecutionModeCeiling = 40;

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
    case 8:  return "OriginLowerLeft";
    case 9:  return "EarlyFragmentTests";
    case 10: return "PointMode";
    case 11: return "Xfb";
    case 12: return "DepthReplacing";
    case 13: return "Bad";
    case 14: return "DepthGreater";
    case 15: return "DepthLess";
    case 16: return "DepthUnchanged";
    case 17: return "LocalSize";
    case 18: return "LocalSizeHint";
    case 19: return "InputPoints";
    case 20: return "InputLines";
    case 21: return "InputLinesAdjacency";
    case 22: return "Triangles";
    case 23: return "InputTrianglesAdjacency";
    case 24: return "Quads";
    case 25: return "Isolines";
    case 26: return "OutputVertices";
    case 27: return "OutputPoints";
    case 28: return "OutputLineStrip";
    case 29: return "OutputTriangleStrip";
    case 30: return "VecTypeHint";
    case 31: return "ContractionOff";
    case 32: return "Bad";

    case ExecutionMode::Initializer:                   return "Initializer";
    case ExecutionMode::Finalizer:                     return "Finalizer";
    case ExecutionMode::SubgroupSize:                  return "SubgroupSize";
    case ExecutionMode::SubgroupsPerWorkgroup:         return "SubgroupsPerWorkgroup";
    case ExecutionMode::SubgroupsPerWorkgroupId:       return "SubgroupsPerWorkgroupId";
    case ExecutionMode::LocalSizeId:                   return "LocalSizeId";
    case ExecutionMode::LocalSizeHintId:               return "LocalSizeHintId";

    case ExecutionMode::PostDepthCoverage:             return "PostDepthCoverage";
    case ExecutionMode::DenormPreserve:                return "DenormPreserve";
    case ExecutionMode::DenormFlushToZero:             return "DenormFlushToZero";
    case ExecutionMode::SignedZeroInfNanPreserve:      return "SignedZeroInfNanPreserve";
    case ExecutionMode::RoundingModeRTE:               return "RoundingModeRTE";
    case ExecutionMode::RoundingModeRTZ:               return "RoundingModeRTZ";
    case ExecutionMode::EarlyAndLateFragmentTestsAMD:  return "EarlyAndLateFragmentTestsAMD";
    case ExecutionMode::StencilRefUnchangedFrontAMD:   return "StencilRefUnchangedFrontAMD";
    case ExecutionMode::StencilRefLessFrontAMD:        return "StencilRefLessFrontAMD";
    case ExecutionMode::StencilRefGreaterBackAMD:      return "StencilRefGreaterBackAMD";
    case ExecutionMode::StencilRefReplacingEXT:        return "StencilRefReplacingEXT";
    case ExecutionMode::SubgroupUniformControlFlowKHR: return "SubgroupUniformControlFlow";
    case ExecutionMode::MaximallyReconvergesKHR:       return "MaximallyReconverges";

    case ExecutionMode::OutputLinesNV:                 return "OutputLinesNV";
    case ExecutionMode::OutputPrimitivesNV:            return "OutputPrimitivesNV";
    case ExecutionMode::OutputTrianglesNV:             return "OutputTrianglesNV";
    case ExecutionMode::DerivativeGroupQuadsNV:        return "DerivativeGroupQuadsNV";
    case ExecutionMode::DerivativeGroupLinearNV:       return "DerivativeGroupLinearNV";

    case ExecutionMode::PixelInterlockOrderedEXT:         return "PixelInterlockOrderedEXT";
    case ExecutionMode::PixelInterlockUnorderedEXT:       return "PixelInterlockUnorderedEXT";
    case ExecutionMode::SampleInterlockOrderedEXT:        return "SampleInterlockOrderedEXT";
    case ExecutionMode::SampleInterlockUnorderedEXT:      return "SampleInterlockUnorderedEXT";
    case ExecutionMode::ShadingRateInterlockOrderedEXT:   return "ShadingRateInterlockOrderedEXT";
    case ExecutionMode::ShadingRateInterlockUnorderedEXT: return "ShadingRateInterlockUnorderedEXT";

    case ExecutionMode::MaxWorkgroupSizeINTEL:    return "MaxWorkgroupSizeINTEL";
    case ExecutionMode::MaxWorkDimINTEL:          return "MaxWorkDimINTEL";
    case ExecutionMode::NoGlobalOffsetINTEL:      return "NoGlobalOffsetINTEL";
    case ExecutionMode::NumSIMDWorkitemsINTEL:    return "NumSIMDWorkitemsINTEL";

    case ExecutionMode::RequireFullQuadsKHR:      return "RequireFullQuadsKHR";
    case ExecutionMode::QuadDerivativesKHR:       return "QuadDerivativesKHR";

    case ExecutionMode::NonCoherentColorAttachmentReadEXT:        return "NonCoherentColorAttachmentReadEXT";
    case ExecutionMode::NonCoherentDepthAttachmentReadEXT:        return "NonCoherentDepthAttachmentReadEXT";
    case ExecutionMode::NonCoherentStencilAttachmentReadEXT:      return "NonCoherentStencilAttachmentReadEXT";

    case ExecutionModeCeiling:
    default: return "Bad";
    }
}

const char* StorageClassString(int StorageClass)
{
    switch (StorageClass) {
    case 0:  return "UniformConstant";
    case 1:  return "Input";
    case 2:  return "Uniform";
    case 3:  return "Output";
    case 4:  return "Workgroup";
    case 5:  return "CrossWorkgroup";
    case 6:  return "Private";
    case 7:  return "Function";
    case 8:  return "Generic";
    case 9:  return "PushConstant";
    case 10: return "AtomicCounter";
    case 11: return "Image";
    case 12: return "StorageBuffer";

    case StorageClass::RayPayloadKHR:            return "RayPayloadKHR";
    case StorageClass::HitAttributeKHR:          return "HitAttributeKHR";
    case StorageClass::IncomingRayPayloadKHR:    return "IncomingRayPayloadKHR";
    case StorageClass::ShaderRecordBufferKHR:    return "ShaderRecordBufferKHR";
    case StorageClass::CallableDataKHR:          return "CallableDataKHR";
    case StorageClass::IncomingCallableDataKHR:  return "IncomingCallableDataKHR";

    case StorageClass::PhysicalStorageBufferEXT: return "PhysicalStorageBufferEXT";
    case StorageClass::TaskPayloadWorkgroupEXT:  return "TaskPayloadWorkgroupEXT";
    case StorageClass::HitObjectAttributeNV:     return "HitObjectAttributeNV";
    case StorageClass::TileImageEXT:             return "TileImageEXT";
    default: return "Bad";
    }
}

const int DecorationCeiling = 45;

const char* DecorationString(int decoration)
{
    switch (decoration) {
    case 0:  return "RelaxedPrecision";
    case 1:  return "SpecId";
    case 2:  return "Block";
    case 3:  return "BufferBlock";
    case 4:  return "RowMajor";
    case 5:  return "ColMajor";
    case 6:  return "ArrayStride";
    case 7:  return "MatrixStride";
    case 8:  return "GLSLShared";
    case 9:  return "GLSLPacked";
    case 10: return "CPacked";
    case 11: return "BuiltIn";
    case 12: return "Bad";
    case 13: return "NoPerspective";
    case 14: return "Flat";
    case 15: return "Patch";
    case 16: return "Centroid";
    case 17: return "Sample";
    case 18: return "Invariant";
    case 19: return "Restrict";
    case 20: return "Aliased";
    case 21: return "Volatile";
    case 22: return "Constant";
    case 23: return "Coherent";
    case 24: return "NonWritable";
    case 25: return "NonReadable";
    case 26: return "Uniform";
    case 27: return "Bad";
    case 28: return "SaturatedConversion";
    case 29: return "Stream";
    case 30: return "Location";
    case 31: return "Component";
    case 32: return "Index";
    case 33: return "Binding";
    case 34: return "DescriptorSet";
    case 35: return "Offset";
    case 36: return "XfbBuffer";
    case 37: return "XfbStride";
    case 38: return "FuncParamAttr";
    case 39: return "FP Rounding Mode";
    case 40: return "FP Fast Math Mode";
    case 41: return "Linkage Attributes";
    case 42: return "NoContraction";
    case 43: return "InputAttachmentIndex";
    case 44: return "Alignment";

    case DecorationCeiling:
    default:  return "Bad";

    case Decoration::WeightTextureQCOM:           return "DecorationWeightTextureQCOM";
    case Decoration::BlockMatchTextureQCOM:       return "DecorationBlockMatchTextureQCOM";
    case Decoration::BlockMatchSamplerQCOM:       return "DecorationBlockMatchSamplerQCOM";
    case Decoration::ExplicitInterpAMD:           return "ExplicitInterpAMD";
    case Decoration::OverrideCoverageNV:          return "OverrideCoverageNV";
    case Decoration::PassthroughNV:               return "PassthroughNV";
    case Decoration::ViewportRelativeNV:          return "ViewportRelativeNV";
    case Decoration::SecondaryViewportRelativeNV: return "SecondaryViewportRelativeNV";
    case Decoration::PerPrimitiveNV:              return "PerPrimitiveNV";
    case Decoration::PerViewNV:                   return "PerViewNV";
    case Decoration::PerTaskNV:                   return "PerTaskNV";

    case Decoration::PerVertexKHR:                return "PerVertexKHR";

    case Decoration::NonUniformEXT:           return "DecorationNonUniformEXT";
    case Decoration::HlslCounterBufferGOOGLE: return "DecorationHlslCounterBufferGOOGLE";
    case Decoration::HlslSemanticGOOGLE:      return "DecorationHlslSemanticGOOGLE";
    case Decoration::RestrictPointerEXT:      return "DecorationRestrictPointerEXT";
    case Decoration::AliasedPointerEXT:       return "DecorationAliasedPointerEXT";

    case Decoration::HitObjectShaderRecordBufferNV:  return "DecorationHitObjectShaderRecordBufferNV";
    }
}

const char* BuiltInString(int builtIn)
{
    switch (builtIn) {
    case 0:  return "Position";
    case 1:  return "PointSize";
    case 2:  return "Bad";
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
    case 21: return "Bad";
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
    case 35: return "Bad";
    case 36: return "SubgroupSize";
    case 37: return "SubgroupMaxSize";
    case 38: return "NumSubgroups";
    case 39: return "NumEnqueuedSubgroups";
    case 40: return "SubgroupId";
    case 41: return "SubgroupLocalInvocationId";
    case 42: return "VertexIndex";                 // TBD: put next to VertexId?
    case 43: return "InstanceIndex";               // TBD: put next to InstanceId?

    case 4416: return "SubgroupEqMaskKHR";
    case 4417: return "SubgroupGeMaskKHR";
    case 4418: return "SubgroupGtMaskKHR";
    case 4419: return "SubgroupLeMaskKHR";
    case 4420: return "SubgroupLtMaskKHR";
    case 4438: return "DeviceIndex";
    case 4440: return "ViewIndex";
    case 4424: return "BaseVertex";
    case 4425: return "BaseInstance";
    case 4426: return "DrawIndex";
    case 4432: return "PrimitiveShadingRateKHR";
    case 4444: return "ShadingRateKHR";
    case 5014: return "FragStencilRefEXT";

    case 4992: return "BaryCoordNoPerspAMD";
    case 4993: return "BaryCoordNoPerspCentroidAMD";
    case 4994: return "BaryCoordNoPerspSampleAMD";
    case 4995: return "BaryCoordSmoothAMD";
    case 4996: return "BaryCoordSmoothCentroidAMD";
    case 4997: return "BaryCoordSmoothSampleAMD";
    case 4998: return "BaryCoordPullModelAMD";
    case BuiltIn::LaunchIdKHR:                 return "LaunchIdKHR";
    case BuiltIn::LaunchSizeKHR:               return "LaunchSizeKHR";
    case BuiltIn::WorldRayOriginKHR:           return "WorldRayOriginKHR";
    case BuiltIn::WorldRayDirectionKHR:        return "WorldRayDirectionKHR";
    case BuiltIn::ObjectRayOriginKHR:          return "ObjectRayOriginKHR";
    case BuiltIn::ObjectRayDirectionKHR:       return "ObjectRayDirectionKHR";
    case BuiltIn::RayTminKHR:                  return "RayTminKHR";
    case BuiltIn::RayTmaxKHR:                  return "RayTmaxKHR";
    case BuiltIn::CullMaskKHR:                 return "CullMaskKHR";
    case BuiltIn::HitTriangleVertexPositionsKHR: return "HitTriangleVertexPositionsKHR";
    case BuiltIn::HitMicroTriangleVertexPositionsNV: return "HitMicroTriangleVertexPositionsNV";
    case BuiltIn::HitMicroTriangleVertexBarycentricsNV: return "HitMicroTriangleVertexBarycentricsNV";
    case BuiltIn::HitKindFrontFacingMicroTriangleNV: return "HitKindFrontFacingMicroTriangleNV";
    case BuiltIn::HitKindBackFacingMicroTriangleNV: return "HitKindBackFacingMicroTriangleNV";
    case BuiltIn::HitIsSphereNV:               return "HitIsSphereNV";
    case BuiltIn::HitIsLSSNV:                  return "HitIsLSSNV";
    case BuiltIn::HitSpherePositionNV:         return "HitSpherePositionNV";
    case BuiltIn::HitSphereRadiusNV:           return "HitSphereRadiusNV";
    case BuiltIn::HitLSSPositionsNV:           return "HitLSSPositionsNV";
    case BuiltIn::HitLSSRadiiNV:               return "HitLLSSRadiiNV";
    case BuiltIn::InstanceCustomIndexKHR:      return "InstanceCustomIndexKHR";
    case BuiltIn::RayGeometryIndexKHR:         return "RayGeometryIndexKHR";
    case BuiltIn::ObjectToWorldKHR:            return "ObjectToWorldKHR";
    case BuiltIn::WorldToObjectKHR:            return "WorldToObjectKHR";
    case BuiltIn::HitTNV:                      return "HitTNV";
    case BuiltIn::HitKindKHR:                  return "HitKindKHR";
    case BuiltIn::IncomingRayFlagsKHR:         return "IncomingRayFlagsKHR";
    case BuiltIn::ViewportMaskNV:              return "ViewportMaskNV";
    case BuiltIn::SecondaryPositionNV:         return "SecondaryPositionNV";
    case BuiltIn::SecondaryViewportMaskNV:     return "SecondaryViewportMaskNV";
    case BuiltIn::PositionPerViewNV:           return "PositionPerViewNV";
    case BuiltIn::ViewportMaskPerViewNV:       return "ViewportMaskPerViewNV";
//    case BuiltIn::FragmentSizeNV:             return "FragmentSizeNV";        // superseded by BuiltInFragSizeEXT
//    case BuiltIn::InvocationsPerPixelNV:      return "InvocationsPerPixelNV"; // superseded by BuiltInFragInvocationCountEXT
    case BuiltIn::BaryCoordKHR:                return "BaryCoordKHR";
    case BuiltIn::BaryCoordNoPerspKHR:         return "BaryCoordNoPerspKHR";
    case BuiltIn::ClusterIDNV:                 return "ClusterIDNV";

    case BuiltIn::FragSizeEXT:                 return "FragSizeEXT";
    case BuiltIn::FragInvocationCountEXT:      return "FragInvocationCountEXT";

    case 5264: return "FullyCoveredEXT";

    case BuiltIn::TaskCountNV:           return "TaskCountNV";
    case BuiltIn::PrimitiveCountNV:      return "PrimitiveCountNV";
    case BuiltIn::PrimitiveIndicesNV:    return "PrimitiveIndicesNV";
    case BuiltIn::ClipDistancePerViewNV: return "ClipDistancePerViewNV";
    case BuiltIn::CullDistancePerViewNV: return "CullDistancePerViewNV";
    case BuiltIn::LayerPerViewNV:        return "LayerPerViewNV";
    case BuiltIn::MeshViewCountNV:       return "MeshViewCountNV";
    case BuiltIn::MeshViewIndicesNV:     return "MeshViewIndicesNV";
    case BuiltIn::WarpsPerSMNV:           return "WarpsPerSMNV";
    case BuiltIn::SMCountNV:              return "SMCountNV";
    case BuiltIn::WarpIDNV:               return "WarpIDNV";
    case BuiltIn::SMIDNV:                 return "SMIDNV";
    case BuiltIn::CurrentRayTimeNV:       return "CurrentRayTimeNV";
    case BuiltIn::PrimitivePointIndicesEXT:        return "PrimitivePointIndicesEXT";
    case BuiltIn::PrimitiveLineIndicesEXT:         return "PrimitiveLineIndicesEXT";
    case BuiltIn::PrimitiveTriangleIndicesEXT:     return "PrimitiveTriangleIndicesEXT";
    case BuiltIn::CullPrimitiveEXT:                return "CullPrimitiveEXT";
    case BuiltIn::CoreCountARM:           return "CoreCountARM";
    case BuiltIn::CoreIDARM:              return "CoreIDARM";
    case BuiltIn::CoreMaxIDARM:           return "CoreMaxIDARM";
    case BuiltIn::WarpIDARM:              return "WarpIDARM";
    case BuiltIn::WarpMaxIDARM:           return "BuiltInWarpMaxIDARM";

    default: return "Bad";
    }
}

const char* DimensionString(int dim)
{
    switch (dim) {
    case 0:  return "1D";
    case 1:  return "2D";
    case 2:  return "3D";
    case 3:  return "Cube";
    case 4:  return "Rect";
    case 5:  return "Buffer";
    case 6:  return "SubpassData";
    case Dim::TileImageDataEXT:  return "TileImageDataEXT";

    default: return "Bad";
    }
}

const char* SamplerAddressingModeString(int mode)
{
    switch (mode) {
    case 0:  return "None";
    case 1:  return "ClampToEdge";
    case 2:  return "Clamp";
    case 3:  return "Repeat";
    case 4:  return "RepeatMirrored";

    default: return "Bad";
    }
}

const char* SamplerFilterModeString(int mode)
{
    switch (mode) {
    case 0: return "Nearest";
    case 1: return "Linear";

    default: return "Bad";
    }
}

const char* ImageFormatString(int format)
{
    switch (format) {
    case  0: return "Unknown";

    // ES/Desktop float
    case  1: return "Rgba32f";
    case  2: return "Rgba16f";
    case  3: return "R32f";
    case  4: return "Rgba8";
    case  5: return "Rgba8Snorm";

    // Desktop float
    case  6: return "Rg32f";
    case  7: return "Rg16f";
    case  8: return "R11fG11fB10f";
    case  9: return "R16f";
    case 10: return "Rgba16";
    case 11: return "Rgb10A2";
    case 12: return "Rg16";
    case 13: return "Rg8";
    case 14: return "R16";
    case 15: return "R8";
    case 16: return "Rgba16Snorm";
    case 17: return "Rg16Snorm";
    case 18: return "Rg8Snorm";
    case 19: return "R16Snorm";
    case 20: return "R8Snorm";

    // ES/Desktop int
    case 21: return "Rgba32i";
    case 22: return "Rgba16i";
    case 23: return "Rgba8i";
    case 24: return "R32i";

    // Desktop int
    case 25: return "Rg32i";
    case 26: return "Rg16i";
    case 27: return "Rg8i";
    case 28: return "R16i";
    case 29: return "R8i";

    // ES/Desktop uint
    case 30: return "Rgba32ui";
    case 31: return "Rgba16ui";
    case 32: return "Rgba8ui";
    case 33: return "R32ui";

    // Desktop uint
    case 34: return "Rgb10a2ui";
    case 35: return "Rg32ui";
    case 36: return "Rg16ui";
    case 37: return "Rg8ui";
    case 38: return "R16ui";
    case 39: return "R8ui";
    case 40: return "R64ui";
    case 41: return "R64i";

    default:
        return "Bad";
    }
}

const char* ImageChannelOrderString(int format)
{
    switch (format) {
    case 0:  return "R";
    case 1:  return "A";
    case 2:  return "RG";
    case 3:  return "RA";
    case 4:  return "RGB";
    case 5:  return "RGBA";
    case 6:  return "BGRA";
    case 7:  return "ARGB";
    case 8:  return "Intensity";
    case 9:  return "Luminance";
    case 10: return "Rx";
    case 11: return "RGx";
    case 12: return "RGBx";
    case 13: return "Depth";
    case 14: return "DepthStencil";
    case 15: return "sRGB";
    case 16: return "sRGBx";
    case 17: return "sRGBA";
    case 18: return "sBGRA";

    default:
        return "Bad";
    }
}

const char* ImageChannelDataTypeString(int type)
{
    switch (type)
    {
    case 0: return "SnormInt8";
    case 1: return "SnormInt16";
    case 2: return "UnormInt8";
    case 3: return "UnormInt16";
    case 4: return "UnormShort565";
    case 5: return "UnormShort555";
    case 6: return "UnormInt101010";
    case 7: return "SignedInt8";
    case 8: return "SignedInt16";
    case 9: return "SignedInt32";
    case 10: return "UnsignedInt8";
    case 11: return "UnsignedInt16";
    case 12: return "UnsignedInt32";
    case 13: return "HalfFloat";
    case 14: return "Float";
    case 15: return "UnormInt24";
    case 16: return "UnormInt101010_2";

    default:
        return "Bad";
    }
}

const int ImageOperandsCeiling = 15;

const char* ImageOperandsString(int format)
{
    switch (format) {
    case ImageOperandsShift::Bias:                    return "Bias";
    case ImageOperandsShift::Lod:                     return "Lod";
    case ImageOperandsShift::Grad:                    return "Grad";
    case ImageOperandsShift::ConstOffset:             return "ConstOffset";
    case ImageOperandsShift::Offset:                  return "Offset";
    case ImageOperandsShift::ConstOffsets:            return "ConstOffsets";
    case ImageOperandsShift::Sample:                  return "Sample";
    case ImageOperandsShift::MinLod:                  return "MinLod";
    case ImageOperandsShift::MakeTexelAvailableKHR:   return "MakeTexelAvailableKHR";
    case ImageOperandsShift::MakeTexelVisibleKHR:     return "MakeTexelVisibleKHR";
    case ImageOperandsShift::NonPrivateTexelKHR:      return "NonPrivateTexelKHR";
    case ImageOperandsShift::VolatileTexelKHR:        return "VolatileTexelKHR";
    case ImageOperandsShift::SignExtend:              return "SignExtend";
    case ImageOperandsShift::ZeroExtend:              return "ZeroExtend";
    case ImageOperandsShift::Nontemporal:             return "Nontemporal";

    case ImageOperandsCeiling:
    default:
        return "Bad";
    }
}

const char* FPFastMathString(int mode)
{
    switch (mode) {
    case 0: return "NotNaN";
    case 1: return "NotInf";
    case 2: return "NSZ";
    case 3: return "AllowRecip";
    case 4: return "Fast";

    default:     return "Bad";
    }
}

const char* FPRoundingModeString(int mode)
{
    switch (mode) {
    case 0:  return "RTE";
    case 1:  return "RTZ";
    case 2:  return "RTP";
    case 3:  return "RTN";

    default: return "Bad";
    }
}

const char* LinkageTypeString(int type)
{
    switch (type) {
    case 0:  return "Export";
    case 1:  return "Import";

    default: return "Bad";
    }
}

const char* FuncParamAttrString(int attr)
{
    switch (attr) {
    case 0:  return "Zext";
    case 1:  return "Sext";
    case 2:  return "ByVal";
    case 3:  return "Sret";
    case 4:  return "NoAlias";
    case 5:  return "NoCapture";
    case 6:  return "NoWrite";
    case 7:  return "NoReadWrite";

    default: return "Bad";
    }
}

const char* AccessQualifierString(int attr)
{
    switch (attr) {
    case 0:  return "ReadOnly";
    case 1:  return "WriteOnly";
    case 2:  return "ReadWrite";

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
    default: return "Bad";
    }
}

const int LoopControlCeiling = LoopControlShift::PartialCount + 1;

const char* LoopControlString(int cont)
{
    switch (cont) {
        case LoopControlShift::Unroll:             return "Unroll";
    case LoopControlShift::DontUnroll:         return "DontUnroll";
    case LoopControlShift::DependencyInfinite: return "DependencyInfinite";
    case LoopControlShift::DependencyLength:   return "DependencyLength";
    case LoopControlShift::MinIterations:      return "MinIterations";
    case LoopControlShift::MaxIterations:      return "MaxIterations";
    case LoopControlShift::IterationMultiple:  return "IterationMultiple";
    case LoopControlShift::PeelCount:          return "PeelCount";
    case LoopControlShift::PartialCount:       return "PartialCount";

    case LoopControlCeiling:
    default: return "Bad";
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

const char* MemorySemanticsString(int mem)
{
    // Note: No bits set (None) means "Relaxed"
    switch (mem) {
    case 0: return "Bad"; // Note: this is a placeholder for 'Consume'
    case 1: return "Acquire";
    case 2: return "Release";
    case 3: return "AcquireRelease";
    case 4: return "SequentiallyConsistent";
    case 5: return "Bad"; // Note: reserved for future expansion
    case 6: return "UniformMemory";
    case 7: return "SubgroupMemory";
    case 8: return "WorkgroupMemory";
    case 9: return "CrossWorkgroupMemory";
    case 10: return "AtomicCounterMemory";
    case 11: return "ImageMemory";

    default:     return "Bad";
    }
}

const int MemoryAccessCeiling = 6;

const char* MemoryAccessString(int mem)
{
    switch (mem) {
        case MemoryAccessShift::Volatile:                 return "Volatile";
    case MemoryAccessShift::Aligned:                  return "Aligned";
    case MemoryAccessShift::Nontemporal:              return "Nontemporal";
    case MemoryAccessShift::MakePointerAvailableKHR:  return "MakePointerAvailableKHR";
    case MemoryAccessShift::MakePointerVisibleKHR:    return "MakePointerVisibleKHR";
    case MemoryAccessShift::NonPrivatePointerKHR:     return "NonPrivatePointerKHR";

    default: return "Bad";
    }
}

const int CooperativeMatrixOperandsCeiling = 6;

const char* CooperativeMatrixOperandsString(int op)
{
    switch (op) {
        case CooperativeMatrixOperandsShift::MatrixASignedComponentsKHR:  return "ASignedComponentsKHR";
    case CooperativeMatrixOperandsShift::MatrixBSignedComponentsKHR:  return "BSignedComponentsKHR";
    case CooperativeMatrixOperandsShift::MatrixCSignedComponentsKHR:  return "CSignedComponentsKHR";
    case CooperativeMatrixOperandsShift::MatrixResultSignedComponentsKHR:  return "ResultSignedComponentsKHR";
    case CooperativeMatrixOperandsShift::SaturatingAccumulationKHR:   return "SaturatingAccumulationKHR";

    default: return "Bad";
    }
}

const int TensorAddressingOperandsCeiling = 3;

const char* TensorAddressingOperandsString(int op)
{
    switch (op) {
        case TensorAddressingOperandsShift::TensorView:  return "TensorView";
        case TensorAddressingOperandsShift::DecodeFunc:  return "DecodeFunc";

    default: return "Bad";
    }
}

const char* ScopeString(int mem)
{
    switch (mem) {
    case 0:  return "CrossDevice";
    case 1:  return "Device";
    case 2:  return "Workgroup";
    case 3:  return "Subgroup";
    case 4:  return "Invocation";

    default: return "Bad";
    }
}

const char* GroupOperationString(int gop)
{

    switch (gop)
    {
        case GroupOperation::Reduce:  return "Reduce";
    case GroupOperation::InclusiveScan:  return "InclusiveScan";
    case GroupOperation::ExclusiveScan:  return "ExclusiveScan";
    case GroupOperation::ClusteredReduce:  return "ClusteredReduce";
    case GroupOperation::PartitionedReduceNV:  return "PartitionedReduceNV";
    case GroupOperation::PartitionedInclusiveScanNV:  return "PartitionedInclusiveScanNV";
    case GroupOperation::PartitionedExclusiveScanNV:  return "PartitionedExclusiveScanNV";

    default: return "Bad";
    }
}

const char* KernelEnqueueFlagsString(int flag)
{
    switch (flag)
    {
    case 0:  return "NoWait";
    case 1:  return "WaitKernel";
    case 2:  return "WaitWorkGroup";

    default: return "Bad";
    }
}

const char* KernelProfilingInfoString(int info)
{
    switch (info)
    {
    case 0:  return "CmdExecTime";

    default: return "Bad";
    }
}

const char* CapabilityString(int info)
{
    switch (info)
    {
    case 0:  return "Matrix";
    case 1:  return "Shader";
    case 2:  return "Geometry";
    case 3:  return "Tessellation";
    case 4:  return "Addresses";
    case 5:  return "Linkage";
    case 6:  return "Kernel";
    case 7:  return "Vector16";
    case 8:  return "Float16Buffer";
    case 9:  return "Float16";
    case 10: return "Float64";
    case 11: return "Int64";
    case 12: return "Int64Atomics";
    case 13: return "ImageBasic";
    case 14: return "ImageReadWrite";
    case 15: return "ImageMipmap";
    case 16: return "Bad";
    case 17: return "Pipes";
    case 18: return "Groups";
    case 19: return "DeviceEnqueue";
    case 20: return "LiteralSampler";
    case 21: return "AtomicStorage";
    case 22: return "Int16";
    case 23: return "TessellationPointSize";
    case 24: return "GeometryPointSize";
    case 25: return "ImageGatherExtended";
    case 26: return "Bad";
    case 27: return "StorageImageMultisample";
    case 28: return "UniformBufferArrayDynamicIndexing";
    case 29: return "SampledImageArrayDynamicIndexing";
    case 30: return "StorageBufferArrayDynamicIndexing";
    case 31: return "StorageImageArrayDynamicIndexing";
    case 32: return "ClipDistance";
    case 33: return "CullDistance";
    case 34: return "ImageCubeArray";
    case 35: return "SampleRateShading";
    case 36: return "ImageRect";
    case 37: return "SampledRect";
    case 38: return "GenericPointer";
    case 39: return "Int8";
    case 40: return "InputAttachment";
    case 41: return "SparseResidency";
    case 42: return "MinLod";
    case 43: return "Sampled1D";
    case 44: return "Image1D";
    case 45: return "SampledCubeArray";
    case 46: return "SampledBuffer";
    case 47: return "ImageBuffer";
    case 48: return "ImageMSArray";
    case 49: return "StorageImageExtendedFormats";
    case 50: return "ImageQuery";
    case 51: return "DerivativeControl";
    case 52: return "InterpolationFunction";
    case 53: return "TransformFeedback";
    case 54: return "GeometryStreams";
    case 55: return "StorageImageReadWithoutFormat";
    case 56: return "StorageImageWriteWithoutFormat";
    case 57: return "MultiViewport";
    case 61: return "GroupNonUniform";
    case 62: return "GroupNonUniformVote";
    case 63: return "GroupNonUniformArithmetic";
    case 64: return "GroupNonUniformBallot";
    case 65: return "GroupNonUniformShuffle";
    case 66: return "GroupNonUniformShuffleRelative";
    case 67: return "GroupNonUniformClustered";
    case 68: return "GroupNonUniformQuad";

    case Capability::SubgroupBallotKHR: return "SubgroupBallotKHR";
    case Capability::DrawParameters:    return "DrawParameters";
    case Capability::SubgroupVoteKHR:   return "SubgroupVoteKHR";
    case Capability::GroupNonUniformRotateKHR: return "CapabilityGroupNonUniformRotateKHR";

    case Capability::StorageUniformBufferBlock16: return "StorageUniformBufferBlock16";
    case Capability::StorageUniform16:            return "StorageUniform16";
    case Capability::StoragePushConstant16:       return "StoragePushConstant16";
    case Capability::StorageInputOutput16:        return "StorageInputOutput16";

    case Capability::StorageBuffer8BitAccess:             return "StorageBuffer8BitAccess";
    case Capability::UniformAndStorageBuffer8BitAccess:   return "UniformAndStorageBuffer8BitAccess";
    case Capability::StoragePushConstant8:                return "StoragePushConstant8";

    case Capability::DeviceGroup: return "DeviceGroup";
    case Capability::MultiView:   return "MultiView";

    case Capability::DenormPreserve:           return "DenormPreserve";
    case Capability::DenormFlushToZero:        return "DenormFlushToZero";
    case Capability::SignedZeroInfNanPreserve: return "SignedZeroInfNanPreserve";
    case Capability::RoundingModeRTE:          return "RoundingModeRTE";
    case Capability::RoundingModeRTZ:          return "RoundingModeRTZ";

    case Capability::StencilExportEXT: return "StencilExportEXT";

    case Capability::Float16ImageAMD:       return "Float16ImageAMD";
    case Capability::ImageGatherBiasLodAMD: return "ImageGatherBiasLodAMD";
    case Capability::FragmentMaskAMD:       return "FragmentMaskAMD";
    case Capability::ImageReadWriteLodAMD:  return "ImageReadWriteLodAMD";

    case Capability::AtomicStorageOps:             return "AtomicStorageOps";

    case Capability::SampleMaskPostDepthCoverage:  return "SampleMaskPostDepthCoverage";
    case Capability::GeometryShaderPassthroughNV:     return "GeometryShaderPassthroughNV";
    case Capability::ShaderViewportIndexLayerNV:      return "ShaderViewportIndexLayerNV";
    case Capability::ShaderViewportMaskNV:            return "ShaderViewportMaskNV";
    case Capability::ShaderStereoViewNV:              return "ShaderStereoViewNV";
    case Capability::PerViewAttributesNV:             return "PerViewAttributesNV";
    case Capability::GroupNonUniformPartitionedNV:    return "GroupNonUniformPartitionedNV";
    case Capability::RayTracingNV:                    return "RayTracingNV";
    case Capability::RayTracingMotionBlurNV:          return "RayTracingMotionBlurNV";
    case Capability::RayTracingKHR:                   return "RayTracingKHR";
    case Capability::RayCullMaskKHR:                  return "RayCullMaskKHR";
    case Capability::RayQueryKHR:                     return "RayQueryKHR";
    case Capability::RayTracingProvisionalKHR:        return "RayTracingProvisionalKHR";
    case Capability::RayTraversalPrimitiveCullingKHR: return "RayTraversalPrimitiveCullingKHR";
    case Capability::RayTracingPositionFetchKHR:      return "RayTracingPositionFetchKHR";
    case Capability::DisplacementMicromapNV:           return "DisplacementMicromapNV";
    case Capability::RayTracingOpacityMicromapEXT:    return "RayTracingOpacityMicromapEXT";
    case Capability::RayTracingDisplacementMicromapNV: return "CapabilityRayTracingDisplacementMicromapNV";
    case Capability::RayQueryPositionFetchKHR:        return "RayQueryPositionFetchKHR";
    case Capability::ComputeDerivativeGroupQuadsNV:   return "ComputeDerivativeGroupQuadsNV";
    case Capability::ComputeDerivativeGroupLinearNV:  return "ComputeDerivativeGroupLinearNV";
    case Capability::FragmentBarycentricKHR:          return "FragmentBarycentricKHR";
    case Capability::MeshShadingNV:                   return "MeshShadingNV";
    case Capability::ImageFootprintNV:                return "ImageFootprintNV";
    case Capability::MeshShadingEXT:                  return "MeshShadingEXT";
//    case Capability::ShadingRateNV:                   return "ShadingRateNV";  // superseded by FragmentDensityEXT
    case Capability::SampleMaskOverrideCoverageNV:    return "SampleMaskOverrideCoverageNV";
    case Capability::FragmentDensityEXT:              return "FragmentDensityEXT";

    case Capability::FragmentFullyCoveredEXT: return "FragmentFullyCoveredEXT";

    case Capability::ShaderNonUniformEXT:                          return "ShaderNonUniformEXT";
    case Capability::RuntimeDescriptorArrayEXT:                    return "RuntimeDescriptorArrayEXT";
    case Capability::InputAttachmentArrayDynamicIndexingEXT:       return "InputAttachmentArrayDynamicIndexingEXT";
    case Capability::UniformTexelBufferArrayDynamicIndexingEXT:    return "UniformTexelBufferArrayDynamicIndexingEXT";
    case Capability::StorageTexelBufferArrayDynamicIndexingEXT:    return "StorageTexelBufferArrayDynamicIndexingEXT";
    case Capability::UniformBufferArrayNonUniformIndexingEXT:      return "UniformBufferArrayNonUniformIndexingEXT";
    case Capability::SampledImageArrayNonUniformIndexingEXT:       return "SampledImageArrayNonUniformIndexingEXT";
    case Capability::StorageBufferArrayNonUniformIndexingEXT:      return "StorageBufferArrayNonUniformIndexingEXT";
    case Capability::StorageImageArrayNonUniformIndexingEXT:       return "StorageImageArrayNonUniformIndexingEXT";
    case Capability::InputAttachmentArrayNonUniformIndexingEXT:    return "InputAttachmentArrayNonUniformIndexingEXT";
    case Capability::UniformTexelBufferArrayNonUniformIndexingEXT: return "UniformTexelBufferArrayNonUniformIndexingEXT";
    case Capability::StorageTexelBufferArrayNonUniformIndexingEXT: return "StorageTexelBufferArrayNonUniformIndexingEXT";

    case Capability::VulkanMemoryModelKHR:                return "VulkanMemoryModelKHR";
    case Capability::VulkanMemoryModelDeviceScopeKHR:     return "VulkanMemoryModelDeviceScopeKHR";

    case Capability::PhysicalStorageBufferAddressesEXT:   return "PhysicalStorageBufferAddressesEXT";

    case Capability::VariablePointers:                    return "VariablePointers";

    case Capability::CooperativeMatrixNV:     return "CooperativeMatrixNV";
    case Capability::CooperativeMatrixKHR:    return "CooperativeMatrixKHR";
    case Capability::CooperativeMatrixReductionsNV:           return "CooperativeMatrixReductionsNV";
    case Capability::CooperativeMatrixConversionsNV:          return "CooperativeMatrixConversionsNV";
    case Capability::CooperativeMatrixPerElementOperationsNV: return "CooperativeMatrixPerElementOperationsNV";
    case Capability::CooperativeMatrixTensorAddressingNV:     return "CooperativeMatrixTensorAddressingNV";
    case Capability::CooperativeMatrixBlockLoadsNV:           return "CooperativeMatrixBlockLoadsNV";
    case Capability::TensorAddressingNV:                      return "TensorAddressingNV";

    case Capability::ShaderSMBuiltinsNV:      return "ShaderSMBuiltinsNV";

    case Capability::CooperativeVectorNV:                     return "CooperativeVectorNV";
    case Capability::CooperativeVectorTrainingNV:             return "CooperativeVectorTrainingNV";

    case Capability::FragmentShaderSampleInterlockEXT:        return "CapabilityFragmentShaderSampleInterlockEXT";
    case Capability::FragmentShaderPixelInterlockEXT:         return "CapabilityFragmentShaderPixelInterlockEXT";
    case Capability::FragmentShaderShadingRateInterlockEXT:   return "CapabilityFragmentShaderShadingRateInterlockEXT";

    case Capability::TileImageColorReadAccessEXT:           return "TileImageColorReadAccessEXT";
    case Capability::TileImageDepthReadAccessEXT:           return "TileImageDepthReadAccessEXT";
    case Capability::TileImageStencilReadAccessEXT:         return "TileImageStencilReadAccessEXT";

    case Capability::CooperativeMatrixLayoutsARM:             return "CooperativeMatrixLayoutsARM";

    case Capability::FragmentShadingRateKHR:                  return "FragmentShadingRateKHR";

    case Capability::DemoteToHelperInvocationEXT:             return "DemoteToHelperInvocationEXT";
    case Capability::AtomicFloat16VectorNV:                   return "AtomicFloat16VectorNV";
    case Capability::ShaderClockKHR:                          return "ShaderClockKHR";
    case Capability::QuadControlKHR:                          return "QuadControlKHR";
    case Capability::Int64ImageEXT:                           return "Int64ImageEXT";

    case Capability::IntegerFunctions2INTEL:              return "CapabilityIntegerFunctions2INTEL";

    case Capability::ExpectAssumeKHR:                         return "ExpectAssumeKHR";

    case Capability::AtomicFloat16AddEXT:                     return "AtomicFloat16AddEXT";
    case Capability::AtomicFloat32AddEXT:                     return "AtomicFloat32AddEXT";
    case Capability::AtomicFloat64AddEXT:                     return "AtomicFloat64AddEXT";
    case Capability::AtomicFloat16MinMaxEXT:                  return "AtomicFloat16MinMaxEXT";
    case Capability::AtomicFloat32MinMaxEXT:                  return "AtomicFloat32MinMaxEXT";
    case Capability::AtomicFloat64MinMaxEXT:                  return "AtomicFloat64MinMaxEXT";

    case Capability::WorkgroupMemoryExplicitLayoutKHR:            return "CapabilityWorkgroupMemoryExplicitLayoutKHR";
    case Capability::WorkgroupMemoryExplicitLayout8BitAccessKHR:  return "CapabilityWorkgroupMemoryExplicitLayout8BitAccessKHR";
    case Capability::WorkgroupMemoryExplicitLayout16BitAccessKHR: return "CapabilityWorkgroupMemoryExplicitLayout16BitAccessKHR";
    case Capability::CoreBuiltinsARM:                             return "CoreBuiltinsARM";

    case Capability::ShaderInvocationReorderNV:                return "ShaderInvocationReorderNV";

    case Capability::TextureSampleWeightedQCOM:           return "TextureSampleWeightedQCOM";
    case Capability::TextureBoxFilterQCOM:                return "TextureBoxFilterQCOM";
    case Capability::TextureBlockMatchQCOM:               return "TextureBlockMatchQCOM";
    case Capability::TextureBlockMatch2QCOM:              return "TextureBlockMatch2QCOM";

    case Capability::ReplicatedCompositesEXT:             return "CapabilityReplicatedCompositesEXT";

    case Capability::DotProductKHR:                       return "DotProductKHR";
    case Capability::DotProductInputAllKHR:               return "DotProductInputAllKHR";
    case Capability::DotProductInput4x8BitKHR:            return "DotProductInput4x8BitKHR";
    case Capability::DotProductInput4x8BitPackedKHR:      return "DotProductInput4x8BitPackedKHR";

    case Capability::RayTracingClusterAccelerationStructureNV:   return "RayTracingClusterAccelerationStructureNV";

    case Capability::RayTracingSpheresGeometryNV:             return "RayTracingSpheresGeometryNV";
    case Capability::RayTracingLinearSweptSpheresGeometryNV:  return "RayTracingLinearSweptSpheresGeometryNV";

    case Capability::BFloat16TypeKHR:                     return "CapabilityBFloat16TypeKHR";
    case Capability::BFloat16DotProductKHR:               return "CapabilityBFloat16DotProductKHR";
    case Capability::BFloat16CooperativeMatrixKHR:        return "CapabilityBFloat16CooperativeMatrixKHR";

    default: return "Bad";
    }
}

const char* OpcodeString(int op)
{
    switch (op) {
    case 0:   return "OpNop";
    case 1:   return "OpUndef";
    case 2:   return "OpSourceContinued";
    case 3:   return "OpSource";
    case 4:   return "OpSourceExtension";
    case 5:   return "OpName";
    case 6:   return "OpMemberName";
    case 7:   return "OpString";
    case 8:   return "OpLine";
    case 9:   return "Bad";
    case 10:  return "OpExtension";
    case 11:  return "OpExtInstImport";
    case 12:  return "OpExtInst";
    case 13:  return "Bad";
    case 14:  return "OpMemoryModel";
    case 15:  return "OpEntryPoint";
    case 16:  return "OpExecutionMode";
    case 17:  return "OpCapability";
    case 18:  return "Bad";
    case 19:  return "OpTypeVoid";
    case 20:  return "OpTypeBool";
    case 21:  return "OpTypeInt";
    case 22:  return "OpTypeFloat";
    case 23:  return "OpTypeVector";
    case 24:  return "OpTypeMatrix";
    case 25:  return "OpTypeImage";
    case 26:  return "OpTypeSampler";
    case 27:  return "OpTypeSampledImage";
    case 28:  return "OpTypeArray";
    case 29:  return "OpTypeRuntimeArray";
    case 30:  return "OpTypeStruct";
    case 31:  return "OpTypeOpaque";
    case 32:  return "OpTypePointer";
    case 33:  return "OpTypeFunction";
    case 34:  return "OpTypeEvent";
    case 35:  return "OpTypeDeviceEvent";
    case 36:  return "OpTypeReserveId";
    case 37:  return "OpTypeQueue";
    case 38:  return "OpTypePipe";
    case 39:  return "OpTypeForwardPointer";
    case 40:  return "Bad";
    case 41:  return "OpConstantTrue";
    case 42:  return "OpConstantFalse";
    case 43:  return "OpConstant";
    case 44:  return "OpConstantComposite";
    case 45:  return "OpConstantSampler";
    case 46:  return "OpConstantNull";
    case 47:  return "Bad";
    case 48:  return "OpSpecConstantTrue";
    case 49:  return "OpSpecConstantFalse";
    case 50:  return "OpSpecConstant";
    case 51:  return "OpSpecConstantComposite";
    case 52:  return "OpSpecConstantOp";
    case 53:  return "Bad";
    case 54:  return "OpFunction";
    case 55:  return "OpFunctionParameter";
    case 56:  return "OpFunctionEnd";
    case 57:  return "OpFunctionCall";
    case 58:  return "Bad";
    case 59:  return "OpVariable";
    case 60:  return "OpImageTexelPointer";
    case 61:  return "OpLoad";
    case 62:  return "OpStore";
    case 63:  return "OpCopyMemory";
    case 64:  return "OpCopyMemorySized";
    case 65:  return "OpAccessChain";
    case 66:  return "OpInBoundsAccessChain";
    case 67:  return "OpPtrAccessChain";
    case 68:  return "OpArrayLength";
    case 69:  return "OpGenericPtrMemSemantics";
    case 70:  return "OpInBoundsPtrAccessChain";
    case 71:  return "OpDecorate";
    case 72:  return "OpMemberDecorate";
    case 73:  return "OpDecorationGroup";
    case 74:  return "OpGroupDecorate";
    case 75:  return "OpGroupMemberDecorate";
    case 76:  return "Bad";
    case 77:  return "OpVectorExtractDynamic";
    case 78:  return "OpVectorInsertDynamic";
    case 79:  return "OpVectorShuffle";
    case 80:  return "OpCompositeConstruct";
    case 81:  return "OpCompositeExtract";
    case 82:  return "OpCompositeInsert";
    case 83:  return "OpCopyObject";
    case 84:  return "OpTranspose";
    case Op::OpCopyLogical: return "OpCopyLogical";
    case 85:  return "Bad";
    case 86:  return "OpSampledImage";
    case 87:  return "OpImageSampleImplicitLod";
    case 88:  return "OpImageSampleExplicitLod";
    case 89:  return "OpImageSampleDrefImplicitLod";
    case 90:  return "OpImageSampleDrefExplicitLod";
    case 91:  return "OpImageSampleProjImplicitLod";
    case 92:  return "OpImageSampleProjExplicitLod";
    case 93:  return "OpImageSampleProjDrefImplicitLod";
    case 94:  return "OpImageSampleProjDrefExplicitLod";
    case 95:  return "OpImageFetch";
    case 96:  return "OpImageGather";
    case 97:  return "OpImageDrefGather";
    case 98:  return "OpImageRead";
    case 99:  return "OpImageWrite";
    case 100: return "OpImage";
    case 101: return "OpImageQueryFormat";
    case 102: return "OpImageQueryOrder";
    case 103: return "OpImageQuerySizeLod";
    case 104: return "OpImageQuerySize";
    case 105: return "OpImageQueryLod";
    case 106: return "OpImageQueryLevels";
    case 107: return "OpImageQuerySamples";
    case 108: return "Bad";
    case 109: return "OpConvertFToU";
    case 110: return "OpConvertFToS";
    case 111: return "OpConvertSToF";
    case 112: return "OpConvertUToF";
    case 113: return "OpUConvert";
    case 114: return "OpSConvert";
    case 115: return "OpFConvert";
    case 116: return "OpQuantizeToF16";
    case 117: return "OpConvertPtrToU";
    case 118: return "OpSatConvertSToU";
    case 119: return "OpSatConvertUToS";
    case 120: return "OpConvertUToPtr";
    case 121: return "OpPtrCastToGeneric";
    case 122: return "OpGenericCastToPtr";
    case 123: return "OpGenericCastToPtrExplicit";
    case 124: return "OpBitcast";
    case 125: return "Bad";
    case 126: return "OpSNegate";
    case 127: return "OpFNegate";
    case 128: return "OpIAdd";
    case 129: return "OpFAdd";
    case 130: return "OpISub";
    case 131: return "OpFSub";
    case 132: return "OpIMul";
    case 133: return "OpFMul";
    case 134: return "OpUDiv";
    case 135: return "OpSDiv";
    case 136: return "OpFDiv";
    case 137: return "OpUMod";
    case 138: return "OpSRem";
    case 139: return "OpSMod";
    case 140: return "OpFRem";
    case 141: return "OpFMod";
    case 142: return "OpVectorTimesScalar";
    case 143: return "OpMatrixTimesScalar";
    case 144: return "OpVectorTimesMatrix";
    case 145: return "OpMatrixTimesVector";
    case 146: return "OpMatrixTimesMatrix";
    case 147: return "OpOuterProduct";
    case 148: return "OpDot";
    case 149: return "OpIAddCarry";
    case 150: return "OpISubBorrow";
    case 151: return "OpUMulExtended";
    case 152: return "OpSMulExtended";
    case 153: return "Bad";
    case 154: return "OpAny";
    case 155: return "OpAll";
    case 156: return "OpIsNan";
    case 157: return "OpIsInf";
    case 158: return "OpIsFinite";
    case 159: return "OpIsNormal";
    case 160: return "OpSignBitSet";
    case 161: return "OpLessOrGreater";
    case 162: return "OpOrdered";
    case 163: return "OpUnordered";
    case 164: return "OpLogicalEqual";
    case 165: return "OpLogicalNotEqual";
    case 166: return "OpLogicalOr";
    case 167: return "OpLogicalAnd";
    case 168: return "OpLogicalNot";
    case 169: return "OpSelect";
    case 170: return "OpIEqual";
    case 171: return "OpINotEqual";
    case 172: return "OpUGreaterThan";
    case 173: return "OpSGreaterThan";
    case 174: return "OpUGreaterThanEqual";
    case 175: return "OpSGreaterThanEqual";
    case 176: return "OpULessThan";
    case 177: return "OpSLessThan";
    case 178: return "OpULessThanEqual";
    case 179: return "OpSLessThanEqual";
    case 180: return "OpFOrdEqual";
    case 181: return "OpFUnordEqual";
    case 182: return "OpFOrdNotEqual";
    case 183: return "OpFUnordNotEqual";
    case 184: return "OpFOrdLessThan";
    case 185: return "OpFUnordLessThan";
    case 186: return "OpFOrdGreaterThan";
    case 187: return "OpFUnordGreaterThan";
    case 188: return "OpFOrdLessThanEqual";
    case 189: return "OpFUnordLessThanEqual";
    case 190: return "OpFOrdGreaterThanEqual";
    case 191: return "OpFUnordGreaterThanEqual";
    case 192: return "Bad";
    case 193: return "Bad";
    case 194: return "OpShiftRightLogical";
    case 195: return "OpShiftRightArithmetic";
    case 196: return "OpShiftLeftLogical";
    case 197: return "OpBitwiseOr";
    case 198: return "OpBitwiseXor";
    case 199: return "OpBitwiseAnd";
    case 200: return "OpNot";
    case 201: return "OpBitFieldInsert";
    case 202: return "OpBitFieldSExtract";
    case 203: return "OpBitFieldUExtract";
    case 204: return "OpBitReverse";
    case 205: return "OpBitCount";
    case 206: return "Bad";
    case 207: return "OpDPdx";
    case 208: return "OpDPdy";
    case 209: return "OpFwidth";
    case 210: return "OpDPdxFine";
    case 211: return "OpDPdyFine";
    case 212: return "OpFwidthFine";
    case 213: return "OpDPdxCoarse";
    case 214: return "OpDPdyCoarse";
    case 215: return "OpFwidthCoarse";
    case 216: return "Bad";
    case 217: return "Bad";
    case 218: return "OpEmitVertex";
    case 219: return "OpEndPrimitive";
    case 220: return "OpEmitStreamVertex";
    case 221: return "OpEndStreamPrimitive";
    case 222: return "Bad";
    case 223: return "Bad";
    case 224: return "OpControlBarrier";
    case 225: return "OpMemoryBarrier";
    case 226: return "Bad";
    case 227: return "OpAtomicLoad";
    case 228: return "OpAtomicStore";
    case 229: return "OpAtomicExchange";
    case 230: return "OpAtomicCompareExchange";
    case 231: return "OpAtomicCompareExchangeWeak";
    case 232: return "OpAtomicIIncrement";
    case 233: return "OpAtomicIDecrement";
    case 234: return "OpAtomicIAdd";
    case 235: return "OpAtomicISub";
    case 236: return "OpAtomicSMin";
    case 237: return "OpAtomicUMin";
    case 238: return "OpAtomicSMax";
    case 239: return "OpAtomicUMax";
    case 240: return "OpAtomicAnd";
    case 241: return "OpAtomicOr";
    case 242: return "OpAtomicXor";
    case 243: return "Bad";
    case 244: return "Bad";
    case 245: return "OpPhi";
    case 246: return "OpLoopMerge";
    case 247: return "OpSelectionMerge";
    case 248: return "OpLabel";
    case 249: return "OpBranch";
    case 250: return "OpBranchConditional";
    case 251: return "OpSwitch";
    case 252: return "OpKill";
    case 253: return "OpReturn";
    case 254: return "OpReturnValue";
    case 255: return "OpUnreachable";
    case 256: return "OpLifetimeStart";
    case 257: return "OpLifetimeStop";
    case 258: return "Bad";
    case 259: return "OpGroupAsyncCopy";
    case 260: return "OpGroupWaitEvents";
    case 261: return "OpGroupAll";
    case 262: return "OpGroupAny";
    case 263: return "OpGroupBroadcast";
    case 264: return "OpGroupIAdd";
    case 265: return "OpGroupFAdd";
    case 266: return "OpGroupFMin";
    case 267: return "OpGroupUMin";
    case 268: return "OpGroupSMin";
    case 269: return "OpGroupFMax";
    case 270: return "OpGroupUMax";
    case 271: return "OpGroupSMax";
    case 272: return "Bad";
    case 273: return "Bad";
    case 274: return "OpReadPipe";
    case 275: return "OpWritePipe";
    case 276: return "OpReservedReadPipe";
    case 277: return "OpReservedWritePipe";
    case 278: return "OpReserveReadPipePackets";
    case 279: return "OpReserveWritePipePackets";
    case 280: return "OpCommitReadPipe";
    case 281: return "OpCommitWritePipe";
    case 282: return "OpIsValidReserveId";
    case 283: return "OpGetNumPipePackets";
    case 284: return "OpGetMaxPipePackets";
    case 285: return "OpGroupReserveReadPipePackets";
    case 286: return "OpGroupReserveWritePipePackets";
    case 287: return "OpGroupCommitReadPipe";
    case 288: return "OpGroupCommitWritePipe";
    case 289: return "Bad";
    case 290: return "Bad";
    case 291: return "OpEnqueueMarker";
    case 292: return "OpEnqueueKernel";
    case 293: return "OpGetKernelNDrangeSubGroupCount";
    case 294: return "OpGetKernelNDrangeMaxSubGroupSize";
    case 295: return "OpGetKernelWorkGroupSize";
    case 296: return "OpGetKernelPreferredWorkGroupSizeMultiple";
    case 297: return "OpRetainEvent";
    case 298: return "OpReleaseEvent";
    case 299: return "OpCreateUserEvent";
    case 300: return "OpIsValidEvent";
    case 301: return "OpSetUserEventStatus";
    case 302: return "OpCaptureEventProfilingInfo";
    case 303: return "OpGetDefaultQueue";
    case 304: return "OpBuildNDRange";
    case 305: return "OpImageSparseSampleImplicitLod";
    case 306: return "OpImageSparseSampleExplicitLod";
    case 307: return "OpImageSparseSampleDrefImplicitLod";
    case 308: return "OpImageSparseSampleDrefExplicitLod";
    case 309: return "OpImageSparseSampleProjImplicitLod";
    case 310: return "OpImageSparseSampleProjExplicitLod";
    case 311: return "OpImageSparseSampleProjDrefImplicitLod";
    case 312: return "OpImageSparseSampleProjDrefExplicitLod";
    case 313: return "OpImageSparseFetch";
    case 314: return "OpImageSparseGather";
    case 315: return "OpImageSparseDrefGather";
    case 316: return "OpImageSparseTexelsResident";
    case 317: return "OpNoLine";
    case 318: return "OpAtomicFlagTestAndSet";
    case 319: return "OpAtomicFlagClear";
    case 320: return "OpImageSparseRead";

    case Op::OpModuleProcessed: return "OpModuleProcessed";
    case Op::OpExecutionModeId:
        return "OpExecutionModeId";
    case Op::OpDecorateId:
        return "OpDecorateId";

    case 333: return "OpGroupNonUniformElect";
    case 334: return "OpGroupNonUniformAll";
    case 335: return "OpGroupNonUniformAny";
    case 336: return "OpGroupNonUniformAllEqual";
    case 337: return "OpGroupNonUniformBroadcast";
    case 338: return "OpGroupNonUniformBroadcastFirst";
    case 339: return "OpGroupNonUniformBallot";
    case 340: return "OpGroupNonUniformInverseBallot";
    case 341: return "OpGroupNonUniformBallotBitExtract";
    case 342: return "OpGroupNonUniformBallotBitCount";
    case 343: return "OpGroupNonUniformBallotFindLSB";
    case 344: return "OpGroupNonUniformBallotFindMSB";
    case 345: return "OpGroupNonUniformShuffle";
    case 346: return "OpGroupNonUniformShuffleXor";
    case 347: return "OpGroupNonUniformShuffleUp";
    case 348: return "OpGroupNonUniformShuffleDown";
    case 349: return "OpGroupNonUniformIAdd";
    case 350: return "OpGroupNonUniformFAdd";
    case 351: return "OpGroupNonUniformIMul";
    case 352: return "OpGroupNonUniformFMul";
    case 353: return "OpGroupNonUniformSMin";
    case 354: return "OpGroupNonUniformUMin";
    case 355: return "OpGroupNonUniformFMin";
    case 356: return "OpGroupNonUniformSMax";
    case 357: return "OpGroupNonUniformUMax";
    case 358: return "OpGroupNonUniformFMax";
    case 359: return "OpGroupNonUniformBitwiseAnd";
    case 360: return "OpGroupNonUniformBitwiseOr";
    case 361: return "OpGroupNonUniformBitwiseXor";
    case 362: return "OpGroupNonUniformLogicalAnd";
    case 363: return "OpGroupNonUniformLogicalOr";
    case 364: return "OpGroupNonUniformLogicalXor";
    case 365: return "OpGroupNonUniformQuadBroadcast";
    case 366: return "OpGroupNonUniformQuadSwap";

    case Op::OpTerminateInvocation:
        return "OpTerminateInvocation";

    case 4421: return "OpSubgroupBallotKHR";
    case 4422: return "OpSubgroupFirstInvocationKHR";
    case 4428: return "OpSubgroupAllKHR";
    case 4429: return "OpSubgroupAnyKHR";
    case 4430: return "OpSubgroupAllEqualKHR";
    case 4432: return "OpSubgroupReadInvocationKHR";
    case 4433: return "OpExtInstWithForwardRefsKHR";

    case Op::OpGroupNonUniformQuadAllKHR:
        return "OpGroupNonUniformQuadAllKHR";
    case Op::OpGroupNonUniformQuadAnyKHR:
        return "OpGroupNonUniformQuadAnyKHR";

    case Op::OpAtomicFAddEXT:
        return "OpAtomicFAddEXT";
    case Op::OpAtomicFMinEXT:
        return "OpAtomicFMinEXT";
    case Op::OpAtomicFMaxEXT:
        return "OpAtomicFMaxEXT";

    case Op::OpAssumeTrueKHR:
        return "OpAssumeTrueKHR";
    case Op::OpExpectKHR:
        return "OpExpectKHR";

    case 5000: return "OpGroupIAddNonUniformAMD";
    case 5001: return "OpGroupFAddNonUniformAMD";
    case 5002: return "OpGroupFMinNonUniformAMD";
    case 5003: return "OpGroupUMinNonUniformAMD";
    case 5004: return "OpGroupSMinNonUniformAMD";
    case 5005: return "OpGroupFMaxNonUniformAMD";
    case 5006: return "OpGroupUMaxNonUniformAMD";
    case 5007: return "OpGroupSMaxNonUniformAMD";

    case 5011: return "OpFragmentMaskFetchAMD";
    case 5012: return "OpFragmentFetchAMD";

    case Op::OpReadClockKHR:               return "OpReadClockKHR";

    case Op::OpDecorateStringGOOGLE:       return "OpDecorateStringGOOGLE";
    case Op::OpMemberDecorateStringGOOGLE: return "OpMemberDecorateStringGOOGLE";

    case Op::OpReportIntersectionKHR:             return "OpReportIntersectionKHR";
    case Op::OpIgnoreIntersectionNV:              return "OpIgnoreIntersectionNV";
    case Op::OpIgnoreIntersectionKHR:             return "OpIgnoreIntersectionKHR";
    case Op::OpTerminateRayNV:                    return "OpTerminateRayNV";
    case Op::OpTerminateRayKHR:                   return "OpTerminateRayKHR";
    case Op::OpTraceNV:                           return "OpTraceNV";
    case Op::OpTraceRayMotionNV:                  return "OpTraceRayMotionNV";
    case Op::OpTraceRayKHR:                       return "OpTraceRayKHR";
    case Op::OpTypeAccelerationStructureKHR:      return "OpTypeAccelerationStructureKHR";
    case Op::OpExecuteCallableNV:                 return "OpExecuteCallableNV";
    case Op::OpExecuteCallableKHR:                return "OpExecuteCallableKHR";
    case Op::OpConvertUToAccelerationStructureKHR: return "OpConvertUToAccelerationStructureKHR";

    case Op::OpGroupNonUniformPartitionNV:       return "OpGroupNonUniformPartitionNV";
    case Op::OpImageSampleFootprintNV:           return "OpImageSampleFootprintNV";
    case Op::OpWritePackedPrimitiveIndices4x8NV: return "OpWritePackedPrimitiveIndices4x8NV";
    case Op::OpEmitMeshTasksEXT:                 return "OpEmitMeshTasksEXT";
    case Op::OpSetMeshOutputsEXT:                return "OpSetMeshOutputsEXT";

    case Op::OpGroupNonUniformRotateKHR:         return "OpGroupNonUniformRotateKHR";

    case Op::OpTypeRayQueryKHR:                                                   return "OpTypeRayQueryKHR";
    case Op::OpRayQueryInitializeKHR:                                             return "OpRayQueryInitializeKHR";
    case Op::OpRayQueryTerminateKHR:                                              return "OpRayQueryTerminateKHR";
    case Op::OpRayQueryGenerateIntersectionKHR:                                   return "OpRayQueryGenerateIntersectionKHR";
    case Op::OpRayQueryConfirmIntersectionKHR:                                    return "OpRayQueryConfirmIntersectionKHR";
    case Op::OpRayQueryProceedKHR:                                                return "OpRayQueryProceedKHR";
    case Op::OpRayQueryGetIntersectionTypeKHR:                                    return "OpRayQueryGetIntersectionTypeKHR";
    case Op::OpRayQueryGetRayTMinKHR:                                             return "OpRayQueryGetRayTMinKHR";
    case Op::OpRayQueryGetRayFlagsKHR:                                            return "OpRayQueryGetRayFlagsKHR";
    case Op::OpRayQueryGetIntersectionTKHR:                                       return "OpRayQueryGetIntersectionTKHR";
    case Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR:                     return "OpRayQueryGetIntersectionInstanceCustomIndexKHR";
    case Op::OpRayQueryGetIntersectionInstanceIdKHR:                              return "OpRayQueryGetIntersectionInstanceIdKHR";
    case Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR:  return "OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR";
    case Op::OpRayQueryGetIntersectionGeometryIndexKHR:                           return "OpRayQueryGetIntersectionGeometryIndexKHR";
    case Op::OpRayQueryGetIntersectionPrimitiveIndexKHR:                          return "OpRayQueryGetIntersectionPrimitiveIndexKHR";
    case Op::OpRayQueryGetIntersectionBarycentricsKHR:                            return "OpRayQueryGetIntersectionBarycentricsKHR";
    case Op::OpRayQueryGetIntersectionFrontFaceKHR:                               return "OpRayQueryGetIntersectionFrontFaceKHR";
    case Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR:                     return "OpRayQueryGetIntersectionCandidateAABBOpaqueKHR";
    case Op::OpRayQueryGetIntersectionObjectRayDirectionKHR:                      return "OpRayQueryGetIntersectionObjectRayDirectionKHR";
    case Op::OpRayQueryGetIntersectionObjectRayOriginKHR:                         return "OpRayQueryGetIntersectionObjectRayOriginKHR";
    case Op::OpRayQueryGetWorldRayDirectionKHR:                                   return "OpRayQueryGetWorldRayDirectionKHR";
    case Op::OpRayQueryGetWorldRayOriginKHR:                                      return "OpRayQueryGetWorldRayOriginKHR";
    case Op::OpRayQueryGetIntersectionObjectToWorldKHR:                           return "OpRayQueryGetIntersectionObjectToWorldKHR";
    case Op::OpRayQueryGetIntersectionWorldToObjectKHR:                           return "OpRayQueryGetIntersectionWorldToObjectKHR";
    case Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR:                 return "OpRayQueryGetIntersectionTriangleVertexPositionsKHR";
    case Op::OpRayQueryGetClusterIdNV:                                            return "OpRayQueryGetIntersectionClusterIdNV";

    case Op::OpRayQueryGetIntersectionSpherePositionNV:                           return "OpRayQueryGetIntersectionSpherePositionNV";
    case Op::OpRayQueryGetIntersectionSphereRadiusNV:                             return "OpRayQueryGetIntersectionSphereRadiusNV";
    case Op::OpRayQueryGetIntersectionLSSHitValueNV:                              return "OpRayQueryGetIntersectionLSSHitValueNV";
    case Op::OpRayQueryGetIntersectionLSSPositionsNV:                             return "OpRayQueryGetIntersectionLSSPositionsNV";
    case Op::OpRayQueryGetIntersectionLSSRadiiNV:                                 return "OpRayQueryGetIntersectionLSSRadiiNV";
    case Op::OpRayQueryIsSphereHitNV:                                             return "OpRayQueryIsSphereHitNV";
    case Op::OpRayQueryIsLSSHitNV:                                                return "OpRayQueryIsLSSHitNV";

    case Op::OpTypeCooperativeMatrixNV:         return "OpTypeCooperativeMatrixNV";
    case Op::OpCooperativeMatrixLoadNV:         return "OpCooperativeMatrixLoadNV";
    case Op::OpCooperativeMatrixStoreNV:        return "OpCooperativeMatrixStoreNV";
    case Op::OpCooperativeMatrixMulAddNV:       return "OpCooperativeMatrixMulAddNV";
    case Op::OpCooperativeMatrixLengthNV:       return "OpCooperativeMatrixLengthNV";
    case Op::OpTypeCooperativeMatrixKHR:        return "OpTypeCooperativeMatrixKHR";
    case Op::OpCooperativeMatrixLoadKHR:        return "OpCooperativeMatrixLoadKHR";
    case Op::OpCooperativeMatrixStoreKHR:       return "OpCooperativeMatrixStoreKHR";
    case Op::OpCooperativeMatrixMulAddKHR:      return "OpCooperativeMatrixMulAddKHR";
    case Op::OpCooperativeMatrixLengthKHR:      return "OpCooperativeMatrixLengthKHR";
    case Op::OpDemoteToHelperInvocationEXT:     return "OpDemoteToHelperInvocationEXT";
    case Op::OpIsHelperInvocationEXT:           return "OpIsHelperInvocationEXT";

    case Op::OpCooperativeMatrixConvertNV:      return "OpCooperativeMatrixConvertNV";
    case Op::OpCooperativeMatrixTransposeNV:    return "OpCooperativeMatrixTransposeNV";
    case Op::OpCooperativeMatrixReduceNV:       return "OpCooperativeMatrixReduceNV";
    case Op::OpCooperativeMatrixLoadTensorNV:   return "OpCooperativeMatrixLoadTensorNV";
    case Op::OpCooperativeMatrixStoreTensorNV:  return "OpCooperativeMatrixStoreTensorNV";
    case Op::OpCooperativeMatrixPerElementOpNV: return "OpCooperativeMatrixPerElementOpNV";
    case Op::OpTypeTensorLayoutNV:              return "OpTypeTensorLayoutNV";
    case Op::OpTypeTensorViewNV:                return "OpTypeTensorViewNV";
    case Op::OpCreateTensorLayoutNV:            return "OpCreateTensorLayoutNV";
    case Op::OpTensorLayoutSetBlockSizeNV:      return "OpTensorLayoutSetBlockSizeNV";
    case Op::OpTensorLayoutSetDimensionNV:      return "OpTensorLayoutSetDimensionNV";
    case Op::OpTensorLayoutSetStrideNV:         return "OpTensorLayoutSetStrideNV";
    case Op::OpTensorLayoutSliceNV:             return "OpTensorLayoutSliceNV";
    case Op::OpTensorLayoutSetClampValueNV:     return "OpTensorLayoutSetClampValueNV";
    case Op::OpCreateTensorViewNV:              return "OpCreateTensorViewNV";
    case Op::OpTensorViewSetDimensionNV:        return "OpTensorViewSetDimensionNV";
    case Op::OpTensorViewSetStrideNV:           return "OpTensorViewSetStrideNV";
    case Op::OpTensorViewSetClipNV:             return "OpTensorViewSetClipNV";

    case Op::OpTypeCooperativeVectorNV:         return "OpTypeCooperativeVectorNV";
    case Op::OpCooperativeVectorMatrixMulNV:    return "OpCooperativeVectorMatrixMulNV";
    case Op::OpCooperativeVectorMatrixMulAddNV: return "OpCooperativeVectorMatrixMulAddNV";
    case Op::OpCooperativeVectorLoadNV:         return "OpCooperativeVectorLoadNV";
    case Op::OpCooperativeVectorStoreNV:        return "OpCooperativeVectorStoreNV";
    case Op::OpCooperativeVectorOuterProductAccumulateNV:   return "OpCooperativeVectorOuterProductAccumulateNV";
    case Op::OpCooperativeVectorReduceSumAccumulateNV:      return "OpCooperativeVectorReduceSumAccumulateNV";

    case Op::OpBeginInvocationInterlockEXT:     return "OpBeginInvocationInterlockEXT";
    case Op::OpEndInvocationInterlockEXT:       return "OpEndInvocationInterlockEXT";

    case Op::OpTypeHitObjectNV:                     return "OpTypeHitObjectNV";
    case Op::OpHitObjectTraceRayNV:                 return "OpHitObjectTraceRayNV";
    case Op::OpHitObjectTraceRayMotionNV:           return "OpHitObjectTraceRayMotionNV";
    case Op::OpHitObjectRecordHitNV:                return "OpHitObjectRecordHitNV";
    case Op::OpHitObjectRecordHitMotionNV:          return "OpHitObjectRecordHitMotionNV";
    case Op::OpHitObjectRecordHitWithIndexNV:       return "OpHitObjectRecordHitWithIndexNV";
    case Op::OpHitObjectRecordHitWithIndexMotionNV: return "OpHitObjectRecordHitWithIndexMotionNV";
    case Op::OpHitObjectRecordMissNV:               return "OpHitObjectRecordMissNV";
    case Op::OpHitObjectRecordMissMotionNV:         return "OpHitObjectRecordMissMotionNV";
    case Op::OpHitObjectRecordEmptyNV:              return "OpHitObjectRecordEmptyNV";
    case Op::OpHitObjectExecuteShaderNV:            return "OpHitObjectExecuteShaderNV";
    case Op::OpReorderThreadWithHintNV:             return "OpReorderThreadWithHintNV";
    case Op::OpReorderThreadWithHitObjectNV:        return "OpReorderThreadWithHitObjectNV";
    case Op::OpHitObjectGetCurrentTimeNV:           return "OpHitObjectGetCurrentTimeNV";
    case Op::OpHitObjectGetAttributesNV:            return "OpHitObjectGetAttributesNV";
    case Op::OpHitObjectGetHitKindNV:               return "OpHitObjectGetFrontFaceNV";
    case Op::OpHitObjectGetPrimitiveIndexNV:        return "OpHitObjectGetPrimitiveIndexNV";
    case Op::OpHitObjectGetGeometryIndexNV:         return "OpHitObjectGetGeometryIndexNV";
    case Op::OpHitObjectGetInstanceIdNV:            return "OpHitObjectGetInstanceIdNV";
    case Op::OpHitObjectGetInstanceCustomIndexNV:   return "OpHitObjectGetInstanceCustomIndexNV";
    case Op::OpHitObjectGetObjectRayDirectionNV:    return "OpHitObjectGetObjectRayDirectionNV";
    case Op::OpHitObjectGetObjectRayOriginNV:       return "OpHitObjectGetObjectRayOriginNV";
    case Op::OpHitObjectGetWorldRayDirectionNV:     return "OpHitObjectGetWorldRayDirectionNV";
    case Op::OpHitObjectGetWorldRayOriginNV:        return "OpHitObjectGetWorldRayOriginNV";
    case Op::OpHitObjectGetWorldToObjectNV:         return "OpHitObjectGetWorldToObjectNV";
    case Op::OpHitObjectGetObjectToWorldNV:         return "OpHitObjectGetObjectToWorldNV";
    case Op::OpHitObjectGetRayTMaxNV:               return "OpHitObjectGetRayTMaxNV";
    case Op::OpHitObjectGetRayTMinNV:               return "OpHitObjectGetRayTMinNV";
    case Op::OpHitObjectIsEmptyNV:                  return "OpHitObjectIsEmptyNV";
    case Op::OpHitObjectIsHitNV:                    return "OpHitObjectIsHitNV";
    case Op::OpHitObjectIsMissNV:                   return "OpHitObjectIsMissNV";
    case Op::OpHitObjectGetShaderBindingTableRecordIndexNV: return "OpHitObjectGetShaderBindingTableRecordIndexNV";
    case Op::OpHitObjectGetShaderRecordBufferHandleNV:   return "OpHitObjectGetShaderRecordBufferHandleNV";
    case Op::OpHitObjectGetClusterIdNV:             return "OpHitObjectGetClusterIdNV";
    case Op::OpHitObjectGetSpherePositionNV:        return "OpHitObjectGetSpherePositionNV";
    case Op::OpHitObjectGetSphereRadiusNV:          return "OpHitObjectGetSphereRadiusNV";
    case Op::OpHitObjectGetLSSPositionsNV:          return "OpHitObjectGetLSSPositionsNV";
    case Op::OpHitObjectGetLSSRadiiNV:              return "OpHitObjectGetLSSRadiiNV";
    case Op::OpHitObjectIsSphereHitNV:              return "OpHitObjectIsSphereHitNV";
    case Op::OpHitObjectIsLSSHitNV:                 return "OpHitObjectIsLSSHitNV";

    case Op::OpFetchMicroTriangleVertexBarycentricNV:       return "OpFetchMicroTriangleVertexBarycentricNV";
    case Op::OpFetchMicroTriangleVertexPositionNV:    return "OpFetchMicroTriangleVertexPositionNV";

    case Op::OpColorAttachmentReadEXT:          return "OpColorAttachmentReadEXT";
    case Op::OpDepthAttachmentReadEXT:          return "OpDepthAttachmentReadEXT";
    case Op::OpStencilAttachmentReadEXT:        return "OpStencilAttachmentReadEXT";

    case Op::OpImageSampleWeightedQCOM:         return "OpImageSampleWeightedQCOM";
    case Op::OpImageBoxFilterQCOM:              return "OpImageBoxFilterQCOM";
    case Op::OpImageBlockMatchSADQCOM:          return "OpImageBlockMatchSADQCOM";
    case Op::OpImageBlockMatchSSDQCOM:          return "OpImageBlockMatchSSDQCOM";
    case Op::OpImageBlockMatchWindowSSDQCOM:    return "OpImageBlockMatchWindowSSDQCOM";
    case Op::OpImageBlockMatchWindowSADQCOM:    return "OpImageBlockMatchWindowSADQCOM";
    case Op::OpImageBlockMatchGatherSSDQCOM:    return "OpImageBlockMatchGatherSSDQCOM";
    case Op::OpImageBlockMatchGatherSADQCOM:    return "OpImageBlockMatchGatherSADQCOM";

    case Op::OpConstantCompositeReplicateEXT: return "OpConstantCompositeReplicateEXT";
    case Op::OpSpecConstantCompositeReplicateEXT: return "OpSpecConstantCompositeReplicateEXT";
    case Op::OpCompositeConstructReplicateEXT: return "OpCompositeConstructReplicateEXT";

    case Op::OpSDotKHR: return "OpSDotKHR";
    case Op::OpUDotKHR: return "OpUDotKHR";
    case Op::OpSUDotKHR: return "OpSUDotKHR";
    case Op::OpSDotAccSatKHR: return "OpSDotAccSatKHR";
    case Op::OpUDotAccSatKHR: return "OpUDotAccSatKHR";
    case Op::OpSUDotAccSatKHR: return "OpSUDotAccSatKHR";

    default:
        return "Bad";
    }
}

// The set of objects that hold all the instruction/operand
// parameterization information.
InstructionParameters InstructionDesc[OpCodeMask + 1];
OperandParameters ExecutionModeOperands[ExecutionModeCeiling];
OperandParameters DecorationOperands[DecorationCeiling];

EnumDefinition OperandClassParams[OperandCount];
EnumParameters ExecutionModeParams[ExecutionModeCeiling];
EnumParameters ImageOperandsParams[ImageOperandsCeiling];
EnumParameters DecorationParams[DecorationCeiling];
EnumParameters LoopControlParams[FunctionControlCeiling];
EnumParameters SelectionControlParams[SelectControlCeiling];
EnumParameters FunctionControlParams[FunctionControlCeiling];
EnumParameters MemoryAccessParams[MemoryAccessCeiling];
EnumParameters CooperativeMatrixOperandsParams[CooperativeMatrixOperandsCeiling];
EnumParameters TensorAddressingOperandsParams[TensorAddressingOperandsCeiling];

// Set up all the parameterizing descriptions of the opcodes, operands, etc.
void Parameterize()
{
    // only do this once.
    static std::once_flag initialized;
    std::call_once(initialized, [](){

        // Exceptions to having a result <id> and a resulting type <id>.
        // (Everything is initialized to have both).

        InstructionDesc[Op::OpNop].setResultAndType(false, false);
        InstructionDesc[Op::OpSource].setResultAndType(false, false);
        InstructionDesc[Op::OpSourceContinued].setResultAndType(false, false);
        InstructionDesc[Op::OpSourceExtension].setResultAndType(false, false);
        InstructionDesc[Op::OpExtension].setResultAndType(false, false);
        InstructionDesc[Op::OpExtInstImport].setResultAndType(true, false);
        InstructionDesc[Op::OpCapability].setResultAndType(false, false);
        InstructionDesc[Op::OpMemoryModel].setResultAndType(false, false);
        InstructionDesc[Op::OpEntryPoint].setResultAndType(false, false);
        InstructionDesc[Op::OpExecutionMode].setResultAndType(false, false);
        InstructionDesc[Op::OpExecutionModeId].setResultAndType(false, false);
        InstructionDesc[Op::OpTypeVoid].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeBool].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeInt].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeFloat].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeVector].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeMatrix].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeImage].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeSampler].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeSampledImage].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeArray].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeRuntimeArray].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeStruct].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeOpaque].setResultAndType(true, false);
        InstructionDesc[Op::OpTypePointer].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeForwardPointer].setResultAndType(false, false);
        InstructionDesc[Op::OpTypeFunction].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeEvent].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeDeviceEvent].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeReserveId].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeQueue].setResultAndType(true, false);
        InstructionDesc[Op::OpTypePipe].setResultAndType(true, false);
        InstructionDesc[Op::OpFunctionEnd].setResultAndType(false, false);
        InstructionDesc[Op::OpStore].setResultAndType(false, false);
        InstructionDesc[Op::OpImageWrite].setResultAndType(false, false);
        InstructionDesc[Op::OpDecorationGroup].setResultAndType(true, false);
        InstructionDesc[Op::OpDecorate].setResultAndType(false, false);
        InstructionDesc[Op::OpDecorateId].setResultAndType(false, false);
        InstructionDesc[Op::OpDecorateStringGOOGLE].setResultAndType(false, false);
        InstructionDesc[Op::OpMemberDecorate].setResultAndType(false, false);
        InstructionDesc[Op::OpMemberDecorateStringGOOGLE].setResultAndType(false, false);
        InstructionDesc[Op::OpGroupDecorate].setResultAndType(false, false);
        InstructionDesc[Op::OpGroupMemberDecorate].setResultAndType(false, false);
        InstructionDesc[Op::OpName].setResultAndType(false, false);
        InstructionDesc[Op::OpMemberName].setResultAndType(false, false);
        InstructionDesc[Op::OpString].setResultAndType(true, false);
        InstructionDesc[Op::OpLine].setResultAndType(false, false);
        InstructionDesc[Op::OpNoLine].setResultAndType(false, false);
        InstructionDesc[Op::OpCopyMemory].setResultAndType(false, false);
        InstructionDesc[Op::OpCopyMemorySized].setResultAndType(false, false);
        InstructionDesc[Op::OpEmitVertex].setResultAndType(false, false);
        InstructionDesc[Op::OpEndPrimitive].setResultAndType(false, false);
        InstructionDesc[Op::OpEmitStreamVertex].setResultAndType(false, false);
        InstructionDesc[Op::OpEndStreamPrimitive].setResultAndType(false, false);
        InstructionDesc[Op::OpControlBarrier].setResultAndType(false, false);
        InstructionDesc[Op::OpMemoryBarrier].setResultAndType(false, false);
        InstructionDesc[Op::OpAtomicStore].setResultAndType(false, false);
        InstructionDesc[Op::OpLoopMerge].setResultAndType(false, false);
        InstructionDesc[Op::OpSelectionMerge].setResultAndType(false, false);
        InstructionDesc[Op::OpLabel].setResultAndType(true, false);
        InstructionDesc[Op::OpBranch].setResultAndType(false, false);
        InstructionDesc[Op::OpBranchConditional].setResultAndType(false, false);
        InstructionDesc[Op::OpSwitch].setResultAndType(false, false);
        InstructionDesc[Op::OpKill].setResultAndType(false, false);
        InstructionDesc[Op::OpTerminateInvocation].setResultAndType(false, false);
        InstructionDesc[Op::OpReturn].setResultAndType(false, false);
        InstructionDesc[Op::OpReturnValue].setResultAndType(false, false);
        InstructionDesc[Op::OpUnreachable].setResultAndType(false, false);
        InstructionDesc[Op::OpLifetimeStart].setResultAndType(false, false);
        InstructionDesc[Op::OpLifetimeStop].setResultAndType(false, false);
        InstructionDesc[Op::OpCommitReadPipe].setResultAndType(false, false);
        InstructionDesc[Op::OpCommitWritePipe].setResultAndType(false, false);
        InstructionDesc[Op::OpGroupCommitWritePipe].setResultAndType(false, false);
        InstructionDesc[Op::OpGroupCommitReadPipe].setResultAndType(false, false);
        InstructionDesc[Op::OpCaptureEventProfilingInfo].setResultAndType(false, false);
        InstructionDesc[Op::OpSetUserEventStatus].setResultAndType(false, false);
        InstructionDesc[Op::OpRetainEvent].setResultAndType(false, false);
        InstructionDesc[Op::OpReleaseEvent].setResultAndType(false, false);
        InstructionDesc[Op::OpGroupWaitEvents].setResultAndType(false, false);
        InstructionDesc[Op::OpAtomicFlagClear].setResultAndType(false, false);
        InstructionDesc[Op::OpModuleProcessed].setResultAndType(false, false);
        InstructionDesc[Op::OpTypeCooperativeMatrixNV].setResultAndType(true, false);
        InstructionDesc[Op::OpCooperativeMatrixStoreNV].setResultAndType(false, false);
        InstructionDesc[Op::OpTypeCooperativeMatrixKHR].setResultAndType(true, false);
        InstructionDesc[Op::OpCooperativeMatrixStoreKHR].setResultAndType(false, false);
        InstructionDesc[Op::OpBeginInvocationInterlockEXT].setResultAndType(false, false);
        InstructionDesc[Op::OpEndInvocationInterlockEXT].setResultAndType(false, false);
        InstructionDesc[Op::OpAssumeTrueKHR].setResultAndType(false, false);
        InstructionDesc[Op::OpTypeTensorLayoutNV].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeTensorViewNV].setResultAndType(true, false);
        InstructionDesc[Op::OpCooperativeMatrixStoreTensorNV].setResultAndType(false, false);
        InstructionDesc[Op::OpTypeCooperativeVectorNV].setResultAndType(true, false);
        InstructionDesc[Op::OpCooperativeVectorStoreNV].setResultAndType(false, false);
        InstructionDesc[Op::OpCooperativeVectorOuterProductAccumulateNV].setResultAndType(false, false);
        InstructionDesc[Op::OpCooperativeVectorReduceSumAccumulateNV].setResultAndType(false, false);

        // Specific additional context-dependent operands

        ExecutionModeOperands[ExecutionMode::Invocations].push(OperandLiteralNumber, "'Number of <<Invocation,invocations>>'");

        ExecutionModeOperands[ExecutionMode::LocalSize].push(OperandLiteralNumber, "'x size'");
        ExecutionModeOperands[ExecutionMode::LocalSize].push(OperandLiteralNumber, "'y size'");
        ExecutionModeOperands[ExecutionMode::LocalSize].push(OperandLiteralNumber, "'z size'");

        ExecutionModeOperands[ExecutionMode::LocalSizeHint].push(OperandLiteralNumber, "'x size'");
        ExecutionModeOperands[ExecutionMode::LocalSizeHint].push(OperandLiteralNumber, "'y size'");
        ExecutionModeOperands[ExecutionMode::LocalSizeHint].push(OperandLiteralNumber, "'z size'");

        ExecutionModeOperands[ExecutionMode::OutputVertices].push(OperandLiteralNumber, "'Vertex count'");
        ExecutionModeOperands[ExecutionMode::VecTypeHint].push(OperandLiteralNumber, "'Vector type'");

        DecorationOperands[Decoration::Stream].push(OperandLiteralNumber, "'Stream Number'");
        DecorationOperands[Decoration::Location].push(OperandLiteralNumber, "'Location'");
        DecorationOperands[Decoration::Component].push(OperandLiteralNumber, "'Component'");
        DecorationOperands[Decoration::Index].push(OperandLiteralNumber, "'Index'");
        DecorationOperands[Decoration::Binding].push(OperandLiteralNumber, "'Binding Point'");
        DecorationOperands[Decoration::DescriptorSet].push(OperandLiteralNumber, "'Descriptor Set'");
        DecorationOperands[Decoration::Offset].push(OperandLiteralNumber, "'Byte Offset'");
        DecorationOperands[Decoration::XfbBuffer].push(OperandLiteralNumber, "'XFB Buffer Number'");
        DecorationOperands[Decoration::XfbStride].push(OperandLiteralNumber, "'XFB Stride'");
        DecorationOperands[Decoration::ArrayStride].push(OperandLiteralNumber, "'Array Stride'");
        DecorationOperands[Decoration::MatrixStride].push(OperandLiteralNumber, "'Matrix Stride'");
        DecorationOperands[Decoration::BuiltIn].push(OperandLiteralNumber, "See <<BuiltIn,*BuiltIn*>>");
        DecorationOperands[Decoration::FPRoundingMode].push(OperandFPRoundingMode, "'Floating-Point Rounding Mode'");
        DecorationOperands[Decoration::FPFastMathMode].push(OperandFPFastMath, "'Fast-Math Mode'");
        DecorationOperands[Decoration::LinkageAttributes].push(OperandLiteralString, "'Name'");
        DecorationOperands[Decoration::LinkageAttributes].push(OperandLinkageType, "'Linkage Type'");
        DecorationOperands[Decoration::FuncParamAttr].push(OperandFuncParamAttr, "'Function Parameter Attribute'");
        DecorationOperands[Decoration::SpecId].push(OperandLiteralNumber, "'Specialization Constant ID'");
        DecorationOperands[Decoration::InputAttachmentIndex].push(OperandLiteralNumber, "'Attachment Index'");
        DecorationOperands[Decoration::Alignment].push(OperandLiteralNumber, "'Alignment'");

        OperandClassParams[OperandSource].set(0, SourceString, nullptr);
        OperandClassParams[OperandExecutionModel].set(0, ExecutionModelString, nullptr);
        OperandClassParams[OperandAddressing].set(0, AddressingString, nullptr);
        OperandClassParams[OperandMemory].set(0, MemoryString, nullptr);
        OperandClassParams[OperandExecutionMode].set(ExecutionModeCeiling, ExecutionModeString, ExecutionModeParams);
        OperandClassParams[OperandExecutionMode].setOperands(ExecutionModeOperands);
        OperandClassParams[OperandStorage].set(0, StorageClassString, nullptr);
        OperandClassParams[OperandDimensionality].set(0, DimensionString, nullptr);
        OperandClassParams[OperandSamplerAddressingMode].set(0, SamplerAddressingModeString, nullptr);
        OperandClassParams[OperandSamplerFilterMode].set(0, SamplerFilterModeString, nullptr);
        OperandClassParams[OperandSamplerImageFormat].set(0, ImageFormatString, nullptr);
        OperandClassParams[OperandImageChannelOrder].set(0, ImageChannelOrderString, nullptr);
        OperandClassParams[OperandImageChannelDataType].set(0, ImageChannelDataTypeString, nullptr);
        OperandClassParams[OperandImageOperands].set(ImageOperandsCeiling, ImageOperandsString, ImageOperandsParams, true);
        OperandClassParams[OperandFPFastMath].set(0, FPFastMathString, nullptr, true);
        OperandClassParams[OperandFPRoundingMode].set(0, FPRoundingModeString, nullptr);
        OperandClassParams[OperandLinkageType].set(0, LinkageTypeString, nullptr);
        OperandClassParams[OperandFuncParamAttr].set(0, FuncParamAttrString, nullptr);
        OperandClassParams[OperandAccessQualifier].set(0, AccessQualifierString, nullptr);
        OperandClassParams[OperandDecoration].set(DecorationCeiling, DecorationString, DecorationParams);
        OperandClassParams[OperandDecoration].setOperands(DecorationOperands);
        OperandClassParams[OperandBuiltIn].set(0, BuiltInString, nullptr);
        OperandClassParams[OperandSelect].set(SelectControlCeiling, SelectControlString, SelectionControlParams, true);
        OperandClassParams[OperandLoop].set(LoopControlCeiling, LoopControlString, LoopControlParams, true);
        OperandClassParams[OperandFunction].set(FunctionControlCeiling, FunctionControlString, FunctionControlParams, true);
        OperandClassParams[OperandMemorySemantics].set(0, MemorySemanticsString, nullptr, true);
        OperandClassParams[OperandMemoryAccess].set(MemoryAccessCeiling, MemoryAccessString, MemoryAccessParams, true);
        OperandClassParams[OperandScope].set(0, ScopeString, nullptr);
        OperandClassParams[OperandGroupOperation].set(0, GroupOperationString, nullptr);
        OperandClassParams[OperandKernelEnqueueFlags].set(0, KernelEnqueueFlagsString, nullptr);
        OperandClassParams[OperandKernelProfilingInfo].set(0, KernelProfilingInfoString, nullptr, true);
        OperandClassParams[OperandCapability].set(0, CapabilityString, nullptr);
        OperandClassParams[OperandCooperativeMatrixOperands].set(CooperativeMatrixOperandsCeiling, CooperativeMatrixOperandsString, CooperativeMatrixOperandsParams, true);
        OperandClassParams[OperandTensorAddressingOperands].set(TensorAddressingOperandsCeiling, TensorAddressingOperandsString, TensorAddressingOperandsParams, true);
        OperandClassParams[OperandOpcode].set(OpCodeMask + 1, OpcodeString, nullptr);

        // set name of operator, an initial set of <id> style operands, and the description

        InstructionDesc[Op::OpSource].operands.push(OperandSource, "");
        InstructionDesc[Op::OpSource].operands.push(OperandLiteralNumber, "'Version'");
        InstructionDesc[Op::OpSource].operands.push(OperandId, "'File'", true);
        InstructionDesc[Op::OpSource].operands.push(OperandLiteralString, "'Source'", true);

        InstructionDesc[Op::OpSourceContinued].operands.push(OperandLiteralString, "'Continued Source'");

        InstructionDesc[Op::OpSourceExtension].operands.push(OperandLiteralString, "'Extension'");

        InstructionDesc[Op::OpName].operands.push(OperandId, "'Target'");
        InstructionDesc[Op::OpName].operands.push(OperandLiteralString, "'Name'");

        InstructionDesc[Op::OpMemberName].operands.push(OperandId, "'Type'");
        InstructionDesc[Op::OpMemberName].operands.push(OperandLiteralNumber, "'Member'");
        InstructionDesc[Op::OpMemberName].operands.push(OperandLiteralString, "'Name'");

        InstructionDesc[Op::OpString].operands.push(OperandLiteralString, "'String'");

        InstructionDesc[Op::OpLine].operands.push(OperandId, "'File'");
        InstructionDesc[Op::OpLine].operands.push(OperandLiteralNumber, "'Line'");
        InstructionDesc[Op::OpLine].operands.push(OperandLiteralNumber, "'Column'");

        InstructionDesc[Op::OpExtension].operands.push(OperandLiteralString, "'Name'");

        InstructionDesc[Op::OpExtInstImport].operands.push(OperandLiteralString, "'Name'");

        InstructionDesc[Op::OpCapability].operands.push(OperandCapability, "'Capability'");

        InstructionDesc[Op::OpMemoryModel].operands.push(OperandAddressing, "");
        InstructionDesc[Op::OpMemoryModel].operands.push(OperandMemory, "");

        InstructionDesc[Op::OpEntryPoint].operands.push(OperandExecutionModel, "");
        InstructionDesc[Op::OpEntryPoint].operands.push(OperandId, "'Entry Point'");
        InstructionDesc[Op::OpEntryPoint].operands.push(OperandLiteralString, "'Name'");
        InstructionDesc[Op::OpEntryPoint].operands.push(OperandVariableIds, "'Interface'");

        InstructionDesc[Op::OpExecutionMode].operands.push(OperandId, "'Entry Point'");
        InstructionDesc[Op::OpExecutionMode].operands.push(OperandExecutionMode, "'Mode'");
        InstructionDesc[Op::OpExecutionMode].operands.push(OperandOptionalLiteral, "See <<Execution_Mode,Execution Mode>>");

        InstructionDesc[Op::OpExecutionModeId].operands.push(OperandId, "'Entry Point'");
        InstructionDesc[Op::OpExecutionModeId].operands.push(OperandExecutionMode, "'Mode'");
        InstructionDesc[Op::OpExecutionModeId].operands.push(OperandVariableIds, "See <<Execution_Mode,Execution Mode>>");

        InstructionDesc[Op::OpTypeInt].operands.push(OperandLiteralNumber, "'Width'");
        InstructionDesc[Op::OpTypeInt].operands.push(OperandLiteralNumber, "'Signedness'");

        InstructionDesc[Op::OpTypeFloat].operands.push(OperandLiteralNumber, "'Width'");
        InstructionDesc[Op::OpTypeFloat].operands.push(OperandOptionalLiteral, "'FP Encoding'");

        InstructionDesc[Op::OpTypeVector].operands.push(OperandId, "'Component Type'");
        InstructionDesc[Op::OpTypeVector].operands.push(OperandLiteralNumber, "'Component Count'");

        InstructionDesc[Op::OpTypeMatrix].operands.push(OperandId, "'Column Type'");
        InstructionDesc[Op::OpTypeMatrix].operands.push(OperandLiteralNumber, "'Column Count'");

        InstructionDesc[Op::OpTypeImage].operands.push(OperandId, "'Sampled Type'");
        InstructionDesc[Op::OpTypeImage].operands.push(OperandDimensionality, "");
        InstructionDesc[Op::OpTypeImage].operands.push(OperandLiteralNumber, "'Depth'");
        InstructionDesc[Op::OpTypeImage].operands.push(OperandLiteralNumber, "'Arrayed'");
        InstructionDesc[Op::OpTypeImage].operands.push(OperandLiteralNumber, "'MS'");
        InstructionDesc[Op::OpTypeImage].operands.push(OperandLiteralNumber, "'Sampled'");
        InstructionDesc[Op::OpTypeImage].operands.push(OperandSamplerImageFormat, "");
        InstructionDesc[Op::OpTypeImage].operands.push(OperandAccessQualifier, "", true);

        InstructionDesc[Op::OpTypeSampledImage].operands.push(OperandId, "'Image Type'");

        InstructionDesc[Op::OpTypeArray].operands.push(OperandId, "'Element Type'");
        InstructionDesc[Op::OpTypeArray].operands.push(OperandId, "'Length'");

        InstructionDesc[Op::OpTypeRuntimeArray].operands.push(OperandId, "'Element Type'");

        InstructionDesc[Op::OpTypeStruct].operands.push(OperandVariableIds, "'Member 0 type', +\n'member 1 type', +\n...");

        InstructionDesc[Op::OpTypeOpaque].operands.push(OperandLiteralString, "The name of the opaque type.");

        InstructionDesc[Op::OpTypePointer].operands.push(OperandStorage, "");
        InstructionDesc[Op::OpTypePointer].operands.push(OperandId, "'Type'");

        InstructionDesc[Op::OpTypeForwardPointer].operands.push(OperandId, "'Pointer Type'");
        InstructionDesc[Op::OpTypeForwardPointer].operands.push(OperandStorage, "");

        InstructionDesc[Op::OpTypePipe].operands.push(OperandAccessQualifier, "'Qualifier'");

        InstructionDesc[Op::OpTypeFunction].operands.push(OperandId, "'Return Type'");
        InstructionDesc[Op::OpTypeFunction].operands.push(OperandVariableIds, "'Parameter 0 Type', +\n'Parameter 1 Type', +\n...");

        InstructionDesc[Op::OpConstant].operands.push(OperandVariableLiterals, "'Value'");

        InstructionDesc[Op::OpConstantComposite].operands.push(OperandVariableIds, "'Constituents'");

        InstructionDesc[Op::OpConstantSampler].operands.push(OperandSamplerAddressingMode, "");
        InstructionDesc[Op::OpConstantSampler].operands.push(OperandLiteralNumber, "'Param'");
        InstructionDesc[Op::OpConstantSampler].operands.push(OperandSamplerFilterMode, "");

        InstructionDesc[Op::OpSpecConstant].operands.push(OperandVariableLiterals, "'Value'");

        InstructionDesc[Op::OpSpecConstantComposite].operands.push(OperandVariableIds, "'Constituents'");

        InstructionDesc[Op::OpSpecConstantOp].operands.push(OperandLiteralNumber, "'Opcode'");
        InstructionDesc[Op::OpSpecConstantOp].operands.push(OperandVariableIds, "'Operands'");

        InstructionDesc[Op::OpVariable].operands.push(OperandStorage, "");
        InstructionDesc[Op::OpVariable].operands.push(OperandId, "'Initializer'", true);

        InstructionDesc[Op::OpFunction].operands.push(OperandFunction, "");
        InstructionDesc[Op::OpFunction].operands.push(OperandId, "'Function Type'");

        InstructionDesc[Op::OpFunctionCall].operands.push(OperandId, "'Function'");
        InstructionDesc[Op::OpFunctionCall].operands.push(OperandVariableIds, "'Argument 0', +\n'Argument 1', +\n...");

        InstructionDesc[Op::OpExtInst].operands.push(OperandId, "'Set'");
        InstructionDesc[Op::OpExtInst].operands.push(OperandLiteralNumber, "'Instruction'");
        InstructionDesc[Op::OpExtInst].operands.push(OperandVariableIds, "'Operand 1', +\n'Operand 2', +\n...");

        InstructionDesc[Op::OpExtInstWithForwardRefsKHR].operands.push(OperandId, "'Set'");
        InstructionDesc[Op::OpExtInstWithForwardRefsKHR].operands.push(OperandLiteralNumber, "'Instruction'");
        InstructionDesc[Op::OpExtInstWithForwardRefsKHR].operands.push(OperandVariableIds, "'Operand 1', +\n'Operand 2', +\n...");

        InstructionDesc[Op::OpLoad].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpLoad].operands.push(OperandMemoryAccess, "", true);
        InstructionDesc[Op::OpLoad].operands.push(OperandLiteralNumber, "", true);
        InstructionDesc[Op::OpLoad].operands.push(OperandId, "", true);

        InstructionDesc[Op::OpStore].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpStore].operands.push(OperandId, "'Object'");
        InstructionDesc[Op::OpStore].operands.push(OperandMemoryAccess, "", true);
        InstructionDesc[Op::OpStore].operands.push(OperandLiteralNumber, "", true);
        InstructionDesc[Op::OpStore].operands.push(OperandId, "", true);

        InstructionDesc[Op::OpPhi].operands.push(OperandVariableIds, "'Variable, Parent, ...'");

        InstructionDesc[Op::OpDecorate].operands.push(OperandId, "'Target'");
        InstructionDesc[Op::OpDecorate].operands.push(OperandDecoration, "");
        InstructionDesc[Op::OpDecorate].operands.push(OperandVariableLiterals, "See <<Decoration,'Decoration'>>.");

        InstructionDesc[Op::OpDecorateId].operands.push(OperandId, "'Target'");
        InstructionDesc[Op::OpDecorateId].operands.push(OperandDecoration, "");
        InstructionDesc[Op::OpDecorateId].operands.push(OperandVariableIds, "See <<Decoration,'Decoration'>>.");

        InstructionDesc[Op::OpDecorateStringGOOGLE].operands.push(OperandId, "'Target'");
        InstructionDesc[Op::OpDecorateStringGOOGLE].operands.push(OperandDecoration, "");
        InstructionDesc[Op::OpDecorateStringGOOGLE].operands.push(OperandVariableLiteralStrings, "'Literal Strings'");

        InstructionDesc[Op::OpMemberDecorate].operands.push(OperandId, "'Structure Type'");
        InstructionDesc[Op::OpMemberDecorate].operands.push(OperandLiteralNumber, "'Member'");
        InstructionDesc[Op::OpMemberDecorate].operands.push(OperandDecoration, "");
        InstructionDesc[Op::OpMemberDecorate].operands.push(OperandVariableLiterals, "See <<Decoration,'Decoration'>>.");

        InstructionDesc[Op::OpMemberDecorateStringGOOGLE].operands.push(OperandId, "'Structure Type'");
        InstructionDesc[Op::OpMemberDecorateStringGOOGLE].operands.push(OperandLiteralNumber, "'Member'");
        InstructionDesc[Op::OpMemberDecorateStringGOOGLE].operands.push(OperandDecoration, "");
        InstructionDesc[Op::OpMemberDecorateStringGOOGLE].operands.push(OperandVariableLiteralStrings, "'Literal Strings'");

        InstructionDesc[Op::OpGroupDecorate].operands.push(OperandId, "'Decoration Group'");
        InstructionDesc[Op::OpGroupDecorate].operands.push(OperandVariableIds, "'Targets'");

        InstructionDesc[Op::OpGroupMemberDecorate].operands.push(OperandId, "'Decoration Group'");
        InstructionDesc[Op::OpGroupMemberDecorate].operands.push(OperandVariableIdLiteral, "'Targets'");

        InstructionDesc[Op::OpVectorExtractDynamic].operands.push(OperandId, "'Vector'");
        InstructionDesc[Op::OpVectorExtractDynamic].operands.push(OperandId, "'Index'");

        InstructionDesc[Op::OpVectorInsertDynamic].operands.push(OperandId, "'Vector'");
        InstructionDesc[Op::OpVectorInsertDynamic].operands.push(OperandId, "'Component'");
        InstructionDesc[Op::OpVectorInsertDynamic].operands.push(OperandId, "'Index'");

        InstructionDesc[Op::OpVectorShuffle].operands.push(OperandId, "'Vector 1'");
        InstructionDesc[Op::OpVectorShuffle].operands.push(OperandId, "'Vector 2'");
        InstructionDesc[Op::OpVectorShuffle].operands.push(OperandVariableLiterals, "'Components'");

        InstructionDesc[Op::OpCompositeConstruct].operands.push(OperandVariableIds, "'Constituents'");

        InstructionDesc[Op::OpCompositeExtract].operands.push(OperandId, "'Composite'");
        InstructionDesc[Op::OpCompositeExtract].operands.push(OperandVariableLiterals, "'Indexes'");

        InstructionDesc[Op::OpCompositeInsert].operands.push(OperandId, "'Object'");
        InstructionDesc[Op::OpCompositeInsert].operands.push(OperandId, "'Composite'");
        InstructionDesc[Op::OpCompositeInsert].operands.push(OperandVariableLiterals, "'Indexes'");

        InstructionDesc[Op::OpCopyObject].operands.push(OperandId, "'Operand'");

        InstructionDesc[Op::OpCopyMemory].operands.push(OperandId, "'Target'");
        InstructionDesc[Op::OpCopyMemory].operands.push(OperandId, "'Source'");
        InstructionDesc[Op::OpCopyMemory].operands.push(OperandMemoryAccess, "", true);

        InstructionDesc[Op::OpCopyMemorySized].operands.push(OperandId, "'Target'");
        InstructionDesc[Op::OpCopyMemorySized].operands.push(OperandId, "'Source'");
        InstructionDesc[Op::OpCopyMemorySized].operands.push(OperandId, "'Size'");
        InstructionDesc[Op::OpCopyMemorySized].operands.push(OperandMemoryAccess, "", true);

        InstructionDesc[Op::OpSampledImage].operands.push(OperandId, "'Image'");
        InstructionDesc[Op::OpSampledImage].operands.push(OperandId, "'Sampler'");

        InstructionDesc[Op::OpImage].operands.push(OperandId, "'Sampled Image'");

        InstructionDesc[Op::OpImageRead].operands.push(OperandId, "'Image'");
        InstructionDesc[Op::OpImageRead].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageRead].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageRead].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageWrite].operands.push(OperandId, "'Image'");
        InstructionDesc[Op::OpImageWrite].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageWrite].operands.push(OperandId, "'Texel'");
        InstructionDesc[Op::OpImageWrite].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageWrite].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSampleImplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSampleImplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSampleImplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSampleImplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSampleExplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSampleExplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSampleExplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSampleExplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSampleDrefImplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSampleDrefImplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSampleDrefImplicitLod].operands.push(OperandId, "'D~ref~'");
        InstructionDesc[Op::OpImageSampleDrefImplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSampleDrefImplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSampleDrefExplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSampleDrefExplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSampleDrefExplicitLod].operands.push(OperandId, "'D~ref~'");
        InstructionDesc[Op::OpImageSampleDrefExplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSampleDrefExplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSampleProjImplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSampleProjImplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSampleProjImplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSampleProjImplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSampleProjExplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSampleProjExplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSampleProjExplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSampleProjExplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSampleProjDrefImplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSampleProjDrefImplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSampleProjDrefImplicitLod].operands.push(OperandId, "'D~ref~'");
        InstructionDesc[Op::OpImageSampleProjDrefImplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSampleProjDrefImplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSampleProjDrefExplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSampleProjDrefExplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSampleProjDrefExplicitLod].operands.push(OperandId, "'D~ref~'");
        InstructionDesc[Op::OpImageSampleProjDrefExplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSampleProjDrefExplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageFetch].operands.push(OperandId, "'Image'");
        InstructionDesc[Op::OpImageFetch].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageFetch].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageFetch].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageGather].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageGather].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageGather].operands.push(OperandId, "'Component'");
        InstructionDesc[Op::OpImageGather].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageGather].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageDrefGather].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageDrefGather].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageDrefGather].operands.push(OperandId, "'D~ref~'");
        InstructionDesc[Op::OpImageDrefGather].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageDrefGather].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseSampleImplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSparseSampleImplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseSampleImplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseSampleImplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseSampleExplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSparseSampleExplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseSampleExplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseSampleExplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseSampleDrefImplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSparseSampleDrefImplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseSampleDrefImplicitLod].operands.push(OperandId, "'D~ref~'");
        InstructionDesc[Op::OpImageSparseSampleDrefImplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseSampleDrefImplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseSampleDrefExplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSparseSampleDrefExplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseSampleDrefExplicitLod].operands.push(OperandId, "'D~ref~'");
        InstructionDesc[Op::OpImageSparseSampleDrefExplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseSampleDrefExplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseSampleProjImplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSparseSampleProjImplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseSampleProjImplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseSampleProjImplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseSampleProjExplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSparseSampleProjExplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseSampleProjExplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseSampleProjExplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseSampleProjDrefImplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSparseSampleProjDrefImplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseSampleProjDrefImplicitLod].operands.push(OperandId, "'D~ref~'");
        InstructionDesc[Op::OpImageSparseSampleProjDrefImplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseSampleProjDrefImplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseSampleProjDrefExplicitLod].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSparseSampleProjDrefExplicitLod].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseSampleProjDrefExplicitLod].operands.push(OperandId, "'D~ref~'");
        InstructionDesc[Op::OpImageSparseSampleProjDrefExplicitLod].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseSampleProjDrefExplicitLod].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseFetch].operands.push(OperandId, "'Image'");
        InstructionDesc[Op::OpImageSparseFetch].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseFetch].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseFetch].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseGather].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSparseGather].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseGather].operands.push(OperandId, "'Component'");
        InstructionDesc[Op::OpImageSparseGather].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseGather].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseDrefGather].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSparseDrefGather].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseDrefGather].operands.push(OperandId, "'D~ref~'");
        InstructionDesc[Op::OpImageSparseDrefGather].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseDrefGather].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseRead].operands.push(OperandId, "'Image'");
        InstructionDesc[Op::OpImageSparseRead].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSparseRead].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSparseRead].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpImageSparseTexelsResident].operands.push(OperandId, "'Resident Code'");

        InstructionDesc[Op::OpImageQuerySizeLod].operands.push(OperandId, "'Image'");
        InstructionDesc[Op::OpImageQuerySizeLod].operands.push(OperandId, "'Level of Detail'");

        InstructionDesc[Op::OpImageQuerySize].operands.push(OperandId, "'Image'");

        InstructionDesc[Op::OpImageQueryLod].operands.push(OperandId, "'Image'");
        InstructionDesc[Op::OpImageQueryLod].operands.push(OperandId, "'Coordinate'");

        InstructionDesc[Op::OpImageQueryLevels].operands.push(OperandId, "'Image'");

        InstructionDesc[Op::OpImageQuerySamples].operands.push(OperandId, "'Image'");

        InstructionDesc[Op::OpImageQueryFormat].operands.push(OperandId, "'Image'");

        InstructionDesc[Op::OpImageQueryOrder].operands.push(OperandId, "'Image'");

        InstructionDesc[Op::OpAccessChain].operands.push(OperandId, "'Base'");
        InstructionDesc[Op::OpAccessChain].operands.push(OperandVariableIds, "'Indexes'");

        InstructionDesc[Op::OpInBoundsAccessChain].operands.push(OperandId, "'Base'");
        InstructionDesc[Op::OpInBoundsAccessChain].operands.push(OperandVariableIds, "'Indexes'");

        InstructionDesc[Op::OpPtrAccessChain].operands.push(OperandId, "'Base'");
        InstructionDesc[Op::OpPtrAccessChain].operands.push(OperandId, "'Element'");
        InstructionDesc[Op::OpPtrAccessChain].operands.push(OperandVariableIds, "'Indexes'");

        InstructionDesc[Op::OpInBoundsPtrAccessChain].operands.push(OperandId, "'Base'");
        InstructionDesc[Op::OpInBoundsPtrAccessChain].operands.push(OperandId, "'Element'");
        InstructionDesc[Op::OpInBoundsPtrAccessChain].operands.push(OperandVariableIds, "'Indexes'");

        InstructionDesc[Op::OpSNegate].operands.push(OperandId, "'Operand'");

        InstructionDesc[Op::OpFNegate].operands.push(OperandId, "'Operand'");

        InstructionDesc[Op::OpNot].operands.push(OperandId, "'Operand'");

        InstructionDesc[Op::OpAny].operands.push(OperandId, "'Vector'");

        InstructionDesc[Op::OpAll].operands.push(OperandId, "'Vector'");

        InstructionDesc[Op::OpConvertFToU].operands.push(OperandId, "'Float Value'");

        InstructionDesc[Op::OpConvertFToS].operands.push(OperandId, "'Float Value'");

        InstructionDesc[Op::OpConvertSToF].operands.push(OperandId, "'Signed Value'");

        InstructionDesc[Op::OpConvertUToF].operands.push(OperandId, "'Unsigned Value'");

        InstructionDesc[Op::OpUConvert].operands.push(OperandId, "'Unsigned Value'");

        InstructionDesc[Op::OpSConvert].operands.push(OperandId, "'Signed Value'");

        InstructionDesc[Op::OpFConvert].operands.push(OperandId, "'Float Value'");

        InstructionDesc[Op::OpSatConvertSToU].operands.push(OperandId, "'Signed Value'");

        InstructionDesc[Op::OpSatConvertUToS].operands.push(OperandId, "'Unsigned Value'");

        InstructionDesc[Op::OpConvertPtrToU].operands.push(OperandId, "'Pointer'");

        InstructionDesc[Op::OpConvertUToPtr].operands.push(OperandId, "'Integer Value'");

        InstructionDesc[Op::OpPtrCastToGeneric].operands.push(OperandId, "'Pointer'");

        InstructionDesc[Op::OpGenericCastToPtr].operands.push(OperandId, "'Pointer'");

        InstructionDesc[Op::OpGenericCastToPtrExplicit].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpGenericCastToPtrExplicit].operands.push(OperandStorage, "'Storage'");

        InstructionDesc[Op::OpGenericPtrMemSemantics].operands.push(OperandId, "'Pointer'");

        InstructionDesc[Op::OpBitcast].operands.push(OperandId, "'Operand'");

        InstructionDesc[Op::OpQuantizeToF16].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpTranspose].operands.push(OperandId, "'Matrix'");

        InstructionDesc[Op::OpCopyLogical].operands.push(OperandId, "'Operand'");

        InstructionDesc[Op::OpIsNan].operands.push(OperandId, "'x'");

        InstructionDesc[Op::OpIsInf].operands.push(OperandId, "'x'");

        InstructionDesc[Op::OpIsFinite].operands.push(OperandId, "'x'");

        InstructionDesc[Op::OpIsNormal].operands.push(OperandId, "'x'");

        InstructionDesc[Op::OpSignBitSet].operands.push(OperandId, "'x'");

        InstructionDesc[Op::OpLessOrGreater].operands.push(OperandId, "'x'");
        InstructionDesc[Op::OpLessOrGreater].operands.push(OperandId, "'y'");

        InstructionDesc[Op::OpOrdered].operands.push(OperandId, "'x'");
        InstructionDesc[Op::OpOrdered].operands.push(OperandId, "'y'");

        InstructionDesc[Op::OpUnordered].operands.push(OperandId, "'x'");
        InstructionDesc[Op::OpUnordered].operands.push(OperandId, "'y'");

        InstructionDesc[Op::OpArrayLength].operands.push(OperandId, "'Structure'");
        InstructionDesc[Op::OpArrayLength].operands.push(OperandLiteralNumber, "'Array member'");

        InstructionDesc[Op::OpIAdd].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpIAdd].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFAdd].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFAdd].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpISub].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpISub].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFSub].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFSub].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpIMul].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpIMul].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFMul].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFMul].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpUDiv].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpUDiv].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpSDiv].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpSDiv].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFDiv].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFDiv].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpUMod].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpUMod].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpSRem].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpSRem].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpSMod].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpSMod].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFRem].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFRem].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFMod].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFMod].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpVectorTimesScalar].operands.push(OperandId, "'Vector'");
        InstructionDesc[Op::OpVectorTimesScalar].operands.push(OperandId, "'Scalar'");

        InstructionDesc[Op::OpMatrixTimesScalar].operands.push(OperandId, "'Matrix'");
        InstructionDesc[Op::OpMatrixTimesScalar].operands.push(OperandId, "'Scalar'");

        InstructionDesc[Op::OpVectorTimesMatrix].operands.push(OperandId, "'Vector'");
        InstructionDesc[Op::OpVectorTimesMatrix].operands.push(OperandId, "'Matrix'");

        InstructionDesc[Op::OpMatrixTimesVector].operands.push(OperandId, "'Matrix'");
        InstructionDesc[Op::OpMatrixTimesVector].operands.push(OperandId, "'Vector'");

        InstructionDesc[Op::OpMatrixTimesMatrix].operands.push(OperandId, "'LeftMatrix'");
        InstructionDesc[Op::OpMatrixTimesMatrix].operands.push(OperandId, "'RightMatrix'");

        InstructionDesc[Op::OpOuterProduct].operands.push(OperandId, "'Vector 1'");
        InstructionDesc[Op::OpOuterProduct].operands.push(OperandId, "'Vector 2'");

        InstructionDesc[Op::OpDot].operands.push(OperandId, "'Vector 1'");
        InstructionDesc[Op::OpDot].operands.push(OperandId, "'Vector 2'");

        InstructionDesc[Op::OpIAddCarry].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpIAddCarry].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpISubBorrow].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpISubBorrow].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpUMulExtended].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpUMulExtended].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpSMulExtended].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpSMulExtended].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpShiftRightLogical].operands.push(OperandId, "'Base'");
        InstructionDesc[Op::OpShiftRightLogical].operands.push(OperandId, "'Shift'");

        InstructionDesc[Op::OpShiftRightArithmetic].operands.push(OperandId, "'Base'");
        InstructionDesc[Op::OpShiftRightArithmetic].operands.push(OperandId, "'Shift'");

        InstructionDesc[Op::OpShiftLeftLogical].operands.push(OperandId, "'Base'");
        InstructionDesc[Op::OpShiftLeftLogical].operands.push(OperandId, "'Shift'");

        InstructionDesc[Op::OpLogicalOr].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpLogicalOr].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpLogicalAnd].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpLogicalAnd].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpLogicalEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpLogicalEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpLogicalNotEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpLogicalNotEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpLogicalNot].operands.push(OperandId, "'Operand'");

        InstructionDesc[Op::OpBitwiseOr].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpBitwiseOr].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpBitwiseXor].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpBitwiseXor].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpBitwiseAnd].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpBitwiseAnd].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpBitFieldInsert].operands.push(OperandId, "'Base'");
        InstructionDesc[Op::OpBitFieldInsert].operands.push(OperandId, "'Insert'");
        InstructionDesc[Op::OpBitFieldInsert].operands.push(OperandId, "'Offset'");
        InstructionDesc[Op::OpBitFieldInsert].operands.push(OperandId, "'Count'");

        InstructionDesc[Op::OpBitFieldSExtract].operands.push(OperandId, "'Base'");
        InstructionDesc[Op::OpBitFieldSExtract].operands.push(OperandId, "'Offset'");
        InstructionDesc[Op::OpBitFieldSExtract].operands.push(OperandId, "'Count'");

        InstructionDesc[Op::OpBitFieldUExtract].operands.push(OperandId, "'Base'");
        InstructionDesc[Op::OpBitFieldUExtract].operands.push(OperandId, "'Offset'");
        InstructionDesc[Op::OpBitFieldUExtract].operands.push(OperandId, "'Count'");

        InstructionDesc[Op::OpBitReverse].operands.push(OperandId, "'Base'");

        InstructionDesc[Op::OpBitCount].operands.push(OperandId, "'Base'");

        InstructionDesc[Op::OpSelect].operands.push(OperandId, "'Condition'");
        InstructionDesc[Op::OpSelect].operands.push(OperandId, "'Object 1'");
        InstructionDesc[Op::OpSelect].operands.push(OperandId, "'Object 2'");

        InstructionDesc[Op::OpIEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpIEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFOrdEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFOrdEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFUnordEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFUnordEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpINotEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpINotEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFOrdNotEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFOrdNotEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFUnordNotEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFUnordNotEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpULessThan].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpULessThan].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpSLessThan].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpSLessThan].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFOrdLessThan].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFOrdLessThan].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFUnordLessThan].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFUnordLessThan].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpUGreaterThan].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpUGreaterThan].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpSGreaterThan].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpSGreaterThan].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFOrdGreaterThan].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFOrdGreaterThan].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFUnordGreaterThan].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFUnordGreaterThan].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpULessThanEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpULessThanEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpSLessThanEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpSLessThanEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFOrdLessThanEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFOrdLessThanEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFUnordLessThanEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFUnordLessThanEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpUGreaterThanEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpUGreaterThanEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpSGreaterThanEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpSGreaterThanEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFOrdGreaterThanEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFOrdGreaterThanEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpFUnordGreaterThanEqual].operands.push(OperandId, "'Operand 1'");
        InstructionDesc[Op::OpFUnordGreaterThanEqual].operands.push(OperandId, "'Operand 2'");

        InstructionDesc[Op::OpDPdx].operands.push(OperandId, "'P'");

        InstructionDesc[Op::OpDPdy].operands.push(OperandId, "'P'");

        InstructionDesc[Op::OpFwidth].operands.push(OperandId, "'P'");

        InstructionDesc[Op::OpDPdxFine].operands.push(OperandId, "'P'");

        InstructionDesc[Op::OpDPdyFine].operands.push(OperandId, "'P'");

        InstructionDesc[Op::OpFwidthFine].operands.push(OperandId, "'P'");

        InstructionDesc[Op::OpDPdxCoarse].operands.push(OperandId, "'P'");

        InstructionDesc[Op::OpDPdyCoarse].operands.push(OperandId, "'P'");

        InstructionDesc[Op::OpFwidthCoarse].operands.push(OperandId, "'P'");

        InstructionDesc[Op::OpEmitStreamVertex].operands.push(OperandId, "'Stream'");

        InstructionDesc[Op::OpEndStreamPrimitive].operands.push(OperandId, "'Stream'");

        InstructionDesc[Op::OpControlBarrier].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpControlBarrier].operands.push(OperandScope, "'Memory'");
        InstructionDesc[Op::OpControlBarrier].operands.push(OperandMemorySemantics, "'Semantics'");

        InstructionDesc[Op::OpMemoryBarrier].operands.push(OperandScope, "'Memory'");
        InstructionDesc[Op::OpMemoryBarrier].operands.push(OperandMemorySemantics, "'Semantics'");

        InstructionDesc[Op::OpImageTexelPointer].operands.push(OperandId, "'Image'");
        InstructionDesc[Op::OpImageTexelPointer].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageTexelPointer].operands.push(OperandId, "'Sample'");

        InstructionDesc[Op::OpAtomicLoad].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicLoad].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicLoad].operands.push(OperandMemorySemantics, "'Semantics'");

        InstructionDesc[Op::OpAtomicStore].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicStore].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicStore].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicStore].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicExchange].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicExchange].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicExchange].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicExchange].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicCompareExchange].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicCompareExchange].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicCompareExchange].operands.push(OperandMemorySemantics, "'Equal'");
        InstructionDesc[Op::OpAtomicCompareExchange].operands.push(OperandMemorySemantics, "'Unequal'");
        InstructionDesc[Op::OpAtomicCompareExchange].operands.push(OperandId, "'Value'");
        InstructionDesc[Op::OpAtomicCompareExchange].operands.push(OperandId, "'Comparator'");

        InstructionDesc[Op::OpAtomicCompareExchangeWeak].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicCompareExchangeWeak].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicCompareExchangeWeak].operands.push(OperandMemorySemantics, "'Equal'");
        InstructionDesc[Op::OpAtomicCompareExchangeWeak].operands.push(OperandMemorySemantics, "'Unequal'");
        InstructionDesc[Op::OpAtomicCompareExchangeWeak].operands.push(OperandId, "'Value'");
        InstructionDesc[Op::OpAtomicCompareExchangeWeak].operands.push(OperandId, "'Comparator'");

        InstructionDesc[Op::OpAtomicIIncrement].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicIIncrement].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicIIncrement].operands.push(OperandMemorySemantics, "'Semantics'");

        InstructionDesc[Op::OpAtomicIDecrement].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicIDecrement].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicIDecrement].operands.push(OperandMemorySemantics, "'Semantics'");

        InstructionDesc[Op::OpAtomicIAdd].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicIAdd].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicIAdd].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicIAdd].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicFAddEXT].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicFAddEXT].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicFAddEXT].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicFAddEXT].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAssumeTrueKHR].operands.push(OperandId, "'Condition'");

        InstructionDesc[Op::OpExpectKHR].operands.push(OperandId, "'Value'");
        InstructionDesc[Op::OpExpectKHR].operands.push(OperandId, "'ExpectedValue'");

        InstructionDesc[Op::OpAtomicISub].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicISub].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicISub].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicISub].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicUMin].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicUMin].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicUMin].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicUMin].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicUMax].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicUMax].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicUMax].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicUMax].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicSMin].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicSMin].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicSMin].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicSMin].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicSMax].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicSMax].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicSMax].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicSMax].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicFMinEXT].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicFMinEXT].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicFMinEXT].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicFMinEXT].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicFMaxEXT].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicFMaxEXT].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicFMaxEXT].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicFMaxEXT].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicAnd].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicAnd].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicAnd].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicAnd].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicOr].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicOr].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicOr].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicOr].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicXor].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicXor].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicXor].operands.push(OperandMemorySemantics, "'Semantics'");
        InstructionDesc[Op::OpAtomicXor].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpAtomicFlagTestAndSet].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicFlagTestAndSet].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicFlagTestAndSet].operands.push(OperandMemorySemantics, "'Semantics'");

        InstructionDesc[Op::OpAtomicFlagClear].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpAtomicFlagClear].operands.push(OperandScope, "'Scope'");
        InstructionDesc[Op::OpAtomicFlagClear].operands.push(OperandMemorySemantics, "'Semantics'");

        InstructionDesc[Op::OpLoopMerge].operands.push(OperandId, "'Merge Block'");
        InstructionDesc[Op::OpLoopMerge].operands.push(OperandId, "'Continue Target'");
        InstructionDesc[Op::OpLoopMerge].operands.push(OperandLoop, "");
        InstructionDesc[Op::OpLoopMerge].operands.push(OperandOptionalLiteral, "");

        InstructionDesc[Op::OpSelectionMerge].operands.push(OperandId, "'Merge Block'");
        InstructionDesc[Op::OpSelectionMerge].operands.push(OperandSelect, "");

        InstructionDesc[Op::OpBranch].operands.push(OperandId, "'Target Label'");

        InstructionDesc[Op::OpBranchConditional].operands.push(OperandId, "'Condition'");
        InstructionDesc[Op::OpBranchConditional].operands.push(OperandId, "'True Label'");
        InstructionDesc[Op::OpBranchConditional].operands.push(OperandId, "'False Label'");
        InstructionDesc[Op::OpBranchConditional].operands.push(OperandVariableLiterals, "'Branch weights'");

        InstructionDesc[Op::OpSwitch].operands.push(OperandId, "'Selector'");
        InstructionDesc[Op::OpSwitch].operands.push(OperandId, "'Default'");
        InstructionDesc[Op::OpSwitch].operands.push(OperandVariableLiteralId, "'Target'");


        InstructionDesc[Op::OpReturnValue].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpLifetimeStart].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpLifetimeStart].operands.push(OperandLiteralNumber, "'Size'");

        InstructionDesc[Op::OpLifetimeStop].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpLifetimeStop].operands.push(OperandLiteralNumber, "'Size'");

        InstructionDesc[Op::OpGroupAsyncCopy].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupAsyncCopy].operands.push(OperandId, "'Destination'");
        InstructionDesc[Op::OpGroupAsyncCopy].operands.push(OperandId, "'Source'");
        InstructionDesc[Op::OpGroupAsyncCopy].operands.push(OperandId, "'Num Elements'");
        InstructionDesc[Op::OpGroupAsyncCopy].operands.push(OperandId, "'Stride'");
        InstructionDesc[Op::OpGroupAsyncCopy].operands.push(OperandId, "'Event'");

        InstructionDesc[Op::OpGroupWaitEvents].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupWaitEvents].operands.push(OperandId, "'Num Events'");
        InstructionDesc[Op::OpGroupWaitEvents].operands.push(OperandId, "'Events List'");

        InstructionDesc[Op::OpGroupAll].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupAll].operands.push(OperandId, "'Predicate'");

        InstructionDesc[Op::OpGroupAny].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupAny].operands.push(OperandId, "'Predicate'");

        InstructionDesc[Op::OpGroupBroadcast].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupBroadcast].operands.push(OperandId, "'Value'");
        InstructionDesc[Op::OpGroupBroadcast].operands.push(OperandId, "'LocalId'");

        InstructionDesc[Op::OpGroupIAdd].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupIAdd].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupIAdd].operands.push(OperandId, "'X'");

        InstructionDesc[Op::OpGroupFAdd].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupFAdd].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupFAdd].operands.push(OperandId, "'X'");

        InstructionDesc[Op::OpGroupUMin].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupUMin].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupUMin].operands.push(OperandId, "'X'");

        InstructionDesc[Op::OpGroupSMin].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupSMin].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupSMin].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupFMin].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupFMin].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupFMin].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupUMax].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupUMax].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupUMax].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupSMax].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupSMax].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupSMax].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupFMax].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupFMax].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupFMax].operands.push(OperandId, "X");

        InstructionDesc[Op::OpReadPipe].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpReadPipe].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpReadPipe].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpReadPipe].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpWritePipe].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpWritePipe].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpWritePipe].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpWritePipe].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpReservedReadPipe].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpReservedReadPipe].operands.push(OperandId, "'Reserve Id'");
        InstructionDesc[Op::OpReservedReadPipe].operands.push(OperandId, "'Index'");
        InstructionDesc[Op::OpReservedReadPipe].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpReservedReadPipe].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpReservedReadPipe].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpReservedWritePipe].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpReservedWritePipe].operands.push(OperandId, "'Reserve Id'");
        InstructionDesc[Op::OpReservedWritePipe].operands.push(OperandId, "'Index'");
        InstructionDesc[Op::OpReservedWritePipe].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpReservedWritePipe].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpReservedWritePipe].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpReserveReadPipePackets].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpReserveReadPipePackets].operands.push(OperandId, "'Num Packets'");
        InstructionDesc[Op::OpReserveReadPipePackets].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpReserveReadPipePackets].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpReserveWritePipePackets].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpReserveWritePipePackets].operands.push(OperandId, "'Num Packets'");
        InstructionDesc[Op::OpReserveWritePipePackets].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpReserveWritePipePackets].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpCommitReadPipe].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpCommitReadPipe].operands.push(OperandId, "'Reserve Id'");
        InstructionDesc[Op::OpCommitReadPipe].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpCommitReadPipe].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpCommitWritePipe].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpCommitWritePipe].operands.push(OperandId, "'Reserve Id'");
        InstructionDesc[Op::OpCommitWritePipe].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpCommitWritePipe].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpIsValidReserveId].operands.push(OperandId, "'Reserve Id'");

        InstructionDesc[Op::OpGetNumPipePackets].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpGetNumPipePackets].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpGetNumPipePackets].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpGetMaxPipePackets].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpGetMaxPipePackets].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpGetMaxPipePackets].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpGroupReserveReadPipePackets].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupReserveReadPipePackets].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpGroupReserveReadPipePackets].operands.push(OperandId, "'Num Packets'");
        InstructionDesc[Op::OpGroupReserveReadPipePackets].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpGroupReserveReadPipePackets].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpGroupReserveWritePipePackets].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupReserveWritePipePackets].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpGroupReserveWritePipePackets].operands.push(OperandId, "'Num Packets'");
        InstructionDesc[Op::OpGroupReserveWritePipePackets].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpGroupReserveWritePipePackets].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpGroupCommitReadPipe].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupCommitReadPipe].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpGroupCommitReadPipe].operands.push(OperandId, "'Reserve Id'");
        InstructionDesc[Op::OpGroupCommitReadPipe].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpGroupCommitReadPipe].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpGroupCommitWritePipe].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupCommitWritePipe].operands.push(OperandId, "'Pipe'");
        InstructionDesc[Op::OpGroupCommitWritePipe].operands.push(OperandId, "'Reserve Id'");
        InstructionDesc[Op::OpGroupCommitWritePipe].operands.push(OperandId, "'Packet Size'");
        InstructionDesc[Op::OpGroupCommitWritePipe].operands.push(OperandId, "'Packet Alignment'");

        InstructionDesc[Op::OpBuildNDRange].operands.push(OperandId, "'GlobalWorkSize'");
        InstructionDesc[Op::OpBuildNDRange].operands.push(OperandId, "'LocalWorkSize'");
        InstructionDesc[Op::OpBuildNDRange].operands.push(OperandId, "'GlobalWorkOffset'");

        InstructionDesc[Op::OpCaptureEventProfilingInfo].operands.push(OperandId, "'Event'");
        InstructionDesc[Op::OpCaptureEventProfilingInfo].operands.push(OperandId, "'Profiling Info'");
        InstructionDesc[Op::OpCaptureEventProfilingInfo].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpSetUserEventStatus].operands.push(OperandId, "'Event'");
        InstructionDesc[Op::OpSetUserEventStatus].operands.push(OperandId, "'Status'");

        InstructionDesc[Op::OpIsValidEvent].operands.push(OperandId, "'Event'");

        InstructionDesc[Op::OpRetainEvent].operands.push(OperandId, "'Event'");

        InstructionDesc[Op::OpReleaseEvent].operands.push(OperandId, "'Event'");

        InstructionDesc[Op::OpGetKernelWorkGroupSize].operands.push(OperandId, "'Invoke'");
        InstructionDesc[Op::OpGetKernelWorkGroupSize].operands.push(OperandId, "'Param'");
        InstructionDesc[Op::OpGetKernelWorkGroupSize].operands.push(OperandId, "'Param Size'");
        InstructionDesc[Op::OpGetKernelWorkGroupSize].operands.push(OperandId, "'Param Align'");

        InstructionDesc[Op::OpGetKernelPreferredWorkGroupSizeMultiple].operands.push(OperandId, "'Invoke'");
        InstructionDesc[Op::OpGetKernelPreferredWorkGroupSizeMultiple].operands.push(OperandId, "'Param'");
        InstructionDesc[Op::OpGetKernelPreferredWorkGroupSizeMultiple].operands.push(OperandId, "'Param Size'");
        InstructionDesc[Op::OpGetKernelPreferredWorkGroupSizeMultiple].operands.push(OperandId, "'Param Align'");

        InstructionDesc[Op::OpGetKernelNDrangeSubGroupCount].operands.push(OperandId, "'ND Range'");
        InstructionDesc[Op::OpGetKernelNDrangeSubGroupCount].operands.push(OperandId, "'Invoke'");
        InstructionDesc[Op::OpGetKernelNDrangeSubGroupCount].operands.push(OperandId, "'Param'");
        InstructionDesc[Op::OpGetKernelNDrangeSubGroupCount].operands.push(OperandId, "'Param Size'");
        InstructionDesc[Op::OpGetKernelNDrangeSubGroupCount].operands.push(OperandId, "'Param Align'");

        InstructionDesc[Op::OpGetKernelNDrangeMaxSubGroupSize].operands.push(OperandId, "'ND Range'");
        InstructionDesc[Op::OpGetKernelNDrangeMaxSubGroupSize].operands.push(OperandId, "'Invoke'");
        InstructionDesc[Op::OpGetKernelNDrangeMaxSubGroupSize].operands.push(OperandId, "'Param'");
        InstructionDesc[Op::OpGetKernelNDrangeMaxSubGroupSize].operands.push(OperandId, "'Param Size'");
        InstructionDesc[Op::OpGetKernelNDrangeMaxSubGroupSize].operands.push(OperandId, "'Param Align'");

        InstructionDesc[Op::OpEnqueueKernel].operands.push(OperandId, "'Queue'");
        InstructionDesc[Op::OpEnqueueKernel].operands.push(OperandId, "'Flags'");
        InstructionDesc[Op::OpEnqueueKernel].operands.push(OperandId, "'ND Range'");
        InstructionDesc[Op::OpEnqueueKernel].operands.push(OperandId, "'Num Events'");
        InstructionDesc[Op::OpEnqueueKernel].operands.push(OperandId, "'Wait Events'");
        InstructionDesc[Op::OpEnqueueKernel].operands.push(OperandId, "'Ret Event'");
        InstructionDesc[Op::OpEnqueueKernel].operands.push(OperandId, "'Invoke'");
        InstructionDesc[Op::OpEnqueueKernel].operands.push(OperandId, "'Param'");
        InstructionDesc[Op::OpEnqueueKernel].operands.push(OperandId, "'Param Size'");
        InstructionDesc[Op::OpEnqueueKernel].operands.push(OperandId, "'Param Align'");
        InstructionDesc[Op::OpEnqueueKernel].operands.push(OperandVariableIds, "'Local Size'");

        InstructionDesc[Op::OpEnqueueMarker].operands.push(OperandId, "'Queue'");
        InstructionDesc[Op::OpEnqueueMarker].operands.push(OperandId, "'Num Events'");
        InstructionDesc[Op::OpEnqueueMarker].operands.push(OperandId, "'Wait Events'");
        InstructionDesc[Op::OpEnqueueMarker].operands.push(OperandId, "'Ret Event'");

        InstructionDesc[Op::OpGroupNonUniformElect].operands.push(OperandScope, "'Execution'");

        InstructionDesc[Op::OpGroupNonUniformAll].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformAll].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupNonUniformAny].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformAny].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupNonUniformAllEqual].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformAllEqual].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupNonUniformBroadcast].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformBroadcast].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformBroadcast].operands.push(OperandId, "ID");

        InstructionDesc[Op::OpGroupNonUniformBroadcastFirst].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformBroadcastFirst].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupNonUniformBallot].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformBallot].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupNonUniformInverseBallot].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformInverseBallot].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupNonUniformBallotBitExtract].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformBallotBitExtract].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformBallotBitExtract].operands.push(OperandId, "Bit");

        InstructionDesc[Op::OpGroupNonUniformBallotBitCount].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformBallotBitCount].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformBallotBitCount].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupNonUniformBallotFindLSB].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformBallotFindLSB].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupNonUniformBallotFindMSB].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformBallotFindMSB].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupNonUniformShuffle].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformShuffle].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformShuffle].operands.push(OperandId, "'Id'");

        InstructionDesc[Op::OpGroupNonUniformShuffleXor].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformShuffleXor].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformShuffleXor].operands.push(OperandId, "Mask");

        InstructionDesc[Op::OpGroupNonUniformShuffleUp].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformShuffleUp].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformShuffleUp].operands.push(OperandId, "Offset");

        InstructionDesc[Op::OpGroupNonUniformShuffleDown].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformShuffleDown].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformShuffleDown].operands.push(OperandId, "Offset");

        InstructionDesc[Op::OpGroupNonUniformIAdd].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformIAdd].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformIAdd].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformIAdd].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformFAdd].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformFAdd].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformFAdd].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformFAdd].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformIMul].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformIMul].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformIMul].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformIMul].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformFMul].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformFMul].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformFMul].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformFMul].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformSMin].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformSMin].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformSMin].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformSMin].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformUMin].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformUMin].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformUMin].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformUMin].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformFMin].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformFMin].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformFMin].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformFMin].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformSMax].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformSMax].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformSMax].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformSMax].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformUMax].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformUMax].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformUMax].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformUMax].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformFMax].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformFMax].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformFMax].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformFMax].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformBitwiseAnd].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformBitwiseAnd].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformBitwiseAnd].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformBitwiseAnd].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformBitwiseOr].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformBitwiseOr].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformBitwiseOr].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformBitwiseOr].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformBitwiseXor].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformBitwiseXor].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformBitwiseXor].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformBitwiseXor].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformLogicalAnd].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformLogicalAnd].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformLogicalAnd].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformLogicalAnd].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformLogicalOr].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformLogicalOr].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformLogicalOr].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformLogicalOr].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformLogicalXor].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformLogicalXor].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupNonUniformLogicalXor].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformLogicalXor].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpGroupNonUniformQuadBroadcast].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformQuadBroadcast].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformQuadBroadcast].operands.push(OperandId, "'Id'");

        InstructionDesc[Op::OpGroupNonUniformQuadSwap].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformQuadSwap].operands.push(OperandId, "X");
        InstructionDesc[Op::OpGroupNonUniformQuadSwap].operands.push(OperandId, "'Direction'");

        InstructionDesc[Op::OpSubgroupBallotKHR].operands.push(OperandId, "'Predicate'");

        InstructionDesc[Op::OpSubgroupFirstInvocationKHR].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpSubgroupAnyKHR].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpSubgroupAnyKHR].operands.push(OperandId, "'Predicate'");

        InstructionDesc[Op::OpSubgroupAllKHR].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpSubgroupAllKHR].operands.push(OperandId, "'Predicate'");

        InstructionDesc[Op::OpSubgroupAllEqualKHR].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpSubgroupAllEqualKHR].operands.push(OperandId, "'Predicate'");

        InstructionDesc[Op::OpGroupNonUniformRotateKHR].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupNonUniformRotateKHR].operands.push(OperandId, "'X'");
        InstructionDesc[Op::OpGroupNonUniformRotateKHR].operands.push(OperandId, "'Delta'");
        InstructionDesc[Op::OpGroupNonUniformRotateKHR].operands.push(OperandId, "'ClusterSize'", true);

        InstructionDesc[Op::OpSubgroupReadInvocationKHR].operands.push(OperandId, "'Value'");
        InstructionDesc[Op::OpSubgroupReadInvocationKHR].operands.push(OperandId, "'Index'");

        InstructionDesc[Op::OpModuleProcessed].operands.push(OperandLiteralString, "'process'");

        InstructionDesc[Op::OpGroupIAddNonUniformAMD].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupIAddNonUniformAMD].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupIAddNonUniformAMD].operands.push(OperandId, "'X'");

        InstructionDesc[Op::OpGroupFAddNonUniformAMD].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupFAddNonUniformAMD].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupFAddNonUniformAMD].operands.push(OperandId, "'X'");

        InstructionDesc[Op::OpGroupUMinNonUniformAMD].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupUMinNonUniformAMD].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupUMinNonUniformAMD].operands.push(OperandId, "'X'");

        InstructionDesc[Op::OpGroupSMinNonUniformAMD].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupSMinNonUniformAMD].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupSMinNonUniformAMD].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupFMinNonUniformAMD].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupFMinNonUniformAMD].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupFMinNonUniformAMD].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupUMaxNonUniformAMD].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupUMaxNonUniformAMD].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupUMaxNonUniformAMD].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupSMaxNonUniformAMD].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupSMaxNonUniformAMD].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupSMaxNonUniformAMD].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupFMaxNonUniformAMD].operands.push(OperandScope, "'Execution'");
        InstructionDesc[Op::OpGroupFMaxNonUniformAMD].operands.push(OperandGroupOperation, "'Operation'");
        InstructionDesc[Op::OpGroupFMaxNonUniformAMD].operands.push(OperandId, "X");

        InstructionDesc[Op::OpFragmentMaskFetchAMD].operands.push(OperandId, "'Image'");
        InstructionDesc[Op::OpFragmentMaskFetchAMD].operands.push(OperandId, "'Coordinate'");

        InstructionDesc[Op::OpFragmentFetchAMD].operands.push(OperandId, "'Image'");
        InstructionDesc[Op::OpFragmentFetchAMD].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpFragmentFetchAMD].operands.push(OperandId, "'Fragment Index'");

        InstructionDesc[Op::OpGroupNonUniformPartitionNV].operands.push(OperandId, "X");

        InstructionDesc[Op::OpGroupNonUniformQuadAllKHR].operands.push(OperandId, "'Predicate'");
        InstructionDesc[Op::OpGroupNonUniformQuadAnyKHR].operands.push(OperandId, "'Predicate'");
        InstructionDesc[Op::OpTypeAccelerationStructureKHR].setResultAndType(true, false);

        InstructionDesc[Op::OpTraceNV].operands.push(OperandId, "'Acceleration Structure'");
        InstructionDesc[Op::OpTraceNV].operands.push(OperandId, "'Ray Flags'");
        InstructionDesc[Op::OpTraceNV].operands.push(OperandId, "'Cull Mask'");
        InstructionDesc[Op::OpTraceNV].operands.push(OperandId, "'SBT Record Offset'");
        InstructionDesc[Op::OpTraceNV].operands.push(OperandId, "'SBT Record Stride'");
        InstructionDesc[Op::OpTraceNV].operands.push(OperandId, "'Miss Index'");
        InstructionDesc[Op::OpTraceNV].operands.push(OperandId, "'Ray Origin'");
        InstructionDesc[Op::OpTraceNV].operands.push(OperandId, "'TMin'");
        InstructionDesc[Op::OpTraceNV].operands.push(OperandId, "'Ray Direction'");
        InstructionDesc[Op::OpTraceNV].operands.push(OperandId, "'TMax'");
        InstructionDesc[Op::OpTraceNV].operands.push(OperandId, "'Payload'");
        InstructionDesc[Op::OpTraceNV].setResultAndType(false, false);

        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'Acceleration Structure'");
        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'Ray Flags'");
        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'Cull Mask'");
        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'SBT Record Offset'");
        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'SBT Record Stride'");
        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'Miss Index'");
        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'Ray Origin'");
        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'TMin'");
        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'Ray Direction'");
        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'TMax'");
        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'Time'");
        InstructionDesc[Op::OpTraceRayMotionNV].operands.push(OperandId, "'Payload'");
        InstructionDesc[Op::OpTraceRayMotionNV].setResultAndType(false, false);

        InstructionDesc[Op::OpTraceRayKHR].operands.push(OperandId, "'Acceleration Structure'");
        InstructionDesc[Op::OpTraceRayKHR].operands.push(OperandId, "'Ray Flags'");
        InstructionDesc[Op::OpTraceRayKHR].operands.push(OperandId, "'Cull Mask'");
        InstructionDesc[Op::OpTraceRayKHR].operands.push(OperandId, "'SBT Record Offset'");
        InstructionDesc[Op::OpTraceRayKHR].operands.push(OperandId, "'SBT Record Stride'");
        InstructionDesc[Op::OpTraceRayKHR].operands.push(OperandId, "'Miss Index'");
        InstructionDesc[Op::OpTraceRayKHR].operands.push(OperandId, "'Ray Origin'");
        InstructionDesc[Op::OpTraceRayKHR].operands.push(OperandId, "'TMin'");
        InstructionDesc[Op::OpTraceRayKHR].operands.push(OperandId, "'Ray Direction'");
        InstructionDesc[Op::OpTraceRayKHR].operands.push(OperandId, "'TMax'");
        InstructionDesc[Op::OpTraceRayKHR].operands.push(OperandId, "'Payload'");
        InstructionDesc[Op::OpTraceRayKHR].setResultAndType(false, false);

        InstructionDesc[Op::OpReportIntersectionKHR].operands.push(OperandId, "'Hit Parameter'");
        InstructionDesc[Op::OpReportIntersectionKHR].operands.push(OperandId, "'Hit Kind'");

        InstructionDesc[Op::OpIgnoreIntersectionNV].setResultAndType(false, false);

        InstructionDesc[Op::OpIgnoreIntersectionKHR].setResultAndType(false, false);

        InstructionDesc[Op::OpTerminateRayNV].setResultAndType(false, false);

        InstructionDesc[Op::OpTerminateRayKHR].setResultAndType(false, false);

        InstructionDesc[Op::OpExecuteCallableNV].operands.push(OperandId, "SBT Record Index");
        InstructionDesc[Op::OpExecuteCallableNV].operands.push(OperandId, "CallableData ID");
        InstructionDesc[Op::OpExecuteCallableNV].setResultAndType(false, false);

        InstructionDesc[Op::OpExecuteCallableKHR].operands.push(OperandId, "SBT Record Index");
        InstructionDesc[Op::OpExecuteCallableKHR].operands.push(OperandId, "CallableData");
        InstructionDesc[Op::OpExecuteCallableKHR].setResultAndType(false, false);

        InstructionDesc[Op::OpConvertUToAccelerationStructureKHR].operands.push(OperandId, "Value");
        InstructionDesc[Op::OpConvertUToAccelerationStructureKHR].setResultAndType(true, true);

        // Ray Query
        InstructionDesc[Op::OpTypeAccelerationStructureKHR].setResultAndType(true, false);
        InstructionDesc[Op::OpTypeRayQueryKHR].setResultAndType(true, false);

        InstructionDesc[Op::OpRayQueryInitializeKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryInitializeKHR].operands.push(OperandId, "'AccelerationS'");
        InstructionDesc[Op::OpRayQueryInitializeKHR].operands.push(OperandId, "'RayFlags'");
        InstructionDesc[Op::OpRayQueryInitializeKHR].operands.push(OperandId, "'CullMask'");
        InstructionDesc[Op::OpRayQueryInitializeKHR].operands.push(OperandId, "'Origin'");
        InstructionDesc[Op::OpRayQueryInitializeKHR].operands.push(OperandId, "'Tmin'");
        InstructionDesc[Op::OpRayQueryInitializeKHR].operands.push(OperandId, "'Direction'");
        InstructionDesc[Op::OpRayQueryInitializeKHR].operands.push(OperandId, "'Tmax'");
        InstructionDesc[Op::OpRayQueryInitializeKHR].setResultAndType(false, false);

        InstructionDesc[Op::OpRayQueryTerminateKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryTerminateKHR].setResultAndType(false, false);

        InstructionDesc[Op::OpRayQueryGenerateIntersectionKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGenerateIntersectionKHR].operands.push(OperandId, "'THit'");
        InstructionDesc[Op::OpRayQueryGenerateIntersectionKHR].setResultAndType(false, false);

        InstructionDesc[Op::OpRayQueryConfirmIntersectionKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryConfirmIntersectionKHR].setResultAndType(false, false);

        InstructionDesc[Op::OpRayQueryProceedKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryProceedKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionTypeKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionTypeKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionTypeKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetRayTMinKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetRayTMinKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetRayFlagsKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetRayFlagsKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionTKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionTKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionTKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionInstanceCustomIndexKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionInstanceIdKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionInstanceIdKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionInstanceIdKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionGeometryIndexKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionGeometryIndexKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionGeometryIndexKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionPrimitiveIndexKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionPrimitiveIndexKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionPrimitiveIndexKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionBarycentricsKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionBarycentricsKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionBarycentricsKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionFrontFaceKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionFrontFaceKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionFrontFaceKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionObjectRayDirectionKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionObjectRayDirectionKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionObjectRayDirectionKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionObjectRayOriginKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionObjectRayOriginKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionObjectRayOriginKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetWorldRayDirectionKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetWorldRayDirectionKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetWorldRayOriginKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetWorldRayOriginKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionObjectToWorldKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionObjectToWorldKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionObjectToWorldKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionWorldToObjectKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionWorldToObjectKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionWorldToObjectKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionTriangleVertexPositionsKHR].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionClusterIdNV].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionClusterIdNV].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionClusterIdNV].setResultAndType(true, true);
        InstructionDesc[Op::OpRayQueryGetIntersectionSpherePositionNV].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionSpherePositionNV].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionSpherePositionNV].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionSphereRadiusNV].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionSphereRadiusNV].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionSphereRadiusNV].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionLSSHitValueNV].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionLSSHitValueNV].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionLSSHitValueNV].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionLSSPositionsNV].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionLSSPositionsNV].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionLSSPositionsNV].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryGetIntersectionLSSRadiiNV].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryGetIntersectionLSSRadiiNV].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryGetIntersectionLSSRadiiNV].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryIsSphereHitNV].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryIsSphereHitNV].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryIsSphereHitNV].setResultAndType(true, true);

        InstructionDesc[Op::OpRayQueryIsLSSHitNV].operands.push(OperandId, "'RayQuery'");
        InstructionDesc[Op::OpRayQueryIsLSSHitNV].operands.push(OperandId, "'Committed'");
        InstructionDesc[Op::OpRayQueryIsLSSHitNV].setResultAndType(true, true);

        InstructionDesc[Op::OpImageSampleFootprintNV].operands.push(OperandId, "'Sampled Image'");
        InstructionDesc[Op::OpImageSampleFootprintNV].operands.push(OperandId, "'Coordinate'");
        InstructionDesc[Op::OpImageSampleFootprintNV].operands.push(OperandId, "'Granularity'");
        InstructionDesc[Op::OpImageSampleFootprintNV].operands.push(OperandId, "'Coarse'");
        InstructionDesc[Op::OpImageSampleFootprintNV].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSampleFootprintNV].operands.push(OperandVariableIds, "", true);

        InstructionDesc[Op::OpWritePackedPrimitiveIndices4x8NV].operands.push(OperandId, "'Index Offset'");
        InstructionDesc[Op::OpWritePackedPrimitiveIndices4x8NV].operands.push(OperandId, "'Packed Indices'");

        InstructionDesc[Op::OpEmitMeshTasksEXT].operands.push(OperandId, "'groupCountX'");
        InstructionDesc[Op::OpEmitMeshTasksEXT].operands.push(OperandId, "'groupCountY'");
        InstructionDesc[Op::OpEmitMeshTasksEXT].operands.push(OperandId, "'groupCountZ'");
        InstructionDesc[Op::OpEmitMeshTasksEXT].operands.push(OperandId, "'Payload'");
        InstructionDesc[Op::OpEmitMeshTasksEXT].setResultAndType(false, false);

        InstructionDesc[Op::OpSetMeshOutputsEXT].operands.push(OperandId, "'vertexCount'");
        InstructionDesc[Op::OpSetMeshOutputsEXT].operands.push(OperandId, "'primitiveCount'");
        InstructionDesc[Op::OpSetMeshOutputsEXT].setResultAndType(false, false);


        InstructionDesc[Op::OpTypeCooperativeMatrixNV].operands.push(OperandId, "'Component Type'");
        InstructionDesc[Op::OpTypeCooperativeMatrixNV].operands.push(OperandId, "'Scope'");
        InstructionDesc[Op::OpTypeCooperativeMatrixNV].operands.push(OperandId, "'Rows'");
        InstructionDesc[Op::OpTypeCooperativeMatrixNV].operands.push(OperandId, "'Columns'");

        InstructionDesc[Op::OpCooperativeMatrixLoadNV].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpCooperativeMatrixLoadNV].operands.push(OperandId, "'Stride'");
        InstructionDesc[Op::OpCooperativeMatrixLoadNV].operands.push(OperandId, "'Column Major'");
        InstructionDesc[Op::OpCooperativeMatrixLoadNV].operands.push(OperandMemoryAccess, "'Memory Access'");
        InstructionDesc[Op::OpCooperativeMatrixLoadNV].operands.push(OperandLiteralNumber, "", true);
        InstructionDesc[Op::OpCooperativeMatrixLoadNV].operands.push(OperandId, "", true);

        InstructionDesc[Op::OpCooperativeMatrixStoreNV].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpCooperativeMatrixStoreNV].operands.push(OperandId, "'Object'");
        InstructionDesc[Op::OpCooperativeMatrixStoreNV].operands.push(OperandId, "'Stride'");
        InstructionDesc[Op::OpCooperativeMatrixStoreNV].operands.push(OperandId, "'Column Major'");
        InstructionDesc[Op::OpCooperativeMatrixStoreNV].operands.push(OperandMemoryAccess, "'Memory Access'");
        InstructionDesc[Op::OpCooperativeMatrixStoreNV].operands.push(OperandLiteralNumber, "", true);
        InstructionDesc[Op::OpCooperativeMatrixStoreNV].operands.push(OperandId, "", true);

        InstructionDesc[Op::OpCooperativeMatrixMulAddNV].operands.push(OperandId, "'A'");
        InstructionDesc[Op::OpCooperativeMatrixMulAddNV].operands.push(OperandId, "'B'");
        InstructionDesc[Op::OpCooperativeMatrixMulAddNV].operands.push(OperandId, "'C'");

        InstructionDesc[Op::OpCooperativeMatrixLengthNV].operands.push(OperandId, "'Type'");

        InstructionDesc[Op::OpTypeCooperativeMatrixKHR].operands.push(OperandId, "'Component Type'");
        InstructionDesc[Op::OpTypeCooperativeMatrixKHR].operands.push(OperandId, "'Scope'");
        InstructionDesc[Op::OpTypeCooperativeMatrixKHR].operands.push(OperandId, "'Rows'");
        InstructionDesc[Op::OpTypeCooperativeMatrixKHR].operands.push(OperandId, "'Columns'");
        InstructionDesc[Op::OpTypeCooperativeMatrixKHR].operands.push(OperandId, "'Use'");

        InstructionDesc[Op::OpCooperativeMatrixLoadKHR].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpCooperativeMatrixLoadKHR].operands.push(OperandId, "'Memory Layout'");
        InstructionDesc[Op::OpCooperativeMatrixLoadKHR].operands.push(OperandId, "'Stride'");
        InstructionDesc[Op::OpCooperativeMatrixLoadKHR].operands.push(OperandMemoryAccess, "'Memory Access'");
        InstructionDesc[Op::OpCooperativeMatrixLoadKHR].operands.push(OperandLiteralNumber, "", true);
        InstructionDesc[Op::OpCooperativeMatrixLoadKHR].operands.push(OperandId, "", true);

        InstructionDesc[Op::OpCooperativeMatrixStoreKHR].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpCooperativeMatrixStoreKHR].operands.push(OperandId, "'Object'");
        InstructionDesc[Op::OpCooperativeMatrixStoreKHR].operands.push(OperandId, "'Memory Layout'");
        InstructionDesc[Op::OpCooperativeMatrixStoreKHR].operands.push(OperandId, "'Stride'");
        InstructionDesc[Op::OpCooperativeMatrixStoreKHR].operands.push(OperandMemoryAccess, "'Memory Access'");
        InstructionDesc[Op::OpCooperativeMatrixStoreKHR].operands.push(OperandLiteralNumber, "", true);
        InstructionDesc[Op::OpCooperativeMatrixStoreKHR].operands.push(OperandId, "", true);

        InstructionDesc[Op::OpCooperativeMatrixMulAddKHR].operands.push(OperandId, "'A'");
        InstructionDesc[Op::OpCooperativeMatrixMulAddKHR].operands.push(OperandId, "'B'");
        InstructionDesc[Op::OpCooperativeMatrixMulAddKHR].operands.push(OperandId, "'C'");
        InstructionDesc[Op::OpCooperativeMatrixMulAddKHR].operands.push(OperandCooperativeMatrixOperands, "'Cooperative Matrix Operands'", true);

        InstructionDesc[Op::OpCooperativeMatrixLengthKHR].operands.push(OperandId, "'Type'");

        InstructionDesc[Op::OpTypeCooperativeVectorNV].operands.push(OperandId, "'Component Type'");
        InstructionDesc[Op::OpTypeCooperativeVectorNV].operands.push(OperandId, "'Components'");

        InstructionDesc[Op::OpCooperativeVectorMatrixMulNV].operands.push(OperandId, "'Input'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulNV].operands.push(OperandId, "'InputInterpretation'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulNV].operands.push(OperandId, "'Matrix'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulNV].operands.push(OperandId, "'MatrixOffset'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulNV].operands.push(OperandId, "'MatrixInterpretation'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulNV].operands.push(OperandId, "'M'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulNV].operands.push(OperandId, "'K'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulNV].operands.push(OperandId, "'MemoryLayout'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulNV].operands.push(OperandId, "'Transpose'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulNV].operands.push(OperandId, "'MatrixStride'", true);
        InstructionDesc[Op::OpCooperativeVectorMatrixMulNV].operands.push(OperandCooperativeMatrixOperands, "'Cooperative Matrix Operands'", true);

        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'Input'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'InputInterpretation'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'Matrix'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'MatrixOffset'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'MatrixInterpretation'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'Bias'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'BiasOffset'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'BiasInterpretation'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'M'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'K'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'MemoryLayout'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'Transpose'");
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandId, "'MatrixStride'", true);
        InstructionDesc[Op::OpCooperativeVectorMatrixMulAddNV].operands.push(OperandCooperativeMatrixOperands, "'Cooperative Matrix Operands'", true);

        InstructionDesc[Op::OpCooperativeVectorLoadNV].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpCooperativeVectorLoadNV].operands.push(OperandId, "'Offset'");
        InstructionDesc[Op::OpCooperativeVectorLoadNV].operands.push(OperandMemoryAccess, "'Memory Access'");
        InstructionDesc[Op::OpCooperativeVectorLoadNV].operands.push(OperandLiteralNumber, "", true);
        InstructionDesc[Op::OpCooperativeVectorLoadNV].operands.push(OperandId, "", true);

        InstructionDesc[Op::OpCooperativeVectorStoreNV].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpCooperativeVectorStoreNV].operands.push(OperandId, "'Offset'");
        InstructionDesc[Op::OpCooperativeVectorStoreNV].operands.push(OperandId, "'Object'");
        InstructionDesc[Op::OpCooperativeVectorStoreNV].operands.push(OperandMemoryAccess, "'Memory Access'");
        InstructionDesc[Op::OpCooperativeVectorStoreNV].operands.push(OperandLiteralNumber, "", true);
        InstructionDesc[Op::OpCooperativeVectorStoreNV].operands.push(OperandId, "", true);

        InstructionDesc[Op::OpCooperativeVectorOuterProductAccumulateNV].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpCooperativeVectorOuterProductAccumulateNV].operands.push(OperandId, "'Offset'");
        InstructionDesc[Op::OpCooperativeVectorOuterProductAccumulateNV].operands.push(OperandId, "'A'");
        InstructionDesc[Op::OpCooperativeVectorOuterProductAccumulateNV].operands.push(OperandId, "'B'");
        InstructionDesc[Op::OpCooperativeVectorOuterProductAccumulateNV].operands.push(OperandId, "'MemoryLayout'");
        InstructionDesc[Op::OpCooperativeVectorOuterProductAccumulateNV].operands.push(OperandId, "'MatrixInterpretation'");
        InstructionDesc[Op::OpCooperativeVectorOuterProductAccumulateNV].operands.push(OperandId, "'MatrixStride'", true);

        InstructionDesc[Op::OpCooperativeVectorReduceSumAccumulateNV].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpCooperativeVectorReduceSumAccumulateNV].operands.push(OperandId, "'Offset'");
        InstructionDesc[Op::OpCooperativeVectorReduceSumAccumulateNV].operands.push(OperandId, "'V'");

        InstructionDesc[Op::OpDemoteToHelperInvocationEXT].setResultAndType(false, false);

        InstructionDesc[Op::OpReadClockKHR].operands.push(OperandScope, "'Scope'");

        InstructionDesc[Op::OpTypeHitObjectNV].setResultAndType(true, false);

        InstructionDesc[Op::OpHitObjectGetShaderRecordBufferHandleNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetShaderRecordBufferHandleNV].setResultAndType(true, true);

        InstructionDesc[Op::OpReorderThreadWithHintNV].operands.push(OperandId, "'Hint'");
        InstructionDesc[Op::OpReorderThreadWithHintNV].operands.push(OperandId, "'Bits'");
        InstructionDesc[Op::OpReorderThreadWithHintNV].setResultAndType(false, false);

        InstructionDesc[Op::OpReorderThreadWithHitObjectNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpReorderThreadWithHitObjectNV].operands.push(OperandId, "'Hint'");
        InstructionDesc[Op::OpReorderThreadWithHitObjectNV].operands.push(OperandId, "'Bits'");
        InstructionDesc[Op::OpReorderThreadWithHitObjectNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectGetCurrentTimeNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetCurrentTimeNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetHitKindNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetHitKindNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetPrimitiveIndexNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetPrimitiveIndexNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetGeometryIndexNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetGeometryIndexNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetInstanceIdNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetInstanceIdNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetInstanceCustomIndexNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetInstanceCustomIndexNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetObjectRayDirectionNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetObjectRayDirectionNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetObjectRayOriginNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetObjectRayOriginNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetWorldRayDirectionNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetWorldRayDirectionNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetWorldRayOriginNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetWorldRayOriginNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetWorldToObjectNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetWorldToObjectNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetObjectToWorldNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetObjectToWorldNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetRayTMaxNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetRayTMaxNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetRayTMinNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetRayTMinNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetShaderBindingTableRecordIndexNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetShaderBindingTableRecordIndexNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectIsEmptyNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectIsEmptyNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectIsHitNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectIsHitNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectIsMissNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectIsMissNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetAttributesNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetAttributesNV].operands.push(OperandId, "'HitObjectAttribute'");
        InstructionDesc[Op::OpHitObjectGetAttributesNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectExecuteShaderNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectExecuteShaderNV].operands.push(OperandId, "'Payload'");
        InstructionDesc[Op::OpHitObjectExecuteShaderNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'Acceleration Structure'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'InstanceId'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'PrimitiveId'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'GeometryIndex'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'HitKind'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'SBT Record Offset'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'SBT Record Stride'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'Origin'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'TMin'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'Direction'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'TMax'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].operands.push(OperandId, "'HitObject Attribute'");
        InstructionDesc[Op::OpHitObjectRecordHitNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'Acceleration Structure'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'InstanceId'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'PrimitiveId'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'GeometryIndex'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'HitKind'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'SBT Record Offset'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'SBT Record Stride'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'Origin'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'TMin'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'Direction'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'TMax'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'Current Time'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].operands.push(OperandId, "'HitObject Attribute'");
        InstructionDesc[Op::OpHitObjectRecordHitMotionNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'Acceleration Structure'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'InstanceId'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'PrimitiveId'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'GeometryIndex'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'HitKind'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'SBT Record Index'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'Origin'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'TMin'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'Direction'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'TMax'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].operands.push(OperandId, "'HitObject Attribute'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'Acceleration Structure'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'InstanceId'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'PrimitiveId'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'GeometryIndex'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'HitKind'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'SBT Record Index'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'Origin'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'TMin'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'Direction'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'TMax'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'Current Time'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].operands.push(OperandId, "'HitObject Attribute'");
        InstructionDesc[Op::OpHitObjectRecordHitWithIndexMotionNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectRecordMissNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectRecordMissNV].operands.push(OperandId, "'SBT Index'");
        InstructionDesc[Op::OpHitObjectRecordMissNV].operands.push(OperandId, "'Origin'");
        InstructionDesc[Op::OpHitObjectRecordMissNV].operands.push(OperandId, "'TMin'");
        InstructionDesc[Op::OpHitObjectRecordMissNV].operands.push(OperandId, "'Direction'");
        InstructionDesc[Op::OpHitObjectRecordMissNV].operands.push(OperandId, "'TMax'");
        InstructionDesc[Op::OpHitObjectRecordMissNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectRecordMissMotionNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectRecordMissMotionNV].operands.push(OperandId, "'SBT Index'");
        InstructionDesc[Op::OpHitObjectRecordMissMotionNV].operands.push(OperandId, "'Origin'");
        InstructionDesc[Op::OpHitObjectRecordMissMotionNV].operands.push(OperandId, "'TMin'");
        InstructionDesc[Op::OpHitObjectRecordMissMotionNV].operands.push(OperandId, "'Direction'");
        InstructionDesc[Op::OpHitObjectRecordMissMotionNV].operands.push(OperandId, "'TMax'");
        InstructionDesc[Op::OpHitObjectRecordMissMotionNV].operands.push(OperandId, "'Current Time'");
        InstructionDesc[Op::OpHitObjectRecordMissMotionNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectRecordEmptyNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectRecordEmptyNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'Acceleration Structure'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'RayFlags'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'Cullmask'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'SBT Record Offset'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'SBT Record Stride'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'Miss Index'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'Origin'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'TMin'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'Direction'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'TMax'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].operands.push(OperandId, "'Payload'");
        InstructionDesc[Op::OpHitObjectTraceRayNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'Acceleration Structure'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'RayFlags'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'Cullmask'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'SBT Record Offset'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'SBT Record Stride'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'Miss Index'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'Origin'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'TMin'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'Direction'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'TMax'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'Time'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].operands.push(OperandId, "'Payload'");
        InstructionDesc[Op::OpHitObjectTraceRayMotionNV].setResultAndType(false, false);

        InstructionDesc[Op::OpHitObjectGetClusterIdNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetClusterIdNV].setResultAndType(true, true);
        InstructionDesc[Op::OpHitObjectGetSpherePositionNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetSpherePositionNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetSphereRadiusNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetSphereRadiusNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetLSSPositionsNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetLSSPositionsNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectGetLSSRadiiNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectGetLSSRadiiNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectIsSphereHitNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectIsSphereHitNV].setResultAndType(true, true);

        InstructionDesc[Op::OpHitObjectIsLSSHitNV].operands.push(OperandId, "'HitObject'");
        InstructionDesc[Op::OpHitObjectIsLSSHitNV].setResultAndType(true, true);

        InstructionDesc[Op::OpFetchMicroTriangleVertexBarycentricNV].operands.push(OperandId, "'Acceleration Structure'");
        InstructionDesc[Op::OpFetchMicroTriangleVertexBarycentricNV].operands.push(OperandId, "'Instance ID'");
        InstructionDesc[Op::OpFetchMicroTriangleVertexBarycentricNV].operands.push(OperandId, "'Geometry Index'");
        InstructionDesc[Op::OpFetchMicroTriangleVertexBarycentricNV].operands.push(OperandId, "'Primitive Index'");
        InstructionDesc[Op::OpFetchMicroTriangleVertexBarycentricNV].operands.push(OperandId, "'Barycentrics'");
        InstructionDesc[Op::OpFetchMicroTriangleVertexBarycentricNV].setResultAndType(true, true);

        InstructionDesc[Op::OpFetchMicroTriangleVertexPositionNV].operands.push(OperandId, "'Acceleration Structure'");
        InstructionDesc[Op::OpFetchMicroTriangleVertexPositionNV].operands.push(OperandId, "'Instance ID'");
        InstructionDesc[Op::OpFetchMicroTriangleVertexPositionNV].operands.push(OperandId, "'Geometry Index'");
        InstructionDesc[Op::OpFetchMicroTriangleVertexPositionNV].operands.push(OperandId, "'Primitive Index'");
        InstructionDesc[Op::OpFetchMicroTriangleVertexPositionNV].operands.push(OperandId, "'Barycentrics'");
        InstructionDesc[Op::OpFetchMicroTriangleVertexPositionNV].setResultAndType(true, true);

        InstructionDesc[Op::OpColorAttachmentReadEXT].operands.push(OperandId, "'Attachment'");
        InstructionDesc[Op::OpColorAttachmentReadEXT].operands.push(OperandId, "'Sample'", true);
        InstructionDesc[Op::OpStencilAttachmentReadEXT].operands.push(OperandId, "'Sample'", true);
        InstructionDesc[Op::OpDepthAttachmentReadEXT].operands.push(OperandId, "'Sample'", true);

        InstructionDesc[Op::OpImageSampleWeightedQCOM].operands.push(OperandId, "'source texture'");
        InstructionDesc[Op::OpImageSampleWeightedQCOM].operands.push(OperandId, "'texture coordinates'");
        InstructionDesc[Op::OpImageSampleWeightedQCOM].operands.push(OperandId, "'weights texture'");
        InstructionDesc[Op::OpImageSampleWeightedQCOM].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageSampleWeightedQCOM].setResultAndType(true, true);

        InstructionDesc[Op::OpImageBoxFilterQCOM].operands.push(OperandId, "'source texture'");
        InstructionDesc[Op::OpImageBoxFilterQCOM].operands.push(OperandId, "'texture coordinates'");
        InstructionDesc[Op::OpImageBoxFilterQCOM].operands.push(OperandId, "'box size'");
        InstructionDesc[Op::OpImageBoxFilterQCOM].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageBoxFilterQCOM].setResultAndType(true, true);

        InstructionDesc[Op::OpImageBlockMatchSADQCOM].operands.push(OperandId, "'target texture'");
        InstructionDesc[Op::OpImageBlockMatchSADQCOM].operands.push(OperandId, "'target coordinates'");
        InstructionDesc[Op::OpImageBlockMatchSADQCOM].operands.push(OperandId, "'reference texture'");
        InstructionDesc[Op::OpImageBlockMatchSADQCOM].operands.push(OperandId, "'reference coordinates'");
        InstructionDesc[Op::OpImageBlockMatchSADQCOM].operands.push(OperandId, "'block size'");
        InstructionDesc[Op::OpImageBlockMatchSADQCOM].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageBlockMatchSADQCOM].setResultAndType(true, true);

        InstructionDesc[Op::OpImageBlockMatchSSDQCOM].operands.push(OperandId, "'target texture'");
        InstructionDesc[Op::OpImageBlockMatchSSDQCOM].operands.push(OperandId, "'target coordinates'");
        InstructionDesc[Op::OpImageBlockMatchSSDQCOM].operands.push(OperandId, "'reference texture'");
        InstructionDesc[Op::OpImageBlockMatchSSDQCOM].operands.push(OperandId, "'reference coordinates'");
        InstructionDesc[Op::OpImageBlockMatchSSDQCOM].operands.push(OperandId, "'block size'");
        InstructionDesc[Op::OpImageBlockMatchSSDQCOM].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageBlockMatchSSDQCOM].setResultAndType(true, true);

        InstructionDesc[Op::OpImageBlockMatchWindowSSDQCOM].operands.push(OperandId, "'target texture'");
        InstructionDesc[Op::OpImageBlockMatchWindowSSDQCOM].operands.push(OperandId, "'target coordinates'");
        InstructionDesc[Op::OpImageBlockMatchWindowSSDQCOM].operands.push(OperandId, "'reference texture'");
        InstructionDesc[Op::OpImageBlockMatchWindowSSDQCOM].operands.push(OperandId, "'reference coordinates'");
        InstructionDesc[Op::OpImageBlockMatchWindowSSDQCOM].operands.push(OperandId, "'block size'");
        InstructionDesc[Op::OpImageBlockMatchWindowSSDQCOM].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageBlockMatchWindowSSDQCOM].setResultAndType(true, true);

        InstructionDesc[Op::OpImageBlockMatchWindowSADQCOM].operands.push(OperandId, "'target texture'");
        InstructionDesc[Op::OpImageBlockMatchWindowSADQCOM].operands.push(OperandId, "'target coordinates'");
        InstructionDesc[Op::OpImageBlockMatchWindowSADQCOM].operands.push(OperandId, "'reference texture'");
        InstructionDesc[Op::OpImageBlockMatchWindowSADQCOM].operands.push(OperandId, "'reference coordinates'");
        InstructionDesc[Op::OpImageBlockMatchWindowSADQCOM].operands.push(OperandId, "'block size'");
        InstructionDesc[Op::OpImageBlockMatchWindowSADQCOM].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageBlockMatchWindowSADQCOM].setResultAndType(true, true);

        InstructionDesc[Op::OpImageBlockMatchGatherSSDQCOM].operands.push(OperandId, "'target texture'");
        InstructionDesc[Op::OpImageBlockMatchGatherSSDQCOM].operands.push(OperandId, "'target coordinates'");
        InstructionDesc[Op::OpImageBlockMatchGatherSSDQCOM].operands.push(OperandId, "'reference texture'");
        InstructionDesc[Op::OpImageBlockMatchGatherSSDQCOM].operands.push(OperandId, "'reference coordinates'");
        InstructionDesc[Op::OpImageBlockMatchGatherSSDQCOM].operands.push(OperandId, "'block size'");
        InstructionDesc[Op::OpImageBlockMatchGatherSSDQCOM].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageBlockMatchGatherSSDQCOM].setResultAndType(true, true);

        InstructionDesc[Op::OpImageBlockMatchGatherSADQCOM].operands.push(OperandId, "'target texture'");
        InstructionDesc[Op::OpImageBlockMatchGatherSADQCOM].operands.push(OperandId, "'target coordinates'");
        InstructionDesc[Op::OpImageBlockMatchGatherSADQCOM].operands.push(OperandId, "'reference texture'");
        InstructionDesc[Op::OpImageBlockMatchGatherSADQCOM].operands.push(OperandId, "'reference coordinates'");
        InstructionDesc[Op::OpImageBlockMatchGatherSADQCOM].operands.push(OperandId, "'block size'");
        InstructionDesc[Op::OpImageBlockMatchGatherSADQCOM].operands.push(OperandImageOperands, "", true);
        InstructionDesc[Op::OpImageBlockMatchGatherSADQCOM].setResultAndType(true, true);

        InstructionDesc[Op::OpConstantCompositeReplicateEXT].operands.push(OperandId, "'Value'");
        InstructionDesc[Op::OpSpecConstantCompositeReplicateEXT].operands.push(OperandId, "'Value'");
        InstructionDesc[Op::OpCompositeConstructReplicateEXT].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpCooperativeMatrixConvertNV].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpCooperativeMatrixTransposeNV].operands.push(OperandId, "'Matrix'");

        InstructionDesc[Op::OpCooperativeMatrixReduceNV].operands.push(OperandId, "'Matrix'");
        InstructionDesc[Op::OpCooperativeMatrixReduceNV].operands.push(OperandLiteralNumber, "'ReduceMask'");
        InstructionDesc[Op::OpCooperativeMatrixReduceNV].operands.push(OperandId, "'CombineFunc'");

        InstructionDesc[Op::OpCooperativeMatrixPerElementOpNV].operands.push(OperandId, "'Matrix'");
        InstructionDesc[Op::OpCooperativeMatrixPerElementOpNV].operands.push(OperandId, "'Operation'");
        InstructionDesc[Op::OpCooperativeMatrixPerElementOpNV].operands.push(OperandVariableIds, "'Operands'");

        InstructionDesc[Op::OpCooperativeMatrixLoadTensorNV].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpCooperativeMatrixLoadTensorNV].operands.push(OperandId, "'Object'");
        InstructionDesc[Op::OpCooperativeMatrixLoadTensorNV].operands.push(OperandId, "'TensorLayout'");
        InstructionDesc[Op::OpCooperativeMatrixLoadTensorNV].operands.push(OperandMemoryAccess, "'Memory Access'");
        InstructionDesc[Op::OpCooperativeMatrixLoadTensorNV].operands.push(OperandTensorAddressingOperands, "'Tensor Addressing Operands'");

        InstructionDesc[Op::OpCooperativeMatrixStoreTensorNV].operands.push(OperandId, "'Pointer'");
        InstructionDesc[Op::OpCooperativeMatrixStoreTensorNV].operands.push(OperandId, "'Object'");
        InstructionDesc[Op::OpCooperativeMatrixStoreTensorNV].operands.push(OperandId, "'TensorLayout'");
        InstructionDesc[Op::OpCooperativeMatrixStoreTensorNV].operands.push(OperandMemoryAccess, "'Memory Access'");
        InstructionDesc[Op::OpCooperativeMatrixStoreTensorNV].operands.push(OperandTensorAddressingOperands, "'Tensor Addressing Operands'");

        InstructionDesc[Op::OpCooperativeMatrixReduceNV].operands.push(OperandId, "'Matrix'");
        InstructionDesc[Op::OpCooperativeMatrixReduceNV].operands.push(OperandLiteralNumber, "'ReduceMask'");

        InstructionDesc[Op::OpTypeTensorLayoutNV].operands.push(OperandId, "'Dim'");
        InstructionDesc[Op::OpTypeTensorLayoutNV].operands.push(OperandId, "'ClampMode'");

        InstructionDesc[Op::OpTypeTensorViewNV].operands.push(OperandId, "'Dim'");
        InstructionDesc[Op::OpTypeTensorViewNV].operands.push(OperandId, "'HasDimensions'");
        InstructionDesc[Op::OpTypeTensorViewNV].operands.push(OperandVariableIds, "'p'");

        InstructionDesc[Op::OpTensorLayoutSetBlockSizeNV].operands.push(OperandId, "'TensorLayout'");
        InstructionDesc[Op::OpTensorLayoutSetBlockSizeNV].operands.push(OperandVariableIds, "'BlockSize'");

        InstructionDesc[Op::OpTensorLayoutSetDimensionNV].operands.push(OperandId, "'TensorLayout'");
        InstructionDesc[Op::OpTensorLayoutSetDimensionNV].operands.push(OperandVariableIds, "'Dim'");

        InstructionDesc[Op::OpTensorLayoutSetStrideNV].operands.push(OperandId, "'TensorLayout'");
        InstructionDesc[Op::OpTensorLayoutSetStrideNV].operands.push(OperandVariableIds, "'Stride'");

        InstructionDesc[Op::OpTensorLayoutSliceNV].operands.push(OperandId, "'TensorLayout'");
        InstructionDesc[Op::OpTensorLayoutSliceNV].operands.push(OperandVariableIds, "'Operands'");

        InstructionDesc[Op::OpTensorLayoutSetClampValueNV].operands.push(OperandId, "'TensorLayout'");
        InstructionDesc[Op::OpTensorLayoutSetClampValueNV].operands.push(OperandId, "'Value'");

        InstructionDesc[Op::OpTensorViewSetDimensionNV].operands.push(OperandId, "'TensorView'");
        InstructionDesc[Op::OpTensorViewSetDimensionNV].operands.push(OperandVariableIds, "'Dim'");

        InstructionDesc[Op::OpTensorViewSetStrideNV].operands.push(OperandId, "'TensorView'");
        InstructionDesc[Op::OpTensorViewSetStrideNV].operands.push(OperandVariableIds, "'Stride'");

        InstructionDesc[Op::OpTensorViewSetClipNV].operands.push(OperandId, "'TensorView'");
        InstructionDesc[Op::OpTensorViewSetClipNV].operands.push(OperandId, "'ClipRowOffset'");
        InstructionDesc[Op::OpTensorViewSetClipNV].operands.push(OperandId, "'ClipRowSpan'");
        InstructionDesc[Op::OpTensorViewSetClipNV].operands.push(OperandId, "'ClipColOffset'");
        InstructionDesc[Op::OpTensorViewSetClipNV].operands.push(OperandId, "'ClipColSpan'");

        InstructionDesc[Op::OpSDotKHR].operands.push(OperandId, "'Vector1'");
        InstructionDesc[Op::OpSDotKHR].operands.push(OperandId, "'Vector2'");
        InstructionDesc[Op::OpSDotKHR].operands.push(OperandLiteralNumber, "'PackedVectorFormat'");

        InstructionDesc[Op::OpUDotKHR].operands.push(OperandId, "'Vector1'");
        InstructionDesc[Op::OpUDotKHR].operands.push(OperandId, "'Vector2'");
        InstructionDesc[Op::OpUDotKHR].operands.push(OperandLiteralNumber, "'PackedVectorFormat'");

        InstructionDesc[Op::OpSUDotKHR].operands.push(OperandId, "'Vector1'");
        InstructionDesc[Op::OpSUDotKHR].operands.push(OperandId, "'Vector2'");
        InstructionDesc[Op::OpSUDotKHR].operands.push(OperandLiteralNumber, "'PackedVectorFormat'");

        InstructionDesc[Op::OpSDotAccSatKHR].operands.push(OperandId, "'Vector1'");
        InstructionDesc[Op::OpSDotAccSatKHR].operands.push(OperandId, "'Vector2'");
        InstructionDesc[Op::OpSDotAccSatKHR].operands.push(OperandId, "'Accumulator'");
        InstructionDesc[Op::OpSDotAccSatKHR].operands.push(OperandLiteralNumber, "'PackedVectorFormat'");

        InstructionDesc[Op::OpUDotAccSatKHR].operands.push(OperandId, "'Vector1'");
        InstructionDesc[Op::OpUDotAccSatKHR].operands.push(OperandId, "'Vector2'");
        InstructionDesc[Op::OpUDotAccSatKHR].operands.push(OperandId, "'Accumulator'");
        InstructionDesc[Op::OpUDotAccSatKHR].operands.push(OperandLiteralNumber, "'PackedVectorFormat'");

        InstructionDesc[Op::OpSUDotAccSatKHR].operands.push(OperandId, "'Vector1'");
        InstructionDesc[Op::OpSUDotAccSatKHR].operands.push(OperandId, "'Vector2'");
        InstructionDesc[Op::OpSUDotAccSatKHR].operands.push(OperandId, "'Accumulator'");
        InstructionDesc[Op::OpSUDotAccSatKHR].operands.push(OperandLiteralNumber, "'PackedVectorFormat'");
    });
}

} // end spv namespace
