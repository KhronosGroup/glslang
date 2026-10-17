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

#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "TestFixture.h"
#include "glslang/MachineIndependent/localintermediate.h"

namespace glslangtest {
namespace {

const char* const AutoTypeDeductionExtension = "#extension GL_EXT_type_deduction : require\n";

// Debug declaration nodes let us inspect even unused or constant variables.
class FindAutoDeclaration : public glslang::TIntermTraverser {
public:
    explicit FindAutoDeclaration(const char* name = "deduced") : name(name) {}

    bool visitVariableDecl(glslang::TVisit, glslang::TIntermVariableDecl* node) override
    {
        if (node->getDeclSymbol()->getName() == name)
            symbol = node->getDeclSymbol();
        return true;
    }

    const glslang::TIntermSymbol* symbol = nullptr;

private:
    const char* name;
};

struct AutoDeductionCase {
    const char* name;
    const char* explicitType;
    const char* expression;
    const char* setup = "";
    const char* use = "";
    const char* globals = "";
    const char* version = "450";
    const char* autoSpecifier = "auto";
    bool global = false;
    EShLanguage stage = EShLangVertex;
    bool vulkan = false;
};

void PrintTo(const AutoDeductionCase& test, std::ostream* stream)
{
    *stream << test.name;
}

std::string MakeAutoShader(const AutoDeductionCase& test, bool useAuto)
{
    const std::string declaration = std::string(useAuto ? test.autoSpecifier : test.explicitType) +
                                    " deduced = " + test.expression + ";\n";
    std::string source = std::string("#version ") + test.version + "\n";
    if (useAuto)
        source += AutoTypeDeductionExtension;
    source += std::string(test.globals) + "\n";
    if (test.global)
        source += declaration;
    source += "void main() {\n";
    // Substitute intermediate declarations too, so explicit controls never
    // depend on auto support.
    std::string setup = test.setup;
    const std::pair<std::string, std::string> markers[] = {
        {"@INT@", "int"}, {"@GRID@", "int[2][3]"}
    };
    for (const auto& marker : markers) {
        for (size_t pos = setup.find(marker.first); pos != std::string::npos; pos = setup.find(marker.first, pos)) {
            const std::string specifier = useAuto ? "auto" : marker.second;
            setup.replace(pos, marker.first.size(), specifier);
            pos += specifier.size();
        }
    }
    source += setup;
    source += "\n";
    if (!test.global)
        source += declaration;
    source += test.use;
    source += "\n}\n";
    return source;
}

using AutoTypeDeductionTest = GlslangTest<::testing::TestWithParam<AutoDeductionCase>>;

EShMessages ConfigureAutoShader(glslang::TShader& shader, const AutoDeductionCase& test)
{
    shader.setDebugInfo(true);
    if (!test.vulkan)
        return EShMsgDefault;
    shader.setEnvInput(glslang::EShSourceGlsl, test.stage, glslang::EShClientVulkan, 450);
    // NV cooperative_matrix2 (tensor layouts/views) requires SPIR-V 1.6.
    shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_3);
    shader.setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_6);
    return static_cast<EShMessages>(EShMsgSpvRules | EShMsgVulkanRules);
}

TEST_P(AutoTypeDeductionTest, ExplicitControlIsValid)
{
    const auto& test = GetParam();
    const std::string source = MakeAutoShader(test, false);
    glslang::TShader shader(test.stage);
    const auto messages = ConfigureAutoShader(shader, test);
    ASSERT_TRUE(compile(&shader, source, "", messages))
        << shader.getInfoLog() << '\n' << source;
    ASSERT_NE(shader.getIntermediate(), nullptr);
    ASSERT_NE(shader.getIntermediate()->getTreeRoot(), nullptr);
    FindAutoDeclaration declaration;
    shader.getIntermediate()->getTreeRoot()->traverse(&declaration);
    ASSERT_NE(declaration.symbol, nullptr) << source;
}

