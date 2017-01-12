void ShaderFunction(float inf) : COLOR0
{
    float3x4 m;

    m._34  = 1.0; // AST should have a normal component select
    m._m23 = 2.0; // same code

    m._11_12_13_14 = float4(3.0);      // AST should have normal column selection (first row)
    m._m10_m11_m12_m13 = float4(3.0);  // AST should have normal column selection (second row)
}
