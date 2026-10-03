#version 310 es

#extension GL_EXT_descriptor_heap : require

precision highp float;

layout(descriptor_heap) uniform highp sampler heapSampler[];
layout(descriptor_heap) uniform highp texture2D heapTexture2D[];
layout(descriptor_heap) buffer StorageBuffer {
    vec4 a;
} heapStorageBuffer[];
layout(descriptor_heap) uniform UniformBuffer {
    vec4 colorOffset;
} heapUniformBuffer[];

layout(location = 0) in vec2 uvs;

layout(location = 0) out vec4 fragColor;

void main()
{
    fragColor = texture(sampler2D(heapTexture2D[27], heapSampler[0]), uvs);
    fragColor += heapUniformBuffer[3].colorOffset;
    heapStorageBuffer[1].a = fragColor;
}
