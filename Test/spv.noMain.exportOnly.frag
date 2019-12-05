#version 460 core

float foo(float, float);

void bar(inout vec3 v, int n)
{
    v.x += n;
}

int bar(vec3 v)
{
    return int(v.x + v.y + v.z);
}

float foo(int n, float s)
{
    return s * float(n);
}

float foo(float a, float b)
{
    return a + b;
}
