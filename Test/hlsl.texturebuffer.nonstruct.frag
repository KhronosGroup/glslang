TextureBuffer<float4> tb : register(t0);

float4 main() : SV_Target
{
    return tb;
}
