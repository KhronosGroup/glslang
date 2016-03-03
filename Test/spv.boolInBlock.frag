#version 450

layout(binding = 0, std140) uniform Uniform
{
    bvec4 b4;
};

layout(binding = 1, std430) buffer Buffer
{
    bvec2 b2;
};

void foo(bvec4 paramb4, out bvec2 paramb2)
{
    bool b1 = paramb4.z;
    paramb2 = bvec2(b1);
}

void main()
{
    b2 = bvec2(0.0);
    if (b4.z)
        b2 = bvec2(b4.x);
    if (b2.x)
        foo(b4, b2);
}