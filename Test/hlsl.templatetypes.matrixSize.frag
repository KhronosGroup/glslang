float4 main() : SV_Target0
{
    matrix<float, 8, 8> m = 1.0;
    return m[0].xyzw;
}
