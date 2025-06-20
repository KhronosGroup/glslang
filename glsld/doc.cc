#include "doc.hpp"
#include "../glslang/MachineIndependent/localintermediate.h"
#include "StandAlone/DirStackFileIncluder.h"
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

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

Doc::Doc() { resource_ = nullptr; }

Doc::Doc(std::string const& uri, const int version, std::string const& text)
{
    resource_ = new __Resource;
    resource_->ref = 1;
    resource_->uri = uri;
    resource_->version = version;
    resource_->text = text;

    infer_language_();
    resource_->shader = std::make_unique<glslang::TShader>(resource_->language);
}

Doc::Doc(const Doc& rhs)
{
    release_();
    resource_ = rhs.resource_;
    resource_->ref += 1;
}

Doc::Doc(Doc&& rhs)
{
    release_();
    resource_ = rhs.resource_;
    rhs.resource_ = nullptr;
}

Doc& Doc::operator=(const Doc& rhs)
{
    release_();
    resource_ = rhs.resource_;
    resource_->ref += 1;
    return *this;
}

Doc& Doc::operator=(Doc&& rhs)
{
    release_();
    resource_ = rhs.resource_;
    return *this;
}

void Doc::infer_language_()
{
    // support compute stage only now
    resource_->language = EShLangCompute;
}

void Doc::release_()
{
    if (resource_) {
        if (resource_->ref == 1) {
            delete resource_;
        } else {
            resource_->ref -= 1;
        }
    }
}

class AllTypesAndSymbolsVisitor_ : public glslang::TIntermTraverser {
public:
    std::map<int, std::vector<TIntermNode*>> nodes_by_line;
    std::vector<glslang::TIntermSymbol*> defs;
    std::vector<glslang::TIntermSymbol*> symbols;
    void visitSymbol(glslang::TIntermSymbol* symbol) override
    {
        nodes_by_line[symbol->getLoc().line].push_back(symbol);
        symbols.push_back(symbol);
    }

    bool visitBinary(glslang::TVisit, glslang::TIntermBinary* node) override
    {
        if (node->getOp() == glslang::EOpIndexDirectStruct || node->getOp() == glslang::EOpIndexDirect ||
            node->getOp() == glslang::EOpIndexIndirect) {
            nodes_by_line[node->getLoc().line].push_back(node);
        }
        return true;
    }

    bool visitAggregate(glslang::TVisit, glslang::TIntermAggregate* agg) override
    {
        if (agg->getOp() != glslang::EOpLinkerObjects) {
            return true;
        }

        for (auto& obj : agg->getSequence()) {
            auto sym = obj->getAsSymbolNode();
            if (!sym)
                continue;
            auto loc = sym->getLoc();
            if (!loc.name) // builtin
                continue;
            defs.push_back(sym);
        }
        return false;
    }

    void visitConstantUnion(glslang::TIntermConstantUnion* node) override {}

    bool visitUnary(glslang::TVisit v, glslang::TIntermUnary* unary) override
    {
        (void)v;
        if (unary->getOp() == glslang::EOpDeclare) {
            defs.push_back(unary->getOperand()->getAsSymbolNode());
            return false;
        } else {
            return true;
        }
    }
};

bool Doc::parse(std::vector<std::string> const& include_dirs)
{
    if (!resource_)
        return false;

    auto& shader = *resource_->shader;
    std::string preambles;
    // TODO: add macro define

    const std::string pound_extension = "#extension GL_GOOGLE_include_directive : enable\n";
    preambles += pound_extension;

    auto& shader_strings = resource_->text;
    const char* shader_source = shader_strings.data();
    const int shader_lengths = (int)shader_strings.size();
    const char* string_names = resource_->uri.data();
    shader.setStringsWithLengthsAndNames(&shader_source, &shader_lengths, &string_names, 1);
    shader.setPreamble(preambles.c_str());
    shader.setEntryPoint("main");

    bool auto_bind_uniforms_ = false;
    auto auto_combined_image_sampler_ = false;
    auto auto_map_locations_ = false;

    shader.setAutoMapBindings(auto_bind_uniforms_);
    if (auto_combined_image_sampler_) {
        shader.setTextureSamplerTransformMode(EShTexSampTransUpgradeTextureRemoveSampler);
    }

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
    shader.setEnvInput(language, EShLangCompute, glslang::EShClientVulkan, 100);
    shader.setEnvInputVulkanRulesRelaxed();
    shader.setInvertY(false);
    shader.setNanMinMaxClamp(false);

    DirStackFileIncluder includer;
    for (auto& d : include_dirs) {
        includer.pushExternalLocalDirectory(d);
    }

    const EShMessages rules = static_cast<EShMessages>(EShMsgCascadingErrors | EShMsgSpvRules | EShMsgVulkanRules);

    auto default_version_ = 110;
    auto default_profile_ = ENoProfile;
    auto force_version_profile_ = false;

    bool success = false;

    success = shader.parse(&kDefaultTBuiltInResource, default_version_, default_profile_, force_version_profile_, false,
                           rules, includer);
    if (!success) {
        std::cerr << shader.getInfoDebugLog() << std::endl;
        return false;
    }

    auto* interm = shader.getIntermediate();

    AllTypesAndSymbolsVisitor_ visitor;
    interm->getTreeRoot()->traverse(&visitor);

    for (auto& s : visitor.defs) {
        auto loc = s->getLoc();
        fprintf(stderr, "symbol %s define at %s:%d:%d\n", s->getName().c_str(), loc.getFilename(), loc.line,
                loc.column);
        resource_->defs[s->getId()] = s;
    }

    for (auto& s : visitor.symbols) {
        std::string name = s->getName().c_str();
        auto loc = s->getLoc();
        fprintf(stderr, "symbol %s use at %s:%d:%d\n", s->getName().c_str(), loc.getFilename(), loc.line, loc.column);
        if (resource_->defs.count(s->getId()) > 0) {
            resource_->symbols.push_back(s);
        } else {
            fprintf(stderr, "found symbol %s use but not defined.\n", name.c_str());
        }
    }

    resource_->nodes_by_line.swap(visitor.nodes_by_line);

    return true;
}

std::vector<glslang::TIntermSymbol*> Doc::locate_symbols_at(const int line, const int col)
{
    std::vector<glslang::TIntermSymbol*> result;
    if (resource_->nodes_by_line.count(line) <= 0) {
        return result;
    }

    auto& nodes = resource_->nodes_by_line[line];
    for (auto* node : nodes) {
        if (auto sym = node->getAsSymbolNode()) {
            auto loc = sym->getLoc();
            auto endcol = loc.column + sym->getName().length();
            if (line == loc.line && loc.column <= col && col <= endcol) {
                result.push_back(sym);
            }
        }
    }

    return result;
}

glslang::TIntermSymbol* Doc::locate_symbol_def(glslang::TIntermSymbol* target)
{
    if (resource_->defs.count(target->getId())) {
        return resource_->defs[target->getId()];
    }

    return nullptr;
}
