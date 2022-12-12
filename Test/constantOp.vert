#version 460 core
#extension GL_EXT_shader_explicit_arithmetic_types : enable

void main(){
    vec2 v2Base             = vec2(1.0, 0.0);
    uint uiBase             = 1;
    float64_t f64Base       = 0.5;
    highp float hpFpBase    = 0.5;
    highp int hpIntBase     = 1;
    highp int hpUintBase    = 1;
    double doubleBase       = 0.5;
    int64_t i64Base         = 1;
    uint64_t ui64Base       = 1;
    mat3 matBase            = mat3(1.0, 0.0, 0.0,
                                   0.0, 1.0, 0.0,
                                   0.0, 1.0, 1.0);
    mat3 inverseMat = inverse(matBase);             // EOpMatrixInverse
    mat3 transpMat  = transpose(matBase);           // EOpTranspose
    uint pkSnorm216 = packSnorm2x16(v2Base);        // EOpPackSnorm2x16
    uint pkUnorm216 = packUnorm2x16(v2Base);        // EOpPackUnorm2x16
    uint pkHalf216  = packHalf2x16(v2Base);         // EOpPackHalf2x16
    vec2 upkSnorm216 = unpackSnorm2x16(uiBase);     // EOpUnpackSnorm2x16
    vec2 upkUnorm216 = unpackUnorm2x16(uiBase);     // EOpUnpackUnorm2x16
    vec2 upkHalf216  = unpackHalf2x16(uiBase);      // EOpUnpackHalf2x16
    float dtmnant    = determinant(matBase);        // EOpDeterminant
    float64_t sh     = sinh(f64Base);               // EOpSinh
    float64_t ch     = cosh(f64Base);               // EOpCosh
    float64_t th     = tanh(f64Base);               // EOpTanh
    float64_t ash    = asinh(f64Base);              // EOpAsinh
    float64_t ach    = acosh(f64Base);              // EOpAcosh
    float64_t ath    = atanh(f64Base);              // EOpAtanh
    int f2i          = floatBitsToInt(hpFpBase);    // EOpFloatBitsToInt
    uint f2ui        = floatBitsToUint(hpFpBase);   // EOpFloatBitsToUint
    float i2f        = intBitsToFloat(hpIntBase);   // EOpIntBitsToFloat
    float ui2f       = uintBitsToFloat(hpUintBase); // EOpUintBitsToFloat
    int64_t d2i64    = doubleBitsToInt64(doubleBase);   // EOpDoubleBitsToInt64
    uint64_t d2ui64  = doubleBitsToUint64(doubleBase);  // EOpDoubleBitsToUint64
    double i642d     = int64BitsToDouble(i64Base);      // EOpInt64BitsToDouble
    double ui642d    = uint64BitsToDouble(ui64Base);    // EOpUint64BitsToDouble
}