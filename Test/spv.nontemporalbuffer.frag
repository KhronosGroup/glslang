#version 460

#pragma use_vulkan_memory_model

#extension GL_EXT_nontemporal_keyword: require

layout(binding=0) uniform nontemporal UNIFORMS {
    ivec2 u_uv;
};
layout(binding=1, rgba8) uniform readonly image2D u_image;

layout(location=0) out vec4 out_color;

void main() {
    out_color = imageLoad(u_image, u_uv);
}
