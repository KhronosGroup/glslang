// Entry point parameters may be left unnamed.
float4 main(float4 pos : SV_Position, float2 : TEXCOORD0, uniform float4, out float4 : SV_Target1) : SV_Target0
{
    return pos;
}
