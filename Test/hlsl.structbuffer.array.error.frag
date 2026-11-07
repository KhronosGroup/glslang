StructuredBuffer<float4> sbuf[2];

float4 main() : SV_Target0
{
    return sbuf[1];
}
