#version 440

void main()
{
    gl_ClipDistance[0] = 1.0;                        // core in 440
    gl_CullDistance[0] = 2.0;                        // ERROR, requires GL_ARB_cull_distance
    gl_Position = vec4(float(gl_MaxCullDistances));  // ERROR, requires GL_ARB_cull_distance
}
