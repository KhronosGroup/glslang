#version 130

lowp vec3 a;
mediump float b;
highp int c;

precision highp float;

in vec4 i;
out vec4 o;

flat in float fflat;
smooth in float fsmooth;
noperspective in float fnop;

void main()
{
    float clip = gl_ClipDistance[3];
}

uniform samplerCube sampC;

void foo()
{
    vec4 s = textureGather(sampC, vec3(0.2));
}

#extension GL_ARB_texture_gather : enable

void bar()
{
    vec4 s = textureGather(sampC, vec3(0.2));
}

flat in vec3 gl_Color;     // ERROR, type
in vec4 gl_Color;
flat in vec4 gl_Color;
flat in vec4 gl_Color[2];  // ERROR, array 
vec4 gl_Color;             // ERROR, storage

#extension GL_ARB_texture_gather : warn

void bar2()
{
    vec4 s = textureGather(sampC, vec3(0.2));
}
