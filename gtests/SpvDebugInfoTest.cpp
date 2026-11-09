// Copyright (C) 2026 NVIDIA Corporation.
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

// Tests for NonSemantic.Shader.DebugInfo (NSDI) features.

#include "TestFixture.h"
#include "SPIRV/NonSemanticShaderDebugInfo.h"
#include "glslang/Public/ResourceLimits.h"
#include <gtest/gtest.h>
#include <cstdint>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace glslangtest {
namespace {

std::string decodeLiteralString(const uint32_t* words, size_t wordCount)
{
    std::string result;
    for (size_t wordIndex = 0; wordIndex < wordCount; ++wordIndex) {
        for (unsigned int byteIndex = 0; byteIndex < 4; ++byteIndex) {
            const char character = static_cast<char>((words[wordIndex] >> (8 * byteIndex)) & 0xff);
            if (character == '\0')
                return result;
            result.push_back(character);
        }
    }
    return result;
}

std::map<std::string, size_t> countDebugTypes(const std::vector<uint32_t>& spirv,
                                            NonSemanticShaderDebugInfoInstructions instruction)
{
    if (spirv.size() < 5 || spirv[0] != spv::MagicNumber)
        return {};

    std::vector<std::string> strings(spirv[3]);
    std::map<std::string, size_t> counts;
    uint32_t debugInfoImportId = 0;
    for (size_t offset = 5; offset < spirv.size();) {
        const uint32_t wordCount = spirv[offset] >> spv::WordCountShift;
        const spv::Op opcode = static_cast<spv::Op>(spirv[offset] & spv::OpCodeMask);
        if (wordCount == 0 || offset + wordCount > spirv.size())
            return {};

        if (opcode == spv::Op::OpExtInstImport && wordCount >= 3) {
            const std::string name = decodeLiteralString(&spirv[offset + 2], wordCount - 2);
            if (name == "NonSemantic.Shader.DebugInfo.100" || name == "NonSemantic.Shader.DebugInfo.101")
                debugInfoImportId = spirv[offset + 1];
        } else if (opcode == spv::Op::OpString && wordCount >= 3) {
            const uint32_t resultId = spirv[offset + 1];
            if (resultId < strings.size())
                strings[resultId] = decodeLiteralString(&spirv[offset + 2], wordCount - 2);
        } else if (opcode == spv::Op::OpExtInst && wordCount >= 6 && debugInfoImportId != 0 &&
                   spirv[offset + 3] == debugInfoImportId && spirv[offset + 4] == instruction) {
            const uint32_t nameId = spirv[offset + 5];
            if (nameId < strings.size())
                ++counts[strings[nameId]];
        }
        offset += wordCount;
    }
    return counts;
}

// Check the source-level member type, including array dimensions and the
// referenced struct. Validation alone cannot establish the intended shape.
void expectDebugReferenceMember(const std::vector<uint32_t>& spirv, const char* memberName,
                                const std::vector<uint32_t>& expectedDimensions, const char* referentName)
{
    ASSERT_GE(spirv.size(), 5u);
    ASSERT_EQ(spirv[0], spv::MagicNumber);
    std::vector<std::string> strings(spirv[3]);
    std::vector<uint32_t> constants(spirv[3]);
    std::vector<bool> isConstant(spirv[3]);
    std::vector<const uint32_t*> debugInstructions(spirv[3], nullptr);
    uint32_t debugImport = 0;
    for (size_t offset = 5; offset < spirv.size();) {
        const auto* words = &spirv[offset];
        const uint32_t wordCount = words[0] >> spv::WordCountShift;
        const auto opcode = static_cast<spv::Op>(words[0] & spv::OpCodeMask);
        ASSERT_GT(wordCount, 0u);
        ASSERT_LE(offset + wordCount, spirv.size());
        if (opcode == spv::Op::OpExtInstImport && wordCount >= 3) {
            const auto name = decodeLiteralString(words + 2, wordCount - 2);
            if (name == "NonSemantic.Shader.DebugInfo.100" || name == "NonSemantic.Shader.DebugInfo.101")
                debugImport = words[1];
        } else if (opcode == spv::Op::OpString && wordCount >= 3) {
            ASSERT_LT(words[1], strings.size());
            strings[words[1]] = decodeLiteralString(words + 2, wordCount - 2);
        } else if ((opcode == spv::Op::OpConstant || opcode == spv::Op::OpSpecConstant) && wordCount == 4) {
            ASSERT_LT(words[2], constants.size());
            constants[words[2]] = words[3];
            isConstant[words[2]] = true;
        } else if ((opcode == spv::Op::OpExtInst || opcode == spv::Op::OpExtInstWithForwardRefsKHR) &&
                   wordCount >= 5 && debugImport != 0 && words[3] == debugImport) {
            ASSERT_LT(words[2], debugInstructions.size());
            debugInstructions[words[2]] = words;
        }
        offset += wordCount;
    }

    std::vector<uint32_t> memberTypes;
    for (const auto* instruction : debugInstructions) {
        if (instruction == nullptr || instruction[4] != NonSemanticShaderDebugInfoDebugTypeMember)
            continue;
        ASSERT_GE(instruction[0] >> spv::WordCountShift, 7u);
        ASSERT_LT(instruction[5], strings.size());
        if (strings[instruction[5]] == memberName)
            memberTypes.push_back(instruction[6]);
    }
    ASSERT_EQ(memberTypes.size(), 1u) << memberName;
    const auto getInstruction = [&](uint32_t id) {
        return id < debugInstructions.size() ? debugInstructions[id] : nullptr;
    };
    const auto* current = getInstruction(memberTypes.front());
    ASSERT_NE(current, nullptr);
    std::vector<uint32_t> dimensions;
    while (current[4] == NonSemanticShaderDebugInfoDebugTypeArray) {
        const auto wordCount = current[0] >> spv::WordCountShift;
        ASSERT_GE(wordCount, 7u);
        // Accept either nested array types or several dimensions in one type.
        for (uint32_t operand = 6; operand < wordCount; ++operand) {
            ASSERT_LT(current[operand], constants.size());
            ASSERT_TRUE(isConstant[current[operand]]);
            dimensions.push_back(constants[current[operand]]);
        }
        ASSERT_LE(dimensions.size(), expectedDimensions.size());
        current = getInstruction(current[5]);
        ASSERT_NE(current, nullptr);
    }
    EXPECT_EQ(dimensions, expectedDimensions);
    ASSERT_EQ(current[4], NonSemanticShaderDebugInfoDebugTypePointer);
    ASSERT_GE(current[0] >> spv::WordCountShift, 8u);
    current = getInstruction(current[5]);
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current[4], NonSemanticShaderDebugInfoDebugTypeComposite);
    ASSERT_GE(current[0] >> spv::WordCountShift, 6u);
    ASSERT_LT(current[5], strings.size());
    EXPECT_EQ(strings[current[5]], referentName);
}

