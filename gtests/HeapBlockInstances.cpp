// Copyright (C) 2026 The Khronos Group Inc.
// SPDX-License-Identifier: BSD-3-Clause

#include "SPIRV/GlslangToSpv.h"
#include "SPIRV/NonSemanticShaderDebugInfo.h"
#include "glslang/Public/ResourceLimits.h"
#include "glslang/Public/ShaderLang.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace glslangtest {
namespace {

const char* const heapHeader = R"(
#version 460
#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_structured_descriptor_heap : require
#extension GL_EXT_scalar_block_layout : require
#extension GL_EXT_nonuniform_qualifier : require
layout(local_size_x = 1) in;
)";

std::string decodeString(const unsigned int* words, unsigned int wordCount)
{
    std::string result;
    for (unsigned int word = 0; word < wordCount; ++word) {
        for (unsigned int byte = 0; byte < 4; ++byte) {
            const char character = static_cast<char>((words[word] >> (8 * byte)) & 0xff);
            if (character == '\0')
                return result;
            result.push_back(character);
        }
    }
    return result;
}

class HeapBlockInstanceTest : public ::testing::Test {
protected:
    bool compile(const std::vector<std::string>& sources, std::vector<unsigned int>& spirv, std::string& error,
                 bool debug = false)
    {
        spirv.clear();
        error.clear();
        std::vector<std::string> completeSources;
        for (const auto& source : sources)
            completeSources.push_back(heapHeader + source);
        std::vector<const char*> strings;
        for (const auto& source : completeSources)
            strings.push_back(source.c_str());

        std::vector<std::unique_ptr<glslang::TShader>> shaders;
        glslang::TProgram program;
        const auto messages = static_cast<EShMessages>(EShMsgSpvRules | EShMsgVulkanRules |
                                                      (debug ? EShMsgDebugInfo : EShMsgDefault));
        for (size_t index = 0; index < sources.size(); ++index) {
            auto shader = std::make_unique<glslang::TShader>(EShLangCompute);
            shader->setStrings(&strings[index], 1);
            shader->setDebugInfo(debug);
            shader->setEnvInput(glslang::EShSourceGlsl, EShLangCompute, glslang::EShClientVulkan, 110);
            shader->setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_4);
            shader->setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_6);
            if (!shader->parse(GetDefaultResources(), 460, false, messages)) {
                error = shader->getInfoLog();
                return false;
            }
            program.addShader(shader.get());
            shaders.push_back(std::move(shader));
        }
        if (!program.link(messages)) {
            error = program.getInfoLog();
            return false;
        }

        glslang::SpvOptions options;
        options.disableOptimizer = true;
        options.validate = true;
        options.generateDebugInfo = debug;
        options.emitNonSemanticShaderDebugInfo = debug;
        options.emitNonSemanticShaderDebugSource = debug;
        spv::SpvBuildLogger logger;
        glslang::GlslangToSpv(*program.getIntermediate(EShLangCompute), spirv, &logger, &options);
        error = logger.getAllMessages();
        return error.empty();
    }

    using HeapLocation = std::pair<spv::BuiltIn, unsigned int>;

    // Validation alone cannot detect an untyped access using another block's
    // heap or layout. Trace the first member's actual heap and byte offset.
    void expectHeapAccesses(const std::vector<unsigned int>& spirv,
                           const std::map<std::string, HeapLocation>& expected)
    {
        std::map<unsigned int, std::string> firstMembers;
        std::map<unsigned int, unsigned int> constants;
        std::map<unsigned int, spv::BuiltIn> heaps;
        std::map<unsigned int, HeapLocation> pointers;
        std::map<std::string, unsigned int> counts;
        ASSERT_GE(spirv.size(), 5u);
        for (size_t offset = 5; offset < spirv.size();) {
            const auto* words = &spirv[offset];
            const unsigned int wordCount = words[0] >> spv::WordCountShift;
            const auto opcode = static_cast<spv::Op>(words[0] & spv::OpCodeMask);
            ASSERT_GT(wordCount, 0u);
            ASSERT_LE(offset + wordCount, spirv.size());
            if (opcode == spv::Op::OpMemberName && wordCount >= 4 && words[2] == 0) {
                std::string name;
                for (unsigned int index = 3; index < wordCount; ++index) {
                    for (unsigned int byte = 0; byte < 4; ++byte) {
                        const char character = static_cast<char>((words[index] >> (8 * byte)) & 0xff);
                        if (character != '\0')
                            name.push_back(character);
                    }
                }
                firstMembers[words[1]] = name;
            } else if (opcode == spv::Op::OpDecorate && wordCount == 4 &&
                       words[2] == static_cast<unsigned int>(spv::Decoration::BuiltIn)) {
                const auto builtin = static_cast<spv::BuiltIn>(words[3]);
                if (builtin == spv::BuiltIn::ResourceHeapEXT || builtin == spv::BuiltIn::SamplerHeapEXT)
                    heaps[words[1]] = builtin;
            } else if (opcode == spv::Op::OpConstant && wordCount == 4) {
                constants[words[2]] = words[3];
            } else if (opcode == spv::Op::OpUntypedAccessChainKHR && wordCount >= 6) {
                const unsigned int base = words[4];
                if (heaps.count(base) != 0) {
                    ASSERT_NE(constants.find(words[5]), constants.end());
                    pointers[words[2]] = {heaps[base], constants[words[5]]};
                } else if (pointers.count(base) != 0) {
                    pointers[words[2]] = pointers[base];
                }
                const auto member = firstMembers.find(words[3]);
                if (member != firstMembers.end() && expected.count(member->second) != 0) {
                    SCOPED_TRACE(member->second);
                    ASSERT_NE(pointers.find(words[2]), pointers.end());
                    EXPECT_EQ(pointers[words[2]], expected.at(member->second));
                    ++counts[member->second];
                }
            }
            offset += wordCount;
        }
        for (const auto& member : expected) {
            SCOPED_TRACE(member.first);
            EXPECT_EQ(counts[member.first], 2u); // One access in each compilation unit.
        }
    }

    void expectDynamicOffsets(const std::vector<unsigned int>& spirv, unsigned int expectedCount)
    {
        std::set<unsigned int> pushConstants;
        std::set<unsigned int> heaps;
        std::map<unsigned int, unsigned int> constants;
        std::map<unsigned int, unsigned int> pointers;
        std::map<unsigned int, unsigned int> loads;
        unsigned int count = 0;
        ASSERT_GE(spirv.size(), 5u);
        for (size_t offset = 5; offset < spirv.size();) {
            const auto* words = &spirv[offset];
            const unsigned int wordCount = words[0] >> spv::WordCountShift;
            const auto opcode = static_cast<spv::Op>(words[0] & spv::OpCodeMask);
            ASSERT_GT(wordCount, 0u);
            ASSERT_LE(offset + wordCount, spirv.size());
            if (opcode == spv::Op::OpVariable && wordCount >= 4 &&
                words[3] == static_cast<unsigned int>(spv::StorageClass::PushConstant)) {
                pushConstants.insert(words[2]);
            } else if (opcode == spv::Op::OpDecorate && wordCount == 4 &&
                       words[2] == static_cast<unsigned int>(spv::Decoration::BuiltIn) &&
                       (words[3] == static_cast<unsigned int>(spv::BuiltIn::ResourceHeapEXT) ||
                        words[3] == static_cast<unsigned int>(spv::BuiltIn::SamplerHeapEXT))) {
                heaps.insert(words[1]);
            } else if (opcode == spv::Op::OpConstant && wordCount == 4) {
                constants[words[2]] = words[3];
            } else if (opcode == spv::Op::OpAccessChain && wordCount == 5 &&
                       pushConstants.count(words[3]) != 0) {
                ASSERT_NE(constants.find(words[4]), constants.end());
                EXPECT_EQ(constants.at(words[4]), 0u); // Parameters.offsetValue
                pointers[words[2]] = words[3];
            } else if (opcode == spv::Op::OpLoad && wordCount >= 4) {
                loads[words[2]] = words[3];
            } else if (opcode == spv::Op::OpUntypedAccessChainKHR && wordCount >= 6 &&
                       heaps.count(words[4]) != 0) {
                ASSERT_NE(loads.find(words[5]), loads.end());
                ASSERT_NE(pointers.find(loads.at(words[5])), pointers.end());
                ++count;
            }
            offset += wordCount;
        }
        EXPECT_EQ(pushConstants.size(), 1u);
        EXPECT_EQ(count, expectedCount);
    }

    void expectSpecializedOffsets(const std::vector<unsigned int>& spirv)
    {
        std::set<unsigned int> heaps;
        std::map<unsigned int, unsigned int> specIds;
        std::map<unsigned int, unsigned int> values;
        std::map<unsigned int, std::set<unsigned int>> dependencies;
        unsigned int count = 0;
        ASSERT_GE(spirv.size(), 5u);
        for (size_t offset = 5; offset < spirv.size();) {
            const auto* words = &spirv[offset];
            const unsigned int wordCount = words[0] >> spv::WordCountShift;
            const auto opcode = static_cast<spv::Op>(words[0] & spv::OpCodeMask);
            ASSERT_GT(wordCount, 0u);
            ASSERT_LE(offset + wordCount, spirv.size());
            if (opcode == spv::Op::OpDecorate && wordCount == 4) {
                if (words[2] == static_cast<unsigned int>(spv::Decoration::SpecId))
                    specIds[words[1]] = words[3];
                else if (words[2] == static_cast<unsigned int>(spv::Decoration::BuiltIn) &&
                         (words[3] == static_cast<unsigned int>(spv::BuiltIn::ResourceHeapEXT) ||
                          words[3] == static_cast<unsigned int>(spv::BuiltIn::SamplerHeapEXT)))
                    heaps.insert(words[1]);
            } else if ((opcode == spv::Op::OpConstant || opcode == spv::Op::OpSpecConstant) && wordCount == 4) {
                values[words[2]] = words[3];
                if (specIds.count(words[2]) != 0)
                    dependencies[words[2]].insert(specIds.at(words[2]));
            } else if (opcode == spv::Op::OpSpecConstantOp && wordCount == 6 &&
                       words[3] == static_cast<unsigned int>(spv::Op::OpIMul)) {
                ASSERT_NE(values.find(words[4]), values.end());
                ASSERT_NE(values.find(words[5]), values.end());
                values[words[2]] = values.at(words[4]) * values.at(words[5]);
                dependencies[words[2]] = dependencies[words[4]];
                dependencies[words[2]].insert(dependencies[words[5]].begin(), dependencies[words[5]].end());
            } else if (opcode == spv::Op::OpUntypedAccessChainKHR && wordCount >= 6 &&
                       heaps.count(words[4]) != 0) {
                ASSERT_NE(values.find(words[5]), values.end());
                EXPECT_EQ(values.at(words[5]), 64u);
                EXPECT_EQ(dependencies[words[5]], std::set<unsigned int>({0}));
                ++count;
            }
            offset += wordCount;
        }
        EXPECT_EQ(count, 2u);
    }

    void expectStoredHeapLoad(const std::vector<unsigned int>& spirv)
    {
        std::set<unsigned int> heapPointers;
        std::set<unsigned int> heapLoads;
        unsigned int stores = 0;
        ASSERT_GE(spirv.size(), 5u);
        for (size_t offset = 5; offset < spirv.size();) {
            const auto* words = &spirv[offset];
            const unsigned int wordCount = words[0] >> spv::WordCountShift;
            const auto opcode = static_cast<spv::Op>(words[0] & spv::OpCodeMask);
            ASSERT_GT(wordCount, 0u);
            ASSERT_LE(offset + wordCount, spirv.size());
            if (opcode == spv::Op::OpDecorate && wordCount == 4 &&
                words[2] == static_cast<unsigned int>(spv::Decoration::BuiltIn) &&
                (words[3] == static_cast<unsigned int>(spv::BuiltIn::ResourceHeapEXT) ||
                 words[3] == static_cast<unsigned int>(spv::BuiltIn::SamplerHeapEXT))) {
                heapPointers.insert(words[1]);
            } else if (opcode == spv::Op::OpUntypedAccessChainKHR && wordCount >= 6 &&
                       heapPointers.count(words[4]) != 0) {
                heapPointers.insert(words[2]);
            } else if ((opcode == spv::Op::OpAccessChain || opcode == spv::Op::OpBufferPointerEXT) &&
                       wordCount >= 4 && heapPointers.count(words[3]) != 0) {
                heapPointers.insert(words[2]);
            } else if (opcode == spv::Op::OpLoad && wordCount >= 4 && heapPointers.count(words[3]) != 0) {
                heapLoads.insert(words[2]);
            } else if (opcode == spv::Op::OpStore && wordCount >= 3) {
                // A clobbered access chain can silently store the array length
                // instead of loading its element, even in valid SPIR-V.
                EXPECT_NE(heapLoads.count(words[2]), 0u);
                ++stores;
            }
            offset += wordCount;
        }
        EXPECT_EQ(stores, 1u);
    }

    // Relate each named member to its array type and specialization dependency;
    // finding the right SpecId somewhere in the module is not sufficient.
    void expectSpecializedArrayLengths(const std::vector<unsigned int>& spirv,
                                       const std::map<std::string, unsigned int>& expected)
    {
        std::map<std::pair<unsigned int, unsigned int>, std::string> members;
        std::map<unsigned int, std::vector<unsigned int>> structures;
        std::map<unsigned int, std::vector<unsigned int>> composites;
        std::map<unsigned int, unsigned int> lengths;
        std::map<unsigned int, unsigned int> specIds;
        std::map<unsigned int, unsigned int> values;
        std::map<unsigned int, std::set<unsigned int>> dependencies;
        ASSERT_GE(spirv.size(), 5u);
        for (size_t offset = 5; offset < spirv.size();) {
            const auto* words = &spirv[offset];
            const unsigned int wordCount = words[0] >> spv::WordCountShift;
            const auto opcode = static_cast<spv::Op>(words[0] & spv::OpCodeMask);
            ASSERT_GT(wordCount, 0u);
            ASSERT_LE(offset + wordCount, spirv.size());
            if (opcode == spv::Op::OpMemberName && wordCount >= 4) {
                std::string name;
                for (unsigned int index = 3; index < wordCount; ++index) {
                    for (unsigned int byte = 0; byte < 4; ++byte) {
                        const char character = static_cast<char>((words[index] >> (8 * byte)) & 0xff);
                        if (character != '\0')
                            name.push_back(character);
                    }
                }
                if (expected.count(name) != 0)
                    members[{words[1], words[2]}] = name;
            } else if (opcode == spv::Op::OpDecorate && wordCount == 4 &&
                       words[2] == static_cast<unsigned int>(spv::Decoration::SpecId)) {
                specIds[words[1]] = words[3];
            } else if (opcode == spv::Op::OpTypeArray && wordCount == 4) {
                lengths[words[1]] = words[3];
            } else if (opcode == spv::Op::OpTypeStruct && wordCount >= 2) {
                structures[words[1]] = std::vector<unsigned int>(words + 2, words + wordCount);
            } else if (opcode == spv::Op::OpSpecConstantComposite && wordCount >= 4) {
                composites[words[2]] = std::vector<unsigned int>(words + 3, words + wordCount);
            } else if ((opcode == spv::Op::OpConstant || opcode == spv::Op::OpSpecConstant) && wordCount == 4) {
                values[words[2]] = words[3];
                if (specIds.count(words[2]) != 0)
                    dependencies[words[2]].insert(specIds.at(words[2]));
            } else if (opcode == spv::Op::OpSpecConstantOp && wordCount == 6 &&
                       words[3] == static_cast<unsigned int>(spv::Op::OpIAdd) &&
                       values.count(words[4]) != 0 && values.count(words[5]) != 0) {
                values[words[2]] = values.at(words[4]) + values.at(words[5]);
                dependencies[words[2]] = dependencies[words[4]];
                dependencies[words[2]].insert(dependencies[words[5]].begin(), dependencies[words[5]].end());
            } else if (opcode == spv::Op::OpSpecConstantOp && wordCount == 6 &&
                       words[3] == static_cast<unsigned int>(spv::Op::OpCompositeExtract) &&
                       composites.count(words[4]) != 0) {
                const auto& components = composites.at(words[4]);
                ASSERT_LT(words[5], components.size());
                const unsigned int component = components[words[5]];
                ASSERT_NE(values.find(component), values.end());
                values[words[2]] = values.at(component);
                dependencies[words[2]] = dependencies[component];
            }
            offset += wordCount;
        }
        std::set<std::string> found;
        for (const auto& member : members) {
            SCOPED_TRACE(member.second);
            ASSERT_NE(structures.find(member.first.first), structures.end());
            const auto& types = structures.at(member.first.first);
            ASSERT_LT(member.first.second, types.size());
            ASSERT_NE(lengths.find(types[member.first.second]), lengths.end());
            const unsigned int length = lengths.at(types[member.first.second]);
            ASSERT_NE(values.find(length), values.end());
            EXPECT_EQ(values.at(length), expected.at(member.second));
            EXPECT_EQ(dependencies[length], std::set<unsigned int>({0}));
            found.insert(member.second);
        }
        EXPECT_EQ(found.size(), expected.size());
    }

    // Each source local must describe the same pointer that the function uses,
    // including locals with identical names in different compilation units.
    void expectDebugLocals(const std::vector<unsigned int>& spirv,
                           const std::map<std::pair<std::string, std::string>, bool>& expected)
    {
        std::map<unsigned int, std::string> names;
        std::map<unsigned int, std::string> strings;
        std::map<unsigned int, std::string> debugNames;
        std::map<unsigned int, unsigned int> variables;
        std::map<unsigned int, std::vector<unsigned int>> declarations;
        std::map<unsigned int, unsigned int> stores;
        std::map<unsigned int, unsigned int> loads;
        std::set<unsigned int> debugImports;
        unsigned int function = 0;
        ASSERT_GE(spirv.size(), 5u);
        for (size_t offset = 5; offset < spirv.size();) {
            const auto* words = &spirv[offset];
            const unsigned int wordCount = words[0] >> spv::WordCountShift;
            const auto opcode = static_cast<spv::Op>(words[0] & spv::OpCodeMask);
            ASSERT_GT(wordCount, 0u);
            ASSERT_LE(offset + wordCount, spirv.size());
            if (opcode == spv::Op::OpName && wordCount >= 3) {
                names[words[1]] = decodeString(words + 2, wordCount - 2);
            } else if (opcode == spv::Op::OpString && wordCount >= 3) {
                strings[words[1]] = decodeString(words + 2, wordCount - 2);
            } else if (opcode == spv::Op::OpExtInstImport && wordCount >= 3 &&
                       decodeString(words + 2, wordCount - 2).find("NonSemantic.Shader.DebugInfo.") == 0) {
                debugImports.insert(words[1]);
            } else if (opcode == spv::Op::OpFunction && wordCount >= 3) {
                function = words[2];
            } else if (opcode == spv::Op::OpFunctionEnd) {
                function = 0;
            } else if (opcode == spv::Op::OpVariable && wordCount >= 4 &&
                       words[3] == static_cast<unsigned int>(spv::StorageClass::Function)) {
                variables[words[2]] = function;
            } else if (opcode == spv::Op::OpStore && wordCount >= 3) {
                ++stores[words[1]];
            } else if (opcode == spv::Op::OpLoad && wordCount >= 4) {
                ++loads[words[3]];
            } else if (opcode == spv::Op::OpExtInst && wordCount >= 6 && debugImports.count(words[3]) != 0) {
                if (words[4] == NonSemanticShaderDebugInfoDebugLocalVariable) {
                    debugNames[words[2]] = strings.at(words[5]);
                } else if (words[4] == NonSemanticShaderDebugInfoDebugDeclare && wordCount >= 8) {
                    ASSERT_NE(variables.find(words[6]), variables.end());
                    EXPECT_EQ(variables.at(words[6]), function);
                    declarations[words[6]].push_back(words[5]);
                }
            }
            offset += wordCount;
        }
        for (const auto& local : expected) {
            SCOPED_TRACE(local.first.first + ":" + local.first.second);
            std::vector<unsigned int> matches;
            for (const auto& variable : variables) {
                if (names[variable.second] == local.first.first && names[variable.first] == local.first.second)
                    matches.push_back(variable.first);
            }
            ASSERT_EQ(matches.size(), 1u);
            const unsigned int variable = matches.front();
            ASSERT_EQ(declarations[variable].size(), 1u);
            EXPECT_EQ(debugNames.at(declarations[variable].front()), local.first.second);
            EXPECT_EQ(stores[variable], local.second ? 1u : 0u);
            EXPECT_EQ(loads[variable], local.second ? 1u : 0u);
        }
    }

    void expectFunctionDimensions(const std::vector<unsigned int>& spirv,
                                  const std::vector<unsigned int>& expectedSpecIds)
    {
        std::map<unsigned int, std::string> names;
        std::map<unsigned int, unsigned int> specIds;
        std::map<unsigned int, unsigned int> dimensions;
        std::map<unsigned int, unsigned int> pointees;
        std::map<unsigned int, std::vector<unsigned int>> parameters;
        std::vector<unsigned int> calls;
        unsigned int function = 0;
        ASSERT_GE(spirv.size(), 5u);
        for (size_t offset = 5; offset < spirv.size();) {
            const auto* words = &spirv[offset];
            const unsigned int wordCount = words[0] >> spv::WordCountShift;
            const auto opcode = static_cast<spv::Op>(words[0] & spv::OpCodeMask);
            ASSERT_GT(wordCount, 0u);
            ASSERT_LE(offset + wordCount, spirv.size());
            if (opcode == spv::Op::OpName && wordCount >= 3) {
                names[words[1]] = decodeString(words + 2, wordCount - 2);
            } else if (opcode == spv::Op::OpDecorate && wordCount == 4 &&
                       words[2] == static_cast<unsigned int>(spv::Decoration::SpecId)) {
                specIds[words[1]] = words[3];
            } else if ((opcode == spv::Op::OpTypeArray || opcode == spv::Op::OpTypeVectorIdEXT) && wordCount == 4) {
                dimensions[words[1]] = words[3];
            } else if (opcode == spv::Op::OpTypePointer && wordCount == 4) {
                pointees[words[1]] = words[3];
            } else if (opcode == spv::Op::OpFunction && wordCount >= 3) {
                function = words[2];
            } else if (opcode == spv::Op::OpFunctionParameter && wordCount == 3) {
                parameters[function].push_back(words[1]);
            } else if (opcode == spv::Op::OpFunctionCall && wordCount >= 4) {
                calls.push_back(words[3]);
            }
            offset += wordCount;
        }
        std::vector<unsigned int> actual;
        std::set<unsigned int> callees;
        for (const auto callee : calls) {
            if (names[callee].find("first(") != 0)
                continue;
            ASSERT_EQ(parameters[callee].size(), 1u);
            unsigned int type = parameters[callee].front();
            if (pointees.count(type) != 0)
                type = pointees.at(type);
            ASSERT_NE(dimensions.find(type), dimensions.end());
            ASSERT_NE(specIds.find(dimensions.at(type)), specIds.end());
            actual.push_back(specIds.at(dimensions.at(type)));
            callees.insert(callee);
        }
        std::sort(actual.begin(), actual.end());
        EXPECT_EQ(actual, expectedSpecIds);
        EXPECT_EQ(callees.size(), expectedSpecIds.size());
    }

    std::vector<std::string> linkedSources(std::vector<std::string> declarations, const std::string& expression)
    {
        std::string main;
        for (const auto& declaration : declarations)
            main += declaration;
        main += "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n"
                "uint helper();\nvoid main() { outputData.result = helper() + " + expression + "; }\n";
        std::reverse(declarations.begin(), declarations.end());
        std::string helper;
        for (const auto& declaration : declarations)
            helper += declaration;
        helper += "uint helper() { return " + expression + "; }\n";
        return {main, helper};
    }
};

