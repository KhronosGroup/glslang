float4 g_const : register(c200000000);

float4 main() : SV_Target0
{
    return g_const;
}
