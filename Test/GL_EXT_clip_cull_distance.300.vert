#version 300 es
#extension GL_EXT_clip_cull_distance : enable

out highp float gl_ClipDistance[4];

void main()
{
    gl_ClipDistance[3] = 1.0;
    gl_CullDistance[1] = 2.0;  // implicitly sized by the index
    gl_Position = vec4(float(gl_MaxClipDistances), float(gl_MaxCullDistances),
                       float(gl_MaxCombinedClipAndCullDistances), 1.0);
}
