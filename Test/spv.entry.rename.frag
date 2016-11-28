
struct PS_OUTPUT
{
    float4 Color : SV_Target0;
};

PS_OUTPUT main()
{
    PS_OUTPUT psout;
    psout.Color = 0;
    return psout;
}
