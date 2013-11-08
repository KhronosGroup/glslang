#version 430 core

layout(location = 3) vec4 v4;  // ERROR

layout(location = 3) uniform vec4 uv4;

layout(location = 2) in   inb1 { vec4 v; } b1;  // ERROR
layout(location = 2) out outb1 { vec4 v; } b2;  // ERROR

out gl_PerVertex {
    float gl_ClipDistance[];
};

void foo()
{
    gl_ClipDistance[2] = 3.7;
}

struct sp {
    highp float f;
    in float g;             // ERROR
    uniform float h;        // ERROR
    invariant float i;      // ERROR
    volatile float j;       // ERROR
    layout(row_major) mat3 m3; // ERROR
};

void foo3(invariant vec4 v4,                 // ERROR
          volatile vec3 v3,
          layout(location = 3) vec2 v2,      // ERROR
          centroid vec3 cv3)                 // ERROR
{
}