#version 140

varying vec4 v;

in vec4 i;
out vec4 o;

in float gl_ClipDistance[5];

void main()
{
    float clip = gl_ClipDistance[2];
}
#ifdef GL_ES
#error GL_ES is set
#else
#error GL_ES is not set
#endif

in struct S { float f; } s; // ERROR

float patch = 3.1;

layout(location=3) in vec4 vl;  // ERROR

#extension GL_ARB_separate_shader_objects : enable

layout(location=4) in vec4 vl2;
