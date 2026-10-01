float4x4 m;

float3 main() : SV_Target
{
    // Matrix swizzle is unimplemented.  Code generation still has to leave a value of the
    // swizzle's own type behind, or the store into the entry point's output ends up taking
    // one of the swizzle indices and the module fails validation.
    return m._m03_m13_m23;
}
