#version 440
#extension GL_ARB_cull_distance : enable

out vec4 color;

void main()
{
    color = vec4(gl_ClipDistance[0], gl_CullDistance[0], 0.0, 1.0);
}