TEST_F(HeapBlockInstanceTest, GlobalMembersPreserveDescriptorAccessAndOffsets)
{
    const std::string source = R"(
layout(constant_id = 0) const uint resourceOffset = 128;
layout(push_constant) uniform Parameters { uint samplerOffset; uint index; } parameters;
layout(buffer_type, std430) buffer Output { vec4 color; uint count; };

layout(heap_offset = resourceOffset) resourceheap Resources {
    uint resourceCount;
    Output outputBuffer;
    texture2D textures[];
};
layout(heap_offset = parameters.samplerOffset) samplerheap Sampling {
    uint samplerCount;
    sampler samplers[];
};

void main()
{
    uint index = (parameters.index + resourceCount + samplerCount) & 1u;
    outputBuffer.color = textureLod(sampler2D(textures[nonuniformEXT(index)], samplers[nonuniformEXT(index)]),
                                   vec2(0.5), 0.0);
    outputBuffer.count = resourceCount + samplerCount;
}
)";
    std::vector<unsigned int> spirv;
    std::string error;
    ASSERT_TRUE(compile({source}, spirv, error)) << error;
    EXPECT_FALSE(spirv.empty());
}

TEST_F(HeapBlockInstanceTest, ReorderedDeclarationsKeepTheirHeapAndLayout)
{
    for (const bool named : {false, true}) {
        SCOPED_TRACE(named);
        const std::vector<std::string> declarations = {
            std::string("layout(heap_offset = 64) resourceheap First { uint first; }") +
                (named ? " firstHeap;\n" : ";\n"),
            std::string("layout(heap_offset = 128) resourceheap Second { uvec2 second; }") +
                (named ? " secondHeap;\n" : ";\n"),
            std::string("layout(heap_offset = 256) samplerheap Third { uvec4 third; }") +
                (named ? " thirdHeap;\n" : ";\n"),
        };
        const std::string expression = named ? "firstHeap.first + secondHeap.second.x + thirdHeap.third.x"
                                             : "first + second.x + third.x";
        auto sources = linkedSources(declarations, expression);
        for (int order = 0; order < 2; ++order) {
            SCOPED_TRACE(order);
            std::vector<unsigned int> spirv;
            std::string error;
            ASSERT_TRUE(compile(sources, spirv, error)) << error;
            expectHeapAccesses(spirv, {{"first", {spv::BuiltIn::ResourceHeapEXT, 64}},
                                     {"second", {spv::BuiltIn::ResourceHeapEXT, 128}},
                                     {"third", {spv::BuiltIn::SamplerHeapEXT, 256}}});
            std::reverse(sources.begin(), sources.end());
        }
    }
}

