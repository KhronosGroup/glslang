struct VI {
    float4 m[2];
    uint2 coord;
};

float4 main(float4 d, VI vi, float4 e) : SV_POSITION
{
    return vi.m[1] + vi.m[0] + float4(vi.coord.x) + d + e;
}