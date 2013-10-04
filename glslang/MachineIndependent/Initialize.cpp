//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
//Copyright (C) 2012-2013 LunarG, Inc.
//
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
//FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
//COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//POSSIBILITY OF SUCH DAMAGE.
//

//
// Create strings that declare built-in definitions, add built-ins programmatically 
// that cannot be expressed in the strings, and establish mappings between
// built-in functions and operators.
//
// Where to put a built-in:
//   TBuiltIns::initialize(version,profile)       context-independent textual built-ins; add them to the right string
//   TBuiltIns::initialize(resources,...)         context-dependent textual built-ins; add them to the right string
//   IdentifyBuiltIns(...,symbolTable)            context-independent programmatic additions/mappings to the symbol table
//   IdentifyBuiltIns(...,symbolTable, resources) context-dependent programmatic additions/mappings to the symbol table
//

#include "../Include/intermediate.h"
#include "Initialize.h"

namespace glslang {

const int FirstProfileVersion = 150;
const bool ForwardCompatibility = false;

TBuiltIns::TBuiltIns()
{
    // Set up textual representations for making all the permutations
    // of texturing/imaging functions.
    prefixes[EbtFloat] =  "";
    prefixes[EbtInt]   = "i";
    prefixes[EbtUint]  = "u";
    postfixes[2] = "2";
    postfixes[3] = "3";
    postfixes[4] = "4";

    // Map from symbolic class of texturing dimension to numeric dimensions.
    dimMap[Esd1D] = 1;
    dimMap[Esd2D] = 2;
    dimMap[EsdRect] = 2;
    dimMap[Esd3D] = 3;
    dimMap[EsdCube] = 3;
    dimMap[EsdBuffer] = 1;
}

TBuiltIns::~TBuiltIns()
{
}

//
// Add all context-independent built-in functions and variables that are present
// for the given version and profile.  Share common ones across stages, otherwise
// make stage-specific entries.
//
// Most built-ins variables can be added as simple text strings.  Some need to
// be added programmatically, which is done later in IdentifyBuiltIns() below.
//
void TBuiltIns::initialize(int version, EProfile profile)
{
    {
        //============================================================================
        //
        // Prototypes for built-in functions seen by both vertex and fragment shaders.
        //
        //============================================================================

        TString& s = commonBuiltins;

        //
        // Angle and Trigonometric Functions.
        //
        s.append("float radians(float degrees);");
        s.append("vec2  radians(vec2  degrees);");
        s.append("vec3  radians(vec3  degrees);");
        s.append("vec4  radians(vec4  degrees);");

        s.append("float degrees(float radians);");
        s.append("vec2  degrees(vec2  radians);");
        s.append("vec3  degrees(vec3  radians);");
        s.append("vec4  degrees(vec4  radians);");

        s.append("float sin(float angle);");
        s.append("vec2  sin(vec2  angle);");
        s.append("vec3  sin(vec3  angle);");
        s.append("vec4  sin(vec4  angle);");

        s.append("float cos(float angle);");
        s.append("vec2  cos(vec2  angle);");
        s.append("vec3  cos(vec3  angle);");
        s.append("vec4  cos(vec4  angle);");

        s.append("float tan(float angle);");
        s.append("vec2  tan(vec2  angle);");
        s.append("vec3  tan(vec3  angle);");
        s.append("vec4  tan(vec4  angle);");

        s.append("float asin(float x);");
        s.append("vec2  asin(vec2  x);");
        s.append("vec3  asin(vec3  x);");
        s.append("vec4  asin(vec4  x);");

        s.append("float acos(float x);");
        s.append("vec2  acos(vec2  x);");
        s.append("vec3  acos(vec3  x);");
        s.append("vec4  acos(vec4  x);");

        s.append("float atan(float y, float x);");
        s.append("vec2  atan(vec2  y, vec2  x);");
        s.append("vec3  atan(vec3  y, vec3  x);");
        s.append("vec4  atan(vec4  y, vec4  x);");

        s.append("float atan(float y_over_x);");
        s.append("vec2  atan(vec2  y_over_x);");
        s.append("vec3  atan(vec3  y_over_x);");
        s.append("vec4  atan(vec4  y_over_x);");

        s.append("float sinh(float angle);");
        s.append("vec2  sinh(vec2  angle);");
        s.append("vec3  sinh(vec3  angle);");
        s.append("vec4  sinh(vec4  angle);");

        s.append("float cosh(float angle);");
        s.append("vec2  cosh(vec2  angle);");
        s.append("vec3  cosh(vec3  angle);");
        s.append("vec4  cosh(vec4  angle);");

        s.append("float tanh(float angle);");
        s.append("vec2  tanh(vec2  angle);");
        s.append("vec3  tanh(vec3  angle);");
        s.append("vec4  tanh(vec4  angle);");

        s.append("float asinh(float x);");
        s.append("vec2  asinh(vec2  x);");
        s.append("vec3  asinh(vec3  x);");
        s.append("vec4  asinh(vec4  x);");

        s.append("float acosh(float x);");
        s.append("vec2  acosh(vec2  x);");
        s.append("vec3  acosh(vec3  x);");
        s.append("vec4  acosh(vec4  x);");

        s.append("float atanh(float y_over_x);");
        s.append("vec2  atanh(vec2  y_over_x);");
        s.append("vec3  atanh(vec3  y_over_x);");
        s.append("vec4  atanh(vec4  y_over_x);");

        //
        // Exponential Functions.
        //
        s.append("float pow(float x, float y);");
        s.append("vec2  pow(vec2  x, vec2  y);");
        s.append("vec3  pow(vec3  x, vec3  y);");
        s.append("vec4  pow(vec4  x, vec4  y);");

        s.append("float exp(float x);");
        s.append("vec2  exp(vec2  x);");
        s.append("vec3  exp(vec3  x);");
        s.append("vec4  exp(vec4  x);");

        s.append("float log(float x);");
        s.append("vec2  log(vec2  x);");
        s.append("vec3  log(vec3  x);");
        s.append("vec4  log(vec4  x);");

        s.append("float exp2(float x);");
        s.append("vec2  exp2(vec2  x);");
        s.append("vec3  exp2(vec3  x);");
        s.append("vec4  exp2(vec4  x);");

        s.append("float log2(float x);");
        s.append("vec2  log2(vec2  x);");
        s.append("vec3  log2(vec3  x);");
        s.append("vec4  log2(vec4  x);");

        s.append("float sqrt(float x);");
        s.append("vec2  sqrt(vec2  x);");
        s.append("vec3  sqrt(vec3  x);");
        s.append("vec4  sqrt(vec4  x);");

        s.append("float inversesqrt(float x);");
        s.append("vec2  inversesqrt(vec2  x);");
        s.append("vec3  inversesqrt(vec3  x);");
        s.append("vec4  inversesqrt(vec4  x);");

        //
        // Common Functions.
        //
        s.append("float abs(float x);");
        s.append("vec2  abs(vec2  x);");
        s.append("vec3  abs(vec3  x);");
        s.append("vec4  abs(vec4  x);");

        if (version >= 130) {
            s.append("  int abs(  int x);");
            s.append("ivec2 abs(ivec2 x);");
            s.append("ivec3 abs(ivec3 x);");
            s.append("ivec4 abs(ivec4 x);");
        }


        s.append("float sign(float x);");
        s.append("vec2  sign(vec2  x);");
        s.append("vec3  sign(vec3  x);");
        s.append("vec4  sign(vec4  x);");

        if (version >= 130) {
            s.append("  int sign(  int x);");
            s.append("ivec2 sign(ivec2 x);");
            s.append("ivec3 sign(ivec3 x);");
            s.append("ivec4 sign(ivec4 x);");
        }

        s.append("float floor(float x);");
        s.append("vec2  floor(vec2  x);");
        s.append("vec3  floor(vec3  x);");
        s.append("vec4  floor(vec4  x);");

        if (version >= 130) {
            s.append("float trunc(float x);");
            s.append("vec2  trunc(vec2  x);");
            s.append("vec3  trunc(vec3  x);");
            s.append("vec4  trunc(vec4  x);");

            s.append("float round(float x);");
            s.append("vec2  round(vec2  x);");
            s.append("vec3  round(vec3  x);");
            s.append("vec4  round(vec4  x);");

            s.append("float roundEven(float x);");
            s.append("vec2  roundEven(vec2  x);");
            s.append("vec3  roundEven(vec3  x);");
            s.append("vec4  roundEven(vec4  x);");
        }

        s.append("float ceil(float x);");
        s.append("vec2  ceil(vec2  x);");
        s.append("vec3  ceil(vec3  x);");
        s.append("vec4  ceil(vec4  x);");

        s.append("float fract(float x);");
        s.append("vec2  fract(vec2  x);");
        s.append("vec3  fract(vec3  x);");
        s.append("vec4  fract(vec4  x);");

        s.append("float mod(float x, float y);");
        s.append("vec2  mod(vec2  x, float y);");
        s.append("vec3  mod(vec3  x, float y);");
        s.append("vec4  mod(vec4  x, float y);");
        s.append("vec2  mod(vec2  x, vec2  y);");
        s.append("vec3  mod(vec3  x, vec3  y);");
        s.append("vec4  mod(vec4  x, vec4  y);");

        if (version >= 130) {
            s.append("float modf(float, out float);");
            s.append("vec2  modf(vec2,  out vec2 );");
            s.append("vec3  modf(vec3,  out vec3 );");
            s.append("vec4  modf(vec4,  out vec4 );");
        }

        s.append("float min(float x, float y);");
        s.append("vec2  min(vec2  x, float y);");
        s.append("vec3  min(vec3  x, float y);");
        s.append("vec4  min(vec4  x, float y);");
        s.append("vec2  min(vec2  x, vec2  y);");
        s.append("vec3  min(vec3  x, vec3  y);");
        s.append("vec4  min(vec4  x, vec4  y);");

        if (version >= 130) {
            s.append("  int min(int    x, int y);");
            s.append("ivec2 min(ivec2  x, int y);");
            s.append("ivec3 min(ivec3  x, int y);");
            s.append("ivec4 min(ivec4  x, int y);");
            s.append("ivec2 min(ivec2  x, ivec2  y);");
            s.append("ivec3 min(ivec3  x, ivec3  y);");
            s.append("ivec4 min(ivec4  x, ivec4  y);");

            s.append(" uint min(uint   x, uint y);");
            s.append("uvec2 min(uvec2  x, uint y);");
            s.append("uvec3 min(uvec3  x, uint y);");
            s.append("uvec4 min(uvec4  x, uint y);");
            s.append("uvec2 min(uvec2  x, uvec2  y);");
            s.append("uvec3 min(uvec3  x, uvec3  y);");
            s.append("uvec4 min(uvec4  x, uvec4  y);");
        }

        s.append("float max(float x, float y);");
        s.append("vec2  max(vec2  x, float y);");
        s.append("vec3  max(vec3  x, float y);");
        s.append("vec4  max(vec4  x, float y);");
        s.append("vec2  max(vec2  x, vec2  y);");
        s.append("vec3  max(vec3  x, vec3  y);");
        s.append("vec4  max(vec4  x, vec4  y);");

        if (version >= 130) {
            s.append("  int max(int    x, int y);");
            s.append("ivec2 max(ivec2  x, int y);");
            s.append("ivec3 max(ivec3  x, int y);");
            s.append("ivec4 max(ivec4  x, int y);");
            s.append("ivec2 max(ivec2  x, ivec2  y);");
            s.append("ivec3 max(ivec3  x, ivec3  y);");
            s.append("ivec4 max(ivec4  x, ivec4  y);");

            s.append(" uint max(uint   x, uint y);");
            s.append("uvec2 max(uvec2  x, uint y);");
            s.append("uvec3 max(uvec3  x, uint y);");
            s.append("uvec4 max(uvec4  x, uint y);");
            s.append("uvec2 max(uvec2  x, uvec2  y);");
            s.append("uvec3 max(uvec3  x, uvec3  y);");
            s.append("uvec4 max(uvec4  x, uvec4  y);");
        }

        s.append("float clamp(float x, float minVal, float maxVal);");
        s.append("vec2  clamp(vec2  x, float minVal, float maxVal);");
        s.append("vec3  clamp(vec3  x, float minVal, float maxVal);");
        s.append("vec4  clamp(vec4  x, float minVal, float maxVal);");
        s.append("vec2  clamp(vec2  x, vec2  minVal, vec2  maxVal);");
        s.append("vec3  clamp(vec3  x, vec3  minVal, vec3  maxVal);");
        s.append("vec4  clamp(vec4  x, vec4  minVal, vec4  maxVal);");

        if (version >= 130) {
            s.append("int    clamp(int x, int minVal, int maxVal);");
            s.append("ivec2  clamp(ivec2  x, int minVal, int maxVal);");
            s.append("ivec3  clamp(ivec3  x, int minVal, int maxVal);");
            s.append("ivec4  clamp(ivec4  x, int minVal, int maxVal);");
            s.append("ivec2  clamp(ivec2  x, ivec2  minVal, ivec2  maxVal);");
            s.append("ivec3  clamp(ivec3  x, ivec3  minVal, ivec3  maxVal);");
            s.append("ivec4  clamp(ivec4  x, ivec4  minVal, ivec4  maxVal);");

            s.append("uint   clamp(uint x, uint minVal, uint maxVal);");
            s.append("uvec2  clamp(uvec2  x, uint minVal, uint maxVal);");
            s.append("uvec3  clamp(uvec3  x, uint minVal, uint maxVal);");
            s.append("uvec4  clamp(uvec4  x, uint minVal, uint maxVal);");
            s.append("uvec2  clamp(uvec2  x, uvec2  minVal, uvec2  maxVal);");
            s.append("uvec3  clamp(uvec3  x, uvec3  minVal, uvec3  maxVal);");
            s.append("uvec4  clamp(uvec4  x, uvec4  minVal, uvec4  maxVal);");
        }

        s.append("float mix(float x, float y, float a);");
        s.append("vec2  mix(vec2  x, vec2  y, float a);");
        s.append("vec3  mix(vec3  x, vec3  y, float a);");
        s.append("vec4  mix(vec4  x, vec4  y, float a);");
        s.append("vec2  mix(vec2  x, vec2  y, vec2  a);");
        s.append("vec3  mix(vec3  x, vec3  y, vec3  a);");
        s.append("vec4  mix(vec4  x, vec4  y, vec4  a);");

        if (version >= 130) {
            s.append("float mix(float x, float y, bool  a);");
            s.append("vec2  mix(vec2  x, vec2  y, bvec2 a);");
            s.append("vec3  mix(vec3  x, vec3  y, bvec3 a);");
            s.append("vec4  mix(vec4  x, vec4  y, bvec4 a);");
        }

        s.append("float step(float edge, float x);");
        s.append("vec2  step(vec2  edge, vec2  x);");
        s.append("vec3  step(vec3  edge, vec3  x);");
        s.append("vec4  step(vec4  edge, vec4  x);");
        s.append("vec2  step(float edge, vec2  x);");
        s.append("vec3  step(float edge, vec3  x);");
        s.append("vec4  step(float edge, vec4  x);");

        s.append("float smoothstep(float edge0, float edge1, float x);");
        s.append("vec2  smoothstep(vec2  edge0, vec2  edge1, vec2  x);");
        s.append("vec3  smoothstep(vec3  edge0, vec3  edge1, vec3  x);");
        s.append("vec4  smoothstep(vec4  edge0, vec4  edge1, vec4  x);");
        s.append("vec2  smoothstep(float edge0, float edge1, vec2  x);");
        s.append("vec3  smoothstep(float edge0, float edge1, vec3  x);");
        s.append("vec4  smoothstep(float edge0, float edge1, vec4  x);");

        if (version >= 130) {
            s.append("bool  isnan(float x);");
            s.append("bvec2 isnan(vec2  x);");
            s.append("bvec3 isnan(vec3  x);");
            s.append("bvec4 isnan(vec4  x);");

            s.append("bool  isinf(float x);");
            s.append("bvec2 isinf(vec2  x);");
            s.append("bvec3 isinf(vec3  x);");
            s.append("bvec4 isinf(vec4  x);");
        }

        if ((profile == EEsProfile && version >= 300) ||
            (profile != EEsProfile && version >= 330)) {
            s.append("int   floatBitsToInt(float value);");
            s.append("ivec2 floatBitsToInt(vec2  value);");
            s.append("ivec3 floatBitsToInt(vec3  value);");
            s.append("ivec4 floatBitsToInt(vec4  value);");

            s.append("uint  floatBitsToUint(float value);");
            s.append("uvec2 floatBitsToUint(vec2  value);");
            s.append("uvec3 floatBitsToUint(vec3  value);");
            s.append("uvec4 floatBitsToUint(vec4  value);");

            s.append("float intBitsToFloat(int   value);");
            s.append("vec2  intBitsToFloat(ivec2 value);");
            s.append("vec3  intBitsToFloat(ivec3 value);");
            s.append("vec4  intBitsToFloat(ivec4 value);");

            s.append("float uintBitsToFloat(uint  value);");
            s.append("vec2  uintBitsToFloat(uvec2 value);");
            s.append("vec3  uintBitsToFloat(uvec3 value);");
            s.append("vec4  uintBitsToFloat(uvec4 value);");
        }

        if ((profile == EEsProfile && version >= 300) ||
            (profile != EEsProfile && version >= 400)) {
            s.append(  "highp uint packSnorm2x16 (vec2);");
            s.append(  "highp vec2 unpackSnorm2x16 (highp uint);");
            s.append(  "highp uint packUnorm2x16 (vec2);");
            s.append(  "highp vec2 unpackUnorm2x16 (highp uint);");
            s.append(  "highp uint packHalf2x16(mediump vec2);");
            s.append("mediump vec2 unpackHalf2x16(highp uint);");
        }

        //
        // Geometric Functions.
        //
        s.append("float length(float x);");
        s.append("float length(vec2  x);");
        s.append("float length(vec3  x);");
        s.append("float length(vec4  x);");

        s.append("float distance(float p0, float p1);");
        s.append("float distance(vec2  p0, vec2  p1);");
        s.append("float distance(vec3  p0, vec3  p1);");
        s.append("float distance(vec4  p0, vec4  p1);");

        s.append("float dot(float x, float y);");
        s.append("float dot(vec2  x, vec2  y);");
        s.append("float dot(vec3  x, vec3  y);");
        s.append("float dot(vec4  x, vec4  y);");

        s.append("vec3 cross(vec3 x, vec3 y);");
        s.append("float normalize(float x);");
        s.append("vec2  normalize(vec2  x);");
        s.append("vec3  normalize(vec3  x);");
        s.append("vec4  normalize(vec4  x);");

        s.append("float faceforward(float N, float I, float Nref);");
        s.append("vec2  faceforward(vec2  N, vec2  I, vec2  Nref);");
        s.append("vec3  faceforward(vec3  N, vec3  I, vec3  Nref);");
        s.append("vec4  faceforward(vec4  N, vec4  I, vec4  Nref);");

        s.append("float reflect(float I, float N);");
        s.append("vec2  reflect(vec2  I, vec2  N);");
        s.append("vec3  reflect(vec3  I, vec3  N);");
        s.append("vec4  reflect(vec4  I, vec4  N);");

        s.append("float refract(float I, float N, float eta);");
        s.append("vec2  refract(vec2  I, vec2  N, float eta);");
        s.append("vec3  refract(vec3  I, vec3  N, float eta);");
        s.append("vec4  refract(vec4  I, vec4  N, float eta);");

        //
        // Matrix Functions.
        //
        s.append("mat2 matrixCompMult(mat2 x, mat2 y);");
        s.append("mat3 matrixCompMult(mat3 x, mat3 y);");
        s.append("mat4 matrixCompMult(mat4 x, mat4 y);");

        if (version >= 120) {
            s.append("mat2   outerProduct(vec2 c, vec2 r);");
            s.append("mat3   outerProduct(vec3 c, vec3 r);");
            s.append("mat4   outerProduct(vec4 c, vec4 r);");
            s.append("mat2x3 outerProduct(vec3 c, vec2 r);");
            s.append("mat3x2 outerProduct(vec2 c, vec3 r);");
            s.append("mat2x4 outerProduct(vec4 c, vec2 r);");
            s.append("mat4x2 outerProduct(vec2 c, vec4 r);");
            s.append("mat3x4 outerProduct(vec4 c, vec3 r);");
            s.append("mat4x3 outerProduct(vec3 c, vec4 r);");

            s.append("mat2   transpose(mat2   m);");
            s.append("mat3   transpose(mat3   m);");
            s.append("mat4   transpose(mat4   m);");
            s.append("mat2x3 transpose(mat3x2 m);");
            s.append("mat3x2 transpose(mat2x3 m);");
            s.append("mat2x4 transpose(mat4x2 m);");
            s.append("mat4x2 transpose(mat2x4 m);");
            s.append("mat3x4 transpose(mat4x3 m);");
            s.append("mat4x3 transpose(mat3x4 m);");

            if (version >= 150) {
                s.append("float determinant(mat2 m);");
                s.append("float determinant(mat3 m);");
                s.append("float determinant(mat4 m);");

                s.append("mat2 inverse(mat2 m);");
                s.append("mat3 inverse(mat3 m);");
                s.append("mat4 inverse(mat4 m);");
            }
        }

        //
        // Vector relational functions.
        //
        s.append("bvec2 lessThan(vec2 x, vec2 y);");
        s.append("bvec3 lessThan(vec3 x, vec3 y);");
        s.append("bvec4 lessThan(vec4 x, vec4 y);");

        s.append("bvec2 lessThan(ivec2 x, ivec2 y);");
        s.append("bvec3 lessThan(ivec3 x, ivec3 y);");
        s.append("bvec4 lessThan(ivec4 x, ivec4 y);");

        s.append("bvec2 lessThanEqual(vec2 x, vec2 y);");
        s.append("bvec3 lessThanEqual(vec3 x, vec3 y);");
        s.append("bvec4 lessThanEqual(vec4 x, vec4 y);");

        s.append("bvec2 lessThanEqual(ivec2 x, ivec2 y);");
        s.append("bvec3 lessThanEqual(ivec3 x, ivec3 y);");
        s.append("bvec4 lessThanEqual(ivec4 x, ivec4 y);");

        s.append("bvec2 greaterThan(vec2 x, vec2 y);");
        s.append("bvec3 greaterThan(vec3 x, vec3 y);");
        s.append("bvec4 greaterThan(vec4 x, vec4 y);");

        s.append("bvec2 greaterThan(ivec2 x, ivec2 y);");
        s.append("bvec3 greaterThan(ivec3 x, ivec3 y);");
        s.append("bvec4 greaterThan(ivec4 x, ivec4 y);");

        s.append("bvec2 greaterThanEqual(vec2 x, vec2 y);");
        s.append("bvec3 greaterThanEqual(vec3 x, vec3 y);");
        s.append("bvec4 greaterThanEqual(vec4 x, vec4 y);");

        s.append("bvec2 greaterThanEqual(ivec2 x, ivec2 y);");
        s.append("bvec3 greaterThanEqual(ivec3 x, ivec3 y);");
        s.append("bvec4 greaterThanEqual(ivec4 x, ivec4 y);");

        s.append("bvec2 equal(vec2 x, vec2 y);");
        s.append("bvec3 equal(vec3 x, vec3 y);");
        s.append("bvec4 equal(vec4 x, vec4 y);");

        s.append("bvec2 equal(ivec2 x, ivec2 y);");
        s.append("bvec3 equal(ivec3 x, ivec3 y);");
        s.append("bvec4 equal(ivec4 x, ivec4 y);");

        s.append("bvec2 equal(bvec2 x, bvec2 y);");
        s.append("bvec3 equal(bvec3 x, bvec3 y);");
        s.append("bvec4 equal(bvec4 x, bvec4 y);");

        s.append("bvec2 notEqual(vec2 x, vec2 y);");
        s.append("bvec3 notEqual(vec3 x, vec3 y);");
        s.append("bvec4 notEqual(vec4 x, vec4 y);");

        s.append("bvec2 notEqual(ivec2 x, ivec2 y);");
        s.append("bvec3 notEqual(ivec3 x, ivec3 y);");
        s.append("bvec4 notEqual(ivec4 x, ivec4 y);");

        s.append("bvec2 notEqual(bvec2 x, bvec2 y);");
        s.append("bvec3 notEqual(bvec3 x, bvec3 y);");
        s.append("bvec4 notEqual(bvec4 x, bvec4 y);");

        s.append("bool any(bvec2 x);");
        s.append("bool any(bvec3 x);");
        s.append("bool any(bvec4 x);");

        s.append("bool all(bvec2 x);");
        s.append("bool all(bvec3 x);");
        s.append("bool all(bvec4 x);");

        s.append("bvec2 not(bvec2 x);");
        s.append("bvec3 not(bvec3 x);");
        s.append("bvec4 not(bvec4 x);");

        s.append("\n");

        //
        // Original-style texture functions existing in both stages.
        // (Per-stage functions below.)
        //
        if ((profile == EEsProfile && version == 100) ||
            profile == ECompatibilityProfile ||
            version < FirstProfileVersion) {
            s.append("vec4 texture2D(sampler2D, vec2);");

            s.append("vec4 texture2DProj(sampler2D, vec3);");
            s.append("vec4 texture2DProj(sampler2D, vec4);");

            s.append("vec4 textureCube(samplerCube, vec3);");
        }

        if (profile != EEsProfile &&
            (profile == ECompatibilityProfile || version < FirstProfileVersion)) {
            s.append("vec4 texture1D(sampler1D, float);");

            s.append("vec4 texture1DProj(sampler1D, vec2);");
            s.append("vec4 texture1DProj(sampler1D, vec4);");

            s.append("vec4 texture3D(sampler3D, vec3);");
            s.append("vec4 texture3DProj(sampler3D, vec4);");

            s.append("vec4 shadow1D(sampler1DShadow, vec3);");
            s.append("vec4 shadow2D(sampler2DShadow, vec3);");
            s.append("vec4 shadow1DProj(sampler1DShadow, vec4);");
            s.append("vec4 shadow2DProj(sampler2DShadow, vec4);");

            // TODO: functionality: non-ES legacy texuring for Lod, others?
        }
        s.append("\n");

        //
        // Noise functions.
        //
        if (profile != EEsProfile) {
            s.append("float noise1(float x);");
            s.append("float noise1(vec2  x);");
            s.append("float noise1(vec3  x);");
            s.append("float noise1(vec4  x);");

            s.append("vec2 noise2(float x);");
            s.append("vec2 noise2(vec2  x);");
            s.append("vec2 noise2(vec3  x);");
            s.append("vec2 noise2(vec4  x);");

            s.append("vec3 noise3(float x);");
            s.append("vec3 noise3(vec2  x);");
            s.append("vec3 noise3(vec3  x);");
            s.append("vec3 noise3(vec4  x);");

            s.append("vec4 noise4(float x);");
            s.append("vec4 noise4(vec2  x);");
            s.append("vec4 noise4(vec3  x);");
            s.append("vec4 noise4(vec4  x);");

            s.append("\n");
        }
    }
    {
        //============================================================================
        //
        // Prototypes for built-in functions seen by vertex shaders only.
        //
        //============================================================================

        TString& s = stageBuiltins[EShLangVertex];

        //
        // Geometric Functions.
        //
        if (profile != EEsProfile)
            s.append("vec4 ftransform();");

        //
        // Original-style texture Functions with lod.
        //
        if (profile != EEsProfile || version == 100) {
            s.append("vec4 texture2DLod(sampler2D, vec2, float);");
            s.append("vec4 texture2DProjLod(sampler2D, vec3, float);");
            s.append("vec4 texture2DProjLod(sampler2D, vec4, float);");
            s.append("vec4 textureCubeLod(samplerCube, vec3, float);");
        }
        if (profile != EEsProfile && version > 100) {
            s.append("vec4 texture1DLod(sampler1D, float, float);");
            s.append("vec4 texture1DProjLod(sampler1D, vec2, float);");
            s.append("vec4 texture1DProjLod(sampler1D, vec4, float);");
            s.append("vec4 texture3DLod(sampler3D, vec3, float);");
            s.append("vec4 texture3DProjLod(sampler3D, vec4, float);");
            s.append("vec4 shadow1DLod(sampler1DShadow, vec3, float);");
            s.append("vec4 shadow2DLod(sampler2DShadow, vec3, float);");
            s.append("vec4 shadow1DProjLod(sampler1DShadow, vec4, float);");
            s.append("vec4 shadow2DProjLod(sampler2DShadow, vec4, float);");
        }
		s.append("\n");
    }
    if (profile != EEsProfile && version >= 150) {
        //============================================================================
        //
        // Prototypes for built-in functions seen by geometry shaders only.
        //
        //============================================================================

        TString& s = stageBuiltins[EShLangGeometry];

        if (version >= 400) {
            s.append("void EmitStreamVertex(int);");
            s.append("void EndStreamPrimitive(int);");
        }
        s.append("void EmitVertex();");
        s.append("void EndPrimitive();");
		s.append("\n");
    }
    if (profile != EEsProfile) {
        //============================================================================
        //
        // Prototypes for all control functions.
        //
        //============================================================================

        if (version >= 400)
            stageBuiltins[EShLangTessControl].append("void barrier();");
        if (version >= 430)
            stageBuiltins[EShLangCompute].append("void barrier();");

        if (version >= 420)
            commonBuiltins.append("void memoryBarrier();");
        if (version >= 430) {
            commonBuiltins.append("void memoryBarrierAtomicCounter();");
            commonBuiltins.append("void memoryBarrierBuffer();");
            commonBuiltins.append("void memoryBarrierImage();");
            stageBuiltins[EShLangCompute].append("void memoryBarrierShared();");
            stageBuiltins[EShLangCompute].append("void groupMemoryBarrier();");
        }
    }
    {
        //============================================================================
        //
        // Prototypes for built-in functions seen by fragment shaders only.
        //
        //============================================================================

        TString& s = stageBuiltins[EShLangFragment];

        //
        // Original-style texture Functions with bias.
        //
        if (profile != EEsProfile || version == 100) {
            s.append("vec4 texture2D(sampler2D, vec2, float);");
            s.append("vec4 texture2DProj(sampler2D, vec3, float);");
            s.append("vec4 texture2DProj(sampler2D, vec4, float);");
            s.append("vec4 textureCube(samplerCube, vec3, float);");
        }
        if (profile != EEsProfile && version > 100) {
            s.append("vec4 texture1D(sampler1D, float, float);");
            s.append("vec4 texture1DProj(sampler1D, vec2, float);");
            s.append("vec4 texture1DProj(sampler1D, vec4, float);");
            s.append("vec4 texture3D(sampler3D, vec3, float);");
            s.append("vec4 texture3DProj(sampler3D, vec4, float);");
            s.append("vec4 shadow1D(sampler1DShadow, vec3, float);");
            s.append("vec4 shadow2D(sampler2DShadow, vec3, float);");
            s.append("vec4 shadow1DProj(sampler1DShadow, vec4, float);");
            s.append("vec4 shadow2DProj(sampler2DShadow, vec4, float);");
        }

		s.append("float dFdx(float p);");
        s.append("vec2  dFdx(vec2  p);");
        s.append("vec3  dFdx(vec3  p);");
        s.append("vec4  dFdx(vec4  p);");

        s.append("float dFdy(float p);");
        s.append("vec2  dFdy(vec2  p);");
        s.append("vec3  dFdy(vec3  p);");
        s.append("vec4  dFdy(vec4  p);");

        s.append("float fwidth(float p);");
        s.append("vec2  fwidth(vec2  p);");
        s.append("vec3  fwidth(vec3  p);");
        s.append("vec4  fwidth(vec4  p);");

		s.append("\n");
    }
    {
        //============================================================================
        //
        // Standard Uniforms
        //
        //============================================================================

        TString& s = commonBuiltins;

        //
        // Depth range in window coordinates, p. 33
        //
        s.append("struct gl_DepthRangeParameters {");
        if (profile == EEsProfile) {
            s.append("    highp float near;");        // n
            s.append("    highp float far;");         // f
            s.append("    highp float diff;");        // f - n
        } else {
            s.append("    float near;");        // n
            s.append("    float far;");         // f
            s.append("    float diff;");        // f - n
        }
        s.append("};");
        s.append("uniform gl_DepthRangeParameters gl_DepthRange;");

        if (profile != EEsProfile && (version < FirstProfileVersion || profile == ECompatibilityProfile)) {
            //
            // Matrix state. p. 31, 32, 37, 39, 40.
            //
            s.append("uniform mat4  gl_ModelViewMatrix;");
            s.append("uniform mat4  gl_ProjectionMatrix;");
            s.append("uniform mat4  gl_ModelViewProjectionMatrix;");

            //
            // Derived matrix state that provides inverse and transposed versions
            // of the matrices above.
            //
            s.append("uniform mat3  gl_NormalMatrix;");

            s.append("uniform mat4  gl_ModelViewMatrixInverse;");
            s.append("uniform mat4  gl_ProjectionMatrixInverse;");
            s.append("uniform mat4  gl_ModelViewProjectionMatrixInverse;");

            s.append("uniform mat4  gl_ModelViewMatrixTranspose;");
            s.append("uniform mat4  gl_ProjectionMatrixTranspose;");
            s.append("uniform mat4  gl_ModelViewProjectionMatrixTranspose;");

            s.append("uniform mat4  gl_ModelViewMatrixInverseTranspose;");
            s.append("uniform mat4  gl_ProjectionMatrixInverseTranspose;");
            s.append("uniform mat4  gl_ModelViewProjectionMatrixInverseTranspose;");

            //
            // Normal scaling p. 39.
            //
            s.append("uniform float gl_NormalScale;");

            //
            // Point Size, p. 66, 67.
            //
            s.append("struct gl_PointParameters {");
            s.append("    float size;");
            s.append("    float sizeMin;");
            s.append("    float sizeMax;");
            s.append("    float fadeThresholdSize;");
            s.append("    float distanceConstantAttenuation;");
            s.append("    float distanceLinearAttenuation;");
            s.append("    float distanceQuadraticAttenuation;");
            s.append("};");

            s.append("uniform gl_PointParameters gl_Point;");

            //
            // Material State p. 50, 55.
            //
            s.append("struct gl_MaterialParameters {");
            s.append("    vec4  emission;");    // Ecm
            s.append("    vec4  ambient;");     // Acm
            s.append("    vec4  diffuse;");     // Dcm
            s.append("    vec4  specular;");    // Scm
            s.append("    float shininess;");   // Srm
            s.append("};");
            s.append("uniform gl_MaterialParameters  gl_FrontMaterial;");
            s.append("uniform gl_MaterialParameters  gl_BackMaterial;");

            //
            // Light State p 50, 53, 55.
            //

            s.append("struct gl_LightSourceParameters {");
            s.append("    vec4  ambient;");             // Acli
            s.append("    vec4  diffuse;");             // Dcli
            s.append("    vec4  specular;");            // Scli
            s.append("    vec4  position;");            // Ppli
            s.append("    vec4  halfVector;");          // Derived: Hi
            s.append("    vec3  spotDirection;");       // Sdli
            s.append("    float spotExponent;");        // Srli
            s.append("    float spotCutoff;");          // Crli
                                                                 // (range: [0.0,90.0], 180.0)
            s.append("    float spotCosCutoff;");       // Derived: cos(Crli)
                                                                 // (range: [1.0,0.0],-1.0)
            s.append("    float constantAttenuation;"); // K0
            s.append("    float linearAttenuation;");   // K1
            s.append("    float quadraticAttenuation;");// K2
            s.append("};");


            s.append("struct gl_LightModelParameters {");
            s.append("    vec4  ambient;");       // Acs
            s.append("};");

            s.append("uniform gl_LightModelParameters  gl_LightModel;");

            //
            // Derived state from products of light and material.
            //

            s.append("struct gl_LightModelProducts {");
            s.append("    vec4  sceneColor;");     // Derived. Ecm + Acm * Acs
            s.append("};");

            s.append("uniform gl_LightModelProducts gl_FrontLightModelProduct;");
            s.append("uniform gl_LightModelProducts gl_BackLightModelProduct;");

            s.append("struct gl_LightProducts {");
            s.append("    vec4  ambient;");        // Acm * Acli
            s.append("    vec4  diffuse;");        // Dcm * Dcli
            s.append("    vec4  specular;");       // Scm * Scli
            s.append("};");

            //
            // Fog p. 161
            //
            s.append("struct gl_FogParameters {");
            s.append("    vec4  color;");
            s.append("    float density;");
            s.append("    float start;");
            s.append("    float end;");
            s.append("    float scale;");   //  1 / (gl_FogEnd - gl_FogStart)
            s.append("};");

            s.append("uniform gl_FogParameters gl_Fog;");
        }

        s.append("\n");
    }
    //============================================================================
    //
    // Vertex attributes, p. 19.
    //
    //============================================================================

    if (profile != EEsProfile) {
        TString& s = stageBuiltins[EShLangVertex];

        if (version < 130) {
            s.append("attribute vec4  gl_Color;");
            s.append("attribute vec4  gl_SecondaryColor;");
            s.append("attribute vec3  gl_Normal;");
            s.append("attribute vec4  gl_Vertex;");
            s.append("attribute vec4  gl_MultiTexCoord0;");
            s.append("attribute vec4  gl_MultiTexCoord1;");
            s.append("attribute vec4  gl_MultiTexCoord2;");
            s.append("attribute vec4  gl_MultiTexCoord3;");
            s.append("attribute vec4  gl_MultiTexCoord4;");
            s.append("attribute vec4  gl_MultiTexCoord5;");
            s.append("attribute vec4  gl_MultiTexCoord6;");
            s.append("attribute vec4  gl_MultiTexCoord7;");
            s.append("attribute float gl_FogCoord;");
        } else if (version < FirstProfileVersion || profile == ECompatibilityProfile) {
            s.append("in vec4  gl_Color;");
            s.append("in vec4  gl_SecondaryColor;");
            s.append("in vec3  gl_Normal;");
            s.append("in vec4  gl_Vertex;");
            s.append("in vec4  gl_MultiTexCoord0;");
            s.append("in vec4  gl_MultiTexCoord1;");
            s.append("in vec4  gl_MultiTexCoord2;");
            s.append("in vec4  gl_MultiTexCoord3;");
            s.append("in vec4  gl_MultiTexCoord4;");
            s.append("in vec4  gl_MultiTexCoord5;");
            s.append("in vec4  gl_MultiTexCoord6;");
            s.append("in vec4  gl_MultiTexCoord7;");
            s.append("in float gl_FogCoord;");
        }

        s.append("\n");
    }
    //============================================================================
    //
    // Define the output varying interface from the vertex shader.
    //
    //============================================================================

    if (profile != EEsProfile) {
        TString& s = stageBuiltins[EShLangVertex];

        if (version < 130) {
            s.append("varying vec4  gl_FrontColor;");
            s.append("varying vec4  gl_BackColor;");
            s.append("varying vec4  gl_FrontSecondaryColor;");
            s.append("varying vec4  gl_BackSecondaryColor;");
            s.append("varying vec4  gl_TexCoord[];");
            s.append("varying float gl_FogFragCoord;");
        } else if (version < FirstProfileVersion || profile == ECompatibilityProfile) {
            s.append("out vec4  gl_FrontColor;");
            s.append("out vec4  gl_BackColor;");
            s.append("out vec4  gl_FrontSecondaryColor;");
            s.append("out vec4  gl_BackSecondaryColor;");
            s.append("out vec4  gl_TexCoord[];");
            s.append("out float gl_FogFragCoord;");
        }

        s.append("\n");
    }
    {
        //============================================================================
        //
        // Define the input varying interface to the fragment shader.
        //
        //============================================================================

        if (profile != EEsProfile) {
            TString& s = stageBuiltins[EShLangFragment];
            if (version < 130) {
                s.append("varying vec4  gl_Color;");
                s.append("varying vec4  gl_SecondaryColor;");
                s.append("varying vec4  gl_TexCoord[];");
                s.append("varying float gl_FogFragCoord;");
            } else if (version < FirstProfileVersion || profile == ECompatibilityProfile) {
                s.append("in vec4  gl_Color;");
                s.append("in vec4  gl_SecondaryColor;");
                s.append("in vec4  gl_TexCoord[];");
                s.append("in float gl_FogFragCoord;");
            }

            s.append("\n");
        }
    }

    if (version >= 130)
        add2ndGenerationSamplingImaging(version, profile);

    //printf("%s\n", commonBuiltins.c_str();
}

//
// Helper function for initialize(), to add the second set of names for texturing, 
// when adding context-independent built-in functions.
//
void TBuiltIns::add2ndGenerationSamplingImaging(int version, EProfile profile)
{
    TBasicType bTypes[3] = { EbtFloat, EbtInt, EbtUint };

    // enumerate all the types
    for (int image = 0; image <= 1; ++image) { // loop over "bool" image vs sampler

        if (image > 0 && version < 420)
            continue;

        for (int shadow = 0; shadow <= 1; ++shadow) { // loop over "bool" shadow or not
            for (int ms = 0; ms <=1; ++ms) {

                if ((ms || image) && shadow)
                    continue;
                if (ms && (profile == EEsProfile || version < 150))
                    continue;

                for (int arrayed = 0; arrayed <= 1; ++arrayed) { // loop over "bool" arrayed or not
                    for (int dim = Esd1D; dim < EsdNumDims; ++dim) { // 1D, 2D, ..., buffer

                        if ((dim == Esd1D || dim == EsdRect) && profile == EEsProfile)
                            continue;
                        if (dim == EsdRect && version < 140)
                            continue;
                        if (dim != Esd2D && ms)
                            continue;
                        if ((dim == Esd3D || dim == EsdRect) && arrayed)
                            continue;
                        if (dim == Esd3D && shadow)
                            continue;
                        if (dim == EsdCube && arrayed && version < 400)
                            continue;
                        if (dim == EsdBuffer && (profile == EEsProfile || version < 140))
                            continue;
                        if (dim == EsdBuffer && (shadow || arrayed || ms))
                            continue;

                        for (int bType = 0; bType < 3; ++bType) { // float, int, uint results

                            if (shadow && bType > 0)
                                continue;

                            //
                            // Now, make all the function prototypes for the type we just built...
                            //

                            TSampler sampler;
                            sampler.set(bTypes[bType], (TSamplerDim)dim, arrayed ? true : false,
                                                                         shadow  ? true : false,
                                                                         ms      ? true : false);
                            if (image)
                                sampler.image = true;

                            TString typeName = sampler.getString();

                            addQueryFunctions(sampler, typeName, version, profile);

                            if (image)
                                addImageFunctions(sampler, typeName, version, profile);
                            else
                                addSamplingFunctions(sampler, typeName, version, profile);
                        }
                    }
                }
            }
        }
    }
}

//
// Helper function for add2ndGenerationSamplingImaging(), 
// when adding context-independent built-in functions.
//
void TBuiltIns::addQueryFunctions(TSampler sampler, TString& typeName, int version, EProfile profile)
{
    //
    // textureSize
    //

    if (version < 430 && sampler.image)
        return;

    TString& s = commonBuiltins;
    if (profile == EEsProfile)
        s.append("highp ");
    int dims = dimMap[sampler.dim] + (sampler.arrayed ? 1 : 0) - (sampler.dim == EsdCube ? 1 : 0);
    if (dims == 1)
        s.append("int");
    else {
        s.append("ivec");
        s.append(postfixes[dims]);
    }
    if (sampler.image)
        s.append(" imageSize(");
    else
        s.append(" textureSize(");
    s.append(typeName);
    if (! sampler.image && sampler.dim != EsdRect && sampler.dim != EsdBuffer && ! sampler.ms)
        s.append(",int);\n");
    else
        s.append(");\n");
}

//
// Helper function for add2ndGenerationSamplingImaging(), 
// when adding context-independent built-in functions.
//
void TBuiltIns::addImageFunctions(TSampler sampler, TString& typeName, int version, EProfile profile)
{
    // TODO: 4.2 Functionality: imaging functions
}

//
// Helper function for add2ndGenerationSamplingImaging(), 
// when adding context-independent built-in functions.
//
void TBuiltIns::addSamplingFunctions(TSampler sampler, TString& typeName, int version, EProfile profile)
{
    // make one string per stage to contain all functions of the passed-in type for that stage
    TString functions[EShLangCount];

    //
    // texturing
    //
    for (int proj = 0; proj <= 1; ++proj) { // loop over "bool" projective or not

        if (proj && (sampler.dim == EsdCube || sampler.dim == EsdBuffer || sampler.arrayed || sampler.ms))
            continue;

        for (int lod = 0; lod <= 1; ++lod) {

            if (lod && (sampler.dim == EsdBuffer || sampler.dim == EsdRect || sampler.ms))
                continue;
            if (lod && sampler.dim == Esd2D && sampler.arrayed && sampler.shadow)
                continue;
            if (lod && sampler.dim == EsdCube && sampler.shadow)
                continue;

            for (int bias = 0; bias <= 1; ++bias) {

                if (bias && (lod || sampler.ms))
                    continue;
                if (bias && sampler.dim == Esd2D && sampler.shadow && sampler.arrayed)
                    continue;
                if (bias && (sampler.dim == EsdRect || sampler.dim == EsdBuffer))
                    continue;

                for (int offset = 0; offset <= 1; ++offset) { // loop over "bool" offset or not

                    if (proj + offset + bias + lod > 3)
                        continue;
                    if (offset && (sampler.dim == EsdCube || sampler.dim == EsdBuffer || sampler.ms))
                        continue;

                    for (int fetch = 0; fetch <= 1; ++fetch) { // loop over "bool" fetch or not

                        if (proj + offset + fetch + bias + lod > 3)
                            continue;
                        if (fetch && (lod || bias))
                            continue;
                        if (fetch && (sampler.shadow || sampler.dim == EsdCube))
                            continue;
                        if (fetch == 0 && (sampler.ms || sampler.dim == EsdBuffer))
                            continue;

                        for (int grad = 0; grad <= 1; ++grad) { // loop over "bool" grad or not

                            if (grad && (lod || bias || sampler.ms))
                                continue;
                            if (grad && sampler.dim == EsdBuffer)
                                continue;
                            if (proj + offset + fetch + grad + bias + lod > 3)
                                continue;

                            for (int extraProj = 0; extraProj <= 1; ++extraProj) {
                                bool compare = false;
                                int totalDims = dimMap[sampler.dim] + (sampler.arrayed ? 1 : 0);
                                // skip dummy unused second component for 1D non-array shadows
                                if (sampler.shadow && totalDims < 2)
                                    totalDims = 2;
                                totalDims += (sampler.shadow ? 1 : 0) + proj;
                                if (totalDims > 4 && sampler.shadow) {
                                    compare = true;
                                    totalDims = 4;
                                }
                                assert(totalDims <= 4);

                                if (extraProj && ! proj)
                                    continue;
                                if (extraProj && (sampler.dim == Esd3D || sampler.shadow))
                                    continue;

                                TString s;

                                // return type
                                if (sampler.shadow)
                                    s.append("float ");
                                else {
                                    s.append(prefixes[sampler.type]);
                                    s.append("vec4 ");
                                }

                                // name
                                if (fetch)
                                    s.append("texel");
                                else
                                    s.append("texture");
                                if (proj)
                                    s.append("Proj");
                                if (lod)
                                    s.append("Lod");
                                if (grad)
                                    s.append("Grad");
                                if (fetch)
                                    s.append("Fetch");
                                if (offset)
                                    s.append("Offset");
                                s.append("(");

                                // sampler type
                                s.append(typeName);

                                // P coordinate
                                if (extraProj)
                                    s.append(",vec4");
                                else {
                                    s.append(",");
                                    TBasicType t = fetch ? EbtInt : EbtFloat;
                                    if (totalDims == 1)
                                        s.append(TType::getBasicString(t));
                                    else {
                                        s.append(prefixes[t]);
                                        s.append("vec");
                                        s.append(postfixes[totalDims]);
                                    }
                                }

                                if (bias && compare)
                                    continue;

                                // non-optional lod argument (lod that's not driven by lod loop)
                                if (fetch && sampler.dim != EsdBuffer && !sampler.ms)
                                    s.append(",int");

                                // non-optional lod
                                if (lod)
                                    s.append(",float");

                                // gradient arguments
                                if (grad) {
                                    if (dimMap[sampler.dim] == 1)
                                        s.append(",float,float");
                                    else {
                                        s.append(",vec");
                                        s.append(postfixes[dimMap[sampler.dim]]);
                                        s.append(",vec");
                                        s.append(postfixes[dimMap[sampler.dim]]);
                                    }
                                }

                                // offset
                                if (offset) {
                                    if (dimMap[sampler.dim] == 1)
                                        s.append(",int");
                                    else {
                                        s.append(",ivec");
                                        s.append(postfixes[dimMap[sampler.dim]]);
                                    }
                                }

                                // optional bias or non-optional compare
                                if (bias || compare)
                                    s.append(",float");

                                s.append(");\n");

                                // Add to the per-language set of built-ins

                                if (! bias) {
                                    functions[EShLangVertex].append(s);
                                    functions[EShLangGeometry].append(s);
                                    functions[EShLangTessControl].append(s);
                                    functions[EShLangTessEvaluation].append(s);
                                    functions[EShLangCompute].append(s);
                                }
                                commonBuiltins.append(s);
                            }
                        }
                    }
                }
            }
        }
    }
}

//
// Add context-dependent built-in functions and variables that are present
// for the given version and profile.  Share common ones across stages, otherwise
// make stage-specific entries.
//
void TBuiltIns::initialize(const TBuiltInResource &resources, int version, EProfile profile, EShLanguage language)
{
    //
    // Initialize the context-dependent (resource-dependent) built-in strings for parsing.
    //
    {
        //============================================================================
        //
        // Standard Uniforms
        //
        //============================================================================

        TString& s = commonBuiltins;
		const int maxSize = 80;
        char builtInConstant[maxSize];

        //
        // Build string of implementation dependent constants.
        //

        if (profile == EEsProfile) {
            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxVertexAttribs = %d;", resources.maxVertexAttribs);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxVertexUniformVectors = %d;", resources.maxVertexUniformVectors);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxVertexTextureImageUnits = %d;", resources.maxVertexTextureImageUnits);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxCombinedTextureImageUnits = %d;", resources.maxCombinedTextureImageUnits);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxTextureImageUnits = %d;", resources.maxTextureImageUnits);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxFragmentUniformVectors = %d;", resources.maxFragmentUniformVectors);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxDrawBuffers = %d;", resources.maxDrawBuffers);
            s.append(builtInConstant);

