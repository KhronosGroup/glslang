/*
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
*/
/* Based on
ANSI C grammar, Lex specification

In 1985, Jeff Lee published this Lex specification together with a Yacc
grammar for the April 30, 1985 ANSI C draft.  Tom Stockfisch reposted
both to net.sources in 1987; that original, as mentioned in the answer
to question 17.25 of the comp.lang.c FAQ, can be ftp'ed from ftp.uu.net,
file usenet/net.sources/ansi.c.grammar.Z.

I intend to keep this version as close to the current C Standard grammar
as possible; please let me know if you discover discrepancies.

Jutta Degener, 1995
*/

D           [0-9]
L           [a-zA-Z_]
H           [a-fA-F0-9]
E           [Ee][+-]?{D}+
O           [0-7]
U           [uU]
F           [fF]
LF          [lL][fF]

/* TODO: double literals, which will likely require pre-processor rework */
/* TODO: unsigned int literals, which will likely require pre-processor rework */

%option nounput
%{
#include <stdio.h>
#include <stdlib.h>
#include "ParseHelper.h"
#include "glslang_tab.cpp.h"

int PaReservedWord();
int PaIdentOrType(TString& id, TParseContext&, TSymbol*&);
int PaIdentOrReserved(bool reserved, TParseContext&, int line, const char* text, YYSTYPE* pyylval);
int PaES30ReservedFromGLSL(int version, TParseContext& pc, int line, const char* text, YYSTYPE* pyylval, int keyword);
int PaPrecisionKeyword(TParseContext&, int line, const char* text, YYSTYPE* pyylval, int keyword);
int PaMatNxM(TParseContext&, int line, const char* text, YYSTYPE* pyylval, int keyword);
int PaDMat(TParseContext&, int line, const char* text, YYSTYPE* pyylval, int keyword);

/* windows only pragma */
#ifdef _MSC_VER
#pragma warning(disable : 4102)
#endif

int yy_input(char* buf, int max_size);

#ifdef _WIN32
    TSourceLoc yylineno;
    extern int yyparse(TParseContext&);
    #define YY_DECL int yylex(YYSTYPE* pyylval, TParseContext& parseContext)
#else
    extern int yyparse(void*);
    #define YY_DECL int yylex(YYSTYPE* pyylval, void* parseContextLocal)
    #define parseContext (*((TParseContext*)(parseContextLocal)))		
#endif

#define YY_INPUT(buf,result,max_size) (result = yy_input(buf, max_size))

%}

%option noyywrap
%option never-interactive
%option outfile="gen_glslang.cpp"
%x FIELDS


%%
<*>"//"[^\n]*"\n"     { /* ?? carriage and/or line-feed? */ };

"attribute"    {  pyylval->lex.line = yylineno; return(ATTRIBUTE); }  // TODO ES 30 reserved
"const"        {  pyylval->lex.line = yylineno; return(CONST); }
"uniform"      {  pyylval->lex.line = yylineno; return(UNIFORM); }
"varying"      {  pyylval->lex.line = yylineno; return(VARYING); }    // TODO ES 30 reserved
"buffer"       {  pyylval->lex.line = yylineno; return(BUFFER); }
"shared"       {  pyylval->lex.line = yylineno; return(SHARED); }

"coherent"     {  return PaES30ReservedFromGLSL(420, parseContext, yylineno, yytext, pyylval, COHERENT); }
"volatile"     {  if (parseContext.profile == EEsProfile || parseContext.version < 420) 
                      return PaReservedWord();    
                  else
                       pyylval->lex.line = yylineno; return(VOLATILE); 
               }
"restrict"     {  return PaES30ReservedFromGLSL(420, parseContext, yylineno, yytext, pyylval, RESTRICT); }
"readonly"     {  return PaES30ReservedFromGLSL(420, parseContext, yylineno, yytext, pyylval, READONLY); }
"writeonly"    {  return PaES30ReservedFromGLSL(420, parseContext, yylineno, yytext, pyylval, WRITEONLY); }

"layout"       {  pyylval->lex.line = yylineno; return(LAYOUT); }

"centroid"      {  pyylval->lex.line = yylineno; return(CENTROID); }
"flat"          {  pyylval->lex.line = yylineno; return(FLAT); }
"smooth"        {  pyylval->lex.line = yylineno; return(SMOOTH); }
"noperspective" {  pyylval->lex.line = yylineno; return(NOPERSPECTIVE); }

"patch"        {  return PaES30ReservedFromGLSL(400, parseContext, yylineno, yytext, pyylval, PATCH); }
"sample"       {  return PaES30ReservedFromGLSL(400, parseContext, yylineno, yytext, pyylval, SAMPLE); }

