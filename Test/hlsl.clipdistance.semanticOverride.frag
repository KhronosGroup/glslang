// A later semantic must not override the clip distance semantic ID.
float4 main(float2 clip : SV_ClipDistance0 : SV_Target4000) : SV_Target0
{
    return clip.x;
}