            if (version == 100) {
                snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxVaryingVectors = %d;", resources.maxVaryingVectors);
                s.append(builtInConstant);
            } else {
                snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxVertexOutputVectors = %d;", resources.maxVertexOutputVectors);
                s.append(builtInConstant);

                snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxFragmentInputVectors = %d;", resources.maxFragmentInputVectors);
                s.append(builtInConstant);

                snprintf(builtInConstant, maxSize, "const mediump int  gl_MinProgramTexelOffset = %d;", resources.minProgramTexelOffset);
                s.append(builtInConstant);

                snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxProgramTexelOffset = %d;", resources.maxProgramTexelOffset);
                s.append(builtInConstant);
            }
        } else {
            snprintf(builtInConstant, maxSize, "const int  gl_MaxVertexAttribs = %d;", resources.maxVertexAttribs);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const int  gl_MaxVertexTextureImageUnits = %d;", resources.maxVertexTextureImageUnits);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const int  gl_MaxCombinedTextureImageUnits = %d;", resources.maxCombinedTextureImageUnits);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const int  gl_MaxTextureImageUnits = %d;", resources.maxTextureImageUnits);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const int  gl_MaxDrawBuffers = %d;", resources.maxDrawBuffers);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const int  gl_MaxLights = %d;", resources.maxLights);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const int  gl_MaxClipPlanes = %d;", resources.maxClipPlanes);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const int  gl_MaxTextureUnits = %d;", resources.maxTextureUnits);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const int  gl_MaxTextureCoords = %d;", resources.maxTextureCoords);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const int  gl_MaxVertexUniformComponents = %d;", resources.maxVertexUniformComponents);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const int  gl_MaxVaryingFloats = %d;", resources.maxVaryingFloats);
            s.append(builtInConstant);

            snprintf(builtInConstant, maxSize, "const int  gl_MaxFragmentUniformComponents = %d;", resources.maxFragmentUniformComponents);
            s.append(builtInConstant);

            if (version < FirstProfileVersion || profile == ECompatibilityProfile) {
                //
                // OpenGL'uniform' state.  Page numbers are in reference to version
                // 1.4 of the OpenGL specification.
                //

                //
                // Matrix state. p. 31, 32, 37, 39, 40.
                //
                s.append("uniform mat4  gl_TextureMatrix[gl_MaxTextureCoords];");

                //
                // Derived matrix state that provides inverse and transposed versions
                // of the matrices above.
                //
                s.append("uniform mat4  gl_TextureMatrixInverse[gl_MaxTextureCoords];");

                s.append("uniform mat4  gl_TextureMatrixTranspose[gl_MaxTextureCoords];");

                s.append("uniform mat4  gl_TextureMatrixInverseTranspose[gl_MaxTextureCoords];");

                //
                // Clip planes p. 42.
                //
                s.append("uniform vec4  gl_ClipPlane[gl_MaxClipPlanes];");

                //
                // Light State p 50, 53, 55.
                //
                s.append("uniform gl_LightSourceParameters  gl_LightSource[gl_MaxLights];");

                //
                // Derived state from products of light.
                //
                s.append("uniform gl_LightProducts gl_FrontLightProduct[gl_MaxLights];");
                s.append("uniform gl_LightProducts gl_BackLightProduct[gl_MaxLights];");

                //
                // Texture Environment and Generation, p. 152, p. 40-42.
                //
                s.append("uniform vec4  gl_TextureEnvColor[gl_MaxTextureImageUnits];");
                s.append("uniform vec4  gl_EyePlaneS[gl_MaxTextureCoords];");
                s.append("uniform vec4  gl_EyePlaneT[gl_MaxTextureCoords];");
                s.append("uniform vec4  gl_EyePlaneR[gl_MaxTextureCoords];");
                s.append("uniform vec4  gl_EyePlaneQ[gl_MaxTextureCoords];");
                s.append("uniform vec4  gl_ObjectPlaneS[gl_MaxTextureCoords];");
                s.append("uniform vec4  gl_ObjectPlaneT[gl_MaxTextureCoords];");
                s.append("uniform vec4  gl_ObjectPlaneR[gl_MaxTextureCoords];");
                s.append("uniform vec4  gl_ObjectPlaneQ[gl_MaxTextureCoords];");
            }
        }

        s.append("\n");
    }
}

