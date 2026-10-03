#version 450

// Without GL_NV_viewport_array2, gl_out's gl_ViewportIndex and gl_Layer stay out of the SPIR-V
layout(vertices = 3) out;

void main()
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