TEST_F(HeapBlockInstanceTest, DifferentHeapInterfacesCanShareABlockName)
{
    auto sources = linkedSources({
        "layout(heap_offset = 64) resourceheap Shared { uint resourceValue; };\n",
        "layout(heap_offset = 128) samplerheap Shared { uvec2 samplerValue; };\n",
    }, "resourceValue + samplerValue.x");
    for (int order = 0; order < 2; ++order) {
        SCOPED_TRACE(order);
        std::vector<unsigned int> spirv;
        std::string error;
        ASSERT_TRUE(compile(sources, spirv, error)) << error;
        expectHeapAccesses(spirv, {{"resourceValue", {spv::BuiltIn::ResourceHeapEXT, 64}},
                                 {"samplerValue", {spv::BuiltIn::SamplerHeapEXT, 128}}});
        std::reverse(sources.begin(), sources.end());
    }
}

TEST_F(HeapBlockInstanceTest, DynamicHeapOffsetsUseTheLinkedPushConstant)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        for (const bool named : {false, true}) {
            SCOPED_TRACE(named);
            const std::string parameters =
                "layout(push_constant) uniform Parameters { uint offsetValue; } parameters;\n";
            const std::string extra =
                "layout(set = 0, binding = 1, std430) readonly buffer Extra { uint unused; } extra;\n";
            const std::string heap = "layout(heap_offset = parameters.offsetValue) " + std::string(storage) +
                " Data { uint value; }" + (named ? " heap;\n" : ";\n");
            const std::string value = named ? "heap.value" : "value";
            for (const bool mainDeclaresHeap : {false, true}) {
                SCOPED_TRACE(mainDeclaresHeap);
                std::vector<std::string> sources = {
                    (mainDeclaresHeap ? parameters + extra + heap : "") +
                        "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n"
                        "uint helper();\nvoid main() { outputData.result = helper()" +
                        (mainDeclaresHeap ? " + " + value : "") + "; }\n",
                    extra + parameters + heap + "uint helper() { return parameters.offsetValue + " +
                        value + " + " + value + "; }\n",
                };
                for (int order = 0; order < 2; ++order) {
                    SCOPED_TRACE(order);
                    std::vector<unsigned int> spirv;
                    std::string error;
                    ASSERT_TRUE(compile(sources, spirv, error)) << error;
                    expectDynamicOffsets(spirv, mainDeclaresHeap ? 3u : 2u);
                    std::reverse(sources.begin(), sources.end());
                }
            }
        }
    }
}

