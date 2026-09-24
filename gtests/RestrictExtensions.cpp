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

#include "glslang/Include/glslang_c_interface.h"
#include "glslang/Public/ResourceLimits.h"
#include "glslang/Public/ShaderLang.h"
#include "glslang/Public/resource_limits_c.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace glslangtest {

class RestrictExtensionsTest : public ::testing::Test {
protected:
    struct Result {
        bool success;
        std::string output;
        std::string infoLog;
    };

    static void setup(glslang::TShader& shader, const char* const* source, const std::vector<const char*>* available)
    {
        shader.setStrings(source, 1);
        shader.setEnvInput(glslang::EShSourceGlsl, EShLangFragment, glslang::EShClientVulkan, 100);
        shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_1);
        shader.setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_3);
        if (available != nullptr)
            shader.restrictAvailableExtensions(available->data(), static_cast<int>(available->size()));
    }

    Result preprocess(const char* source, const std::vector<const char*>* available)
    {
        glslang::TShader shader(EShLangFragment);
        setup(shader, &source, available);
        std::string output;
        glslang::TShader::ForbidIncluder includer;
        const bool success =
            shader.preprocess(GetDefaultResources(), 450, ENoProfile, false, false, EShMsgDefault, &output, includer);
        return {success, output, shader.getInfoLog()};
    }

    Result parse(const char* source, const std::vector<const char*>* available)
    {
        glslang::TShader shader(EShLangFragment);
        setup(shader, &source, available);
        const EShMessages messages = static_cast<EShMessages>(EShMsgSpvRules | EShMsgVulkanRules);
        const bool success = shader.parse(GetDefaultResources(), 450, false, messages);
        return {success, "", shader.getInfoLog()};
    }

    static bool contains(const std::string& text, const std::string& pattern)
    {
        return text.find(pattern) != std::string::npos;
    }
};

// Issue #2595: choose a code path from the predefined extension macros.
static const char* kMacros = R"glsl(
#version 450
#ifdef VULKAN
vulkan_defined
#endif
#ifdef GL_KHR_shader_subgroup_ballot
ballot_defined
#endif
#ifdef GL_EXT_ray_tracing
ray_tracing_defined
#endif
)glsl";

static const char* kRequireRayQuery = R"glsl(
#version 450
#extension GL_EXT_ray_query : require
void main() {}
)glsl";

static const char* kEnableRayTracing = R"glsl(
#version 450
#extension GL_EXT_ray_tracing : enable
void main() {}
)glsl";

static const char* kUseBallot = R"glsl(
#version 450
#extension GL_KHR_shader_subgroup_ballot : enable
layout(location = 0) out vec4 color;
void main() {
    color = vec4(subgroupBallot(true));
}
)glsl";

static const char* kUseElect = R"glsl(
#version 450
#extension GL_KHR_shader_subgroup_ballot : enable
layout(location = 0) out vec4 color;
void main() {
    color = vec4(subgroupElect());
}
)glsl";

static const char* kImplicitConversion = R"glsl(#version 310 es
#extension GL_EXT_shader_implicit_conversions : enable
precision mediump float;
layout(location = 0) out highp float color;
void main() {
    int i = 1;
    color = i;
}
)glsl";

TEST_F(RestrictExtensionsTest, WithoutRestrictionExtensionsArePredefined)
{
    auto r = preprocess(kMacros, nullptr);
    ASSERT_TRUE(r.success) << r.infoLog;
    EXPECT_TRUE(contains(r.output, "vulkan_defined"));
    EXPECT_TRUE(contains(r.output, "ballot_defined"));
    EXPECT_TRUE(contains(r.output, "ray_tracing_defined"));
}

TEST_F(RestrictExtensionsTest, OnlyListedExtensionsArePredefined)
{
    const std::vector<const char*> available = {"GL_KHR_shader_subgroup_basic", "GL_KHR_shader_subgroup_ballot"};
    auto r = preprocess(kMacros, &available);
    ASSERT_TRUE(r.success) << r.infoLog;
    EXPECT_TRUE(contains(r.output, "vulkan_defined"));
    EXPECT_TRUE(contains(r.output, "ballot_defined"));
    EXPECT_FALSE(contains(r.output, "ray_tracing_defined"));
}

TEST_F(RestrictExtensionsTest, EmptyListPredefinesNoExtension)
{
    const std::vector<const char*> available;
    auto r = preprocess(kMacros, &available);
    ASSERT_TRUE(r.success) << r.infoLog;
    EXPECT_TRUE(contains(r.output, "vulkan_defined"));
    EXPECT_FALSE(contains(r.output, "ballot_defined"));
    EXPECT_FALSE(contains(r.output, "ray_tracing_defined"));
}

