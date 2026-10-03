#version 310 es

#extension GL_EXT_descriptor_heap : require

precision highp float;

// Still an error: without layout(descriptor_heap) this is not a heap declaration
uniform highp texture2D notHeap[];

void main()
{
}
