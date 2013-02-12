#version 120

float lowp;
float mediump;
float highp;

float precision;

in vec4 i;
out vec4 o;

uniform mat4x2 m;

void main()
{
    mat2x3 m23 = mat2x3(m);
}
