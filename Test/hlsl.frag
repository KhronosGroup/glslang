float4x4 World;
float4x4 View;
float4x4 Projection;

float4 AmbientColor = float4(1, 1, 1, 1);
float AmbientIntensity = 0.1;

//float4 PixelShaderFunction(VertexShaderOutput input) : COLOR0
//{
//    return AmbientColor * AmbientIntensity;
//}
