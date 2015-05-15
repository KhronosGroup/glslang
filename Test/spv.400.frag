#version 400 core

in vec2 c2D;
flat in int i;
out vec4 outp;
out ivec4 ioutp;
out uvec4 uoutp;
uniform sampler2D arrayedSampler[5];
uniform usampler2DRect samp2dr;
uniform isampler2DArray isamp2DA;
uniform sampler2DRectShadow u2drs;

#extension GL_ARB_separate_shader_objects : enable

layout(location = 6) in vec4 vl2;

void foo23()
{
    const ivec2[3] offsets = ivec2[3](ivec2(1,2), ivec2(3,4), ivec2(15,16));

    outp.x += textureProjGradOffset(u2drs, outp, vec2(0.0), vec2(0.0), offsets[1]);
}

void main()
{
    vec4 v;
    v = texture(arrayedSampler[i], c2D);
    outp.x = gl_ClipDistance[1];
    outp.yzw = v.yzw;

    ivec2 offsets[4];
    const ivec2 constOffsets[4] = ivec2[4](ivec2(1,2), ivec2(3,4), ivec2(15,16), ivec2(-2,0));
    uoutp = textureGatherOffsets(samp2dr, c2D, constOffsets, 2);
    outp += textureGather(arrayedSampler[0], c2D);
    ioutp = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), 3);
    ioutp += textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), 1+2);
    ioutp += textureGatherOffset(isamp2DA, vec3(0.1), ivec2(i));

    outp += gl_FragCoord + vl2;
    foo23();
}

