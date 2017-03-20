struct Test
{
    float4 memVar;
    float4 memFun(float4 a) : SV_Position
    {
        return 2 * a;
    }
    int memFun(int a) : SV_Position
    {
        return 2 + a;
    }
    int i;
};

float4 main() : SV_Target0
{
   Test test;
   float4 f4 = float4(1.0,1.0,1.0,1.0);
   f4 += test.memFun(float4(5.0f,5.0f,5.0f,5.0f));
   f4 += test.memFun(7);
   return f4;
}
