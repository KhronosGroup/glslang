#version 460

#extension GL_EXT_spirv_intrinsics : enable
#extension GL_EXT_spirv_intrinsics_variadic : enable

spirv_instruction(id = 1) void bad(..., int x);

void main()
{
}
