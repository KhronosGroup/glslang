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
}
