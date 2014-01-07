#version 430 core

layout(location = 3) vec4 v4;  // ERROR

layout(location = 4) uniform vec4 uv4;

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

struct S {
    mat3x2 m[7];  // needs 7*3 locations
    float f;      // needs 1 location
};                // needs 22 locations

layout(location = 10) out S cs[2];     // 10 through 10 + 2 * 22 - 1 = 53
layout(location = 54) out float cf;
layout(location = 53) out float cg; // ERROR, collision at 31

layout(location = 10) in vec4 alias1;
layout(location = 10) in vec4 alias2;  // okay for vertex input on desktop

out float gl_ClipDistance[17];  // ERROR, size too big