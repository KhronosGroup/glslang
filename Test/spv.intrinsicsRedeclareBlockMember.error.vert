#version 450

#extension GL_EXT_spirv_intrinsics: enable

// With GL_EXT_spirv_intrinsics, gl_Position here is a user variable. It takes
// that name at global scope, so gl_PerVertex can no longer be copied there:
// redeclaring or requalifying another of its members is an error, and
// invariant(all) can only warn about them.
layout(location = 0) out vec4 gl_Position;
out float gl_ClipDistance[4];
invariant gl_PointSize;
#pragma STDGL invariant(all)

void main()
{
    gl_Position = vec4(1.0);
}