bool containsDebugTypeBasic(const std::vector<uint32_t>& spirv, const char* expectedName,
                            uint32_t expectedWidth, spv::FPEncoding expectedFPEncoding)
{
    if (spirv.size() < 5 || spirv[0] != spv::MagicNumber)
        return false;

    const uint32_t idBound = spirv[3];
    std::vector<std::string> strings(idBound);
    std::vector<uint32_t> constants(idBound);
    std::vector<bool> isConstant(idBound);
    uint32_t debugInfoImportId = 0;

    size_t end = spirv.size();

    // Resolve the IDs referenced by DebugTypeBasic before inspecting the instruction itself.
    // OpExtInstImport gives the result ID used to select the .101 debug-info instruction set,
    // OpString gives the source-level type name, and OpConstant gives the values of the width,
    // base encoding, flags, and optional FPEncoding operands.
    //
    // For example, the relevant SPIR-V for floate2m1_t has this shape:
    //   %debug = OpExtInstImport "NonSemantic.Shader.DebugInfo.101"
    //   %name = OpString "floate2m1_t"
    //   %width = OpConstant %uint 4
    //   %encoding = OpConstant %uint 3       ; NonSemanticShaderDebugInfoFloat
    //   %flags = OpConstant %uint 0          ; NonSemanticShaderDebugInfoNone
    //   %fpEncoding = OpConstant %uint 4225  ; Float4E2M1EXT
    //   %type = OpExtInst %void %debug DebugTypeBasic
    //               %name %width %encoding %flags %fpEncoding
    for (size_t offset = 5; offset < spirv.size();) {
        const uint32_t wordCount = spirv[offset] >> spv::WordCountShift;
        const spv::Op opcode = static_cast<spv::Op>(spirv[offset] & spv::OpCodeMask);
        if (wordCount == 0 || offset + wordCount > spirv.size())
            return false;

        if (opcode == spv::Op::OpFunction) {
            // SPIR-V's logical layout places imports, debug strings, constants, and global
            // debug-type instructions before the first OpFunction. Record that boundary while
            // resolving IDs so this pass can exit early and the subsequent DebugTypeBasic scan
            // can stop there as well.
            end = offset;
            break;
        }

        if (opcode == spv::Op::OpExtInstImport && wordCount >= 3) {
            const uint32_t resultId = spirv[offset + 1];
            if (resultId < idBound &&
                decodeLiteralString(&spirv[offset + 2], wordCount - 2) ==
                    "NonSemantic.Shader.DebugInfo.101") {
                debugInfoImportId = resultId;
            }
        } else if (opcode == spv::Op::OpString && wordCount >= 3) {
            const uint32_t resultId = spirv[offset + 1];
            if (resultId < idBound)
                strings[resultId] = decodeLiteralString(&spirv[offset + 2], wordCount - 2);
        } else if (opcode == spv::Op::OpConstant && wordCount == 4) {
            const uint32_t resultId = spirv[offset + 2];
            if (resultId < idBound) {
                constants[resultId] = spirv[offset + 3];
                isConstant[resultId] = true;
            }
        }

        offset += wordCount;
    }

    if (debugInfoImportId == 0)
        return false;

    const auto hasConstantValue = [&](uint32_t id, uint32_t value) {
        return id < idBound && isConstant[id] && constants[id] == value;
    };

    // A DebugTypeBasic with an FPEncoding has five operands after its instruction number:
    // Name, Size, Encoding, Flags, and FPEncoding. Including the five-word OpExtInst prefix,
    // that gives a word count of 10. Match the imported .101 instruction set and resolve each
    // operand ID through the OpString and OpConstant tables populated above.
    for (size_t offset = 5; offset < end;) {
        const uint32_t wordCount = spirv[offset] >> spv::WordCountShift;
        const spv::Op opcode = static_cast<spv::Op>(spirv[offset] & spv::OpCodeMask);
        if (wordCount == 0 || offset + wordCount > spirv.size())
            return false;

        if (opcode == spv::Op::OpExtInst && wordCount == 10 &&
            spirv[offset + 3] == debugInfoImportId &&
            spirv[offset + 4] == NonSemanticShaderDebugInfoDebugTypeBasic) {
            const uint32_t nameId = spirv[offset + 5];
            const uint32_t widthId = spirv[offset + 6];
            const uint32_t encodingId = spirv[offset + 7];
            const uint32_t flagsId = spirv[offset + 8];
            const uint32_t fpEncodingId = spirv[offset + 9];
            if (nameId < idBound && strings[nameId] == expectedName &&
                hasConstantValue(widthId, expectedWidth) &&
                hasConstantValue(encodingId, NonSemanticShaderDebugInfoFloat) &&
                hasConstantValue(flagsId, NonSemanticShaderDebugInfoNone) &&
                hasConstantValue(fpEncodingId, static_cast<uint32_t>(expectedFPEncoding))) {
                return true;
            }
        }

        offset += wordCount;
    }

    return false;
}

