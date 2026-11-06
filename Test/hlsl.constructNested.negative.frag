// Each nested constructor whose argument list fails to parse must not
// put a token back, or the token stream is backed up past its history.
float4 main() : SV_Target0
{
    return float4(float4(float4(float4(float4(float4(;
}
