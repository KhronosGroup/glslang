// Copyright 2016 The Shaderc Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// The program demonstrates basic shader compilation using the Shaderc C++ API.
// For clarity, each method is deliberately self-contained.
//
// Techniques demonstrated:
//  - Preprocessing GLSL source text
//  - Compiling a shader to SPIR-V assembly text
//  - Compliing a shader to a SPIR-V binary module
//  - Performing optimization with compilation
//  - Setting basic options: setting a preprocessor symbol.
//  - Checking compilation status and extracting an error message.

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

#include "StandAlone/DirStackFileIncluder.h"
#include "glslang/Include/BaseTypes.h"
#include "glslang/Include/InfoSink.h"
#include "glslang/MachineIndependent/localintermediate.h"
#include "glslang/Public/ShaderLang.h"
#include <iterator>

static const TBuiltInResource kDefaultTBuiltInResource = {
    /*.maxLights = */ 8,        // From OpenGL 3.0 table 6.46.
    /*.maxClipPlanes = */ 6,    // From OpenGL 3.0 table 6.46.
    /*.maxTextureUnits = */ 2,  // From OpenGL 3.0 table 6.50.
    /*.maxTextureCoords = */ 8, // From OpenGL 3.0 table 6.50.
    /*.maxVertexAttribs = */ 16,
    /*.maxVertexUniformComponents = */ 4096,
    /*.maxVaryingFloats = */ 60, // From OpenGLES 3.1 table 6.44.
    /*.maxVertexTextureImageUnits = */ 16,
    /*.maxCombinedTextureImageUnits = */ 80,
    /*.maxTextureImageUnits = */ 16,
    /*.maxFragmentUniformComponents = */ 1024,

    // glslang has 32 maxDrawBuffers.
    // Pixel phone Vulkan driver in Android N has 8
    // maxFragmentOutputAttachments.
    /*.maxDrawBuffers = */ 8,

    /*.maxVertexUniformVectors = */ 256,
    /*.maxVaryingVectors = */ 15, // From OpenGLES 3.1 table 6.44.
    /*.maxFragmentUniformVectors = */ 256,
    /*.maxVertexOutputVectors = */ 16,  // maxVertexOutputComponents / 4
    /*.maxFragmentInputVectors = */ 15, // maxFragmentInputComponents / 4
    /*.minProgramTexelOffset = */ -8,
    /*.maxProgramTexelOffset = */ 7,
    /*.maxClipDistances = */ 8,
    /*.maxComputeWorkGroupCountX = */ 65535,
    /*.maxComputeWorkGroupCountY = */ 65535,
    /*.maxComputeWorkGroupCountZ = */ 65535,
    /*.maxComputeWorkGroupSizeX = */ 1024,
    /*.maxComputeWorkGroupSizeX = */ 1024,
    /*.maxComputeWorkGroupSizeZ = */ 64,
    /*.maxComputeUniformComponents = */ 512,
    /*.maxComputeTextureImageUnits = */ 16,
    /*.maxComputeImageUniforms = */ 8,
    /*.maxComputeAtomicCounters = */ 8,
    /*.maxComputeAtomicCounterBuffers = */ 1, // From OpenGLES 3.1 Table 6.43
    /*.maxVaryingComponents = */ 60,
    /*.maxVertexOutputComponents = */ 64,
    /*.maxGeometryInputComponents = */ 64,
    /*.maxGeometryOutputComponents = */ 128,
    /*.maxFragmentInputComponents = */ 128,
    /*.maxImageUnits = */ 8, // This does not seem to be defined anywhere,
                             // set to ImageUnits.
    /*.maxCombinedImageUnitsAndFragmentOutputs = */ 8,
    /*.maxCombinedShaderOutputResources = */ 8,
    /*.maxImageSamples = */ 0,
    /*.maxVertexImageUniforms = */ 0,
    /*.maxTessControlImageUniforms = */ 0,
    /*.maxTessEvaluationImageUniforms = */ 0,
    /*.maxGeometryImageUniforms = */ 0,
    /*.maxFragmentImageUniforms = */ 8,
    /*.maxCombinedImageUniforms = */ 8,
    /*.maxGeometryTextureImageUnits = */ 16,
    /*.maxGeometryOutputVertices = */ 256,
    /*.maxGeometryTotalOutputComponents = */ 1024,
    /*.maxGeometryUniformComponents = */ 512,
    /*.maxGeometryVaryingComponents = */ 60, // Does not seem to be defined
                                             // anywhere, set equal to
                                             // maxVaryingComponents.
    /*.maxTessControlInputComponents = */ 128,
    /*.maxTessControlOutputComponents = */ 128,
    /*.maxTessControlTextureImageUnits = */ 16,
    /*.maxTessControlUniformComponents = */ 1024,
    /*.maxTessControlTotalOutputComponents = */ 4096,
    /*.maxTessEvaluationInputComponents = */ 128,
    /*.maxTessEvaluationOutputComponents = */ 128,
    /*.maxTessEvaluationTextureImageUnits = */ 16,
    /*.maxTessEvaluationUniformComponents = */ 1024,
    /*.maxTessPatchComponents = */ 120,
    /*.maxPatchVertices = */ 32,
    /*.maxTessGenLevel = */ 64,
    /*.maxViewports = */ 16,
    /*.maxVertexAtomicCounters = */ 0,
    /*.maxTessControlAtomicCounters = */ 0,
    /*.maxTessEvaluationAtomicCounters = */ 0,
    /*.maxGeometryAtomicCounters = */ 0,
    /*.maxFragmentAtomicCounters = */ 8,
    /*.maxCombinedAtomicCounters = */ 8,
    /*.maxAtomicCounterBindings = */ 1,
    /*.maxVertexAtomicCounterBuffers = */ 0, // From OpenGLES 3.1 Table 6.41.

    // ARB_shader_atomic_counters.
    /*.maxTessControlAtomicCounterBuffers = */ 0,
    /*.maxTessEvaluationAtomicCounterBuffers = */ 0,
    /*.maxGeometryAtomicCounterBuffers = */ 0,
    // /ARB_shader_atomic_counters.

    /*.maxFragmentAtomicCounterBuffers = */ 0, // From OpenGLES 3.1 Table 6.43.
    /*.maxCombinedAtomicCounterBuffers = */ 1,
    /*.maxAtomicCounterBufferSize = */ 32,
    /*.maxTransformFeedbackBuffers = */ 4,
    /*.maxTransformFeedbackInterleavedComponents = */ 64,
    /*.maxCullDistances = */ 8,                // ARB_cull_distance.
    /*.maxCombinedClipAndCullDistances = */ 8, // ARB_cull_distance.
    /*.maxSamples = */ 4,
    /* .maxMeshOutputVerticesNV = */ 256,
    /* .maxMeshOutputPrimitivesNV = */ 512,
    /* .maxMeshWorkGroupSizeX_NV = */ 32,
    /* .maxMeshWorkGroupSizeY_NV = */ 1,
    /* .maxMeshWorkGroupSizeZ_NV = */ 1,
    /* .maxTaskWorkGroupSizeX_NV = */ 32,
    /* .maxTaskWorkGroupSizeY_NV = */ 1,
    /* .maxTaskWorkGroupSizeZ_NV = */ 1,
    /* .maxMeshViewCountNV = */ 4,
    /* .maxMeshOutputVerticesEXT = */ 256,
    /* .maxMeshOutputPrimitivesEXT = */ 256,
    /* .maxMeshWorkGroupSizeX_EXT = */ 128,
    /* .maxMeshWorkGroupSizeY_EXT = */ 128,
    /* .maxMeshWorkGroupSizeZ_EXT = */ 128,
    /* .maxTaskWorkGroupSizeX_EXT = */ 128,
    /* .maxTaskWorkGroupSizeY_EXT = */ 128,
    /* .maxTaskWorkGroupSizeZ_EXT = */ 128,
    /* .maxMeshViewCountEXT = */ 4,
    /* .maxDualSourceDrawBuffersEXT = */ 1,
    // This is the glslang TLimits structure.
    // It defines whether or not the following features are enabled.
    // We want them to all be enabled.
    /*.limits = */
    {
        /*.nonInductiveForLoops = */ 1,
        /*.whileLoops = */ 1,
        /*.doWhileLoops = */ 1,
        /*.generalUniformIndexing = */ 1,
        /*.generalAttributeMatrixVectorIndexing = */ 1,
        /*.generalVaryingIndexing = */ 1,
        /*.generalSamplerIndexing = */ 1,
        /*.generalVariableIndexing = */ 1,
        /*.generalConstantMatrixVectorIndexing = */ 1,
    }};

