#version 460

#extension GL_EXT_spirv_intrinsics : enable
#extension GL_EXT_spirv_intrinsics_variadic : enable

spirv_instruction(id = 81)
float extractComp(vec4 composite, spirv_literal ...);

// The ellipsis is only valid on a 'spirv_instruction' declaration.
void userFunc(int n, ...);

// Two variadic overloads that tie on their (identical) leading parameter.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 1) void amb(uint x, ...);
spirv_instruction(set = "Fictional.TestExtInstSet", id = 2) void amb(uint x, uint y, ...);

// ERROR: the same signature redeclared with a different qualifier on the tail.
// The tail qualifier is not part of the signature, so it must not change.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 3) void requal(float x, ...);
spirv_instruction(set = "Fictional.TestExtInstSet", id = 3) void requal(float x, spirv_literal ...);

spirv_instruction(set = "Fictional.TestExtInstSet", id = 4) void rawTail(...);

layout(location = 0) in vec4 vec4In;
layout(location = 1) in int dyn;

void main()
{
    // ERROR: a 'spirv_literal' trailing argument must be a front-end constant.
    float f = extractComp(vec4In, dyn);

    // ERROR: ambiguous between amb(uint, ...) and amb(uint, uint, ...); the
    // trailing tail does not disambiguate.
    uint a = 1u;
    uint b = 2u;
    amb(a, b);

    // ERROR: string literals are not valid trailing variadic SPIR-V operands.
    rawTail("oops");
}
