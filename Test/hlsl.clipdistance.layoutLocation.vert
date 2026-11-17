// A layout qualifier can't follow a semantic.
float4 main(out float2 clip : SV_ClipDistance0 : layout(location = 4000)) : SV_Position
{
    clip = 0.5;
    return 1.0;
}