"break"        {  pyylval->lex.line = yylineno; return(BREAK); }
"continue"     {  pyylval->lex.line = yylineno; return(CONTINUE); }
"do"           {  pyylval->lex.line = yylineno; return(DO); }
"for"          {  pyylval->lex.line = yylineno; return(FOR); }
"while"        {  pyylval->lex.line = yylineno; return(WHILE); }
"switch"       {  pyylval->lex.line = yylineno; return(SWITCH); }
"case"         {  pyylval->lex.line = yylineno; return(CASE); }
"default"      {  pyylval->lex.line = yylineno; return(DEFAULT); }

"if"           {  pyylval->lex.line = yylineno; return(IF); }
"else"         {  pyylval->lex.line = yylineno; return(ELSE); }

"subroutine"   {  return PaES30ReservedFromGLSL(400, parseContext, yylineno, yytext, pyylval, SUBROUTINE); }

"in"           {  pyylval->lex.line = yylineno; return(IN); }
"out"          {  pyylval->lex.line = yylineno; return(OUT); }
"inout"        {  pyylval->lex.line = yylineno; return(INOUT); }

"precise"      {  pyylval->lex.line = yylineno; return(PRECISE); }
"invariant"    {  pyylval->lex.line = yylineno; return(INVARIANT); }

"highp"        {  return PaPrecisionKeyword(parseContext, yylineno, yytext, pyylval, HIGH_PRECISION); }
"mediump"      {  return PaPrecisionKeyword(parseContext, yylineno, yytext, pyylval, MEDIUM_PRECISION); }
"lowp"         {  return PaPrecisionKeyword(parseContext, yylineno, yytext, pyylval, LOW_PRECISION); }
"precision"    {  return PaPrecisionKeyword(parseContext, yylineno, yytext, pyylval, PRECISION); }

"float"        {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(FLOAT); }
"double"       {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(DOUBLE); }
"int"          {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(INT); }
"uint"         {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UINT); }
"void"         {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(VOID); }
"bool"         {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(BOOL); }
"true"         {  pyylval->lex.line = yylineno; pyylval->lex.b = true;  return(BOOLCONSTANT); }
"false"        {  pyylval->lex.line = yylineno; pyylval->lex.b = false; return(BOOLCONSTANT); }

"discard"      {  pyylval->lex.line = yylineno; return(DISCARD); }
"return"       {  pyylval->lex.line = yylineno; return(RETURN); }

"atomic_uint"  { return PaES30ReservedFromGLSL(420, parseContext, yylineno, yytext, pyylval, ATOMIC_UINT); }

"mat2"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(MAT2); }
"mat3"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(MAT3); }
"mat4"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(MAT4); }

"mat2x2"       { return PaMatNxM(parseContext, yylineno, yytext, pyylval, MAT2X2); }
"mat2x3"       { return PaMatNxM(parseContext, yylineno, yytext, pyylval, MAT2X3); }
"mat2x4"       { return PaMatNxM(parseContext, yylineno, yytext, pyylval, MAT2X4); }
"mat3x2"       { return PaMatNxM(parseContext, yylineno, yytext, pyylval, MAT3X2); }
"mat3x3"       { return PaMatNxM(parseContext, yylineno, yytext, pyylval, MAT3X3); }
"mat3x4"       { return PaMatNxM(parseContext, yylineno, yytext, pyylval, MAT3X4); }
"mat4x2"       { return PaMatNxM(parseContext, yylineno, yytext, pyylval, MAT4X2); }
"mat4x3"       { return PaMatNxM(parseContext, yylineno, yytext, pyylval, MAT4X3); }
"mat4x4"       { return PaMatNxM(parseContext, yylineno, yytext, pyylval, MAT4X4); }
"dmat2"        { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT2);   }
"dmat3"        { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT3);   }
"dmat4"        { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT4);   }
"dmat2x2"      { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT2X2); }
"dmat2x3"      { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT2X3); }
"dmat2x4"      { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT2X4); }
"dmat3x2"      { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT3X2); }
"dmat3x3"      { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT3X3); }
"dmat3x4"      { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT3X4); }
"dmat4x2"      { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT4X2); }
"dmat4x3"      { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT4X3); }
"dmat4x4"      { return   PaDMat(parseContext, yylineno, yytext, pyylval, DMAT4X4); }

"vec2"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (VEC2); }
"vec3"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (VEC3); }
"vec4"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (VEC4); }
"dvec2"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (DVEC2); }
"dvec3"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (DVEC3); }
"dvec4"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (DVEC4); }
"ivec2"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (IVEC2); }
"ivec3"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (IVEC3); }
"ivec4"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (IVEC4); }
"uvec2"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (UVEC2); }
"uvec3"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (UVEC3); }
"uvec4"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (UVEC4); }
"bvec2"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (BVEC2); }
"bvec3"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (BVEC3); }
"bvec4"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return (BVEC4); }

"sampler1D"       {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLER1D; }
"sampler2D"       {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLER2D; }
"sampler3D"       {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLER3D; }
"samplerCube"     {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLERCUBE; }
"sampler1DShadow" {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLER1DSHADOW; }
"sampler2DShadow" {  pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLER2DSHADOW; }

