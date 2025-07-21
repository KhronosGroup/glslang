// Copyright (C) 2025 NVIDIA Corporation
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

#include <gtest/gtest.h>

#include "TestFixture.h"

namespace glslangtest {
namespace {

using StructNameTest = GlslangTest<::testing::Test>;

// Test the original bug report case from issue #3931.
TEST_F(StructNameTest, OriginalBugReportStructMember)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_as_struct_member.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);

    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_as_struct_member.frag", input, "", controls,
                                          glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);

    // Should NOT have the original syntax error that was reported in the GitHub issue.
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);

    // Should compile successfully.
    EXPECT_EQ(result.shaderResults[0].output.find("compilation errors"), std::string::npos);
}

// Test struct names used as array member names.
TEST_F(StructNameTest, StructNameAsArrayMember)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_as_array_member.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);

    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_as_array_member.frag", input, "", controls,
                                          glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);

    // Should NOT have the original syntax error that was reported in the GitHub issue.
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);

    // Should compile successfully.
    EXPECT_EQ(result.shaderResults[0].output.find("compilation errors"), std::string::npos);
}

} // anonymous namespace
} // namespace glslangtest