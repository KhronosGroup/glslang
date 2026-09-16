#version 320 es

void main()
{
    gl_ClipDistance[0] = 1.0;                        // ERROR, requires GL_EXT_clip_cull_distance
    gl_CullDistance[0] = 2.0;                        // ERROR, requires GL_EXT_clip_cull_distance
    gl_Position = vec4(float(gl_MaxClipDistances));  // ERROR, requires GL_EXT_clip_cull_distance
}
