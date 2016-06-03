float VertexShaderFunction(float inF0, float inF1, float inF2, int inI0)
{
    // AllMemoryBarrier();              // invalid in fragment stage  TODO: parser currently crashes on empty arg list
    // AllMemoryBarrierWithGroupSync(); // invalid in fragment stage  TODO: parser currently crashes on empty arg list
    asdouble(inF0, inF1);                     // expected error: only integer inputs
    CheckAccessFullyMapped(3.0);              // expected error: only valid on integers
    CheckAccessFullyMapped(3);                // expected error: only valid in pixel & compute stages
    clip(inF0);                               // expected error: only valid in pixel & compute stages
    countbits(inF0);                          // expected error: only integer inputs
    cross(inF0, inF1);                        // expected error: only on float3 inputs
    D3DCOLORtoUBYTE4(inF0);                   // expected error: only on float4 inputs
    // DeviceMemoryBarrier();                    // TODO: expected error: only valid in pixel & compute stages
    // DeviceMemoryBarrierWithGroupSync();       // TODO: expected error: only valid in compute stage
    ddx(inF0);                                // expected error: only valid in pixel & compute stages
    ddx_coarse(inF0);                         // expected error: only valid in pixel & compute stages
    ddx_fine(inF0);                           // expected error: only valid in pixel & compute stages
    ddy(inF0);                                // expected error: only valid in pixel & compute stages
    ddy_coarse(inF0);                         // expected error: only valid in pixel & compute stages
    ddy_fine(inF0);                           // expected error: only valid in pixel & compute stages
    determinant(inF0);                        // expected error: only valid on mats
    EvaluateAttributeAtCentroid(inF0);        // expected error: only valid in pixel stage
    EvaluateAttributeAtSample(inF0, 2);       // expected error: only valid in pixel stage
    EvaluateAttributeSnapped(inF0, int2(2));  // expected error: only valid in pixel stage
    f16tof32(inF0);                           // expected error: only integer inputs
    firstbithigh(inF0);                       // expected error: only integer inputs
    firstbitlow(inF0);                        // expected error: only integer inputs
    fma(inF0, inF1, inF2);                    // expected error: only double inputs
    // InterlockedAdd(inI0, inI0, 3);            // expected error: last parameter is out TODO: accepted even though marked as out in proto generator
    // InterlockedAnd(inI0, inI0, 3);            // expected error: last parameter is out TODO: accepted even though marked as out i    // InterlockedMax(inI0, inI0, 3);            // expected error: last parameter is out TODO: accepted even though marked as out in proto generator
    // InterlockedMin(inI0, inI0, 3);            // expected error: last parameter is out TODO: accepted even though marked as out in proto generator
    // InterlockedOor(inI0, inI0, 3);            // expected error: last parameter is out TODO: accepted even though marked as out in proto generator
    // InterlockedXor(inI0, inI0, 3);            // expected error: last parameter is out TODO: accepted even though marked as out in proto generator
    // GroupMemoryBarrier();               // TODO: expected error: only valid in compute stage
    // GroupMemoryBarrierWithGroupSync();  // TODO: expected error: only valid in compute stage
    length(inF0);                             // expect error: invalid on scalars
    msad4(inF0, float2(0), float4(0));        // expected error: only integer inputs
    normalize(inF0);                          // expect error: invalid on scalars
    reflect(inF0, inF1);                      // expect error: invalid on scalars
    refract(inF0, inF1, inF2);                // expect error: invalid on scalars
    refract(float2(0), float2(0), float2(0)); // expected error: last parameter only scalar
    reversebits(inF0);                        // expected error: only integer inputs
    transpose(inF0);                          // expect error: only valid on mats

    // TODO: texture intrinsics, when we can declare samplers.

    return 0.0;
}

float1 VertexShaderFunction(float1 inF0, float1 inF1, float1 inF2, int1 inI0)
{
    // TODO: ... add when float1 prototypes are generated

    GetRenderTargetSamplePosition(inF0); // expected error: only integer inputs

    return 0.0;
}

float2 VertexShaderFunction(float2 inF0, float2 inF1, float2 inF2, int2 inI0)
{
    asdouble(inF0, inF1);         // expected error: only integer inputs
    CheckAccessFullyMapped(inF0); // expect error: only valid on scalars
    countbits(inF0);              // expected error: only integer inputs
    cross(inF0, inF1);            // expected error: only on float3 inputs
    D3DCOLORtoUBYTE4(inF0);       // expected error: only on float4 inputs
    ddx(inF0);                                // only valid in pixel & compute stages
    ddx_coarse(inF0);                         // only valid in pixel & compute stages
    ddx_fine(inF0);                           // only valid in pixel & compute stages
    ddy(inF0);                                // only valid in pixel & compute stages
    ddy_coarse(inF0);                         // only valid in pixel & compute stages
    ddy_fine(inF0);                           // only valid in pixel & compute stages
    determinant(inF0);            // expect error: only valid on mats
    EvaluateAttributeAtCentroid(inF0);        // expected error: only valid in pixel stage
    EvaluateAttributeAtSample(inF0, 2);       // expected error: only valid in pixel stage
    EvaluateAttributeSnapped(inF0, int2(2));  // expected error: only valid in pixel stage
    f16tof32(inF0);               // expected error: only integer inputs
    firstbithigh(inF0);           // expected error: only integer inputs
    firstbitlow(inF0);            // expected error: only integer inputs
    fma(inF0, inF1, inF2);        // expected error: only double inputs
    noise(inF0);                  // expected error: only valid in pixel stage
    reversebits(inF0);            // expected error: only integer inputs
    transpose(inF0);              // expect error: only valid on mats

    // TODO: texture intrinsics, when we can declare samplers.

    return float2(1,2);
}

