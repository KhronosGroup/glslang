#version 450

#extension GL_NV_viewport_array2 : require

layout(vertices = 3) out;

void main()
{
    // Error: Vulkan does not allow Layer or ViewportIndex in tessellation control shaders
    gl_out[gl_InvocationID].gl_Layer = 2;
}