TEST_F(HeapBlockInstanceTest, SpecializedHeapOffsetsKeepTheirDependencies)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        for (const bool named : {false, true}) {
            SCOPED_TRACE(named);
            for (const bool sharedArrayLength : {false, true}) {
                SCOPED_TRACE(sharedArrayLength);
                std::vector<std::string> constants = {
                    "layout(constant_id = 0) const uint A = 16u;\n",
                    "layout(constant_id = 1) const uint B = 64u;\n",
                };
                std::vector<std::string> sources;
                for (const bool main : {true, false}) {
                    const std::string array = main ? "mainArray" : "helperArray";
                    const std::string length = sharedArrayLength ? array + ".length()" : "A";
                    std::string source = constants[0] + constants[1];
                    if (sharedArrayLength)
                        source += "uint " + array + "[A];\n";
                    source += "const uint computedOffset = " + length + " * 4u;\n"
                        "const uint heapOffset = computedOffset;\n"
                        "layout(heap_offset = heapOffset) " + storage + " Data { uint value; }" +
                        (named ? " heap;\n" : ";\n");
                    const std::string expression = "B + " + length + " + " + (named ? "heap.value" : "value");
                    if (main)
                        source += "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n"
                            "uint helper();\nvoid main() { outputData.result = helper() + " + expression + "; }\n";
                    else
                        source += "uint helper() { return " + expression + "; }\n";
                    sources.push_back(source);
                    std::reverse(constants.begin(), constants.end());
                }
                for (int order = 0; order < 2; ++order) {
                    SCOPED_TRACE(order);
                    std::vector<unsigned int> spirv;
                    std::string error;
                    ASSERT_TRUE(compile(sources, spirv, error)) << error;
                    expectSpecializedOffsets(spirv);
                    std::reverse(sources.begin(), sources.end());
                }
            }
        }
    }
}

