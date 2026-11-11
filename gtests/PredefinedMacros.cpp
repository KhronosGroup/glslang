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

#include "glslang/Public/ResourceLimits.h"
#include "glslang/Public/ShaderLang.h"
#include <gtest/gtest.h>
#include <string>

namespace glslangtest {

// Preprocesses a fragment shader, for Vulkan at the given SPIR-V version if vulkan is set, and returns true
// if the preamble predefines the macro.
static bool isPredefined(const std::string& version, const std::string& macro, bool vulkan = false,
                         glslang::EShTargetLanguageVersion spv = glslang::EShTargetSpv_1_0)
{
    const std::string source = "#version " + version + "\n#ifdef " + macro + "\nmacro_defined\n#endif\n";
    const char* text = source.c_str();
    glslang::TShader shader(EShLangFragment);
    shader.setStrings(&text, 1);
    if (vulkan) {
        shader.setEnvInput(glslang::EShSourceGlsl, EShLangFragment, glslang::EShClientVulkan, 100);
        shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_1);
        shader.setEnvTarget(glslang::EShTargetSpv, spv);
    }
    std::string output;
    glslang::TShader::ForbidIncluder includer;
    EXPECT_TRUE(shader.preprocess(GetDefaultResources(), 100, ENoProfile, false, false, EShMsgDefault, &output,
                                  includer))
        << shader.getInfoLog();
    return output.find("macro_defined") != std::string::npos;
}

TEST(PredefinedMacros, ExtensionThatHadNone)
{
    EXPECT_FALSE(isPredefined("440", "GL_ARB_shader_clock"));
    EXPECT_TRUE(isPredefined("450", "GL_ARB_shader_clock"));
}

TEST(PredefinedMacros, FirstVersion)
{
    EXPECT_FALSE(isPredefined("450", "GL_EXT_ray_query"));
    EXPECT_TRUE(isPredefined("460", "GL_EXT_ray_query"));
}

TEST(PredefinedMacros, EveryProfileThatSupportsTheExtension)
{
    EXPECT_FALSE(isPredefined("300 es", "GL_KHR_shader_subgroup_basic"));
    EXPECT_TRUE(isPredefined("310 es", "GL_KHR_shader_subgroup_basic"));
}

TEST(PredefinedMacros, LastVersion)
{
    EXPECT_TRUE(isPredefined("100", "GL_OES_texture_3D"));
    EXPECT_FALSE(isPredefined("300 es", "GL_OES_texture_3D"));
    EXPECT_TRUE(isPredefined("420 compatibility", "GL_ARB_texture_rectangle"));
    EXPECT_FALSE(isPredefined("420 core", "GL_ARB_texture_rectangle"));
}

TEST(PredefinedMacros, Target)
{
    EXPECT_TRUE(isPredefined("450", "GL_ARB_bindless_texture"));
    EXPECT_FALSE(isPredefined("450", "GL_ARB_bindless_texture", true));
    EXPECT_FALSE(isPredefined("450", "GL_EXT_buffer_reference"));
    EXPECT_TRUE(isPredefined("450", "GL_EXT_buffer_reference", true));
}

TEST(PredefinedMacros, MinimumSpirvVersion)
{
    EXPECT_TRUE(isPredefined("450", "GL_KHR_shader_subgroup_basic"));
    EXPECT_FALSE(isPredefined("450", "GL_KHR_shader_subgroup_basic", true, glslang::EShTargetSpv_1_2));
    EXPECT_TRUE(isPredefined("450", "GL_KHR_shader_subgroup_basic", true, glslang::EShTargetSpv_1_3));
}

} // namespace glslangtest
