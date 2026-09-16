#version 440
#extension GL_ARB_cull_distance : enable

out gl_PerVertex {
    vec4 gl_Position;
    float gl_ClipDistance[2];
    float gl_CullDistance[3];
};

void main()
{
    gl_ClipDistance[1] = 1.0;
    gl_CullDistance[2] = float(gl_MaxCullDistances + gl_MaxCombinedClipAndCullDistances);
    gl_Position = vec4(1.0);
}
