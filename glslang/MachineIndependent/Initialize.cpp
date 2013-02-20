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
// Create strings that declare built-in definitions, add built-ins that
// cannot be expressed in the files, and establish mappings between
// built-in functions and operators.
//

#include "../Include/intermediate.h"
#include "Initialize.h"

const int FirstProfileVersion = 150;

void TBuiltIns::initialize(int version, EProfile profile)
{
    //
    // Initialize all the built-in strings for parsing.
    //
    TString BuiltInFunctions;
    TString BuiltInFunctionsVertex;
    TString BuiltInFunctionsFragment;
    TString StandardVertexVaryings;
    TString StandardFragmentVaryings;
    TString StandardVertexAttributes;
    TString StandardUniforms;

    {
        //============================================================================
        //
        // Prototypes for built-in functions seen by both vertex and fragment shaders.
        //
        //============================================================================

        TString& s = BuiltInFunctions;

        //
        // Angle and Trigonometric Functions.
        //
        s.append(TString("float radians(float degrees);"));
        s.append(TString("vec2  radians(vec2  degrees);"));
        s.append(TString("vec3  radians(vec3  degrees);"));
        s.append(TString("vec4  radians(vec4  degrees);"));

        s.append(TString("float degrees(float radians);"));
        s.append(TString("vec2  degrees(vec2  radians);"));
        s.append(TString("vec3  degrees(vec3  radians);"));
        s.append(TString("vec4  degrees(vec4  radians);"));

        s.append(TString("float sin(float angle);"));
        s.append(TString("vec2  sin(vec2  angle);"));
        s.append(TString("vec3  sin(vec3  angle);"));
        s.append(TString("vec4  sin(vec4  angle);"));

        s.append(TString("float cos(float angle);"));
        s.append(TString("vec2  cos(vec2  angle);"));
        s.append(TString("vec3  cos(vec3  angle);"));
        s.append(TString("vec4  cos(vec4  angle);"));

        s.append(TString("float tan(float angle);"));
        s.append(TString("vec2  tan(vec2  angle);"));
        s.append(TString("vec3  tan(vec3  angle);"));
        s.append(TString("vec4  tan(vec4  angle);"));

        s.append(TString("float asin(float x);"));
        s.append(TString("vec2  asin(vec2  x);"));
        s.append(TString("vec3  asin(vec3  x);"));
        s.append(TString("vec4  asin(vec4  x);"));

        s.append(TString("float acos(float x);"));
        s.append(TString("vec2  acos(vec2  x);"));
        s.append(TString("vec3  acos(vec3  x);"));
        s.append(TString("vec4  acos(vec4  x);"));

        s.append(TString("float atan(float y, float x);"));
        s.append(TString("vec2  atan(vec2  y, vec2  x);"));
        s.append(TString("vec3  atan(vec3  y, vec3  x);"));
        s.append(TString("vec4  atan(vec4  y, vec4  x);"));

        s.append(TString("float atan(float y_over_x);"));
        s.append(TString("vec2  atan(vec2  y_over_x);"));
        s.append(TString("vec3  atan(vec3  y_over_x);"));
        s.append(TString("vec4  atan(vec4  y_over_x);"));

        //
        // Exponential Functions.
        //
        s.append(TString("float pow(float x, float y);"));
        s.append(TString("vec2  pow(vec2  x, vec2  y);"));
        s.append(TString("vec3  pow(vec3  x, vec3  y);"));
        s.append(TString("vec4  pow(vec4  x, vec4  y);"));

        s.append(TString("float exp(float x);"));
        s.append(TString("vec2  exp(vec2  x);"));
        s.append(TString("vec3  exp(vec3  x);"));
        s.append(TString("vec4  exp(vec4  x);"));

        s.append(TString("float log(float x);"));
        s.append(TString("vec2  log(vec2  x);"));
        s.append(TString("vec3  log(vec3  x);"));
        s.append(TString("vec4  log(vec4  x);"));

        s.append(TString("float exp2(float x);"));
        s.append(TString("vec2  exp2(vec2  x);"));
        s.append(TString("vec3  exp2(vec3  x);"));
        s.append(TString("vec4  exp2(vec4  x);"));

        s.append(TString("float log2(float x);"));
        s.append(TString("vec2  log2(vec2  x);"));
        s.append(TString("vec3  log2(vec3  x);"));
        s.append(TString("vec4  log2(vec4  x);"));

        s.append(TString("float sqrt(float x);"));
        s.append(TString("vec2  sqrt(vec2  x);"));
        s.append(TString("vec3  sqrt(vec3  x);"));
        s.append(TString("vec4  sqrt(vec4  x);"));

        s.append(TString("float inversesqrt(float x);"));
        s.append(TString("vec2  inversesqrt(vec2  x);"));
        s.append(TString("vec3  inversesqrt(vec3  x);"));
        s.append(TString("vec4  inversesqrt(vec4  x);"));

        //
        // Common Functions.
        //
        s.append(TString("float abs(float x);"));
        s.append(TString("vec2  abs(vec2  x);"));
        s.append(TString("vec3  abs(vec3  x);"));
        s.append(TString("vec4  abs(vec4  x);"));

        s.append(TString("float sign(float x);"));
        s.append(TString("vec2  sign(vec2  x);"));
        s.append(TString("vec3  sign(vec3  x);"));
        s.append(TString("vec4  sign(vec4  x);"));

        s.append(TString("float floor(float x);"));
        s.append(TString("vec2  floor(vec2  x);"));
        s.append(TString("vec3  floor(vec3  x);"));
        s.append(TString("vec4  floor(vec4  x);"));

        s.append(TString("float ceil(float x);"));
        s.append(TString("vec2  ceil(vec2  x);"));
        s.append(TString("vec3  ceil(vec3  x);"));
        s.append(TString("vec4  ceil(vec4  x);"));

        s.append(TString("float fract(float x);"));
        s.append(TString("vec2  fract(vec2  x);"));
        s.append(TString("vec3  fract(vec3  x);"));
        s.append(TString("vec4  fract(vec4  x);"));

        s.append(TString("float mod(float x, float y);"));
        s.append(TString("vec2  mod(vec2  x, float y);"));
        s.append(TString("vec3  mod(vec3  x, float y);"));
        s.append(TString("vec4  mod(vec4  x, float y);"));
        s.append(TString("vec2  mod(vec2  x, vec2  y);"));
        s.append(TString("vec3  mod(vec3  x, vec3  y);"));
        s.append(TString("vec4  mod(vec4  x, vec4  y);"));

        s.append(TString("float min(float x, float y);"));
        s.append(TString("vec2  min(vec2  x, float y);"));
        s.append(TString("vec3  min(vec3  x, float y);"));
        s.append(TString("vec4  min(vec4  x, float y);"));
        s.append(TString("vec2  min(vec2  x, vec2  y);"));
        s.append(TString("vec3  min(vec3  x, vec3  y);"));
        s.append(TString("vec4  min(vec4  x, vec4  y);"));

        s.append(TString("float max(float x, float y);"));
        s.append(TString("vec2  max(vec2  x, float y);"));
        s.append(TString("vec3  max(vec3  x, float y);"));
        s.append(TString("vec4  max(vec4  x, float y);"));
        s.append(TString("vec2  max(vec2  x, vec2  y);"));
        s.append(TString("vec3  max(vec3  x, vec3  y);"));
        s.append(TString("vec4  max(vec4  x, vec4  y);"));

        s.append(TString("float clamp(float x, float minVal, float maxVal);"));
        s.append(TString("vec2  clamp(vec2  x, float minVal, float maxVal);"));
        s.append(TString("vec3  clamp(vec3  x, float minVal, float maxVal);"));
        s.append(TString("vec4  clamp(vec4  x, float minVal, float maxVal);"));
        s.append(TString("vec2  clamp(vec2  x, vec2  minVal, vec2  maxVal);"));
        s.append(TString("vec3  clamp(vec3  x, vec3  minVal, vec3  maxVal);"));
        s.append(TString("vec4  clamp(vec4  x, vec4  minVal, vec4  maxVal);"));

        s.append(TString("float mix(float x, float y, float a);"));
        s.append(TString("vec2  mix(vec2  x, vec2  y, float a);"));
        s.append(TString("vec3  mix(vec3  x, vec3  y, float a);"));
        s.append(TString("vec4  mix(vec4  x, vec4  y, float a);"));
        s.append(TString("vec2  mix(vec2  x, vec2  y, vec2  a);"));
        s.append(TString("vec3  mix(vec3  x, vec3  y, vec3  a);"));
        s.append(TString("vec4  mix(vec4  x, vec4  y, vec4  a);"));

        s.append(TString("float step(float edge, float x);"));
        s.append(TString("vec2  step(vec2  edge, vec2  x);"));
        s.append(TString("vec3  step(vec3  edge, vec3  x);"));
        s.append(TString("vec4  step(vec4  edge, vec4  x);"));
        s.append(TString("vec2  step(float edge, vec2  x);"));
        s.append(TString("vec3  step(float edge, vec3  x);"));
        s.append(TString("vec4  step(float edge, vec4  x);"));

        s.append(TString("float smoothstep(float edge0, float edge1, float x);"));
        s.append(TString("vec2  smoothstep(vec2  edge0, vec2  edge1, vec2  x);"));
        s.append(TString("vec3  smoothstep(vec3  edge0, vec3  edge1, vec3  x);"));
        s.append(TString("vec4  smoothstep(vec4  edge0, vec4  edge1, vec4  x);"));
        s.append(TString("vec2  smoothstep(float edge0, float edge1, vec2  x);"));
        s.append(TString("vec3  smoothstep(float edge0, float edge1, vec3  x);"));
        s.append(TString("vec4  smoothstep(float edge0, float edge1, vec4  x);"));

        //
        // Geometric Functions.
        //
        s.append(TString("float length(float x);"));
        s.append(TString("float length(vec2  x);"));
        s.append(TString("float length(vec3  x);"));
        s.append(TString("float length(vec4  x);"));

        s.append(TString("float distance(float p0, float p1);"));
        s.append(TString("float distance(vec2  p0, vec2  p1);"));
        s.append(TString("float distance(vec3  p0, vec3  p1);"));
        s.append(TString("float distance(vec4  p0, vec4  p1);"));

        s.append(TString("float dot(float x, float y);"));
        s.append(TString("float dot(vec2  x, vec2  y);"));
        s.append(TString("float dot(vec3  x, vec3  y);"));
        s.append(TString("float dot(vec4  x, vec4  y);"));

        s.append(TString("vec3 cross(vec3 x, vec3 y);"));
        s.append(TString("float normalize(float x);"));
        s.append(TString("vec2  normalize(vec2  x);"));
        s.append(TString("vec3  normalize(vec3  x);"));
        s.append(TString("vec4  normalize(vec4  x);"));

        s.append(TString("float faceforward(float N, float I, float Nref);"));
        s.append(TString("vec2  faceforward(vec2  N, vec2  I, vec2  Nref);"));
        s.append(TString("vec3  faceforward(vec3  N, vec3  I, vec3  Nref);"));
        s.append(TString("vec4  faceforward(vec4  N, vec4  I, vec4  Nref);"));

        s.append(TString("float reflect(float I, float N);"));
        s.append(TString("vec2  reflect(vec2  I, vec2  N);"));
        s.append(TString("vec3  reflect(vec3  I, vec3  N);"));
        s.append(TString("vec4  reflect(vec4  I, vec4  N);"));

        s.append(TString("float refract(float I, float N, float eta);"));
        s.append(TString("vec2  refract(vec2  I, vec2  N, float eta);"));
        s.append(TString("vec3  refract(vec3  I, vec3  N, float eta);"));
        s.append(TString("vec4  refract(vec4  I, vec4  N, float eta);"));

        //
        // Matrix Functions.
        //
        s.append(TString("mat2 matrixCompMult(mat2 x, mat2 y);"));
        s.append(TString("mat3 matrixCompMult(mat3 x, mat3 y);"));
        s.append(TString("mat4 matrixCompMult(mat4 x, mat4 y);"));

        if (version >= 120) {
            s.append(TString("mat2   outerProduct(vec2 c, vec2 r);"));
            s.append(TString("mat3   outerProduct(vec3 c, vec3 r);"));
            s.append(TString("mat4   outerProduct(vec4 c, vec4 r);"));
            s.append(TString("mat2x3 outerProduct(vec3 c, vec2 r);"));
            s.append(TString("mat3x2 outerProduct(vec2 c, vec3 r);"));
            s.append(TString("mat2x4 outerProduct(vec4 c, vec2 r);"));
            s.append(TString("mat4x2 outerProduct(vec2 c, vec4 r);"));
            s.append(TString("mat3x4 outerProduct(vec4 c, vec3 r);"));
            s.append(TString("mat4x3 outerProduct(vec3 c, vec4 r);"));

            s.append(TString("mat2   transpose(mat2   m);"));
            s.append(TString("mat3   transpose(mat3   m);"));
            s.append(TString("mat4   transpose(mat4   m);"));
            s.append(TString("mat2x3 transpose(mat3x2 m);"));
            s.append(TString("mat3x2 transpose(mat2x3 m);"));
            s.append(TString("mat2x4 transpose(mat4x2 m);"));
            s.append(TString("mat4x2 transpose(mat2x4 m);"));
            s.append(TString("mat3x4 transpose(mat4x3 m);"));
            s.append(TString("mat4x3 transpose(mat3x4 m);"));

            if (version >= 150) {
                s.append(TString("float determinant(mat2 m);"));
                s.append(TString("float determinant(mat3 m);"));
                s.append(TString("float determinant(mat4 m);"));
                
                s.append(TString("mat2 inverse(mat2 m);"));
                s.append(TString("mat3 inverse(mat3 m);"));
                s.append(TString("mat4 inverse(mat4 m);"));
            }
        }

        //
        // Vector relational functions.
        //
        s.append(TString("bvec2 lessThan(vec2 x, vec2 y);"));
        s.append(TString("bvec3 lessThan(vec3 x, vec3 y);"));
        s.append(TString("bvec4 lessThan(vec4 x, vec4 y);"));

        s.append(TString("bvec2 lessThan(ivec2 x, ivec2 y);"));
        s.append(TString("bvec3 lessThan(ivec3 x, ivec3 y);"));
        s.append(TString("bvec4 lessThan(ivec4 x, ivec4 y);"));

        s.append(TString("bvec2 lessThanEqual(vec2 x, vec2 y);"));
        s.append(TString("bvec3 lessThanEqual(vec3 x, vec3 y);"));
        s.append(TString("bvec4 lessThanEqual(vec4 x, vec4 y);"));

        s.append(TString("bvec2 lessThanEqual(ivec2 x, ivec2 y);"));
        s.append(TString("bvec3 lessThanEqual(ivec3 x, ivec3 y);"));
        s.append(TString("bvec4 lessThanEqual(ivec4 x, ivec4 y);"));

        s.append(TString("bvec2 greaterThan(vec2 x, vec2 y);"));
        s.append(TString("bvec3 greaterThan(vec3 x, vec3 y);"));
        s.append(TString("bvec4 greaterThan(vec4 x, vec4 y);"));

        s.append(TString("bvec2 greaterThan(ivec2 x, ivec2 y);"));
        s.append(TString("bvec3 greaterThan(ivec3 x, ivec3 y);"));
        s.append(TString("bvec4 greaterThan(ivec4 x, ivec4 y);"));

        s.append(TString("bvec2 greaterThanEqual(vec2 x, vec2 y);"));
        s.append(TString("bvec3 greaterThanEqual(vec3 x, vec3 y);"));
        s.append(TString("bvec4 greaterThanEqual(vec4 x, vec4 y);"));

        s.append(TString("bvec2 greaterThanEqual(ivec2 x, ivec2 y);"));
        s.append(TString("bvec3 greaterThanEqual(ivec3 x, ivec3 y);"));
        s.append(TString("bvec4 greaterThanEqual(ivec4 x, ivec4 y);"));

        s.append(TString("bvec2 equal(vec2 x, vec2 y);"));
        s.append(TString("bvec3 equal(vec3 x, vec3 y);"));
        s.append(TString("bvec4 equal(vec4 x, vec4 y);"));

        s.append(TString("bvec2 equal(ivec2 x, ivec2 y);"));
        s.append(TString("bvec3 equal(ivec3 x, ivec3 y);"));
        s.append(TString("bvec4 equal(ivec4 x, ivec4 y);"));

        s.append(TString("bvec2 equal(bvec2 x, bvec2 y);"));
        s.append(TString("bvec3 equal(bvec3 x, bvec3 y);"));
        s.append(TString("bvec4 equal(bvec4 x, bvec4 y);"));

        s.append(TString("bvec2 notEqual(vec2 x, vec2 y);"));
        s.append(TString("bvec3 notEqual(vec3 x, vec3 y);"));
        s.append(TString("bvec4 notEqual(vec4 x, vec4 y);"));

        s.append(TString("bvec2 notEqual(ivec2 x, ivec2 y);"));
        s.append(TString("bvec3 notEqual(ivec3 x, ivec3 y);"));
        s.append(TString("bvec4 notEqual(ivec4 x, ivec4 y);"));

        s.append(TString("bvec2 notEqual(bvec2 x, bvec2 y);"));
        s.append(TString("bvec3 notEqual(bvec3 x, bvec3 y);"));
        s.append(TString("bvec4 notEqual(bvec4 x, bvec4 y);"));

        s.append(TString("bool any(bvec2 x);"));
        s.append(TString("bool any(bvec3 x);"));
        s.append(TString("bool any(bvec4 x);"));

        s.append(TString("bool all(bvec2 x);"));
        s.append(TString("bool all(bvec3 x);"));
        s.append(TString("bool all(bvec4 x);"));

        s.append(TString("bvec2 not(bvec2 x);"));
        s.append(TString("bvec3 not(bvec3 x);"));
        s.append(TString("bvec4 not(bvec4 x);"));

        //
        // Texture Functions.
        //
        s.append(TString("vec4 texture1D(sampler1D sampler, float coord);"));
        s.append(TString("vec4 texture1DProj(sampler1D sampler, vec2 coord);"));
        s.append(TString("vec4 texture1DProj(sampler1D sampler, vec4 coord);"));

        s.append(TString("vec4 texture2D(sampler2D sampler, vec2 coord);"));
        s.append(TString("vec4 texture2DProj(sampler2D sampler, vec3 coord);"));
        s.append(TString("vec4 texture2DProj(sampler2D sampler, vec4 coord);"));

        s.append(TString("vec4 texture3D(sampler3D sampler, vec3 coord);"));
        s.append(TString("vec4 texture3DProj(sampler3D sampler, vec4 coord);"));

        s.append(TString("vec4 textureCube(samplerCube sampler, vec3 coord);"));

        s.append(TString("vec4 shadow1D(sampler1DShadow sampler, vec3 coord);"));

        s.append(TString("vec4 shadow2D(sampler2DShadow sampler, vec3 coord);"));

        s.append(TString("vec4 shadow1DProj(sampler1DShadow sampler, vec4 coord);"));

        s.append(TString("vec4 shadow2DProj(sampler2DShadow sampler, vec4 coord);"));

        // ARB_texture_rectangle
        s.append(TString("vec4 texture2DRect(sampler2DRect sampler, vec2 coord);"));
        s.append(TString("vec4 texture2DRectProj(sampler2DRect sampler, vec3 coord);"));
        s.append(TString("vec4 texture2DRectProj(sampler2DRect sampler, vec4 coord);"));
        s.append(TString("vec4 shadow2DRect(sampler2DRectShadow sampler, vec3 coord);"));
        s.append(TString("vec4 shadow2DRectProj(sampler2DRectShadow sampler, vec4 coord);"));

        //
        // Noise functions.
        //
        s.append(TString("float noise1(float x);"));
        s.append(TString("float noise1(vec2  x);"));
        s.append(TString("float noise1(vec3  x);"));
        s.append(TString("float noise1(vec4  x);"));

        s.append(TString("vec2 noise2(float x);"));
        s.append(TString("vec2 noise2(vec2  x);"));
        s.append(TString("vec2 noise2(vec3  x);"));
        s.append(TString("vec2 noise2(vec4  x);"));

        s.append(TString("vec3 noise3(float x);"));
        s.append(TString("vec3 noise3(vec2  x);"));
        s.append(TString("vec3 noise3(vec3  x);"));
        s.append(TString("vec3 noise3(vec4  x);"));

        s.append(TString("vec4 noise4(float x);"));
        s.append(TString("vec4 noise4(vec2  x);"));
        s.append(TString("vec4 noise4(vec3  x);"));
        s.append(TString("vec4 noise4(vec4  x);"));

        s.append(TString("\n"));
    }
    {
        //============================================================================
        //
        // Prototypes for built-in functions seen by vertex shaders only.
        //
        //============================================================================

        TString& s = BuiltInFunctionsVertex;

        //
        // Geometric Functions.
        //
        s.append(TString("vec4 ftransform();"));

        //
        // Texture Functions.
        //
        s.append(TString("vec4 texture1DLod(sampler1D sampler, float coord, float lod);"));
        s.append(TString("vec4 texture1DProjLod(sampler1D sampler, vec2 coord, float lod);"));
        s.append(TString("vec4 texture1DProjLod(sampler1D sampler, vec4 coord, float lod);"));

        s.append(TString("vec4 texture2DLod(sampler2D sampler, vec2 coord, float lod);"));
        s.append(TString("vec4 texture2DProjLod(sampler2D sampler, vec3 coord, float lod);"));
        s.append(TString("vec4 texture2DProjLod(sampler2D sampler, vec4 coord, float lod);"));

        s.append(TString("vec4 texture3DLod(sampler3D sampler, vec3 coord, float lod);"));
        s.append(TString("vec4 texture3DProjLod(sampler3D sampler, vec4 coord, float lod);"));
        s.append(TString("vec4 textureCubeLod(samplerCube sampler, vec3 coord, float lod);"));

        s.append(TString("vec4 shadow1DLod(sampler1DShadow sampler, vec3 coord, float lod);"));
        s.append(TString("vec4 shadow2DLod(sampler2DShadow sampler, vec3 coord, float lod);"));
        s.append(TString("vec4 shadow1DProjLod(sampler1DShadow sampler, vec4 coord, float lod);"));
        s.append(TString("vec4 shadow2DProjLod(sampler2DShadow sampler, vec4 coord, float lod);"));

		s.append(TString("\n"));
    }
    {
        //============================================================================
        //
        // Prototypes for built-in functions seen by fragment shaders only.
        //
        //============================================================================

        TString& s = BuiltInFunctionsFragment;

        //
        // Texture Functions.
        //
		s.append(TString("vec4 texture1D(sampler1D sampler, float coord, float bias);"));
        s.append(TString("vec4 texture1DProj(sampler1D sampler, vec2 coord, float bias);"));
        s.append(TString("vec4 texture1DProj(sampler1D sampler, vec4 coord, float bias);"));

        s.append(TString("vec4 texture2D(sampler2D sampler, vec2 coord, float bias);"));
        s.append(TString("vec4 texture2DProj(sampler2D sampler, vec3 coord, float bias);"));
        s.append(TString("vec4 texture2DProj(sampler2D sampler, vec4 coord, float bias);"));

		s.append(TString("vec4 texture3D(sampler3D sampler, vec3 coord, float bias);"));
        s.append(TString("vec4 texture3DProj(sampler3D sampler, vec4 coord, float bias);"));
        s.append(TString("vec4 textureCube(samplerCube sampler, vec3 coord, float bias);"));

		s.append(TString("vec4 shadow1D(sampler1DShadow sampler, vec3 coord, float bias);"));
        s.append(TString("vec4 shadow2D(sampler2DShadow sampler, vec3 coord, float bias);"));
        s.append(TString("vec4 shadow1DProj(sampler1DShadow sampler, vec4 coord, float bias);"));
        s.append(TString("vec4 shadow2DProj(sampler2DShadow sampler, vec4 coord, float bias);"));

		s.append(TString("float dFdx(float p);"));
        s.append(TString("vec2  dFdx(vec2  p);"));
        s.append(TString("vec3  dFdx(vec3  p);"));
        s.append(TString("vec4  dFdx(vec4  p);"));

        s.append(TString("float dFdy(float p);"));
        s.append(TString("vec2  dFdy(vec2  p);"));
        s.append(TString("vec3  dFdy(vec3  p);"));
        s.append(TString("vec4  dFdy(vec4  p);"));

        s.append(TString("float fwidth(float p);"));
        s.append(TString("vec2  fwidth(vec2  p);"));
        s.append(TString("vec3  fwidth(vec3  p);"));
        s.append(TString("vec4  fwidth(vec4  p);"));

		s.append(TString("\n"));
    }
    {
        //============================================================================
        //
        // Standard Uniforms
        //
        //============================================================================

        TString& s = StandardUniforms;

        //
        // Depth range in window coordinates, p. 33
        //
        s.append(TString("struct gl_DepthRangeParameters {"));
        if (profile == EEsProfile) {
            s.append(TString("    highp float near;"));        // n
            s.append(TString("    highp float far;"));         // f
            s.append(TString("    highp float diff;"));        // f - n
        } else {
            s.append(TString("    float near;"));        // n
            s.append(TString("    float far;"));         // f
            s.append(TString("    float diff;"));        // f - n
        }
        s.append(TString("};"));
        s.append(TString("uniform gl_DepthRangeParameters gl_DepthRange;"));

        if (profile != EEsProfile && (version < FirstProfileVersion || profile == ECompatibilityProfile)) {
            //
            // Matrix state. p. 31, 32, 37, 39, 40.
            //
            s.append(TString("uniform mat4  gl_ModelViewMatrix;"));
            s.append(TString("uniform mat4  gl_ProjectionMatrix;"));
            s.append(TString("uniform mat4  gl_ModelViewProjectionMatrix;"));

            //
            // Derived matrix state that provides inverse and transposed versions
            // of the matrices above.
            //
            s.append(TString("uniform mat3  gl_NormalMatrix;"));

            s.append(TString("uniform mat4  gl_ModelViewMatrixInverse;"));
            s.append(TString("uniform mat4  gl_ProjectionMatrixInverse;"));
            s.append(TString("uniform mat4  gl_ModelViewProjectionMatrixInverse;"));

            s.append(TString("uniform mat4  gl_ModelViewMatrixTranspose;"));
            s.append(TString("uniform mat4  gl_ProjectionMatrixTranspose;"));
            s.append(TString("uniform mat4  gl_ModelViewProjectionMatrixTranspose;"));

            s.append(TString("uniform mat4  gl_ModelViewMatrixInverseTranspose;"));
            s.append(TString("uniform mat4  gl_ProjectionMatrixInverseTranspose;"));
            s.append(TString("uniform mat4  gl_ModelViewProjectionMatrixInverseTranspose;"));

            //
            // Normal scaling p. 39.
            //
            s.append(TString("uniform float gl_NormalScale;"));

            //
            // Point Size, p. 66, 67.
            //
            s.append(TString("struct gl_PointParameters {"));
            s.append(TString("    float size;"));
            s.append(TString("    float sizeMin;"));
            s.append(TString("    float sizeMax;"));
            s.append(TString("    float fadeThresholdSize;"));
            s.append(TString("    float distanceConstantAttenuation;"));
            s.append(TString("    float distanceLinearAttenuation;"));
            s.append(TString("    float distanceQuadraticAttenuation;"));
            s.append(TString("};"));

            s.append(TString("uniform gl_PointParameters gl_Point;"));

            //
            // Material State p. 50, 55.
            //
            s.append(TString("struct gl_MaterialParameters {"));
            s.append(TString("    vec4  emission;"));    // Ecm
            s.append(TString("    vec4  ambient;"));     // Acm
            s.append(TString("    vec4  diffuse;"));     // Dcm
            s.append(TString("    vec4  specular;"));    // Scm
            s.append(TString("    float shininess;"));   // Srm
            s.append(TString("};"));
            s.append(TString("uniform gl_MaterialParameters  gl_FrontMaterial;"));
            s.append(TString("uniform gl_MaterialParameters  gl_BackMaterial;"));

            //
            // Light State p 50, 53, 55.
            //

            s.append(TString("struct gl_LightSourceParameters {"));
            s.append(TString("    vec4  ambient;"));             // Acli
            s.append(TString("    vec4  diffuse;"));             // Dcli
            s.append(TString("    vec4  specular;"));            // Scli
            s.append(TString("    vec4  position;"));            // Ppli
            s.append(TString("    vec4  halfVector;"));          // Derived: Hi
            s.append(TString("    vec3  spotDirection;"));       // Sdli
            s.append(TString("    float spotExponent;"));        // Srli
            s.append(TString("    float spotCutoff;"));          // Crli
                                                                 // (range: [0.0,90.0], 180.0)
            s.append(TString("    float spotCosCutoff;"));       // Derived: cos(Crli)
                                                                 // (range: [1.0,0.0],-1.0)
            s.append(TString("    float constantAttenuation;")); // K0
            s.append(TString("    float linearAttenuation;"));   // K1
            s.append(TString("    float quadraticAttenuation;"));// K2
            s.append(TString("};"));


            s.append(TString("struct gl_LightModelParameters {"));
            s.append(TString("    vec4  ambient;"));       // Acs
            s.append(TString("};"));

            s.append(TString("uniform gl_LightModelParameters  gl_LightModel;"));

            //
            // Derived state from products of light and material.
            //

            s.append(TString("struct gl_LightModelProducts {"));
            s.append(TString("    vec4  sceneColor;"));     // Derived. Ecm + Acm * Acs
            s.append(TString("};"));

            s.append(TString("uniform gl_LightModelProducts gl_FrontLightModelProduct;"));
            s.append(TString("uniform gl_LightModelProducts gl_BackLightModelProduct;"));

            s.append(TString("struct gl_LightProducts {"));
            s.append(TString("    vec4  ambient;"));        // Acm * Acli
            s.append(TString("    vec4  diffuse;"));        // Dcm * Dcli
            s.append(TString("    vec4  specular;"));       // Scm * Scli
            s.append(TString("};"));

            //
            // Fog p. 161
            //
            s.append(TString("struct gl_FogParameters {"));
            s.append(TString("    vec4  color;"));
            s.append(TString("    float density;"));
            s.append(TString("    float start;"));
            s.append(TString("    float end;"));
            s.append(TString("    float scale;"));   //  1 / (gl_FogEnd - gl_FogStart)
            s.append(TString("};"));

            s.append(TString("uniform gl_FogParameters gl_Fog;"));
        }

        s.append(TString("\n"));
    }
    //============================================================================
    //
    // Vertex attributes, p. 19.
    //
    //============================================================================

    if (profile != EEsProfile) {
        TString& s = StandardVertexAttributes;

        if (version < 130) {
            s.append(TString("attribute vec4  gl_Color;"));
            s.append(TString("attribute vec4  gl_SecondaryColor;"));
            s.append(TString("attribute vec3  gl_Normal;"));
            s.append(TString("attribute vec4  gl_Vertex;"));
            s.append(TString("attribute vec4  gl_MultiTexCoord0;"));
            s.append(TString("attribute vec4  gl_MultiTexCoord1;"));
            s.append(TString("attribute vec4  gl_MultiTexCoord2;"));
            s.append(TString("attribute vec4  gl_MultiTexCoord3;"));
            s.append(TString("attribute vec4  gl_MultiTexCoord4;"));
            s.append(TString("attribute vec4  gl_MultiTexCoord5;"));
            s.append(TString("attribute vec4  gl_MultiTexCoord6;"));
            s.append(TString("attribute vec4  gl_MultiTexCoord7;"));
            s.append(TString("attribute float gl_FogCoord;"));
        } else if (version < FirstProfileVersion || profile == ECompatibilityProfile) {
            s.append(TString("in vec4  gl_Color;"));
            s.append(TString("in vec4  gl_SecondaryColor;"));
            s.append(TString("in vec3  gl_Normal;"));
            s.append(TString("in vec4  gl_Vertex;"));
            s.append(TString("in vec4  gl_MultiTexCoord0;"));
            s.append(TString("in vec4  gl_MultiTexCoord1;"));
            s.append(TString("in vec4  gl_MultiTexCoord2;"));
            s.append(TString("in vec4  gl_MultiTexCoord3;"));
            s.append(TString("in vec4  gl_MultiTexCoord4;"));
            s.append(TString("in vec4  gl_MultiTexCoord5;"));
            s.append(TString("in vec4  gl_MultiTexCoord6;"));
            s.append(TString("in vec4  gl_MultiTexCoord7;"));
            s.append(TString("in float gl_FogCoord;"));
        }

        s.append(TString("\n"));
    }
    //============================================================================
    //
    // Define the output varying interface from the vertex shader.
    //
    //============================================================================

    if (profile != EEsProfile) {
        TString& s = StandardVertexVaryings;

        if (version < 130) {
            s.append(TString("varying vec4  gl_FrontColor;"));
            s.append(TString("varying vec4  gl_BackColor;"));
            s.append(TString("varying vec4  gl_FrontSecondaryColor;"));
            s.append(TString("varying vec4  gl_BackSecondaryColor;"));
            s.append(TString("varying vec4  gl_TexCoord[];"));
            s.append(TString("varying float gl_FogFragCoord;"));
        } else if (version < FirstProfileVersion || profile == ECompatibilityProfile) {
            s.append(TString("out vec4  gl_FrontColor;"));
            s.append(TString("out vec4  gl_BackColor;"));
            s.append(TString("out vec4  gl_FrontSecondaryColor;"));
            s.append(TString("out vec4  gl_BackSecondaryColor;"));
            s.append(TString("out vec4  gl_TexCoord[];"));
            s.append(TString("out float gl_FogFragCoord;"));
        }

        s.append(TString("\n"));
    }
    {
        //============================================================================
        //
        // Define the input varying interface to the fragment shader.
        //
        //============================================================================

        if (profile != EEsProfile) {
            TString& s = StandardFragmentVaryings;
            if (version < 130) {
                s.append(TString("varying vec4  gl_Color;"));
                s.append(TString("varying vec4  gl_SecondaryColor;"));
                s.append(TString("varying vec4  gl_TexCoord[];"));
                s.append(TString("varying float gl_FogFragCoord;"));
            } else if (version < FirstProfileVersion || profile == ECompatibilityProfile) {
                s.append(TString("in vec4  gl_Color;"));
                s.append(TString("in vec4  gl_SecondaryColor;"));
                s.append(TString("in vec4  gl_TexCoord[];"));
                s.append(TString("in float gl_FogFragCoord;"));
            }

            s.append(TString("\n"));
        }
    }

    builtInStrings[EShLangFragment].push_back(BuiltInFunctions.c_str());
    builtInStrings[EShLangFragment].push_back(BuiltInFunctionsFragment);
    builtInStrings[EShLangFragment].push_back(StandardUniforms);
    builtInStrings[EShLangFragment].push_back(StandardFragmentVaryings);

    builtInStrings[EShLangVertex].push_back(BuiltInFunctions);
    builtInStrings[EShLangVertex].push_back(BuiltInFunctionsVertex);
    builtInStrings[EShLangVertex].push_back(StandardVertexVaryings);
    builtInStrings[EShLangVertex].push_back(StandardVertexAttributes);
    builtInStrings[EShLangVertex].push_back(StandardUniforms);
}