glslang::TIntermediate* parse_ast(glslang::TShader& shader, std::string const& fname,
                                  std::string const& input_source_string,
                                  std::map<std::string, std::string> const& defines)
{
    std::string preambles;

    for (auto& [key, value] : defines) {
        preambles.append("#define ").append(key).append(" ").append(value).append("\n");
    }

    const std::string pound_extension = "#extension GL_GOOGLE_include_directive : enable\n";
    preambles += pound_extension;

    // Parsing requires its own Glslang symbol tables.
    auto used_shader_stage = EShLangCompute;
    std::string error_tag = fname;
    const char* shader_strings = input_source_string.data();
    const int shader_lengths = static_cast<int>(input_source_string.size());
    const char* string_names = error_tag.c_str();
    shader.setStringsWithLengthsAndNames(&shader_strings, &shader_lengths, &string_names, 1);
    shader.setPreamble(preambles.c_str());
    shader.setEntryPoint("main");
    bool auto_bind_uniforms_ = false;
    auto auto_combined_image_sampler_ = false;
    auto auto_map_locations_ = false;

    shader.setAutoMapBindings(auto_bind_uniforms_);
    if (auto_combined_image_sampler_) {
        shader.setTextureSamplerTransformMode(EShTexSampTransUpgradeTextureRemoveSampler);
    }
    shader.setAutoMapLocations(auto_map_locations_);

    shader.setShiftImageBinding(0);
    shader.setShiftSamplerBinding(0);
    shader.setShiftTextureBinding(0);
    shader.setShiftUboBinding(0);
    shader.setShiftSsboBinding(0);
    shader.setShiftUavBinding(0);

    shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_3);
    shader.setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_3);
    glslang::EShSource language = glslang::EShSourceGlsl;
    // This option will only be used if the Vulkan client is used.
    // If new versions of GL_KHR_vulkan_glsl come out, it would make sense to
    // let callers specify which version to use. For now, just use 100.
    shader.setEnvInput(language, used_shader_stage, glslang::EShClientVulkan, 100);
    shader.setEnvInputVulkanRulesRelaxed();
    shader.setInvertY(false);
    shader.setNanMinMaxClamp(false);

    DirStackFileIncluder includer;
    includer.pushExternalLocalDirectory("/Users/conley/github/glslang");
#if 1
    const EShMessages rules = static_cast<EShMessages>(EShMsgCascadingErrors | EShMsgSpvRules | EShMsgVulkanRules);

    auto default_version_ = 110;
    auto default_profile_ = ENoProfile;
    auto force_version_profile_ = false;

    bool success = false;
#if 0
    std::string preprocessed_source;
    success = shader.preprocess(&kDefaultTBuiltInResource, default_version_, default_profile_,
                                     force_version_profile_, false, rules, &preprocessed_source, includer);
    if (!success) {
        std::cerr << "preprocess source code failed" << std::endl;
        return nullptr;
    }

    std::cerr << "preprocess source code: " << std::endl << preprocessed_source << std::endl;
#endif
    success = shader.parse(&kDefaultTBuiltInResource, default_version_, default_profile_, force_version_profile_, false,
                           rules, includer);

    if (!success) {
        std::cerr << "compile info log : " << shader.getInfoLog() << std::endl
                  << "compile debug log: " << shader.getInfoDebugLog() << std::endl;
        return nullptr;
    }

    auto ast = shader.getIntermediate();
    return ast;
#endif
}

class AllTypesAndSymbolsVisitor : public glslang::TIntermTraverser {
public:
    void visitSymbol(glslang::TIntermSymbol* symbol) override
    {
        auto loc = symbol->getLoc();

        auto const& typ = symbol->getType();
        auto typeName = typ.isStruct() ? typ.getTypeName() : typ.getBasicTypeString();
        fprintf(stderr, "meet symbol: %s at %s:%d:%d, type: %s\n", symbol->getName().c_str(), loc.getFilename(),
                loc.line, loc.column, typeName.c_str());
        fflush(stderr);
    }

    bool visitUnary(glslang::TVisit v, glslang::TIntermUnary* node) override { 
		if (node->getOp() != glslang::EOpDeclare) return true;

		auto sym = node->getOperand()->getAsSymbolNode();
		auto loc = node->getLoc();
		fprintf(stderr, "%s defined at %s:%d:%d\n", sym->getName().c_str(), loc.getFilename(), loc.line, loc.column);
		return true; }