"sampler2DRect"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLER2DRECT; }
"isampler2DRect"       { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return ISAMPLER2DRECT; }
"usampler2DRect"       { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return USAMPLER2DRECT; }
"sampler2DRectShadow"  { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLER2DRECTSHADOW; }

"samplerCubeShadow"    { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLERCUBESHADOW; }
"sampler1DArray"       { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLER1DARRAY; }
"sampler2DArray"       { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLER2DARRAY; }
"samplerCubeArray"     { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLERCUBEARRAY; }
"sampler1DArrayShadow" { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLER1DARRAYSHADOW; }
"sampler2DArrayShadow" { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLER2DARRAYSHADOW; }
"samplerCubeArrayShadow" { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return SAMPLERCUBEARRAYSHADOW; }
"isampler1D"           { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return ISAMPLER1D; }
"isampler2D"           { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return ISAMPLER2D; }
"isampler3D"           { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return ISAMPLER3D; }
"isamplerCube"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return ISAMPLERCUBE; }
"isamplerCubeArray"    { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return ISAMPLERCUBEARRAY; }
"isampler1DArray"      { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return ISAMPLER1DARRAY; }
"isampler2DArray"      { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return ISAMPLER2DARRAY; }
"usampler1D"           { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return USAMPLER1D; }
"usampler2D"           { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return USAMPLER2D; }
"usampler3D"           { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return USAMPLER3D; }
"usamplerCube"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return USAMPLERCUBE; }
"usamplerCubeArray"    { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return USAMPLERCUBEARRAY; }
"usampler1DArray"      { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return USAMPLER1DARRAY; }
"usampler2DArray"      { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return USAMPLER2DARRAY; }

"samplerBuffer"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(SAMPLERBUFFER); }
"isamplerBuffer"       { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(ISAMPLERBUFFER); }
"usamplerBuffer"       { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(USAMPLERBUFFER); }
"sampler2DMS"          { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(SAMPLER2DMS); }
"isampler2DMS"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(ISAMPLER2DMS); }
"usampler2DMS"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(USAMPLER2DMS); }
"sampler2DMSArray"     { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(SAMPLER2DMSARRAY); }
"isampler2DMSArray"    { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(ISAMPLER2DMSARRAY); }
"usampler2DMSArray"    { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(USAMPLER2DMSARRAY); }
"image1D"              { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IMAGE1D); }
"iimage1D"             { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IIMAGE1D); }
"uimage1D"             { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UIMAGE1D); }
"image2D"              { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IMAGE2D); }
"iimage2D"             { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IIMAGE2D); }
"uimage2D"             { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UIMAGE2D); }
"image3D"              { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IMAGE3D); }
"iimage3D"             { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IIMAGE3D); }
"uimage3D"             { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UIMAGE3D); }
"image2DRect"          { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IMAGE2DRECT); }
"iimage2DRect"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IIMAGE2DRECT); }
"uimage2DRect"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UIMAGE2DRECT); }
"imageCube"            { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IMAGECUBE); }
"iimageCube"           { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IIMAGECUBE); }
"uimageCube"           { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UIMAGECUBE); }
"imageBuffer"          { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IMAGEBUFFER); }
"iimageBuffer"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IIMAGEBUFFER); }
"uimageBuffer"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UIMAGEBUFFER); }
"image1DArray"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IMAGE1DARRAY); }
"iimage1DArray"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IIMAGE1DARRAY); }
"uimage1DArray"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UIMAGE1DARRAY); }
"image2DArray"         { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IMAGE2DARRAY); }
"iimage2DArray"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IIMAGE2DARRAY); }
"uimage2DArray"        { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UIMAGE2DARRAY); }
"imageCubeArray"       { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IMAGECUBEARRAY); }
"iimageCubeArray"      { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IIMAGECUBEARRAY); }
"uimageCubeArray"      { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UIMAGECUBEARRAY); }
"image2DMS"            { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IMAGE2DMS); }
"iimage2DMS"           { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IIMAGE2DMS); }
"uimage2DMS"           { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UIMAGE2DMS); }
"image2DMSArray"       { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IMAGE2DMSARRAY); }
"iimage2DMSArray"      { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(IIMAGE2DMSARRAY); }
"uimage2DMSArray"      { pyylval->lex.line = yylineno; parseContext.lexAfterType = true; return(UIMAGE2DMSARRAY); }

"struct"       {  pyylval->lex.line = yylineno; return(STRUCT); }

"asm"          {  PaReservedWord(); return 0; }

"class"        {  PaReservedWord(); return 0; }
"union"        {  PaReservedWord(); return 0; }
"enum"         {  PaReservedWord(); return 0; }
"typedef"      {  PaReservedWord(); return 0; }
"template"     {  PaReservedWord(); return 0; }
"this"         {  PaReservedWord(); return 0; }
"packed"       {  PaReservedWord(); return 0; }