bool containsDebugEntryPoint(const std::vector<uint32_t>& spirv, const char* expectedCompilerSignature,
                             const char* expectedCommandLineArguments, const char* expectedCurrentWorkingDirectory)
{
    if (spirv.size() < 5 || spirv[0] != spv::MagicNumber)
        return false;

    const uint32_t idBound = spirv[3];
    std::vector<std::string> strings(idBound);
    uint32_t debugInfoImportId = 0;
    uint32_t compilerSignatureId = 0;
    uint32_t commandLineArgumentsId = 0;
    uint32_t currentWorkingDirectoryId = 0;

    for (size_t offset = 5; offset < spirv.size();) {
        const uint32_t wordCount = spirv[offset] >> spv::WordCountShift;
        const spv::Op opcode = static_cast<spv::Op>(spirv[offset] & spv::OpCodeMask);
        if (wordCount == 0 || offset + wordCount > spirv.size())
            return false;

        if (opcode == spv::Op::OpExtInstImport && wordCount >= 3) {
            if (decodeLiteralString(&spirv[offset + 2], wordCount - 2) ==
                "NonSemantic.Shader.DebugInfo.102") {
                debugInfoImportId = spirv[offset + 1];
            }
        } else if (opcode == spv::Op::OpString && wordCount >= 3) {
            const uint32_t resultId = spirv[offset + 1];
            if (resultId < idBound)
                strings[resultId] = decodeLiteralString(&spirv[offset + 2], wordCount - 2);
        } else if (opcode == spv::Op::OpExtInst && wordCount == 10 &&
                   spirv[offset + 3] == debugInfoImportId &&
                   spirv[offset + 4] == NonSemanticShaderDebugInfoDebugEntryPoint) {
            compilerSignatureId = spirv[offset + 7];
            commandLineArgumentsId = spirv[offset + 8];
            currentWorkingDirectoryId = spirv[offset + 9];
        }

        offset += wordCount;
    }

    return debugInfoImportId != 0 && compilerSignatureId < idBound &&
           strings[compilerSignatureId] == expectedCompilerSignature && commandLineArgumentsId < idBound &&
           strings[commandLineArgumentsId] == expectedCommandLineArguments && currentWorkingDirectoryId < idBound &&
           strings[currentWorkingDirectoryId] == expectedCurrentWorkingDirectory;
}

class SpvDebugInfoTest : public ::testing::Test {
protected:
    glslang::EShTargetClientVersion vulkanVersion = glslang::EShTargetVulkan_1_1;
    glslang::EShTargetLanguageVersion spirvVersion = glslang::EShTargetSpv_1_3;

    bool compileToSpirvWithDebugInfo(const std::string& source, std::vector<uint32_t>& spirv, std::string& error,
                                     const char* compilerSignature = nullptr,
                                     const char* commandLineArguments = nullptr,
                                     const char* currentWorkingDirectory = nullptr)
    {
        spirv.clear();
        error.clear();
        glslang::TShader shader(EShLangCompute);
        const char* str = source.c_str();
        shader.setStrings(&str, 1);
        shader.setEnvInput(glslang::EShSourceGlsl, EShLangCompute,
                           glslang::EShClientVulkan, 110);
        shader.setEnvClient(glslang::EShClientVulkan, vulkanVersion);
        shader.setEnvTarget(glslang::EShTargetSpv, spirvVersion);

        EShMessages messages = static_cast<EShMessages>(EShMsgDefault | EShMsgDebugInfo);
        if (!shader.parse(GetDefaultResources(), 450, false, messages)) {
            error = "COMPILATION_FAILED: " + std::string(shader.getInfoLog());
            return false;
        }

        glslang::TProgram program;
        program.addShader(&shader);
        if (!program.link(messages)) {
            error = "LINKING_FAILED: " + std::string(program.getInfoLog());
            return false;
        }

        glslang::SpvOptions opts;
        opts.generateDebugInfo = true;
        opts.emitNonSemanticShaderDebugInfo = true;
        opts.disableOptimizer = true;
        opts.compilerSignature = compilerSignature;
        opts.commandLineArguments = commandLineArguments;
        opts.currentWorkingDirectory = currentWorkingDirectory;

        glslang::GlslangToSpv(*program.getIntermediate(EShLangCompute), spirv, &opts);
        return true;
    }

    // Compile a GLSL compute shader with NonSemantic debug info enabled, targeting
    // Vulkan 1.1 / SPIR-V 1.3, and return the disassembly.
    std::string compileWithDebugInfo(const std::string& source)
    {
        std::vector<uint32_t> spirv;
        std::string error;
        if (!compileToSpirvWithDebugInfo(source, spirv, error))
            return error;

        std::ostringstream out;
        spv::Disassemble(out, spirv);
        return out.str();
    }
};

TEST_F(SpvDebugInfoTest, BasicDebugTypesAreReused)
{
    const std::string source = R"(
#version 460
#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_shader_explicit_arithmetic_types : require
#extension GL_EXT_shader_8bit_storage : require
#extension GL_EXT_shader_16bit_storage : require
layout(local_size_x = 1) in;
#define MEMBERS bool b; int8_t i8; uint8_t u8; int16_t i16; uint16_t u16; \
    int i; uint u; int64_t i64; uint64_t u64; float16_t f16; float f; double d;
layout(descriptor_heap, std430) buffer A { MEMBERS } heaps_a[];
layout(descriptor_heap, std430) buffer B { MEMBERS } heaps_b[];
layout(binding = 0, std430) buffer Output { uint u; float f; bool b; } result;
void main() {
    result.u = 1u;
    result.f = 1.0;
    result.b = true;
}
)";
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    std::vector<uint32_t> spirv;
    std::string error;
    ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;

    auto counts = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeBasic);
    for (const char* name : {"bool", "int8_t", "uint8_t", "int16_t", "uint16_t", "int", "uint",
                             "int64_t", "uint64_t", "float16_t", "float", "double"})
        EXPECT_EQ(counts[name], 1u) << name;
}

TEST_F(SpvDebugInfoTest, FloatDebugTypesAreReusedByEncoding)
{
    const std::string source = R"(
#version 460
#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_shader_explicit_arithmetic_types : require
#extension GL_EXT_shader_16bit_storage : require
#extension GL_EXT_bfloat16 : require
#extension GL_EXT_float_e4m3 : require
#extension GL_EXT_float_e5m2 : require
#extension GL_EXT_float_ue8m0 : require
#extension GL_EXT_float_mxint8 : require
layout(local_size_x = 1) in;
#define MEMBERS float16_t f16; bfloat16_t bf; floate4m3_t e4m3; floate5m2_t e5m2; \
    floatue8m0_t ue8m0; floatmxint8_t mxint8;
layout(descriptor_heap, std430) buffer A { MEMBERS } heaps_a[];
layout(descriptor_heap, std430) buffer B { MEMBERS } heaps_b[];
void main() {}
)";
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    std::vector<uint32_t> spirv;
    std::string error;
    ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;

    auto counts = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeBasic);
    EXPECT_EQ(counts["float16_t"], 1u);
    const struct {
        const char* name;
        uint32_t width;
        spv::FPEncoding encoding;
    } cases[] = {
        {"bfloat16_t", 16, spv::FPEncoding::BFloat16KHR},
        {"floate4m3_t", 8, spv::FPEncoding::Float8E4M3EXT},
        {"floate5m2_t", 8, spv::FPEncoding::Float8E5M2EXT},
        {"floatue8m0_t", 8, spv::FPEncoding::Float8UnsignedE8M0EXT},
        {"floatmxint8_t", 8, spv::FPEncoding::MXInt8EXT},
    };
    for (const auto& test : cases) {
        EXPECT_EQ(counts[test.name], 1u) << test.name;
        EXPECT_TRUE(containsDebugTypeBasic(spirv, test.name, test.width, test.encoding)) << test.name;
    }
}

