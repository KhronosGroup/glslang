#version 130

uniform vec4 uv4;
uniform vec3 glass;

const int ci = 8;

vec4 a = ci * uv4;

in vec3 iv3;
in vec4 cup;

void main()
{
}

vec4 b = ci * a;

ivec2 foo(mat2 m)
{
    return ivec2(m[0]);
}

vec4 c = b * b;
