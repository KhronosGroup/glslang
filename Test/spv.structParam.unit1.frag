#version 460 core

struct MyStruct {
    vec3 v;
    int i;
};

int foo(inout MyStruct s)
{
    s.v = vec3(0.f, 1.f, 2.f);
    return s.i;
}
