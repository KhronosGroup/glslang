#version 320 es
#extension GL_EXT_clip_cull_distance : enable

precision mediump float;
out vec4 color;

void main()
{
    color = vec4(gl_ClipDistance[0], gl_CullDistance[0], 0.0, 1.0);
}
