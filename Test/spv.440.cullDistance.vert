#version 440
#extension GL_ARB_cull_distance : enable

void main()
{
    gl_CullDistance[1] = 1.0;
    gl_ClipDistance[0] = 2.0;
    gl_Position = vec4(1.0);
}