TEST_P(AutoTypeDeductionTest, MatchesExplicitDeclaration)
{
    const auto& test = GetParam();
    const std::string explicitSource = MakeAutoShader(test, false);
    const std::string autoSource = MakeAutoShader(test, true);
    SCOPED_TRACE(autoSource);

    // An independent explicit declaration checks that the test itself is legal.
    glslang::TShader explicitShader(test.stage);
    const auto messages = ConfigureAutoShader(explicitShader, test);
    ASSERT_TRUE(compile(&explicitShader, explicitSource, "", messages))
        << explicitShader.getInfoLog() << '\n' << explicitSource;

    glslang::TShader autoShader(test.stage);
    ConfigureAutoShader(autoShader, test);
    ASSERT_TRUE(compile(&autoShader, autoSource, "", messages)) << autoShader.getInfoLog();

    ASSERT_NE(explicitShader.getIntermediate(), nullptr);
    ASSERT_NE(autoShader.getIntermediate(), nullptr);
    ASSERT_NE(explicitShader.getIntermediate()->getTreeRoot(), nullptr);
    ASSERT_NE(autoShader.getIntermediate()->getTreeRoot(), nullptr);

    FindAutoDeclaration expected;
    FindAutoDeclaration actual;
    explicitShader.getIntermediate()->getTreeRoot()->traverse(&expected);
    autoShader.getIntermediate()->getTreeRoot()->traverse(&actual);
    ASSERT_NE(expected.symbol, nullptr);
    ASSERT_NE(actual.symbol, nullptr);

    const auto& expectedType = expected.symbol->getType();
    const auto& actualType = actual.symbol->getType();
    EXPECT_TRUE(actualType == expectedType)
        << "Expected " << expectedType.getCompleteString()
        << ", got " << actualType.getCompleteString();

    // TType equality describes the type, not the declaration's qualifiers.
    const auto& expectedQualifier = expectedType.getQualifier();
    const auto& actualQualifier = actualType.getQualifier();
    EXPECT_EQ(actualQualifier.storage, expectedQualifier.storage);
    EXPECT_EQ(actualQualifier.precision, expectedQualifier.precision);
    EXPECT_EQ(actualQualifier.builtIn, expectedQualifier.builtIn);
    EXPECT_EQ(actualQualifier.invariant, expectedQualifier.invariant);
    EXPECT_EQ(actualQualifier.noContraction, expectedQualifier.noContraction);
    EXPECT_EQ(actualQualifier.isSpecConstant(), expectedQualifier.isSpecConstant());
    EXPECT_EQ(actualQualifier.isNonUniform(), expectedQualifier.isNonUniform());
    EXPECT_EQ(actualQualifier.isMemory(), expectedQualifier.isMemory());
    EXPECT_EQ(actualQualifier.hasLocation(), expectedQualifier.hasLocation());
    EXPECT_EQ(actualQualifier.hasBinding(), expectedQualifier.hasBinding());
    EXPECT_EQ(actualQualifier.hasSet(), expectedQualifier.hasSet());
    EXPECT_EQ(actualQualifier.hasSpecConstantId(), expectedQualifier.hasSpecConstantId());
    if (expectedQualifier.hasSpecConstantId())
        EXPECT_EQ(actualQualifier.layoutSpecConstantId, expectedQualifier.layoutSpecConstantId);

    if (expectedQualifier.isFrontEndConstant()) {
        const auto& expectedValues = expected.symbol->getConstArray();
        const auto& actualValues = actual.symbol->getConstArray();
        ASSERT_GT(expectedValues.size(), 0);
        ASSERT_EQ(actualValues.size(), expectedValues.size());
        EXPECT_TRUE(actualValues == expectedValues)
            << "Auto deduction must preserve the folded initializer value";
    }

    // Check every array dimension explicitly; scalar-only inference must fail.
    ASSERT_EQ(actualType.isArray(), expectedType.isArray());
    if (expectedType.isArray()) {
        const auto* expectedSizes = expectedType.getArraySizes();
        const auto* actualSizes = actualType.getArraySizes();
        ASSERT_EQ(actualSizes->getNumDims(), expectedSizes->getNumDims());
        for (int dim = 0; dim < expectedSizes->getNumDims(); ++dim) {
            EXPECT_EQ(actualSizes->getDimSize(dim), expectedSizes->getDimSize(dim));
            EXPECT_EQ(actualSizes->getDimNode(dim) != nullptr, expectedSizes->getDimNode(dim) != nullptr);
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    ValuesAndQualifiers, AutoTypeDeductionTest,
    ::testing::ValuesIn(std::vector<AutoDeductionCase>{
        {"Bool", "bool", "true"},
        {"Int", "int", "1"},
        {"Uint", "uint", "1u"},
        {"Float", "float", "1.0"},
        {"Double", "double", "1.0lf"},
        {"BoolVector", "bvec3", "bvec3(true, false, true)"},
        {"IntVector", "ivec2", "ivec2(1, 2)"},
        {"UintVector", "uvec4", "uvec4(1u)"},
        {"FloatVector", "vec3", "vec3(1.0)", "", "deduced.x = 2.0;"},
        {"DoubleVector", "dvec2", "dvec2(1.0lf)"},
        {"SquareMatrix", "mat3", "mat3(1.0)"},
        {"RectangularMatrix", "mat2x3", "mat2x3(1.0)", "", "deduced[1][2] = 2.0;"},
        {"DoubleMatrix", "dmat3x2", "dmat3x2(1.0lf)"},
        {"UnaryExpression", "int", "-source", "int source = 2;"},
        {"BinaryExpression", "vec3", "source + vec3(1.0)", "vec3 source = vec3(2.0);"},
        {"ConditionalExpression", "vec2", "flag ? vec2(1.0) : vec2(2.0)", "bool flag = true;"},
        {"BuiltinFunction", "float", "length(vec3(1.0))"},
        {"Swizzle", "vec2", "source.yx", "vec4 source = vec4(1.0);"},
        {"VectorIndex", "float", "source[1]", "vec3 source = vec3(1.0);"},
        {"UserFunction", "uint", "makeValue()", "", "", "uint makeValue() { return 7u; }"},
        {"OverloadedFunction", "vec3", "makeValue(vec3(1.0))", "", "",
         "float makeValue(float x) { return x; } vec3 makeValue(vec3 x) { return x; }"},
        {"ChainedDeduction", "int", "first + 1", "@INT@ first = 1;"},
        {"DropsConst", "int", "source", "const int source = 0;", "deduced = 1;"},
        {"DropsUniform", "int", "source", "", "deduced = 1;", "uniform int source;"},
        {"DropsUniformVector", "vec4", "source", "", "deduced = vec4(0.0);", "uniform vec4 source;"},
        {"DropsInputStorage", "vec3", "source", "", "deduced.x = 2.0;",
         "layout(location=0) in vec3 source;"},
        {"DropsPrecise", "float", "source", "precise float source = 1.0;"},
        {"ExplicitConst", "const int", "1", "", "", "", "450", "const auto"},
        {"ExplicitConstRuntimeValue", "const float", "source", "float source = 1.0;",
         "", "", "450", "const auto"},
        {"Global", "int", "1", "", "deduced = 2;", "", "450", "auto", true},
        {"GlobalConst", "const vec3", "vec3(1.0)", "", "", "", "450", "const auto", true},
        {"DefaultFloatPrecision", "float", "source", "highp float source = 1.0;", "",
         "precision mediump float;", "310 es"},
        {"DefaultIntPrecision", "int", "source", "highp int source = 1;", "",
         "precision lowp int;", "310 es"},
        {"ExplicitPrecision", "highp float", "source", "lowp float source = 1.0;", "",
         "precision mediump float;", "310 es", "highp auto"},
        {"StructVariable", "Data", "source", "Data source = Data(vec3(1.0), 2);",
         "deduced.position.x = 3.0; deduced.count = 4;",
         "struct Data { vec3 position; int count; };"},
        {"StructConstructor", "Data", "Data(vec3(1.0), 2)", "", "",
         "struct Data { vec3 position; int count; };"},
        {"StructFunction", "Data", "makeData()", "", "",
         "struct Data { vec3 position; int count; }; Data makeData() { return Data(vec3(1.0), 2); }"},
        {"NestedStruct", "Outer", "source", "Outer source = Outer(Inner(1), vec2(2.0));",
         "deduced.inner.value = 3;",
         "struct Inner { int value; }; struct Outer { Inner inner; vec2 vector; };"},
        {"ConstStruct", "Data", "source", "const Data source = Data(1);",
         "deduced.value = 2;", "struct Data { int value; };"},
        {"StructMember", "vec3", "source.position", "Data source = Data(vec3(1.0));", "",
         "struct Data { vec3 position; };"},
        {"UninitializedArray", "int[10]", "source", "int source[10];",
         "deduced[0] = 1; deduced[9] = 2; int count[deduced.length()];"},
        {"InitializedArray", "int[3]", "source", "int source[3] = int[3](1, 2, 3);",
         "deduced[2] = 4;"},
        {"ArrayConstructor", "vec2[2]", "vec2[2](vec2(1.0), vec2(2.0))"},
        {"MultidimensionalArray", "int[2][3]", "source", "int source[2][3];",
         "deduced[1][2] = 4; int outer[deduced.length()]; int inner[deduced[0].length()];"},
        {"ArrayElement", "int", "source[0]", "int source[10];"},
        {"ArraySlice", "int[3]", "source[0]", "int source[2][3];", "deduced[2] = 4;"},
        {"ConstArray", "int[3]", "source", "const int source[3] = int[3](1, 2, 3);",
         "deduced[0] = 4;"},
        {"StructArray", "Data[2]", "source", "Data source[2];", "deduced[1].value = 4;",
         "struct Data { int value; };"},
        {"StructWithArray", "Data", "source", "Data source;", "deduced.values[2] = 4;",
         "struct Data { int values[3]; };"},
        {"ArrayFunction", "int[3]", "makeArray()", "", "deduced[2] = 4;",
         "int[3] makeArray() { return int[3](1, 2, 3); }"},
        {"MemberArray", "float[4]", "source.values", "Data source;", "deduced[3] = 1.0;",
         "struct Data { float values[4]; };"},
        {"ForInitializer", "int", "0", "for (@INT@ i = 0; i < 2; ++i) { int used = i; }"},
        {"NestedScope", "int", "source", "int source = 1; { @INT@ local = source; local = 2; }"},
        {"StructNameAsVariable", "int", "1", "", "", "struct deduced { int value; };"},
        {"Int64", "int64_t", "int64_t(1)", "", "",
         "#extension GL_ARB_gpu_shader_int64 : require"},
        {"Float16", "float16_t", "float16_t(1.0)", "", "",
         "#extension GL_EXT_shader_explicit_arithmetic_types_float16 : require"},
    }),
    [](const ::testing::TestParamInfo<AutoDeductionCase>& info) { return info.param.name; });

// These combinations follow the access chains and expression shapes in
// glsld's EvaluatorTest.glsl and OverloadTest.glsl. All declarations use
// concrete GLSL types; only the declaration under test uses auto.
const char* const DeepAutoGlobals = R"(
    struct InnerData {
        float scalar;
        int count;
        vec3 vector;
        mat2 matrices[2];
        int indices[2][3];
    };
    struct MiddleData {
        InnerData inner;
        vec4 vectors[3];
        mat4 matrix;
    };
    struct OuterData {
        MiddleData middle[2];
        dvec2 doubles;
    };

    const InnerData innerA = {
        1.25, 7, vec3(1.0, 2.0, 3.0),
        {mat2(1.0, 2.0, 3.0, 4.0), mat2(5.0, 6.0, 7.0, 8.0)},
        {{1, 2, 3}, {4, 5, 6}}
    };
    const InnerData innerB = {
        2.5, 11, vec3(4.0, 5.0, 6.0),
        {mat2(5.0, 6.0, 7.0, 8.0), mat2(9.0, 10.0, 11.0, 12.0)},
        {{7, 8, 9}, {10, 11, 12}}
    };
    const MiddleData middleA = {
        innerA,
        {vec4(1.0, 2.0, 3.0, 4.0), vec4(5.0, 6.0, 7.0, 8.0), vec4(9.0, 10.0, 11.0, 12.0)},
        mat4(1.0)
    };
    const MiddleData middleB = {
        innerB,
        {vec4(20.0, 21.0, 22.0, 23.0), vec4(24.0, 25.0, 26.0, 27.0), vec4(28.0, 29.0, 30.0, 31.0)},
        mat4(2.0)
    };
    const OuterData constantOuter = {{middleA, middleB}, dvec2(9.5, 10.5)};
    OuterData makeOuter() { return constantOuter; }

    // Different result types expose which overload was selected in the AST.
    bool selectType(float x) { return true; }
    int selectType(int x) { return 1; }
    float selectType(vec2 x) { return 1.0; }
    vec2 selectType(vec3 x) { return vec2(1.0); }
    vec3 selectType(vec4 x) { return vec3(1.0); }
    vec4 selectType(mat2 x) { return vec4(1.0); }
    ivec2 selectType(mat4 x) { return ivec2(1); }
    dvec2 selectType(InnerData x) { return dvec2(1.0); }
    dvec3 selectType(MiddleData x) { return dvec3(1.0); }
    dvec4 selectType(OuterData x) { return dvec4(1.0); }
    bvec2 selectType(int x[3]) { return bvec2(true); }
    bvec3 selectType(int x[2][3]) { return bvec3(true); }
    bvec4 selectType(mat2 x[2]) { return bvec4(true); }
)";

AutoDeductionCase DeepAutoCase(const char* name, const char* explicitType, const char* expression,
                               const char* use = "", const char* setup = "OuterData source = makeOuter();",
                               const char* autoSpecifier = "auto")
{
    return {name, explicitType, expression, setup, use, DeepAutoGlobals, "450", autoSpecifier};
}

INSTANTIATE_TEST_SUITE_P(
    DeepExpressions, AutoTypeDeductionTest,
    ::testing::ValuesIn(std::vector<AutoDeductionCase>{
        DeepAutoCase("DeepScalar", "int", "source.middle[1].inner.indices[1][2]", "deduced = 9;"),
        DeepAutoCase("ComputedIndices", "int",
                    "source.middle[bitCount(3)-1].inner.indices[bitCount(3)-1][bitCount(7)-1]"),
        DeepAutoCase("MatrixArrayColumnSwizzle", "vec2", "source.middle[0].inner.matrices[1][0].yx"),
        DeepAutoCase("VectorArraySwizzle", "vec3", "source.middle[1].vectors[2].wzx"),
        DeepAutoCase("MatrixColumnSwizzle", "vec3", "source.middle[0].matrix[2].wzx"),
        DeepAutoCase("TemporaryAccessChain", "vec2", "makeOuter().middle[1].inner.matrices[0][1].yx"),
        DeepAutoCase("TemporaryArrayConstructor", "dvec2",
                    "OuterData[2](makeOuter(), makeOuter())[1].doubles.yx"),
        DeepAutoCase("ArrayOfMatrixCopies", "mat2[2]", "source.middle[0].inner.matrices",
                    "deduced[1][0].x = 3.0;"),
        DeepAutoCase("NestedArrayCopy", "int[2][3]", "source.middle[1].inner.indices",
                    "deduced[1][2] = 3;"),
        DeepAutoCase("NestedSubarrayCopy", "int[3]", "source.middle[1].inner.indices[0]",
                    "deduced[2] = 3;"),
        DeepAutoCase("WholeOuterCopy", "OuterData", "constantOuter",
                    "deduced.middle[1].inner.indices[0][2] = 3;"),
        DeepAutoCase("MiddleArrayCopy", "MiddleData[2]", "constantOuter.middle",
                    "deduced[1].inner.matrices[0][1].y = 3.0;"),
        DeepAutoCase("NestedBuiltinArguments", "vec3",
                    "max(normalize(source.middle[0].inner.vector.zyx + vec3(0.5)), "
                    "abs(source.middle[1].vectors[2].wzx))"),
        DeepAutoCase("MatrixVectorArithmetic", "vec4",
                    "source.middle[1].matrix * source.middle[0].inner.vector.xyzz"),
        DeepAutoCase("MatrixConstructorArithmetic", "mat2",
                    "mat2(source.middle[0].inner.vector.xy, source.middle[1].vectors[2].wz) * "
                    "transpose(source.middle[0].inner.matrices[1])"),
        DeepAutoCase("NestedConditional", "vec2",
                    "source.middle[0].inner.count > 0 ? "
                    "(source.middle[1].inner.count > 0 ? source.middle[1].inner.vector.xy : "
                    "source.middle[0].vectors[0].zw) : source.middle[1].vectors[1].yx"),
        DeepAutoCase("NestedFunctionArithmetic", "dvec2",
                    "(makeOuter().doubles * makeOuter().doubles.x + makeOuter().doubles) / "
                    "(makeOuter().doubles + 1.0lf)"),
        DeepAutoCase("NestedArrayConstructors", "vec2",
                    "vec2[2](source.middle[0].vectors[0].xy, source.middle[1].vectors[1].zw)[1] + "
                    "source.middle[0].inner.matrices[0] * source.middle[1].inner.vector.xy"),
        DeepAutoCase("ThreeDimensionalArray", "vec2[2][2][2]", "cube", "deduced[1][1][1].y = 3.0;",
                    "vec2 cube[2][2][2];"),
        DeepAutoCase("ThreeDimensionalSlice", "vec2[2][2]", "cube[1]", "deduced[1][1].y = 3.0;",
                    "vec2 cube[2][2][2];"),
        DeepAutoCase("OverloadScalar", "bool", "selectType(source.middle[0].inner.scalar)"),
        DeepAutoCase("OverloadMatrix", "vec4", "selectType(source.middle[0].inner.matrices[1])"),
        DeepAutoCase("OverloadInnerStruct", "dvec2", "selectType(source.middle[1].inner)"),
        DeepAutoCase("OverloadMiddleStruct", "dvec3", "selectType(source.middle[0])"),
        DeepAutoCase("OverloadOuterStruct", "dvec4", "selectType(makeOuter())"),
        DeepAutoCase("OverloadArray", "bvec2", "selectType(source.middle[0].inner.indices[1])"),
        DeepAutoCase("OverloadNestedArray", "bvec3", "selectType(source.middle[1].inner.indices)"),
        DeepAutoCase("OverloadMatrixArray", "bvec4", "selectType(source.middle[0].inner.matrices)"),
        DeepAutoCase("FourNestedOverloads", "bool",
                    "selectType(selectType(selectType(selectType(source.middle[0].vectors[0]))))"),
        DeepAutoCase("DeductionFeedsOverload", "bvec3", "selectType(previous)", "",
                    "OuterData source = makeOuter(); @GRID@ previous = source.middle[0].inner.indices;"),
        DeepAutoCase("FoldedDeepInteger", "const int", "constantOuter.middle[1].inner.indices[1][2]",
                    "", "", "const auto"),
        DeepAutoCase("FoldedComputedIndex", "const int",
                    "constantOuter.middle[bitCount(3)-1].inner.indices[1][bitCount(7)-1]",
                    "", "", "const auto"),
        DeepAutoCase("FoldedMatrixSwizzle", "const vec2", "constantOuter.middle[1].inner.matrices[0][1].yx",
                    "", "", "const auto"),
        DeepAutoCase("FoldedBuiltinComposition", "const vec3",
                    "max(constantOuter.middle[0].inner.vector, abs(constantOuter.middle[1].vectors[0].wzx))",
                    "", "", "const auto"),
        DeepAutoCase("FoldedMatrixVector", "const vec4",
                    "constantOuter.middle[1].matrix * constantOuter.middle[0].vectors[0]",
                    "", "", "const auto"),
    }),
    [](const ::testing::TestParamInfo<AutoDeductionCase>& info) { return info.param.name; });

INSTANTIATE_TEST_SUITE_P(
    ExpressionBoundaries, AutoTypeDeductionTest,
    ::testing::ValuesIn(std::vector<AutoDeductionCase>{
        {"ParenthesizedValue", "vec2", "(((source)))", "vec2 source = vec2(1.0);", "deduced.x = 2.0;"},
        {"CommaValue", "uint", "(sideEffect(), 3u)", "", "", "void sideEffect() {}"},
        {"CommaArray", "int[3]", "(sideEffect(), source)", "int source[3];", "deduced[2] = 4;",
         "void sideEffect() {}"},
        {"AssignmentValue", "int", "(source = 3)", "int source = 1;", "deduced = 4;"},
        {"CompoundAssignmentValue", "vec3", "(source += vec3(1.0))", "vec3 source = vec3(1.0);"},
        {"PreIncrementValue", "int", "++source", "int source = 1;"},
        {"PostIncrementValue", "int", "source++", "int source = 1;"},
        {"ArrayConditional", "int[3]", "flag ? first : second",
         "bool flag = true; int first[3]; int second[3];", "deduced[2] = 4;"},
        {"InferredLengthSourceArray", "int[3]", "source", "int source[] = int[](1, 2, 3);"},
        {"InferredLengthArrayConstructor", "int[3]", "int[](1, 2, 3)"},
        {"ConstructorInfersOuterArraySize", "int[2][3]",
         "int[][3](int[3](1, 2, 3), int[3](4, 5, 6))", "", "deduced[1][2] = 7;"},
        {"ConstructorInfersInnerArraySize", "int[2][3]",
         "int[2][](int[](1, 2, 3), int[](4, 5, 6))", "", "deduced[1][2] = 7;"},
        {"ConstructorInfersEveryArraySize", "int[2][3]",
         "int[][](int[](1, 2, 3), int[](4, 5, 6))", "", "deduced[1][2] = 7;"},
        {"ConstructorInfersThreeArraySizes", "int[2][2][2]",
         "int[][][](int[][](int[](1, 2), int[](3, 4)), int[][](int[](5, 6), int[](7, 8)))",
         "", "deduced[1][1][1] = 9;"},
        {"SourceInfersEveryArraySizeFromConstructor", "int[2][3]", "source",
         "int source[][] = int[][](int[](1, 2, 3), int[](4, 5, 6));", "deduced[1][2] = 7;"},
        {"SourceInfersOuterArraySizeFromBraces", "int[2][3]", "source",
         "int source[][3] = {{1, 2, 3}, {4, 5, 6}};", "deduced[1][2] = 7;"},
        {"ArrayLengthResult", "int", "source.length()", "vec3 source[4];"},
        {"MatrixColumnResult", "vec3", "source[1]", "mat2x3 source = mat2x3(1.0);"},
        {"ConstGlobalSource", "int", "source", "", "deduced = 2;",
         "const int source = 1;"},
        {"ShadowsGlobalWithDifferentType", "int", "1", "", "deduced = 2;", "float deduced = 1.0;"},
        {"InitializerLooksUpOuterScope", "float", "deduced", "", "deduced = 2.0;", "float deduced = 1.0;"},
        {"DefaultPrecisionIsLocal", "float", "source", "precision lowp float; highp float source = 1.0;", "",
         "precision highp float;", "310 es"},
        {"DropsUniformLocation", "float", "source", "", "deduced = 2.0;",
         "layout(location=7) uniform float source;"},
        {"DropsBufferMemoryQualifiers", "vec4", "source", "", "deduced.x = 2.0;",
         "layout(std430, binding=0) readonly coherent buffer Inputs { vec4 source; };"},
        {"BuiltinVariable", "int", "gl_VertexID", "", "deduced = 2;"},
        {"RepeatedSwizzleIsCopiedValue", "vec3", "source.xxx", "vec3 source = vec3(1.0);",
         "deduced.y = 2.0;"},
        {"NonuniformValue", "int", "nonuniformEXT(source)", "int source = 1;", "deduced = 2;",
         "#extension GL_EXT_nonuniform_qualifier : require"},
    }),
    [](const ::testing::TestParamInfo<AutoDeductionCase>& info) { return info.param.name; });

const char* const AutoCoopMatKHRGlobals = R"(
    #extension GL_KHR_memory_scope_semantics : require
    #extension GL_KHR_cooperative_matrix : require
    #extension GL_EXT_shader_explicit_arithmetic_types : require
    layout(local_size_x=32) in;
)";

