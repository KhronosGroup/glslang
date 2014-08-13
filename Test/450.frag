#version 450 core

in float in1;
in vec2 in2;
in vec3 in3;
in vec4 in4;

void main()
{
    vec2 v2 = dFdxFine(in2);
    vec3 v3 = dFdyCoarse(in3);
    vec4 v4 = fwidth(in4);
    v4 = dFdyFine(in4);
    v3 = dFdyFine(in3);
    float f = dFdx(in1) + dFdxFine(in1) + dFdxCoarse(in1);
    v4 = fwidthCoarse(in4) + fwidthFine(in4);

    float cull = gl_CullDistance[2];
    float consts = gl_MaxCullDistances + gl_MaxCombinedClipAndCullDistances;

    if (gl_HelperInvocation)
        ++v4;

    int sum = gl_MaxVertexImageUniforms +
              gl_MaxFragmentImageUniforms +
              gl_MaxComputeImageUniforms +
              gl_MaxCombinedImageUniforms +
              gl_MaxCombinedShaderOutputResources;

    bool b1, b3, b;
    uint uin;
    bvec2 b2 = mix(bvec2(b1), bvec2(b3), bvec2(b));
    uint um = mix(uin, uin, b);
    ivec3 im3 = mix(ivec3(uin), ivec3(uin), bvec3(b));
}
