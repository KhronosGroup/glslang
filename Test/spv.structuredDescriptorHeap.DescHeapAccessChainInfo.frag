#version 460

#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_samplerless_texture_functions : require
#extension GL_EXT_structured_descriptor_heap : require

resourceheap ResourceHeap {
    texture2D Texture2D;
    textureBuffer TextureBuffer;
    layout(rgba32f) image2D Image2D;
    layout(r32f) imageBuffer ImageBuffer;
} resourceHeap;

samplerheap SamplerHeap {
    sampler Sampler;
    samplerShadow SamplerShadow;
} samplerHeap;

layout(location = 0) out vec4 FragColor;

void main() {
    FragColor = texture(sampler2D(resourceHeap.Texture2D, samplerHeap.Sampler), vec2(0.0))
              + vec4(texture(sampler2DShadow(resourceHeap.Texture2D, samplerHeap.SamplerShadow), vec3(0.0)))
              + texelFetch(resourceHeap.TextureBuffer, 0)
              + imageLoad(resourceHeap.Image2D, ivec2(0))
              + imageLoad(resourceHeap.ImageBuffer, 0);
}