"resource"     {  if (parseContext.profile == EEsProfile && parseContext.version >= 300 ||
                      parseContext.profile != EEsProfile && parseContext.version >= 420)    
                          return PaReservedWord();
               }

"goto"         {  PaReservedWord(); return 0; }

"inline"       {  PaReservedWord(); return 0; }
"noinline"     {  PaReservedWord(); return 0; }
"public"       {  PaReservedWord(); return 0; }
"static"       {  PaReservedWord(); return 0; }
"extern"       {  PaReservedWord(); return 0; }
"external"     {  PaReservedWord(); return 0; }
"interface"    {  PaReservedWord(); return 0; }

"long"         {  PaReservedWord(); return 0; }
"short"        {  PaReservedWord(); return 0; }
"half"         {  PaReservedWord(); return 0; }
"fixed"        {  PaReservedWord(); return 0; }
"unsigned"     {  PaReservedWord(); return 0; }

"superp"       {  bool reserved = (parseContext.profile == EEsProfile || parseContext.version >= 130);
                  return PaIdentOrReserved(reserved, parseContext, yylineno, yytext, pyylval); }

"input"        {  PaReservedWord(); return 0; }
"output"       {  PaReservedWord(); return 0; }

"hvec2"        {  PaReservedWord(); return 0; }
"hvec3"        {  PaReservedWord(); return 0; }
"hvec4"        {  PaReservedWord(); return 0; }
"fvec2"        {  PaReservedWord(); return 0; }
"fvec3"        {  PaReservedWord(); return 0; }
"fvec4"        {  PaReservedWord(); return 0; }

"sampler3DRect" { PaReservedWord(); return 0; }

"filter"       {  PaReservedWord(); return 0; }

"sizeof"       {  PaReservedWord(); return 0; }
"cast"         {  PaReservedWord(); return 0; }

"namespace"    {  PaReservedWord(); return 0; }
"using"        {  PaReservedWord(); return 0; }

{L}({L}|{D})*       {
   pyylval->lex.line = yylineno;
   pyylval->lex.string = NewPoolTString(yytext);
   return PaIdentOrType(*pyylval->lex.string, parseContext, pyylval->lex.symbol);
}

0[xX]{H}+         { pyylval->lex.line = yylineno; pyylval->lex.i = strtol(yytext, 0, 0); return(INTCONSTANT); }
0{O}+             { pyylval->lex.line = yylineno; pyylval->lex.i = strtol(yytext, 0, 0); return(INTCONSTANT); }
0{D}+             { pyylval->lex.line = yylineno; parseContext.error(yylineno, "Invalid Octal number.", yytext, "", ""); parseContext.recover(); return 0;}
{D}+              { pyylval->lex.line = yylineno; pyylval->lex.i = strtol(yytext, 0, 0); return(INTCONSTANT); }

0[xX]{H}+{U}      { pyylval->lex.line = yylineno; pyylval->lex.i = strtol(yytext, 0, 0); return(UINTCONSTANT); }
0{O}+{U}          { pyylval->lex.line = yylineno; pyylval->lex.i = strtol(yytext, 0, 0); return(UINTCONSTANT); }
0{D}+{U}          { pyylval->lex.line = yylineno; parseContext.error(yylineno, "Invalid Octal number.", yytext, "", ""); parseContext.recover(); return 0;}
{D}+{U}           { pyylval->lex.line = yylineno; pyylval->lex.i = strtol(yytext, 0, 0); return(UINTCONSTANT); }

{D}+{F}               { pyylval->lex.line = yylineno; pyylval->lex.f = static_cast<float>(atof(yytext)); return(FLOATCONSTANT); }
{D}+{E}{F}?           { pyylval->lex.line = yylineno; pyylval->lex.f = static_cast<float>(atof(yytext)); return(FLOATCONSTANT); }
{D}+"."{D}*({E})?{F}? { pyylval->lex.line = yylineno; pyylval->lex.f = static_cast<float>(atof(yytext)); return(FLOATCONSTANT); }
"."{D}+({E})?{F}?     { pyylval->lex.line = yylineno; pyylval->lex.f = static_cast<float>(atof(yytext)); return(FLOATCONSTANT); }

{D}+{LF}              { pyylval->lex.line = yylineno; pyylval->lex.d = atof(yytext); return(DOUBLECONSTANT); }
{D}+{E}{LF}           { pyylval->lex.line = yylineno; pyylval->lex.d = atof(yytext); return(DOUBLECONSTANT); }
{D}+"."{D}*({E})?{LF} { pyylval->lex.line = yylineno; pyylval->lex.d = atof(yytext); return(DOUBLECONSTANT); }
"."{D}+({E})?{LF}     { pyylval->lex.line = yylineno; pyylval->lex.d = atof(yytext); return(DOUBLECONSTANT); }

"/*"            {  int ret = PaParseComment(pyylval->lex.line, parseContext); if (!ret) return ret; }

