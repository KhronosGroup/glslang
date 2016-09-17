struct InParam {
    float2 v;
    float4 fragCoord : SV_POSITION;
    int2 i2;
};

float4 PixelShaderFunction(InParam i) : COLOR0
{
    InParam local;
    local = i;

    return local.fragCoord;
}
