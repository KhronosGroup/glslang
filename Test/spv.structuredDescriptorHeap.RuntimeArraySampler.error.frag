#version 460

#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_structured_descriptor_heap : require
#extension GL_EXT_nonuniform_qualifier : require
#extension GL_EXT_uniform_buffer_unsized_array : require

layout(push_constant) uniform PushConstant {
    uint index;
} pc;

layout(heap_offset = 0) samplerheap NonLastSamplerHeap {
    sampler samplers[];
    uint tail;
} nonLastHeap;

layout(location = 0) out vec4 FragColor;

void nonLastSamplerMember() {
    nonLastHeap.samplers[pc.index]; // runtime array is not last
}

void main() {
    FragColor = vec4(0.0);
}
