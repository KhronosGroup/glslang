
float PixelShaderFunction1(float1 inF0, float1 inF1, float1 inF2, uint1 inU0, uint1 inU1)
{
    uint1 out_u1;

    bool r000 = all(inF0);
    float r001 = abs(inF0);
    float r002 = acos(inF0);
    bool r003 = any(inF0);
    float r004 = asin(inF0);
    int r005 = asint(inF0);
    uint r006 = asuint(inF0);
    float r007 = asfloat(inU0);
    // asdouble(inU0, inU1);  // TODO: enable when HLSL parser used for intrinsics
    float r009 = atan(inF0);
    float r010 = atan2(inF0, inF1);
    float r011 = ceil(inF0);
    float r012 = clamp(inF0, inF1, inF2);
    clip(inF0);
    float r014 = cos(inF0);
    float r015 = cosh(inF0);
    uint r016 = countbits(7);
    float r017 = ddx(inF0);
    float r018 = ddx_coarse(inF0);
    float r019 = ddx_fine(inF0);
    float r020 = ddy(inF0);
    float r021 = ddy_coarse(inF0);
    float r022 = ddy_fine(inF0);
    float r023 = degrees(inF0);
    // EvaluateAttributeAtCentroid(inF0);
    // EvaluateAttributeAtSample(inF0, 0);
    // TODO: EvaluateAttributeSnapped(inF0, int2(1,2));
    float r027 = exp(inF0);
    float r028 = exp2(inF0);
    uint r029 = firstbithigh(7);
    uint r030 = firstbitlow(7);
    float r031 = floor(inF0);
    // TODO: fma(inD0, inD1, inD2);
    float r033 = fmod(inF0, inF1);
    float r034 = frac(inF0);
    float r035 = frexp(inF0, inF1);
    float r036 = fwidth(inF0);
    bool r037 = isinf(inF0);
    bool r038 = isnan(inF0);
    float r039 = ldexp(inF0, inF1);
    float r039a = lerp(inF0, inF1, inF2);
    float r040 = log(inF0);
    float1 r041 = log10(inF0);
    float r042 = log2(inF0);
    float r043 = max(inF0, inF1);
    float r044 = min(inF0, inF1);
    float r045 = pow(inF0, inF1);
    float r046 = radians(inF0);
    float1 r047 = rcp(inF0);
    uint r048 = reversebits(2);
    float r049 = round(inF0);
    float r050 = rsqrt(inF0);
    float r051 = saturate(inF0);
    float r052 = sign(inF0);
    float r053 = sin(inF0);
    sincos(inF0, inF1, inF2);
    float r055 = sinh(inF0);
    float r056 = smoothstep(inF0, inF1, inF2);
    float r057 = sqrt(inF0);
    float r058 = step(inF0, inF1);
    float r059 = tan(inF0);
    float r060 = tanh(inF0);
    // TODO: sampler intrinsics, when we can declare the types.
    float r061 = trunc(inF0);

    return 0.0;
}

struct PS_OUTPUT { float4 color : SV_Target0; };

PS_OUTPUT main()
{
    PS_OUTPUT ps_output;
    ps_output.color = 1.0;
    return ps_output;
};
