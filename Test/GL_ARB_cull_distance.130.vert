#version 130
#extension GL_ARB_cull_distance : enable

out float gl_CullDistance[2];

void main()
{
    gl_ClipDistance[0] = 1.0;
    gl_CullDistance[1] = 2.0;
    gl_Position = vec4(1.0);
}