TEST_F(RestrictExtensionsTest, UnknownNamesInTheListAreIgnored)
{
    const std::vector<const char*> available = {"GL_NOT_AN_EXTENSION", "GL_KHR_shader_subgroup_ballot"};
    auto r = preprocess(kMacros, &available);
    ASSERT_TRUE(r.success) << r.infoLog;
    EXPECT_TRUE(contains(r.output, "ballot_defined"));
    EXPECT_FALSE(contains(r.output, "ray_tracing_defined"));
}

TEST_F(RestrictExtensionsTest, RequiringAnUnavailableExtensionIsAnError)
{
    const std::vector<const char*> available = {"GL_KHR_shader_subgroup_ballot"};
    auto r = parse(kRequireRayQuery, &available);
    EXPECT_FALSE(r.success);
    EXPECT_TRUE(contains(r.infoLog, "ERROR: 0:3: '#extension' : extension not supported: GL_EXT_ray_query"))
        << r.infoLog;
}

TEST_F(RestrictExtensionsTest, EnablingAnUnavailableExtensionOnlyWarns)
{
    // Unrestricted, this fails because GL_EXT_ray_tracing needs SPIR-V 1.4.
    const std::vector<const char*> available;
    auto r = parse(kEnableRayTracing, &available);
    EXPECT_TRUE(r.success) << r.infoLog;
    EXPECT_TRUE(contains(r.infoLog, "WARNING: 0:3: '#extension' : extension not supported: GL_EXT_ray_tracing"))
        << r.infoLog;
}

TEST_F(RestrictExtensionsTest, BuiltInsOfAnUnavailableExtensionAreRejected)
{
    const std::vector<const char*> available = {"GL_KHR_shader_subgroup_basic"};
    auto r = parse(kUseBallot, &available);
    EXPECT_FALSE(r.success);
    EXPECT_TRUE(contains(r.infoLog, "required extension not requested: GL_KHR_shader_subgroup_ballot")) << r.infoLog;
}

TEST_F(RestrictExtensionsTest, AnUnavailableExtensionImpliesNothing)
{
    // Enabling ballot would request basic as well, but ballot is not available.
    const std::vector<const char*> available = {"GL_KHR_shader_subgroup_basic"};
    auto r = parse(kUseElect, &available);
    EXPECT_FALSE(r.success);
    EXPECT_TRUE(contains(r.infoLog, "required extension not requested: GL_KHR_shader_subgroup_basic")) << r.infoLog;
}

TEST_F(RestrictExtensionsTest, AnUnavailableExtensionEnablesNoFeature)
{
    const std::vector<const char*> available;
    auto r = parse(kImplicitConversion, &available);
    EXPECT_FALSE(r.success);
    EXPECT_TRUE(contains(r.infoLog, "cannot convert")) << r.infoLog;
}

TEST_F(RestrictExtensionsTest, ImpliedExtensionsAreNotAddedAutomatically)
{
    // #extension ballot also requests basic, which is not listed.
    const std::vector<const char*> available = {"GL_KHR_shader_subgroup_ballot"};
    auto r = parse(kUseBallot, &available);
    EXPECT_TRUE(r.success) << r.infoLog;
    EXPECT_TRUE(contains(r.infoLog, "extension not supported: GL_KHR_shader_subgroup_basic")) << r.infoLog;
}

TEST_F(RestrictExtensionsTest, ListedExtensionsWorkAsBefore)
{
    const std::vector<const char*> available = {"GL_KHR_shader_subgroup_basic", "GL_KHR_shader_subgroup_ballot"};
    auto r = parse(kUseBallot, &available);
    EXPECT_TRUE(r.success) << r.infoLog;
    EXPECT_FALSE(contains(r.infoLog, "extension not supported")) << r.infoLog;
}

TEST_F(RestrictExtensionsTest, CInterface)
{
    glslang_input_t input = {};
    input.language = GLSLANG_SOURCE_GLSL;
    input.stage = GLSLANG_STAGE_FRAGMENT;
    input.client = GLSLANG_CLIENT_VULKAN;
    input.client_version = GLSLANG_TARGET_VULKAN_1_1;
    input.target_language = GLSLANG_TARGET_SPV;
    input.target_language_version = GLSLANG_TARGET_SPV_1_3;
    input.code = kMacros;
    input.default_version = 450;
    input.default_profile = GLSLANG_NO_PROFILE;
    input.messages = GLSLANG_MSG_DEFAULT_BIT;
    input.resource = glslang_default_resource();

    glslang_shader_t* shader = glslang_shader_create(&input);
    const char* const available[] = {"GL_KHR_shader_subgroup_ballot"};
    glslang_shader_restrict_available_extensions(shader, available, 1);
    ASSERT_TRUE(glslang_shader_preprocess(shader, &input)) << glslang_shader_get_info_log(shader);
    const std::string output = glslang_shader_get_preprocessed_code(shader);
    glslang_shader_delete(shader);

    EXPECT_TRUE(contains(output, "ballot_defined"));
    EXPECT_FALSE(contains(output, "ray_tracing_defined"));
}

} // namespace glslangtest
