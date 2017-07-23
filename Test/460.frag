#version 460 core

struct S {
    float f;
    vec4 v;
};

in S s;

void main()
{
    interpolateAtCentroid(s.v);
}
