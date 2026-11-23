#version 460

#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_structured_descriptor_heap : require

struct VertexData {
    vec4 position;
};

layout(heap_offset = 0) resourceheap NonLastResourceHeap {
    VertexData vertices[];
    uint tail;
} nonLastHeap;

void nonLastStructureMember() {
    nonLastHeap.vertices[gl_VertexIndex]; // runtime array is not last
}

void main() {
    gl_Position = vec4(0.0);
}
