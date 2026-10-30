// Copyright (C) 2026 The Khronos Group Inc.
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
//    Neither the name of The Khronos Group Inc. nor the names of its
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

#include "SPIRV/disassemble.h"
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

namespace glslangtest {
namespace {

// Disassemble a malformed module; the disassembler must reject it rather than
// read past the end of the word stream.
void disassembleBody(std::vector<unsigned int> body)
{
    std::vector<unsigned int> words = {0x07230203, 0x00010000, 0, 16, 0};
    words.insert(words.end(), body.begin(), body.end());
    words.shrink_to_fit();
    std::ostringstream out;
    spv::Disassemble(out, words);
}

using DisassembleDeathTest = ::testing::Test;

TEST_F(DisassembleDeathTest, ShortHeader)
{
    std::vector<unsigned int> words = {0x07230203, 0x00010000, 0, 16};
    std::ostringstream out;
    EXPECT_EXIT(spv::Disassemble(out, words), ::testing::ExitedWithCode(1), "");
}

TEST_F(DisassembleDeathTest, ZeroWordCount) { EXPECT_EXIT(disassembleBody({0}), ::testing::ExitedWithCode(1), ""); }

TEST_F(DisassembleDeathTest, MissingResultId)
{
    // OpTypeVector with a word count of 1
    EXPECT_EXIT(disassembleBody({(1u << 16) | 23}), ::testing::ExitedWithCode(1), "");
}

TEST_F(DisassembleDeathTest, MissingFixedOperands)
{
    // OpTypeVector and OpTypeImage with only a result id
    EXPECT_EXIT(disassembleBody({(2u << 16) | 23, 1}), ::testing::ExitedWithCode(1), "");
    EXPECT_EXIT(disassembleBody({(2u << 16) | 25, 1}), ::testing::ExitedWithCode(1), "");
}

TEST_F(DisassembleDeathTest, OperandPastEnd)
{
    // OpLoad with an Aligned memory operand but no alignment literal
    EXPECT_EXIT(disassembleBody({(5u << 16) | 61, 1, 2, 3, 2}), ::testing::ExitedWithCode(1), "");
    // OpGroupMemberDecorate with an unpaired trailing operand
    EXPECT_EXIT(disassembleBody({(5u << 16) | 75, 1, 2, 3, 4}), ::testing::ExitedWithCode(1), "");
}

TEST_F(DisassembleDeathTest, ValidModule)
{
    // OpTypeVoid
    std::vector<unsigned int> words = {0x07230203, 0x00010000, 0, 16, 0, (2u << 16) | 19, 1};
    std::ostringstream out;
    spv::Disassemble(out, words);
    EXPECT_NE(out.str().find("TypeVoid"), std::string::npos);
}

} // anonymous namespace
} // namespace glslangtest
