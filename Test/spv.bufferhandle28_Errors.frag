#version 450

#extension GL_EXT_buffer_reference : enable

layout(buffer_reference, std430) buffer BlockA { float a; };
layout(buffer_reference, std430) buffer BlockB { uint b; };

layout(set = 0, binding = 0) uniform Handles {
    BlockA pa;
    BlockB pb;
} handles;

float f(BlockA p) { return p.a; }

layout(location = 0) out float o;

void main()
{
    // BlockB is not BlockA. While the mangled name carried nothing for a reference
    // type, this matched f(BlockA) and emitted SPIR-V that failed validation.
    o = f(handles.pb);
}
