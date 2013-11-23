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

    uvec3 uv3;
    bvec3 b3;
    b3 = lessThan(uv3, uv3);
    b3 = equal(uv3, uv3);
    const bvec2 bl1 = greaterThanEqual(uvec2(2, 3), uvec2(3,3));
    const bvec2 bl2 = equal(uvec2(2, 3), uvec2(3,3));
    const bvec2 bl3 = equal(bl1, bl2);  // yes, equal
    int a1[int(bl3.x)];
    int a2[int(bl3.y)];
    a1[0];  // size 1
    a2[0];  // size 1
    const bvec4 bl4 = notEqual(greaterThan(uvec4(1,2,3,4), uvec4(0,2,0,6)), lessThanEqual(uvec4(7,8,9,10), uvec4(6, 8, 0, 11)));  // compare (t,f,t,f) with (f,t,f,t)
    int a3[int(bl4.x)+int(bl4.y)+int(bl4.z)+int(bl4.w)];
    a3[3];  // size 4
    b3 != b3;
    b3 < b3;                   // ERROR
    uv3 > uv3;                 // ERROR
    uvec2(2, 3) >= uvec2(3,3); // ERROR
    int(bl4) <= int(bl4);      // true
    int(bl4.x) > int(bl4.y);   // false
}

#extension GL_ARB_texture_gather : enable
#extension GL_ARB_texture_rectangle : enable

uniform sampler2D samp2D;
uniform sampler2DShadow samp2DS;
uniform sampler2DRect samp2DR;
uniform sampler2DArray samp2DA;

void bar23()
{
    vec4 s;
    s = textureGatherOffset(sampC, vec3(0.3), ivec2(1));        // ERROR
    s = textureGatherOffset(samp2DR, vec2(0.3), ivec2(1));      // ERROR
    s = textureGatherOffset(samp2D, vec2(0.3), ivec2(1));
    s = textureGatherOffset(samp2DA, vec3(0.3), ivec2(1));
    s = textureGatherOffset(samp2DS, vec2(0.3), 1.3, ivec2(1)); // ERROR
    s = textureGatherOffset(samp2D, vec2(0.3), ivec2(1), 2);    // ERROR
}

#extension GL_ARB_gpu_shader5 : enable

void bar234()
{
    vec4 s;
    s = textureGatherOffset(samp2D, vec2(0.3), ivec2(1));
    s = textureGatherOffset(samp2DA, vec3(0.3), ivec2(1));
    s = textureGatherOffset(samp2DR, vec2(0.3), ivec2(1));
    s = textureGatherOffset(samp2DS, vec2(0.3), 1.3, ivec2(1));
    s = textureGatherOffset(samp2D, vec2(0.3), ivec2(1), 2);
}