//
// Finish adding/processing context-independent built-in symbols.
// 1) Programmatically add symbols that could not be added by simple text strings above.
// 2) Map built-in functions to operators, for those that will turn into an operation node
//    instead of remaining a function call.
//
void IdentifyBuiltIns(int version, EProfile profile, EShLanguage language, TSymbolTable& symbolTable)
{
    TPrecisionQualifier pq;
    //
    // First, insert some special built-in variables that are not in
    // the built-in text strings.
    //
    switch(language) {
    case EShLangVertex:
        pq = profile == EEsProfile ? EpqHigh : EpqNone;
        symbolTable.insert(*new TVariable(NewPoolTString("gl_Position"),    TType(EbtFloat, EvqPosition, pq, 4)));

        pq = profile == EEsProfile ? (version > 100 ? EpqHigh : EpqMedium) : EpqNone;
        symbolTable.insert(*new TVariable(NewPoolTString("gl_PointSize"),   TType(EbtFloat, EvqPointSize, pq, 1)));

        if (profile != EEsProfile)
            symbolTable.insert(*new TVariable(NewPoolTString("gl_ClipVertex"),  TType(EbtFloat, EvqClipVertex, 4)));

        if (version >= 130) {
            pq = profile == EEsProfile ? EpqHigh : EpqNone;
            symbolTable.insert(*new TVariable(NewPoolTString("gl_VertexID"),    TType(EbtInt, EvqVertexId, pq, 1)));
            if (version >= 140)
                symbolTable.insert(*new TVariable(NewPoolTString("gl_InstanceID"),  TType(EbtInt, EvqInstanceId, pq, 1)));
        }
        break;

    case EShLangTessControl:
    case EShLangTessEvaluation:
    case EShLangGeometry:
        // TODO: desktop functionality: support new stages
        break;

    case EShLangFragment:
        symbolTable.insert(*new TVariable(NewPoolTString("gl_FrontFacing"), TType(EbtBool,  EvqFace, 1)));

        if (profile == EEsProfile)
            pq = version == 100 ? EpqMedium : EpqHigh;
        else
            pq = EpqNone;
        symbolTable.insert(*new TVariable(NewPoolTString("gl_FragCoord"),   TType(EbtFloat, EvqFragCoord, pq, 4)));

        if (profile == EEsProfile || version >= 120) {
            pq = profile == EEsProfile ? EpqMedium : EpqNone;
            symbolTable.insert(*new TVariable(NewPoolTString("gl_PointCoord"),  TType(EbtFloat, EvqPointCoord, pq, 2)));
        }

        if (version < FirstProfileVersion || profile == ECompatibilityProfile || (! ForwardCompatibility && profile != EEsProfile && version < 420)) {
            pq = profile == EEsProfile ? EpqMedium : EpqNone;
            symbolTable.insert(*new TVariable(NewPoolTString("gl_FragColor"),   TType(EbtFloat, EvqFragColor, pq, 4)));
        }

        if (profile != EEsProfile || version > 100) {
            pq = profile == EEsProfile ? EpqHigh : EpqNone;
            symbolTable.insert(*new TVariable(NewPoolTString("gl_FragDepth"),   TType(EbtFloat, EvqFragDepth, pq, 1)));
        }
        break;

    case EShLangCompute:
        // TODO: desktop functionality: support new stages
        break;

    default:
        assert(false && "Language not supported");
        break;
    }

    //
    // Next, identify which built-ins from the already loaded headers have
    // a mapping to an operator.  Those that are not identified as such are
    // expected to be resolved through a library of functions, versus as
    // operations.
    //
    symbolTable.relateToOperator("not",              EOpVectorLogicalNot);

    symbolTable.relateToOperator("matrixCompMult",   EOpMul);
    if (version >= 120) {
        symbolTable.relateToOperator("outerProduct", EOpOuterProduct);
        symbolTable.relateToOperator("transpose", EOpTranspose);
        if (version >= 150) {
            symbolTable.relateToOperator("determinant", EOpDeterminant);
            symbolTable.relateToOperator("inverse", EOpMatrixInverse);
        }
    }

    symbolTable.relateToOperator("mod",              EOpMod);
    symbolTable.relateToOperator("modf",             EOpModf);

    symbolTable.relateToOperator("equal",            EOpVectorEqual);
    symbolTable.relateToOperator("notEqual",         EOpVectorNotEqual);
    symbolTable.relateToOperator("lessThan",         EOpLessThan);
    symbolTable.relateToOperator("greaterThan",      EOpGreaterThan);
    symbolTable.relateToOperator("lessThanEqual",    EOpLessThanEqual);
    symbolTable.relateToOperator("greaterThanEqual", EOpGreaterThanEqual);

    symbolTable.relateToOperator("radians",      EOpRadians);
    symbolTable.relateToOperator("degrees",      EOpDegrees);
    symbolTable.relateToOperator("sin",          EOpSin);
    symbolTable.relateToOperator("cos",          EOpCos);
    symbolTable.relateToOperator("tan",          EOpTan);
    symbolTable.relateToOperator("asin",         EOpAsin);
    symbolTable.relateToOperator("acos",         EOpAcos);
    symbolTable.relateToOperator("atan",         EOpAtan);
    symbolTable.relateToOperator("sinh",         EOpSinh);
    symbolTable.relateToOperator("cosh",         EOpCosh);
    symbolTable.relateToOperator("tanh",         EOpTanh);
    symbolTable.relateToOperator("asinh",        EOpAsinh);
    symbolTable.relateToOperator("acosh",        EOpAcosh);
    symbolTable.relateToOperator("atanh",        EOpAtanh);

    symbolTable.relateToOperator("pow",          EOpPow);
    symbolTable.relateToOperator("exp2",         EOpExp2);
    symbolTable.relateToOperator("log",          EOpLog);
    symbolTable.relateToOperator("exp",          EOpExp);
    symbolTable.relateToOperator("log2",         EOpLog2);
    symbolTable.relateToOperator("sqrt",         EOpSqrt);
    symbolTable.relateToOperator("inversesqrt",  EOpInverseSqrt);

    symbolTable.relateToOperator("abs",          EOpAbs);
    symbolTable.relateToOperator("sign",         EOpSign);
    symbolTable.relateToOperator("floor",        EOpFloor);
    symbolTable.relateToOperator("trunc",        EOpTrunc);
    symbolTable.relateToOperator("round",        EOpRound);
    symbolTable.relateToOperator("roundEven",    EOpRoundEven);
    symbolTable.relateToOperator("ceil",         EOpCeil);
    symbolTable.relateToOperator("fract",        EOpFract);
    symbolTable.relateToOperator("min",          EOpMin);
    symbolTable.relateToOperator("max",          EOpMax);
    symbolTable.relateToOperator("clamp",        EOpClamp);
    symbolTable.relateToOperator("mix",          EOpMix);
    symbolTable.relateToOperator("step",         EOpStep);
    symbolTable.relateToOperator("smoothstep",   EOpSmoothStep);

    symbolTable.relateToOperator("isnan",  EOpIsNan);
    symbolTable.relateToOperator("isinf",  EOpIsInf);

    symbolTable.relateToOperator("floatBitsToInt",  EOpFloatBitsToInt);
    symbolTable.relateToOperator("floatBitsToUint", EOpFloatBitsToUint);
    symbolTable.relateToOperator("intBitsToFloat",  EOpIntBitsToFloat);
    symbolTable.relateToOperator("uintBitsToFloat", EOpUintBitsToFloat);
    symbolTable.relateToOperator("packSnorm2x16",   EOpPackSnorm2x16);
    symbolTable.relateToOperator("unpackSnorm2x16", EOpUnpackSnorm2x16);
    symbolTable.relateToOperator("packUnorm2x16",   EOpPackUnorm2x16);
    symbolTable.relateToOperator("unpackUnorm2x16", EOpUnpackUnorm2x16);
    symbolTable.relateToOperator("packHalf2x16",    EOpPackHalf2x16);
    symbolTable.relateToOperator("unpackHalf2x16",  EOpUnpackHalf2x16);

    symbolTable.relateToOperator("length",       EOpLength);
    symbolTable.relateToOperator("distance",     EOpDistance);
    symbolTable.relateToOperator("dot",          EOpDot);
    symbolTable.relateToOperator("cross",        EOpCross);
    symbolTable.relateToOperator("normalize",    EOpNormalize);
    symbolTable.relateToOperator("faceforward",  EOpFaceForward);
    symbolTable.relateToOperator("reflect",      EOpReflect);
    symbolTable.relateToOperator("refract",      EOpRefract);

    symbolTable.relateToOperator("any",          EOpAny);
    symbolTable.relateToOperator("all",          EOpAll);

    symbolTable.relateToOperator("barrier",                    EOpBarrier);
    symbolTable.relateToOperator("memoryBarrier",              EOpMemoryBarrier);
    symbolTable.relateToOperator("memoryBarrierAtomicCounter", EOpMemoryBarrierAtomicCounter);
    symbolTable.relateToOperator("memoryBarrierBuffer",        EOpMemoryBarrierBuffer);
    symbolTable.relateToOperator("memoryBarrierImage",         EOpMemoryBarrierImage);

    switch(language) {
    case EShLangVertex:
        break;

    case EShLangTessControl:
    case EShLangTessEvaluation:
        break;

    case EShLangGeometry:
        symbolTable.relateToOperator("EmitStreamVertex",   EOpEmitStreamVertex);
        symbolTable.relateToOperator("EndStreamPrimitive", EOpEndStreamPrimitive);
        symbolTable.relateToOperator("EmitVertex",         EOpEmitVertex);
        symbolTable.relateToOperator("EndPrimitive",       EOpEndPrimitive);
        break;

    case EShLangFragment:
        symbolTable.relateToOperator("dFdx",         EOpDPdx);
        symbolTable.relateToOperator("dFdy",         EOpDPdy);
        symbolTable.relateToOperator("fwidth",       EOpFwidth);
        break;

    case EShLangCompute:
        symbolTable.relateToOperator("memoryBarrierShared", EOpMemoryBarrierShared);
        symbolTable.relateToOperator("groupMemoryBarrier",  EOpGroupMemoryBarrier);
        break;

	default:
        assert(false && "Language not supported");
    }
}

//
// Add context-dependent (resource-specific) built-ins not yet handled.  These
// would be ones that need to be programmatically added because they cannot 
// be added by simple text strings.
//
void IdentifyBuiltIns(int version, EProfile profile, EShLanguage language, TSymbolTable& symbolTable, const TBuiltInResource &resources)
{
    switch(language) {

    case EShLangFragment:
        // Set up gl_FragData based on current array size.
        if (version < FirstProfileVersion || profile == ECompatibilityProfile || (! ForwardCompatibility && profile != EEsProfile && version < 420)) {
            TPrecisionQualifier pq = profile == EEsProfile ? EpqMedium : EpqNone;
            TType fragData(EbtFloat, EvqFragColor, pq, 4);
            TArraySizes* arraySizes = NewPoolTArraySizes();
            arraySizes->setSize(resources.maxDrawBuffers);
            fragData.setArraySizes(arraySizes);
            symbolTable.insert(*new TVariable(NewPoolTString("gl_FragData"), fragData));
        }
        break;

	default:
        break;
    }
}

} // end namespace glslang
