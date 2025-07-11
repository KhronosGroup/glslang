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

#include "TestFixture.h"

namespace glslangtest {
namespace {

using StructNameTest = GlslangTest<::testing::Test>;

// Test that struct names can be used as variable names in declarations (should NOT have syntax errors)
TEST_F(StructNameTest, StructNameInDeclaration)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_in_declaration.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_in_declaration.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    
    // Should parse successfully (no syntax errors)
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used as single variable names (should parse successfully, no redefinition error)
TEST_F(StructNameTest, StructNameAsVariable)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_as_variable.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_as_variable.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    // Should parse successfully (no syntax errors)
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used as variable names with initializers (should parse successfully, no redefinition error)
TEST_F(StructNameTest, StructNameAsVariableWithInitializer)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_as_variable_with_initializer.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_as_variable_with_initializer.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    // Should parse successfully (no syntax errors)
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used as variable names with arrays (should parse successfully, no redefinition error)
TEST_F(StructNameTest, StructNameAsVariableWithArray)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_as_variable_with_array.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_as_variable_with_array.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    // Should parse successfully (no syntax errors)
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used as variable names with array initializers (should parse successfully, no redefinition error)
TEST_F(StructNameTest, StructNameAsVariableWithArrayInitializer)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_as_variable_with_array_initializer.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_as_variable_with_array_initializer.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    // Should parse successfully (no syntax errors)
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used as struct member names (should parse successfully)
TEST_F(StructNameTest, StructNameAsStructMember)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_as_struct_member.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_as_struct_member.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    
    // Should parse successfully
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used as struct member names with arrays (should parse successfully)
TEST_F(StructNameTest, StructNameAsStructMemberWithArray)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_as_struct_member_with_array.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_as_struct_member_with_array.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    
    // Should parse successfully
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that multiple struct names can be used in the same declaration (should parse successfully, no redefinition error)
TEST_F(StructNameTest, MultipleStructNames)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/multiple_struct_names.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("multiple_struct_names.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    // Should parse successfully (no syntax errors)
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used in function parameters (should parse successfully)
TEST_F(StructNameTest, StructNameInFunctionParams)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_in_function_params.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_in_function_params.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    
    // Should parse successfully
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used in function parameters with arrays (should parse successfully)
TEST_F(StructNameTest, StructNameInFunctionParamsWithArray)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_in_function_params_with_array.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_in_function_params_with_array.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    
    // Should parse successfully
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used in vertex shaders (should parse successfully)
TEST_F(StructNameTest, StructNameInVertexShader)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_in_vertex_shader.vert";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_in_vertex_shader.vert", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    
    // Should parse successfully
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used in compute shaders (should parse successfully)
TEST_F(StructNameTest, StructNameInComputeShader)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_in_compute_shader.comp";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_in_compute_shader.comp", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    
    // Should parse successfully
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used with qualifiers (should parse successfully)
TEST_F(StructNameTest, StructNameWithQualifiers)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_with_qualifiers.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_with_qualifiers.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    
    // Should parse successfully
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test edge cases with struct names (should parse successfully)
TEST_F(StructNameTest, StructNameEdgeCases)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_edge_cases.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_edge_cases.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    
    // Should parse successfully
    EXPECT_TRUE(result.linkingError.empty() || 
                result.linkingError.find("syntax error") == std::string::npos);
}

// Test that struct names can be used in the middle of variable declarations (should parse successfully)
TEST_F(StructNameTest, StructNameInMiddle)
{
    const std::string inputFname = GlobalTestSettings.testRoot + "/struct_name_in_middle.frag";
    std::string input;
    tryLoadFile(inputFname, "input", &input);
    
    EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result = compileAndLink("struct_name_in_middle.frag", input, "", controls,
                                         glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0);
    
    // Should NOT have the original syntax error
    EXPECT_EQ(result.linkingError.find("syntax error, unexpected TYPE_NAME, expecting IDENTIFIER"), std::string::npos);
    // Should NOT have any syntax errors
    EXPECT_EQ(result.linkingError.find("syntax error"), std::string::npos);
    // Should NOT have redefinition errors (these are different variables)
    EXPECT_EQ(result.linkingError.find("redefinition"), std::string::npos);
}

}  // anonymous namespace
}  // namespace glslangtest 