const char* const AutoCoopMatNVGlobals = R"(
    #extension GL_KHR_memory_scope_semantics : require
    #extension GL_NV_cooperative_matrix : require
    #extension GL_EXT_shader_explicit_arithmetic_types : require
    layout(local_size_x=32) in;
)";

const char* const AutoLongVectorGlobals = R"(
    #extension GL_EXT_long_vector : require
    #extension GL_EXT_shader_explicit_arithmetic_types : require
    layout(local_size_x=32) in;
)";

const char* const AutoCoopVectorGlobals = R"(
    #extension GL_NV_cooperative_vector : require
    #extension GL_EXT_shader_explicit_arithmetic_types : require
    layout(local_size_x=32) in;
)";

AutoDeductionCase ParameterizedAutoCase(const char* name, const char* explicitType,
                                      const char* expression, const char* setup,
                                      const char* globals, const char* use = "")
{
    return {name, explicitType, expression, setup, use, globals, "460", "auto", false,
            EShLangCompute, true};
}

INSTANTIATE_TEST_SUITE_P(
    ParameterizedTypes, AutoTypeDeductionTest,
    ::testing::ValuesIn(std::vector<AutoDeductionCase>{
        ParameterizedAutoCase("CoopMatKHRFloat", "coopmat<float, gl_ScopeSubgroup, 16, 8, gl_MatrixUseAccumulator>",
                             "source", "coopmat<float, gl_ScopeSubgroup, 16, 8, gl_MatrixUseAccumulator> source;",
                             AutoCoopMatKHRGlobals),
        ParameterizedAutoCase("CoopMatKHRHalf", "coopmat<float16_t, gl_ScopeSubgroup, 16, 8, gl_MatrixUseA>",
                             "source", "coopmat<float16_t, gl_ScopeSubgroup, 16, 8, gl_MatrixUseA> source;",
                             AutoCoopMatKHRGlobals),
        ParameterizedAutoCase("CoopMatKHRInt", "coopmat<int, gl_ScopeSubgroup, 16, 8, gl_MatrixUseAccumulator>",
                             "source", "coopmat<int, gl_ScopeSubgroup, 16, 8, gl_MatrixUseAccumulator> source;",
                             AutoCoopMatKHRGlobals),
        ParameterizedAutoCase("CoopMatKHRUint8", "coopmat<uint8_t, gl_ScopeSubgroup, 8, 16, gl_MatrixUseB>",
                             "source", "coopmat<uint8_t, gl_ScopeSubgroup, 8, 16, gl_MatrixUseB> source;",
                             AutoCoopMatKHRGlobals),
        ParameterizedAutoCase("CoopMatKHRConstructor", "coopmat<float, gl_ScopeSubgroup, 16, 8, gl_MatrixUseAccumulator>",
                             "coopmat<float, gl_ScopeSubgroup, 16, 8, gl_MatrixUseAccumulator>(1.0)", "",
                             AutoCoopMatKHRGlobals),
        ParameterizedAutoCase("CoopMatKHRArray", "coopmat<float, gl_ScopeSubgroup, 16, 8, gl_MatrixUseAccumulator>[2]",
                             "source", "coopmat<float, gl_ScopeSubgroup, 16, 8, gl_MatrixUseAccumulator> source[2];",
                             AutoCoopMatKHRGlobals),
        ParameterizedAutoCase("CoopMatNVFloat", "fcoopmatNV<32, gl_ScopeSubgroup, 16, 8>",
                             "source", "fcoopmatNV<32, gl_ScopeSubgroup, 16, 8> source;", AutoCoopMatNVGlobals),
        ParameterizedAutoCase("CoopMatNVHalf", "fcoopmatNV<16, gl_ScopeSubgroup, 8, 16>",
                             "source", "fcoopmatNV<16, gl_ScopeSubgroup, 8, 16> source;", AutoCoopMatNVGlobals),
        ParameterizedAutoCase("CoopMatNVConstructor", "fcoopmatNV<32, gl_ScopeSubgroup, 8, 8>",
                             "fcoopmatNV<32, gl_ScopeSubgroup, 8, 8>(1.0)", "", AutoCoopMatNVGlobals),
        ParameterizedAutoCase("LongVectorFloat", "vector<float, 8>", "source",
                             "vector<float, 8> source = vector<float, 8>(1.0);", AutoLongVectorGlobals),
        ParameterizedAutoCase("LongVectorHalf", "vector<float16_t, 16>", "source",
                             "vector<float16_t, 16> source = vector<float16_t, 16>(1.0);", AutoLongVectorGlobals),
        ParameterizedAutoCase("LongVectorInt", "vector<int, 12>", "source",
                             "vector<int, 12> source = vector<int, 12>(1);", AutoLongVectorGlobals),
        ParameterizedAutoCase("LongVectorUint8", "vector<uint8_t, 8>", "source",
                             "vector<uint8_t, 8> source = vector<uint8_t, 8>(uint8_t(1));", AutoLongVectorGlobals),
        ParameterizedAutoCase("LongVectorConstructor", "vector<float, 8>", "vector<float, 8>(1.0)", "",
                             AutoLongVectorGlobals),
        ParameterizedAutoCase("LongVectorArithmetic", "vector<float, 8>", "source + source",
                             "vector<float, 8> source = vector<float, 8>(1.0);", AutoLongVectorGlobals),
        ParameterizedAutoCase("LongVectorArray", "vector<float, 8>[2]", "source",
                             "vector<float, 8> source[2];", AutoLongVectorGlobals),
        ParameterizedAutoCase("CoopVectorFloat", "coopvecNV<float, 8>", "source",
                             "coopvecNV<float, 8> source = coopvecNV<float, 8>(1.0);", AutoCoopVectorGlobals),
        ParameterizedAutoCase("CoopVectorHalf", "coopvecNV<float16_t, 16>", "source",
                             "coopvecNV<float16_t, 16> source = coopvecNV<float16_t, 16>(1.0);", AutoCoopVectorGlobals),
        ParameterizedAutoCase("CoopVectorUint", "coopvecNV<uint, 8>", "source",
                             "coopvecNV<uint, 8> source = coopvecNV<uint, 8>(1u);", AutoCoopVectorGlobals),
        ParameterizedAutoCase("CoopVectorConstructor", "coopvecNV<float, 8>", "coopvecNV<float, 8>(1.0)", "",
                             AutoCoopVectorGlobals),
    }),
    [](const ::testing::TestParamInfo<AutoDeductionCase>& info) { return info.param.name; });

