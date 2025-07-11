//
// Copyright (C) 2016 Google, Inc.
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
//    Neither the name of Google Inc. nor the names of its
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

#include <memory>

#include <gtest/gtest.h>

#include "TestFixture.h"

namespace glslangtest {
namespace {

using LinkTest = GlslangTest<
    ::testing::TestWithParam<std::vector<std::string>>>;

TEST_P(LinkTest, FromFile)
{
    const auto& fileNames = GetParam();
    const size_t fileCount = fileNames.size();
    const EShMessages controls = DeriveOptions(Source::GLSL, Semantics::OpenGL, Target::AST);
    GlslangResult result;
    result.validationResult = true;

    // Compile each input shader file.
    std::vector<std::unique_ptr<glslang::TShader>> shaders;
    for (size_t i = 0; i < fileCount; ++i) {
        std::string contents;
        tryLoadFile(GlobalTestSettings.testRoot + "/" + fileNames[i],
                    "input", &contents);
        shaders.emplace_back(
                new glslang::TShader(GetShaderStage(GetSuffix(fileNames[i]))));
        auto* shader = shaders.back().get();
        compile(shader, contents, "", controls);
        result.shaderResults.push_back(
            {fileNames[i], shader->getInfoLog(), shader->getInfoDebugLog()});
    }

    // Link all of them.
    glslang::TProgram program;
    for (const auto& shader : shaders) program.addShader(shader.get());
    program.link(controls);
    result.linkingOutput = program.getInfoLog();
    result.linkingError = program.getInfoDebugLog();

    std::ostringstream stream;
    outputResultToStream(&stream, result, controls);

    // Check with expected results.
    const std::string expectedOutputFname =
        GlobalTestSettings.testRoot + "/baseResults/" + fileNames.front() + ".out";
    std::string expectedOutput;
    tryLoadFile(expectedOutputFname, "expected output", &expectedOutput);

    checkEqAndUpdateIfRequested(expectedOutput, stream.str(), expectedOutputFname);
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Glsl, LinkTest,
    ::testing::ValuesIn(std::vector<std::vector<std::string>>({
        {"mains1.frag", "mains2.frag", "noMain1.geom", "noMain2.geom"},
        {"implicitArraySize.vert", "implicitArraySize.frag"},
        {"implicitArraySizeBuiltin.vert", "implicitArraySizeBuiltin.geom"},
        {"implicitArraySize1.geom", "implicitArraySize2.geom"},
        {"implicitArraySizeUniform.vert", "implicitArraySizeUniform.frag"},
        {"implicitArraySizeUniformContradict.vert", "implicitArraySizeUniformContradict.frag"},
        {"noMain.vert", "mains.frag"},
        {"link1.frag", "link2.frag", "link3.frag"},
        {"recurse1.vert", "recurse1.frag", "recurse2.frag"},
        {"300link.frag"},
        {"300link2.frag"},
        {"300link3.frag"},
        {"empty.frag", "empty2.frag", "empty3.frag"},
        {"150.tesc", "150.tese", "400.tesc", "400.tese", "410.tesc", "420.tesc", "420.tese"},
        {"max_vertices_0.geom"},
        {"contradict_0.geom", "contradict_1.geom"},
        {"es-link1.frag", "es-link2.frag"},
        {"missingBodies.vert"},
        {"link.multiAnonBlocksInvalid.0.0.vert", "link.multiAnonBlocksInvalid.0.1.vert"},
        {"link.multiAnonBlocksValid.0.0.vert", "link.multiAnonBlocksValid.0.1.vert"},
        {"link.multiBlocksInvalid.0.0.vert", "link.multiBlocksInvalid.0.1.vert"},
        {"link.multiBlocksValid.1.0.vert", "link.multiBlocksValid.1.1.vert"},
        {"link.multiUnitLayout.0.vert", "link.multiUnitLayout.1.vert"},
        {"link.multiUnitLayout.0.frag", "link.multiUnitLayout.1.frag"},
        {"link.multiUnitLayout.0.tese", "link.multiUnitLayout.1.tese"},
        {"link.multiUnitLayout.0.mesh", "link.multiUnitLayout.1.mesh"},
        {"link.multiUnitLayout.2.vert", "link.multiUnitLayout.0.vert"},
        {"link.multiUnitLayout.2.frag", "link.multiUnitLayout.0.frag"},
        {"link.multiUnitLayout.2.tese", "link.multiUnitLayout.0.tese"},
        {"link.multiUnitLayout.2.mesh", "link.multiUnitLayout.0.mesh"},
        {"link.tesselation.vert", "link.tesselation.frag"},
        {"link.tesselation.tese", "link.tesselation.tesc"},
        {"link.redeclareBuiltin.vert", "link.redeclareBuiltin.geom"},
        {"link.crossStageIO.0.vert", "link.crossStageIO.0.frag"},
        {"link.crossStageIO.1.vert", "link.crossStageIO.1.geom", "link.crossStageIO.1.frag"},
        {"link.missingCrossStageIO.0.vert", "link.missingCrossStageIO.0.frag"},
    }))
);
// clang-format on

}  // anonymous namespace
}  // namespace glslangtest
