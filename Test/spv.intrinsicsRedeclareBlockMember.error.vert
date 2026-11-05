#version 450
#extension GL_EXT_spirv_intrinsics : enable
layout(location = 0) out vec4 gl_Position;
out float gl_ClipDistance[4];
invariant gl_PointSize;
precise gl_PointSize;
#pragma STDGL invariant(all)
void main() {}