const char* const AutoTensorNVGlobals = R"(
    #extension GL_KHR_memory_scope_semantics : require
    #extension GL_KHR_cooperative_matrix : require
    #extension GL_NV_cooperative_matrix2 : require
    layout(local_size_x=32) in;
)";

const char* const AutoReferenceGlobals = R"(
    #extension GL_EXT_buffer_reference : require
    #extension GL_EXT_shader_explicit_arithmetic_types_int64 : require
    layout(buffer_reference, std430) buffer Reference { int value; };
    Reference makeReference() { return Reference(uint64_t(0)); }
    layout(local_size_x=32) in;
)";

const char* const AutoSpirvTypeGlobals = R"(
    #extension GL_EXT_spirv_intrinsics : require
    layout(local_size_x=32) in;
)";

INSTANTIATE_TEST_SUITE_P(
    TensorAndSpecialTypes, AutoTypeDeductionTest,
    ::testing::ValuesIn(std::vector<AutoDeductionCase>{
        ParameterizedAutoCase("TensorLayoutFactory", "tensorLayoutNV<2>", "createTensorLayoutNV(2)", "",
                             AutoTensorNVGlobals),
        ParameterizedAutoCase("TensorLayoutCopy", "tensorLayoutNV<2>", "source",
                             "tensorLayoutNV<2> source = createTensorLayoutNV(2);", AutoTensorNVGlobals),
        ParameterizedAutoCase("TensorLayoutClamp", "tensorLayoutNV<3, 1>", "createTensorLayoutNV(3, 1)", "",
                             AutoTensorNVGlobals),
        ParameterizedAutoCase("TensorLayoutNestedFactory", "tensorLayoutNV<2>",
                             "sliceTensorLayoutNV(setTensorLayoutDimensionNV(createTensorLayoutNV(2), 256, 512), 0, 32, 0, 64)",
                             "", AutoTensorNVGlobals),
        ParameterizedAutoCase("TensorLayoutArray", "tensorLayoutNV<2>[2]", "source",
                             "tensorLayoutNV<2> source[2];", AutoTensorNVGlobals),
        ParameterizedAutoCase("TensorViewFactory", "tensorViewNV<5>", "createTensorViewNV(5)", "",
                             AutoTensorNVGlobals),
        ParameterizedAutoCase("TensorViewCopy", "tensorViewNV<2, true, 1, 0>", "source",
                             "tensorViewNV<2, true, 1, 0> source = createTensorViewNV(2, true, 1, 0);", AutoTensorNVGlobals),
        ParameterizedAutoCase("TensorViewPermutation", "tensorViewNV<3, false, 0, 2, 1>",
                             "createTensorViewNV(3, false, 0, 2, 1)", "", AutoTensorNVGlobals),
        ParameterizedAutoCase("TensorViewNestedFactory", "tensorViewNV<2, true, 1, 0>",
                             "setTensorViewStrideNV(setTensorViewDimensionsNV(createTensorViewNV(2, true, 1, 0), 16, 32), 32, 1)",
                             "", AutoTensorNVGlobals),
        ParameterizedAutoCase("TensorViewArray", "tensorViewNV<2>[2]", "source",
                             "tensorViewNV<2> source[2];", AutoTensorNVGlobals),
        ParameterizedAutoCase("BufferReferenceCopy", "Reference", "source",
                             "Reference source = Reference(uint64_t(0));", AutoReferenceGlobals),
        ParameterizedAutoCase("BufferReferenceFunction", "Reference", "makeReference()", "", AutoReferenceGlobals),
        ParameterizedAutoCase("BufferReferenceArray", "Reference[2]", "source", "Reference source[2];", AutoReferenceGlobals),
        ParameterizedAutoCase("SpirvTypeStruct", "spirv_type(id=30)", "source", "spirv_type(id=30) source;",
                             AutoSpirvTypeGlobals),
        ParameterizedAutoCase("SpirvTypeInteger", "spirv_type(id=21, 32, 1)", "source",
                             "spirv_type(id=21, 32, 1) source;", AutoSpirvTypeGlobals),
    }),
    [](const ::testing::TestParamInfo<AutoDeductionCase>& info) { return info.param.name; });

const char* const AutoSpecializationGlobals = R"(
    layout(local_size_x=1) in;
    layout(constant_id=0) const int Length = 3;
)";

AutoDeductionCase SpecializationAutoCase(const char* name, const char* explicitType,
                                       const char* expression, const char* setup = "",
                                       const char* autoSpecifier = "auto", bool global = false)
{
    auto test = ParameterizedAutoCase(name, explicitType, expression, setup, AutoSpecializationGlobals);
    test.autoSpecifier = autoSpecifier;
    test.global = global;
    return test;
}

INSTANTIATE_TEST_SUITE_P(
    SpecializationConstants, AutoTypeDeductionTest,
    ::testing::ValuesIn(std::vector<AutoDeductionCase>{
        SpecializationAutoCase("DropsSourceConstantId", "int", "Length"),
        SpecializationAutoCase("ConstPreservesSpecialization", "const int", "Length", "", "const auto"),
        SpecializationAutoCase("DerivedSpecialization", "const int", "Length * 2 + 1", "", "const auto"),
        SpecializationAutoCase("ExplicitConstantId", "layout(constant_id=7) const int", "1", "",
                               "layout(constant_id=7) const auto", true),
        SpecializationAutoCase("ArraySpecializedInnerLength", "int[2][Length]", "source", "int source[2][Length];"),
    }),
    [](const ::testing::TestParamInfo<AutoDeductionCase>& info) { return info.param.name; });

