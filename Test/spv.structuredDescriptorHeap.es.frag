#version 310 es

#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_structured_descriptor_heap : require

precision highp float;

resourceheap ResourceHeap {
    uint count;
    highp texture2D textures[];
} resources;

samplerheap SamplerHeap {
    highp samplerShadow shadowSampler;
    highp sampler samplers[];
} samplers;

layout(location = 0) in vec2 uvs;
layout(location = 0) out vec4 fragColor;

void main()
{
    fragColor = texture(sampler2D(resources.textures[2], samplers.samplers[1]), uvs);
    fragColor.x += float(resources.count);
}
