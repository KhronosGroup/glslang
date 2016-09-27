struct OutParam {
    float2 v;
    int2 i;
};

float4 PixelShaderFunction(float4 input, out float4 out1, out OutParam out2, out OutParam out3) : COLOR0
{
    out1 = input;
    out2.v = 2.0;
    out2.i = 3;
    OutParam local;
    local.v = 12.0;
    local.i = 13;
    out3 = local;

    return out1;
}