struct AutoResourceRestrictionCase {
    const char* name;
    const char* type;
    const char* globals;
    const char* diagnostic;
};

void PrintTo(const AutoResourceRestrictionCase& test, std::ostream* stream)
{
    *stream << test.name;
}

using AutoTypeDeductionResourceTest = GlslangTest<::testing::TestWithParam<AutoResourceRestrictionCase>>;

// Deducing a resource type must not bypass the existing declaration rules.
// Both the explicit declaration and auto must reject an illegal local copy.
TEST_P(AutoTypeDeductionResourceTest, PreservesLocalResourceRestrictions)
{
    const auto& test = GetParam();
    const auto declaration = ParameterizedAutoCase(test.name, test.type, "source", "", test.globals);
    for (bool useAuto : {false, true}) {
        const std::string source = MakeAutoShader(declaration, useAuto);
        SCOPED_TRACE(source);
        glslang::TShader shader(EShLangCompute);
        const auto messages = ConfigureAutoShader(shader, declaration);
        ASSERT_FALSE(compile(&shader, source, "", messages));
        const std::string log = shader.getInfoLog();
        EXPECT_NE(log.find(test.diagnostic), std::string::npos) << log;
        EXPECT_EQ(log.find("syntax error"), std::string::npos) << log;
    }
}

INSTANTIATE_TEST_SUITE_P(
    ResourceRules, AutoTypeDeductionResourceTest,
    ::testing::ValuesIn(std::vector<AutoResourceRestrictionCase>{
        {"TensorARMInt", "tensorARM<int, 2>",
         "#extension GL_ARM_tensors : require\n"
         "layout(local_size_x=1) in; layout(binding=0) uniform tensorARM<int, 2> source;",
         "tensorARM types can only be used in uniform variables or function parameters"},
        {"TensorARMFloat", "tensorARM<float, 4>",
         "#extension GL_ARM_tensors : require\n"
         "layout(local_size_x=1) in; layout(binding=0) uniform tensorARM<float, 4> source;",
         "tensorARM types can only be used in uniform variables or function parameters"},
        {"Sampler", "sampler2D", "layout(local_size_x=1) in; layout(binding=0) uniform sampler2D source;",
         "sampler/image types can only be used in uniform variables or function parameters"},
        {"Image", "image2D", "layout(local_size_x=1) in; layout(binding=0, rgba32f) uniform image2D source;",
         "sampler/image types can only be used in uniform variables or function parameters"},
        {"RayQuery", "rayQueryEXT",
         "#extension GL_EXT_ray_query : require\nlayout(local_size_x=1) in; rayQueryEXT source;",
         "ray queries can only be initialized"},
        {"SpecializedArrayInitializer", "int[Length]",
         "layout(local_size_x=1) in; layout(constant_id=0) const int Length=3; int source[Length];",
         "can't use with types containing arrays sized with a specialization constant"},
        {"SpecializedExpressionArrayInitializer", "int[Length+1]",
         "layout(local_size_x=1) in; layout(constant_id=0) const int Length=3; int source[Length+1];",
         "can't use with types containing arrays sized with a specialization constant"},
        {"RuntimeSizedArrayInitializer", "int[]",
         "layout(local_size_x=1) in; layout(std430, binding=0) buffer Inputs { int source[]; };",
         "array"},
    }),
    [](const ::testing::TestParamInfo<AutoResourceRestrictionCase>& info) { return info.param.name; });

using AutoTypeDeductionMultiDeclarationTest = GlslangTest<::testing::TestWithParam<AutoDeductionCase>>;

// The expression field contains three comma-separated initialized declarators.
// Compare all three with an explicit control, including qualifiers and constants.
TEST_P(AutoTypeDeductionMultiDeclarationTest, EveryDeclaratorMatchesExplicitDeclaration)
{
    const auto& test = GetParam();
    const std::string explicitSource = MakeAutoShader(test, false);
    const std::string autoSource = MakeAutoShader(test, true);
    SCOPED_TRACE(autoSource);
    glslang::TShader control(test.stage);
    const auto messages = ConfigureAutoShader(control, test);
    ASSERT_TRUE(compile(&control, explicitSource, "", messages)) << control.getInfoLog() << '\n' << explicitSource;
    glslang::TShader shader(test.stage);
    ConfigureAutoShader(shader, test);
    ASSERT_TRUE(compile(&shader, autoSource, "", messages)) << shader.getInfoLog();
    ASSERT_NE(control.getIntermediate(), nullptr);
    ASSERT_NE(shader.getIntermediate(), nullptr);
    ASSERT_NE(control.getIntermediate()->getTreeRoot(), nullptr);
    ASSERT_NE(shader.getIntermediate()->getTreeRoot(), nullptr);

    for (const char* name : {"deduced", "second", "third"}) {
        SCOPED_TRACE(name);
        FindAutoDeclaration expected(name);
        FindAutoDeclaration actual(name);
        control.getIntermediate()->getTreeRoot()->traverse(&expected);
        shader.getIntermediate()->getTreeRoot()->traverse(&actual);
        ASSERT_NE(expected.symbol, nullptr);
        ASSERT_NE(actual.symbol, nullptr);
        const auto& expectedType = expected.symbol->getType();
        const auto& actualType = actual.symbol->getType();
        EXPECT_TRUE(actualType == expectedType)
            << "Expected " << expectedType.getCompleteString() << ", got " << actualType.getCompleteString();
        const auto& expectedQualifier = expectedType.getQualifier();
        const auto& actualQualifier = actualType.getQualifier();
        EXPECT_EQ(actualQualifier.storage, expectedQualifier.storage);
        EXPECT_EQ(actualQualifier.precision, expectedQualifier.precision);
        EXPECT_EQ(actualQualifier.isFrontEndConstant(), expectedQualifier.isFrontEndConstant());
        EXPECT_EQ(actualQualifier.isSpecConstant(), expectedQualifier.isSpecConstant());
        EXPECT_EQ(actualQualifier.isMemory(), expectedQualifier.isMemory());
        EXPECT_EQ(actualQualifier.isNonUniform(), expectedQualifier.isNonUniform());
        EXPECT_EQ(actualQualifier.hasLocation(), expectedQualifier.hasLocation());
        EXPECT_EQ(actualQualifier.hasBinding(), expectedQualifier.hasBinding());
        EXPECT_EQ(actualQualifier.hasSpecConstantId(), expectedQualifier.hasSpecConstantId());
        if (expectedQualifier.isFrontEndConstant())
            EXPECT_TRUE(actual.symbol->getConstArray() == expected.symbol->getConstArray());
    }
}

INSTANTIATE_TEST_SUITE_P(
    MultipleDeclarators, AutoTypeDeductionMultiDeclarationTest,
    ::testing::ValuesIn(std::vector<AutoDeductionCase>{
        {"Integers", "int", "1, second = 2, third = 3", "", "deduced = second + third;"},
        {"EarlierDeclaratorsAreVisible", "int", "1, second = deduced + 1, third = second + deduced"},
        {"ParenthesizedCommaIsExpression", "uint", "(1, 2u), second = (3, 4u), third = second + 1u"},
        {"FunctionArgumentsContainCommas", "vec3", "vec3(1.0, 2.0, 3.0), second = vec3(4.0, 5.0, 6.0), third = second"},
        {"DropsSourceConst", "int", "source, second = source, third = source", "const int source = 1;",
         "deduced = 2; second = 3; third = 4;"},
        {"ConstQualifiesEveryDeclarator", "const int", "1, second = deduced + 1, third = second + 1", "",
         "", "", "450", "const auto"},
        {"Global", "int", "1, second = 2, third = 3", "", "second = third;", "", "450", "auto", true},
        {"GlobalConstChain", "const int", "1, second = deduced + 1, third = second + 1", "", "",
         "", "450", "const auto", true},
        {"Arrays", "int[2]", "source, second = deduced, third = int[2](3, 4)", "int source[2] = int[2](1, 2);",
         "deduced[0] = 3; second[1] = 4; third[0] = 5;"},
        {"MultidimensionalArrays", "int[2][3]", "source, second = deduced, third = second", "int source[2][3];",
         "second[1][2] = 4; third[0][1] = 5;"},
        {"StructureIdentity", "Data", "Data(1), second = deduced, third = Data(3)", "", "second.value = 4;",
         "struct Data { int value; };"},
        {"DifferentSourcePrecisions", "float", "highSource, second = lowSource, third = deduced",
         "highp float highSource = 1.0; lowp float lowSource = 2.0;", "", "precision mediump float;", "310 es"},
        {"ExplicitPrecisionQualifiesEveryDeclarator", "highp float", "1.0, second = 2.0, third = second", "", "",
         "precision mediump float;", "310 es", "highp auto"},
        {"DropsUniformLayout", "float", "source, second = source, third = source", "",
         "deduced = 1.0; second = 2.0; third = 3.0;", "layout(location=7) uniform float source;"},
        {"DropsBufferMemoryQualifiers", "vec4", "source, second = source, third = source", "", "third.x = 2.0;",
         "layout(std430, binding=0) coherent readonly buffer Inputs { vec4 source; };"},
        {"ForInitializer", "int", "0, second = deduced, third = second", "for (@INT@ i = 0, j = i; i < 2; ++i) { j += i; }"},
        ParameterizedAutoCase("LongVector", "vector<float, 8>", "source, second = deduced, third = second",
                             "vector<float, 8> source = vector<float, 8>(1.0);", AutoLongVectorGlobals),
        ParameterizedAutoCase("CooperativeMatrix", "coopmat<float, gl_ScopeSubgroup, 16, 8, gl_MatrixUseAccumulator>",
                             "source, second = deduced, third = second",
                             "coopmat<float, gl_ScopeSubgroup, 16, 8, gl_MatrixUseAccumulator> source;", AutoCoopMatKHRGlobals),
        ParameterizedAutoCase("CooperativeVector", "coopvecNV<float, 8>", "source, second = deduced, third = second",
                             "coopvecNV<float, 8> source = coopvecNV<float, 8>(1.0);", AutoCoopVectorGlobals),
        ParameterizedAutoCase("TensorLayout", "tensorLayoutNV<2>", "createTensorLayoutNV(2), second = deduced, third = second",
                             "", AutoTensorNVGlobals),
        ParameterizedAutoCase("TensorView", "tensorViewNV<2, true, 1, 0>",
                             "createTensorViewNV(2, true, 1, 0), second = deduced, third = second", "", AutoTensorNVGlobals),
        ParameterizedAutoCase("BufferReference", "Reference", "makeReference(), second = deduced, third = second",
                             "", AutoReferenceGlobals),
        SpecializationAutoCase("SpecializedInnerArrayLength", "int[2][Length]", "source, second = deduced, third = second",
                               "int source[2][Length];"),
        SpecializationAutoCase("SpecializationExpressionChain", "const int", "Length, second = deduced + 1, third = second + 1",
                               "", "const auto"),
    }),
    [](const ::testing::TestParamInfo<AutoDeductionCase>& info) { return info.param.name; });

