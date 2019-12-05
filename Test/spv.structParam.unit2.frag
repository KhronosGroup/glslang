#version 460 core

struct MyStruct {
    vec3 v;
    int i;
};

int foo(inout MyStruct);

out float cout;

void main()
{
    MyStruct s;
    s.i = 2;
    int r = foo(s);
}
