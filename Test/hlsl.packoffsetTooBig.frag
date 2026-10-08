cbuffer cb
{
    float4 m0 : packoffset(c200000000);
};

float4 main() : SV_Target0
{
    return m0;
}
