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
        if (symbol->getName() == "anon@1") {
            fprintf(stderr, "meet block anon@1\n");
        }

        auto const& typ = symbol->getType();
        auto typeName = typ.isStruct() ? typ.getTypeName() : typ.getBasicTypeString();
        fprintf(stderr, "meet symbol: %s mangled name: %s access name: %s at %s:%d:%d, type: %s\n",
                symbol->getName().c_str(), symbol->getMangledName().c_str(), symbol->getAccessName().c_str(),
                loc.getFilename(), loc.line, loc.column, typeName.c_str());
        fflush(stderr);
    }

    bool visitUnary(glslang::TVisit v, glslang::TIntermUnary* node) override
    {
        if (node->getOp() != glslang::EOpDeclare)
            return true;

        auto sym = node->getOperand()->getAsSymbolNode();
        auto loc = node->getLoc();
        fprintf(stderr, "%s defined at %s:%d:%d\n", sym->getName().c_str(), loc.getFilename(), loc.line, loc.column);
        return true;
    }

    bool visitAggregate(glslang::TVisit v, glslang::TIntermAggregate* agg) override
    {
        auto op = agg->getOp();
        const char* aggName = agg->getName().c_str();

        if (op == glslang::EOpLinkerObjects) {
            for (auto& item : agg->getSequence()) {
                auto sym = item->getAsSymbolNode();
                const auto& type = sym->getType();

                auto l = item->getLoc();
                auto fname = l.name ? l.name->c_str() : "null";
                fprintf(stderr, "meet linker object: %s access name %s at %s:%d:%d type: %s\n", sym->getName().c_str(),
                        sym->getAccessName().c_str(), fname, item->getLoc().line, item->getLoc().column,
                        type.getCompleteString().c_str());
            }
        }

        if (op != glslang::EOpFunction)
            return true;
        fprintf(stderr, "meet aggregate function define: %s at loc: %s:%d:%d\n", aggName, agg->getLoc().getFilename(),
                agg->getLoc().line, agg->getLoc().column);
        fflush(stderr);
        return true;
    }

    bool visitBinary(glslang::TVisit, glslang::TIntermBinary* node) override 
	{
		
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

    TInfoSink sink;
    ast->output(sink, true);
    std::cerr << sink.info.c_str() << std::endl;
    std::cerr << sink.debug.c_str() << std::endl;
    // visitAllTypesAndSymbols(ast);

    return 0;
}
