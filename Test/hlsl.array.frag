float4 a[4];

struct {
    float4 m[7];
} s[11];

static float4 C = float4(1,2,3,4);

float4 PixelShaderFunction(int i : sem1, float4 input[3] : sem2) : SV_TARGET0
{
    float4 b[10] = { C, C, C, C, C, C, C, C, C, C };
    return a[1] + a[i] + input[2] + input[i] + b[5] + b[i] + s[i].m[i];
}