TEST_F(SpvDebugInfoTest, OpaqueDebugTypesAreReusedAcrossDeclarations)
{
    const std::string source = R"(
#version 460
#extension GL_EXT_descriptor_heap : require
layout(local_size_x = 1) in;
layout(descriptor_heap) uniform texture2D textures_a[];
layout(descriptor_heap) uniform sampler samplers_a[];
layout(descriptor_heap) uniform textureCube cubes_a[];
layout(descriptor_heap) uniform texture2D textures_b[];
layout(descriptor_heap) uniform sampler samplers_b[];
layout(descriptor_heap) uniform textureCube cubes_b[];
void main() {}
)";
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    std::vector<uint32_t> spirv;
    std::string error;
    ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;

    auto counts = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeComposite);
    EXPECT_EQ(counts["texture2D"], 1u);
    EXPECT_EQ(counts["sampler"], 1u);
    EXPECT_EQ(counts["textureCube"], 1u);
}

TEST_F(SpvDebugInfoTest, AccelerationStructureDebugTypesAreReusedAcrossDescriptorPaths)
{
    const std::string header = R"(
#version 460
#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_structured_descriptor_heap : require
#extension GL_EXT_ray_query : require
layout(local_size_x = 1) in;
layout(binding = 1, std430) buffer Output { uint value; } outbuf;
)";
    const std::string bound = "layout(binding = 0) uniform accelerationStructureEXT scene;\n";
    const std::string heaps = R"(
layout(descriptor_heap) uniform accelerationStructureEXT asA[];
layout(descriptor_heap) uniform accelerationStructureEXT asB[];
resourceheap RayHeap {
    accelerationStructureEXT topLevelAs[2];
    accelerationStructureEXT backup;
} rayHeap;
)";
    std::string body = "void main() { rayQueryEXT query; uint result = 0u;\n";
    for (const char* expression : {"scene", "asA[0]", "asB[1]", "rayHeap.topLevelAs[0]", "rayHeap.backup"}) {
        body += std::string("rayQueryInitializeEXT(query, ") + expression +
            ", 0u, 255u, vec3(0.0), 0.0, vec3(1.0, 0.0, 0.0), 1000.0);\n";
        body += "result += rayQueryProceedEXT(query) ? 1u : 0u;\n";
    }
    body += "outbuf.value = result; }\n";
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    for (const auto& declarations : {bound + heaps, heaps + bound}) {
        const std::string source = header + declarations + body;
        SCOPED_TRACE(source);
        std::vector<uint32_t> spirv;
        std::string error;
        ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;
        auto counts = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeComposite);
        EXPECT_EQ(counts["accelerationStructure"], 1u);
        EXPECT_EQ(counts["accelerationStructureNV"], 0u);
        EXPECT_EQ(counts["accelerationStructureEXT"], 0u);
    }
}

TEST_F(SpvDebugInfoTest, UnusedAccelerationStructureHeapsOnlyEmitSourceDebugTypes)
{
    const std::string header = R"(
#version 460
#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_structured_descriptor_heap : require
#extension GL_EXT_ray_query : require
layout(local_size_x = 1) in;
)";
    const std::string arrays = R"(
layout(descriptor_heap) uniform accelerationStructureEXT first[];
layout(descriptor_heap) uniform accelerationStructureEXT second[];
)";
    const std::string structured = R"(
resourceheap RayHeap {
    accelerationStructureEXT topLevelAs[2];
    accelerationStructureEXT backup;
} rayHeap;
)";
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    for (const auto& declarations : {arrays, structured, arrays + structured}) {
        const std::string source = header + declarations + "void main() {}\n";
        SCOPED_TRACE(source);
        std::vector<uint32_t> spirv;
        std::string error;
        ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;
        auto counts = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeComposite);
        EXPECT_EQ(counts["accelerationStructure"], 1u);
        EXPECT_EQ(counts["accelerationStructureNV"], 0u);
        EXPECT_EQ(counts["accelerationStructureEXT"], 0u);
        std::ostringstream assembly;
        spv::Disassemble(assembly, spirv);
        EXPECT_EQ(assembly.str().find("TypeAccelerationStructure"), std::string::npos);
    }
}

TEST_F(SpvDebugInfoTest, CompositeDebugTypesAreReusedForDescriptorHeaps)
{
    const std::string source = R"(
#version 460
#extension GL_EXT_descriptor_heap : require
layout(local_size_x = 1) in;
layout(descriptor_heap) buffer A { uint a; } heap_a[];
layout(descriptor_heap) buffer B { uint b; } heap_b[];
layout(descriptor_heap) uniform U { uint value; } uniforms[4];
void main() {
    heap_a[0].a = uniforms[2].value;
    heap_b[1].b = heap_a[0].a;
}
)";
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    std::vector<uint32_t> spirv;
    std::string error;
    ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;

    auto counts = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeComposite);
    for (const char* name : {"A", "B", "U"})
        EXPECT_EQ(counts[name], 1u) << name;
    auto members = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeMember);
    for (const char* name : {"a", "b", "value"})
        EXPECT_EQ(members[name], 1u) << name;
}

TEST_F(SpvDebugInfoTest, CompositeDebugTypesAreReusedForStructuredHeaps)
{
    const std::string source = R"(
#version 460
#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_structured_descriptor_heap : require
layout(local_size_x = 1) in;
layout(buffer_type, std430) buffer DataBuffer { uint value; };
layout(heap_offset = 64) resourceheap FirstHeap {
    uint count;
    DataBuffer dataBuffer;
} firstHeap;
layout(heap_offset = 64) resourceheap SecondHeap {
    DataBuffer dataBuffer;
    uint count;
} secondHeap;
void main() {
    firstHeap.dataBuffer.value = secondHeap.dataBuffer.value + firstHeap.count + secondHeap.count;
}
)";
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    std::vector<uint32_t> spirv;
    std::string error;
    ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;

    auto counts = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeComposite);
    for (const char* name : {"DataBuffer", "FirstHeap", "SecondHeap"})
        EXPECT_EQ(counts[name], 1u) << name;
}

