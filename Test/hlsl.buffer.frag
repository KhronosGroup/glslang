cbuffer {
    float4 v1;
};

tbuffer {
    float4 v2;
};

cbuffer cbufName : register(b2) {
    float4 v3;
    int i3 : packoffset(c1.y);
};

tbuffer tbufName : register(b8) {
    float4 v4 : packoffset(c1);
    int i4 : packoffset(c3);
};

float4 PixelShaderFunction(float4 input) : COLOR0
{
    return input + v1 + v2 + v3 + v4;
}
