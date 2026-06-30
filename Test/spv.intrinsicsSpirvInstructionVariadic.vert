#version 460

#extension GL_EXT_spirv_intrinsics : enable
#extension GL_EXT_spirv_intrinsics_variadic : enable

// Literal tail: each trailing argument is encoded as a literal operand. Here the
// trailing arguments are the literal index list of OpCompositeExtract.
spirv_instruction(id = 81) // OpCompositeExtract
float extractComp(vec4 composite, spirv_literal ...);

// Default (by-id) tail: each trailing argument is encoded by <id>. This is the
// form needed to express a printf-like instruction, shown here with a fictional
// extended instruction set.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 1)
void byId(uint base, ...);

// By-reference tail: each trailing argument is passed as a SPIR-V pointer.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 2)
void byRef(spirv_by_reference ...);

layout(location = 0) in vec4 vec4In;
layout(location = 0) out float floatOut;

void main()
{
    // OpCompositeExtract with literal index 2.
    floatOut = extractComp(vec4In, 2);

    uint base = 1u;
    uint arg = 7u;
    byId(base, arg);  // two trailing arguments, by id
    byId(base);       // zero trailing arguments

    float p = 1.0;
    float q = 2.0;
    byRef(p, q);      // trailing arguments passed by pointer
    byRef(p);         // single trailing argument: no fixed params, one operand
}
