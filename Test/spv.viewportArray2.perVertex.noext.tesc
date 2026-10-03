#version 450

layout(vertices = 3) out;

void main()
{
    // Errors: these need GL_NV_viewport_array2
    gl_out[gl_InvocationID].gl_ViewportIndex = 1;
    gl_out[gl_InvocationID].gl_Layer = 2;
}
