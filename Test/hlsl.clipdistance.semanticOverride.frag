// A declaration can only have one semantic.
float4 main(float2 clip : SV_ClipDistance0 : SV_Target4000) : SV_Target0
{
    return clip.x;
}