"+="            {  pyylval->lex.line = yylineno; return(ADD_ASSIGN); }
"-="            {  pyylval->lex.line = yylineno; return(SUB_ASSIGN); }
"*="            {  pyylval->lex.line = yylineno; return(MUL_ASSIGN); }
"/="            {  pyylval->lex.line = yylineno; return(DIV_ASSIGN); }
"%="            {  pyylval->lex.line = yylineno; return(MOD_ASSIGN); }
"<<="           {  pyylval->lex.line = yylineno; return(LEFT_ASSIGN); }
">>="           {  pyylval->lex.line = yylineno; return(RIGHT_ASSIGN); }
"&="            {  pyylval->lex.line = yylineno; return(AND_ASSIGN); }
"^="            {  pyylval->lex.line = yylineno; return(XOR_ASSIGN); }
"|="            {  pyylval->lex.line = yylineno; return(OR_ASSIGN); }

"++"            {  pyylval->lex.line = yylineno; return(INC_OP); }
"--"            {  pyylval->lex.line = yylineno; return(DEC_OP); }
"&&"            {  pyylval->lex.line = yylineno; return(AND_OP); }
"||"            {  pyylval->lex.line = yylineno; return(OR_OP); }
"^^"            {  pyylval->lex.line = yylineno; return(XOR_OP); }
"<="            {  pyylval->lex.line = yylineno; return(LE_OP); }
">="            {  pyylval->lex.line = yylineno; return(GE_OP); }
"=="            {  pyylval->lex.line = yylineno; return(EQ_OP); }
"!="            {  pyylval->lex.line = yylineno; return(NE_OP); }
"<<"            {  pyylval->lex.line = yylineno; return(LEFT_OP); }
">>"            {  pyylval->lex.line = yylineno; return(RIGHT_OP); }
";"         {  pyylval->lex.line = yylineno; parseContext.lexAfterType = false; return(SEMICOLON); }
("{"|"<%")      {  pyylval->lex.line = yylineno; parseContext.lexAfterType = false; return(LEFT_BRACE); }
("}"|"%>")      {  pyylval->lex.line = yylineno; return(RIGHT_BRACE); }
","         {  pyylval->lex.line = yylineno; if (parseContext.inTypeParen) parseContext.lexAfterType = false; return(COMMA); }
":"         {  pyylval->lex.line = yylineno; return(COLON); }
"="         {  pyylval->lex.line = yylineno; parseContext.lexAfterType = false; return(EQUAL); }
"("         {  pyylval->lex.line = yylineno; parseContext.lexAfterType = false; parseContext.inTypeParen = true; return(LEFT_PAREN); }
")"         {  pyylval->lex.line = yylineno; parseContext.inTypeParen = false; return(RIGHT_PAREN); }
("["|"<:")      {  pyylval->lex.line = yylineno; return(LEFT_BRACKET); }
("]"|":>")      {  pyylval->lex.line = yylineno; return(RIGHT_BRACKET); }
"."         { BEGIN(FIELDS);  return(DOT); }
"!"         {  pyylval->lex.line = yylineno; return(BANG); }
"-"         {  pyylval->lex.line = yylineno; return(DASH); }
"~"         {  pyylval->lex.line = yylineno; return(TILDE); }
"+"         {  pyylval->lex.line = yylineno; return(PLUS); }
"*"         {  pyylval->lex.line = yylineno; return(STAR); }
"/"         {  pyylval->lex.line = yylineno; return(SLASH); }
"%"         {  pyylval->lex.line = yylineno; return(PERCENT); }
"<"         {  pyylval->lex.line = yylineno; return(LEFT_ANGLE); }
">"         {  pyylval->lex.line = yylineno; return(RIGHT_ANGLE); }
"|"         {  pyylval->lex.line = yylineno; return(VERTICAL_BAR); }
"^"         {  pyylval->lex.line = yylineno; return(CARET); }
"&"         {  pyylval->lex.line = yylineno; return(AMPERSAND); }
"?"         {  pyylval->lex.line = yylineno; return(QUESTION); }

<FIELDS>{L}({L}|{D})* {
BEGIN(INITIAL);
    pyylval->lex.line = yylineno;
    pyylval->lex.string = NewPoolTString(yytext);
    return FIELD_SELECTION; }
<FIELDS>[ \t\v\f\r] {}

[ \t\v\n\f\r]   {  }
<*><<EOF>> { (&parseContext)->AfterEOF = true; yy_delete_buffer(YY_CURRENT_BUFFER); yyterminate();}
<*>.    { parseContext.infoSink.info << "FLEX: Unknown char " << yytext << "\n";
          return 0; }

%%


//Including Pre-processor.
extern "C" {
  #include "./preprocessor/preprocess.h"
}

//
// The YY_INPUT macro just calls this.  Maybe this could be just put into
// the macro directly.
//

