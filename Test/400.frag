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
    uvec4 uv4 = textureGatherOffsets(samp2dr, c2D, offsets, 2);
    vec4 v4 = textureGather(arrayedSampler[0], c2D);
    ivec4 iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), 3);
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), i);  // ERROR, last argument not const
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), 4);  // ERROR, last argument out of range
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), 1+2);
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(i));
}

layout(location = 4) in vec4 vl; // ERROR, not supported

#ifdef GL_ARB_separate_shader_objects
#extension GL_ARB_separate_shader_objects : enable
#endif

layout(location = 4) in vec4 vl2;

layout(location = 3) uniform vec3 uv3;