    bool visitAggregate(glslang::TVisit v, glslang::TIntermAggregate* agg) override
    {
#define _MAP_OP(_op)                                                                                                   \
    {                                                                                                                  \
        glslang::_op, #_op                                                                                             \
    }

        static std::map<glslang::TOperator, const char*> op_map = {
            _MAP_OP(EOpNull),          // if in a node, should only mean a node is still
                                       // being built
            _MAP_OP(EOpSequence),      // denotes a list of statements, or parameters, etc.
            _MAP_OP(EOpScope),         // Used by debugging to denote a scoped list of
                                       // statements
            _MAP_OP(EOpLinkerObjects), // for aggregate node of objects the linker may
                                       // need, if not reference by the rest of the AST
            _MAP_OP(EOpFunctionCall),
            _MAP_OP(EOpFunction),   // For function definition
            _MAP_OP(EOpParameters), // an aggregate listing the parameters to a
                                    // function
            _MAP_OP(EOpSpirvInst),

            //
            // Unary operators
            //

            _MAP_OP(EOpNegative),
            _MAP_OP(EOpLogicalNot),
            _MAP_OP(EOpVectorLogicalNot),
            _MAP_OP(EOpBitwiseNot),

            _MAP_OP(EOpPostIncrement),
            _MAP_OP(EOpPostDecrement),
            _MAP_OP(EOpPreIncrement),
            _MAP_OP(EOpPreDecrement),

            _MAP_OP(EOpCopyObject),

            _MAP_OP(EOpDeclare), // Used by debugging to force declaration of
                                 // variable in correct scope

            // Operator used to represent all conversions between int, float, and
            // bool. The specific types are inferred from TBasicType.
            _MAP_OP(EOpConvNumeric),

            // uint64_t <-> pointer
            _MAP_OP(EOpConvUint64ToPtr),
            _MAP_OP(EOpConvPtrToUint64),

            // uvec2 <-> pointer
            _MAP_OP(EOpConvUvec2ToPtr),
            _MAP_OP(EOpConvPtrToUvec2),

            // uint64_t -> accelerationStructureEXT
            _MAP_OP(EOpConvUint64ToAccStruct),

            // uvec2 -> accelerationStructureEXT
            _MAP_OP(EOpConvUvec2ToAccStruct),

            //
            // binary operations
            //

            _MAP_OP(EOpAdd),
            _MAP_OP(EOpSub),
            _MAP_OP(EOpMul),
            _MAP_OP(EOpDiv),
            _MAP_OP(EOpMod),
            _MAP_OP(EOpRightShift),
            _MAP_OP(EOpLeftShift),
            _MAP_OP(EOpAnd),
            _MAP_OP(EOpInclusiveOr),
            _MAP_OP(EOpExclusiveOr),
            _MAP_OP(EOpEqual),
            _MAP_OP(EOpNotEqual),
            _MAP_OP(EOpVectorEqual),
            _MAP_OP(EOpVectorNotEqual),
            _MAP_OP(EOpLessThan),
            _MAP_OP(EOpGreaterThan),
            _MAP_OP(EOpLessThanEqual),
            _MAP_OP(EOpGreaterThanEqual),
            _MAP_OP(EOpComma),

            _MAP_OP(EOpVectorTimesScalar),
            _MAP_OP(EOpVectorTimesMatrix),
            _MAP_OP(EOpMatrixTimesVector),
            _MAP_OP(EOpMatrixTimesScalar),

            _MAP_OP(EOpLogicalOr),
            _MAP_OP(EOpLogicalXor),
            _MAP_OP(EOpLogicalAnd),

            _MAP_OP(EOpIndexDirect),
            _MAP_OP(EOpIndexIndirect),
            _MAP_OP(EOpIndexDirectStruct),

            _MAP_OP(EOpVectorSwizzle),

            _MAP_OP(EOpMethod),
            _MAP_OP(EOpScoping),

            //
            // Built-in functions mapped to operators
            //

            _MAP_OP(EOpRadians),
            _MAP_OP(EOpDegrees),
            _MAP_OP(EOpSin),
            _MAP_OP(EOpCos),
            _MAP_OP(EOpTan),
            _MAP_OP(EOpAsin),
            _MAP_OP(EOpAcos),
            _MAP_OP(EOpAtan),
            _MAP_OP(EOpSinh),
            _MAP_OP(EOpCosh),
            _MAP_OP(EOpTanh),
            _MAP_OP(EOpAsinh),
            _MAP_OP(EOpAcosh),
            _MAP_OP(EOpAtanh),

            _MAP_OP(EOpPow),
            _MAP_OP(EOpExp),
            _MAP_OP(EOpLog),
            _MAP_OP(EOpExp2),
            _MAP_OP(EOpLog2),
            _MAP_OP(EOpSqrt),
            _MAP_OP(EOpInverseSqrt),

            _MAP_OP(EOpAbs),
            _MAP_OP(EOpSign),
            _MAP_OP(EOpFloor),
            _MAP_OP(EOpTrunc),
            _MAP_OP(EOpRound),
            _MAP_OP(EOpRoundEven),
            _MAP_OP(EOpCeil),
            _MAP_OP(EOpFract),
            _MAP_OP(EOpModf),
            _MAP_OP(EOpMin),
            _MAP_OP(EOpMax),
            _MAP_OP(EOpClamp),
            _MAP_OP(EOpMix),
            _MAP_OP(EOpStep),
            _MAP_OP(EOpSmoothStep),

            _MAP_OP(EOpIsNan),
            _MAP_OP(EOpIsInf),

            _MAP_OP(EOpFma),

            _MAP_OP(EOpFrexp),
            _MAP_OP(EOpLdexp),

            _MAP_OP(EOpFloatBitsToInt),
            _MAP_OP(EOpFloatBitsToUint),
            _MAP_OP(EOpIntBitsToFloat),
            _MAP_OP(EOpUintBitsToFloat),
            _MAP_OP(EOpDoubleBitsToInt64),
            _MAP_OP(EOpDoubleBitsToUint64),
            _MAP_OP(EOpInt64BitsToDouble),
            _MAP_OP(EOpUint64BitsToDouble),
            _MAP_OP(EOpFloat16BitsToInt16),
            _MAP_OP(EOpFloat16BitsToUint16),
            _MAP_OP(EOpInt16BitsToFloat16),
            _MAP_OP(EOpUint16BitsToFloat16),
            _MAP_OP(EOpPackSnorm2x16),
            _MAP_OP(EOpUnpackSnorm2x16),
            _MAP_OP(EOpPackUnorm2x16),
            _MAP_OP(EOpUnpackUnorm2x16),
            _MAP_OP(EOpPackSnorm4x8),
            _MAP_OP(EOpUnpackSnorm4x8),
            _MAP_OP(EOpPackUnorm4x8),
            _MAP_OP(EOpUnpackUnorm4x8),
            _MAP_OP(EOpPackHalf2x16),
            _MAP_OP(EOpUnpackHalf2x16),
            _MAP_OP(EOpPackDouble2x32),
            _MAP_OP(EOpUnpackDouble2x32),
            _MAP_OP(EOpPackInt2x32),
            _MAP_OP(EOpUnpackInt2x32),
            _MAP_OP(EOpPackUint2x32),
            _MAP_OP(EOpUnpackUint2x32),
            _MAP_OP(EOpPackFloat2x16),
            _MAP_OP(EOpUnpackFloat2x16),
            _MAP_OP(EOpPackInt2x16),
            _MAP_OP(EOpUnpackInt2x16),
            _MAP_OP(EOpPackUint2x16),
            _MAP_OP(EOpUnpackUint2x16),
            _MAP_OP(EOpPackInt4x16),
            _MAP_OP(EOpUnpackInt4x16),
            _MAP_OP(EOpPackUint4x16),
            _MAP_OP(EOpUnpackUint4x16),
            _MAP_OP(EOpPack16),
            _MAP_OP(EOpPack32),
            _MAP_OP(EOpPack64),
            _MAP_OP(EOpUnpack32),
            _MAP_OP(EOpUnpack16),
            _MAP_OP(EOpUnpack8),

            _MAP_OP(EOpLength),
            _MAP_OP(EOpDistance),
            _MAP_OP(EOpDot),
            _MAP_OP(EOpCross),
            _MAP_OP(EOpNormalize),
            _MAP_OP(EOpFaceForward),
            _MAP_OP(EOpReflect),
            _MAP_OP(EOpRefract),

            _MAP_OP(EOpMin3),
            _MAP_OP(EOpMax3),
            _MAP_OP(EOpMid3),

            _MAP_OP(EOpDPdx),         // Fragment only
            _MAP_OP(EOpDPdy),         // Fragment only
            _MAP_OP(EOpFwidth),       // Fragment only
            _MAP_OP(EOpDPdxFine),     // Fragment only
            _MAP_OP(EOpDPdyFine),     // Fragment only
            _MAP_OP(EOpFwidthFine),   // Fragment only
            _MAP_OP(EOpDPdxCoarse),   // Fragment only
            _MAP_OP(EOpDPdyCoarse),   // Fragment only
            _MAP_OP(EOpFwidthCoarse), // Fragment only

            _MAP_OP(EOpInterpolateAtCentroid), // Fragment only
            _MAP_OP(EOpInterpolateAtSample),   // Fragment only
            _MAP_OP(EOpInterpolateAtOffset),   // Fragment only
            _MAP_OP(EOpInterpolateAtVertex),

            _MAP_OP(EOpMatrixTimesMatrix),
            _MAP_OP(EOpOuterProduct),
            _MAP_OP(EOpDeterminant),
            _MAP_OP(EOpMatrixInverse),
            _MAP_OP(EOpTranspose),

            _MAP_OP(EOpFtransform),

            _MAP_OP(EOpNoise),

            _MAP_OP(EOpEmitVertex),         // geometry only
            _MAP_OP(EOpEndPrimitive),       // geometry only
            _MAP_OP(EOpEmitStreamVertex),   // geometry only
            _MAP_OP(EOpEndStreamPrimitive), // geometry only

            _MAP_OP(EOpBarrier),
            _MAP_OP(EOpMemoryBarrier),
            _MAP_OP(EOpMemoryBarrierAtomicCounter),
            _MAP_OP(EOpMemoryBarrierBuffer),
            _MAP_OP(EOpMemoryBarrierImage),
            _MAP_OP(EOpMemoryBarrierShared), // compute only
            _MAP_OP(EOpGroupMemoryBarrier),  // compute only

            _MAP_OP(EOpBallot),
            _MAP_OP(EOpReadInvocation),
            _MAP_OP(EOpReadFirstInvocation),

            _MAP_OP(EOpAnyInvocation),
            _MAP_OP(EOpAllInvocations),
            _MAP_OP(EOpAllInvocationsEqual),

            _MAP_OP(EOpSubgroupGuardStart),
            _MAP_OP(EOpSubgroupBarrier),
            _MAP_OP(EOpSubgroupMemoryBarrier),
            _MAP_OP(EOpSubgroupMemoryBarrierBuffer),
            _MAP_OP(EOpSubgroupMemoryBarrierImage),
            _MAP_OP(EOpSubgroupMemoryBarrierShared), // compute only
            _MAP_OP(EOpSubgroupElect),
            _MAP_OP(EOpSubgroupAll),
            _MAP_OP(EOpSubgroupAny),
            _MAP_OP(EOpSubgroupAllEqual),
            _MAP_OP(EOpSubgroupBroadcast),
            _MAP_OP(EOpSubgroupBroadcastFirst),
            _MAP_OP(EOpSubgroupBallot),
            _MAP_OP(EOpSubgroupInverseBallot),
            _MAP_OP(EOpSubgroupBallotBitExtract),
            _MAP_OP(EOpSubgroupBallotBitCount),
            _MAP_OP(EOpSubgroupBallotInclusiveBitCount),
            _MAP_OP(EOpSubgroupBallotExclusiveBitCount),
            _MAP_OP(EOpSubgroupBallotFindLSB),
            _MAP_OP(EOpSubgroupBallotFindMSB),
            _MAP_OP(EOpSubgroupShuffle),
            _MAP_OP(EOpSubgroupShuffleXor),
            _MAP_OP(EOpSubgroupShuffleUp),
            _MAP_OP(EOpSubgroupShuffleDown),
            _MAP_OP(EOpSubgroupRotate),
            _MAP_OP(EOpSubgroupClusteredRotate),
            _MAP_OP(EOpSubgroupAdd),
            _MAP_OP(EOpSubgroupMul),
            _MAP_OP(EOpSubgroupMin),
            _MAP_OP(EOpSubgroupMax),
            _MAP_OP(EOpSubgroupAnd),
            _MAP_OP(EOpSubgroupOr),
            _MAP_OP(EOpSubgroupXor),
            _MAP_OP(EOpSubgroupInclusiveAdd),
            _MAP_OP(EOpSubgroupInclusiveMul),
            _MAP_OP(EOpSubgroupInclusiveMin),
            _MAP_OP(EOpSubgroupInclusiveMax),
            _MAP_OP(EOpSubgroupInclusiveAnd),
            _MAP_OP(EOpSubgroupInclusiveOr),
            _MAP_OP(EOpSubgroupInclusiveXor),
            _MAP_OP(EOpSubgroupExclusiveAdd),
            _MAP_OP(EOpSubgroupExclusiveMul),
            _MAP_OP(EOpSubgroupExclusiveMin),
            _MAP_OP(EOpSubgroupExclusiveMax),
            _MAP_OP(EOpSubgroupExclusiveAnd),
            _MAP_OP(EOpSubgroupExclusiveOr),
            _MAP_OP(EOpSubgroupExclusiveXor),
            _MAP_OP(EOpSubgroupClusteredAdd),
            _MAP_OP(EOpSubgroupClusteredMul),
            _MAP_OP(EOpSubgroupClusteredMin),
            _MAP_OP(EOpSubgroupClusteredMax),
            _MAP_OP(EOpSubgroupClusteredAnd),
            _MAP_OP(EOpSubgroupClusteredOr),
            _MAP_OP(EOpSubgroupClusteredXor),
            _MAP_OP(EOpSubgroupQuadBroadcast),
            _MAP_OP(EOpSubgroupQuadSwapHorizontal),
            _MAP_OP(EOpSubgroupQuadSwapVertical),
            _MAP_OP(EOpSubgroupQuadSwapDiagonal),
            _MAP_OP(EOpSubgroupQuadAll),
            _MAP_OP(EOpSubgroupQuadAny),

            _MAP_OP(EOpSubgroupPartition),
            _MAP_OP(EOpSubgroupPartitionedAdd),
            _MAP_OP(EOpSubgroupPartitionedMul),
            _MAP_OP(EOpSubgroupPartitionedMin),
            _MAP_OP(EOpSubgroupPartitionedMax),
            _MAP_OP(EOpSubgroupPartitionedAnd),
            _MAP_OP(EOpSubgroupPartitionedOr),
            _MAP_OP(EOpSubgroupPartitionedXor),
            _MAP_OP(EOpSubgroupPartitionedInclusiveAdd),
            _MAP_OP(EOpSubgroupPartitionedInclusiveMul),
            _MAP_OP(EOpSubgroupPartitionedInclusiveMin),
            _MAP_OP(EOpSubgroupPartitionedInclusiveMax),
            _MAP_OP(EOpSubgroupPartitionedInclusiveAnd),
            _MAP_OP(EOpSubgroupPartitionedInclusiveOr),
            _MAP_OP(EOpSubgroupPartitionedInclusiveXor),
            _MAP_OP(EOpSubgroupPartitionedExclusiveAdd),
            _MAP_OP(EOpSubgroupPartitionedExclusiveMul),
            _MAP_OP(EOpSubgroupPartitionedExclusiveMin),
            _MAP_OP(EOpSubgroupPartitionedExclusiveMax),
            _MAP_OP(EOpSubgroupPartitionedExclusiveAnd),
            _MAP_OP(EOpSubgroupPartitionedExclusiveOr),
            _MAP_OP(EOpSubgroupPartitionedExclusiveXor),

            _MAP_OP(EOpSubgroupGuardStop),

            // Integer dot product
            _MAP_OP(EOpDotPackedEXT),
            _MAP_OP(EOpDotAccSatEXT),
            _MAP_OP(EOpDotPackedAccSatEXT),

            _MAP_OP(EOpMinInvocations),
            _MAP_OP(EOpMaxInvocations),
            _MAP_OP(EOpAddInvocations),
            _MAP_OP(EOpMinInvocationsNonUniform),
            _MAP_OP(EOpMaxInvocationsNonUniform),
            _MAP_OP(EOpAddInvocationsNonUniform),
            _MAP_OP(EOpMinInvocationsInclusiveScan),
            _MAP_OP(EOpMaxInvocationsInclusiveScan),
            _MAP_OP(EOpAddInvocationsInclusiveScan),
            _MAP_OP(EOpMinInvocationsInclusiveScanNonUniform),
            _MAP_OP(EOpMaxInvocationsInclusiveScanNonUniform),
            _MAP_OP(EOpAddInvocationsInclusiveScanNonUniform),
            _MAP_OP(EOpMinInvocationsExclusiveScan),
            _MAP_OP(EOpMaxInvocationsExclusiveScan),
            _MAP_OP(EOpAddInvocationsExclusiveScan),
            _MAP_OP(EOpMinInvocationsExclusiveScanNonUniform),
            _MAP_OP(EOpMaxInvocationsExclusiveScanNonUniform),
            _MAP_OP(EOpAddInvocationsExclusiveScanNonUniform),
            _MAP_OP(EOpSwizzleInvocations),
            _MAP_OP(EOpSwizzleInvocationsMasked),
            _MAP_OP(EOpWriteInvocation),
            _MAP_OP(EOpMbcnt),

            _MAP_OP(EOpCubeFaceIndex),
            _MAP_OP(EOpCubeFaceCoord),
            _MAP_OP(EOpTime),

            _MAP_OP(EOpAtomicAdd),
            _MAP_OP(EOpAtomicSubtract),
            _MAP_OP(EOpAtomicMin),
            _MAP_OP(EOpAtomicMax),
            _MAP_OP(EOpAtomicAnd),
            _MAP_OP(EOpAtomicOr),
            _MAP_OP(EOpAtomicXor),
            _MAP_OP(EOpAtomicExchange),
            _MAP_OP(EOpAtomicCompSwap),
            _MAP_OP(EOpAtomicLoad),
            _MAP_OP(EOpAtomicStore),

            _MAP_OP(EOpAtomicCounterIncrement), // results in pre-increment value
            _MAP_OP(EOpAtomicCounterDecrement), // results in post-decrement value
            _MAP_OP(EOpAtomicCounter),
            _MAP_OP(EOpAtomicCounterAdd),
            _MAP_OP(EOpAtomicCounterSubtract),
            _MAP_OP(EOpAtomicCounterMin),
            _MAP_OP(EOpAtomicCounterMax),
            _MAP_OP(EOpAtomicCounterAnd),
            _MAP_OP(EOpAtomicCounterOr),
            _MAP_OP(EOpAtomicCounterXor),
            _MAP_OP(EOpAtomicCounterExchange),
            _MAP_OP(EOpAtomicCounterCompSwap),

            _MAP_OP(EOpAny),
            _MAP_OP(EOpAll),

            _MAP_OP(EOpCooperativeMatrixLoad),
            _MAP_OP(EOpCooperativeMatrixStore),
            _MAP_OP(EOpCooperativeMatrixMulAdd),
            _MAP_OP(EOpCooperativeMatrixLoadNV),
            _MAP_OP(EOpCooperativeMatrixStoreNV),
            _MAP_OP(EOpCooperativeMatrixLoadTensorNV),
            _MAP_OP(EOpCooperativeMatrixStoreTensorNV),
            _MAP_OP(EOpCooperativeMatrixMulAddNV),
            _MAP_OP(EOpCooperativeMatrixReduceNV),
            _MAP_OP(EOpCooperativeMatrixPerElementOpNV),
            _MAP_OP(EOpCooperativeMatrixTransposeNV),

            _MAP_OP(EOpCreateTensorLayoutNV),
            _MAP_OP(EOpTensorLayoutSetBlockSizeNV),
            _MAP_OP(EOpTensorLayoutSetDimensionNV),
            _MAP_OP(EOpTensorLayoutSetStrideNV),
            _MAP_OP(EOpTensorLayoutSliceNV),
            _MAP_OP(EOpTensorLayoutSetClampValueNV),

            _MAP_OP(EOpCreateTensorViewNV),
            _MAP_OP(EOpTensorViewSetDimensionNV),
            _MAP_OP(EOpTensorViewSetStrideNV),
            _MAP_OP(EOpTensorViewSetClipNV),

            _MAP_OP(EOpCooperativeVectorMatMulNV),
            _MAP_OP(EOpCooperativeVectorMatMulAddNV),
            _MAP_OP(EOpCooperativeVectorLoadNV),
            _MAP_OP(EOpCooperativeVectorStoreNV),
            _MAP_OP(EOpCooperativeVectorOuterProductAccumulateNV),
            _MAP_OP(EOpCooperativeVectorReduceSumAccumulateNV),

            _MAP_OP(EOpBeginInvocationInterlock), // Fragment only
            _MAP_OP(EOpEndInvocationInterlock),   // Fragment only

            _MAP_OP(EOpIsHelperInvocation),

            _MAP_OP(EOpDebugPrintf),

            //
            // Branch
            //

            _MAP_OP(EOpKill),                  // Fragment only
            _MAP_OP(EOpTerminateInvocation),   // Fragment only
            _MAP_OP(EOpDemote),                // Fragment only
            _MAP_OP(EOpTerminateRayKHR),       // Any-hit only
            _MAP_OP(EOpIgnoreIntersectionKHR), // Any-hit only
            _MAP_OP(EOpReturn),
            _MAP_OP(EOpBreak),
            _MAP_OP(EOpContinue),
            _MAP_OP(EOpCase),
            _MAP_OP(EOpDefault),

            //
            // Constructors
            //

            _MAP_OP(EOpConstructGuardStart),
            _MAP_OP(EOpConstructInt), // these first scalar forms also identify
                                      // what implicit conversion is needed
            _MAP_OP(EOpConstructUint),
            _MAP_OP(EOpConstructInt8),
            _MAP_OP(EOpConstructUint8),
            _MAP_OP(EOpConstructInt16),
            _MAP_OP(EOpConstructUint16),
            _MAP_OP(EOpConstructInt64),
            _MAP_OP(EOpConstructUint64),
            _MAP_OP(EOpConstructBool),
            _MAP_OP(EOpConstructFloat),
            _MAP_OP(EOpConstructDouble),
            // Keep vector and matrix constructors in a consistent relative order
            // for TParseContext::constructBuiltIn, which converts between 8/16/32
            // bit vector constructors
            _MAP_OP(EOpConstructVec2),
            _MAP_OP(EOpConstructVec3),
            _MAP_OP(EOpConstructVec4),
            _MAP_OP(EOpConstructMat2x2),
            _MAP_OP(EOpConstructMat2x3),
            _MAP_OP(EOpConstructMat2x4),
            _MAP_OP(EOpConstructMat3x2),
            _MAP_OP(EOpConstructMat3x3),
            _MAP_OP(EOpConstructMat3x4),
            _MAP_OP(EOpConstructMat4x2),
            _MAP_OP(EOpConstructMat4x3),
            _MAP_OP(EOpConstructMat4x4),
            _MAP_OP(EOpConstructDVec2),
            _MAP_OP(EOpConstructDVec3),
            _MAP_OP(EOpConstructDVec4),
            _MAP_OP(EOpConstructBVec2),
            _MAP_OP(EOpConstructBVec3),
            _MAP_OP(EOpConstructBVec4),
            _MAP_OP(EOpConstructI8Vec2),
            _MAP_OP(EOpConstructI8Vec3),
            _MAP_OP(EOpConstructI8Vec4),
            _MAP_OP(EOpConstructU8Vec2),
            _MAP_OP(EOpConstructU8Vec3),
            _MAP_OP(EOpConstructU8Vec4),
            _MAP_OP(EOpConstructI16Vec2),
            _MAP_OP(EOpConstructI16Vec3),
            _MAP_OP(EOpConstructI16Vec4),
            _MAP_OP(EOpConstructU16Vec2),
            _MAP_OP(EOpConstructU16Vec3),
            _MAP_OP(EOpConstructU16Vec4),
            _MAP_OP(EOpConstructIVec2),
            _MAP_OP(EOpConstructIVec3),
            _MAP_OP(EOpConstructIVec4),
            _MAP_OP(EOpConstructUVec2),
            _MAP_OP(EOpConstructUVec3),
            _MAP_OP(EOpConstructUVec4),
            _MAP_OP(EOpConstructI64Vec2),
            _MAP_OP(EOpConstructI64Vec3),
            _MAP_OP(EOpConstructI64Vec4),
            _MAP_OP(EOpConstructU64Vec2),
            _MAP_OP(EOpConstructU64Vec3),
            _MAP_OP(EOpConstructU64Vec4),
            _MAP_OP(EOpConstructDMat2x2),
            _MAP_OP(EOpConstructDMat2x3),
            _MAP_OP(EOpConstructDMat2x4),
            _MAP_OP(EOpConstructDMat3x2),
            _MAP_OP(EOpConstructDMat3x3),
            _MAP_OP(EOpConstructDMat3x4),
            _MAP_OP(EOpConstructDMat4x2),
            _MAP_OP(EOpConstructDMat4x3),
            _MAP_OP(EOpConstructDMat4x4),
            _MAP_OP(EOpConstructIMat2x2),
            _MAP_OP(EOpConstructIMat2x3),
            _MAP_OP(EOpConstructIMat2x4),
            _MAP_OP(EOpConstructIMat3x2),
            _MAP_OP(EOpConstructIMat3x3),
            _MAP_OP(EOpConstructIMat3x4),
            _MAP_OP(EOpConstructIMat4x2),
            _MAP_OP(EOpConstructIMat4x3),
            _MAP_OP(EOpConstructIMat4x4),
            _MAP_OP(EOpConstructUMat2x2),
            _MAP_OP(EOpConstructUMat2x3),
            _MAP_OP(EOpConstructUMat2x4),
            _MAP_OP(EOpConstructUMat3x2),
            _MAP_OP(EOpConstructUMat3x3),
            _MAP_OP(EOpConstructUMat3x4),
            _MAP_OP(EOpConstructUMat4x2),
            _MAP_OP(EOpConstructUMat4x3),
            _MAP_OP(EOpConstructUMat4x4),
            _MAP_OP(EOpConstructBMat2x2),
            _MAP_OP(EOpConstructBMat2x3),
            _MAP_OP(EOpConstructBMat2x4),
            _MAP_OP(EOpConstructBMat3x2),
            _MAP_OP(EOpConstructBMat3x3),
            _MAP_OP(EOpConstructBMat3x4),
            _MAP_OP(EOpConstructBMat4x2),
            _MAP_OP(EOpConstructBMat4x3),
            _MAP_OP(EOpConstructBMat4x4),
            _MAP_OP(EOpConstructFloat16),
            _MAP_OP(EOpConstructF16Vec2),
            _MAP_OP(EOpConstructF16Vec3),
            _MAP_OP(EOpConstructF16Vec4),
            _MAP_OP(EOpConstructF16Mat2x2),
            _MAP_OP(EOpConstructF16Mat2x3),
            _MAP_OP(EOpConstructF16Mat2x4),
            _MAP_OP(EOpConstructF16Mat3x2),
            _MAP_OP(EOpConstructF16Mat3x3),
            _MAP_OP(EOpConstructF16Mat3x4),
            _MAP_OP(EOpConstructF16Mat4x2),
            _MAP_OP(EOpConstructF16Mat4x3),
            _MAP_OP(EOpConstructF16Mat4x4),
            _MAP_OP(EOpConstructBFloat16),
            _MAP_OP(EOpConstructBF16Vec2),
            _MAP_OP(EOpConstructBF16Vec3),
            _MAP_OP(EOpConstructBF16Vec4),
            _MAP_OP(EOpConstructStruct),
            _MAP_OP(EOpConstructTextureSampler),
            _MAP_OP(EOpConstructNonuniform), // expected to be transformed away,
                                             // not present in final AST
            _MAP_OP(EOpConstructReference),
            _MAP_OP(EOpConstructCooperativeMatrixNV),
            _MAP_OP(EOpConstructCooperativeMatrixKHR),
            _MAP_OP(EOpConstructCooperativeVectorNV),
            _MAP_OP(EOpConstructAccStruct),
            _MAP_OP(EOpConstructGuardEnd),

            //
            // moves
            //

            _MAP_OP(EOpAssign),
            _MAP_OP(EOpAddAssign),
            _MAP_OP(EOpSubAssign),
            _MAP_OP(EOpMulAssign),
            _MAP_OP(EOpVectorTimesMatrixAssign),
            _MAP_OP(EOpVectorTimesScalarAssign),
            _MAP_OP(EOpMatrixTimesScalarAssign),
            _MAP_OP(EOpMatrixTimesMatrixAssign),
            _MAP_OP(EOpDivAssign),
            _MAP_OP(EOpModAssign),
            _MAP_OP(EOpAndAssign),
            _MAP_OP(EOpInclusiveOrAssign),
            _MAP_OP(EOpExclusiveOrAssign),
            _MAP_OP(EOpLeftShiftAssign),
            _MAP_OP(EOpRightShiftAssign),

            //
            // Array operators
            //

            // Can apply to arrays, vectors, or matrices.
            // Can be decomposed to a constant at compile time, but this does not
            // always happen, due to link-time effects. So, consumer can expect
            // either a link-time sized or run-time sized array.
            _MAP_OP(EOpArrayLength),

            //
            // Image operations
            //

            _MAP_OP(EOpImageGuardBegin),

            _MAP_OP(EOpImageQuerySize),
            _MAP_OP(EOpImageQuerySamples),
            _MAP_OP(EOpImageLoad),
            _MAP_OP(EOpImageStore),
            _MAP_OP(EOpImageLoadLod),
            _MAP_OP(EOpImageStoreLod),
            _MAP_OP(EOpImageAtomicAdd),
            _MAP_OP(EOpImageAtomicMin),
            _MAP_OP(EOpImageAtomicMax),
            _MAP_OP(EOpImageAtomicAnd),
            _MAP_OP(EOpImageAtomicOr),
            _MAP_OP(EOpImageAtomicXor),
            _MAP_OP(EOpImageAtomicExchange),
            _MAP_OP(EOpImageAtomicCompSwap),
            _MAP_OP(EOpImageAtomicLoad),
            _MAP_OP(EOpImageAtomicStore),

            _MAP_OP(EOpSubpassLoad),
            _MAP_OP(EOpSubpassLoadMS),
            _MAP_OP(EOpSparseImageLoad),
            _MAP_OP(EOpSparseImageLoadLod),
            _MAP_OP(EOpColorAttachmentReadEXT), // Fragment only

            _MAP_OP(EOpImageGuardEnd),

            //
            // Texture operations
            //

            _MAP_OP(EOpTextureGuardBegin),

            _MAP_OP(EOpTextureQuerySize),
            _MAP_OP(EOpTextureQueryLod),
            _MAP_OP(EOpTextureQueryLevels),
            _MAP_OP(EOpTextureQuerySamples),

            _MAP_OP(EOpSamplingGuardBegin),

            _MAP_OP(EOpTexture),
            _MAP_OP(EOpTextureProj),
            _MAP_OP(EOpTextureLod),
            _MAP_OP(EOpTextureOffset),
            _MAP_OP(EOpTextureFetch),
            _MAP_OP(EOpTextureFetchOffset),
            _MAP_OP(EOpTextureProjOffset),
            _MAP_OP(EOpTextureLodOffset),
            _MAP_OP(EOpTextureProjLod),
            _MAP_OP(EOpTextureProjLodOffset),
            _MAP_OP(EOpTextureGrad),
            _MAP_OP(EOpTextureGradOffset),
            _MAP_OP(EOpTextureProjGrad),
            _MAP_OP(EOpTextureProjGradOffset),
            _MAP_OP(EOpTextureGather),
            _MAP_OP(EOpTextureGatherOffset),
            _MAP_OP(EOpTextureGatherOffsets),
            _MAP_OP(EOpTextureClamp),
            _MAP_OP(EOpTextureOffsetClamp),
            _MAP_OP(EOpTextureGradClamp),
            _MAP_OP(EOpTextureGradOffsetClamp),
            _MAP_OP(EOpTextureGatherLod),
            _MAP_OP(EOpTextureGatherLodOffset),
            _MAP_OP(EOpTextureGatherLodOffsets),
            _MAP_OP(EOpFragmentMaskFetch),
            _MAP_OP(EOpFragmentFetch),

            _MAP_OP(EOpSparseTextureGuardBegin),

            _MAP_OP(EOpSparseTexture),
            _MAP_OP(EOpSparseTextureLod),
            _MAP_OP(EOpSparseTextureOffset),
            _MAP_OP(EOpSparseTextureFetch),
            _MAP_OP(EOpSparseTextureFetchOffset),
            _MAP_OP(EOpSparseTextureLodOffset),
            _MAP_OP(EOpSparseTextureGrad),
            _MAP_OP(EOpSparseTextureGradOffset),
            _MAP_OP(EOpSparseTextureGather),
            _MAP_OP(EOpSparseTextureGatherOffset),
            _MAP_OP(EOpSparseTextureGatherOffsets),
            _MAP_OP(EOpSparseTexelsResident),
            _MAP_OP(EOpSparseTextureClamp),
            _MAP_OP(EOpSparseTextureOffsetClamp),
            _MAP_OP(EOpSparseTextureGradClamp),
            _MAP_OP(EOpSparseTextureGradOffsetClamp),
            _MAP_OP(EOpSparseTextureGatherLod),
            _MAP_OP(EOpSparseTextureGatherLodOffset),
            _MAP_OP(EOpSparseTextureGatherLodOffsets),

            _MAP_OP(EOpSparseTextureGuardEnd),

            _MAP_OP(EOpImageFootprintGuardBegin),
            _MAP_OP(EOpImageSampleFootprintNV),
            _MAP_OP(EOpImageSampleFootprintClampNV),
            _MAP_OP(EOpImageSampleFootprintLodNV),
            _MAP_OP(EOpImageSampleFootprintGradNV),
            _MAP_OP(EOpImageSampleFootprintGradClampNV),
            _MAP_OP(EOpImageFootprintGuardEnd),
            _MAP_OP(EOpSamplingGuardEnd),
            _MAP_OP(EOpTextureGuardEnd),

            //
            // Integer operations
            //

            _MAP_OP(EOpAddCarry),
            _MAP_OP(EOpSubBorrow),
            _MAP_OP(EOpUMulExtended),
            _MAP_OP(EOpIMulExtended),
            _MAP_OP(EOpBitfieldExtract),
            _MAP_OP(EOpBitfieldInsert),
            _MAP_OP(EOpBitFieldReverse),
            _MAP_OP(EOpBitCount),
            _MAP_OP(EOpFindLSB),
            _MAP_OP(EOpFindMSB),

            _MAP_OP(EOpCountLeadingZeros),
            _MAP_OP(EOpCountTrailingZeros),
            _MAP_OP(EOpAbsDifference),
            _MAP_OP(EOpAddSaturate),
            _MAP_OP(EOpSubSaturate),
            _MAP_OP(EOpAverage),
            _MAP_OP(EOpAverageRounded),
            _MAP_OP(EOpMul32x16),

            _MAP_OP(EOpTraceNV),
            _MAP_OP(EOpTraceRayMotionNV),
            _MAP_OP(EOpTraceKHR),
            _MAP_OP(EOpReportIntersection),
            _MAP_OP(EOpIgnoreIntersectionNV),
            _MAP_OP(EOpTerminateRayNV),
            _MAP_OP(EOpExecuteCallableNV),
            _MAP_OP(EOpExecuteCallableKHR),
            _MAP_OP(EOpWritePackedPrimitiveIndices4x8NV),
            _MAP_OP(EOpEmitMeshTasksEXT),
            _MAP_OP(EOpSetMeshOutputsEXT),

            //
            // GL_EXT_ray_query operations
            //

            _MAP_OP(EOpRayQueryInitialize),
            _MAP_OP(EOpRayQueryTerminate),
            _MAP_OP(EOpRayQueryGenerateIntersection),
            _MAP_OP(EOpRayQueryConfirmIntersection),
            _MAP_OP(EOpRayQueryProceed),
            _MAP_OP(EOpRayQueryGetIntersectionType),
            _MAP_OP(EOpRayQueryGetRayTMin),
            _MAP_OP(EOpRayQueryGetRayFlags),
            _MAP_OP(EOpRayQueryGetIntersectionT),
            _MAP_OP(EOpRayQueryGetIntersectionInstanceCustomIndex),
            _MAP_OP(EOpRayQueryGetIntersectionInstanceId),
            _MAP_OP(EOpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffset),
            _MAP_OP(EOpRayQueryGetIntersectionGeometryIndex),
            _MAP_OP(EOpRayQueryGetIntersectionPrimitiveIndex),
            _MAP_OP(EOpRayQueryGetIntersectionBarycentrics),
            _MAP_OP(EOpRayQueryGetIntersectionFrontFace),
            _MAP_OP(EOpRayQueryGetIntersectionCandidateAABBOpaque),
            _MAP_OP(EOpRayQueryGetIntersectionObjectRayDirection),
            _MAP_OP(EOpRayQueryGetIntersectionObjectRayOrigin),
            _MAP_OP(EOpRayQueryGetWorldRayDirection),
            _MAP_OP(EOpRayQueryGetWorldRayOrigin),
            _MAP_OP(EOpRayQueryGetIntersectionObjectToWorld),
            _MAP_OP(EOpRayQueryGetIntersectionWorldToObject),

            //
            // GL_NV_shader_invocation_reorder
            //

            _MAP_OP(EOpHitObjectTraceRayNV),
            _MAP_OP(EOpHitObjectTraceRayMotionNV),
            _MAP_OP(EOpHitObjectRecordHitNV),
            _MAP_OP(EOpHitObjectRecordHitMotionNV),
            _MAP_OP(EOpHitObjectRecordHitWithIndexNV),
            _MAP_OP(EOpHitObjectRecordHitWithIndexMotionNV),
            _MAP_OP(EOpHitObjectRecordMissNV),
            _MAP_OP(EOpHitObjectRecordMissMotionNV),
            _MAP_OP(EOpHitObjectRecordEmptyNV),
            _MAP_OP(EOpHitObjectExecuteShaderNV),
            _MAP_OP(EOpHitObjectIsEmptyNV),
            _MAP_OP(EOpHitObjectIsMissNV),
            _MAP_OP(EOpHitObjectIsHitNV),
            _MAP_OP(EOpHitObjectGetRayTMinNV),
            _MAP_OP(EOpHitObjectGetRayTMaxNV),
            _MAP_OP(EOpHitObjectGetObjectRayOriginNV),
            _MAP_OP(EOpHitObjectGetObjectRayDirectionNV),
            _MAP_OP(EOpHitObjectGetWorldRayOriginNV),
            _MAP_OP(EOpHitObjectGetWorldRayDirectionNV),
            _MAP_OP(EOpHitObjectGetWorldToObjectNV),
            _MAP_OP(EOpHitObjectGetObjectToWorldNV),
            _MAP_OP(EOpHitObjectGetInstanceCustomIndexNV),
            _MAP_OP(EOpHitObjectGetInstanceIdNV),
            _MAP_OP(EOpHitObjectGetGeometryIndexNV),
            _MAP_OP(EOpHitObjectGetPrimitiveIndexNV),
            _MAP_OP(EOpHitObjectGetHitKindNV),
            _MAP_OP(EOpHitObjectGetShaderBindingTableRecordIndexNV),
            _MAP_OP(EOpHitObjectGetShaderRecordBufferHandleNV),
            _MAP_OP(EOpHitObjectGetAttributesNV),
            _MAP_OP(EOpHitObjectGetCurrentTimeNV),
            _MAP_OP(EOpReorderThreadNV),
            _MAP_OP(EOpFetchMicroTriangleVertexPositionNV),
            _MAP_OP(EOpFetchMicroTriangleVertexBarycentricNV),

            // HLSL operations
            //

            _MAP_OP(EOpClip), // discard if input value < 0
            _MAP_OP(EOpIsFinite),
            _MAP_OP(EOpLog10),                               // base 10 log
            _MAP_OP(EOpRcp),                                 // 1/x
            _MAP_OP(EOpSaturate),                            // clamp from 0 to 1
            _MAP_OP(EOpSinCos),                              // sin and cos in out parameters
            _MAP_OP(EOpGenMul),                              // mul(x,y) on any of mat/vec/scalars
            _MAP_OP(EOpDst),                                 // x = 1, y=src0.y * src1.y, z=src0.z, w=src1.w
            _MAP_OP(EOpInterlockedAdd),                      // atomic ops, but uses [optional] out arg
                                                             // instead of return
            _MAP_OP(EOpInterlockedAnd),                      // ...
            _MAP_OP(EOpInterlockedCompareExchange),          // ...
            _MAP_OP(EOpInterlockedCompareStore),             // ...
            _MAP_OP(EOpInterlockedExchange),                 // ...
            _MAP_OP(EOpInterlockedMax),                      // ...
            _MAP_OP(EOpInterlockedMin),                      // ...
            _MAP_OP(EOpInterlockedOr),                       // ...
            _MAP_OP(EOpInterlockedXor),                      // ...
            _MAP_OP(EOpAllMemoryBarrierWithGroupSync),       // memory barriers without
                                                             // non-hlsl AST equivalents
            _MAP_OP(EOpDeviceMemoryBarrier),                 // ...
            _MAP_OP(EOpDeviceMemoryBarrierWithGroupSync),    // ...
            _MAP_OP(EOpWorkgroupMemoryBarrier),              // ...
            _MAP_OP(EOpWorkgroupMemoryBarrierWithGroupSync), // ...
            _MAP_OP(EOpEvaluateAttributeSnapped),            // InterpolateAtOffset with int
                                                             // position on 16x16 grid
            _MAP_OP(EOpF32tof16),                            // HLSL conversion: half of a PackHalf2x16
            _MAP_OP(EOpF16tof32),                            // HLSL conversion: half of an UnpackHalf2x16
            _MAP_OP(EOpLit),                                 // HLSL lighting coefficient vector
            _MAP_OP(EOpTextureBias),                         // HLSL texture bias: will be lowered to
                                                             // EOpTexture
            _MAP_OP(EOpAsDouble),                            // slightly different from EOpUint64BitsToDouble
            _MAP_OP(EOpD3DCOLORtoUBYTE4),                    // convert and swizzle 4-component color
                                                             // to UBYTE4 range

            _MAP_OP(EOpMethodSample),                          // Texture object methods.  These are
                                                               // translated to existing
            _MAP_OP(EOpMethodSampleBias),                      // AST methods, and exist to represent
                                                               // HLSL semantics until that
            _MAP_OP(EOpMethodSampleCmp),                       // translation is performed.  See
                                                               // HlslParseContext::decomposeSampleMethods().
            _MAP_OP(EOpMethodSampleCmpLevelZero),              // ...
            _MAP_OP(EOpMethodSampleGrad),                      // ...
            _MAP_OP(EOpMethodSampleLevel),                     // ...
            _MAP_OP(EOpMethodLoad),                            // ...
            _MAP_OP(EOpMethodGetDimensions),                   // ...
            _MAP_OP(EOpMethodGetSamplePosition),               // ...
            _MAP_OP(EOpMethodGather),                          // ...
            _MAP_OP(EOpMethodCalculateLevelOfDetail),          // ...
            _MAP_OP(EOpMethodCalculateLevelOfDetailUnclamped), // ...

            // Load already defined above for textures
            _MAP_OP(EOpMethodLoad2),            // Structure buffer object methods.  These are
                                                // translated to existing
            _MAP_OP(EOpMethodLoad3),            // AST methods, and exist to represent HLSL
                                                // semantics until that
            _MAP_OP(EOpMethodLoad4),            // translation is performed.  See
                                                // HlslParseContext::decomposeSampleMethods().
            _MAP_OP(EOpMethodStore),            // ...
            _MAP_OP(EOpMethodStore2),           // ...
            _MAP_OP(EOpMethodStore3),           // ...
            _MAP_OP(EOpMethodStore4),           // ...
            _MAP_OP(EOpMethodIncrementCounter), // ...
            _MAP_OP(EOpMethodDecrementCounter), // ...
            // EOpMethodAppend is defined for geo shaders below
            _MAP_OP(EOpMethodConsume),

            // SM5 texture methods
            _MAP_OP(EOpMethodGatherRed),      // These are covered under the above
                                              // EOpMethodSample comment about
            _MAP_OP(EOpMethodGatherGreen),    // translation to existing AST opcodes.
                                              // They exist temporarily
            _MAP_OP(EOpMethodGatherBlue),     // because HLSL arguments are slightly
                                              // different.
            _MAP_OP(EOpMethodGatherAlpha),    // ...
            _MAP_OP(EOpMethodGatherCmp),      // ...
            _MAP_OP(EOpMethodGatherCmpRed),   // ...
            _MAP_OP(EOpMethodGatherCmpGreen), // ...
            _MAP_OP(EOpMethodGatherCmpBlue),  // ...
            _MAP_OP(EOpMethodGatherCmpAlpha), // ...

            // geometry methods
            _MAP_OP(EOpMethodAppend),       // Geometry shader methods
            _MAP_OP(EOpMethodRestartStrip), // ...

            // matrix
            _MAP_OP(EOpMatrixSwizzle), // select multiple matrix components
                                       // (non-column)

            // SM6 wave ops
            _MAP_OP(EOpWaveGetLaneCount),    // Will decompose to gl_SubgroupSize.
            _MAP_OP(EOpWaveGetLaneIndex),    // Will decompose to gl_SubgroupInvocationID.
            _MAP_OP(EOpWaveActiveCountBits), // Will decompose to
                                             // subgroupBallotBitCount(subgroupBallot()).
            _MAP_OP(EOpWavePrefixCountBits), // Will decompose to
                                             // subgroupBallotInclusiveBitCount(subgroupBallot()).

            // GL_EXT_expect_assume
            _MAP_OP(EOpAssumeEXT),
            _MAP_OP(EOpExpectEXT),

            // Shader Clock Ops
            _MAP_OP(EOpReadClockSubgroupKHR),
            _MAP_OP(EOpReadClockDeviceKHR),

            // GL_EXT_ray_tracing_position_fetch
            _MAP_OP(EOpRayQueryGetIntersectionTriangleVertexPositionsEXT),

            // Shader tile image ops
            _MAP_OP(EOpStencilAttachmentReadEXT), // Fragment only
            _MAP_OP(EOpDepthAttachmentReadEXT),   // Fragment only

            // Image processing
            _MAP_OP(EOpImageSampleWeightedQCOM),
            _MAP_OP(EOpImageBoxFilterQCOM),
            _MAP_OP(EOpImageBlockMatchSADQCOM),
            _MAP_OP(EOpImageBlockMatchSSDQCOM),

            // Image processing2
            _MAP_OP(EOpImageBlockMatchWindowSSDQCOM),
            _MAP_OP(EOpImageBlockMatchWindowSADQCOM),
            _MAP_OP(EOpImageBlockMatchGatherSSDQCOM),
            _MAP_OP(EOpImageBlockMatchGatherSADQCOM),

            // GL_NV_cluster_acceleration_structure
            _MAP_OP(EOpRayQueryGetIntersectionClusterIdNV),
            _MAP_OP(EOpHitObjectGetClusterIdNV),

            // GL_NV_linear_swept_spheres
            _MAP_OP(EOpRayQueryGetIntersectionSpherePositionNV),
            _MAP_OP(EOpRayQueryGetIntersectionSphereRadiusNV),
            _MAP_OP(EOpRayQueryGetIntersectionLSSHitValueNV),
            _MAP_OP(EOpRayQueryGetIntersectionLSSPositionsNV),
            _MAP_OP(EOpRayQueryGetIntersectionLSSRadiiNV),
            _MAP_OP(EOpRayQueryIsSphereHitNV),
            _MAP_OP(EOpRayQueryIsLSSHitNV),
            _MAP_OP(EOpHitObjectGetSpherePositionNV),
            _MAP_OP(EOpHitObjectGetSphereRadiusNV),
            _MAP_OP(EOpHitObjectGetLSSPositionsNV),
            _MAP_OP(EOpHitObjectGetLSSRadiiNV),
            _MAP_OP(EOpHitObjectIsSphereHitNV),
            _MAP_OP(EOpHitObjectIsLSSHitNV),

        };

        auto op = agg->getOp();
        const char* aggName = agg->getName().c_str();

        auto loc = agg->getLoc();
        fprintf(stderr, "meet aggregate node at loc: %s:%d:%d, op = %s\n", loc.getFilename(), loc.line, loc.column,
                op_map[op]);
        fflush(stderr);

        if (op != glslang::EOpFunction)
            return true;
        fprintf(stderr, "meet aggregate function define: %s at loc: %s:%d:%d\n", aggName, agg->getLoc().getFilename(),
                agg->getLoc().line, agg->getLoc().column);
        fflush(stderr);

#define _MAP_STR(_name)                                                                                                \
    {                                                                                                                  \
        _name, #_name                                                                                                  \
    }
        static std::map<glslang::TStorageQualifier, const char*> storageQualifiers = {
            _MAP_STR(glslang::EvqTemporary),
            _MAP_STR(glslang::EvqGlobal),
            _MAP_STR(glslang::EvqConst),
            _MAP_STR(glslang::EvqVaryingIn),
            _MAP_STR(glslang::EvqVaryingOut),
            _MAP_STR(glslang::EvqUniform),
            _MAP_STR(glslang::EvqBuffer),
            _MAP_STR(glslang::EvqShared),
            _MAP_STR(glslang::EvqSpirvStorageClass),
            _MAP_STR(glslang::EvqPayload),
            _MAP_STR(glslang::EvqPayloadIn),
            _MAP_STR(glslang::EvqHitAttr),
            _MAP_STR(glslang::EvqCallableData),
            _MAP_STR(glslang::EvqCallableDataIn),
            _MAP_STR(glslang::EvqHitObjectAttrNV),
            _MAP_STR(glslang::EvqtaskPayloadSharedEXT),
            _MAP_STR(glslang::EvqIn),
            _MAP_STR(glslang::EvqOut),
            _MAP_STR(glslang::EvqInOut),
            _MAP_STR(glslang::EvqConstReadOnly),
            _MAP_STR(glslang::EvqVertexId),
            _MAP_STR(glslang::EvqInstanceId),
            _MAP_STR(glslang::EvqPosition),
            _MAP_STR(glslang::EvqPosition),
            _MAP_STR(glslang::EvqClipVertex),
            _MAP_STR(glslang::EvqFace),
            _MAP_STR(glslang::EvqFragCoord),
            _MAP_STR(glslang::EvqPointCoord),
            _MAP_STR(glslang::EvqFragColor),
            _MAP_STR(glslang::EvqFragDepth),
            _MAP_STR(glslang::EvqFragStencil),
            _MAP_STR(glslang::EvqTileImageEXT),
            _MAP_STR(glslang::EvqLast),
        };
#undef _MAP_STR

#undef _MAP_OP

        auto quolifier = agg->getQualifierList();
        for (auto const& quo : quolifier) {
            fprintf(stderr, "agg qualifier: %s\n", storageQualifiers[quo]);
            fflush(stderr);
        }

        // auto const& pragmaTable = agg->getPragmaTable();
        // for (auto pos = pragmaTable.cbegin(); pos != pragmaTable.cend(); ++pos) {
        //   fprintf(stderr, "agg pragma table key: %s, value: %s\n",
        //           pos->first.c_str(), pos->second.c_str());
        // }

        auto childs = agg->getSequence();
        fprintf(stderr, "agg %s has %zu children\n", aggName, childs.size());
        return true;
    }
};

