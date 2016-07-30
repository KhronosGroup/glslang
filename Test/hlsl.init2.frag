
void Test1()
{
    struct mystruct { float2 a; };
    mystruct test1 = {
        { 1, 2, },          // test trailing commas
    };

    mystruct test2 = {
        { { 1, 2, } },      // test unneeded levels
    };

    float test3 = { 1 } ;   // test scalar initialization
}

struct PS_OUTPUT { float4 color : SV_Target0; };

PS_OUTPUT main()
{
    PS_OUTPUT ps_output;
    ps_output.color = 1.0;
    return ps_output;
}