TEST_F(HeapBlockInstanceTest, SpecializationSizedHeapMembersPreserveTheAccessChain)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        for (const bool named : {false, true}) {
            SCOPED_TRACE(named);
            for (const auto* size : {"16", "Size", "Size + 8u"}) {
                SCOPED_TRACE(size);
                for (const bool buffer : {false, true}) {
                    if (buffer && std::string(storage) == "samplerheap")
                        continue;
                    SCOPED_TRACE(buffer);
                    const std::string array = "uint values[" + std::string(size) + "];";
                    std::string source = "layout(constant_id = 0) const uint Size = 16u;\n";
                    if (buffer)
                        source += "layout(buffer_type, std430) buffer Data { " + array + " };\n";
                    source += "layout(heap_offset = 64) " + std::string(storage) + " Heap { " +
                        (buffer ? "Data data;" : array) + " }" + (named ? " heap;\n" : ";\n") +
                        "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n"
                        "void main() { outputData.result = " + (named ? "heap." : "") +
                        (buffer ? "data." : "") + "values[0]; }\n";
                    std::vector<unsigned int> spirv;
                    std::string error;
                    ASSERT_TRUE(compile({source}, spirv, error)) << error;
                    expectStoredHeapLoad(spirv);
                }
            }
        }
    }
}

