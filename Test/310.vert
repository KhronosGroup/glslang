#version 310 es

shared vec4 s;   // ERROR
layout(local_size_x = 2) out;  // ERROR
buffer vec4 v;  // ERROR

layout(location = 2) uniform mat4 x;
layout(location = 3) uniform mat4 y;
layout(location = 2) out mat4 xi;
layout(location = 3) out mat4 yi;  // ERROR, locations conflict with xi

void main()
{
    uvec2 u2;
    u2 = uaddCarry(u2, u2, u2);
    uint u1;
    u1 = usubBorrow(u1, u1, u1);
    uvec4 u4;
    umulExtended(u4, u4, u4, u4);
    ivec4 i4;
    imulExtended(i4, i4, i4, i4);
    int i1;
    i1 = bitfieldExtract(i1, 4, 5);
    uvec3 u3;
    u3 = bitfieldExtract(u3, 4, 5);
    ivec3 i3;
    i3 = bitfieldInsert(i3, i3, 4, 5);
    u1 = bitfieldInsert(u1, u1, 4, 5);
    ivec2 i2;
    i2 = bitfieldReverse(i2);
    u4 = bitfieldReverse(u4);
    i1 = bitCount(i1);
    i3 = bitCount(u3);
    i2 = findLSB(i2);
    i4 = findLSB(u4);
    i1 = findMSB(i1);
    i2 = findMSB(u2);

    vec3 v3;
    v3 = frexp(v3, i3);
    vec2 v2;
    v2 = ldexp(v2, i2);

    mediump vec4 v4;
    u1 = packUnorm4x8(v4);
    u1 = packSnorm4x8(v4);
    v4 = unpackUnorm4x8(u1);
    v4 = unpackSnorm4x8(u1);
}

precision highp sampler2DMS;
precision highp isampler2DMS;
precision highp usampler2DMS;

uniform sampler2DMS s2dms;
uniform isampler2DMS is2dms;
uniform usampler2DMS us2dms;
uniform usampler2DMSArray us2dmsa;   // ERROR

void foo()
{
    ivec2 v2;
    v2 = textureSize(s2dms);
    v2 = textureSize(us2dms);
    vec4 v4 = texelFetch(s2dms, v2, 2);
    ivec4 iv4 = texelFetch(is2dms, v2, 2);
    textureSamples(s2dms);   // ERROR


}

out bool outb;         // ERROR
out sampler2D outo;    // ERROR
out float outa[4];
out float outaa[4][2]; // ERROR
struct S { float f; };
out S outs;
out S[4] outasa;       // ERROR
out S outsa[4];        // ERROR
struct SA { float f[4]; };
out SA outSA;          // ERROR
struct SS { float f; S s; };
out SS outSS;          // ERROR
