struct S0
{
    int x;
    int y;
    SamplerState ss;
};

struct S1
{
    float b;
    SamplerState samplerState;
    S0 s0;
    int a;
};

struct S2
{
    int a1;
    int a2;
    int a3;
    int a4;
    int a5;
    S1 resources;
};

float4 main(float4 vpos : VPOS) : COLOR0
{
    S1 s1;
    S2 s2;
    s2.resources = s1;
    return float4(0,0,0,0);
}