TEST_F(SpvDebugInfoTest, CompositeDebugTypesAreReusedAcrossLayouts)
{
    const std::string header = R"(
#version 460
#extension GL_EXT_descriptor_heap : require
layout(local_size_x = 1) in;
struct Payload { bool flag; uvec2 ids[2]; };
)";
    const std::string bound = "layout(binding = 0, std430) buffer Bound { Payload value; } bound;\n";
    const std::string heap = "layout(descriptor_heap, std430) buffer Heap { Payload value; } heaps[];\n";
    const std::string readBound = "local.flag = bound.value.flag;\n";
    const std::string readHeap = "local.ids[0] = heaps[0].value.ids[1];\n";
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    // Exercise both creation orders and a local struct with a different physical
    // layout (bool is lowered to uint only in the buffer/heap representations).
    for (const auto& declarations : {bound + heap, heap + bound}) {
        for (const auto& reads : {readBound + readHeap, readHeap + readBound}) {
            const std::string source = header + declarations + "void main() { Payload local;\n" + reads +
                "bound.value.ids[0] = local.ids[0];\n"
                "bound.value.flag = local.flag;\n"
                "heaps[1].value.ids[0] = local.ids[0];\n}\n";
            SCOPED_TRACE(source);
            std::vector<uint32_t> spirv;
            std::string error;
            ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;

            auto counts = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeComposite);
            for (const char* name : {"Payload", "Bound", "Heap"})
                EXPECT_EQ(counts[name], 1u) << name;
            auto members = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeMember);
            EXPECT_EQ(members["flag"], 1u);
            EXPECT_EQ(members["ids"], 1u);
        }
    }
}

TEST_F(SpvDebugInfoTest, RecursiveCompositeDebugTypesAreReused)
{
    const std::string source = R"(
#version 460
#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_buffer_reference : require
layout(local_size_x = 1) in;
struct Payload { uint data; };
layout(buffer_reference) buffer Node;
layout(buffer_reference, std430, buffer_reference_align = 8) buffer Node {
    Node next;
    Payload value;
};
layout(descriptor_heap, std430) buffer Heap { Node root; Payload value; } heaps[];
void main() { heaps[0].root.next.value.data = heaps[0].value.data; }
)";
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    std::vector<uint32_t> spirv;
    std::string error;
    ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;

    auto counts = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeComposite);
    EXPECT_EQ(counts["Node"], 1u);
    EXPECT_EQ(counts["Heap"], 1u);
    EXPECT_EQ(counts["Payload"], 1u);
}

TEST_F(SpvDebugInfoTest, BufferReferenceArrayDebugTypesPreserveElements)
{
    const std::string header = R"(
#version 460
#extension GL_EXT_buffer_reference : require
#extension GL_EXT_descriptor_heap : require
layout(local_size_x = 1) in;
layout(buffer_reference, std430) buffer Node { uint value; };
)";
    const struct {
        const char* suffix;
        const char* index;
        std::vector<uint32_t> dimensions;
    } arrays[] = {
        {"[2]", "[0]", {2}},
        {"[2][3]", "[0][1]", {2, 3}},
        {"[]", "[0]", {0}},
    };
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    for (bool descriptorHeap : {false, true}) {
        for (bool scalarFirst : {false, true}) {
            for (const auto& array : arrays) {
                const std::string layout = descriptorHeap ? "descriptor_heap" : "binding = 0";
                const std::string base = descriptorHeap ? "refs[0]" : "refs";
                const std::string source = header + "layout(" + layout + ", std430) buffer Refs { " +
                    (scalarFirst ? "Node root; " : "") + "Node nodes" + array.suffix + "; } refs" +
                    (descriptorHeap ? "[]" : "") + ";\nvoid main() { " + base + ".nodes" + array.index +
                    ".value = 7u; }\n";
                SCOPED_TRACE(source);
                std::vector<uint32_t> spirv;
                std::string error;
                ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;
                EXPECT_NO_FATAL_FAILURE(expectDebugReferenceMember(spirv, "nodes", array.dimensions, "Node"));
                if (scalarFirst) {
                    EXPECT_NO_FATAL_FAILURE(expectDebugReferenceMember(spirv, "root", {}, "Node"));
                }
                auto counts = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeComposite);
                EXPECT_EQ(counts["Node"], 1u);
                EXPECT_EQ(counts["Refs"], 1u);
            }
        }
    }
}

TEST_F(SpvDebugInfoTest, RecursiveBufferReferenceArrayDebugTypesPreserveElements)
{
    const std::string header = R"(
#version 460
#extension GL_EXT_buffer_reference : require
#extension GL_EXT_descriptor_heap : require
layout(local_size_x = 1) in;
layout(buffer_reference) buffer Node;
layout(buffer_reference, std430) buffer Node { Node next[2]; uint value; };
layout(constant_id = 0) const int Count = 2;
)";
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    const struct {
        const char* layout;
        const char* count;
        const char* suffix;
        const char* body;
    } cases[] = {
        {"binding = 0", "Count", "", "refs.nodes[0][1].next[1].value = 7u;"},
        {"descriptor_heap", "2", "[]", "refs[0].nodes[0][1].next[1].value = 7u;"},
        {"descriptor_heap", "Count", "[]", "refs[0].nodes[0][1].next[1].value = 7u;"},
        // An unused specialized heap also exercises source-only type conversion.
        {"descriptor_heap", "Count", "[]", ""},
    };
    for (const auto& test : cases) {
        const std::string source = header + "layout(" + test.layout +
            ", std430) buffer Refs { Node nodes[" + test.count + "][3]; } refs" + test.suffix +
            ";\nvoid main() { " + test.body + " }\n";
        SCOPED_TRACE(source);
        std::vector<uint32_t> spirv;
        std::string error;
        ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;
        EXPECT_NO_FATAL_FAILURE(expectDebugReferenceMember(spirv, "nodes", {2, 3}, "Node"));
        EXPECT_NO_FATAL_FAILURE(expectDebugReferenceMember(spirv, "next", {2}, "Node"));
    }
}

TEST_F(SpvDebugInfoTest, SameNameStructDeclarationsRemainDistinct)
{
    const std::string source = R"(
#version 460
#extension GL_EXT_descriptor_heap : require
layout(local_size_x = 1) in;
struct Item { uint value; };
layout(descriptor_heap, std430) buffer Heap { Item value; } heaps[];
uint other() {
    struct Item { uint value; };
    Item local;
    local.value = 7u;
    return local.value;
}
void main() { heaps[0].value.value = other(); }
)";
    vulkanVersion = glslang::EShTargetVulkan_1_4;
    spirvVersion = glslang::EShTargetSpv_1_6;
    std::vector<uint32_t> spirv;
    std::string error;
    ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;

    auto counts = countDebugTypes(spirv, NonSemanticShaderDebugInfoDebugTypeComposite);
    EXPECT_EQ(counts["Item"], 2u);
    EXPECT_EQ(counts["Heap"], 1u);
}