int yy_input(char* buf, int max_size)
{
     char *char_token =NULL;
     int len;

    if ((len = yylex_CPP(buf, max_size)) == 0)
        return 0;
    if (len >= max_size)
        YY_FATAL_ERROR( "input buffer overflow, can't enlarge buffer because scanner uses REJECT" );

    buf[len] = ' ';
	return len+1;
}


//
// Parse an array of strings using yyparse.  We set up globals used by
// yywrap.
//
// Returns 0 for success, as per yyparse().
//
int PaParseStrings(char* argv[], int strLen[], int argc, TParseContext& parseContextLocal)
{
    int argv0len;

    ScanFromString(argv[0]);

    //Storing the Current Compiler Parse context into the cpp structure.
	cpp->pC = (void*)&parseContextLocal;
	
	if (!argv || argc == 0)
        return 1;

    for (int i = 0; i < argc; ++i) {
        if (! argv[i]) {
            parseContextLocal.error(0, "Null shader source string", "", "");
            parseContextLocal.recover();
            return 1;
        }
    }

    if (! strLen) {
        argv0len = (int) strlen(argv[0]);
        strLen   = &argv0len;
    }
    yyrestart(0);
    (&parseContextLocal)->AfterEOF = false;
    cpp->PaWhichStr = 0;
    cpp->PaArgv     = argv;
    cpp->PaArgc     = argc;
    cpp->PaStrLen   = strLen;
    cpp->notAVersionToken = 0;
    yylineno   = 1;

    // TODO: CPP: a shader containing nothing but white space and comments is valid, even though it has no parse tokens
    int len = 0;
    while (argv[0][len] == ' '  ||
           argv[0][len] == '\t' ||
           argv[0][len] == '\n' ||
           argv[0][len] == '\r')
        if (++len >= strLen[0])
            return 0;

    if (*cpp->PaStrLen > 0) {
        int ret;
        #ifdef _WIN32
            ret = yyparse(parseContextLocal);
        #else
            ret = yyparse((void*)(&parseContextLocal));
        #endif
        if (cpp->CompileError == 1 || parseContextLocal.recoveredFromError || parseContextLocal.numErrors > 0)
             return 1;
        else
             return 0;
    } else
        return 0;
}

void yyerror(char *s)
{
    TParseContext& pc = *((TParseContext *)cpp->pC);

    if (pc.AfterEOF) {
        if (cpp->tokensBeforeEOF == 1) {
            GlobalParseContext->error(yylineno, "", "pre-mature EOF", s, "");
            GlobalParseContext->recover();
        }
    } else {
        GlobalParseContext->error(yylineno, "", yytext, s, "");
        GlobalParseContext->recover();
    }
}

int PaReservedWord()
{
    GlobalParseContext->error(yylineno, "Reserved word.", yytext, "", "");
    GlobalParseContext->recover();

    return 0;
}

int PaIdentOrType(TString& id, TParseContext& parseContextLocal, TSymbol*& symbol)
{
    symbol = parseContextLocal.symbolTable.find(id);
    if (parseContextLocal.lexAfterType == false && symbol) {
        if (TVariable* variable = symbol->getAsVariable()) {
            if (variable->isUserType()) {
                parseContextLocal.lexAfterType = true;
                return TYPE_NAME;
            }
        }
    }

    return IDENTIFIER;
}

int PaIdentOrReserved(bool reserved, TParseContext& pc, int line, const char* text, YYSTYPE* pyylval)
{
    if (reserved)
        PaReservedWord();

    pyylval->lex.line = line;
    pyylval->lex.string = NewPoolTString(text);
    pc.infoSink.info.message(EPrefixWarning, pyylval->lex.string->c_str(), yylineno);
    pc.infoSink.info.message(EPrefixWarning, "using future reserved keyword", yylineno);

    return PaIdentOrType(*pyylval->lex.string, pc, pyylval->lex.symbol);
}

int PaES30ReservedFromGLSL(int version, TParseContext& pc, int line, const char* text, YYSTYPE* pyylval, int keyword)
{
    if (pc.profile == EEsProfile && pc.version < 300 ||
        pc.profile != EEsProfile && pc.version < version) {
            pyylval->lex.line = yylineno;
            pyylval->lex.string = NewPoolTString(yytext);
            pc.infoSink.info.message(EPrefixWarning, pyylval->lex.string->c_str(), yylineno);
            pc.infoSink.info.message(EPrefixWarning, "future reserved word in ES 300 and keyword in GLSL", yylineno);

            return PaIdentOrType(*pyylval->lex.string, pc, pyylval->lex.symbol);
    } else if (pc.profile == EEsProfile && pc.version >= 300)

        return PaReservedWord();
    else {
        pyylval->lex.line = yylineno;

        return keyword;
    }
}