struct AutoErrorCase {
    const char* name;
    const char* source;
    const char* diagnostic;
    EShLanguage stage = EShLangVertex;
    bool vulkan = false;
};

void PrintTo(const AutoErrorCase& test, std::ostream* stream)
{
    *stream << test.name;
}

using AutoTypeDeductionErrorTest = GlslangTest<::testing::TestWithParam<AutoErrorCase>>;

TEST_P(AutoTypeDeductionErrorTest, RejectsInvalidDeclaration)
{
    // Prevent a broken lexer from making every negative test pass trivially.
    glslang::TShader probe(EShLangVertex);
    ASSERT_TRUE(compile(&probe, std::string("#version 450\n") + AutoTypeDeductionExtension +
                       "void main() { auto probe = 1; }", "", EShMsgDefault))
        << "Basic auto declaration must work before testing rejection:\n" << probe.getInfoLog();

    const auto& test = GetParam();
    const std::string source = std::string("#version 450\n") + AutoTypeDeductionExtension + test.source;
    SCOPED_TRACE(source);
    glslang::TShader shader(test.stage);
    AutoDeductionCase environment = {};
    environment.stage = test.stage;
    environment.vulkan = test.vulkan;
    const auto messages = ConfigureAutoShader(shader, environment);
    ASSERT_FALSE(compile(&shader, source, "", messages));
    EXPECT_NE(std::string(shader.getInfoLog()).find(test.diagnostic), std::string::npos)
        << shader.getInfoLog();
}

INSTANTIATE_TEST_SUITE_P(
    InvalidPrograms, AutoTypeDeductionErrorTest,
    ::testing::ValuesIn(std::vector<AutoErrorCase>{
        {"VoidFunction", "void nothing() {} void main() { auto value = nothing(); }", "void"},
        {"UndefinedName", "void main() { auto value = missing; }", "undeclared identifier"},
        {"Redefinition", "void main() { auto value = 1; auto value = 2; }", "redefinition"},
        {"ConstWrite", "void main() { const auto value = 1; value = 2; }", "const"},
        {"SourceRemainsConst", "void main() { const int source = 1; auto value = source; source = 2; }", "const"},
        {"SourceArrayRemainsConst", "void main() { const int source[2] = int[2](1, 2); auto value = source; source[0] = 3; }", "const"},
        {"ConstArrayWrite", "void main() { int source[2]; const auto value = source; value[0] = 3; }", "const"},
        {"ArrayBounds", "void main() { int source[10]; auto value = source; value[10] = 1; }", "array index out of range"},
        {"NestedArrayBounds", "void main() { int source[2][3]; auto value = source; value[0][3] = 1; }", "array index out of range"},
        {"TypeRemainsFixed", "void main() { auto value = 1; value = vec3(1.0); }", "cannot convert"},
        {"StructIdentity", "struct A { int x; }; struct B { int x; }; void takeB(B x) {} void main() { A a = A(1); auto value = a; takeB(value); }", "no matching overloaded function"},
        {"MissingInitializer", "void main() { auto value; }", "syntax error"},
        {"BareInitializerList", "void main() { auto value = {1, 2}; }", "syntax error"},
        {"VariableInitializerList", "void main() { int x = 1, y = 2, z = 3; auto value = {x, y, z}; }", "syntax error"},
        {"MixedInitializerList", "void main() { int x = 1; float y = 2.0; vec3 z = vec3(3.0); auto value = {x, y, z}; }", "syntax error"},
        {"EmptyInitializerList", "void main() { auto value = {}; }", "syntax error"},
        {"SingleElementInitializerList", "void main() { auto value = {1}; }", "syntax error"},
        {"NestedInitializerList", "void main() { auto value = {{1, 2}, {3, 4}}; }", "syntax error"},
        {"ConstInitializerList", "void main() { const auto value = {1, 2}; }", "syntax error"},
        {"FunctionInitializerList", "int makeValue() { return 1; } void main() { auto value = {makeValue(), makeValue()}; }", "syntax error"},
        {"TrailingCommaInitializerList", "void main() { auto value = {1, 2,}; }", "syntax error"},
        {"ParameterPlaceholder", "void take(auto value) {} void main() {}", "syntax error"},
        {"ReturnPlaceholder", "auto makeValue() { return 1; } void main() {}", "syntax error"},
        {"SelfReference", "void main() { auto value = value; }", "undeclared identifier"},
        {"ForwardReference", "void main() { auto value = later; int later = 1; }", "undeclared identifier"},
        {"EscapedScope", "void main() { { auto local = 1; } auto value = local; }", "undeclared identifier"},
        {"ForVariableEscapedScope", "void main() { for (auto i = 0; i < 2; ++i) {} auto value = i; }", "undeclared identifier"},
        {"CommaEndsInVoid", "void nothing() {} void main() { auto value = (1, nothing()); }", "void"},
        {"IncompleteLengthMethod", "void main() { int source[3]; auto value = source.length; }", "incomplete method syntax"},
        {"NamedFunctionIsNotValue", "void functionName() {} void main() { auto value = functionName; }", "function"},
        {"OverloadGroupIsNotValue", "int functionName(int x) { return x; } float functionName(float x) { return x; } void main() { auto value = functionName; }", "function"},
        {"MultipleDeclaratorsScalarMismatch", "void main() { auto first = 1, second = 2.0; }", "inconsistent types deduced"},
        {"MultipleDeclaratorsSignednessMismatch", "void main() { auto first = 1, second = 2u; }", "inconsistent types deduced"},
        {"MultipleDeclaratorsVectorSizeMismatch", "void main() { auto first = vec2(1.0), second = vec3(1.0); }", "inconsistent types deduced"},
        {"MultipleDeclaratorsMatrixShapeMismatch", "void main() { auto first = mat2x3(1.0), second = mat3x2(1.0); }", "inconsistent types deduced"},
        {"MultipleDeclaratorsArraySizeMismatch", "void main() { auto first = int[2](1, 2), second = int[3](1, 2, 3); }", "inconsistent types deduced"},
        {"MultipleDeclaratorsArrayRankMismatch", "void main() { int a[2], b[2][2]; auto first = a, second = b; }", "inconsistent types deduced"},
        {"MultipleDeclaratorsStructureMismatch", "struct A { int x; }; struct B { int x; }; void main() { auto first = A(1), second = B(2); }", "inconsistent types deduced"},
        {"MultipleDeclaratorsThirdTypeMismatch", "void main() { auto first = 1, second = 2, third = 3.0; }", "inconsistent types deduced"},
        {"MultipleDeclaratorsGlobalMismatch", "auto first = 1, second = 2.0; void main() {}", "inconsistent types deduced"},
        {"MultipleDeclaratorsMissingInitializer", "void main() { auto first = 1, second; }", "initializer required"},
        {"MultipleDeclaratorsThirdMissingInitializer", "void main() { auto first = 1, second = 2, third; }", "initializer required"},
        {"MultipleDeclaratorsSingleBraceInitializer", "void main() { auto first = 1, second = {2}; }", "brace initializer"},
        {"MultipleDeclaratorsListInitializer", "void main() { auto first = ivec2(1), second = {2, 3}; }", "brace initializer"},
        {"MultipleDeclaratorsNestedBraceInitializer", "void main() { auto first = mat2(1.0), second = {{1.0, 0.0}, {0.0, 1.0}}; }", "brace initializer"},
        {"MultipleDeclaratorsEmptyBraceInitializer", "#extension GL_EXT_null_initializer : require\nvoid main() { auto first = 1, second = {}; }", "brace initializer"},
        {"MultipleDeclaratorsArraySuffix", "void main() { auto first = int[2](1, 2), second[2] = int[2](3, 4); }", "array specifier is not allowed with auto"},
        {"MultipleDeclaratorsSecondSelfReference", "void main() { auto first = 1, second = second; }", "undeclared identifier"},
        {"MultipleDeclaratorsForwardReference", "void main() { auto first = second, second = 1; }", "undeclared identifier"},
        {"MultipleDeclaratorsRedefinition", "void main() { auto value = 1, value = 2; }", "redefinition"},
        {"MultipleDeclaratorsConstThirdWrite", "void main() { const auto first = 1, second = 2, third = 3; third = 4; }", "const"},
        {"MultipleDeclaratorsFunctionName", "int makeValue() { return 1; } void main() { auto first = 1, second = makeValue; }", "function"},
        {"MultipleDeclaratorsLongVectorLengthMismatch", "#extension GL_EXT_long_vector : require\nlayout(local_size_x=1) in;\n"
         "void main() { vector<float, 8> a; vector<float, 16> b; auto first = a, second = b; }",
         "inconsistent types deduced", EShLangCompute, true},
        {"MultipleDeclaratorsTensorLayoutRankMismatch", "#extension GL_NV_cooperative_matrix2 : require\nlayout(local_size_x=1) in;\n"
         "void main() { auto first = createTensorLayoutNV(2), second = createTensorLayoutNV(3); }",
         "inconsistent types deduced", EShLangCompute, true},
        {"MultipleDeclaratorsTensorViewPermutationMismatch", "#extension GL_NV_cooperative_matrix2 : require\nlayout(local_size_x=1) in;\n"
         "void main() { auto first = createTensorViewNV(2, true, 1, 0), second = createTensorViewNV(2, true, 0, 1); }",
         "inconsistent types deduced", EShLangCompute, true},
        {"IfDeclarationUnsupportedByGlsl", "void main() { if (auto flag = true) {} }", "syntax error"},
        {"SuffixArrayUnsupported", "void main() { auto value[3] = int[3](1, 2, 3); }", "syntax error"},
        {"StructMemberPlaceholderUnsupported", "struct Data { auto value; }; void main() {}", "syntax error"},
        {"WriteonlyBufferRead", "layout(std430, binding=0) writeonly buffer Inputs { int source; }; void main() { auto value = source; }", "writeonly"},
        {"GlobalConstNonconstant", "float makeValue() { return 1.0; } const auto value = makeValue(); void main() {}", "global const initializers must be constant"},
    }),
    [](const ::testing::TestParamInfo<AutoErrorCase>& info) { return info.param.name; });

