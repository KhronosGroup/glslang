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
