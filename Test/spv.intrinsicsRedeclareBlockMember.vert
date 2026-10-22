#version 450

#extension GL_EXT_spirv_intrinsics: enable

// With GL_EXT_spirv_intrinsics, gl_PointSize here is a user variable. The
// gl_PerVertex members before it can still be used and requalified.
layout(location = 0) out float gl_PointSize;
invariant gl_Position;

void main()
{
    gl_Position = vec4(1.0);
    gl_PointSize = 1.0;
}
