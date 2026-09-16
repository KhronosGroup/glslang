#version 320 es
#extension GL_EXT_clip_cull_distance : enable

out gl_PerVertex {
    highp vec4 gl_Position;
    highp float gl_ClipDistance[4];
    highp float gl_CullDistance[2];
};

void main()
{
    gl_ClipDistance[3] = 1.0;
    gl_CullDistance[1] = 2.0;
    gl_Position = vec4(1.0);
}
