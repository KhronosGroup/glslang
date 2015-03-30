/*
** Copyright (c) 2014-2015 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

//
// Author: John Kessenich, LunarG
//

namespace GLSL_STD_450 {

enum Entrypoints {
    Round,
    RoundEven,
    Trunc,
    Abs,
    Sign,
    Floor,
    Ceil,
    Fract,

    Radians,
    Degrees,
    Sin,
    Cos,
    Tan,
    Asin,
    Acos,
    Atan,
    Sinh,
    Cosh,
    Tanh,
    Asinh,
    Acosh,
    Atanh,
    Atan2,

    Pow,
    Exp,
    Log,
    Exp2,
    Log2,
    Sqrt,
    InverseSqrt,

    Determinant,
    MatrixInverse,

    Modf,            // second argument needs the OpVariable, not an OpLoad
    Min,
    Max,
    Clamp,
    Mix,
    Step,
    SmoothStep,

    FloatBitsToInt,
    FloatBitsToUint,
    IntBitsToFloat,
    UintBitsToFloat,

    Fma,
    Frexp,
    Ldexp,

    PackSnorm4x8,
    PackUnorm4x8,
    PackSnorm2x16,
    PackUnorm2x16,
    PackHalf2x16,
    PackDouble2x32,
    UnpackSnorm2x16,
    UnpackUnorm2x16,
    UnpackHalf2x16,
    UnpackSnorm4x8,
    UnpackUnorm4x8,
    UnpackDouble2x32,

    Length,
    Distance,
    Cross,
    Normalize,
    Ftransform,
    FaceForward,
    Reflect,
    Refract,

    UaddCarry,
    UsubBorrow,
    UmulExtended,
    ImulExtended,
    BitfieldExtract,
    BitfieldInsert,
    BitfieldReverse,
    BitCount,
    FindLSB,
    FindMSB,

    InterpolateAtCentroid,
    InterpolateAtSample,
    InterpolateAtOffset,

    Count
};

inline void GetDebugNames(const char** names)
{
    for (int i = 0; i < Count; ++i)
        names[i] = "Unknown";

    names[Round]                   = "round";
    names[RoundEven]               = "roundEven";
    names[Trunc]                   = "trunc";
    names[Abs]                     = "abs";
    names[Sign]                    = "sign";
    names[Floor]                   = "floor";
    names[Ceil]                    = "ceil";
    names[Fract]                   = "fract";
    names[Radians]                 = "radians";
    names[Degrees]                 = "degrees";
    names[Sin]                     = "sin";
    names[Cos]                     = "cos";
    names[Tan]                     = "tan";
    names[Asin]                    = "asin";
    names[Acos]                    = "acos";
    names[Atan]                    = "atan";
    names[Sinh]                    = "sinh";
    names[Cosh]                    = "cosh";
    names[Tanh]                    = "tanh";
    names[Asinh]                   = "asinh";
    names[Acosh]                   = "acosh";
    names[Atanh]                   = "atanh";
    names[Atan2]                   = "atan2";
    names[Pow]                     = "pow";
    names[Exp]                     = "exp";
    names[Log]                     = "log";
    names[Exp2]                    = "exp2";
    names[Log2]                    = "log2";
    names[Sqrt]                    = "sqrt";
    names[InverseSqrt]             = "inverseSqrt";
    names[Determinant]             = "determinant";
    names[MatrixInverse]           = "matrixInverse";
    names[Modf]                    = "modf";
    names[Min]                     = "min";
    names[Max]                     = "max";
    names[Clamp]                   = "clamp";
    names[Mix]                     = "mix";
    names[Step]                    = "step";
    names[SmoothStep]              = "smoothStep";
    names[FloatBitsToInt]          = "floatBitsToInt";
    names[FloatBitsToUint]         = "floatBitsToUint";
    names[IntBitsToFloat]          = "intBitsToFloat";
    names[UintBitsToFloat]         = "uintBitsToFloat";
    names[Fma]                     = "fma";
    names[Frexp]                   = "frexp";
    names[Ldexp]                   = "ldexp";
    names[PackSnorm4x8]            = "packSnorm4x8";
    names[PackUnorm4x8]            = "packUnorm4x8";
    names[PackSnorm2x16]           = "packSnorm2x16";
    names[PackUnorm2x16]           = "packUnorm2x16";
    names[PackHalf2x16]            = "packHalf2x16";
    names[PackDouble2x32]          = "packDouble2x32";
    names[PackHalf2x16]            = "packHalf2x16";
    names[UnpackSnorm2x16]         = "unpackSnorm2x16";
    names[UnpackUnorm2x16]         = "unpackUnorm2x16";
    names[UnpackHalf2x16]          = "unpackHalf2x16";
    names[UnpackSnorm4x8]          = "unpackSnorm4x8";
    names[UnpackUnorm4x8]          = "unpackUnorm4x8";
    names[UnpackDouble2x32]        = "unpackDouble2x32";
    names[UnpackHalf2x16]          = "unpackHalf2x16";
    names[Length]                  = "length";
    names[Distance]                = "distance";
    names[Cross]                   = "cross";
    names[Normalize]               = "normalize";
    names[Ftransform]              = "ftransform";
    names[FaceForward]             = "faceForward";
    names[Reflect]                 = "reflect";
    names[Refract]                 = "refract";
    names[UaddCarry]               = "uaddCarry";
    names[UsubBorrow]              = "usubBorrow";
    names[UmulExtended]            = "umulExtended";
    names[ImulExtended]            = "imulExtended";
    names[BitfieldExtract]         = "bitfieldExtract";
    names[BitfieldInsert]          = "bitfieldInsert";
    names[BitfieldReverse]         = "bitfieldReverse";
    names[BitCount]                = "bitCount";
    names[FindLSB]                 = "findLSB";
    names[FindMSB]                 = "findMSB";
    names[InterpolateAtCentroid]   = "interpolateAtCentroid";
    names[InterpolateAtSample]     = "interpolateAtSample";
    names[InterpolateAtOffset]     = "interpolateAtOffset";
}

}; // end namespace GLSL_STD_450