TEST_F(SpvDebugInfoTest, DebugEntryPointUsesSuppliedCompilationMetadata)
{
    const std::string source = R"(
#version 450 core
layout(local_size_x = 1) in;
void main() {}
)";
    constexpr char compilerSignature[] = "test compiler signature";
    constexpr char commandLineArguments[] = "-V -gVS shader.comp";
    constexpr char currentWorkingDirectory[] = "test/current/working/directory";
    std::vector<uint32_t> spirv;
    std::string error;
    ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error, compilerSignature, commandLineArguments,
                                           currentWorkingDirectory))
        << error;

    EXPECT_TRUE(containsDebugEntryPoint(spirv, compilerSignature, commandLineArguments, currentWorkingDirectory));
}

// DebugTypeVectorIdEXT (opcode 109) must be emitted for OpTypeCooperativeVectorNV
// when NonSemantic debug info is enabled.
TEST_F(SpvDebugInfoTest, CooperativeVectorNVEmitsDebugTypeVectorIdEXT)
{
    const std::string source = R"(
#version 450 core
#extension GL_KHR_memory_scope_semantics : enable
#extension GL_NV_cooperative_vector : enable
#extension GL_EXT_shader_explicit_arithmetic_types : enable
layout(local_size_x = 64) in;
layout(set = 0, binding = 0) buffer B { float data[]; } buf;
void main() {
    coopvecNV<float, 8> v = coopvecNV<float, 8>(0.0);
    v = v + v;
    buf.data[gl_GlobalInvocationID.x] = v[0];
}
)";
    std::string spirv = compileWithDebugInfo(source);
    EXPECT_NE(spirv.find("DebugTypeVectorIdEXT"), std::string::npos)
        << "Expected DebugTypeVectorIdEXT in disassembly.\nSPIR-V:\n" << spirv;
    EXPECT_NE(spirv.find("TypeCooperativeVectorNV"), std::string::npos)
        << "Expected TypeCooperativeVectorNV in disassembly.\nSPIR-V:\n" << spirv;
}

// DebugTypeVectorIdEXT must also be emitted when the component count is a
// specialization constant (OpSpecConstant), since the spec allows any constant
// instruction for the ComponentCount operand.
TEST_F(SpvDebugInfoTest, CooperativeVectorNVSpecConstCountEmitsDebugTypeVectorIdEXT)
{
    const std::string source = R"(
#version 450 core
#extension GL_KHR_memory_scope_semantics : enable
#extension GL_NV_cooperative_vector : enable
#extension GL_EXT_shader_explicit_arithmetic_types : enable
layout(local_size_x = 64) in;
layout(constant_id = 0) const uint N = 16;
layout(set = 0, binding = 0) buffer B { float data[]; } buf;
void main() {
    coopvecNV<float, N> v = coopvecNV<float, N>(1.0);
    buf.data[gl_GlobalInvocationID.x] = v[0];
}
)";
    std::string spirv = compileWithDebugInfo(source);
    EXPECT_NE(spirv.find("DebugTypeVectorIdEXT"), std::string::npos)
        << "Expected DebugTypeVectorIdEXT with spec-constant count.\nSPIR-V:\n" << spirv;
}

// DebugTypeCooperativeMatrixKHR (opcode 110) must replace the former
// opaque-composite workaround for OpTypeCooperativeMatrixKHR.
TEST_F(SpvDebugInfoTest, CooperativeMatrixKHREmitsDebugTypeCooperativeMatrixKHR)
{
    const std::string source = R"(
#version 450 core
#pragma use_vulkan_memory_model
#extension GL_KHR_memory_scope_semantics : enable
#extension GL_KHR_cooperative_matrix : enable
#extension GL_EXT_shader_explicit_arithmetic_types_float16 : enable
layout(local_size_x = 32) in;
layout(set = 0, binding = 0) buffer B { float16_t data[]; } buf;
void main() {
    coopmat<float16_t, gl_ScopeSubgroup, 16, 16, gl_MatrixUseAccumulator> m =
        coopmat<float16_t, gl_ScopeSubgroup, 16, 16, gl_MatrixUseAccumulator>(float16_t(0.0));
    coopMatStore(m, buf.data, 0, 0, gl_CooperativeMatrixLayoutRowMajor);
}
)";
    std::string spirv = compileWithDebugInfo(source);
    EXPECT_NE(spirv.find("DebugTypeCooperativeMatrixKHR"), std::string::npos)
        << "Expected DebugTypeCooperativeMatrixKHR in disassembly.\nSPIR-V:\n" << spirv;
    // The old opaque-composite workaround must not appear.
    EXPECT_EQ(spirv.find("coopmat<"), std::string::npos)
        << "Opaque-composite workaround should not appear in disassembly.\nSPIR-V:\n" << spirv;
}

// DebugTypeCooperativeMatrixKHR must be emitted when Rows and Columns are
// specialization constants (OpSpecConstant), since the spec allows any constant
// instruction for those operands.
TEST_F(SpvDebugInfoTest, CooperativeMatrixKHRSpecConstDimsEmitsDebugType)
{
    const std::string source = R"(
#version 450 core
#pragma use_vulkan_memory_model
#extension GL_KHR_memory_scope_semantics : enable
#extension GL_KHR_cooperative_matrix : enable
#extension GL_EXT_shader_explicit_arithmetic_types_float16 : enable
layout(local_size_x = 32) in;
layout(constant_id = 0) const uint M = 16;
layout(constant_id = 1) const uint N = 16;
layout(set = 0, binding = 0) buffer B { float16_t data[]; } buf;
void main() {
    coopmat<float16_t, gl_ScopeSubgroup, M, N, gl_MatrixUseAccumulator> m =
        coopmat<float16_t, gl_ScopeSubgroup, M, N, gl_MatrixUseAccumulator>(float16_t(0.0));
    coopMatStore(m, buf.data, 0, 0, gl_CooperativeMatrixLayoutRowMajor);
}
)";
    std::string spirv = compileWithDebugInfo(source);
    EXPECT_NE(spirv.find("DebugTypeCooperativeMatrixKHR"), std::string::npos)
        << "Expected DebugTypeCooperativeMatrixKHR with spec-constant dims.\nSPIR-V:\n" << spirv;
}