struct AutoExtensionCase {
    const char* name;
    const char* source;
    bool succeeds;
    bool warns = false;
    const char* version = "450";
    const char* diagnostic = "syntax error";
};

void PrintTo(const AutoExtensionCase& test, std::ostream* stream)
{
    *stream << test.name;
}

using AutoTypeDeductionExtensionTest = GlslangTest<::testing::TestWithParam<AutoExtensionCase>>;

// These sources deliberately bypass MakeAutoShader: the extension state itself
// is under test, so no helper may implicitly enable deduction.
TEST_P(AutoTypeDeductionExtensionTest, HonorsExtensionBehavior)
{
    const auto& test = GetParam();
    const std::string source = std::string("#version ") + test.version + "\n" + test.source;
    SCOPED_TRACE(source);
    glslang::TShader shader(EShLangVertex);
    const bool compiled = compile(&shader, source, "", EShMsgDefault);
    const std::string log = shader.getInfoLog();
    EXPECT_EQ(compiled, test.succeeds) << log;
    // An unregistered extension must not make a negative test pass.
    EXPECT_EQ(log.find("extension not supported"), std::string::npos) << log;
    if (!test.succeeds)
        EXPECT_NE(log.find(test.diagnostic), std::string::npos) << log;
    if (test.warns) {
        EXPECT_NE(log.find("WARNING:"), std::string::npos) << log;
        EXPECT_NE(log.find("GL_EXT_type_deduction is being used for auto"), std::string::npos) << log;
    } else {
        EXPECT_EQ(log.find("WARNING:"), std::string::npos) << log;
    }
}

INSTANTIATE_TEST_SUITE_P(
    ExtensionStates, AutoTypeDeductionExtensionTest,
    ::testing::ValuesIn(std::vector<AutoExtensionCase>{
        {"DefaultAllowsIdentifier", "void main() { int auto = 1; auto = 2; }", true},
        {"DisableAllowsIdentifier", "#extension GL_EXT_type_deduction : disable\n"
         "void main() { int auto = 1; auto = 2; }", true},
        {"DefaultRejectsDeduction", "void main() { auto value = 1; }", false, false, "450", "undeclared identifier"},
        {"DisableRejectsDeduction", "#extension GL_EXT_type_deduction : disable\n"
         "void main() { auto value = 1; }", false, false, "450", "undeclared identifier"},
        {"EnableAllowsDeduction", "#extension GL_EXT_type_deduction : enable\n"
         "void main() { auto value = 1; value = 2; }", true},
        {"RequireAllowsDeduction", "#extension GL_EXT_type_deduction : require\n"
         "void main() { auto value = 1; value = 2; }", true},
        {"WarnAllowsDeductionWithWarning", "#extension GL_EXT_type_deduction : warn\n"
         "void main() { auto value = 1; value = 2; }", true, true},
        {"WarnWithoutUseIsSilent", "#extension GL_EXT_type_deduction : warn\n"
         "void main() { int value = 1; }", true},
        {"EnableReservesAuto", "#extension GL_EXT_type_deduction : enable\n"
         "void main() { int auto = 1; }", false},
        {"RequireReservesAuto", "#extension GL_EXT_type_deduction : require\n"
         "void main() { int auto = 1; }", false},
        {"WarnReservesAuto", "#extension GL_EXT_type_deduction : warn\n"
         "void main() { int auto = 1; }", false, true},
        {"DefaultAllowsFunctionName", "int auto(int x) { return x; } void main() { int value = auto(1); }", true},
        {"DefaultAllowsMemberName", "struct Data { int auto; }; void main() { Data value; value.auto = 1; }", true},
        {"DefaultAllowsTypeName", "struct auto { int x; }; void main() { auto value = auto(1); }", true},
        {"DisableAllowsTypeName", "#extension GL_EXT_type_deduction : disable\n"
         "struct auto { int x; }; void main() { auto value = auto(1); }", true},
        {"EnableRejectsTypeName", "#extension GL_EXT_type_deduction : enable\n"
         "struct auto { int x; }; void main() {}", false},
        {"EnableThenDisableRestoresIdentifier", "#extension GL_EXT_type_deduction : enable\n"
         "void helper() { auto value = 1; }\n"
         "#extension GL_EXT_type_deduction : disable\n"
         "void main() { int auto = 2; auto = 3; }", true},
        {"EnableThenDisableRejectsDeduction", "#extension GL_EXT_type_deduction : enable\n"
         "void helper() { auto value = 1; }\n"
         "#extension GL_EXT_type_deduction : disable\n"
         "void main() { auto value = 2; }", false, false, "450", "undeclared identifier"},
        {"DisableThenEnableAllowsDeduction", "#extension GL_EXT_type_deduction : disable\n"
         "void helper() { int auto = 1; }\n"
         "#extension GL_EXT_type_deduction : enable\n"
         "void main() { auto value = 2; }", true},
        {"WarnThenDisableRestoresIdentifier", "#extension GL_EXT_type_deduction : warn\n"
         "#extension GL_EXT_type_deduction : disable\n"
         "void main() { int auto = 1; }", true},
        {"AllDisableRestoresIdentifier", "#extension GL_EXT_type_deduction : require\n"
         "#extension all : disable\nvoid main() { int auto = 1; }", true},
        {"AllDisableRejectsDeduction", "#extension GL_EXT_type_deduction : require\n"
         "#extension all : disable\nvoid main() { auto value = 1; }", false, false, "450", "undeclared identifier"},
        {"AllWarnAllowsDeductionWithWarning", "#extension all : warn\n"
         "void main() { auto value = 1; }", true, true},
        {"EnableAfterAllDisable", "#extension all : disable\n"
         "#extension GL_EXT_type_deduction : enable\nvoid main() { auto value = 1; }", true},
        {"SupportMacroDefinedByDefault", "#ifndef GL_EXT_type_deduction\n#error missing support macro\n#endif\n"
         "#if GL_EXT_type_deduction != 1\n#error invalid support macro\n#endif\nvoid main() {}", true},
        {"SupportMacroDefinedWhenDisabled", "#extension GL_EXT_type_deduction : disable\n"
         "#ifndef GL_EXT_type_deduction\n#error missing support macro\n#endif\nvoid main() {}", true},
        {"SupportMacroCanGuardRequire", "#ifdef GL_EXT_type_deduction\n"
         "#extension GL_EXT_type_deduction : require\n#endif\nvoid main() { auto value = 1; }", true},
        {"EsDefaultAllowsIdentifier", "void main() { int auto = 1; auto = 2; }", true, false, "310 es"},
        {"EsDefaultRejectsDeduction", "void main() { auto value = 1; }", false, false, "310 es", "undeclared identifier"},
        {"EsRequireAllowsDeduction", "#extension GL_EXT_type_deduction : require\n"
         "void main() { auto value = 1; }", true, false, "310 es"},
        {"EsWarnAllowsDeductionWithWarning", "#extension GL_EXT_type_deduction : warn\n"
         "void main() { auto value = 1; }", true, true, "310 es"},
        {"EsSupportMacroCanGuardRequire", "#ifdef GL_EXT_type_deduction\n"
         "#extension GL_EXT_type_deduction : require\n#endif\nvoid main() { auto value = 1; }",
         true, false, "310 es"},
    }),
    [](const ::testing::TestParamInfo<AutoExtensionCase>& info) { return info.param.name; });

using AutoTypeDeductionEdgeTest = GlslangTest<::testing::Test>;

TEST_F(AutoTypeDeductionEdgeTest, ExtensionStateDoesNotLeakBetweenShaders)
{
    // Destroy each shader before compiling the next, as callers often do when
    // compiling many independent sources through one initialized library.
    for (const char* behavior : {"require", "warn"}) {
        {
            glslang::TShader shader(EShLangVertex);
            const std::string source = std::string("#version 450\n#extension GL_EXT_type_deduction : ") +
                                       behavior + "\nvoid main() { auto value = 1; }";
            ASSERT_TRUE(compile(&shader, source, "", EShMsgDefault)) << shader.getInfoLog();
        }
        {
            glslang::TShader shader(EShLangVertex);
            ASSERT_TRUE(compile(&shader, "#version 450\nvoid main() { int auto = 1; auto = 2; }",
                                "", EShMsgDefault)) << shader.getInfoLog();
            EXPECT_EQ(std::string(shader.getInfoLog()).find("WARNING:"), std::string::npos);
        }
        {
            glslang::TShader shader(EShLangVertex);
            ASSERT_FALSE(compile(&shader, "#version 450\nvoid main() { auto value = 1; }",
                                 "", EShMsgDefault));
            EXPECT_NE(std::string(shader.getInfoLog()).find("undeclared identifier"), std::string::npos)
                << shader.getInfoLog();
        }
    }
}

