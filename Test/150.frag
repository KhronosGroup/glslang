#version 150 core

in vec4 gl_FragCoord;
layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;  // ERROR
layout(pixel_center_integer) in vec4 gl_FragCoord;  // ERROR
layout(origin_upper_left) in vec4 foo;  // ERROR
layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;

void main()
{
    vec4 c = gl_FragCoord;
}

layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;  // ERROR, declared after use

in struct S { float f; } s;

float patch = 3.1;