// DebugTypeCooperativeMatrixKHR must be emitted for each distinct (component,
// scope, rows, cols, use) tuple -- MatrixUseA, MatrixUseB, and MatrixUseAccumulator
// with different component types all produce separate debug type instructions.
TEST_F(SpvDebugInfoTest, CooperativeMatrixKHRMultipleUsesEmitDistinctDebugTypes)
{
    const std::string source = R"(
#version 450 core
#pragma use_vulkan_memory_model
#extension GL_KHR_memory_scope_semantics : enable
#extension GL_KHR_cooperative_matrix : enable
#extension GL_EXT_shader_explicit_arithmetic_types_float16 : enable
layout(local_size_x = 32) in;
layout(set = 0, binding = 0) buffer B { float16_t data[]; } buf;
void main() {
    coopmat<float16_t, gl_ScopeSubgroup, 16, 16, gl_MatrixUseA>           matA;
    coopmat<float16_t, gl_ScopeSubgroup, 16, 16, gl_MatrixUseB>           matB;
    coopmat<float,     gl_ScopeSubgroup, 16, 16, gl_MatrixUseAccumulator>  matC =
        coopmat<float, gl_ScopeSubgroup, 16, 16, gl_MatrixUseAccumulator>(0.0);
    matC = coopMatMulAdd(matA, matB, matC);
    coopMatStore(matC, buf.data, 0, 0, gl_CooperativeMatrixLayoutRowMajor);
}
)";
    std::string spirv = compileWithDebugInfo(source);

    // Count occurrences of DebugTypeCooperativeMatrixKHR: one for each distinct
    // (component, scope, rows, cols, use) combination used above.
    size_t count = 0;
    size_t pos = 0;
    while ((pos = spirv.find("DebugTypeCooperativeMatrixKHR", pos)) != std::string::npos) {
        ++count;
        pos += 1;
    }
    EXPECT_GE(count, 3u)
        << "Expected at least 3 DebugTypeCooperativeMatrixKHR instructions.\nSPIR-V:\n" << spirv;
}

// The removed golden-file test spv.debuginfo.coopmatKHR.comp combined spec-constant
// dimensions with all three matrix use types. Verify that distinct
// DebugTypeCooperativeMatrixKHR instructions are emitted for MatrixUseA (lM x lK),
// MatrixUseB (lK x lN), and MatrixUseAccumulator (lM x lN) when all dimensions are
// specialization constants.
TEST_F(SpvDebugInfoTest, CooperativeMatrixKHRSpecConstDimsMultipleUsesEmitDistinctDebugTypes)
{
    const std::string source = R"(
#version 450 core
#pragma use_vulkan_memory_model
#extension GL_KHR_memory_scope_semantics : enable
#extension GL_KHR_cooperative_matrix : enable
#extension GL_EXT_shader_explicit_arithmetic_types_float16 : enable
layout(local_size_x = 32) in;
layout(constant_id = 0) const uint lM = 16;
layout(constant_id = 1) const uint lN = 16;
layout(constant_id = 2) const uint lK = 16;
layout(set = 0, binding = 0) buffer B { float data[]; } buf;
void main() {
    coopmat<float16_t, gl_ScopeSubgroup, lM, lK, gl_MatrixUseA>           matA;
    coopmat<float16_t, gl_ScopeSubgroup, lK, lN, gl_MatrixUseB>           matB;
    coopmat<float,     gl_ScopeSubgroup, lM, lN, gl_MatrixUseAccumulator>  matC =
        coopmat<float, gl_ScopeSubgroup, lM, lN, gl_MatrixUseAccumulator>(0.0);
    matC = coopMatMulAdd(matA, matB, matC);
    coopMatStore(matC, buf.data, 0, 0, gl_CooperativeMatrixLayoutRowMajor);
}
)";
    std::string spirv = compileWithDebugInfo(source);

    size_t count = 0;
    size_t pos = 0;
    while ((pos = spirv.find("DebugTypeCooperativeMatrixKHR", pos)) != std::string::npos) {
        ++count;
        pos += 1;
    }
    EXPECT_GE(count, 3u)
        << "Expected at least 3 DebugTypeCooperativeMatrixKHR instructions "
           "(one per use type with spec-constant dimensions).\nSPIR-V:\n" << spirv;
}

// DebugTypeBasic for bfloat16_t must carry the debug type name "bfloat16_t",
// which is emitted only when the FPEncoding operand (BFloat16KHR = 0) is present.
TEST_F(SpvDebugInfoTest, BFloat16EmitsDebugTypeBasicWithFPEncoding)
{
    const std::string source = R"(
#version 450 core
#extension GL_EXT_bfloat16 : require
#extension GL_EXT_shader_explicit_arithmetic_types : enable
layout(local_size_x = 64) in;
layout(set = 0, binding = 0) buffer B { float data[]; } buf;
void main() {
    bfloat16_t bf = bfloat16_t(1.0);
    buf.data[gl_GlobalInvocationID.x] = float(bf);
}
)";
    std::string spirv = compileWithDebugInfo(source);
    // The DebugTypeBasic for bfloat16_t should contain the name "bfloat16_t".
    EXPECT_NE(spirv.find("\"bfloat16_t\""), std::string::npos)
        << "Expected \"bfloat16_t\" string in debug type.\nSPIR-V:\n" << spirv;
}

// DebugTypeBasic for floate4m3_t must carry the debug type name "floate4m3_t",
// which is emitted only when the FPEncoding operand (Float8E4M3EXT = 4214) is present.
TEST_F(SpvDebugInfoTest, Float8E4M3EmitsDebugTypeBasicWithFPEncoding)
{
    const std::string source = R"(
#version 450 core
#extension GL_EXT_bfloat16 : require
#extension GL_EXT_float_e4m3 : require
#extension GL_EXT_shader_explicit_arithmetic_types : enable
layout(local_size_x = 64) in;
layout(set = 0, binding = 0) buffer B { float data[]; } buf;
void main() {
    floate4m3_t f = floate4m3_t(2.0);
    buf.data[gl_GlobalInvocationID.x] = float(f);
}
)";
    std::string spirv = compileWithDebugInfo(source);
    EXPECT_NE(spirv.find("\"floate4m3_t\""), std::string::npos)
        << "Expected \"floate4m3_t\" string in debug type.\nSPIR-V:\n" << spirv;
}

