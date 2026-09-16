#version 320 es
#extension GL_EXT_clip_cull_distance : enable

layout(triangles) in;

void main()
{
    gl_Position = gl_in[0].gl_Position;
    gl_ClipDistance[2] = gl_in[1].gl_ClipDistance[2];
    gl_CullDistance[0] = gl_in[2].gl_CullDistance[0];
}