bool visitAllTypesAndSymbols(glslang::TIntermediate* intermediate)
{
    auto* root = intermediate->getTreeRoot();
    TInfoSink infoSink;
    auto* visitor = new AllTypesAndSymbolsVisitor();
    root->traverse(visitor);
    return true;
}

int main(const int argc, const char* argv[])
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << ": <compute shader file>" << std::endl;
        return -1;
    }

    // std::cerr << "file source: " << std::endl << source << std::endl;

    std::ifstream ifs(argv[1]);
    std::string source;

    std::istreambuf_iterator<char> it(ifs);

    std::copy(it, std::istreambuf_iterator<char>(), std::back_inserter(source));

    glslang::TShader shader(EShLangCompute);
    glslang::TIntermediate* ast = parse_ast(shader, argv[1], source,
                                            {{"ACC_TYPE", "float"},
                                             {"ALIGNED", "1"},
                                             {"B_TYPE", "f16vec4"},
                                             {"DATA_A_F32", "1"},
                                             {"D_TYPE", "float"},
                                             {"FLOAT_TYPE_VEC2", "vec2"},
                                             {"LOAD_VEC_A", "4"},
                                             {"LOAD_VEC_B", "4"}});
    if (!ast) {
        std::cerr << "parse ast failed." << std::endl;
        return -1;
    }

    // TInfoSink sink;
    // ast->output(sink, true);
    // std::cerr << sink.info.c_str() << std::endl;
    // std::cerr << sink.debug.c_str() << std::endl;
    visitAllTypesAndSymbols(ast);

    return 0;
}
