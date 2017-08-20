float4 a[4];

struct {
    float4 m[7];
} s[11];


const float4 C = float4(1,2,3,4);
float4 a1[1] = { float4(1,2,3,4) };
float4 a2[2] = { C, float4(1,2,3,4), };
const float4 c1[1] = { float4(1,2,3,4) };
const float4 c2[2] = { C, float4(1,2,3,4), };

float4 PixelShaderFunction(int i, float4 input[3]) : COLOR0
{
    float4 b[10];
    float4 tmp = C + a1[0] + c1[0] + a2[i] + c2[i];
    return a[1] + a[i] + input[2] + input[i] + b[5] + b[i] + s[i].m[i] + tmp;
}