// DebugTypeBasic for floate5m2_t must carry the debug type name "floate5m2_t",
// which is emitted only when the FPEncoding operand (Float8E5M2EXT = 4215) is present.
TEST_F(SpvDebugInfoTest, Float8E5M2EmitsDebugTypeBasicWithFPEncoding)
{
    const std::string source = R"(
#version 450 core
#extension GL_EXT_bfloat16 : require
#extension GL_EXT_float_e5m2 : require
#extension GL_EXT_shader_explicit_arithmetic_types : enable
layout(local_size_x = 64) in;
layout(set = 0, binding = 0) buffer B { float data[]; } buf;
void main() {
    floate5m2_t f = floate5m2_t(3.0);
    buf.data[gl_GlobalInvocationID.x] = float(f);
}
)";
    std::string spirv = compileWithDebugInfo(source);
    EXPECT_NE(spirv.find("\"floate5m2_t\""), std::string::npos)
        << "Expected \"floate5m2_t\" string in debug type.\nSPIR-V:\n" << spirv;
}

// DebugTypeBasic for OCP microscaling types must carry their source-level type
// names, which are emitted only when the FPEncoding operand is present.
TEST_F(SpvDebugInfoTest, OcpMicroscalingTypesEmitDebugTypeBasicWithFPEncoding)
{
    const std::string source = R"(
#version 450 core
#extension GL_EXT_float_e2m1 : require
#extension GL_EXT_float_e3m2 : require
#extension GL_EXT_float_e2m3 : require
#extension GL_EXT_float_ue8m0 : require
#extension GL_EXT_float_mxint8 : require
#extension GL_EXT_shader_explicit_arithmetic_types : enable
layout(local_size_x = 64) in;
layout(set = 0, binding = 0) buffer B { float data[]; } buf;
void main() {
    floate2m1_t e2m1 = floate2m1_t(1.0fe2m1);
    floate3m2_t e3m2 = floate3m2_t(1.0fe3m2);
    floate2m3_t e2m3 = floate2m3_t(1.0fe2m3);
    floatue8m0_t ue8m0 = floatue8m0_t(1.0fue8m0);
    floatmxint8_t mxint8 = floatmxint8_t(1.0fmxint8);
    buf.data[gl_GlobalInvocationID.x] =
        float(e2m1) + float(e3m2) + float(e2m3) + float(ue8m0) + float(mxint8);
}
)";
    std::vector<uint32_t> spirv;
    std::string error;
    ASSERT_TRUE(compileToSpirvWithDebugInfo(source, spirv, error)) << error;

    struct ExpectedDebugType {
        const char* name;
        uint32_t width;
        spv::FPEncoding fpEncoding;
    };
    const ExpectedDebugType expectedTypes[] = {
        {"floate2m1_t", 4, spv::FPEncoding::Float4E2M1EXT},
        {"floate3m2_t", 6, spv::FPEncoding::Float6E3M2EXT},
        {"floate2m3_t", 6, spv::FPEncoding::Float6E2M3EXT},
        {"floatue8m0_t", 8, spv::FPEncoding::Float8UnsignedE8M0EXT},
        {"floatmxint8_t", 8, spv::FPEncoding::MXInt8EXT},
    };

    std::ostringstream disassembly;
    spv::Disassemble(disassembly, spirv);
    for (const auto& expected : expectedTypes) {
        EXPECT_TRUE(containsDebugTypeBasic(spirv, expected.name, expected.width, expected.fpEncoding))
            << "Expected DebugTypeBasic for \"" << expected.name << "\" with width " << expected.width
            << " and FPEncoding " << static_cast<uint32_t>(expected.fpEncoding)
            << ".\nSPIR-V:\n" << disassembly.str();
    }
}

// When a version-101 opcode is emitted the import string must be promoted to
// NonSemantic.Shader.DebugInfo.101.
TEST_F(SpvDebugInfoTest, Version101OpcodePromotesImportStringTo101)
{
    // DebugTypeCooperativeMatrixKHR is a version-101 opcode; using it must
    // cause the import string to read ".101", not ".100".
    const std::string source = R"(
#version 450 core
#pragma use_vulkan_memory_model
#extension GL_KHR_memory_scope_semantics : enable
#extension GL_KHR_cooperative_matrix : enable
#extension GL_EXT_shader_explicit_arithmetic_types_float16 : enable
layout(local_size_x = 32) in;
layout(set = 0, binding = 0) buffer B { float16_t data[]; } buf;
void main() {
    coopmat<float16_t, gl_ScopeSubgroup, 16, 16, gl_MatrixUseAccumulator> m =
        coopmat<float16_t, gl_ScopeSubgroup, 16, 16, gl_MatrixUseAccumulator>(float16_t(0.0));
    coopMatStore(m, buf.data, 0, 0, gl_CooperativeMatrixLayoutRowMajor);
}
)";
    std::string spirv = compileWithDebugInfo(source);
    EXPECT_NE(spirv.find("\"NonSemantic.Shader.DebugInfo.101\""), std::string::npos)
        << "Expected import string NonSemantic.Shader.DebugInfo.101.\nSPIR-V:\n" << spirv;
    EXPECT_EQ(spirv.find("\"NonSemantic.Shader.DebugInfo.100\""), std::string::npos)
        << "Import string must not be .100 when version-101 opcodes are used.\nSPIR-V:\n" << spirv;
}

// When only version-100 opcodes are emitted the import string must stay at
// NonSemantic.Shader.DebugInfo.100 and must not be promoted to .101.
TEST_F(SpvDebugInfoTest, Version100OnlyKeepsImportStringAt100)
{
    const std::string source = R"(
#version 450 core
layout(local_size_x = 64) in;
layout(set = 0, binding = 0) buffer B { float data[]; } buf;
void main() {
    float x = buf.data[gl_GlobalInvocationID.x];
    buf.data[gl_GlobalInvocationID.x] = x * 2.0;
}
)";
    std::string spirv = compileWithDebugInfo(source);
    EXPECT_NE(spirv.find("\"NonSemantic.Shader.DebugInfo.100\""), std::string::npos)
        << "Expected import string NonSemantic.Shader.DebugInfo.100.\nSPIR-V:\n" << spirv;
    EXPECT_EQ(spirv.find("\"NonSemantic.Shader.DebugInfo.101\""), std::string::npos)
        << "Import string must not be .101 when only version-100 opcodes are used.\nSPIR-V:\n" << spirv;
}

} // namespace
} // namespace glslangtest
