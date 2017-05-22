float4 PixelShaderFunction() : COLOR0
{
	uint i = 42;
    if (0 == GlobalOrderedCountIncrement(i))
    {
        return float4(1, 2, 3, 4);
    }
    else
    {
        return float4(4, 3, 2, 1);
    }
}
