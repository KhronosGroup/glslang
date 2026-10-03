#version 310 es

#extension GL_EXT_descriptor_heap : require
#extension GL_EXT_structured_descriptor_heap : require

precision highp float;

// Still an error: only the last member of a heap block may be unsized
resourceheap ResourceHeap {
    highp texture2D notLast[];
    uint count;
} resources;

void main()
{
}