void TBuiltIns::initialize(const TBuiltInResource &resources, int version, EProfile profile, EShLanguage language)
{
    //
    // Initialize the context-dependent (resource-dependent) built-in strings for parsing.
    //
    TString StandardUniforms;

    {
        //============================================================================
        //
        // Standard Uniforms
        //
        //============================================================================

        TString& s = StandardUniforms;
		const int maxSize = 80;
        char builtInConstant[maxSize];

        //
        // Implementation dependent constants.  The example values below
        // are the minimum values allowed for these maximums.
        //

        if (profile == EEsProfile) {
            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxVertexAttribs = %d;", resources.maxVertexAttribs);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxVertexUniformVectors = %d;", resources.maxVertexUniformVectors);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxVertexTextureImageUnits = %d;", resources.maxVertexTextureImageUnits);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxCombinedTextureImageUnits = %d;", resources.maxCombinedTextureImageUnits);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxTextureImageUnits = %d;", resources.maxTextureImageUnits);
            s.append(TString(builtInConstant));
            
            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxFragmentUniformVectors = %d;", resources.maxFragmentUniformVectors);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxDrawBuffers = %d;", resources.maxDrawBuffers);
            s.append(TString(builtInConstant));

            if (version == 100) {
                snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxVaryingVectors = %d;", resources.maxVaryingVectors);
                s.append(TString(builtInConstant));
            } else {
                snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxVertexOutputVectors = %d;", resources.maxVertexOutputVectors);
                s.append(TString(builtInConstant));

                snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxFragmentInputVectors = %d;", resources.maxFragmentInputVectors);
                s.append(TString(builtInConstant));

                snprintf(builtInConstant, maxSize, "const mediump int  gl_MinProgramTexelOffset = %d;", resources.minProgramTexelOffset);
                s.append(TString(builtInConstant));
                
                snprintf(builtInConstant, maxSize, "const mediump int  gl_MaxProgramTexelOffset = %d;", resources.maxProgramTexelOffset);
                s.append(TString(builtInConstant));
            }
        } else {
            snprintf(builtInConstant, maxSize, "const int  gl_MaxVertexAttribs = %d;", resources.maxVertexAttribs);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const int  gl_MaxVertexTextureImageUnits = %d;", resources.maxVertexTextureImageUnits);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const int  gl_MaxCombinedTextureImageUnits = %d;", resources.maxCombinedTextureImageUnits);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const int  gl_MaxTextureImageUnits = %d;", resources.maxTextureImageUnits);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const int  gl_MaxDrawBuffers = %d;", resources.maxDrawBuffers);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const int  gl_MaxLights = %d;", resources.maxLights);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const int  gl_MaxClipPlanes = %d;", resources.maxClipPlanes);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const int  gl_MaxTextureUnits = %d;", resources.maxTextureUnits);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const int  gl_MaxTextureCoords = %d;", resources.maxTextureCoords);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const int  gl_MaxVertexUniformComponents = %d;", resources.maxVertexUniformComponents);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const int  gl_MaxVaryingFloats = %d;", resources.maxVaryingFloats);
            s.append(TString(builtInConstant));

            snprintf(builtInConstant, maxSize, "const int  gl_MaxFragmentUniformComponents = %d;", resources.maxFragmentUniformComponents);
            s.append(TString(builtInConstant));

            if (version < FirstProfileVersion || profile == ECompatibilityProfile) {
                //
                // OpenGL'uniform' state.  Page numbers are in reference to version
                // 1.4 of the OpenGL specification.
                //

                //
                // Matrix state. p. 31, 32, 37, 39, 40.
                //
                s.append(TString("uniform mat4  gl_TextureMatrix[gl_MaxTextureCoords];"));

                //
                // Derived matrix state that provides inverse and transposed versions
                // of the matrices above.
                //
                s.append(TString("uniform mat4  gl_TextureMatrixInverse[gl_MaxTextureCoords];"));

                s.append(TString("uniform mat4  gl_TextureMatrixTranspose[gl_MaxTextureCoords];"));

                s.append(TString("uniform mat4  gl_TextureMatrixInverseTranspose[gl_MaxTextureCoords];"));

                //
                // Clip planes p. 42.
                //
                s.append(TString("uniform vec4  gl_ClipPlane[gl_MaxClipPlanes];"));

                //
                // Light State p 50, 53, 55.
                //
                s.append(TString("uniform gl_LightSourceParameters  gl_LightSource[gl_MaxLights];"));

                //
                // Derived state from products of light.
                //
                s.append(TString("uniform gl_LightProducts gl_FrontLightProduct[gl_MaxLights];"));
                s.append(TString("uniform gl_LightProducts gl_BackLightProduct[gl_MaxLights];"));

                //
                // Textureg Environment and Generation, p. 152, p. 40-42.
                //
                s.append(TString("uniform vec4  gl_TextureEnvColor[gl_MaxTextureImageUnits];"));
                s.append(TString("uniform vec4  gl_EyePlaneS[gl_MaxTextureCoords];"));
                s.append(TString("uniform vec4  gl_EyePlaneT[gl_MaxTextureCoords];"));
                s.append(TString("uniform vec4  gl_EyePlaneR[gl_MaxTextureCoords];"));
                s.append(TString("uniform vec4  gl_EyePlaneQ[gl_MaxTextureCoords];"));
                s.append(TString("uniform vec4  gl_ObjectPlaneS[gl_MaxTextureCoords];"));
                s.append(TString("uniform vec4  gl_ObjectPlaneT[gl_MaxTextureCoords];"));
                s.append(TString("uniform vec4  gl_ObjectPlaneR[gl_MaxTextureCoords];"));
                s.append(TString("uniform vec4  gl_ObjectPlaneQ[gl_MaxTextureCoords];"));
            }
        }

        s.append(TString("\n"));
    }

    builtInStrings[EShLangFragment].push_back(StandardUniforms);
    builtInStrings[EShLangVertex].push_back(StandardUniforms);
}