TEST_F(HeapBlockInstanceTest, LinkedArrayDimensionsKeepTheirSpecializationConstant)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        for (const bool named : {false, true}) {
            SCOPED_TRACE(named);
            for (const std::string kind : {"pod", "struct", "buffer", "reference", "cast"}) {
                if (kind == "buffer" && std::string(storage) == "samplerheap")
                    continue;
                SCOPED_TRACE(kind);
                std::vector<std::string> constants = {
                    "layout(constant_id = 0) const uint A = 16u;\n",
                    "layout(constant_id = 1) const uint B = 64u;\n",
                };
                std::vector<std::string> sources;
                for (int unit = 0; unit < 2; ++unit) {
                    const std::string index = std::to_string(unit);
                    const std::string type = "Data" + index;
                    const std::string member = "values" + index;
                    const std::string array = "uint " + member + "[A];";
                    std::string source = constants[0] + constants[1];
                    if (kind == "struct")
                        source += "struct " + type + " { " + array + " };\n";
                    else if (kind == "buffer")
                        source += "layout(buffer_type, std430) buffer " + type + " { " + array + " };\n";
                    else if (kind == "reference" || kind == "cast")
                        source += "#extension GL_EXT_buffer_reference : require\n"
                            "#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require\n"
                            "layout(buffer_reference, std430) buffer " + type + ";\n"
                            "layout(buffer_reference, std430) buffer " + type + " { " +
                            (kind == "reference" ? type + " next; " : "") + array + " };\n";
                    const std::string heapMember = kind == "pod" ? array : kind == "cast" ?
                        "uint64_t address" + index + ";" : type + " data" + index + ";";
                    source += "layout(heap_offset = " + std::to_string(64 + 64 * unit) + ") " + storage +
                        " Heap" + index + " { " + heapMember +
                        " }" + (named ? " heap" + index : "") + ";\n";
                    const std::string prefix = named ? "heap" + index + "." : "";
                    const std::string value = kind == "cast" ?
                        type + "(" + prefix + "address" + index + ")." + member + "[0]" : prefix +
                        (kind == "pod" ? "" : "data" + index + ".") +
                        (kind == "reference" ? "next." : "") + member + "[0]";
                    if (unit == 0)
                        source += "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n"
                            "uint helper();\nvoid main() { outputData.result = B + " + value + " + helper(); }\n";
                    else
                        source += "uint helper() { return B + " + value + "; }\n";
                    sources.push_back(source);
                    std::reverse(constants.begin(), constants.end());
                }
                for (int order = 0; order < 2; ++order) {
                    SCOPED_TRACE(order);
                    std::vector<unsigned int> spirv;
                    std::string error;
                    ASSERT_TRUE(compile(sources, spirv, error)) << error;
                    expectSpecializedArrayLengths(spirv, {{"values0", 16}, {"values1", 16}});
                    std::reverse(sources.begin(), sources.end());
                }
            }
        }
    }
}

TEST_F(HeapBlockInstanceTest, SharedSpecializationSizedMembersStillMatchAcrossUnits)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        for (const bool named : {false, true}) {
            SCOPED_TRACE(named);
            for (const bool alias : {false, true}) {
                SCOPED_TRACE(alias);
                const std::string constants = "layout(constant_id = 0) const uint A = 16u;\n"
                    "layout(constant_id = 1) const uint B = 64u;\n";
                const std::string reversed = "layout(constant_id = 1) const uint B = 64u;\n"
                    "layout(constant_id = 0) const uint A = 16u;\n";
                const std::string heap = "const uint Count = A + 8u;\nlayout(heap_offset = 64) " +
                    std::string(storage) + " Shared { uint values[" + (alias ? "Count" : "A") +
                    "]; }" + (named ? " heap;\n" : ";\n");
                const std::string value = named ? "heap.values[0]" : "values[0]";
                std::vector<std::string> sources = {
                    constants + heap +
                        "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n"
                        "uint helper();\nvoid main() { outputData.result = B + " + value + " + helper(); }\n",
                    reversed + heap + "uint helper() { return B + " + value + "; }\n",
                };
                for (int order = 0; order < 2; ++order) {
                    SCOPED_TRACE(order);
                    std::vector<unsigned int> spirv;
                    std::string error;
                    ASSERT_TRUE(compile(sources, spirv, error)) << error;
                    expectSpecializedArrayLengths(spirv, {{"values", alias ? 24u : 16u}});
                    std::reverse(sources.begin(), sources.end());
                }
            }
        }
    }
}

