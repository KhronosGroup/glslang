#version 450

precision lowp sampler2D;
precision lowp int;
precision lowp float;

uniform lowp sampler2D s;

layout(location = 0) in lowp vec2 v;

layout(location = 0) out lowp vec4 color;

void main()
{
    color = texture(s, v);
}
