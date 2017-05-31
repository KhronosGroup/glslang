#version 450

struct S {
    int a;
};

uniform ubuf {
    S s;
};

layout(location = 0) in vec4 inv;
layout(location = 0) out vec4 outv;

void foo(S s)
{
    outv = s.a * inv;
}

void main()
{
    foo(s);
}