#version 460

#extension GL_EXT_spirv_intrinsics : enable
#extension GL_EXT_spirv_intrinsics_variadic : enable

spirv_instruction(id = 81)
float extractComp(vec4 composite, spirv_literal . . .);

layout(location = 0) in vec4 vec4In;
layout(location = 0) out float floatOut;

void main()
{
    floatOut = extractComp(vec4In, 2);
}
