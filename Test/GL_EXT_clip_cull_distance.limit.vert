#version 320 es
#extension GL_EXT_clip_cull_distance : enable

out gl_PerVertex {
    highp vec4 gl_Position;
    highp float gl_ClipDistance[9];  // ERROR, larger than gl_MaxClipDistances
    highp float gl_CullDistance[9];  // ERROR, larger than gl_MaxCullDistances
};

void main()
{
    gl_Position = vec4(1.0);
}