float3 VertexShaderFunction(float3 inF0, float3 inF1, float3 inF2, int3 inI0)
{
    CheckAccessFullyMapped(inF0);  // expect error: only valid on scalars
    countbits(inF0);            // expected error: only integer inputs
    ddx(inF0);                                // only valid in pixel & compute stages
    ddx_coarse(inF0);                         // only valid in pixel & compute stages
    ddx_fine(inF0);                           // only valid in pixel & compute stages
    ddy(inF0);                                // only valid in pixel & compute stages
    ddy_coarse(inF0);                         // only valid in pixel & compute stages
    ddy_fine(inF0);                           // only valid in pixel & compute stages
    D3DCOLORtoUBYTE4(inF0);     // expected error: only on float4 inputs
    determinant(inF0);          // expect error: only valid on mats
    EvaluateAttributeAtCentroid(inF0);        // expected error: only valid in pixel stage
    EvaluateAttributeAtSample(inF0, 2);       // expected error: only valid in pixel stage
    EvaluateAttributeSnapped(inF0, int2(2));  // expected error: only valid in pixel stage
    f16tof32(inF0);             // expected error: only integer inputs
    firstbithigh(inF0);         // expected error: only integer inputs
    firstbitlow(inF0);          // expected error: only integer inputs
    fma(inF0, inF1, inF2);      // expected error: only double inputs
    noise(inF0);                  // expected error: only valid in pixel stage
    reversebits(inF0);          // expected error: only integer inputs
    transpose(inF0);            // expect error: only valid on mats

    // TODO: texture intrinsics, when we can declare samplers.

    return float3(1,2,3);
}

float4 VertexShaderFunction(float4 inF0, float4 inF1, float4 inF2, int4 inI0)
{
    CheckAccessFullyMapped(inF0);  // expect error: only valid on scalars
    countbits(inF0);            // expected error: only integer inputs
    cross(inF0, inF1);          // expected error: only on float3 inputs
    determinant(inF0);          // expect error: only valid on mats
    ddx(inF0);                                // only valid in pixel & compute stages
    ddx_coarse(inF0);                         // only valid in pixel & compute stages
    ddx_fine(inF0);                           // only valid in pixel & compute stages
    ddy(inF0);                                // only valid in pixel & compute stages
    ddy_coarse(inF0);                         // only valid in pixel & compute stages
    ddy_fine(inF0);                           // only valid in pixel & compute stages
    EvaluateAttributeAtCentroid(inF0);        // expected error: only valid in pixel stage
    EvaluateAttributeAtSample(inF0, 2);       // expected error: only valid in pixel stage
    EvaluateAttributeSnapped(inF0, int2(2));  // expected error: only valid in pixel stage
    f16tof32(inF0);             // expected error: only integer inputs
    firstbithigh(inF0);         // expected error: only integer inputs
    firstbitlow(inF0);          // expected error: only integer inputs
    fma(inF0, inF1, inF2);      // expected error: only double inputs
    noise(inF0);                  // expected error: only valid in pixel stage
    reversebits(inF0);          // expected error: only integer inputs
    transpose(inF0);            // expect error: only valid on mats

    // TODO: texture intrinsics, when we can declare samplers.

    return float4(1,2,3,4);
}

// TODO: FXC doesn't accept this with (), but glslang doesn't accept it without.
#define MATFNS() \
    countbits(inF0);                         \
    cross(inF0, inF1);                       \
    D3DCOLORtoUBYTE4(inF0);                  \
    ddx(inF0);                               \
    ddx_coarse(inF0);                        \
    ddx_fine(inF0);                          \
    ddy(inF0);                               \
    ddy_coarse(inF0);                        \
    ddy_fine(inF0);                          \
    EvaluateAttributeAtCentroid(inF0);       \
    EvaluateAttributeAtSample(inF0, 2);      \
    EvaluateAttributeSnapped(inF0, int2(2)); \
    f16tof32(inF0);                          \
    firstbithigh(inF0);                      \
    firstbitlow(inF0);                       \
    fma(inF0, inF1, inF2);                   \
    noise(inF0);                             \
    reversebits(inF0);                       \
    length(inF0);                            \
    noise(inF0);                             \
    normalize(inF0);                         \
    reflect(inF0, inF1);                     \
    refract(inF0, inF1, 1.0);                \
    reversebits(inF0);                       \
    

// TODO: turn on non-square matrix tests when protos are available.

float2x2 VertexShaderFunction(float2x2 inF0, float2x2 inF1, float2x2 inF2)
{
    // TODO: FXC doesn't accept this with (), but glslang doesn't accept it without.
    MATFNS()

    return float2x2(2,2,2,2);
}

float3x3 VertexShaderFunction(float3x3 inF0, float3x3 inF1, float3x3 inF2)
{
    // TODO: FXC doesn't accept this with (), but glslang doesn't accept it without.
    MATFNS()

    return float3x3(3,3,3,3,3,3,3,3,3);
}

float4x4 VertexShaderFunction(float4x4 inF0, float4x4 inF1, float4x4 inF2)
{
    // TODO: FXC doesn't accept this with (), but glslang doesn't accept it without.
    MATFNS()

    return float4x4(4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4);
}
