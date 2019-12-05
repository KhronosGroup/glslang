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

out float cout;

void main()
{
    vec3 v = vec3(0, 1, 2);
    bar(v, -1);
    int n = bar(v);
    float x = foo(1.f, 2.f);
    float y = foo(n, 2.f);
    cout = x + y;
}

float foo(float a, float b)
{
    return a + b;
}
