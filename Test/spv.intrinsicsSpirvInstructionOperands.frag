#version 450
#extension GL_EXT_spirv_intrinsics : enable
#extension GL_EXT_buffer_reference : enable

struct S { float a; float b; };
layout(buffer_reference) buffer B { S s; };
layout(push_constant) uniform PC { B b; };

// Opcodes the SPIR-V post-processing inspects, with operand lists the builder never produces
spirv_instruction(id = 12) float extInstNoOperands();
spirv_instruction(id = 61) float loadNoOperands();
spirv_instruction(id = 61) float loadBool(bool v);
spirv_instruction(id = 61) float loadRef(spirv_by_reference float p);
spirv_instruction(id = 65) float accessChain(spirv_by_reference S p, int i);
spirv_instruction(id = 61) float loadAligned(float p, spirv_literal int access, spirv_literal int align);

layout(location = 0) out float o;

void main()
{
    o = extInstNoOperands() + loadNoOperands() + loadBool(true) + loadRef(b.s.a) +
        loadAligned(accessChain(b.s, 7), 2, 4);
}
