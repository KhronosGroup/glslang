void foo(float f)
{
	if (f < 1.0)
		discard;
}

float4 PixelShaderFunction(float4 input) : COLOR0
{
    foo(input.z);
	if (input.x)
		discard;
	float f = input.x;
	discard;
}