int PaPrecisionKeyword(TParseContext& pc, int line, const char* text, YYSTYPE* pyylval, int keyword)
{
    if (pc.profile == EEsProfile || pc.version >= 130)
        return keyword;

    pyylval->lex.line = line;
    pyylval->lex.string = NewPoolTString(text);
    pc.infoSink.info.message(EPrefixWarning, pyylval->lex.string->c_str(), yylineno);
    pc.infoSink.info.message(EPrefixWarning, "using ES precision qualifier keyword", yylineno);

    return PaIdentOrType(*pyylval->lex.string, pc, pyylval->lex.symbol);
}

int PaMatNxM(TParseContext& pc, int line, const char* text, YYSTYPE* pyylval, int keyword)
{
    if (pc.version > 110)
        return keyword;

    pyylval->lex.line = line;
    pyylval->lex.string = NewPoolTString(text);
    pc.infoSink.info.message(EPrefixWarning, pyylval->lex.string->c_str(), yylineno);
    pc.infoSink.info.message(EPrefixWarning, "using future non-square matrix type keyword", yylineno);

    return PaIdentOrType(*pyylval->lex.string, pc, pyylval->lex.symbol);
}

int PaDMat(TParseContext& pc, int line, const char* text, YYSTYPE* pyylval, int keyword)
{
    if (pc.profile == EEsProfile && pc.version >= 300) {
        PaReservedWord();
        return 0;
    }

    if (pc.profile != EEsProfile && pc.version >= 400)
        return keyword;

    pyylval->lex.line = line;
    pyylval->lex.string = NewPoolTString(text);
    pc.infoSink.info.message(EPrefixWarning, pyylval->lex.string->c_str(), yylineno);
    pc.infoSink.info.message(EPrefixWarning, "using future type keyword", yylineno);

    return PaIdentOrType(*pyylval->lex.string, pc, pyylval->lex.symbol);
}

int PaParseComment(int& lineno, TParseContext& parseContextLocal)
{
    int transitionFlag = 0;
    int nextChar;

    while (transitionFlag != 2) {
        nextChar = yyinput();
        if (nextChar == '\n')
             lineno++;
        switch (nextChar) {
        case '*' :
            transitionFlag = 1;
            break;
        case '/' :  /* if star is the previous character, then it is the end of comment */
            if (transitionFlag == 1) {
                return 1 ;
            }
            break;
        case EOF :
            /* Raise error message here */
            parseContextLocal.error(yylineno, "End of shader found before end of comment.", "", "", "");
            GlobalParseContext->recover();
            return YY_NULL;
        default :  /* Any other character will be a part of the comment */
            transitionFlag = 0;
        }
    }
    return 1;
}

