#version 320 es
#extension GL_EXT_clip_cull_distance : enable

layout(vertices = 3) out;

// gl_PointSize is dropped on purpose: the remaining members must keep their own
// extension requirements after the redeclaration.
out gl_PerVertex {
    highp vec4 gl_Position;
    highp float gl_ClipDistance[4];
    highp float gl_CullDistance[2];
} gl_out[];

void main()
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    gl_out[gl_InvocationID].gl_ClipDistance[1] = gl_in[gl_InvocationID].gl_ClipDistance[2];
    gl_out[gl_InvocationID].gl_CullDistance[0] = gl_in[gl_InvocationID].gl_CullDistance[1];
    gl_TessLevelOuter[0] = 1.0;
}
