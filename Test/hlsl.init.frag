float4 a1 = float4(1, 0.5, 0, 1), b1 = float4(2.0, 2.5, 2.1, 2.2);
float a2 = 0.2, b2;
float a3, b3 = 0.3;
float a4, b4 = 0.4, c4;
float a5 = 0.5, b5, c5 = 1.5;

float4 ShaderFunction(float4 input) : COLOR0
{
    float4 a2 = float4(0.2, 0.3, 0.4, 0.5);

    return input * a1;
}