extern "C" {

void CPPDebugLogMsg(const char *msg)
{
    TParseContext& pc = *((TParseContext *)cpp->pC);

    pc.infoSink.debug.message(EPrefixNone, msg);
}

void CPPWarningToInfoLog(const char *msg)
{
    TParseContext& pc = *((TParseContext *)cpp->pC);

    pc.infoSink.info.message(EPrefixWarning, msg, yylineno);
}

void CPPShInfoLogMsg(const char *msg)
{
    TParseContext& pc = *((TParseContext *)cpp->pC);

    pc.error(yylineno,"", "",msg,"");
    GlobalParseContext->recover();
}

void CPPErrorToInfoLog(const char *msg)
{
    TParseContext& pc = *((TParseContext *)cpp->pC);

    pc.error(yylineno, "CPP error:", "", msg, "");
    GlobalParseContext->recover();
}

void SetLineNumber(int line)
{
    yylineno &= ~SourceLocLineMask;
    yylineno |= line;
}

void SetStringNumber(int string)
{
    yylineno = (string << SourceLocStringShift) | (yylineno & SourceLocLineMask);
}

int GetStringNumber(void)
{
    return yylineno >> 16;
}

int GetLineNumber(void)
{
    return yylineno & SourceLocLineMask;
}

void IncLineNumber(void)
{
    if ((yylineno & SourceLocLineMask) <= SourceLocLineMask)
        ++yylineno;
}

void DecLineNumber(void)
{
    if ((yylineno & SourceLocLineMask) > 0)
        --yylineno;
}

void HandlePragma(const char **tokens, int numTokens)
{
    TParseContext& pc = *((TParseContext *)cpp->pC);

    if (!strcmp(tokens[0], "optimize")) {
        if (numTokens != 4) {
            CPPShInfoLogMsg("optimize pragma syntax is incorrect");
            return;
        }

        if (strcmp(tokens[1], "(")) {
            CPPShInfoLogMsg("\"(\" expected after 'optimize' keyword");
            return;
        }

        if (!strcmp(tokens[2], "on"))
            pc.contextPragma.optimize = true;
        else if (!strcmp(tokens[2], "off"))
            pc.contextPragma.optimize = false;
        else {
            CPPShInfoLogMsg("\"on\" or \"off\" expected after '(' for 'optimize' pragma");
            return;
        }

        if (strcmp(tokens[3], ")")) {
            CPPShInfoLogMsg("\")\" expected to end 'optimize' pragma");
            return;
        }
    } else if (!strcmp(tokens[0], "debug")) {
        if (numTokens != 4) {
            CPPShInfoLogMsg("debug pragma syntax is incorrect");
            return;
        }

        if (strcmp(tokens[1], "(")) {
            CPPShInfoLogMsg("\"(\" expected after 'debug' keyword");
            return;
        }

        if (!strcmp(tokens[2], "on"))
            pc.contextPragma.debug = true;
        else if (!strcmp(tokens[2], "off"))
            pc.contextPragma.debug = false;
        else {
            CPPShInfoLogMsg("\"on\" or \"off\" expected after '(' for 'debug' pragma");
            return;
        }

        if (strcmp(tokens[3], ")")) {
            CPPShInfoLogMsg("\")\" expected to end 'debug' pragma");
            return;
        }
    } else {

#ifdef PRAGMA_TABLE
        //
        // implementation specific pragma
        // use parseContext.contextPragma.pragmaTable to store the information about pragma
        // For now, just ignore the pragma that the implementation cannot recognize
        // An Example of one such implementation for a pragma that has a syntax like
        // #pragma pragmaname(pragmavalue)
        // This implementation stores the current pragmavalue against the pragma name in pragmaTable.
        //
        if (numTokens == 4 && !strcmp(tokens[1], "(") && !strcmp(tokens[3], ")")) {
            TPragmaTable& pragmaTable = parseContext.contextPragma.pragmaTable;
            TPragmaTable::iterator iter;
            iter = pragmaTable.find(TString(tokens[0]));
            if (iter != pragmaTable.end()) {
                iter->second = tokens[2];
            } else {
                pragmaTable[tokens[0]] = tokens[2];
            }
        } else if (numTokens >= 2) {
            TPragmaTable& pragmaTable = parseContext.contextPragma.pragmaTable;
            TPragmaTable::iterator iter;
            iter = pragmaTable.find(TString(tokens[0]));
            if (iter != pragmaTable.end()) {
                iter->second = tokens[1];
            } else {
                pragmaTable[tokens[0]] = tokens[1];
            }
        }
#endif // PRAGMA_TABLE
    }
}

void StoreStr(const char *string)
{
    TParseContext& pc = *((TParseContext *)cpp->pC);

    TString strSrc;
    strSrc = TString(string);

    pc.HashErrMsg = pc.HashErrMsg + " " + strSrc;
}

const char* GetStrfromTStr(void)
{
    TParseContext& pc = *((TParseContext *)cpp->pC);

    cpp->ErrMsg = pc.HashErrMsg.c_str();
    return cpp->ErrMsg;
}

void ResetTString(void)
{
    TParseContext& pc = *((TParseContext *)cpp->pC);

    pc.HashErrMsg = "";
}

void SetVersion(int version)
{
    // called by the CPP, but this functionality is currently
    // taken over by ScanVersion() before parsing starts

    // CPP should still report errors in semantics
}

void SetProfile(EProfile profile)
{
    // called by the CPP, but this functionality is currently
    // taken over by ScanVersion() before parsing starts

    // CPP should still report errors in semantics
}

TBehavior GetBehavior(const char* behavior)
{
    if (!strcmp("require", behavior))
        return EBhRequire;
    else if (!strcmp("enable", behavior))
        return EBhEnable;
    else if (!strcmp("disable", behavior))
        return EBhDisable;
    else if (!strcmp("warn", behavior))
        return EBhWarn;
    else {
        CPPShInfoLogMsg((TString("behavior '") + behavior + "' is not supported").c_str());
        return EBhDisable;
    }
}

void updateExtensionBehavior(const char* extName, const char* behavior)
{
    TParseContext& pc = *((TParseContext *)cpp->pC);
    TBehavior behaviorVal = GetBehavior(behavior);
    TMap<TString, TBehavior>:: iterator iter;
    TString msg;

    // special cased for all extension
    if (!strcmp(extName, "all")) {
        if (behaviorVal == EBhRequire || behaviorVal == EBhEnable) {
            CPPShInfoLogMsg("extension 'all' cannot have 'require' or 'enable' behavior");
            return;
        } else {
            for (iter = pc.extensionBehavior.begin(); iter != pc.extensionBehavior.end(); ++iter)
                iter->second = behaviorVal;
        }
    } else {
        iter = pc.extensionBehavior.find(TString(extName));
        if (iter == pc.extensionBehavior.end()) {
            switch (behaviorVal) {
            case EBhRequire:
                CPPShInfoLogMsg((TString("extension '") + extName + "' is not supported").c_str());
                break;
            case EBhEnable:
            case EBhWarn:
            case EBhDisable:
                msg = TString("extension '") + extName + "' is not supported";
                pc.infoSink.info.message(EPrefixWarning, msg.c_str(), yylineno);
                break;
            }
            return;
        } else
            iter->second = behaviorVal;
    }
}

}  // extern "C"

void ResetFlex()
{
    yy_start = 1;
}