TEST_F(HeapBlockInstanceTest, SpecializationSizedFunctionArgumentsKeepMatchingTypes)
{
    const std::string size = "layout(constant_id = 0) const uint Size = 16u;\n";
    const std::string other = "layout(constant_id = 1) const uint Other = 64u;\n";
    std::vector<std::string> sources = {
        size + other + "layout(heap_offset = 64) resourceheap Heap { uint values[Size]; };\n"
            "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n"
            "uint first(uint data[Size]);\nvoid main() { outputData.result = first(values); }\n",
        other + size + "uint last(uint data[Size]) { return data[0]; }\n"
            "uint first(uint data[Size]) { return last(data); }\n",
    };
    for (int order = 0; order < 2; ++order) {
        SCOPED_TRACE(order);
        std::vector<unsigned int> spirv;
        std::string error;
        ASSERT_TRUE(compile(sources, spirv, error)) << error;
        expectSpecializedArrayLengths(spirv, {{"values", 16}});
        expectFunctionDimensions(spirv, {0});
        std::reverse(sources.begin(), sources.end());
    }
}

TEST_F(HeapBlockInstanceTest, SpecializationSizedOverloadsKeepDistinctTypes)
{
    const std::string a = "layout(constant_id = 0) const uint A = 16u;\n";
    const std::string b = "layout(constant_id = 1) const uint B = 16u;\n";
    const std::string firstA = "uint first(uint data[A]) { return data[0] + 1u; }\n";
    const std::string firstB = "uint first(uint data[B]) { return data[0] + 2u; }\n";
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        for (const bool named : {false, true}) {
            SCOPED_TRACE(named);
            const std::string heap = "layout(heap_offset = 64) " + std::string(storage) +
                " Heap { uint a[A]; uint b[B]; }" + (named ? " heap;\n" : ";\n");
            const std::string prefix = named ? "heap." : "";
            const std::string entry = "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n"
                "void main() { outputData.result = first(" + prefix + "a) + first(" + prefix + "b); }\n";
            std::vector<unsigned int> spirv;
            std::string error;
            ASSERT_TRUE(compile({a + b + heap + firstA + firstB + entry}, spirv, error)) << error;
            expectFunctionDimensions(spirv, {0, 1});

            const std::vector<std::string> units = {
                a + b + heap + "uint first(uint data[A]);\nuint first(uint data[B]);\n" + entry,
                b + a + firstA,
                a + b + "uint unusedBeforeFunction;\n" + firstB,
            };
            std::vector<unsigned int> order = {0, 1, 2};
            do {
                SCOPED_TRACE(std::to_string(order[0]) + std::to_string(order[1]) + std::to_string(order[2]));
                ASSERT_TRUE(compile({units[order[0]], units[order[1]], units[order[2]]}, spirv, error)) << error;
                expectFunctionDimensions(spirv, {0, 1});
            } while (std::next_permutation(order.begin(), order.end()));
        }
    }
}

TEST_F(HeapBlockInstanceTest, RejectsIncompatibleSpecializationSizedArguments)
{
    const std::string constants = "layout(constant_id = 0) const uint A = 16u;\n"
        "layout(constant_id = 1) const uint B = 16u;\n";
    const std::string definition = "uint first(uint data[B]) { return data[0]; }\n";
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        const std::string heap = std::string(storage) + " Heap { uint values[A]; };\n";
        const std::string entry = "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n"
            "void main() { outputData.result = first(values); }\n";
        std::vector<unsigned int> spirv;
        std::string error;
        ASSERT_FALSE(compile({constants + heap + definition + entry}, spirv, error));
        EXPECT_NE(error.find("no matching overloaded function"), std::string::npos) << error;

        std::vector<std::string> sources = {
            constants + heap + "uint first(uint data[A]);\n" + entry,
            constants + definition,
        };
        for (int order = 0; order < 2; ++order) {
            SCOPED_TRACE(order);
            ASSERT_FALSE(compile(sources, spirv, error));
            EXPECT_NE(error.find("No function definition"), std::string::npos) << error;
            std::reverse(sources.begin(), sources.end());
        }
    }
}

TEST_F(HeapBlockInstanceTest, SpecializationSizedTypeParameterOverloadsRemainDistinct)
{
    const std::string source = "#extension GL_EXT_long_vector : require\n"
        "layout(constant_id = 0) const uint A = 16u;\n"
        "layout(constant_id = 1) const uint B = 16u;\n"
        "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n"
        "uint first(vector<uint, A> data) { return data[0] + 1u; }\n"
        "uint first(vector<uint, B> data) { return data[0] + 2u; }\n"
        "void main() { outputData.result = first(vector<uint, A>(1u)) + first(vector<uint, B>(2u)); }\n";
    std::vector<unsigned int> spirv;
    std::string error;
    ASSERT_TRUE(compile({source}, spirv, error)) << error;
    expectFunctionDimensions(spirv, {0, 1});
}

TEST_F(HeapBlockInstanceTest, SpecializedArrayAliasesRemainConstantsWithDebugInfo)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        for (const bool named : {false, true}) {
            SCOPED_TRACE(named);
            const std::string source = "layout(constant_id = 0) const uint A = 16u;\n"
                "layout(constant_id = 1) const uint B = 64u;\n"
                "const uvec2 Pair = uvec2(A, B);\nconst uint Count = Pair.x;\n"
                "layout(heap_offset = 64) " + std::string(storage) + " Heap { uint values[Count]; }" +
                (named ? " heap;\n" : ";\n") +
                "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n"
                "void main() { outputData.result = " + (named ? "heap." : "") + "values[0]; }\n";
            for (const bool debug : {false, true}) {
                SCOPED_TRACE(debug);
                std::vector<unsigned int> spirv;
                std::string error;
                ASSERT_TRUE(compile({source}, spirv, error, debug)) << error;
                expectStoredHeapLoad(spirv);
                expectSpecializedArrayLengths(spirv, {{"values", 16}});
            }
        }
    }
}

