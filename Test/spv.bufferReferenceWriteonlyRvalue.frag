#version 450

#extension GL_EXT_buffer_reference : enable
#extension GL_EXT_buffer_reference2 : enable

layout(buffer_reference, std430) writeonly buffer Ref {
    int a;
};

layout(set = 0, binding = 0, std430) buffer Root {
    Ref r;
} root;

void main()
{
    // Reading a member of a writeonly buffer_reference through pointer
    // arithmetic bottoms out on a non-symbol base, so the l-value base
    // is not a TIntermSymbol.
    int v = (root.r + 1).a;
}