TEST_F(AutoTypeDeductionEdgeTest, CopiesAnonymousStructAcrossMultipleDeclarators)
{
    const std::string source = R"(
        #version 450
        #extension GL_EXT_type_deduction : require
        void main() {
            struct { int count; vec3 points[2]; } source;
            auto deduced = source, second = deduced, third = second;
            deduced.count = 2;
            second.points[1].y = 3.0;
            third.count = 4;
        }
    )";
    glslang::TShader shader(EShLangVertex);
    shader.setDebugInfo(true);
    ASSERT_TRUE(compile(&shader, source, "", EShMsgDefault)) << shader.getInfoLog();
    ASSERT_NE(shader.getIntermediate(), nullptr);
    ASSERT_NE(shader.getIntermediate()->getTreeRoot(), nullptr);
    FindAutoDeclaration original("source");
    shader.getIntermediate()->getTreeRoot()->traverse(&original);
    ASSERT_NE(original.symbol, nullptr);
    for (const char* name : {"deduced", "second", "third"}) {
        SCOPED_TRACE(name);
        FindAutoDeclaration deduced(name);
        shader.getIntermediate()->getTreeRoot()->traverse(&deduced);
        ASSERT_NE(deduced.symbol, nullptr);
        EXPECT_TRUE(original.symbol->getType() == deduced.symbol->getType());
        EXPECT_EQ(deduced.symbol->getQualifier().storage, glslang::EvqTemporary);
    }
}

TEST_F(AutoTypeDeductionEdgeTest, DeclarationListStateDoesNotLeak)
{
    const std::string source = std::string("#version 450\n") + AutoTypeDeductionExtension + R"(
        void main() {
            auto a = 1, b = a + 1;
            auto c = 1.0, d = c + 1.0;
            const auto e = true, f = false;
            // Ordinary declarations still allow mixed initializer types,
            // missing initializers, array suffixes, and brace initializers.
            float g = 1, h = 2u;
            int i, j;
            int k[2], l[3];
            int m[2] = int[2](1, 2), n[3] = {3, 4, 5};
            auto o = vec3(1.0), p = o;
            struct Data { int value; };
            auto q = Data(1), r = q;
        }
    )";
    glslang::TShader shader(EShLangVertex);
    ASSERT_TRUE(compile(&shader, source, "", EShMsgDefault)) << shader.getInfoLog();
}

TEST_F(AutoTypeDeductionEdgeTest, ParameterStorageIsNotInherited)
{
    const char* parameterQualifiers[] = {"in", "const in", "inout"};
    for (const char* qualifier : parameterQualifiers) {
        const std::string source = std::string("#version 450\n") + AutoTypeDeductionExtension +
                                  "void helper(" + qualifier + R"( vec3 source) {
            auto deduced = source;
            deduced.x = 2.0;
        }
        void main() {}
        )";
        SCOPED_TRACE(source);
        glslang::TShader shader(EShLangVertex);
        shader.setDebugInfo(true);
        ASSERT_TRUE(compile(&shader, source, "", EShMsgDefault)) << shader.getInfoLog();
        ASSERT_NE(shader.getIntermediate(), nullptr);
        ASSERT_NE(shader.getIntermediate()->getTreeRoot(), nullptr);
        FindAutoDeclaration declaration;
        shader.getIntermediate()->getTreeRoot()->traverse(&declaration);
        ASSERT_NE(declaration.symbol, nullptr);
        EXPECT_EQ(declaration.symbol->getQualifier().storage, glslang::EvqTemporary);
        EXPECT_EQ(declaration.symbol->getBasicType(), glslang::EbtFloat);
        EXPECT_EQ(declaration.symbol->getVectorSize(), 3);
    }
}

TEST_F(AutoTypeDeductionEdgeTest, EsGlobalInitializerStillMustBeConstant)
{
    for (const char* specifier : {"float", "auto"}) {
        const std::string source = std::string("#version 310 es\nprecision mediump float;\n") +
                                   AutoTypeDeductionExtension +
                                   "uniform float source;\n" + specifier +
                                   " deduced = source;\nvoid main() {}\n";
        SCOPED_TRACE(source);
        glslang::TShader shader(EShLangVertex);
        ASSERT_FALSE(compile(&shader, source, "", EShMsgDefault));
        EXPECT_NE(std::string(shader.getInfoLog()).find("non-constant global initializer"), std::string::npos)
            << shader.getInfoLog();
    }
}

using AutoTypeDeductionSyntaxTest = GlslangTest<::testing::Test>;

// GLSL has target-typed brace initialization. Rejecting braces after auto must
// not disable the existing syntax when a concrete destination type is given.
TEST_F(AutoTypeDeductionSyntaxTest, ExplicitTypesStillAllowBraceInitializers)
{
    const std::string source = R"(
        #version 450
        struct Data { int count; float scale; };
        void main() {
            vec3 vector = {1.0, 2.0, 3.0};
            int values[3] = {1, 2, 3};
            Data data = {1, 2.0};
        }
    )";
    glslang::TShader shader(EShLangVertex);
    ASSERT_TRUE(compile(&shader, source, "", EShMsgDefault)) << shader.getInfoLog();
}

using AutoTypeDeductionBackendTest = GlslangTest<::testing::Test>;

TEST_F(AutoTypeDeductionBackendTest, GeneratesSpirvForTensorLayoutsAndViews)
{
    const auto test = ParameterizedAutoCase("TensorBackend", "", "", "", AutoTensorNVGlobals);
    const std::string source = std::string("#version 460\n") + AutoTypeDeductionExtension + AutoTensorNVGlobals + R"(
        void main() {
            auto initialLayout = createTensorLayoutNV(2);
            auto resizedLayout = setTensorLayoutDimensionNV(initialLayout, 256, 512);
            auto slicedLayout = sliceTensorLayoutNV(resizedLayout, 0, 32, 0, 64);
            tensorLayoutNV<2> explicitLayout = slicedLayout;
            auto initialView = createTensorViewNV(2, true, 1, 0);
            auto resizedView = setTensorViewDimensionsNV(initialView, 16, 32);
            auto stridedView = setTensorViewStrideNV(resizedView, 32, 1);
            tensorViewNV<2, true, 1, 0> explicitView = stridedView;
        }
    )";
    glslang::TShader shader(EShLangCompute);
    const auto messages = ConfigureAutoShader(shader, test);
    shader.setDebugInfo(false);
    ASSERT_TRUE(compile(&shader, source, "", messages)) << shader.getInfoLog();
    glslang::TProgram program;
    program.addShader(&shader);
    ASSERT_TRUE(program.link(messages)) << program.getInfoLog();
    ASSERT_NE(program.getIntermediate(EShLangCompute), nullptr);

    std::vector<unsigned int> spirv;
    spv::SpvBuildLogger logger;
    glslang::SpvOptions options;
    options.disableOptimizer = true;
    options.validate = true;
    glslang::GlslangToSpv(*program.getIntermediate(EShLangCompute), spirv, &logger, &options);
    ASSERT_GE(spirv.size(), 5u);
    EXPECT_EQ(spirv[0], 0x07230203u);
    EXPECT_TRUE(logger.getAllMessages().empty()) << logger.getAllMessages();
}

using AutoTypeDeductionCopyTest = GlslangTest<::testing::Test>;

TEST_F(AutoTypeDeductionCopyTest, CoopMatWithSpirvElementTypeDoesNotCrash)
{
    const auto test = ParameterizedAutoCase(
        "CoopMatSpirvElement",
        "coopmat<spirv_type(id=22, 32), gl_ScopeSubgroup, 8, 8, gl_MatrixUseAccumulator>",
        "source",
        "coopmat<spirv_type(id=22, 32), gl_ScopeSubgroup, 8, 8, gl_MatrixUseAccumulator> source;",
        "#extension GL_KHR_cooperative_matrix : require\n"
        "#extension GL_KHR_memory_scope_semantics : require\n"
        "#extension GL_EXT_spirv_intrinsics : require\nlayout(local_size_x=32) in;");
    glslang::TShader control(EShLangCompute);
    const auto messages = ConfigureAutoShader(control, test);
    ASSERT_TRUE(compile(&control, MakeAutoShader(test, false), "", messages)) << control.getInfoLog();

    // A malformed deep copy can dereference a null spirvType pointer.
    // Isolate compilation so a regression fails this case rather than aborting
    // the entire GoogleTest process. Success, not a crash, is the expectation.
    EXPECT_EXIT({
        glslang::TShader shader(EShLangCompute);
        const auto childMessages = ConfigureAutoShader(shader, test);
        if (!compile(&shader, MakeAutoShader(test, true), "", childMessages)) {
            std::cerr << shader.getInfoLog();
            std::exit(1);
        }
        std::exit(0);
    }, ::testing::ExitedWithCode(0), "");
}

TEST_F(AutoTypeDeductionBackendTest, GeneratesSpirvForArrayAndStructCopies)
{
    const std::string source = R"(
        #version 450
        #extension GL_EXT_type_deduction : require
        layout(local_size_x=1) in;
        layout(std430, binding=0) buffer Output { int result[]; };
        struct Data { int values[3]; };
        Data makeData() { return Data(int[3](1, 2, 3)); }
        void main() {
            const int source[3] = int[3](1, 2, 3);
            auto values = source;
            auto data = makeData();
            values[0] = 4;
            data.values[1] = 5;
            auto sum = values[0] + data.values[1];
            result[0] = sum;
        }
    )";
    glslang::TShader shader(EShLangCompute);
    shader.setEnvInput(glslang::EShSourceGlsl, EShLangCompute, glslang::EShClientVulkan, 450);
    shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_0);
    shader.setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_0);
    const auto messages = static_cast<EShMessages>(EShMsgSpvRules | EShMsgVulkanRules);
    ASSERT_TRUE(compile(&shader, source, "", messages)) << shader.getInfoLog();

    glslang::TProgram program;
    program.addShader(&shader);
    ASSERT_TRUE(program.link(messages)) << program.getInfoLog();
    ASSERT_NE(program.getIntermediate(EShLangCompute), nullptr);
    std::vector<unsigned int> spirv;
    glslang::GlslangToSpv(*program.getIntermediate(EShLangCompute), spirv);
    ASSERT_GE(spirv.size(), 5u);
    EXPECT_EQ(spirv[0], 0x07230203u);
}

} // anonymous namespace
} // namespace glslangtest