void IdentifyBuiltIns(int version, EProfile profile, EShLanguage language, TSymbolTable& symbolTable)
{
    TPrecisionQualifier pq;
    //
    // First, insert some special built-in variables that are not in
    // the built-in text strings.
    //
    switch(language) {
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

        if (version < FirstProfileVersion || profile == ECompatibilityProfile) {
            pq = profile == EEsProfile ? EpqMedium : EpqNone;
            symbolTable.insert(*new TVariable(NewPoolTString("gl_FragColor"),   TType(EbtFloat, EvqFragColor, pq, 4)));
        }

        if (profile != EEsProfile || version > 100) {
            pq = profile == EEsProfile ? EpqHigh : EpqNone;
            symbolTable.insert(*new TVariable(NewPoolTString("gl_FragDepth"),   TType(EbtFloat, EvqFragDepth, pq, 1)));
        }
        break;

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
        // TODO: support these stages
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
    symbolTable.relateToOperator("ceil",         EOpCeil);
    symbolTable.relateToOperator("fract",        EOpFract);
    symbolTable.relateToOperator("min",          EOpMin);
    symbolTable.relateToOperator("max",          EOpMax);
    symbolTable.relateToOperator("clamp",        EOpClamp);
    symbolTable.relateToOperator("mix",          EOpMix);
    symbolTable.relateToOperator("step",         EOpStep);
    symbolTable.relateToOperator("smoothstep",   EOpSmoothStep);

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

    switch(language) {

    case EShLangVertex:
        break;

    case EShLangFragment:
        symbolTable.relateToOperator("dFdx",         EOpDPdx);
        symbolTable.relateToOperator("dFdy",         EOpDPdy);
        symbolTable.relateToOperator("fwidth",       EOpFwidth);

        break;

	default: assert(false && "Language not supported");
    }
}

void IdentifyBuiltIns(int version, EProfile profile, EShLanguage language, TSymbolTable& symbolTable, const TBuiltInResource &resources)
{
    //
    // Set resource-specific built-ins not yet handled.
    //
    switch(language) {

    case EShLangFragment:
        // Set up gl_FragData based on current array size.
        if (version < FirstProfileVersion || profile == ECompatibilityProfile) {
            TPrecisionQualifier pq = profile == EEsProfile ? EpqMedium : EpqNone;
            TType fragData(EbtFloat, EvqFragColor, 4);
            TArraySizes arraySizes = NewPoolTArraySizes();
            arraySizes->push_back(resources.maxDrawBuffers);
            fragData.setArraySizes(arraySizes);
            symbolTable.insert(*new TVariable(NewPoolTString("gl_FragData"),    fragData));
        }
        break;

	default: break;
    }
}
