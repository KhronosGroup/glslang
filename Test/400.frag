#version 400 core

in vec2 c2D;
flat in int i;
out vec4 outp;
uniform sampler2D arrayedSampler[5];
uniform usampler2DRect samp2dr;
uniform isampler2DArray isamp2DA;

void main()
{
    vec4 v;
    v = texture(arrayedSampler[i], c2D);
    outp.x = gl_ClipDistance[1];

    ivec2 offsets[4];
    const ivec2 constOffsets[4] = ivec2[4](ivec2(1,2), ivec2(3,4), ivec2(15,16), ivec2(-2,0));
    uvec4 uv4 = textureGatherOffsets(samp2dr, c2D, offsets, 2);  // ERROR, offsets not constant
    uv4 = textureGatherOffsets(samp2dr, c2D, constOffsets, 2);
    vec4 v4 = textureGather(arrayedSampler[0], c2D);
    ivec4 iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), 3);
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), i);  // ERROR, last argument not const
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), 4);  // ERROR, last argument out of range
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), 1+2);
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(i));

    vec4 c = gl_FragCoord;
}

layout(location = 4) in vec4 vl; // ERROR, not supported

#ifdef GL_ARB_separate_shader_objects
#extension GL_ARB_separate_shader_objects : enable
#endif

layout(location = 6) in vec4 vl2;

layout(location = 3) uniform vec3 uv3;

layout(location = 5) in vec4 gl_Color;      // ERROR, layout
noperspective in float gl_ClipDistance[4];  // ERROR, can't change qualifier

layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;  // ERROR, declared after use

uniform sampler2DRectShadow u2drs;

void foo23()
{
    const ivec2[3] offsets = ivec2[3](ivec2(1,2), ivec2(3,4), ivec2(15,16));

    textureProjGradOffset(u2drs, outp, vec2(0.0), vec2(0.0), ivec2(c2D));     // ERROR, offset not constant
    textureProjGradOffset(u2drs, outp, vec2(0.0), vec2(0.0), offsets[1]);
    textureProjGradOffset(u2drs, outp, vec2(0.0), vec2(0.0), offsets[2]);     // ERROR, offset out of range
    textureProjGradOffset(u2drs, outp, vec2(0.0), vec2(0.0), ivec2(-10, 20)); // ERROR, offset out of range
}

patch in vec4 patchIn;              // ERROR
patch out vec4 patchOut;            // ERROR