TEST_F(HeapBlockInstanceTest, LinkedDebugDeclarationsKeepTheirVariableIdentity)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        for (const bool named : {false, true}) {
            SCOPED_TRACE(named);
            const std::string heap = "layout(heap_offset = 64) " + std::string(storage) +
                " Heap { uint word; }" + (named ? " heap;\n" : ";\n");
            const std::string value = named ? "heap.word" : "word";
            const std::string output = "layout(set = 0, binding = 0, std430) buffer Result { uint result; } outputData;\n";
            std::vector<std::string> sources = {
                heap + output + "uint helper();\nvoid main() {\nuint value = " + value +
                    ";\nuint unusedMain;\noutputData.result = value + helper();\n}\n",
                heap + output + "uint helper() {\nuint value = " + value +
                    ";\nuint unusedHelper;\nreturn value;\n}\n",
            };
            for (int order = 0; order < 2; ++order) {
                SCOPED_TRACE(order);
                std::vector<unsigned int> spirv;
                std::string error;
                ASSERT_TRUE(compile(sources, spirv, error, true)) << error;
                expectDebugLocals(spirv, {{{"main", "value"}, true}, {{"helper(", "value"}, true},
                                         {{"main", "unusedMain"}, false}, {{"helper(", "unusedHelper"}, false}});
                std::reverse(sources.begin(), sources.end());
            }
        }
    }
}

TEST_F(HeapBlockInstanceTest, RejectsDifferentSpecializationSizedMemberTypes)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        for (const std::string mismatch : {"spec-id", "symbol", "alias", "expression"}) {
            SCOPED_TRACE(mismatch);
            std::vector<std::string> sources;
            for (int unit = 0; unit < 2; ++unit) {
                std::string source = "layout(constant_id = " + std::to_string(mismatch == "spec-id" ? unit : 0) +
                    ") const uint A = 16u;\nlayout(constant_id = 2) const uint B = 16u;\n";
                source += "const uint Count = " + std::string(mismatch == "alias" && unit == 1 ? "B" : "A") + " + 8u;\n";
                const std::string size = mismatch == "alias" ? "Count" :
                    mismatch == "expression" ? "A + 8u" : mismatch == "symbol" && unit == 1 ? "B" : "A";
                source += "layout(heap_offset = 64) " + std::string(storage) + " Shared { uint values[" + size + "]; };\n";
                source += unit == 0 ? "uint helper();\nvoid main() { uint value = values[0] + helper(); }\n" :
                    "uint helper() { return values[0]; }\n";
                sources.push_back(source);
            }
            for (int order = 0; order < 2; ++order) {
                SCOPED_TRACE(order);
                std::vector<unsigned int> spirv;
                std::string error;
                ASSERT_FALSE(compile(sources, spirv, error));
                EXPECT_NE(error.find("Member names and types must match"), std::string::npos) << error;
                std::reverse(sources.begin(), sources.end());
            }
        }
    }
}

TEST_F(HeapBlockInstanceTest, RejectsWritesToGlobalHeapMembers)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        for (const auto* operation : {"value = 1u;", "++value;", "writeValue(value);"}) {
            SCOPED_TRACE(operation);
            const std::string source = std::string(storage) + " Data { uint value; };\n"
                "void writeValue(out uint outputValue) { outputValue = 1u; }\n"
                "void main() { " + operation + " }\n";
            std::vector<unsigned int> spirv;
            std::string error;
            ASSERT_FALSE(compile({source}, spirv, error));
            EXPECT_NE(error.find("can't modify a descriptor heap"), std::string::npos) << error;
        }
    }
}

TEST_F(HeapBlockInstanceTest, RejectsGlobalMemberNameCollisions)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        const std::string block = std::string(storage) + " Data { uint value; };\n";
        for (const bool blockFirst : {false, true}) {
            SCOPED_TRACE(blockFirst);
            const std::string source = (blockFirst ? block + "uint value;\n" : "uint value;\n" + block) +
                "void main() {}\n";
            std::vector<unsigned int> spirv;
            std::string error;
            ASSERT_FALSE(compile({source}, spirv, error));
            EXPECT_NE(error.find(blockFirst ? "redefinition" : "already has a name at global scope"),
                      std::string::npos) << error;
        }
    }
}

TEST_F(HeapBlockInstanceTest, RejectsArraysOfHeapBlocks)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        for (const auto* size : {"", "2"}) {
            SCOPED_TRACE(size);
            const std::string source = std::string(storage) + " Data { uint value; } instance[" + size +
                "];\nvoid main() {}\n";
            std::vector<unsigned int> spirv;
            std::string error;
            ASSERT_FALSE(compile({source}, spirv, error));
            EXPECT_NE(error.find("block cannot itself be an array"), std::string::npos) << error;
        }
    }
}

TEST_F(HeapBlockInstanceTest, BlockNamesRemainRequired)
{
    for (const auto* storage : {"resourceheap", "samplerheap"}) {
        SCOPED_TRACE(storage);
        const std::string source = std::string(storage) + " { uint value; } instance;\nvoid main() {}\n";
        std::vector<unsigned int> spirv;
        std::string error;
        ASSERT_FALSE(compile({source}, spirv, error));
        EXPECT_NE(error.find("syntax error"), std::string::npos) << error;
    }
}

TEST_F(HeapBlockInstanceTest, OrdinaryDescriptorHeapBlocksStillRequireInstances)
{
    for (const auto* storage : {"uniform", "buffer"}) {
        SCOPED_TRACE(storage);
        const std::string source = "layout(descriptor_heap, std430) " + std::string(storage) +
            " Data { uint value; };\nvoid main() {}\n";
        std::vector<unsigned int> spirv;
        std::string error;
        ASSERT_FALSE(compile({source}, spirv, error));
        EXPECT_NE(error.find("decorated block should be explicitly"), std::string::npos) << error;
    }
}

} // anonymous namespace
} // namespace glslangtest
