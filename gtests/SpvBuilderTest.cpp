// SPDX-FileCopyrightText: 2026 NVIDIA Corporation
// SPDX-License-Identifier: BSD-3-Clause

#include "SPIRV/SpvBuilder.h"
#include <gtest/gtest.h>
#include <vector>

namespace glslangtest {
namespace {

void expectDebugInfoNone(spv::Builder& builder, spv::Id result)
{
    ASSERT_NE(result, 0u);
    std::vector<unsigned int> words;
    builder.dump(words);
    unsigned int count = 0;
    bool found = false;
    for (size_t offset = 5; offset < words.size();) {
        const unsigned int length = words[offset] >> spv::WordCountShift;
        ASSERT_GT(length, 0u);
        ASSERT_LE(offset + length, words.size());
        if ((words[offset] & spv::OpCodeMask) == static_cast<unsigned int>(spv::Op::OpExtInst) &&
            length == 5 && words[offset + 4] == spv::NonSemanticShaderDebugInfoDebugInfoNone) {
            ++count;
            if (words[offset + 2] == result) {
                found = true;
                EXPECT_EQ(words[offset + 1], builder.makeVoidType());
            }
        }
        offset += length;
    }
    EXPECT_TRUE(found);
    EXPECT_EQ(count, 1u);
}

TEST(SpvBuilderTest, MissingTypeReturnsDebugInfoNone)
{
    spv::SpvBuildLogger logger;
    spv::Builder builder(spv::Spv_1_0, 0, &logger);
    // This is an actual type with no debug mapping, created before debug emission.
    const auto type = builder.makeIntType(32);
    builder.setEmitNonSemanticShaderDebugInfo(false);
    const auto result = builder.getDebugType(type);
    EXPECT_EQ(result, builder.getDebugType(type));
    expectDebugInfoNone(builder, result);
}

TEST(SpvBuilderTest, MissingFunctionReturnsDebugInfoNone)
{
    spv::SpvBuildLogger logger;
    spv::Builder builder(spv::Spv_1_0, 0, &logger);
    builder.setSource(spv::SourceLanguage::HLSL, 500);
    builder.setEmitNonSemanticShaderDebugInfo(false);
    // HLSL wrappers deliberately have no DebugFunction mapping.
    const auto function = builder.makeEntryPoint("main");
    const auto result = builder.getDebugFunction(function->getId());
    EXPECT_EQ(result, builder.getDebugFunction(function->getId()));
    expectDebugInfoNone(builder, result);
}

}  // anonymous namespace
}  // namespace glslangtest
