// Enabling GL_EXT_structured_descriptor_heap only allows opaque members in
// resourceheap / samplerheap blocks, not in ordinary uniform or buffer blocks.
#version 460
#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_structured_descriptor_heap : require

layout(binding = 0) uniform U {
    sampler2D s; // ERROR
    vec4 v;
} u;

layout(location = 0) out vec4 o;

void main()
{
    o = texture(u.s, vec2(0)) + u.v;
}
