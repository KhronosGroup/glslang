float4 PixelShaderFunction() : COLOR0
{
    if (WaveIsHelperLane())
    {
        return float4(1, 2, 3, 4);
    }
    else
    {
        return float4(4, 3, 2, 1);
    }
}
