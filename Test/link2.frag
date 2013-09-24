#version 130

uniform vec4 uv4;
uniform vec2 glass;

const int ci = 8;

vec4 d = ci * uv4;

in vec3 iv3;
flat in vec4 cup;

vec4 e = ci * d;

ivec2 foo()
{
    return ivec2(2);
}

vec4 f = e * e;
