float4 PixelShaderFunction() : COLOR0
{
    if (0 == WaveGetOrderedIndex())
    {
        return float4(1, 2, 3, 4);
    }
    else
    {
        return float4(4, 3, 2, 1);
    }
}
