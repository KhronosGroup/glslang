#version 460 core

float foo(float, float);

void bar(inout vec3 v, int);
int bar(vec3);

float foo(int, float);

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

float foo(float a, float b);
