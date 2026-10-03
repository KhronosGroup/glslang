#version 450

#extension GL_NV_viewport_array2 : require

layout(vertices = 3) out;

void main()
{
    gl_out[gl_InvocationID].gl_ViewportIndex = 1;
    gl_out[gl_InvocationID].gl_Layer = 2;
    gl_out[gl_InvocationID].gl_ViewportMask[0] = 4;
}
