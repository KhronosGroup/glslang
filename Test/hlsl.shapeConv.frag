float4 PixelShaderFunction(float4 input, float f) : COLOR0
{
    float4 v;
    v = 1;
    v = 2.0;
    v = f;
    float3 u;
    u = float(1);
    u = float(2.0);
    u = float(f);

    return input;
}
