#version 460

#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_structured_descriptor_heap : require

layout(push_constant) uniform PushConstant {
    vec2 texCoord;
    uint textureIdx;
    uint samplerIdx;
} pc;

layout(heap_offset = 0) resourceheap ResourceHeap {
    texture2D textures[];
} textures;

layout(heap_offset = 0) samplerheap SamplerHeap {
    sampler samplers[];
} samplers;

layout(heap_offset = 64) samplerheap PrefixedSamplerHeap {
    uint count;
    sampler firstSampler;
    sampler samplers[];
} prefixedSamplers;

struct SamplerRecord {
    sampler value;
    sampler pair[2];
};

layout(heap_offset = 128) samplerheap StructuredSamplerHeap {
    SamplerRecord records[];
} structuredSamplers;

struct TextureRecord {
    texture2D value;
    texture2D pair[2];
};

layout(heap_offset = 192) resourceheap StructuredTextureHeap {
    TextureRecord records[];
} structuredTextures;

layout(heap_offset = 256) samplerheap MultidimensionalSamplerHeap {
    SamplerRecord records[][2];
} multidimensionalSamplers;

layout(heap_offset = 320) resourceheap MultidimensionalTextureHeap {
    TextureRecord records[][2];
} multidimensionalTextures;

struct SamplerData {
    vec4 color;
    vec4 weights[2];
};

layout(heap_offset = 384) samplerheap SamplerDataHeap {
    uvec4 counts;
    SamplerData records[];
} samplerData;

layout(location = 0) out vec4 FragColor;

void main() {
    uint textureIndex = pc.textureIdx;
    uint samplerIndex = pc.samplerIdx;
    uint innerIndex   = samplerIndex & 1u;

    vec4 first = texture(sampler2D(textures.textures[0], samplers.samplers[0]), pc.texCoord);

    FragColor = texture(sampler2D(textures.textures[pc.textureIdx],
                                  samplers.samplers[pc.samplerIdx]),
                        pc.texCoord) + first;
    FragColor += texture(sampler2D(textures.textures[textureIndex + 1u],
                                   prefixedSamplers.samplers[samplerIndex]),
                         pc.texCoord);
    FragColor += texture(sampler2D(structuredTextures.records[textureIndex].value,
                                   structuredSamplers.records[samplerIndex].value),
                         pc.texCoord);
    FragColor += texture(sampler2D(structuredTextures.records[textureIndex].pair[innerIndex],
                                   structuredSamplers.records[samplerIndex].pair[innerIndex]),
                         pc.texCoord);
    FragColor += texture(sampler2D(multidimensionalTextures.records[textureIndex][innerIndex].value,
                                   multidimensionalSamplers.records[samplerIndex][innerIndex].value),
                         pc.texCoord);

    FragColor += samplerData.records[samplerIndex].color;
    FragColor *= samplerData.records[samplerIndex].weights[innerIndex];

    FragColor += vec4(float(multidimensionalSamplers.records[samplerIndex].length()));
    for (int i = 0; i != 2; ++i) {
        FragColor += texture(sampler2D(textures.textures[textureIndex],
                                       samplers.samplers[int(samplerIndex) + i]),
                             pc.texCoord);
    }
}
