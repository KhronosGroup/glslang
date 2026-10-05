struct PSInput
{
    float4 pos : SV_POSITION;
};

float adjust(float x)
{
    return saturate(x);
}

float4 main(PSInput input) : SV_Target
{
    float f = input.pos.x;

    return float4(adjust((f + 1.0)++), 0.0, 0.0, 1.0);
}
