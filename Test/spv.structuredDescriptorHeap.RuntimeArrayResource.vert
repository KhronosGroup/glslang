#version 460

#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_structured_descriptor_heap : require

struct VertexData {
    vec4 position;
    vec4 color;
    vec4 attributes[2];
};

layout(heap_offset = 0) resourceheap ResourceHeap {
    VertexData vertices[];
} heap;

layout(heap_offset = 64) resourceheap PrefixedResourceHeap {
    uvec4 counts;
    vec4 header[2];
    VertexData vertices[];
} prefixedHeap;

layout(heap_offset = 128) resourceheap ScalarResourceHeap {
    int values[];
} scalarHeap;

layout(heap_offset = 320) resourceheap MultidimensionalResourceHeap {
    VertexData vertices[][2];
} multidimensionalHeap;

struct NestedVertexData {
    VertexData vertex;
    vec4 weights[2][3];
};

layout(heap_offset = 384) resourceheap NestedResourceHeap {
    uvec4 counts;
    NestedVertexData vertices[];
} nestedHeap;

layout(location = 0) out vec4 VertColor;

out gl_PerVertex {
    vec4 gl_Position;
};

vec4 readVertexColor(uint index) {
    return heap.vertices[index].color + heap.vertices[index].attributes[1];
}

void main() {
    uint index = uint(gl_VertexIndex);
    int innerIndex = gl_VertexIndex & 1;

    vec4 firstPosition = heap.vertices[0].position;
    gl_Position = heap.vertices[gl_VertexIndex].position;
    VertColor = heap.vertices[index].color + firstPosition;

    VertColor += prefixedHeap.vertices[index + 1u].color;
    VertColor += readVertexColor(index);
    VertColor += heap.vertices[index].attributes[innerIndex];

    VertColor += vec4(float(scalarHeap.values[gl_VertexIndex]));
    VertColor += multidimensionalHeap.vertices[index][innerIndex].color;
    VertColor += nestedHeap.vertices[index].vertex.color;
    VertColor += nestedHeap.vertices[index].weights[innerIndex][index % 3u];

    VertColor += vec4(float(multidimensionalHeap.vertices[index].length()));
    for (int i = 0; i != 2; ++i) {
        VertColor += prefixedHeap.vertices[gl_VertexIndex + i].color;  
    }
}
