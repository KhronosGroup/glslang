#version 460 core

float foo(in float, out int, inout vec3);

out float cout;

void main()
{
    int x;
    vec3 v = vec3(0.f, 1.f, 2.f);
    float r = foo(1.f, x, v);
}
