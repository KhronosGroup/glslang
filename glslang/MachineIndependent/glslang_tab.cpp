/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 44 "MachineIndependent/glslang.y"


/* Based on:
ANSI C Yacc grammar

In 1985, Jeff Lee published his Yacc grammar (which is accompanied by a
matching Lex specification) for the April 30, 1985 draft version of the
ANSI C standard.  Tom Stockfisch reposted it to net.sources in 1987; that
original, as mentioned in the answer to question 17.25 of the comp.lang.c
FAQ, can be ftp'ed from ftp.uu.net, file usenet/net.sources/ansi.c.grammar.Z.

I intend to keep this version as close to the current C Standard grammar as
possible; please let me know if you discover discrepancies.

Jutta Degener, 1995
*/

#include "SymbolTable.h"
#include "ParseHelper.h"
#include "../Public/ShaderLang.h"
#include "attribute.h"

using namespace glslang;


#line 97 "MachineIndependent/glslang_tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "glslang_tab.cpp.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONST = 3,                      /* CONST  */
  YYSYMBOL_BOOL = 4,                       /* BOOL  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_UINT = 6,                       /* UINT  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_BVEC2 = 8,                      /* BVEC2  */
  YYSYMBOL_BVEC3 = 9,                      /* BVEC3  */
  YYSYMBOL_BVEC4 = 10,                     /* BVEC4  */
  YYSYMBOL_IVEC2 = 11,                     /* IVEC2  */
  YYSYMBOL_IVEC3 = 12,                     /* IVEC3  */
  YYSYMBOL_IVEC4 = 13,                     /* IVEC4  */
  YYSYMBOL_UVEC2 = 14,                     /* UVEC2  */
  YYSYMBOL_UVEC3 = 15,                     /* UVEC3  */
  YYSYMBOL_UVEC4 = 16,                     /* UVEC4  */
  YYSYMBOL_VEC2 = 17,                      /* VEC2  */
  YYSYMBOL_VEC3 = 18,                      /* VEC3  */
  YYSYMBOL_VEC4 = 19,                      /* VEC4  */
  YYSYMBOL_MAT2 = 20,                      /* MAT2  */
  YYSYMBOL_MAT3 = 21,                      /* MAT3  */
  YYSYMBOL_MAT4 = 22,                      /* MAT4  */
  YYSYMBOL_MAT2X2 = 23,                    /* MAT2X2  */
  YYSYMBOL_MAT2X3 = 24,                    /* MAT2X3  */
  YYSYMBOL_MAT2X4 = 25,                    /* MAT2X4  */
  YYSYMBOL_MAT3X2 = 26,                    /* MAT3X2  */
  YYSYMBOL_MAT3X3 = 27,                    /* MAT3X3  */
  YYSYMBOL_MAT3X4 = 28,                    /* MAT3X4  */
  YYSYMBOL_MAT4X2 = 29,                    /* MAT4X2  */
  YYSYMBOL_MAT4X3 = 30,                    /* MAT4X3  */
  YYSYMBOL_MAT4X4 = 31,                    /* MAT4X4  */
  YYSYMBOL_SAMPLER2D = 32,                 /* SAMPLER2D  */
  YYSYMBOL_SAMPLER3D = 33,                 /* SAMPLER3D  */
  YYSYMBOL_SAMPLERCUBE = 34,               /* SAMPLERCUBE  */
  YYSYMBOL_SAMPLER2DSHADOW = 35,           /* SAMPLER2DSHADOW  */
  YYSYMBOL_SAMPLERCUBESHADOW = 36,         /* SAMPLERCUBESHADOW  */
  YYSYMBOL_SAMPLER2DARRAY = 37,            /* SAMPLER2DARRAY  */
  YYSYMBOL_SAMPLER2DARRAYSHADOW = 38,      /* SAMPLER2DARRAYSHADOW  */
  YYSYMBOL_ISAMPLER2D = 39,                /* ISAMPLER2D  */
  YYSYMBOL_ISAMPLER3D = 40,                /* ISAMPLER3D  */
  YYSYMBOL_ISAMPLERCUBE = 41,              /* ISAMPLERCUBE  */
  YYSYMBOL_ISAMPLER2DARRAY = 42,           /* ISAMPLER2DARRAY  */
  YYSYMBOL_USAMPLER2D = 43,                /* USAMPLER2D  */
  YYSYMBOL_USAMPLER3D = 44,                /* USAMPLER3D  */
  YYSYMBOL_USAMPLERCUBE = 45,              /* USAMPLERCUBE  */
  YYSYMBOL_USAMPLER2DARRAY = 46,           /* USAMPLER2DARRAY  */
  YYSYMBOL_SAMPLER = 47,                   /* SAMPLER  */
  YYSYMBOL_SAMPLERSHADOW = 48,             /* SAMPLERSHADOW  */
  YYSYMBOL_TEXTURE2D = 49,                 /* TEXTURE2D  */
  YYSYMBOL_TEXTURE3D = 50,                 /* TEXTURE3D  */
  YYSYMBOL_TEXTURECUBE = 51,               /* TEXTURECUBE  */
  YYSYMBOL_TEXTURE2DARRAY = 52,            /* TEXTURE2DARRAY  */
  YYSYMBOL_ITEXTURE2D = 53,                /* ITEXTURE2D  */
  YYSYMBOL_ITEXTURE3D = 54,                /* ITEXTURE3D  */
  YYSYMBOL_ITEXTURECUBE = 55,              /* ITEXTURECUBE  */
  YYSYMBOL_ITEXTURE2DARRAY = 56,           /* ITEXTURE2DARRAY  */
  YYSYMBOL_UTEXTURE2D = 57,                /* UTEXTURE2D  */
  YYSYMBOL_UTEXTURE3D = 58,                /* UTEXTURE3D  */
  YYSYMBOL_UTEXTURECUBE = 59,              /* UTEXTURECUBE  */
  YYSYMBOL_UTEXTURE2DARRAY = 60,           /* UTEXTURE2DARRAY  */
  YYSYMBOL_ATTRIBUTE = 61,                 /* ATTRIBUTE  */
  YYSYMBOL_VARYING = 62,                   /* VARYING  */
  YYSYMBOL_FLOATE5M2_T = 63,               /* FLOATE5M2_T  */
  YYSYMBOL_FLOATE4M3_T = 64,               /* FLOATE4M3_T  */
  YYSYMBOL_BFLOAT16_T = 65,                /* BFLOAT16_T  */
  YYSYMBOL_FLOAT16_T = 66,                 /* FLOAT16_T  */
  YYSYMBOL_FLOAT32_T = 67,                 /* FLOAT32_T  */
  YYSYMBOL_DOUBLE = 68,                    /* DOUBLE  */
  YYSYMBOL_FLOAT64_T = 69,                 /* FLOAT64_T  */
  YYSYMBOL_INT64_T = 70,                   /* INT64_T  */
  YYSYMBOL_UINT64_T = 71,                  /* UINT64_T  */
  YYSYMBOL_INT32_T = 72,                   /* INT32_T  */
  YYSYMBOL_UINT32_T = 73,                  /* UINT32_T  */
  YYSYMBOL_INT16_T = 74,                   /* INT16_T  */
  YYSYMBOL_UINT16_T = 75,                  /* UINT16_T  */
  YYSYMBOL_INT8_T = 76,                    /* INT8_T  */
  YYSYMBOL_UINT8_T = 77,                   /* UINT8_T  */
  YYSYMBOL_I64VEC2 = 78,                   /* I64VEC2  */
  YYSYMBOL_I64VEC3 = 79,                   /* I64VEC3  */
  YYSYMBOL_I64VEC4 = 80,                   /* I64VEC4  */
  YYSYMBOL_U64VEC2 = 81,                   /* U64VEC2  */
  YYSYMBOL_U64VEC3 = 82,                   /* U64VEC3  */
  YYSYMBOL_U64VEC4 = 83,                   /* U64VEC4  */
  YYSYMBOL_I32VEC2 = 84,                   /* I32VEC2  */
  YYSYMBOL_I32VEC3 = 85,                   /* I32VEC3  */
  YYSYMBOL_I32VEC4 = 86,                   /* I32VEC4  */
  YYSYMBOL_U32VEC2 = 87,                   /* U32VEC2  */
  YYSYMBOL_U32VEC3 = 88,                   /* U32VEC3  */
  YYSYMBOL_U32VEC4 = 89,                   /* U32VEC4  */
  YYSYMBOL_I16VEC2 = 90,                   /* I16VEC2  */
  YYSYMBOL_I16VEC3 = 91,                   /* I16VEC3  */
  YYSYMBOL_I16VEC4 = 92,                   /* I16VEC4  */
  YYSYMBOL_U16VEC2 = 93,                   /* U16VEC2  */
  YYSYMBOL_U16VEC3 = 94,                   /* U16VEC3  */
  YYSYMBOL_U16VEC4 = 95,                   /* U16VEC4  */
  YYSYMBOL_I8VEC2 = 96,                    /* I8VEC2  */
  YYSYMBOL_I8VEC3 = 97,                    /* I8VEC3  */
  YYSYMBOL_I8VEC4 = 98,                    /* I8VEC4  */
  YYSYMBOL_U8VEC2 = 99,                    /* U8VEC2  */
  YYSYMBOL_U8VEC3 = 100,                   /* U8VEC3  */
  YYSYMBOL_U8VEC4 = 101,                   /* U8VEC4  */
  YYSYMBOL_DVEC2 = 102,                    /* DVEC2  */
  YYSYMBOL_DVEC3 = 103,                    /* DVEC3  */
  YYSYMBOL_DVEC4 = 104,                    /* DVEC4  */
  YYSYMBOL_DMAT2 = 105,                    /* DMAT2  */
  YYSYMBOL_DMAT3 = 106,                    /* DMAT3  */
  YYSYMBOL_DMAT4 = 107,                    /* DMAT4  */
  YYSYMBOL_BF16VEC2 = 108,                 /* BF16VEC2  */
  YYSYMBOL_BF16VEC3 = 109,                 /* BF16VEC3  */
  YYSYMBOL_BF16VEC4 = 110,                 /* BF16VEC4  */
  YYSYMBOL_FE5M2VEC2 = 111,                /* FE5M2VEC2  */
  YYSYMBOL_FE5M2VEC3 = 112,                /* FE5M2VEC3  */
  YYSYMBOL_FE5M2VEC4 = 113,                /* FE5M2VEC4  */
  YYSYMBOL_FE4M3VEC2 = 114,                /* FE4M3VEC2  */
  YYSYMBOL_FE4M3VEC3 = 115,                /* FE4M3VEC3  */
  YYSYMBOL_FE4M3VEC4 = 116,                /* FE4M3VEC4  */
  YYSYMBOL_F16VEC2 = 117,                  /* F16VEC2  */
  YYSYMBOL_F16VEC3 = 118,                  /* F16VEC3  */
  YYSYMBOL_F16VEC4 = 119,                  /* F16VEC4  */
  YYSYMBOL_F16MAT2 = 120,                  /* F16MAT2  */
  YYSYMBOL_F16MAT3 = 121,                  /* F16MAT3  */
  YYSYMBOL_F16MAT4 = 122,                  /* F16MAT4  */
  YYSYMBOL_F32VEC2 = 123,                  /* F32VEC2  */
  YYSYMBOL_F32VEC3 = 124,                  /* F32VEC3  */
  YYSYMBOL_F32VEC4 = 125,                  /* F32VEC4  */
  YYSYMBOL_F32MAT2 = 126,                  /* F32MAT2  */
  YYSYMBOL_F32MAT3 = 127,                  /* F32MAT3  */
  YYSYMBOL_F32MAT4 = 128,                  /* F32MAT4  */
  YYSYMBOL_F64VEC2 = 129,                  /* F64VEC2  */
  YYSYMBOL_F64VEC3 = 130,                  /* F64VEC3  */
  YYSYMBOL_F64VEC4 = 131,                  /* F64VEC4  */
  YYSYMBOL_F64MAT2 = 132,                  /* F64MAT2  */
  YYSYMBOL_F64MAT3 = 133,                  /* F64MAT3  */
  YYSYMBOL_F64MAT4 = 134,                  /* F64MAT4  */
  YYSYMBOL_DMAT2X2 = 135,                  /* DMAT2X2  */
  YYSYMBOL_DMAT2X3 = 136,                  /* DMAT2X3  */
  YYSYMBOL_DMAT2X4 = 137,                  /* DMAT2X4  */
  YYSYMBOL_DMAT3X2 = 138,                  /* DMAT3X2  */
  YYSYMBOL_DMAT3X3 = 139,                  /* DMAT3X3  */
  YYSYMBOL_DMAT3X4 = 140,                  /* DMAT3X4  */
  YYSYMBOL_DMAT4X2 = 141,                  /* DMAT4X2  */
  YYSYMBOL_DMAT4X3 = 142,                  /* DMAT4X3  */
  YYSYMBOL_DMAT4X4 = 143,                  /* DMAT4X4  */
  YYSYMBOL_F16MAT2X2 = 144,                /* F16MAT2X2  */
  YYSYMBOL_F16MAT2X3 = 145,                /* F16MAT2X3  */
  YYSYMBOL_F16MAT2X4 = 146,                /* F16MAT2X4  */
  YYSYMBOL_F16MAT3X2 = 147,                /* F16MAT3X2  */
  YYSYMBOL_F16MAT3X3 = 148,                /* F16MAT3X3  */
  YYSYMBOL_F16MAT3X4 = 149,                /* F16MAT3X4  */
  YYSYMBOL_F16MAT4X2 = 150,                /* F16MAT4X2  */
  YYSYMBOL_F16MAT4X3 = 151,                /* F16MAT4X3  */
  YYSYMBOL_F16MAT4X4 = 152,                /* F16MAT4X4  */
  YYSYMBOL_F32MAT2X2 = 153,                /* F32MAT2X2  */
  YYSYMBOL_F32MAT2X3 = 154,                /* F32MAT2X3  */
  YYSYMBOL_F32MAT2X4 = 155,                /* F32MAT2X4  */
  YYSYMBOL_F32MAT3X2 = 156,                /* F32MAT3X2  */
  YYSYMBOL_F32MAT3X3 = 157,                /* F32MAT3X3  */
  YYSYMBOL_F32MAT3X4 = 158,                /* F32MAT3X4  */
  YYSYMBOL_F32MAT4X2 = 159,                /* F32MAT4X2  */
  YYSYMBOL_F32MAT4X3 = 160,                /* F32MAT4X3  */
  YYSYMBOL_F32MAT4X4 = 161,                /* F32MAT4X4  */
  YYSYMBOL_F64MAT2X2 = 162,                /* F64MAT2X2  */
  YYSYMBOL_F64MAT2X3 = 163,                /* F64MAT2X3  */
  YYSYMBOL_F64MAT2X4 = 164,                /* F64MAT2X4  */
  YYSYMBOL_F64MAT3X2 = 165,                /* F64MAT3X2  */
  YYSYMBOL_F64MAT3X3 = 166,                /* F64MAT3X3  */
  YYSYMBOL_F64MAT3X4 = 167,                /* F64MAT3X4  */
  YYSYMBOL_F64MAT4X2 = 168,                /* F64MAT4X2  */
  YYSYMBOL_F64MAT4X3 = 169,                /* F64MAT4X3  */
  YYSYMBOL_F64MAT4X4 = 170,                /* F64MAT4X4  */
  YYSYMBOL_ATOMIC_UINT = 171,              /* ATOMIC_UINT  */
  YYSYMBOL_ACCSTRUCTNV = 172,              /* ACCSTRUCTNV  */
  YYSYMBOL_ACCSTRUCTEXT = 173,             /* ACCSTRUCTEXT  */
  YYSYMBOL_RAYQUERYEXT = 174,              /* RAYQUERYEXT  */
  YYSYMBOL_FCOOPMATNV = 175,               /* FCOOPMATNV  */
  YYSYMBOL_ICOOPMATNV = 176,               /* ICOOPMATNV  */
  YYSYMBOL_UCOOPMATNV = 177,               /* UCOOPMATNV  */
  YYSYMBOL_COOPMAT = 178,                  /* COOPMAT  */
  YYSYMBOL_COOPVECNV = 179,                /* COOPVECNV  */
  YYSYMBOL_VECTOR = 180,                   /* VECTOR  */
  YYSYMBOL_HITOBJECTNV = 181,              /* HITOBJECTNV  */
  YYSYMBOL_HITOBJECTATTRNV = 182,          /* HITOBJECTATTRNV  */
  YYSYMBOL_HITOBJECTEXT = 183,             /* HITOBJECTEXT  */
  YYSYMBOL_HITOBJECTATTREXT = 184,         /* HITOBJECTATTREXT  */
  YYSYMBOL_TENSORLAYOUTNV = 185,           /* TENSORLAYOUTNV  */
  YYSYMBOL_TENSORVIEWNV = 186,             /* TENSORVIEWNV  */
  YYSYMBOL_TENSORARM = 187,                /* TENSORARM  */
  YYSYMBOL_SAMPLERCUBEARRAY = 188,         /* SAMPLERCUBEARRAY  */
  YYSYMBOL_SAMPLERCUBEARRAYSHADOW = 189,   /* SAMPLERCUBEARRAYSHADOW  */
  YYSYMBOL_ISAMPLERCUBEARRAY = 190,        /* ISAMPLERCUBEARRAY  */
  YYSYMBOL_USAMPLERCUBEARRAY = 191,        /* USAMPLERCUBEARRAY  */
  YYSYMBOL_SAMPLER1D = 192,                /* SAMPLER1D  */
  YYSYMBOL_SAMPLER1DARRAY = 193,           /* SAMPLER1DARRAY  */
  YYSYMBOL_SAMPLER1DARRAYSHADOW = 194,     /* SAMPLER1DARRAYSHADOW  */
  YYSYMBOL_ISAMPLER1D = 195,               /* ISAMPLER1D  */
  YYSYMBOL_SAMPLER1DSHADOW = 196,          /* SAMPLER1DSHADOW  */
  YYSYMBOL_SAMPLER2DRECT = 197,            /* SAMPLER2DRECT  */
  YYSYMBOL_SAMPLER2DRECTSHADOW = 198,      /* SAMPLER2DRECTSHADOW  */
  YYSYMBOL_ISAMPLER2DRECT = 199,           /* ISAMPLER2DRECT  */
  YYSYMBOL_USAMPLER2DRECT = 200,           /* USAMPLER2DRECT  */
  YYSYMBOL_SAMPLERBUFFER = 201,            /* SAMPLERBUFFER  */
  YYSYMBOL_ISAMPLERBUFFER = 202,           /* ISAMPLERBUFFER  */
  YYSYMBOL_USAMPLERBUFFER = 203,           /* USAMPLERBUFFER  */
  YYSYMBOL_SAMPLER2DMS = 204,              /* SAMPLER2DMS  */
  YYSYMBOL_ISAMPLER2DMS = 205,             /* ISAMPLER2DMS  */
  YYSYMBOL_USAMPLER2DMS = 206,             /* USAMPLER2DMS  */
  YYSYMBOL_SAMPLER2DMSARRAY = 207,         /* SAMPLER2DMSARRAY  */
  YYSYMBOL_ISAMPLER2DMSARRAY = 208,        /* ISAMPLER2DMSARRAY  */
  YYSYMBOL_USAMPLER2DMSARRAY = 209,        /* USAMPLER2DMSARRAY  */
  YYSYMBOL_SAMPLEREXTERNALOES = 210,       /* SAMPLEREXTERNALOES  */
  YYSYMBOL_SAMPLEREXTERNAL2DY2YEXT = 211,  /* SAMPLEREXTERNAL2DY2YEXT  */
  YYSYMBOL_ISAMPLER1DARRAY = 212,          /* ISAMPLER1DARRAY  */
  YYSYMBOL_USAMPLER1D = 213,               /* USAMPLER1D  */
  YYSYMBOL_USAMPLER1DARRAY = 214,          /* USAMPLER1DARRAY  */
  YYSYMBOL_F16SAMPLER1D = 215,             /* F16SAMPLER1D  */
  YYSYMBOL_F16SAMPLER2D = 216,             /* F16SAMPLER2D  */
  YYSYMBOL_F16SAMPLER3D = 217,             /* F16SAMPLER3D  */
  YYSYMBOL_F16SAMPLER2DRECT = 218,         /* F16SAMPLER2DRECT  */
  YYSYMBOL_F16SAMPLERCUBE = 219,           /* F16SAMPLERCUBE  */
  YYSYMBOL_F16SAMPLER1DARRAY = 220,        /* F16SAMPLER1DARRAY  */
  YYSYMBOL_F16SAMPLER2DARRAY = 221,        /* F16SAMPLER2DARRAY  */
  YYSYMBOL_F16SAMPLERCUBEARRAY = 222,      /* F16SAMPLERCUBEARRAY  */
  YYSYMBOL_F16SAMPLERBUFFER = 223,         /* F16SAMPLERBUFFER  */
  YYSYMBOL_F16SAMPLER2DMS = 224,           /* F16SAMPLER2DMS  */
  YYSYMBOL_F16SAMPLER2DMSARRAY = 225,      /* F16SAMPLER2DMSARRAY  */
  YYSYMBOL_F16SAMPLER1DSHADOW = 226,       /* F16SAMPLER1DSHADOW  */
  YYSYMBOL_F16SAMPLER2DSHADOW = 227,       /* F16SAMPLER2DSHADOW  */
  YYSYMBOL_F16SAMPLER1DARRAYSHADOW = 228,  /* F16SAMPLER1DARRAYSHADOW  */
  YYSYMBOL_F16SAMPLER2DARRAYSHADOW = 229,  /* F16SAMPLER2DARRAYSHADOW  */
  YYSYMBOL_F16SAMPLER2DRECTSHADOW = 230,   /* F16SAMPLER2DRECTSHADOW  */
  YYSYMBOL_F16SAMPLERCUBESHADOW = 231,     /* F16SAMPLERCUBESHADOW  */
  YYSYMBOL_F16SAMPLERCUBEARRAYSHADOW = 232, /* F16SAMPLERCUBEARRAYSHADOW  */
  YYSYMBOL_IMAGE1D = 233,                  /* IMAGE1D  */
  YYSYMBOL_IIMAGE1D = 234,                 /* IIMAGE1D  */
  YYSYMBOL_UIMAGE1D = 235,                 /* UIMAGE1D  */
  YYSYMBOL_IMAGE2D = 236,                  /* IMAGE2D  */
  YYSYMBOL_IIMAGE2D = 237,                 /* IIMAGE2D  */
  YYSYMBOL_UIMAGE2D = 238,                 /* UIMAGE2D  */
  YYSYMBOL_IMAGE3D = 239,                  /* IMAGE3D  */
  YYSYMBOL_IIMAGE3D = 240,                 /* IIMAGE3D  */
  YYSYMBOL_UIMAGE3D = 241,                 /* UIMAGE3D  */
  YYSYMBOL_IMAGE2DRECT = 242,              /* IMAGE2DRECT  */
  YYSYMBOL_IIMAGE2DRECT = 243,             /* IIMAGE2DRECT  */
  YYSYMBOL_UIMAGE2DRECT = 244,             /* UIMAGE2DRECT  */
  YYSYMBOL_IMAGECUBE = 245,                /* IMAGECUBE  */
  YYSYMBOL_IIMAGECUBE = 246,               /* IIMAGECUBE  */
  YYSYMBOL_UIMAGECUBE = 247,               /* UIMAGECUBE  */
  YYSYMBOL_IMAGEBUFFER = 248,              /* IMAGEBUFFER  */
  YYSYMBOL_IIMAGEBUFFER = 249,             /* IIMAGEBUFFER  */
  YYSYMBOL_UIMAGEBUFFER = 250,             /* UIMAGEBUFFER  */
  YYSYMBOL_IMAGE1DARRAY = 251,             /* IMAGE1DARRAY  */
  YYSYMBOL_IIMAGE1DARRAY = 252,            /* IIMAGE1DARRAY  */
  YYSYMBOL_UIMAGE1DARRAY = 253,            /* UIMAGE1DARRAY  */
  YYSYMBOL_IMAGE2DARRAY = 254,             /* IMAGE2DARRAY  */
  YYSYMBOL_IIMAGE2DARRAY = 255,            /* IIMAGE2DARRAY  */
  YYSYMBOL_UIMAGE2DARRAY = 256,            /* UIMAGE2DARRAY  */
  YYSYMBOL_IMAGECUBEARRAY = 257,           /* IMAGECUBEARRAY  */
  YYSYMBOL_IIMAGECUBEARRAY = 258,          /* IIMAGECUBEARRAY  */
  YYSYMBOL_UIMAGECUBEARRAY = 259,          /* UIMAGECUBEARRAY  */
  YYSYMBOL_IMAGE2DMS = 260,                /* IMAGE2DMS  */
  YYSYMBOL_IIMAGE2DMS = 261,               /* IIMAGE2DMS  */
  YYSYMBOL_UIMAGE2DMS = 262,               /* UIMAGE2DMS  */
  YYSYMBOL_IMAGE2DMSARRAY = 263,           /* IMAGE2DMSARRAY  */
  YYSYMBOL_IIMAGE2DMSARRAY = 264,          /* IIMAGE2DMSARRAY  */
  YYSYMBOL_UIMAGE2DMSARRAY = 265,          /* UIMAGE2DMSARRAY  */
  YYSYMBOL_F16IMAGE1D = 266,               /* F16IMAGE1D  */
  YYSYMBOL_F16IMAGE2D = 267,               /* F16IMAGE2D  */
  YYSYMBOL_F16IMAGE3D = 268,               /* F16IMAGE3D  */
  YYSYMBOL_F16IMAGE2DRECT = 269,           /* F16IMAGE2DRECT  */
  YYSYMBOL_F16IMAGECUBE = 270,             /* F16IMAGECUBE  */
  YYSYMBOL_F16IMAGE1DARRAY = 271,          /* F16IMAGE1DARRAY  */
  YYSYMBOL_F16IMAGE2DARRAY = 272,          /* F16IMAGE2DARRAY  */
  YYSYMBOL_F16IMAGECUBEARRAY = 273,        /* F16IMAGECUBEARRAY  */
  YYSYMBOL_F16IMAGEBUFFER = 274,           /* F16IMAGEBUFFER  */
  YYSYMBOL_F16IMAGE2DMS = 275,             /* F16IMAGE2DMS  */
  YYSYMBOL_F16IMAGE2DMSARRAY = 276,        /* F16IMAGE2DMSARRAY  */
  YYSYMBOL_I64IMAGE1D = 277,               /* I64IMAGE1D  */
  YYSYMBOL_U64IMAGE1D = 278,               /* U64IMAGE1D  */
  YYSYMBOL_I64IMAGE2D = 279,               /* I64IMAGE2D  */
  YYSYMBOL_U64IMAGE2D = 280,               /* U64IMAGE2D  */
  YYSYMBOL_I64IMAGE3D = 281,               /* I64IMAGE3D  */
  YYSYMBOL_U64IMAGE3D = 282,               /* U64IMAGE3D  */
  YYSYMBOL_I64IMAGE2DRECT = 283,           /* I64IMAGE2DRECT  */
  YYSYMBOL_U64IMAGE2DRECT = 284,           /* U64IMAGE2DRECT  */
  YYSYMBOL_I64IMAGECUBE = 285,             /* I64IMAGECUBE  */
  YYSYMBOL_U64IMAGECUBE = 286,             /* U64IMAGECUBE  */
  YYSYMBOL_I64IMAGEBUFFER = 287,           /* I64IMAGEBUFFER  */
  YYSYMBOL_U64IMAGEBUFFER = 288,           /* U64IMAGEBUFFER  */
  YYSYMBOL_I64IMAGE1DARRAY = 289,          /* I64IMAGE1DARRAY  */
  YYSYMBOL_U64IMAGE1DARRAY = 290,          /* U64IMAGE1DARRAY  */
  YYSYMBOL_I64IMAGE2DARRAY = 291,          /* I64IMAGE2DARRAY  */
  YYSYMBOL_U64IMAGE2DARRAY = 292,          /* U64IMAGE2DARRAY  */
  YYSYMBOL_I64IMAGECUBEARRAY = 293,        /* I64IMAGECUBEARRAY  */
  YYSYMBOL_U64IMAGECUBEARRAY = 294,        /* U64IMAGECUBEARRAY  */
  YYSYMBOL_I64IMAGE2DMS = 295,             /* I64IMAGE2DMS  */
  YYSYMBOL_U64IMAGE2DMS = 296,             /* U64IMAGE2DMS  */
  YYSYMBOL_I64IMAGE2DMSARRAY = 297,        /* I64IMAGE2DMSARRAY  */
  YYSYMBOL_U64IMAGE2DMSARRAY = 298,        /* U64IMAGE2DMSARRAY  */
  YYSYMBOL_TEXTURECUBEARRAY = 299,         /* TEXTURECUBEARRAY  */
  YYSYMBOL_ITEXTURECUBEARRAY = 300,        /* ITEXTURECUBEARRAY  */
  YYSYMBOL_UTEXTURECUBEARRAY = 301,        /* UTEXTURECUBEARRAY  */
  YYSYMBOL_TEXTURE1D = 302,                /* TEXTURE1D  */
  YYSYMBOL_ITEXTURE1D = 303,               /* ITEXTURE1D  */
  YYSYMBOL_UTEXTURE1D = 304,               /* UTEXTURE1D  */
  YYSYMBOL_TEXTURE1DARRAY = 305,           /* TEXTURE1DARRAY  */
  YYSYMBOL_ITEXTURE1DARRAY = 306,          /* ITEXTURE1DARRAY  */
  YYSYMBOL_UTEXTURE1DARRAY = 307,          /* UTEXTURE1DARRAY  */
  YYSYMBOL_TEXTURE2DRECT = 308,            /* TEXTURE2DRECT  */
  YYSYMBOL_ITEXTURE2DRECT = 309,           /* ITEXTURE2DRECT  */
  YYSYMBOL_UTEXTURE2DRECT = 310,           /* UTEXTURE2DRECT  */
  YYSYMBOL_TEXTUREBUFFER = 311,            /* TEXTUREBUFFER  */
  YYSYMBOL_ITEXTUREBUFFER = 312,           /* ITEXTUREBUFFER  */
  YYSYMBOL_UTEXTUREBUFFER = 313,           /* UTEXTUREBUFFER  */
  YYSYMBOL_TEXTURE2DMS = 314,              /* TEXTURE2DMS  */
  YYSYMBOL_ITEXTURE2DMS = 315,             /* ITEXTURE2DMS  */
  YYSYMBOL_UTEXTURE2DMS = 316,             /* UTEXTURE2DMS  */
  YYSYMBOL_TEXTURE2DMSARRAY = 317,         /* TEXTURE2DMSARRAY  */
  YYSYMBOL_ITEXTURE2DMSARRAY = 318,        /* ITEXTURE2DMSARRAY  */
  YYSYMBOL_UTEXTURE2DMSARRAY = 319,        /* UTEXTURE2DMSARRAY  */
  YYSYMBOL_F16TEXTURE1D = 320,             /* F16TEXTURE1D  */
  YYSYMBOL_F16TEXTURE2D = 321,             /* F16TEXTURE2D  */
  YYSYMBOL_F16TEXTURE3D = 322,             /* F16TEXTURE3D  */
  YYSYMBOL_F16TEXTURE2DRECT = 323,         /* F16TEXTURE2DRECT  */
  YYSYMBOL_F16TEXTURECUBE = 324,           /* F16TEXTURECUBE  */
  YYSYMBOL_F16TEXTURE1DARRAY = 325,        /* F16TEXTURE1DARRAY  */
  YYSYMBOL_F16TEXTURE2DARRAY = 326,        /* F16TEXTURE2DARRAY  */
  YYSYMBOL_F16TEXTURECUBEARRAY = 327,      /* F16TEXTURECUBEARRAY  */
  YYSYMBOL_F16TEXTUREBUFFER = 328,         /* F16TEXTUREBUFFER  */
  YYSYMBOL_F16TEXTURE2DMS = 329,           /* F16TEXTURE2DMS  */
  YYSYMBOL_F16TEXTURE2DMSARRAY = 330,      /* F16TEXTURE2DMSARRAY  */
  YYSYMBOL_SUBPASSINPUT = 331,             /* SUBPASSINPUT  */
  YYSYMBOL_SUBPASSINPUTMS = 332,           /* SUBPASSINPUTMS  */
  YYSYMBOL_ISUBPASSINPUT = 333,            /* ISUBPASSINPUT  */
  YYSYMBOL_ISUBPASSINPUTMS = 334,          /* ISUBPASSINPUTMS  */
  YYSYMBOL_USUBPASSINPUT = 335,            /* USUBPASSINPUT  */
  YYSYMBOL_USUBPASSINPUTMS = 336,          /* USUBPASSINPUTMS  */
  YYSYMBOL_F16SUBPASSINPUT = 337,          /* F16SUBPASSINPUT  */
  YYSYMBOL_F16SUBPASSINPUTMS = 338,        /* F16SUBPASSINPUTMS  */
  YYSYMBOL_SPIRV_INSTRUCTION = 339,        /* SPIRV_INSTRUCTION  */
  YYSYMBOL_SPIRV_EXECUTION_MODE = 340,     /* SPIRV_EXECUTION_MODE  */
  YYSYMBOL_SPIRV_EXECUTION_MODE_ID = 341,  /* SPIRV_EXECUTION_MODE_ID  */
  YYSYMBOL_SPIRV_DECORATE = 342,           /* SPIRV_DECORATE  */
  YYSYMBOL_SPIRV_DECORATE_ID = 343,        /* SPIRV_DECORATE_ID  */
  YYSYMBOL_SPIRV_DECORATE_STRING = 344,    /* SPIRV_DECORATE_STRING  */
  YYSYMBOL_SPIRV_TYPE = 345,               /* SPIRV_TYPE  */
  YYSYMBOL_SPIRV_STORAGE_CLASS = 346,      /* SPIRV_STORAGE_CLASS  */
  YYSYMBOL_SPIRV_BY_REFERENCE = 347,       /* SPIRV_BY_REFERENCE  */
  YYSYMBOL_SPIRV_LITERAL = 348,            /* SPIRV_LITERAL  */
  YYSYMBOL_ATTACHMENTEXT = 349,            /* ATTACHMENTEXT  */
  YYSYMBOL_IATTACHMENTEXT = 350,           /* IATTACHMENTEXT  */
  YYSYMBOL_UATTACHMENTEXT = 351,           /* UATTACHMENTEXT  */
  YYSYMBOL_LEFT_OP = 352,                  /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 353,                 /* RIGHT_OP  */
  YYSYMBOL_INC_OP = 354,                   /* INC_OP  */
  YYSYMBOL_DEC_OP = 355,                   /* DEC_OP  */
  YYSYMBOL_LE_OP = 356,                    /* LE_OP  */
  YYSYMBOL_GE_OP = 357,                    /* GE_OP  */
  YYSYMBOL_EQ_OP = 358,                    /* EQ_OP  */
  YYSYMBOL_NE_OP = 359,                    /* NE_OP  */
  YYSYMBOL_AND_OP = 360,                   /* AND_OP  */
  YYSYMBOL_OR_OP = 361,                    /* OR_OP  */
  YYSYMBOL_XOR_OP = 362,                   /* XOR_OP  */
  YYSYMBOL_MUL_ASSIGN = 363,               /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 364,               /* DIV_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 365,               /* ADD_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 366,               /* MOD_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 367,              /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 368,             /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 369,               /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 370,               /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 371,                /* OR_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 372,               /* SUB_ASSIGN  */
  YYSYMBOL_STRING_LITERAL = 373,           /* STRING_LITERAL  */
  YYSYMBOL_LEFT_PAREN = 374,               /* LEFT_PAREN  */
  YYSYMBOL_RIGHT_PAREN = 375,              /* RIGHT_PAREN  */
  YYSYMBOL_LEFT_BRACKET = 376,             /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 377,            /* RIGHT_BRACKET  */
  YYSYMBOL_LEFT_BRACE = 378,               /* LEFT_BRACE  */
  YYSYMBOL_RIGHT_BRACE = 379,              /* RIGHT_BRACE  */
  YYSYMBOL_DOT = 380,                      /* DOT  */
  YYSYMBOL_ELLIPSIS = 381,                 /* ELLIPSIS  */
  YYSYMBOL_COMMA = 382,                    /* COMMA  */
  YYSYMBOL_COLON = 383,                    /* COLON  */
  YYSYMBOL_EQUAL = 384,                    /* EQUAL  */
  YYSYMBOL_SEMICOLON = 385,                /* SEMICOLON  */
  YYSYMBOL_BANG = 386,                     /* BANG  */
  YYSYMBOL_DASH = 387,                     /* DASH  */
  YYSYMBOL_TILDE = 388,                    /* TILDE  */
  YYSYMBOL_PLUS = 389,                     /* PLUS  */
  YYSYMBOL_STAR = 390,                     /* STAR  */
  YYSYMBOL_SLASH = 391,                    /* SLASH  */
  YYSYMBOL_PERCENT = 392,                  /* PERCENT  */
  YYSYMBOL_LEFT_ANGLE = 393,               /* LEFT_ANGLE  */
  YYSYMBOL_RIGHT_ANGLE = 394,              /* RIGHT_ANGLE  */
  YYSYMBOL_VERTICAL_BAR = 395,             /* VERTICAL_BAR  */
  YYSYMBOL_CARET = 396,                    /* CARET  */
  YYSYMBOL_AMPERSAND = 397,                /* AMPERSAND  */
  YYSYMBOL_QUESTION = 398,                 /* QUESTION  */
  YYSYMBOL_INVARIANT = 399,                /* INVARIANT  */
  YYSYMBOL_HIGH_PRECISION = 400,           /* HIGH_PRECISION  */
  YYSYMBOL_MEDIUM_PRECISION = 401,         /* MEDIUM_PRECISION  */
  YYSYMBOL_LOW_PRECISION = 402,            /* LOW_PRECISION  */
  YYSYMBOL_PRECISION = 403,                /* PRECISION  */
  YYSYMBOL_PACKED = 404,                   /* PACKED  */
  YYSYMBOL_RESOURCE = 405,                 /* RESOURCE  */
  YYSYMBOL_SUPERP = 406,                   /* SUPERP  */
  YYSYMBOL_FLOATCONSTANT = 407,            /* FLOATCONSTANT  */
  YYSYMBOL_INTCONSTANT = 408,              /* INTCONSTANT  */
  YYSYMBOL_UINTCONSTANT = 409,             /* UINTCONSTANT  */
  YYSYMBOL_BOOLCONSTANT = 410,             /* BOOLCONSTANT  */
  YYSYMBOL_IDENTIFIER = 411,               /* IDENTIFIER  */
  YYSYMBOL_TYPE_NAME = 412,                /* TYPE_NAME  */
  YYSYMBOL_CENTROID = 413,                 /* CENTROID  */
  YYSYMBOL_IN = 414,                       /* IN  */
  YYSYMBOL_OUT = 415,                      /* OUT  */
  YYSYMBOL_INOUT = 416,                    /* INOUT  */
  YYSYMBOL_STRUCT = 417,                   /* STRUCT  */
  YYSYMBOL_VOID = 418,                     /* VOID  */
  YYSYMBOL_WHILE = 419,                    /* WHILE  */
  YYSYMBOL_BREAK = 420,                    /* BREAK  */
  YYSYMBOL_CONTINUE = 421,                 /* CONTINUE  */
  YYSYMBOL_DO = 422,                       /* DO  */
  YYSYMBOL_ELSE = 423,                     /* ELSE  */
  YYSYMBOL_FOR = 424,                      /* FOR  */
  YYSYMBOL_IF = 425,                       /* IF  */
  YYSYMBOL_DISCARD = 426,                  /* DISCARD  */
  YYSYMBOL_RETURN = 427,                   /* RETURN  */
  YYSYMBOL_SWITCH = 428,                   /* SWITCH  */
  YYSYMBOL_CASE = 429,                     /* CASE  */
  YYSYMBOL_DEFAULT = 430,                  /* DEFAULT  */
  YYSYMBOL_TERMINATE_INVOCATION = 431,     /* TERMINATE_INVOCATION  */
  YYSYMBOL_TERMINATE_RAY = 432,            /* TERMINATE_RAY  */
  YYSYMBOL_IGNORE_INTERSECTION = 433,      /* IGNORE_INTERSECTION  */
  YYSYMBOL_UNIFORM = 434,                  /* UNIFORM  */
  YYSYMBOL_SHARED = 435,                   /* SHARED  */
  YYSYMBOL_BUFFER = 436,                   /* BUFFER  */
  YYSYMBOL_TILEIMAGEEXT = 437,             /* TILEIMAGEEXT  */
  YYSYMBOL_FLAT = 438,                     /* FLAT  */
  YYSYMBOL_SMOOTH = 439,                   /* SMOOTH  */
  YYSYMBOL_LAYOUT = 440,                   /* LAYOUT  */
  YYSYMBOL_DOUBLECONSTANT = 441,           /* DOUBLECONSTANT  */
  YYSYMBOL_INT16CONSTANT = 442,            /* INT16CONSTANT  */
  YYSYMBOL_UINT16CONSTANT = 443,           /* UINT16CONSTANT  */
  YYSYMBOL_FLOAT16CONSTANT = 444,          /* FLOAT16CONSTANT  */
  YYSYMBOL_INT32CONSTANT = 445,            /* INT32CONSTANT  */
  YYSYMBOL_UINT32CONSTANT = 446,           /* UINT32CONSTANT  */
  YYSYMBOL_INT64CONSTANT = 447,            /* INT64CONSTANT  */
  YYSYMBOL_UINT64CONSTANT = 448,           /* UINT64CONSTANT  */
  YYSYMBOL_SUBROUTINE = 449,               /* SUBROUTINE  */
  YYSYMBOL_DEMOTE = 450,                   /* DEMOTE  */
  YYSYMBOL_FUNCTION = 451,                 /* FUNCTION  */
  YYSYMBOL_PAYLOADNV = 452,                /* PAYLOADNV  */
  YYSYMBOL_PAYLOADINNV = 453,              /* PAYLOADINNV  */
  YYSYMBOL_HITATTRNV = 454,                /* HITATTRNV  */
  YYSYMBOL_CALLDATANV = 455,               /* CALLDATANV  */
  YYSYMBOL_CALLDATAINNV = 456,             /* CALLDATAINNV  */
  YYSYMBOL_PAYLOADEXT = 457,               /* PAYLOADEXT  */
  YYSYMBOL_PAYLOADINEXT = 458,             /* PAYLOADINEXT  */
  YYSYMBOL_HITATTREXT = 459,               /* HITATTREXT  */
  YYSYMBOL_CALLDATAEXT = 460,              /* CALLDATAEXT  */
  YYSYMBOL_CALLDATAINEXT = 461,            /* CALLDATAINEXT  */
  YYSYMBOL_PATCH = 462,                    /* PATCH  */
  YYSYMBOL_SAMPLE = 463,                   /* SAMPLE  */
  YYSYMBOL_NONUNIFORM = 464,               /* NONUNIFORM  */
  YYSYMBOL_RESOURCEHEAP = 465,             /* RESOURCEHEAP  */
  YYSYMBOL_SAMPLERHEAP = 466,              /* SAMPLERHEAP  */
  YYSYMBOL_COHERENT = 467,                 /* COHERENT  */
  YYSYMBOL_VOLATILE = 468,                 /* VOLATILE  */
  YYSYMBOL_RESTRICT = 469,                 /* RESTRICT  */
  YYSYMBOL_READONLY = 470,                 /* READONLY  */
  YYSYMBOL_WRITEONLY = 471,                /* WRITEONLY  */
  YYSYMBOL_NONTEMPORAL = 472,              /* NONTEMPORAL  */
  YYSYMBOL_DEVICECOHERENT = 473,           /* DEVICECOHERENT  */
  YYSYMBOL_QUEUEFAMILYCOHERENT = 474,      /* QUEUEFAMILYCOHERENT  */
  YYSYMBOL_WORKGROUPCOHERENT = 475,        /* WORKGROUPCOHERENT  */
  YYSYMBOL_SUBGROUPCOHERENT = 476,         /* SUBGROUPCOHERENT  */
  YYSYMBOL_NONPRIVATE = 477,               /* NONPRIVATE  */
  YYSYMBOL_SHADERCALLCOHERENT = 478,       /* SHADERCALLCOHERENT  */
  YYSYMBOL_NOPERSPECTIVE = 479,            /* NOPERSPECTIVE  */
  YYSYMBOL_EXPLICITINTERPAMD = 480,        /* EXPLICITINTERPAMD  */
  YYSYMBOL_PERVERTEXEXT = 481,             /* PERVERTEXEXT  */
  YYSYMBOL_PERVERTEXNV = 482,              /* PERVERTEXNV  */
  YYSYMBOL_PERPRIMITIVENV = 483,           /* PERPRIMITIVENV  */
  YYSYMBOL_PERVIEWNV = 484,                /* PERVIEWNV  */
  YYSYMBOL_PERTASKNV = 485,                /* PERTASKNV  */
  YYSYMBOL_PERPRIMITIVEEXT = 486,          /* PERPRIMITIVEEXT  */
  YYSYMBOL_TASKPAYLOADWORKGROUPEXT = 487,  /* TASKPAYLOADWORKGROUPEXT  */
  YYSYMBOL_PRECISE = 488,                  /* PRECISE  */
  YYSYMBOL_YYACCEPT = 489,                 /* $accept  */
  YYSYMBOL_variable_identifier = 490,      /* variable_identifier  */
  YYSYMBOL_primary_expression = 491,       /* primary_expression  */
  YYSYMBOL_postfix_expression = 492,       /* postfix_expression  */
  YYSYMBOL_integer_expression = 493,       /* integer_expression  */
  YYSYMBOL_function_call = 494,            /* function_call  */
  YYSYMBOL_function_call_or_method = 495,  /* function_call_or_method  */
  YYSYMBOL_function_call_generic = 496,    /* function_call_generic  */
  YYSYMBOL_function_call_header_no_parameters = 497, /* function_call_header_no_parameters  */
  YYSYMBOL_function_call_header_with_parameters = 498, /* function_call_header_with_parameters  */
  YYSYMBOL_function_call_header = 499,     /* function_call_header  */
  YYSYMBOL_function_identifier = 500,      /* function_identifier  */
  YYSYMBOL_unary_expression = 501,         /* unary_expression  */
  YYSYMBOL_unary_operator = 502,           /* unary_operator  */
  YYSYMBOL_multiplicative_expression = 503, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 504,      /* additive_expression  */
  YYSYMBOL_shift_expression = 505,         /* shift_expression  */
  YYSYMBOL_relational_expression = 506,    /* relational_expression  */
  YYSYMBOL_equality_expression = 507,      /* equality_expression  */
  YYSYMBOL_and_expression = 508,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 509,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 510,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 511,   /* logical_and_expression  */
  YYSYMBOL_logical_xor_expression = 512,   /* logical_xor_expression  */
  YYSYMBOL_logical_or_expression = 513,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 514,   /* conditional_expression  */
  YYSYMBOL_515_1 = 515,                    /* $@1  */
  YYSYMBOL_assignment_expression = 516,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 517,      /* assignment_operator  */
  YYSYMBOL_expression = 518,               /* expression  */
  YYSYMBOL_constant_expression = 519,      /* constant_expression  */
  YYSYMBOL_declaration = 520,              /* declaration  */
  YYSYMBOL_block_structure = 521,          /* block_structure  */
  YYSYMBOL_522_2 = 522,                    /* $@2  */
  YYSYMBOL_identifier_list = 523,          /* identifier_list  */
  YYSYMBOL_function_prototype = 524,       /* function_prototype  */
  YYSYMBOL_function_prototype_with_spirv_variadic_tail = 525, /* function_prototype_with_spirv_variadic_tail  */
  YYSYMBOL_function_declarator = 526,      /* function_declarator  */
  YYSYMBOL_function_header_with_parameters = 527, /* function_header_with_parameters  */
  YYSYMBOL_function_header = 528,          /* function_header  */
  YYSYMBOL_parameter_declarator = 529,     /* parameter_declarator  */
  YYSYMBOL_parameter_declaration = 530,    /* parameter_declaration  */
  YYSYMBOL_parameter_type_specifier = 531, /* parameter_type_specifier  */
  YYSYMBOL_init_declarator_list = 532,     /* init_declarator_list  */
  YYSYMBOL_single_declaration = 533,       /* single_declaration  */
  YYSYMBOL_fully_specified_type = 534,     /* fully_specified_type  */
  YYSYMBOL_invariant_qualifier = 535,      /* invariant_qualifier  */
  YYSYMBOL_interpolation_qualifier = 536,  /* interpolation_qualifier  */
  YYSYMBOL_layout_qualifier = 537,         /* layout_qualifier  */
  YYSYMBOL_layout_qualifier_id_list = 538, /* layout_qualifier_id_list  */
  YYSYMBOL_layout_qualifier_id = 539,      /* layout_qualifier_id  */
  YYSYMBOL_precise_qualifier = 540,        /* precise_qualifier  */
  YYSYMBOL_type_qualifier = 541,           /* type_qualifier  */
  YYSYMBOL_single_type_qualifier = 542,    /* single_type_qualifier  */
  YYSYMBOL_storage_qualifier = 543,        /* storage_qualifier  */
  YYSYMBOL_non_uniform_qualifier = 544,    /* non_uniform_qualifier  */
  YYSYMBOL_type_name_list = 545,           /* type_name_list  */
  YYSYMBOL_type_specifier = 546,           /* type_specifier  */
  YYSYMBOL_array_specifier = 547,          /* array_specifier  */
  YYSYMBOL_type_parameter_specifier_opt = 548, /* type_parameter_specifier_opt  */
  YYSYMBOL_type_parameter_specifier = 549, /* type_parameter_specifier  */
  YYSYMBOL_type_parameter_specifier_list = 550, /* type_parameter_specifier_list  */
  YYSYMBOL_type_specifier_nonarray = 551,  /* type_specifier_nonarray  */
  YYSYMBOL_precision_qualifier = 552,      /* precision_qualifier  */
  YYSYMBOL_struct_specifier = 553,         /* struct_specifier  */
  YYSYMBOL_554_3 = 554,                    /* $@3  */
  YYSYMBOL_555_4 = 555,                    /* $@4  */
  YYSYMBOL_struct_declaration_list = 556,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration_with_heap = 557, /* struct_declaration_with_heap  */
  YYSYMBOL_block_heap_inner_structure = 558, /* block_heap_inner_structure  */
  YYSYMBOL_559_5 = 559,                    /* $@5  */
  YYSYMBOL_struct_declaration_without_heap = 560, /* struct_declaration_without_heap  */
  YYSYMBOL_struct_declaration = 561,       /* struct_declaration  */
  YYSYMBOL_struct_declarator_list = 562,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 563,        /* struct_declarator  */
  YYSYMBOL_initializer = 564,              /* initializer  */
  YYSYMBOL_initializer_list = 565,         /* initializer_list  */
  YYSYMBOL_declaration_statement = 566,    /* declaration_statement  */
  YYSYMBOL_statement = 567,                /* statement  */
  YYSYMBOL_simple_statement = 568,         /* simple_statement  */
  YYSYMBOL_demote_statement = 569,         /* demote_statement  */
  YYSYMBOL_compound_statement = 570,       /* compound_statement  */
  YYSYMBOL_571_6 = 571,                    /* $@6  */
  YYSYMBOL_572_7 = 572,                    /* $@7  */
  YYSYMBOL_statement_no_new_scope = 573,   /* statement_no_new_scope  */
  YYSYMBOL_statement_scoped = 574,         /* statement_scoped  */
  YYSYMBOL_575_8 = 575,                    /* $@8  */
  YYSYMBOL_576_9 = 576,                    /* $@9  */
  YYSYMBOL_compound_statement_no_new_scope = 577, /* compound_statement_no_new_scope  */
  YYSYMBOL_statement_list = 578,           /* statement_list  */
  YYSYMBOL_expression_statement = 579,     /* expression_statement  */
  YYSYMBOL_selection_statement = 580,      /* selection_statement  */
  YYSYMBOL_selection_statement_nonattributed = 581, /* selection_statement_nonattributed  */
  YYSYMBOL_selection_rest_statement = 582, /* selection_rest_statement  */
  YYSYMBOL_condition = 583,                /* condition  */
  YYSYMBOL_switch_statement = 584,         /* switch_statement  */
  YYSYMBOL_switch_statement_nonattributed = 585, /* switch_statement_nonattributed  */
  YYSYMBOL_586_10 = 586,                   /* $@10  */
  YYSYMBOL_switch_statement_list = 587,    /* switch_statement_list  */
  YYSYMBOL_case_label = 588,               /* case_label  */
  YYSYMBOL_iteration_statement = 589,      /* iteration_statement  */
  YYSYMBOL_iteration_statement_nonattributed = 590, /* iteration_statement_nonattributed  */
  YYSYMBOL_591_11 = 591,                   /* $@11  */
  YYSYMBOL_592_12 = 592,                   /* $@12  */
  YYSYMBOL_593_13 = 593,                   /* $@13  */
  YYSYMBOL_for_init_statement = 594,       /* for_init_statement  */
  YYSYMBOL_conditionopt = 595,             /* conditionopt  */
  YYSYMBOL_for_rest_statement = 596,       /* for_rest_statement  */
  YYSYMBOL_jump_statement = 597,           /* jump_statement  */
  YYSYMBOL_translation_unit = 598,         /* translation_unit  */
  YYSYMBOL_external_declaration = 599,     /* external_declaration  */
  YYSYMBOL_function_definition = 600,      /* function_definition  */
  YYSYMBOL_601_14 = 601,                   /* $@14  */
  YYSYMBOL_attribute = 602,                /* attribute  */
  YYSYMBOL_attribute_list = 603,           /* attribute_list  */
  YYSYMBOL_single_attribute = 604,         /* single_attribute  */
  YYSYMBOL_spirv_requirements_list = 605,  /* spirv_requirements_list  */
  YYSYMBOL_spirv_requirements_parameter = 606, /* spirv_requirements_parameter  */
  YYSYMBOL_spirv_extension_list = 607,     /* spirv_extension_list  */
  YYSYMBOL_spirv_capability_list = 608,    /* spirv_capability_list  */
  YYSYMBOL_spirv_execution_mode_qualifier = 609, /* spirv_execution_mode_qualifier  */
  YYSYMBOL_spirv_execution_mode_parameter_list = 610, /* spirv_execution_mode_parameter_list  */
  YYSYMBOL_spirv_execution_mode_parameter = 611, /* spirv_execution_mode_parameter  */
  YYSYMBOL_spirv_execution_mode_id_parameter_list = 612, /* spirv_execution_mode_id_parameter_list  */
  YYSYMBOL_spirv_storage_class_qualifier = 613, /* spirv_storage_class_qualifier  */
  YYSYMBOL_spirv_decorate_qualifier = 614, /* spirv_decorate_qualifier  */
  YYSYMBOL_spirv_decorate_parameter_list = 615, /* spirv_decorate_parameter_list  */
  YYSYMBOL_spirv_decorate_parameter = 616, /* spirv_decorate_parameter  */
  YYSYMBOL_spirv_decorate_id_parameter_list = 617, /* spirv_decorate_id_parameter_list  */
  YYSYMBOL_spirv_decorate_id_parameter = 618, /* spirv_decorate_id_parameter  */
  YYSYMBOL_spirv_decorate_string_parameter_list = 619, /* spirv_decorate_string_parameter_list  */
  YYSYMBOL_spirv_type_specifier = 620,     /* spirv_type_specifier  */
  YYSYMBOL_spirv_type_parameter_list = 621, /* spirv_type_parameter_list  */
  YYSYMBOL_spirv_type_parameter = 622,     /* spirv_type_parameter  */
  YYSYMBOL_spirv_instruction_qualifier = 623, /* spirv_instruction_qualifier  */
  YYSYMBOL_spirv_instruction_qualifier_list = 624, /* spirv_instruction_qualifier_list  */
  YYSYMBOL_spirv_instruction_qualifier_id = 625 /* spirv_instruction_qualifier_id  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 111 "MachineIndependent/glslang.y"


#define parseContext (*pParseContext)
#define yyerror(context, msg) context->parserError(msg)

extern int yylex(YYSTYPE*, TParseContext&);


#line 765 "MachineIndependent/glslang_tab.cpp"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  477
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   15329

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  489
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  137
/* YYNRULES -- Number of rules.  */
#define YYNRULES  738
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1007

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   743


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   366,   366,   372,   375,   380,   383,   386,   390,   393,
     396,   400,   404,   408,   412,   416,   420,   426,   433,   436,
     439,   442,   445,   450,   458,   465,   472,   478,   482,   489,
     492,   498,   516,   541,   549,   554,   581,   589,   595,   599,
     603,   619,   626,   627,   628,   629,   635,   636,   641,   646,
     655,   656,   661,   669,   670,   676,   685,   686,   691,   696,
     701,   709,   710,   719,   731,   732,   741,   742,   751,   752,
     761,   762,   770,   771,   779,   780,   788,   789,   789,   807,
     808,   824,   828,   832,   836,   841,   845,   849,   853,   857,
     861,   865,   872,   875,   886,   893,   898,   905,   912,   917,
     922,   929,   932,   935,   938,   943,   951,   951,   963,   967,
     974,   979,   987,   995,  1004,  1010,  1019,  1025,  1031,  1037,
    1046,  1049,  1056,  1069,  1092,  1115,  1130,  1149,  1160,  1171,
    1181,  1191,  1201,  1210,  1213,  1218,  1223,  1228,  1236,  1241,
    1247,  1252,  1257,  1266,  1276,  1303,  1312,  1319,  1326,  1333,
    1340,  1348,  1356,  1366,  1376,  1383,  1393,  1399,  1402,  1409,
    1413,  1417,  1425,  1434,  1437,  1448,  1451,  1454,  1458,  1462,
    1466,  1470,  1473,  1478,  1482,  1487,  1495,  1499,  1504,  1510,
    1516,  1523,  1528,  1533,  1541,  1546,  1558,  1572,  1578,  1583,
    1588,  1593,  1601,  1609,  1617,  1625,  1633,  1641,  1649,  1657,
    1665,  1673,  1680,  1687,  1691,  1696,  1701,  1706,  1711,  1716,
    1721,  1725,  1729,  1733,  1737,  1741,  1747,  1753,  1763,  1770,
    1773,  1781,  1788,  1799,  1804,  1812,  1816,  1826,  1829,  1835,
    1841,  1847,  1855,  1865,  1869,  1873,  1877,  1882,  1886,  1891,
    1896,  1901,  1906,  1911,  1916,  1921,  1926,  1931,  1937,  1943,
    1949,  1954,  1959,  1964,  1969,  1974,  1979,  1984,  1989,  1994,
    1999,  2004,  2009,  2016,  2021,  2026,  2031,  2036,  2041,  2046,
    2051,  2056,  2061,  2066,  2071,  2076,  2081,  2086,  2094,  2102,
    2110,  2116,  2122,  2128,  2134,  2140,  2146,  2152,  2158,  2164,
    2170,  2176,  2182,  2188,  2194,  2200,  2206,  2212,  2218,  2224,
    2230,  2236,  2242,  2248,  2254,  2260,  2266,  2272,  2278,  2284,
    2290,  2296,  2302,  2308,  2314,  2320,  2326,  2332,  2338,  2344,
    2350,  2356,  2362,  2370,  2378,  2386,  2394,  2402,  2410,  2418,
    2426,  2434,  2442,  2450,  2458,  2464,  2470,  2476,  2482,  2488,
    2494,  2500,  2506,  2512,  2518,  2524,  2530,  2536,  2542,  2548,
    2554,  2560,  2566,  2572,  2578,  2584,  2590,  2596,  2602,  2608,
    2614,  2620,  2626,  2632,  2638,  2644,  2650,  2656,  2662,  2668,
    2674,  2678,  2682,  2686,  2691,  2696,  2701,  2706,  2711,  2716,
    2721,  2726,  2731,  2736,  2741,  2746,  2751,  2756,  2762,  2768,
    2774,  2780,  2786,  2792,  2798,  2804,  2810,  2816,  2822,  2828,
    2834,  2839,  2844,  2849,  2854,  2859,  2864,  2869,  2874,  2879,
    2884,  2889,  2894,  2899,  2904,  2909,  2914,  2919,  2924,  2929,
    2934,  2939,  2944,  2949,  2954,  2959,  2964,  2969,  2974,  2979,
    2984,  2989,  2994,  2999,  3005,  3011,  3016,  3021,  3026,  3032,
    3037,  3042,  3047,  3053,  3058,  3063,  3068,  3074,  3079,  3084,
    3089,  3095,  3101,  3107,  3113,  3118,  3124,  3130,  3136,  3141,
    3146,  3151,  3156,  3161,  3167,  3172,  3177,  3182,  3188,  3193,
    3198,  3203,  3209,  3214,  3219,  3224,  3230,  3235,  3240,  3245,
    3251,  3256,  3261,  3266,  3272,  3277,  3282,  3287,  3293,  3298,
    3303,  3308,  3314,  3319,  3324,  3329,  3335,  3340,  3345,  3350,
    3356,  3361,  3366,  3371,  3377,  3382,  3387,  3392,  3398,  3403,
    3408,  3413,  3419,  3424,  3429,  3434,  3440,  3445,  3450,  3455,
    3461,  3466,  3471,  3476,  3481,  3486,  3491,  3496,  3501,  3506,
    3511,  3516,  3521,  3526,  3531,  3536,  3541,  3546,  3551,  3556,
    3561,  3566,  3571,  3576,  3581,  3587,  3593,  3599,  3605,  3611,
    3617,  3623,  3630,  3637,  3643,  3649,  3655,  3661,  3668,  3675,
    3682,  3689,  3694,  3699,  3703,  3709,  3715,  3721,  3725,  3729,
    3733,  3738,  3754,  3759,  3764,  3772,  3772,  3788,  3788,  3798,
    3801,  3804,  3814,  3827,  3844,  3844,  3859,  3862,  3875,  3897,
    3924,  3928,  3934,  3939,  3950,  3953,  3959,  3965,  3974,  3977,
    3983,  3987,  3988,  3994,  3995,  3996,  3997,  3998,  3999,  4000,
    4001,  4005,  4013,  4014,  4018,  4014,  4032,  4033,  4037,  4037,
    4044,  4044,  4058,  4061,  4071,  4079,  4090,  4091,  4095,  4098,
    4105,  4112,  4116,  4124,  4128,  4137,  4140,  4147,  4147,  4167,
    4170,  4176,  4188,  4200,  4203,  4211,  4211,  4230,  4230,  4252,
    4252,  4273,  4276,  4282,  4285,  4291,  4295,  4302,  4307,  4312,
    4319,  4322,  4326,  4330,  4334,  4343,  4347,  4356,  4359,  4362,
    4370,  4370,  4412,  4417,  4420,  4425,  4428,  4433,  4436,  4441,
    4444,  4449,  4452,  4457,  4460,  4465,  4469,  4474,  4478,  4483,
    4487,  4494,  4497,  4502,  4505,  4508,  4511,  4514,  4519,  4528,
    4539,  4544,  4552,  4556,  4561,  4565,  4570,  4574,  4579,  4583,
    4590,  4593,  4598,  4601,  4604,  4607,  4612,  4615,  4620,  4626,
    4629,  4632,  4635,  4640,  4644,  4649,  4653,  4658,  4662,  4669,
    4672,  4677,  4680,  4685,  4688,  4694,  4697,  4702,  4705
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CONST", "BOOL", "INT",
  "UINT", "FLOAT", "BVEC2", "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4",
  "UVEC2", "UVEC3", "UVEC4", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3",
  "MAT4", "MAT2X2", "MAT2X3", "MAT2X4", "MAT3X2", "MAT3X3", "MAT3X4",
  "MAT4X2", "MAT4X3", "MAT4X4", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE",
  "SAMPLER2DSHADOW", "SAMPLERCUBESHADOW", "SAMPLER2DARRAY",
  "SAMPLER2DARRAYSHADOW", "ISAMPLER2D", "ISAMPLER3D", "ISAMPLERCUBE",
  "ISAMPLER2DARRAY", "USAMPLER2D", "USAMPLER3D", "USAMPLERCUBE",
  "USAMPLER2DARRAY", "SAMPLER", "SAMPLERSHADOW", "TEXTURE2D", "TEXTURE3D",
  "TEXTURECUBE", "TEXTURE2DARRAY", "ITEXTURE2D", "ITEXTURE3D",
  "ITEXTURECUBE", "ITEXTURE2DARRAY", "UTEXTURE2D", "UTEXTURE3D",
  "UTEXTURECUBE", "UTEXTURE2DARRAY", "ATTRIBUTE", "VARYING", "FLOATE5M2_T",
  "FLOATE4M3_T", "BFLOAT16_T", "FLOAT16_T", "FLOAT32_T", "DOUBLE",
  "FLOAT64_T", "INT64_T", "UINT64_T", "INT32_T", "UINT32_T", "INT16_T",
  "UINT16_T", "INT8_T", "UINT8_T", "I64VEC2", "I64VEC3", "I64VEC4",
  "U64VEC2", "U64VEC3", "U64VEC4", "I32VEC2", "I32VEC3", "I32VEC4",
  "U32VEC2", "U32VEC3", "U32VEC4", "I16VEC2", "I16VEC3", "I16VEC4",
  "U16VEC2", "U16VEC3", "U16VEC4", "I8VEC2", "I8VEC3", "I8VEC4", "U8VEC2",
  "U8VEC3", "U8VEC4", "DVEC2", "DVEC3", "DVEC4", "DMAT2", "DMAT3", "DMAT4",
  "BF16VEC2", "BF16VEC3", "BF16VEC4", "FE5M2VEC2", "FE5M2VEC3",
  "FE5M2VEC4", "FE4M3VEC2", "FE4M3VEC3", "FE4M3VEC4", "F16VEC2", "F16VEC3",
  "F16VEC4", "F16MAT2", "F16MAT3", "F16MAT4", "F32VEC2", "F32VEC3",
  "F32VEC4", "F32MAT2", "F32MAT3", "F32MAT4", "F64VEC2", "F64VEC3",
  "F64VEC4", "F64MAT2", "F64MAT3", "F64MAT4", "DMAT2X2", "DMAT2X3",
  "DMAT2X4", "DMAT3X2", "DMAT3X3", "DMAT3X4", "DMAT4X2", "DMAT4X3",
  "DMAT4X4", "F16MAT2X2", "F16MAT2X3", "F16MAT2X4", "F16MAT3X2",
  "F16MAT3X3", "F16MAT3X4", "F16MAT4X2", "F16MAT4X3", "F16MAT4X4",
  "F32MAT2X2", "F32MAT2X3", "F32MAT2X4", "F32MAT3X2", "F32MAT3X3",
  "F32MAT3X4", "F32MAT4X2", "F32MAT4X3", "F32MAT4X4", "F64MAT2X2",
  "F64MAT2X3", "F64MAT2X4", "F64MAT3X2", "F64MAT3X3", "F64MAT3X4",
  "F64MAT4X2", "F64MAT4X3", "F64MAT4X4", "ATOMIC_UINT", "ACCSTRUCTNV",
  "ACCSTRUCTEXT", "RAYQUERYEXT", "FCOOPMATNV", "ICOOPMATNV", "UCOOPMATNV",
  "COOPMAT", "COOPVECNV", "VECTOR", "HITOBJECTNV", "HITOBJECTATTRNV",
  "HITOBJECTEXT", "HITOBJECTATTREXT", "TENSORLAYOUTNV", "TENSORVIEWNV",
  "TENSORARM", "SAMPLERCUBEARRAY", "SAMPLERCUBEARRAYSHADOW",
  "ISAMPLERCUBEARRAY", "USAMPLERCUBEARRAY", "SAMPLER1D", "SAMPLER1DARRAY",
  "SAMPLER1DARRAYSHADOW", "ISAMPLER1D", "SAMPLER1DSHADOW", "SAMPLER2DRECT",
  "SAMPLER2DRECTSHADOW", "ISAMPLER2DRECT", "USAMPLER2DRECT",
  "SAMPLERBUFFER", "ISAMPLERBUFFER", "USAMPLERBUFFER", "SAMPLER2DMS",
  "ISAMPLER2DMS", "USAMPLER2DMS", "SAMPLER2DMSARRAY", "ISAMPLER2DMSARRAY",
  "USAMPLER2DMSARRAY", "SAMPLEREXTERNALOES", "SAMPLEREXTERNAL2DY2YEXT",
  "ISAMPLER1DARRAY", "USAMPLER1D", "USAMPLER1DARRAY", "F16SAMPLER1D",
  "F16SAMPLER2D", "F16SAMPLER3D", "F16SAMPLER2DRECT", "F16SAMPLERCUBE",
  "F16SAMPLER1DARRAY", "F16SAMPLER2DARRAY", "F16SAMPLERCUBEARRAY",
  "F16SAMPLERBUFFER", "F16SAMPLER2DMS", "F16SAMPLER2DMSARRAY",
  "F16SAMPLER1DSHADOW", "F16SAMPLER2DSHADOW", "F16SAMPLER1DARRAYSHADOW",
  "F16SAMPLER2DARRAYSHADOW", "F16SAMPLER2DRECTSHADOW",
  "F16SAMPLERCUBESHADOW", "F16SAMPLERCUBEARRAYSHADOW", "IMAGE1D",
  "IIMAGE1D", "UIMAGE1D", "IMAGE2D", "IIMAGE2D", "UIMAGE2D", "IMAGE3D",
  "IIMAGE3D", "UIMAGE3D", "IMAGE2DRECT", "IIMAGE2DRECT", "UIMAGE2DRECT",
  "IMAGECUBE", "IIMAGECUBE", "UIMAGECUBE", "IMAGEBUFFER", "IIMAGEBUFFER",
  "UIMAGEBUFFER", "IMAGE1DARRAY", "IIMAGE1DARRAY", "UIMAGE1DARRAY",
  "IMAGE2DARRAY", "IIMAGE2DARRAY", "UIMAGE2DARRAY", "IMAGECUBEARRAY",
  "IIMAGECUBEARRAY", "UIMAGECUBEARRAY", "IMAGE2DMS", "IIMAGE2DMS",
  "UIMAGE2DMS", "IMAGE2DMSARRAY", "IIMAGE2DMSARRAY", "UIMAGE2DMSARRAY",
  "F16IMAGE1D", "F16IMAGE2D", "F16IMAGE3D", "F16IMAGE2DRECT",
  "F16IMAGECUBE", "F16IMAGE1DARRAY", "F16IMAGE2DARRAY",
  "F16IMAGECUBEARRAY", "F16IMAGEBUFFER", "F16IMAGE2DMS",
  "F16IMAGE2DMSARRAY", "I64IMAGE1D", "U64IMAGE1D", "I64IMAGE2D",
  "U64IMAGE2D", "I64IMAGE3D", "U64IMAGE3D", "I64IMAGE2DRECT",
  "U64IMAGE2DRECT", "I64IMAGECUBE", "U64IMAGECUBE", "I64IMAGEBUFFER",
  "U64IMAGEBUFFER", "I64IMAGE1DARRAY", "U64IMAGE1DARRAY",
  "I64IMAGE2DARRAY", "U64IMAGE2DARRAY", "I64IMAGECUBEARRAY",
  "U64IMAGECUBEARRAY", "I64IMAGE2DMS", "U64IMAGE2DMS", "I64IMAGE2DMSARRAY",
  "U64IMAGE2DMSARRAY", "TEXTURECUBEARRAY", "ITEXTURECUBEARRAY",
  "UTEXTURECUBEARRAY", "TEXTURE1D", "ITEXTURE1D", "UTEXTURE1D",
  "TEXTURE1DARRAY", "ITEXTURE1DARRAY", "UTEXTURE1DARRAY", "TEXTURE2DRECT",
  "ITEXTURE2DRECT", "UTEXTURE2DRECT", "TEXTUREBUFFER", "ITEXTUREBUFFER",
  "UTEXTUREBUFFER", "TEXTURE2DMS", "ITEXTURE2DMS", "UTEXTURE2DMS",
  "TEXTURE2DMSARRAY", "ITEXTURE2DMSARRAY", "UTEXTURE2DMSARRAY",
  "F16TEXTURE1D", "F16TEXTURE2D", "F16TEXTURE3D", "F16TEXTURE2DRECT",
  "F16TEXTURECUBE", "F16TEXTURE1DARRAY", "F16TEXTURE2DARRAY",
  "F16TEXTURECUBEARRAY", "F16TEXTUREBUFFER", "F16TEXTURE2DMS",
  "F16TEXTURE2DMSARRAY", "SUBPASSINPUT", "SUBPASSINPUTMS", "ISUBPASSINPUT",
  "ISUBPASSINPUTMS", "USUBPASSINPUT", "USUBPASSINPUTMS", "F16SUBPASSINPUT",
  "F16SUBPASSINPUTMS", "SPIRV_INSTRUCTION", "SPIRV_EXECUTION_MODE",
  "SPIRV_EXECUTION_MODE_ID", "SPIRV_DECORATE", "SPIRV_DECORATE_ID",
  "SPIRV_DECORATE_STRING", "SPIRV_TYPE", "SPIRV_STORAGE_CLASS",
  "SPIRV_BY_REFERENCE", "SPIRV_LITERAL", "ATTACHMENTEXT", "IATTACHMENTEXT",
  "UATTACHMENTEXT", "LEFT_OP", "RIGHT_OP", "INC_OP", "DEC_OP", "LE_OP",
  "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "XOR_OP", "MUL_ASSIGN",
  "DIV_ASSIGN", "ADD_ASSIGN", "MOD_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "SUB_ASSIGN", "STRING_LITERAL",
  "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACKET", "RIGHT_BRACKET",
  "LEFT_BRACE", "RIGHT_BRACE", "DOT", "ELLIPSIS", "COMMA", "COLON",
  "EQUAL", "SEMICOLON", "BANG", "DASH", "TILDE", "PLUS", "STAR", "SLASH",
  "PERCENT", "LEFT_ANGLE", "RIGHT_ANGLE", "VERTICAL_BAR", "CARET",
  "AMPERSAND", "QUESTION", "INVARIANT", "HIGH_PRECISION",
  "MEDIUM_PRECISION", "LOW_PRECISION", "PRECISION", "PACKED", "RESOURCE",
  "SUPERP", "FLOATCONSTANT", "INTCONSTANT", "UINTCONSTANT", "BOOLCONSTANT",
  "IDENTIFIER", "TYPE_NAME", "CENTROID", "IN", "OUT", "INOUT", "STRUCT",
  "VOID", "WHILE", "BREAK", "CONTINUE", "DO", "ELSE", "FOR", "IF",
  "DISCARD", "RETURN", "SWITCH", "CASE", "DEFAULT", "TERMINATE_INVOCATION",
  "TERMINATE_RAY", "IGNORE_INTERSECTION", "UNIFORM", "SHARED", "BUFFER",
  "TILEIMAGEEXT", "FLAT", "SMOOTH", "LAYOUT", "DOUBLECONSTANT",
  "INT16CONSTANT", "UINT16CONSTANT", "FLOAT16CONSTANT", "INT32CONSTANT",
  "UINT32CONSTANT", "INT64CONSTANT", "UINT64CONSTANT", "SUBROUTINE",
  "DEMOTE", "FUNCTION", "PAYLOADNV", "PAYLOADINNV", "HITATTRNV",
  "CALLDATANV", "CALLDATAINNV", "PAYLOADEXT", "PAYLOADINEXT", "HITATTREXT",
  "CALLDATAEXT", "CALLDATAINEXT", "PATCH", "SAMPLE", "NONUNIFORM",
  "RESOURCEHEAP", "SAMPLERHEAP", "COHERENT", "VOLATILE", "RESTRICT",
  "READONLY", "WRITEONLY", "NONTEMPORAL", "DEVICECOHERENT",
  "QUEUEFAMILYCOHERENT", "WORKGROUPCOHERENT", "SUBGROUPCOHERENT",
  "NONPRIVATE", "SHADERCALLCOHERENT", "NOPERSPECTIVE", "EXPLICITINTERPAMD",
  "PERVERTEXEXT", "PERVERTEXNV", "PERPRIMITIVENV", "PERVIEWNV",
  "PERTASKNV", "PERPRIMITIVEEXT", "TASKPAYLOADWORKGROUPEXT", "PRECISE",
  "$accept", "variable_identifier", "primary_expression",
  "postfix_expression", "integer_expression", "function_call",
  "function_call_or_method", "function_call_generic",
  "function_call_header_no_parameters",
  "function_call_header_with_parameters", "function_call_header",
  "function_identifier", "unary_expression", "unary_operator",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_xor_expression",
  "logical_or_expression", "conditional_expression", "$@1",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "block_structure", "$@2",
  "identifier_list", "function_prototype",
  "function_prototype_with_spirv_variadic_tail", "function_declarator",
  "function_header_with_parameters", "function_header",
  "parameter_declarator", "parameter_declaration",
  "parameter_type_specifier", "init_declarator_list", "single_declaration",
  "fully_specified_type", "invariant_qualifier", "interpolation_qualifier",
  "layout_qualifier", "layout_qualifier_id_list", "layout_qualifier_id",
  "precise_qualifier", "type_qualifier", "single_type_qualifier",
  "storage_qualifier", "non_uniform_qualifier", "type_name_list",
  "type_specifier", "array_specifier", "type_parameter_specifier_opt",
  "type_parameter_specifier", "type_parameter_specifier_list",
  "type_specifier_nonarray", "precision_qualifier", "struct_specifier",
  "$@3", "$@4", "struct_declaration_list", "struct_declaration_with_heap",
  "block_heap_inner_structure", "$@5", "struct_declaration_without_heap",
  "struct_declaration", "struct_declarator_list", "struct_declarator",
  "initializer", "initializer_list", "declaration_statement", "statement",
  "simple_statement", "demote_statement", "compound_statement", "$@6",
  "$@7", "statement_no_new_scope", "statement_scoped", "$@8", "$@9",
  "compound_statement_no_new_scope", "statement_list",
  "expression_statement", "selection_statement",
  "selection_statement_nonattributed", "selection_rest_statement",
  "condition", "switch_statement", "switch_statement_nonattributed",
  "$@10", "switch_statement_list", "case_label", "iteration_statement",
  "iteration_statement_nonattributed", "$@11", "$@12", "$@13",
  "for_init_statement", "conditionopt", "for_rest_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "function_definition", "$@14", "attribute", "attribute_list",
  "single_attribute", "spirv_requirements_list",
  "spirv_requirements_parameter", "spirv_extension_list",
  "spirv_capability_list", "spirv_execution_mode_qualifier",
  "spirv_execution_mode_parameter_list", "spirv_execution_mode_parameter",
  "spirv_execution_mode_id_parameter_list",
  "spirv_storage_class_qualifier", "spirv_decorate_qualifier",
  "spirv_decorate_parameter_list", "spirv_decorate_parameter",
  "spirv_decorate_id_parameter_list", "spirv_decorate_id_parameter",
  "spirv_decorate_string_parameter_list", "spirv_type_specifier",
  "spirv_type_parameter_list", "spirv_type_parameter",
  "spirv_instruction_qualifier", "spirv_instruction_qualifier_list",
  "spirv_instruction_qualifier_id", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-862)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-733)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    4898,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -315,  -306,  -302,
    -278,  -274,  -250,  -240,  -204,  -862,  -862,  -862,  -862,  -862,
    -319,  -862,  -862,  -862,  -862,  -862,   -34,  -862,  -862,  -862,
    -862,  -862,  -316,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -177,  -153,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -312,  -267,  -196,  -151,  6356,  -239,  -862,  -176,  -862,
    -862,  -862,  -862,  5870,  -862,  -862,  -862,  -862,  -154,  -862,
    -862,  1010,  -862,  -862, 10244,  -133,  -862,  -862,  -862,  6842,
    -174,  -244,  -157,  -137,  -131,  -130,  -174,  -125,  -135, 14878,
    -862,   -90,  -361,  -105,  -862,  -318,  -862,   -59,   -55,  7328,
    -134,  -862,  -862,  -862, 10244,   -58,   -49,  -862,  -232,  -862,
     -14,  -126,  -862,  -862, 13495,     8,  -862,  -862,  -862,     3,
       1, 10244,   -26, 10244,  -862,     5,    11,     4,  7814,    10,
       6,  -862,  -226,  -862,  -221,    14,    15,    17,    18,  -216,
      19,    20,    21,    22,    23,    24,  -206,    12,    25,    34,
    -322,  -862,    26, 10244,  -862,    30,  -862,  -200,  -862,  -862,
    -197, 11651,  -862,  -256,  1496,  -862,  -862,    35,  -862,  -862,
    -862,  -862,  -323,  -282,  -862, 12112,  -249,  -862,   -18,  -862,
   13495, 13495,  -862, 13495,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -257,  -862,  -862,  -862,    41,  -195, 13956,
      43,  -862, 13495,  -862,    44,  -328,    33,   -55, 10244,    45,
    -862,  -862,  8300,    39,    40,  -332,  -174,  -862,    36,  -862,
    -317,    46,  -124, 13495,  -118,  -862,  -142,  -101,  -147,  -100,
      53,   -96,  -174,  -862, 14417,  -862,   -95, 13495,    51,  -135,
    -862,  8786,    42,    50, 10244,    42, 10244,  -862, 10244, 13495,
    -862,  -361,  -862,    47,  -862,  -862,   -21,   -28,   -83,  -314,
     -64,    48,    54,    56,    70,    75,  -321,    78,  -862, 12573,
    -862,    73,  -862,  -862,    83,    76,    77,  -862,    89,    91,
      81, 13034,    93, 13495,    87,    86,    90,    92,    94,  -258,
    -862,  -862,   -68,  -862,  -267,    98,    44,  -862,  -862,  -862,
    -862,  -862,  1982,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  5384,  -862, 12112,    33, 12112,  -237, 10729,  -862,
    -862, 12112, 10244,  -862,  -862,  -862,  -194,  -311,  -862,  -862,
   13495,    67,  -862,  -862, 13495,   105,  -862,  -862,  -862, 13495,
    -862,  -862,   103,   104,   111,   112,  -862,  -327,  -862,  -862,
    -191,   107,  -862,  -862,  -862,  -862,  -862,  -862,  -186,  -862,
    -183,  -862,  -862,  -182,   113,  -862,  -862,  -862,  -862,  -181,
    -862,  -180,  -862,  -862,  -862,  -862,  -862,  -172,  -862,   114,
    -862,  -170,   116,  -168,   107,  -862,  -330,  -166,  -862,   118,
     119,  -862,  -862,  -862,    42,     8,   -41,  -862,  -862, 10244,
   10244,   -40,  -862,  -862,   110,  -862,  -862,  -862, 13495, 13495,
   13495, 13495, 13495, 13495, 13495, 13495, 13495, 13495, 13495, 13495,
   13495, 13495, 13495, 13495, 13495, 13495, 13495,  -862,  -862,  -862,
     122,  -862,  2468,  -862,  -862,  -862,  2468,  -862, 13495,  -862,
    -862,   -33, 13495,   -10,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
   13495, 13495,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
   12112,  -862,  -862,   -25,  -862,  9272,  -862, 13495,   123,   120,
    -862,  -862,  -862,   126,   128,  -862,  -862,  -862,  -862,  -144,
    -127,  -862,  -325,  -862,  -317,  -862,  -317,  -862, 13495, 13495,
    -862,  -142,  -862,  -142,  -862,  -147,  -147,  -862,   131,    53,
    -862, 14417,  -862, 13495,  -862,  -862, 10244,   -27,    33,    42,
    -862,  -862,  -862,  -862,  -862,  -862,   -21,   -21,   -28,   -28,
     -83,   -83,   -83,   -83,  -314,  -314,   -64,    48,    54,    56,
      70,    75, 13495,  -862,  2468,  4412,    88,  3926,  -164,  -862,
    -162,  -862,  -862,  -862,  -862,  -862, 11190,  -862,  -862,  -862,
    -862,  -862,  -862,   133,  -862,   100,  -862,  -160,  -862,  -158,
    -862,  -156,  -862,  -152,  -862,  -150,  -148,  -862,  9758,  -862,
    -862,    -8,   130,   120,    99,   136,   138,  -862,  -862,  4412,
     137,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -862, 13495,  -862,   132,  2954, 13495,  -862,   129,
     142,    95,   141,  3440,  -862,   143,  -862, 12112,  -862,  -862,
    -862,  -146, 13495,  2954,   137,  -862,  -862,  2468,  -862,   135,
     120,  -862,  -862,  2468,   144,  -862,  -862
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   176,   237,   235,   236,   234,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   238,   239,   240,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     375,   376,   377,   378,   379,   380,   381,   401,   402,   403,
     404,   405,   406,   407,   416,   429,   430,   417,   418,   420,
     419,   421,   422,   423,   424,   425,   426,   427,   428,   185,
     186,   264,   265,   263,   266,   267,   262,   268,   275,   276,
     273,   274,   271,   272,   269,   270,   307,   308,   309,   319,
     320,   321,   304,   305,   306,   316,   317,   318,   301,   302,
     303,   313,   314,   315,   298,   299,   300,   310,   311,   312,
     277,   278,   279,   322,   323,   324,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   334,   335,
     336,   292,   293,   294,   346,   347,   348,   295,   296,   297,
     358,   359,   360,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   373,
     370,   371,   372,   557,   558,   559,   560,   564,   566,   568,
     192,   569,   193,   561,   562,   565,   385,   386,   409,   412,
     374,   383,   384,   400,   382,   431,   432,   435,   436,   437,
     439,   440,   441,   443,   444,   445,   447,   448,   544,   545,
     408,   410,   411,   387,   388,   389,   433,   390,   394,   395,
     398,   438,   442,   446,   391,   392,   396,   397,   434,   393,
     399,   478,   480,   481,   482,   484,   485,   486,   488,   489,
     490,   492,   493,   494,   496,   497,   498,   500,   501,   502,
     504,   505,   506,   508,   509,   510,   512,   513,   514,   516,
     517,   518,   520,   521,   479,   483,   487,   491,   495,   503,
     507,   511,   499,   515,   519,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   413,   414,   415,
     449,   458,   460,   454,   459,   461,   462,   464,   465,   466,
     468,   469,   470,   472,   473,   474,   476,   477,   450,   451,
     452,   463,   453,   455,   456,   457,   467,   471,   475,   549,
     550,   553,   554,   555,   556,   551,   552,     0,     0,     0,
       0,     0,     0,     0,     0,   174,   175,   546,   547,   548,
       0,   669,   145,   572,   573,   574,     0,   571,   180,   178,
     179,   177,     0,   233,   181,   183,   184,   182,   147,   146,
       0,   215,   563,   195,   197,   191,   199,   201,   196,   198,
     194,   200,   202,   187,   188,   218,   189,   190,   203,   210,
     211,   212,   213,   214,   204,   205,   206,   207,   208,   209,
     148,   149,   151,   150,   152,   154,   155,   153,   217,   162,
     668,     0,   670,     0,   121,   120,     0,   133,   138,   169,
     168,   166,   170,     0,   163,   165,   171,   143,   228,   167,
     570,     0,   665,   667,     0,     0,   172,   173,   567,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     577,     0,     0,     0,   101,     0,    95,     0,   110,     0,
       0,   129,   122,   131,     0,   132,     0,    99,   139,   104,
     108,     0,   164,   144,     0,   221,   227,     1,   666,     0,
     121,   120,     0,     0,    98,     0,     0,   121,   120,     0,
       0,   677,     0,   735,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   675,
       0,   673,     0,     0,   575,   159,   161,     0,   157,   219,
       0,     0,   102,     0,     0,   671,   111,     0,   123,   114,
     128,   130,   125,   134,   124,     0,   140,   106,     0,   105,
       0,     0,     9,     0,    44,    43,    45,    42,     5,     6,
       7,     8,     2,    16,    14,    15,    17,    10,    11,    12,
      13,     3,    18,    37,    20,    25,    26,     0,     0,    30,
       0,   231,     0,    36,   230,     0,   222,   112,     0,     0,
      96,    97,     0,   174,   175,     0,     0,   733,     0,   685,
       0,     0,     0,     0,     0,   702,     0,     0,     0,     0,
       0,     0,     0,   727,     0,   700,     0,     0,     0,     0,
     100,     0,     0,     0,   580,     0,   579,   586,     0,     0,
     156,     0,   216,     0,   223,    46,    50,    53,    56,    61,
      64,    66,    68,    70,    72,    74,    76,     0,    34,     0,
     103,   613,   622,   626,     0,     0,     0,   647,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
      79,    92,     0,   600,     0,   171,   143,   603,   624,   602,
     610,   601,     0,   604,   605,   628,   606,   635,   607,   608,
     643,   609,     0,   115,     0,   126,     0,   135,     0,   594,
     142,     0,     0,   109,    38,    39,     0,   228,    22,    23,
       0,     0,    28,    27,     0,   233,    31,    33,    40,     0,
     229,   113,   174,   175,     0,     0,   737,     0,   738,   678,
       0,     0,   736,   697,   693,   694,   695,   696,     0,   691,
       0,    94,   698,     0,     0,   712,   713,   714,   715,     0,
     710,     0,   719,   720,   721,   722,   718,     0,   716,     0,
     723,     0,     0,     0,     2,   731,   228,     0,   729,     0,
       0,   672,   674,   584,     0,   592,     0,   590,   578,     0,
     581,     0,   582,   587,     0,   160,   158,   220,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    77,   224,   225,
       0,   612,     0,   645,   658,   657,     0,   649,     0,   661,
     659,     0,     0,     0,   642,   662,   663,   664,   611,    82,
      83,    85,    84,    87,    88,    89,    90,    91,    86,    81,
       0,     0,   627,   623,   625,   629,   636,   644,   127,   137,
       0,   597,   598,     0,   141,     0,     4,     0,     0,    24,
      21,    32,   232,     0,     0,   117,   116,   681,   683,     0,
       0,   734,     0,   687,     0,   686,     0,   689,     0,     0,
     704,     0,   703,     0,   706,     0,     0,   708,     0,     0,
     728,     0,   725,     0,   701,   676,     0,     0,   593,     0,
     588,   583,   576,    47,    48,    49,    52,    51,    54,    55,
      59,    60,    57,    58,    62,    63,    65,    67,    69,    71,
      73,    75,     0,   226,   614,     0,     0,     0,     0,   660,
       0,   641,    80,    93,   136,   595,     0,   107,    41,    19,
     119,   118,   679,     0,   680,     0,   692,     0,   699,     0,
     711,     0,   717,     0,   724,     0,     0,   730,     0,   589,
     591,     0,     0,   633,     0,     0,     0,   652,   651,   654,
     620,   637,   596,   599,   682,   684,   688,   690,   705,   707,
     709,   726,   585,     0,   615,     0,     0,     0,   653,     0,
       0,   632,     0,     0,   630,     0,    78,     0,   617,   646,
     616,     0,   655,     0,   620,   619,   621,   639,   634,     0,
     656,   650,   631,   640,     0,   648,   638
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -862,  -584,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
    -862,  -862,  -456,  -862,  -405,  -404,  -484,  -408,  -266,  -265,
    -264,  -263,  -261,  -268,  -862,  -518,  -862,  -531,  -862,  -523,
    -572,    13,  -862,  -862,  -862,     7,  -862,  -409,  -407,  -403,
      66,  -420,    68,  -862,  -862,  -433,  -862,  -862,  -862,  -862,
     -86,  -862,  -410,  -413,  -862,     9,  -862,     0,  -445,  -862,
    -862,  -862,  -535,   180,  -862,  -862,  -862,   -81,   -77,  -862,
    -862,  -588,  -605,  -578,  -349,  -669,  -862,  -376,  -656,  -861,
    -862,  -440,  -862,  -862,  -450,  -449,  -862,  -862,    96,  -769,
    -373,  -862,  -136,  -862,  -411,  -862,  -132,  -862,  -862,  -862,
    -862,  -128,  -862,  -862,  -862,  -862,  -862,  -862,  -862,  -862,
     121,  -862,  -862,     2,  -862,   -62,  -199,  -461,  -862,  -862,
    -862,  -310,  -313,  -309,  -862,  -862,  -308,  -307,  -305,  -320,
    -304,  -862,  -324,  -303,  -862,  -412,  -576
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   561,   562,   563,   848,   564,   565,   566,   567,   568,
     569,   570,   659,   572,   626,   627,   628,   629,   630,   631,
     632,   633,   634,   635,   636,   660,   912,   661,   830,   662,
     755,   663,   411,   692,   471,   664,   486,   413,   414,   415,
     461,   462,   463,   416,   417,   418,   419,   420,   421,   517,
     518,   422,   423,   424,   425,   573,   520,   638,   523,   475,
     476,   575,   428,   429,   430,   618,   513,   613,   614,   615,
     886,   616,   617,   766,   767,   690,   843,   667,   668,   669,
     670,   671,   802,   952,   989,   981,   982,   983,   990,   672,
     673,   674,   675,   984,   955,   676,   677,   985,  1004,   678,
     679,   680,   915,   806,   917,   959,   979,   980,   681,   431,
     432,   433,   457,   682,   510,   511,   490,   491,   859,   860,
     435,   728,   729,   733,   436,   437,   739,   740,   747,   748,
     751,   438,   757,   758,   439,   492,   493
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     427,   482,   434,   637,   689,   464,   482,   412,   697,   426,
     472,   773,   722,   410,   746,   838,   834,   839,   571,   842,
     696,   732,   844,   536,   483,   479,   770,   480,   722,   483,
     576,   481,   487,   914,   506,   760,   488,   771,   706,   528,
     796,   716,   785,   786,   717,  -732,   857,   775,   716,   464,
     515,   472,  -732,   521,   709,   608,   723,   448,   521,   440,
     609,   684,   450,   474,   847,   625,   710,   522,   441,   756,
     472,   464,   442,   454,   516,   731,   718,   797,   464,   787,
     788,   858,   474,   718,   694,   695,   731,   685,   687,   731,
     724,   725,   726,   727,   521,   451,   443,   698,   699,   455,
     444,   731,   686,   611,   845,   819,   820,   821,   822,   823,
     824,   825,   826,   827,   828,   988,   708,   -35,   456,   700,
     639,   800,   996,   701,   445,   719,   829,   639,   811,   640,
     813,   719,   988,   719,   446,   691,   719,   625,   719,   639,
     719,   719,   534,   466,   521,   719,   467,   840,   625,   587,
     916,   625,   535,   689,   589,   689,   588,   689,   528,   595,
     689,   590,   528,   625,   494,   773,   596,   495,   464,   603,
     447,   924,   464,   851,   720,   620,   604,   849,   622,   458,
     703,   846,   621,   625,   861,   623,   887,   704,   831,   863,
     753,   588,   865,   867,   870,   872,   864,   452,   472,   866,
     868,   871,   873,   874,   769,   877,   611,   880,   611,   882,
     875,   960,   878,   961,   881,   966,   883,   967,   831,   968,
     831,   453,   864,   969,   868,   970,   871,   971,  1003,   999,
     875,   459,   878,   932,   883,   468,   831,   489,   933,   474,
     773,   529,   496,   498,   500,   502,   504,   505,   508,   482,
     934,   497,   484,   852,   495,   935,   538,   963,   834,   539,
     742,   743,   744,   745,   552,   735,   736,   737,   738,   783,
     784,   499,   483,   479,   495,   480,   509,   501,   503,   481,
     495,   495,   769,   507,   730,   918,   495,   495,   514,   920,
     734,   746,   746,   495,   789,   790,   938,   732,   948,   922,
     923,   900,   901,   902,   903,   722,   519,   741,   749,   689,
     495,   495,   752,   759,   831,   495,   495,   832,   998,   524,
     888,   350,   893,   894,   895,   625,   625,   625,   625,   625,
     625,   625,   625,   625,   625,   625,   625,   625,   625,   625,
     625,   889,   889,   773,   890,   891,   756,   834,   756,   831,
     731,   731,   919,   532,   925,   889,   472,   926,   949,   781,
     769,   782,   533,   731,   537,   731,   353,   354,   355,   778,
     779,   780,   831,   921,   831,   973,   896,   897,   577,   898,
     899,   904,   905,   578,   521,   579,   582,   605,   586,   951,
     580,   928,   953,   693,   585,   689,   581,   592,   591,   593,
     594,   597,   598,   599,   600,   601,   602,   606,   607,   639,
     683,   610,   625,   625,   619,   465,   702,   707,   -34,   534,
     714,   715,   717,   473,   426,   625,   750,   625,   761,   768,
     794,   427,   426,   434,   427,   769,   953,   795,   412,   427,
     426,   434,   986,   426,   410,   791,   485,   721,   426,   512,
     792,   793,   801,   765,   991,   798,   689,   803,   777,   465,
     526,   804,   805,   807,   465,   808,   809,   812,   426,  1000,
     814,   815,   -36,   426,   574,   816,   769,   817,   850,   818,
     -29,   465,   954,   473,   853,   854,   855,   856,   465,   892,
     426,   862,   426,   884,   885,   869,   876,   426,   879,   913,
     929,   930,   831,   931,   944,   483,   964,   956,   965,   974,
     975,   976,   977,   612,   992,  -618,   987,   993,   994,   641,
    1005,   997,   426,  1006,   666,   906,   954,   907,   911,   908,
     530,   909,   531,   665,   910,   776,   449,   774,   769,   772,
     950,   957,   995,  1001,   958,  1002,   835,   762,   978,   483,
     836,   936,   478,   525,   837,   942,   937,   946,     0,     0,
     939,     0,     0,     0,   940,   941,     0,     0,     0,     0,
       0,   943,     0,     0,     0,   945,     0,     0,   465,   711,
     947,     0,   465,     0,     0,     0,     0,   426,     0,     0,
       0,   426,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   764,     0,     0,   612,     0,   612,     0,   612,     0,
     426,     0,     0,   426,     0,   426,     0,   426,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   666,     0,     0,     0,     0,     0,     0,     0,
       0,   665,   427,     0,     0,     0,     0,     0,     0,     0,
       0,   426,   612,     0,     0,     0,     0,     0,     0,     0,
       0,   426,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   764,
     612,     0,     0,     0,     0,     0,     0,     0,   426,   426,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   666,     0,     0,     0,   666,     0,     0,     0,
       0,   665,     0,     0,     0,   665,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   612,     0,     0,     0,     0,
       0,     0,     0,     0,   426,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   612,     0,     0,     0,
       0,     0,     0,     0,     0,   426,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   666,   666,     0,   666,     0,   434,
       0,     0,     0,   665,   665,     0,   665,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   612,     0,
       0,     0,     0,     0,     0,     0,     0,   426,     0,   666,
       0,     0,     0,     0,     0,     0,     0,     0,   665,     0,
       0,     0,     0,     0,     0,     0,   666,     0,     0,     0,
       0,     0,     0,   666,     0,   665,     0,     0,     0,     0,
       0,     0,   665,   666,     0,     0,     0,   666,     0,     0,
       0,     0,   665,   666,     0,     0,   665,     0,     0,     0,
     477,     0,   665,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   350,     0,     0,     0,
       0,     0,     0,     0,     0,   351,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   352,
     353,   354,   355,   356,     0,     0,     0,     0,     0,     0,
       0,     0,   357,   358,   359,   360,   361,   362,   363,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   364,   365,   366,   367,   368,   369,
     370,     0,     0,     0,     0,     0,     0,     0,     0,   371,
       0,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,     0,     0,
     540,   541,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   542,
     543,     0,   350,     0,   641,   642,     0,     0,     0,     0,
       0,   643,   544,   545,   546,   547,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   352,   353,   354,   355,   356,
       0,     0,     0,   548,   549,   550,   551,   552,   357,   358,
     359,   360,   361,   362,   363,   644,   645,   646,   647,     0,
     648,   649,   650,   651,   652,   653,   654,   655,   656,   657,
     364,   365,   366,   367,   368,   369,   370,   553,   554,   555,
     556,   557,   558,   559,   560,   371,   658,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,     0,     0,   540,   541,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   542,   543,     0,   350,     0,
     641,   833,     0,     0,     0,     0,     0,   643,   544,   545,
     546,   547,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   352,   353,   354,   355,   356,     0,     0,     0,   548,
     549,   550,   551,   552,   357,   358,   359,   360,   361,   362,
     363,   644,   645,   646,   647,     0,   648,   649,   650,   651,
     652,   653,   654,   655,   656,   657,   364,   365,   366,   367,
     368,   369,   370,   553,   554,   555,   556,   557,   558,   559,
     560,   371,   658,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
       0,     0,   540,   541,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   542,   543,     0,   350,     0,   641,     0,     0,     0,
       0,     0,     0,   643,   544,   545,   546,   547,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   352,   353,   354,
     355,   356,     0,     0,     0,   548,   549,   550,   551,   552,
     357,   358,   359,   360,   361,   362,   363,   644,   645,   646,
     647,     0,   648,   649,   650,   651,   652,   653,   654,   655,
     656,   657,   364,   365,   366,   367,   368,   369,   370,   553,
     554,   555,   556,   557,   558,   559,   560,   371,   658,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,     0,     0,   540,   541,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   542,   543,     0,
     350,     0,   524,     0,     0,     0,     0,     0,     0,   643,
     544,   545,   546,   547,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   352,   353,   354,   355,   356,     0,     0,
       0,   548,   549,   550,   551,   552,   357,   358,   359,   360,
     361,   362,   363,   644,   645,   646,   647,     0,   648,   649,
     650,   651,   652,   653,   654,   655,   656,   657,   364,   365,
     366,   367,   368,   369,   370,   553,   554,   555,   556,   557,
     558,   559,   560,   371,   658,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,     0,     0,   540,   541,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   542,   543,     0,   350,     0,     0,     0,
       0,     0,     0,     0,     0,   643,   544,   545,   546,   547,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   352,
     353,   354,   355,   356,     0,     0,     0,   548,   549,   550,
     551,   552,   357,   358,   359,   360,   361,   362,   363,   644,
     645,   646,   647,     0,   648,   649,   650,   651,   652,   653,
     654,   655,   656,   657,   364,   365,   366,   367,   368,   369,
     370,   553,   554,   555,   556,   557,   558,   559,   560,   371,
     658,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,     0,     0,
     540,   541,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   542,
     543,     0,   350,     0,     0,     0,     0,     0,     0,     0,
       0,   643,   544,   545,   546,   547,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   352,   353,   354,   355,   356,
       0,     0,     0,   548,   549,   550,   551,   552,   357,   358,
     359,   360,   361,   362,   363,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     364,   365,   366,   367,   368,   369,   370,   553,   554,   555,
     556,   557,   558,   559,   560,   371,     0,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,     0,     0,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,     0,     0,   540,   541,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   542,   543,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   544,   545,
     546,   547,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   352,   353,   354,   355,     0,     0,     0,     0,   548,
     549,   550,   551,   552,   357,   358,   359,   360,   361,   362,
     363,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   364,   365,   366,   367,
     368,   369,   370,   553,   554,   555,   556,   557,   558,   559,
     560,   371,     0,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   350,     0,     0,     0,     0,     0,
       0,     0,     0,   351,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   352,   353,   354,
     355,   356,     0,     0,     0,     0,     0,     0,     0,     0,
     357,   358,   359,   360,   361,   362,   363,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   364,   365,   366,   367,   368,   369,   370,     0,
       0,     0,     0,     0,     0,     0,     0,   371,     0,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,     0,     0,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   352,   353,   354,   355,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   357,   358,   359,   360,
     361,   362,   363,   644,     0,     0,   647,     0,   648,   649,
       0,     0,   652,     0,     0,     0,     0,     0,   364,   365,
     366,   367,   368,   369,   370,     0,     0,     0,     0,     0,
       0,     0,     0,   371,     0,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,     0,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   469,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   352,
     353,   354,   355,     0,     0,     0,     0,     0,     0,     0,
       0,   470,   357,   358,   359,   360,   361,   362,   363,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   364,   365,   366,   367,   368,   369,
     370,     0,     0,     0,     0,     0,     0,     0,     0,   371,
       0,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,     0,     0,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   460,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   352,   353,   354,   355,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   357,   358,
     359,   360,   361,   362,   363,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     364,   365,   366,   367,   368,   369,   370,     0,     0,     0,
       0,     0,     0,     0,     0,   371,     0,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,     0,     0,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   350,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   352,   353,   354,   355,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   357,   358,   359,   360,   361,   362,
     363,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   364,   365,   366,   367,
     368,   369,   370,     0,     0,     0,     0,     0,     0,     0,
       0,   371,     0,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,     0,     0,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   527,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   352,   353,   354,
     355,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     357,   358,   359,   360,   361,   362,   363,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   364,   365,   366,   367,   368,   369,   370,     0,
       0,     0,     0,     0,     0,     0,     0,   371,     0,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,     0,     0,     0,   340,   341,   342,   343,
     344,   583,   584,   347,   348,   349,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   460,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   352,   353,   354,   355,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   357,   358,   359,   360,
     361,   362,   363,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   364,   365,
     366,   367,   368,   369,   370,     0,     0,     0,     0,     0,
       0,     0,     0,   371,     0,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,     0,
       0,     0,   340,   341,   342,   343,   344,   712,   713,   347,
     348,   349,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   527,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   352,
     353,   354,   355,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   357,   358,   359,   360,   361,   362,   363,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   364,   365,   366,   367,   368,   369,
     370,     0,     0,     0,     0,     0,     0,     0,     0,   371,
       0,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,     0,     0,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   763,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   352,   353,   354,   355,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   357,   358,
     359,   360,   361,   362,   363,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     364,   365,   366,   367,   368,   369,   370,     0,     0,     0,
       0,     0,     0,     0,     0,   371,     0,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,     0,     0,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   927,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   352,   353,   354,   355,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   357,   358,   359,   360,   361,   362,
     363,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   364,   365,   366,   367,
     368,   369,   370,     0,     0,     0,     0,     0,     0,     0,
       0,   371,     0,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,     0,     0,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   972,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   352,   353,   354,
     355,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     357,   358,   359,   360,   361,   362,   363,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   364,   365,   366,   367,   368,   369,   370,     0,
       0,     0,     0,     0,     0,     0,     0,   371,     0,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,     0,     0,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   352,   353,   354,   355,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   357,   358,   359,   360,
     361,   362,   363,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   364,   365,
     366,   367,   368,   369,   370,     0,     0,     0,     0,     0,
       0,     0,     0,   371,     0,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
       0,     0,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,     0,   181,     0,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,     0,     0,
       0,     0,     0,     0,   343,     0,     0,     0,   347,   348,
     349,     0,     0,   540,   541,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   542,   543,     0,     0,     0,   688,   841,     0,
       0,     0,     0,     0,     0,   544,   545,   546,   547,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   548,   549,   550,   551,
     552,   357,     0,     0,     0,     0,   362,   363,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     553,   554,   555,   556,   557,   558,   559,   560,     0,     0,
     372,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   385,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,     0,     0,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,     0,   181,     0,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,     0,
       0,     0,     0,     0,     0,   343,     0,     0,     0,   347,
     348,   349,     0,     0,   540,   541,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   542,   543,     0,     0,     0,   688,   962,
       0,     0,     0,     0,     0,     0,   544,   545,   546,   547,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   548,   549,   550,
     551,   552,   357,     0,     0,     0,     0,   362,   363,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   553,   554,   555,   556,   557,   558,   559,   560,     0,
       0,   372,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   385,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,     0,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,     0,   181,     0,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
       0,     0,     0,     0,     0,     0,   343,     0,     0,     0,
     347,   348,   349,     0,     0,   540,   541,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   542,   543,     0,     0,   624,     0,
       0,     0,     0,     0,     0,     0,     0,   544,   545,   546,
     547,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   548,   549,
     550,   551,   552,   357,     0,     0,     0,     0,   362,   363,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   553,   554,   555,   556,   557,   558,   559,   560,
       0,     0,   372,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   385,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     0,     0,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,     0,   181,     0,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,     0,     0,     0,     0,     0,     0,   343,     0,     0,
       0,   347,   348,   349,     0,     0,   540,   541,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   542,   543,     0,     0,     0,
     688,     0,     0,     0,     0,     0,     0,     0,   544,   545,
     546,   547,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   548,
     549,   550,   551,   552,   357,     0,     0,     0,     0,   362,
     363,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   553,   554,   555,   556,   557,   558,   559,
     560,     0,     0,   372,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   385,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,     0,     0,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,     0,   181,     0,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,     0,     0,     0,     0,     0,     0,   343,     0,
       0,     0,   347,   348,   349,     0,     0,   540,   541,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   542,   543,     0,     0,
     799,     0,     0,     0,     0,     0,     0,     0,     0,   544,
     545,   546,   547,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     548,   549,   550,   551,   552,   357,     0,     0,     0,     0,
     362,   363,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   553,   554,   555,   556,   557,   558,
     559,   560,     0,     0,   372,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   385,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,     0,     0,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,     0,   181,     0,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,     0,     0,     0,     0,     0,     0,   343,
       0,     0,     0,   347,   348,   349,     0,     0,   540,   541,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   542,   543,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   810,
     544,   545,   546,   547,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   548,   549,   550,   551,   552,   357,     0,     0,     0,
       0,   362,   363,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   553,   554,   555,   556,   557,
     558,   559,   560,     0,     0,   372,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   385,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,     0,     0,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,     0,   181,     0,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,     0,     0,     0,     0,     0,     0,
     343,     0,     0,     0,   347,   348,   349,     0,     0,   540,
     541,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   542,   543,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   544,   545,   546,   547,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   548,   549,   550,   551,   552,   357,     0,     0,
       0,     0,   362,   363,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   553,   554,   555,   556,
     557,   558,   559,   560,     0,     0,   372,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   385,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,     0,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,     0,   181,
       0,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,     0,     0,     0,     0,     0,
       0,   343,     0,     0,     0,   347,   348,   349,     0,     0,
     540,   541,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   542,
     543,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   544,   545,   546,   547,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   548,   549,   550,   551,   552,   357,     0,
       0,     0,     0,   362,   705,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   553,   554,   555,
     556,   557,   558,   559,   560,     0,     0,   372,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     385,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,     0,     0,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,     0,
     181,     0,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,     0,     0,     0,     0,
       0,     0,   343,     0,     0,     0,   347,   348,   349,     0,
       0,   540,   541,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     542,   543,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   544,   545,   546,   547,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   548,   549,   550,   551,   754,   357,
       0,     0,     0,     0,   362,   363,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   553,   554,
     555,   556,   557,   558,   559,   560,     0,     0,   372,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   385,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
       0,   181,     0,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,     0,     0,     0,
       0,     0,     0,   343,     0,     0,     0,   347,   348,   349,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     357,     0,     0,     0,     0,   362,   363,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   372
};

static const yytype_int16 yycheck[] =
{
       0,   434,     0,   521,   535,   415,   439,     0,   543,     0,
     423,   616,   588,     0,   598,   684,   672,   686,   474,   688,
     543,   593,   691,   468,   434,   434,   614,   434,   604,   439,
     475,   434,   439,   802,   446,   607,   439,   615,   569,   459,
     361,   373,   356,   357,   376,   375,   373,   619,   373,   459,
     411,   464,   382,   376,   382,   377,   373,   376,   376,   374,
     382,   384,   378,   393,   375,   521,   394,   385,   374,   604,
     483,   481,   374,   385,   435,   593,   408,   398,   488,   393,
     394,   408,   393,   408,   540,   541,   604,   532,   533,   607,
     407,   408,   409,   410,   376,   411,   374,   354,   355,   411,
     374,   619,   384,   513,   692,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   976,   572,   374,   385,   376,
     376,   639,   983,   380,   374,   586,   384,   376,   651,   385,
     653,   592,   993,   594,   374,   384,   597,   593,   599,   376,
     601,   602,   374,   382,   376,   606,   385,   384,   604,   375,
     806,   607,   384,   684,   375,   686,   382,   688,   578,   375,
     691,   382,   582,   619,   408,   770,   382,   411,   578,   375,
     374,   840,   582,   704,   586,   375,   382,   700,   375,   375,
     375,   375,   382,   639,   375,   382,   764,   382,   382,   375,
     602,   382,   375,   375,   375,   375,   382,   374,   611,   382,
     382,   382,   382,   375,   614,   375,   616,   375,   618,   375,
     382,   375,   382,   375,   382,   375,   382,   375,   382,   375,
     382,   374,   382,   375,   382,   375,   382,   375,   997,   375,
     382,   382,   382,   377,   382,   411,   382,   411,   382,   393,
     845,   375,   441,   442,   443,   444,   445,   446,   447,   682,
     377,   408,   385,   709,   411,   382,   382,   926,   914,   385,
     407,   408,   409,   410,   411,   407,   408,   409,   410,   352,
     353,   408,   682,   682,   411,   682,   411,   408,   408,   682,
     411,   411,   692,   408,   408,   808,   411,   411,   378,   812,
     408,   875,   876,   411,   358,   359,   868,   869,   886,   830,
     831,   785,   786,   787,   788,   881,   411,   408,   408,   840,
     411,   411,   408,   408,   382,   411,   411,   385,   987,   378,
     765,   376,   778,   779,   780,   781,   782,   783,   784,   785,
     786,   787,   788,   789,   790,   791,   792,   793,   794,   795,
     796,   382,   382,   948,   385,   385,   881,  1003,   883,   382,
     868,   869,   385,   411,   379,   382,   769,   382,   385,   387,
     770,   389,   411,   881,   378,   883,   400,   401,   402,   390,
     391,   392,   382,   383,   382,   383,   781,   782,   375,   783,
     784,   789,   790,   382,   376,   411,   382,   375,   382,   912,
     385,   847,   915,   411,   384,   926,   385,   382,   384,   382,
     382,   382,   382,   382,   382,   382,   382,   382,   374,   376,
     375,   385,   868,   869,   384,   415,   375,   374,   374,   374,
     381,   381,   376,   423,   415,   881,   373,   883,   377,   379,
     360,   431,   423,   431,   434,   845,   959,   362,   431,   439,
     431,   439,   973,   434,   431,   397,   439,   411,   439,   449,
     396,   395,   379,   411,   977,   377,   987,   374,   411,   459,
     458,   385,   385,   374,   464,   374,   385,   374,   459,   992,
     383,   385,   374,   464,   474,   385,   886,   385,   411,   385,
     375,   481,   915,   483,   381,   381,   375,   375,   488,   379,
     481,   384,   483,   375,   375,   382,   382,   488,   382,   377,
     377,   375,   382,   375,   373,   915,   373,   419,   408,   379,
     411,   375,   374,   513,   385,   378,   384,   375,   423,   378,
     385,   378,   513,   379,   524,   791,   959,   792,   796,   793,
     464,   794,   464,   524,   795,   621,   356,   618,   948,   616,
     889,   917,   982,   993,   917,   994,   682,   609,   959,   959,
     682,   864,   431,   457,   682,   875,   866,   881,    -1,    -1,
     869,    -1,    -1,    -1,   871,   873,    -1,    -1,    -1,    -1,
      -1,   876,    -1,    -1,    -1,   879,    -1,    -1,   578,   577,
     883,    -1,   582,    -1,    -1,    -1,    -1,   578,    -1,    -1,
      -1,   582,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   611,    -1,    -1,   614,    -1,   616,    -1,   618,    -1,
     611,    -1,    -1,   614,    -1,   616,    -1,   618,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   672,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   672,   682,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   682,   692,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   692,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   769,
     770,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   769,   770,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   802,    -1,    -1,    -1,   806,    -1,    -1,    -1,
      -1,   802,    -1,    -1,    -1,   806,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   845,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   845,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   886,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   886,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   914,   915,    -1,   917,    -1,   917,
      -1,    -1,    -1,   914,   915,    -1,   917,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   948,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   948,    -1,   959,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   959,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   976,    -1,    -1,    -1,
      -1,    -1,    -1,   983,    -1,   976,    -1,    -1,    -1,    -1,
      -1,    -1,   983,   993,    -1,    -1,    -1,   997,    -1,    -1,
      -1,    -1,   993,  1003,    -1,    -1,   997,    -1,    -1,    -1,
       0,    -1,  1003,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   376,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   385,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,
     400,   401,   402,   403,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   412,   413,   414,   415,   416,   417,   418,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   434,   435,   436,   437,   438,   439,
     440,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   449,
      -1,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,    -1,    -1,
     354,   355,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,
     374,    -1,   376,    -1,   378,   379,    -1,    -1,    -1,    -1,
      -1,   385,   386,   387,   388,   389,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   399,   400,   401,   402,   403,
      -1,    -1,    -1,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,    -1,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   435,   436,   437,   438,   439,   440,   441,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,    -1,    -1,   354,   355,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   373,   374,    -1,   376,    -1,
     378,   379,    -1,    -1,    -1,    -1,    -1,   385,   386,   387,
     388,   389,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   399,   400,   401,   402,   403,    -1,    -1,    -1,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,    -1,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
      -1,    -1,   354,   355,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   373,   374,    -1,   376,    -1,   378,    -1,    -1,    -1,
      -1,    -1,    -1,   385,   386,   387,   388,   389,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,   400,   401,
     402,   403,    -1,    -1,    -1,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,    -1,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,    -1,    -1,   354,   355,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,   374,    -1,
     376,    -1,   378,    -1,    -1,    -1,    -1,    -1,    -1,   385,
     386,   387,   388,   389,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   399,   400,   401,   402,   403,    -1,    -1,
      -1,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,    -1,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,    -1,    -1,   354,   355,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   373,   374,    -1,   376,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   385,   386,   387,   388,   389,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,
     400,   401,   402,   403,    -1,    -1,    -1,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,    -1,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,    -1,    -1,
     354,   355,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,
     374,    -1,   376,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   385,   386,   387,   388,   389,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   399,   400,   401,   402,   403,
      -1,    -1,    -1,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     434,   435,   436,   437,   438,   439,   440,   441,   442,   443,
     444,   445,   446,   447,   448,   449,    -1,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    -1,    -1,    -1,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,    -1,    -1,   354,   355,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   373,   374,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   386,   387,
     388,   389,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   399,   400,   401,   402,    -1,    -1,    -1,    -1,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,    -1,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   376,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   385,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,   400,   401,
     402,   403,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     412,   413,   414,   415,   416,   417,   418,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   434,   435,   436,   437,   438,   439,   440,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   449,    -1,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,    -1,    -1,    -1,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   399,   400,   401,   402,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   412,   413,   414,   415,
     416,   417,   418,   419,    -1,    -1,   422,    -1,   424,   425,
      -1,    -1,   428,    -1,    -1,    -1,    -1,    -1,   434,   435,
     436,   437,   438,   439,   440,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   449,    -1,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,    -1,
      -1,    -1,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   385,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,
     400,   401,   402,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   411,   412,   413,   414,   415,   416,   417,   418,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   434,   435,   436,   437,   438,   439,
     440,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   449,
      -1,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,    -1,    -1,    -1,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   381,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   399,   400,   401,   402,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   412,   413,
     414,   415,   416,   417,   418,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     434,   435,   436,   437,   438,   439,   440,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   449,    -1,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    -1,    -1,    -1,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   376,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   399,   400,   401,   402,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   412,   413,   414,   415,   416,   417,
     418,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   434,   435,   436,   437,
     438,   439,   440,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   449,    -1,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,    -1,    -1,    -1,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   381,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,   400,   401,
     402,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     412,   413,   414,   415,   416,   417,   418,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   434,   435,   436,   437,   438,   439,   440,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   449,    -1,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,    -1,    -1,    -1,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   381,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   399,   400,   401,   402,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   412,   413,   414,   415,
     416,   417,   418,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   434,   435,
     436,   437,   438,   439,   440,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   449,    -1,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,    -1,
      -1,    -1,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   381,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,
     400,   401,   402,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   412,   413,   414,   415,   416,   417,   418,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   434,   435,   436,   437,   438,   439,
     440,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   449,
      -1,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,    -1,    -1,    -1,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   378,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   399,   400,   401,   402,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   412,   413,
     414,   415,   416,   417,   418,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     434,   435,   436,   437,   438,   439,   440,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   449,    -1,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    -1,    -1,    -1,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   379,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   399,   400,   401,   402,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   412,   413,   414,   415,   416,   417,
     418,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   434,   435,   436,   437,
     438,   439,   440,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   449,    -1,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,    -1,    -1,    -1,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   379,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   399,   400,   401,
     402,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     412,   413,   414,   415,   416,   417,   418,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   434,   435,   436,   437,   438,   439,   440,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   449,    -1,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,    -1,    -1,    -1,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   399,   400,   401,   402,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   412,   413,   414,   415,
     416,   417,   418,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   434,   435,
     436,   437,   438,   439,   440,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   449,    -1,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,    -1,   183,    -1,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,    -1,    -1,
      -1,    -1,    -1,    -1,   345,    -1,    -1,    -1,   349,   350,
     351,    -1,    -1,   354,   355,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   373,   374,    -1,    -1,    -1,   378,   379,    -1,
      -1,    -1,    -1,    -1,    -1,   386,   387,   388,   389,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   407,   408,   409,   410,
     411,   412,    -1,    -1,    -1,    -1,   417,   418,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     441,   442,   443,   444,   445,   446,   447,   448,    -1,    -1,
     451,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   464,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,    -1,   183,    -1,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,    -1,
      -1,    -1,    -1,    -1,    -1,   345,    -1,    -1,    -1,   349,
     350,   351,    -1,    -1,   354,   355,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   373,   374,    -1,    -1,    -1,   378,   379,
      -1,    -1,    -1,    -1,    -1,    -1,   386,   387,   388,   389,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   407,   408,   409,
     410,   411,   412,    -1,    -1,    -1,    -1,   417,   418,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   441,   442,   443,   444,   445,   446,   447,   448,    -1,
      -1,   451,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   464,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,    -1,   183,    -1,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
      -1,    -1,    -1,    -1,    -1,    -1,   345,    -1,    -1,    -1,
     349,   350,   351,    -1,    -1,   354,   355,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   373,   374,    -1,    -1,   377,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   386,   387,   388,
     389,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   407,   408,
     409,   410,   411,   412,    -1,    -1,    -1,    -1,   417,   418,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   441,   442,   443,   444,   445,   446,   447,   448,
      -1,    -1,   451,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   464,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,    -1,   183,    -1,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    -1,    -1,    -1,    -1,    -1,    -1,   345,    -1,    -1,
      -1,   349,   350,   351,    -1,    -1,   354,   355,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   373,   374,    -1,    -1,    -1,
     378,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   386,   387,
     388,   389,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   407,
     408,   409,   410,   411,   412,    -1,    -1,    -1,    -1,   417,
     418,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   441,   442,   443,   444,   445,   446,   447,
     448,    -1,    -1,   451,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   464,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,    -1,   183,    -1,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,    -1,    -1,    -1,    -1,    -1,    -1,   345,    -1,
      -1,    -1,   349,   350,   351,    -1,    -1,   354,   355,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   373,   374,    -1,    -1,
     377,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   386,
     387,   388,   389,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     407,   408,   409,   410,   411,   412,    -1,    -1,    -1,    -1,
     417,   418,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   441,   442,   443,   444,   445,   446,
     447,   448,    -1,    -1,   451,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   464,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,    -1,   183,    -1,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,    -1,    -1,    -1,    -1,    -1,    -1,   345,
      -1,    -1,    -1,   349,   350,   351,    -1,    -1,   354,   355,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,   374,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   385,
     386,   387,   388,   389,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   407,   408,   409,   410,   411,   412,    -1,    -1,    -1,
      -1,   417,   418,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   441,   442,   443,   444,   445,
     446,   447,   448,    -1,    -1,   451,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   464,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,    -1,   183,    -1,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,    -1,    -1,    -1,    -1,    -1,    -1,
     345,    -1,    -1,    -1,   349,   350,   351,    -1,    -1,   354,
     355,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,   374,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   386,   387,   388,   389,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   407,   408,   409,   410,   411,   412,    -1,    -1,
      -1,    -1,   417,   418,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   441,   442,   443,   444,
     445,   446,   447,   448,    -1,    -1,   451,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   464,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,    -1,   183,
      -1,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,    -1,    -1,    -1,    -1,    -1,
      -1,   345,    -1,    -1,    -1,   349,   350,   351,    -1,    -1,
     354,   355,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,
     374,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   386,   387,   388,   389,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   407,   408,   409,   410,   411,   412,    -1,
      -1,    -1,    -1,   417,   418,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   441,   442,   443,
     444,   445,   446,   447,   448,    -1,    -1,   451,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     464,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,    -1,
     183,    -1,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,    -1,    -1,    -1,    -1,
      -1,    -1,   345,    -1,    -1,    -1,   349,   350,   351,    -1,
      -1,   354,   355,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     373,   374,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   386,   387,   388,   389,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   407,   408,   409,   410,   411,   412,
      -1,    -1,    -1,    -1,   417,   418,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   441,   442,
     443,   444,   445,   446,   447,   448,    -1,    -1,   451,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   464,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
      -1,   183,    -1,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,    -1,    -1,    -1,
      -1,    -1,    -1,   345,    -1,    -1,    -1,   349,   350,   351,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     412,    -1,    -1,    -1,    -1,   417,   418,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   451
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     376,   385,   399,   400,   401,   402,   403,   412,   413,   414,
     415,   416,   417,   418,   434,   435,   436,   437,   438,   439,
     440,   449,   451,   452,   453,   454,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     520,   521,   524,   526,   527,   528,   532,   533,   534,   535,
     536,   537,   540,   541,   542,   543,   544,   546,   551,   552,
     553,   598,   599,   600,   602,   609,   613,   614,   620,   623,
     374,   374,   374,   374,   374,   374,   374,   374,   376,   552,
     378,   411,   374,   374,   385,   411,   385,   601,   375,   382,
     381,   529,   530,   531,   541,   546,   382,   385,   411,   385,
     411,   523,   542,   546,   393,   548,   549,     0,   599,   526,
     527,   528,   534,   541,   385,   524,   525,   527,   528,   411,
     605,   606,   624,   625,   408,   411,   605,   408,   605,   408,
     605,   408,   605,   408,   605,   605,   624,   408,   605,   411,
     603,   604,   546,   555,   378,   411,   435,   538,   539,   411,
     545,   376,   385,   547,   378,   577,   602,   381,   530,   375,
     529,   531,   411,   411,   374,   384,   547,   378,   382,   385,
     354,   355,   373,   374,   386,   387,   388,   389,   407,   408,
     409,   410,   411,   441,   442,   443,   444,   445,   446,   447,
     448,   490,   491,   492,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   544,   546,   550,   547,   375,   382,   411,
     385,   385,   382,   347,   348,   384,   382,   375,   382,   375,
     382,   384,   382,   382,   382,   375,   382,   382,   382,   382,
     382,   382,   382,   375,   382,   375,   382,   374,   377,   382,
     385,   541,   546,   556,   557,   558,   560,   561,   554,   384,
     375,   382,   375,   382,   377,   501,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   546,   376,
     385,   378,   379,   385,   419,   420,   421,   422,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   450,   501,
     514,   516,   518,   520,   524,   544,   546,   566,   567,   568,
     569,   570,   578,   579,   580,   581,   584,   585,   588,   589,
     590,   597,   602,   375,   384,   547,   384,   547,   378,   516,
     564,   384,   522,   411,   501,   501,   518,   551,   354,   355,
     376,   380,   375,   375,   382,   418,   516,   374,   501,   382,
     394,   602,   347,   348,   381,   381,   373,   376,   408,   606,
     624,   411,   625,   373,   407,   408,   409,   410,   610,   611,
     408,   514,   519,   612,   408,   407,   408,   409,   410,   615,
     616,   408,   407,   408,   409,   410,   490,   617,   618,   408,
     373,   619,   408,   624,   411,   519,   551,   621,   622,   408,
     519,   377,   604,   378,   546,   411,   562,   563,   379,   541,
     560,   562,   557,   561,   556,   519,   539,   411,   390,   391,
     392,   387,   389,   352,   353,   356,   357,   393,   394,   358,
     359,   397,   396,   395,   360,   362,   361,   398,   377,   377,
     514,   379,   571,   374,   385,   385,   592,   374,   374,   385,
     385,   518,   374,   518,   383,   385,   385,   385,   385,   363,
     364,   365,   366,   367,   368,   369,   370,   371,   372,   384,
     517,   382,   385,   379,   567,   581,   585,   590,   564,   564,
     384,   379,   564,   565,   564,   560,   375,   375,   493,   518,
     411,   516,   501,   381,   381,   375,   375,   373,   408,   607,
     608,   375,   384,   375,   382,   375,   382,   375,   382,   382,
     375,   382,   375,   382,   375,   382,   382,   375,   382,   382,
     375,   382,   375,   382,   375,   375,   559,   562,   547,   382,
     385,   385,   379,   501,   501,   501,   503,   503,   504,   504,
     505,   505,   505,   505,   506,   506,   507,   508,   509,   510,
     511,   512,   515,   377,   578,   591,   567,   593,   518,   385,
     518,   383,   516,   516,   564,   379,   382,   379,   501,   377,
     375,   375,   377,   382,   377,   382,   611,   610,   519,   612,
     616,   615,   618,   617,   373,   619,   621,   622,   560,   385,
     563,   518,   572,   518,   534,   583,   419,   566,   579,   594,
     375,   375,   379,   564,   373,   408,   375,   375,   375,   375,
     375,   375,   379,   383,   379,   411,   375,   374,   583,   595,
     596,   574,   575,   576,   582,   586,   516,   384,   568,   573,
     577,   518,   385,   375,   423,   570,   568,   378,   564,   375,
     518,   573,   574,   578,   587,   385,   379
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   489,   490,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   492,   492,
     492,   492,   492,   492,   493,   494,   495,   496,   496,   497,
     497,   498,   498,   499,   500,   500,   500,   501,   501,   501,
     501,   501,   502,   502,   502,   502,   503,   503,   503,   503,
     504,   504,   504,   505,   505,   505,   506,   506,   506,   506,
     506,   507,   507,   507,   508,   508,   509,   509,   510,   510,
     511,   511,   512,   512,   513,   513,   514,   515,   514,   516,
     516,   517,   517,   517,   517,   517,   517,   517,   517,   517,
     517,   517,   518,   518,   519,   520,   520,   520,   520,   520,
     520,   520,   520,   520,   520,   520,   522,   521,   523,   523,
     524,   524,   524,   524,   524,   524,   525,   525,   525,   525,
     526,   526,   527,   527,   528,   529,   529,   529,   530,   530,
     530,   530,   531,   532,   532,   532,   532,   532,   533,   533,
     533,   533,   533,   534,   534,   535,   536,   536,   536,   536,
     536,   536,   536,   536,   536,   536,   537,   538,   538,   539,
     539,   539,   540,   541,   541,   542,   542,   542,   542,   542,
     542,   542,   542,   542,   542,   542,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   544,   545,
     545,   546,   546,   547,   547,   547,   547,   548,   548,   549,
     550,   550,   550,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   552,   552,   552,   554,   553,   555,   553,   556,
     556,   556,   556,   557,   559,   558,   560,   560,   561,   561,
     562,   562,   563,   563,   564,   564,   564,   564,   565,   565,
     566,   567,   567,   568,   568,   568,   568,   568,   568,   568,
     568,   569,   570,   571,   572,   570,   573,   573,   575,   574,
     576,   574,   577,   577,   578,   578,   579,   579,   580,   580,
     581,   582,   582,   583,   583,   584,   584,   586,   585,   587,
     587,   588,   588,   589,   589,   591,   590,   592,   590,   593,
     590,   594,   594,   595,   595,   596,   596,   597,   597,   597,
     597,   597,   597,   597,   597,   598,   598,   599,   599,   599,
     601,   600,   602,   603,   603,   604,   604,   605,   605,   606,
     606,   607,   607,   608,   608,   609,   609,   609,   609,   609,
     609,   610,   610,   611,   611,   611,   611,   611,   612,   612,
     613,   613,   614,   614,   614,   614,   614,   614,   614,   614,
     615,   615,   616,   616,   616,   616,   617,   617,   618,   618,
     618,   618,   618,   619,   619,   620,   620,   620,   620,   621,
     621,   622,   622,   623,   623,   624,   624,   625,   625
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     2,     2,     1,     1,     1,     2,     2,     2,
       1,     2,     3,     2,     1,     1,     1,     1,     2,     2,
       2,     4,     1,     1,     1,     1,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     2,     3,     3,     2,     2,
       4,     2,     3,     4,     2,     3,     0,     6,     1,     3,
       2,     3,     3,     4,     3,     4,     4,     4,     5,     5,
       1,     1,     2,     3,     3,     2,     3,     4,     2,     1,
       2,     1,     1,     1,     3,     4,     6,     5,     1,     2,
       3,     5,     4,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     3,     1,
       3,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     1,     1,
       3,     2,     3,     2,     3,     3,     4,     1,     0,     3,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     5,     1,
       1,     2,     2,     3,     0,     5,     1,     2,     3,     4,
       1,     3,     1,     2,     1,     3,     4,     2,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     0,     0,     5,     1,     1,     0,     2,
       0,     2,     2,     3,     1,     2,     1,     2,     1,     2,
       5,     3,     1,     1,     4,     1,     2,     0,     8,     0,
       1,     3,     2,     1,     2,     0,     6,     0,     8,     0,
       7,     1,     1,     1,     0,     2,     3,     2,     2,     2,
       3,     2,     2,     2,     2,     1,     2,     1,     1,     1,
       0,     3,     5,     1,     3,     1,     4,     1,     3,     5,
       5,     1,     3,     1,     3,     4,     6,     6,     8,     6,
       8,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       4,     6,     4,     6,     6,     8,     6,     8,     6,     8,
       1,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     6,     8,     4,     6,     1,
       3,     1,     1,     4,     6,     1,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (pParseContext, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, pParseContext); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (pParseContext);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, pParseContext);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, glslang::TParseContext* pParseContext)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], pParseContext);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, pParseContext); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, glslang::TParseContext* pParseContext)
{
  YY_USE (yyvaluep);
  YY_USE (pParseContext);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (glslang::TParseContext* pParseContext)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs YY_ATTRIBUTE_UNUSED = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, parseContext);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* variable_identifier: IDENTIFIER  */
#line 366 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.intermTypedNode) = parseContext.handleVariable((yyvsp[0].lex).loc, (yyvsp[0].lex).symbol, (yyvsp[0].lex).string);
    }
#line 5800 "MachineIndependent/glslang_tab.cpp"
    break;

  case 3: /* primary_expression: variable_identifier  */
#line 372 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 5808 "MachineIndependent/glslang_tab.cpp"
    break;

  case 4: /* primary_expression: LEFT_PAREN expression RIGHT_PAREN  */
#line 375 "MachineIndependent/glslang.y"
                                        {
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
        if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
            (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
    }
#line 5818 "MachineIndependent/glslang_tab.cpp"
    break;

  case 5: /* primary_expression: FLOATCONSTANT  */
#line 380 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 5826 "MachineIndependent/glslang_tab.cpp"
    break;

  case 6: /* primary_expression: INTCONSTANT  */
#line 383 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 5834 "MachineIndependent/glslang_tab.cpp"
    break;

  case 7: /* primary_expression: UINTCONSTANT  */
#line 386 "MachineIndependent/glslang.y"
                   {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 5843 "MachineIndependent/glslang_tab.cpp"
    break;

  case 8: /* primary_expression: BOOLCONSTANT  */
#line 390 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 5851 "MachineIndependent/glslang_tab.cpp"
    break;

  case 9: /* primary_expression: STRING_LITERAL  */
#line 393 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true);
    }
#line 5859 "MachineIndependent/glslang_tab.cpp"
    break;

  case 10: /* primary_expression: INT32CONSTANT  */
#line 396 "MachineIndependent/glslang.y"
                    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 5868 "MachineIndependent/glslang_tab.cpp"
    break;

  case 11: /* primary_expression: UINT32CONSTANT  */
#line 400 "MachineIndependent/glslang.y"
                     {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 5877 "MachineIndependent/glslang_tab.cpp"
    break;

  case 12: /* primary_expression: INT64CONSTANT  */
#line 404 "MachineIndependent/glslang.y"
                    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i64, (yyvsp[0].lex).loc, true);
    }
#line 5886 "MachineIndependent/glslang_tab.cpp"
    break;

  case 13: /* primary_expression: UINT64CONSTANT  */
#line 408 "MachineIndependent/glslang.y"
                     {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u64, (yyvsp[0].lex).loc, true);
    }
#line 5895 "MachineIndependent/glslang_tab.cpp"
    break;

  case 14: /* primary_expression: INT16CONSTANT  */
#line 412 "MachineIndependent/glslang.y"
                    {
        parseContext.explicitInt16Check((yyvsp[0].lex).loc, "16-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((short)(yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 5904 "MachineIndependent/glslang_tab.cpp"
    break;

  case 15: /* primary_expression: UINT16CONSTANT  */
#line 416 "MachineIndependent/glslang.y"
                     {
        parseContext.explicitInt16Check((yyvsp[0].lex).loc, "16-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((unsigned short)(yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 5913 "MachineIndependent/glslang_tab.cpp"
    break;

  case 16: /* primary_expression: DOUBLECONSTANT  */
#line 420 "MachineIndependent/glslang.y"
                     {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double literal");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtDouble, (yyvsp[0].lex).loc, true);
    }
#line 5924 "MachineIndependent/glslang_tab.cpp"
    break;

  case 17: /* primary_expression: FLOAT16CONSTANT  */
#line 426 "MachineIndependent/glslang.y"
                      {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat16, (yyvsp[0].lex).loc, true);
    }
#line 5933 "MachineIndependent/glslang_tab.cpp"
    break;

  case 18: /* postfix_expression: primary_expression  */
#line 433 "MachineIndependent/glslang.y"
                         {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 5941 "MachineIndependent/glslang_tab.cpp"
    break;

  case 19: /* postfix_expression: postfix_expression LEFT_BRACKET integer_expression RIGHT_BRACKET  */
#line 436 "MachineIndependent/glslang.y"
                                                                       {
        (yyval.interm.intermTypedNode) = parseContext.handleBracketDereference((yyvsp[-2].lex).loc, (yyvsp[-3].interm.intermTypedNode), (yyvsp[-1].interm.intermTypedNode));
    }
#line 5949 "MachineIndependent/glslang_tab.cpp"
    break;

  case 20: /* postfix_expression: function_call  */
#line 439 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 5957 "MachineIndependent/glslang_tab.cpp"
    break;

  case 21: /* postfix_expression: postfix_expression DOT IDENTIFIER  */
#line 442 "MachineIndependent/glslang.y"
                                        {
        (yyval.interm.intermTypedNode) = parseContext.handleDotDereference((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode), *(yyvsp[0].lex).string);
    }
#line 5965 "MachineIndependent/glslang_tab.cpp"
    break;

  case 22: /* postfix_expression: postfix_expression INC_OP  */
#line 445 "MachineIndependent/glslang.y"
                                {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "++", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "++", EOpPostIncrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 5975 "MachineIndependent/glslang_tab.cpp"
    break;

  case 23: /* postfix_expression: postfix_expression DEC_OP  */
#line 450 "MachineIndependent/glslang.y"
                                {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "--", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "--", EOpPostDecrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 5985 "MachineIndependent/glslang_tab.cpp"
    break;

  case 24: /* integer_expression: expression  */
#line 458 "MachineIndependent/glslang.y"
                 {
        parseContext.arrayIndexCheck((yyvsp[0].interm.intermTypedNode), "[]");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 5994 "MachineIndependent/glslang_tab.cpp"
    break;

  case 25: /* function_call: function_call_or_method  */
#line 465 "MachineIndependent/glslang.y"
                              {
        (yyval.interm.intermTypedNode) = parseContext.handleFunctionCall((yyvsp[0].interm).loc, (yyvsp[0].interm).function, (yyvsp[0].interm).intermNode);
        delete (yyvsp[0].interm).function;
    }
#line 6003 "MachineIndependent/glslang_tab.cpp"
    break;

  case 26: /* function_call_or_method: function_call_generic  */
#line 472 "MachineIndependent/glslang.y"
                            {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 6011 "MachineIndependent/glslang_tab.cpp"
    break;

  case 27: /* function_call_generic: function_call_header_with_parameters RIGHT_PAREN  */
#line 478 "MachineIndependent/glslang.y"
                                                       {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6020 "MachineIndependent/glslang_tab.cpp"
    break;

  case 28: /* function_call_generic: function_call_header_no_parameters RIGHT_PAREN  */
#line 482 "MachineIndependent/glslang.y"
                                                     {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6029 "MachineIndependent/glslang_tab.cpp"
    break;

  case 29: /* function_call_header_no_parameters: function_call_header VOID  */
#line 489 "MachineIndependent/glslang.y"
                                {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 6037 "MachineIndependent/glslang_tab.cpp"
    break;

  case 30: /* function_call_header_no_parameters: function_call_header  */
#line 492 "MachineIndependent/glslang.y"
                           {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 6045 "MachineIndependent/glslang_tab.cpp"
    break;

  case 31: /* function_call_header_with_parameters: function_call_header assignment_expression  */
#line 498 "MachineIndependent/glslang.y"
                                                 {
        if (parseContext.spvVersion.vulkan > 0
            && parseContext.spvVersion.vulkanRelaxed
            && (yyvsp[0].interm.intermTypedNode)->getType().containsOpaque())
        {
            (yyval.interm).intermNode = parseContext.vkRelaxedRemapFunctionArgument((yyval.interm).loc, (yyvsp[-1].interm).function, (yyvsp[0].interm.intermTypedNode));
            (yyval.interm).function = (yyvsp[-1].interm).function;
        }
        else
        {
            TParameter param = { 0, new TType, {} };
            param.type->shallowCopy((yyvsp[0].interm.intermTypedNode)->getType());

            (yyvsp[-1].interm).function->addParameter(param);
            (yyval.interm).function = (yyvsp[-1].interm).function;
            (yyval.interm).intermNode = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 6068 "MachineIndependent/glslang_tab.cpp"
    break;

  case 32: /* function_call_header_with_parameters: function_call_header_with_parameters COMMA assignment_expression  */
#line 516 "MachineIndependent/glslang.y"
                                                                       {
        if (parseContext.spvVersion.vulkan > 0
            && parseContext.spvVersion.vulkanRelaxed
            && (yyvsp[0].interm.intermTypedNode)->getType().containsOpaque())
        {
            TIntermNode* remappedNode = parseContext.vkRelaxedRemapFunctionArgument((yyvsp[-1].lex).loc, (yyvsp[-2].interm).function, (yyvsp[0].interm.intermTypedNode));
            if (remappedNode == (yyvsp[0].interm.intermTypedNode))
                (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
            else
                (yyval.interm).intermNode = parseContext.intermediate.mergeAggregate((yyvsp[-2].interm).intermNode, remappedNode, (yyvsp[-1].lex).loc);
            (yyval.interm).function = (yyvsp[-2].interm).function;
        }
        else
        {
            TParameter param = { 0, new TType, {} };
            param.type->shallowCopy((yyvsp[0].interm.intermTypedNode)->getType());

            (yyvsp[-2].interm).function->addParameter(param);
            (yyval.interm).function = (yyvsp[-2].interm).function;
            (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
        }
    }
#line 6095 "MachineIndependent/glslang_tab.cpp"
    break;

  case 33: /* function_call_header: function_identifier LEFT_PAREN  */
#line 541 "MachineIndependent/glslang.y"
                                     {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 6103 "MachineIndependent/glslang_tab.cpp"
    break;

  case 34: /* function_identifier: type_specifier  */
#line 549 "MachineIndependent/glslang.y"
                     {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 6113 "MachineIndependent/glslang_tab.cpp"
    break;

  case 35: /* function_identifier: postfix_expression  */
#line 554 "MachineIndependent/glslang.y"
                         {
        //
        // Should be a method or subroutine call, but we haven't recognized the arguments yet.
        //
        (yyval.interm).function = 0;
        (yyval.interm).intermNode = 0;

        TIntermMethod* method = (yyvsp[0].interm.intermTypedNode)->getAsMethodNode();
        if (method) {
            (yyval.interm).function = new TFunction(&method->getMethodName(), method->getType(), EOpArrayLength);
            (yyval.interm).intermNode = method->getObject();
        } else {
            TIntermSymbol* symbol = (yyvsp[0].interm.intermTypedNode)->getAsSymbolNode();
            if (symbol) {
                parseContext.reservedErrorCheck(symbol->getLoc(), symbol->getName());
                TFunction *function = new TFunction(&symbol->getName(), TType(EbtVoid));
                (yyval.interm).function = function;
            } else
                parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "function call, method, or subroutine call expected", "", "");
        }

        if ((yyval.interm).function == 0) {
            // error recover
            TString* empty = NewPoolTString("");
            (yyval.interm).function = new TFunction(empty, TType(EbtVoid), EOpNull);
        }
    }
#line 6145 "MachineIndependent/glslang_tab.cpp"
    break;

  case 36: /* function_identifier: non_uniform_qualifier  */
#line 581 "MachineIndependent/glslang.y"
                            {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 6155 "MachineIndependent/glslang_tab.cpp"
    break;

  case 37: /* unary_expression: postfix_expression  */
#line 589 "MachineIndependent/glslang.y"
                         {
        parseContext.variableCheck((yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        if (TIntermMethod* method = (yyvsp[0].interm.intermTypedNode)->getAsMethodNode())
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "incomplete method syntax", method->getMethodName().c_str(), "");
    }
#line 6166 "MachineIndependent/glslang_tab.cpp"
    break;

  case 38: /* unary_expression: INC_OP unary_expression  */
#line 595 "MachineIndependent/glslang.y"
                              {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "++", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "++", EOpPreIncrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 6175 "MachineIndependent/glslang_tab.cpp"
    break;

  case 39: /* unary_expression: DEC_OP unary_expression  */
#line 599 "MachineIndependent/glslang.y"
                              {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "--", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "--", EOpPreDecrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 6184 "MachineIndependent/glslang_tab.cpp"
    break;

  case 40: /* unary_expression: unary_operator unary_expression  */
#line 603 "MachineIndependent/glslang.y"
                                      {
        if ((yyvsp[-1].interm).op != EOpNull) {
            char errorOp[2] = {0, 0};
            switch((yyvsp[-1].interm).op) {
            case EOpNegative:   errorOp[0] = '-'; break;
            case EOpLogicalNot: errorOp[0] = '!'; break;
            case EOpBitwiseNot: errorOp[0] = '~'; break;
            default: break; // some compilers want this
            }
            (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].interm).loc, errorOp, (yyvsp[-1].interm).op, (yyvsp[0].interm.intermTypedNode));
        } else {
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
            if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
                (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
        }
    }
#line 6205 "MachineIndependent/glslang_tab.cpp"
    break;

  case 41: /* unary_expression: LEFT_PAREN type_specifier_nonarray RIGHT_PAREN unary_expression  */
#line 619 "MachineIndependent/glslang.y"
                                                                      {
        (yyval.interm.intermTypedNode) = parseContext.handleTypeCast((yyvsp[-3].lex).loc, new TType((yyvsp[-2].interm.type)), (yyvsp[0].interm.intermTypedNode));
    }
#line 6213 "MachineIndependent/glslang_tab.cpp"
    break;

  case 42: /* unary_operator: PLUS  */
#line 626 "MachineIndependent/glslang.y"
            { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNull; }
#line 6219 "MachineIndependent/glslang_tab.cpp"
    break;

  case 43: /* unary_operator: DASH  */
#line 627 "MachineIndependent/glslang.y"
            { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNegative; }
#line 6225 "MachineIndependent/glslang_tab.cpp"
    break;

  case 44: /* unary_operator: BANG  */
#line 628 "MachineIndependent/glslang.y"
            { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLogicalNot; }
#line 6231 "MachineIndependent/glslang_tab.cpp"
    break;

  case 45: /* unary_operator: TILDE  */
#line 629 "MachineIndependent/glslang.y"
            { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpBitwiseNot;
              parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise not"); }
#line 6238 "MachineIndependent/glslang_tab.cpp"
    break;

  case 46: /* multiplicative_expression: unary_expression  */
#line 635 "MachineIndependent/glslang.y"
                       { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6244 "MachineIndependent/glslang_tab.cpp"
    break;

  case 47: /* multiplicative_expression: multiplicative_expression STAR unary_expression  */
#line 636 "MachineIndependent/glslang.y"
                                                      {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "*", EOpMul, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6254 "MachineIndependent/glslang_tab.cpp"
    break;

  case 48: /* multiplicative_expression: multiplicative_expression SLASH unary_expression  */
#line 641 "MachineIndependent/glslang.y"
                                                       {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "/", EOpDiv, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6264 "MachineIndependent/glslang_tab.cpp"
    break;

  case 49: /* multiplicative_expression: multiplicative_expression PERCENT unary_expression  */
#line 646 "MachineIndependent/glslang.y"
                                                         {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "%");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "%", EOpMod, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6275 "MachineIndependent/glslang_tab.cpp"
    break;

  case 50: /* additive_expression: multiplicative_expression  */
#line 655 "MachineIndependent/glslang.y"
                                { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6281 "MachineIndependent/glslang_tab.cpp"
    break;

  case 51: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 656 "MachineIndependent/glslang.y"
                                                         {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "+", EOpAdd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6291 "MachineIndependent/glslang_tab.cpp"
    break;

  case 52: /* additive_expression: additive_expression DASH multiplicative_expression  */
#line 661 "MachineIndependent/glslang.y"
                                                         {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "-", EOpSub, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6301 "MachineIndependent/glslang_tab.cpp"
    break;

  case 53: /* shift_expression: additive_expression  */
#line 669 "MachineIndependent/glslang.y"
                          { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6307 "MachineIndependent/glslang_tab.cpp"
    break;

  case 54: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 670 "MachineIndependent/glslang.y"
                                                   {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift left");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<<", EOpLeftShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6318 "MachineIndependent/glslang_tab.cpp"
    break;

  case 55: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 676 "MachineIndependent/glslang.y"
                                                    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift right");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">>", EOpRightShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6329 "MachineIndependent/glslang_tab.cpp"
    break;

  case 56: /* relational_expression: shift_expression  */
#line 685 "MachineIndependent/glslang.y"
                       { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6335 "MachineIndependent/glslang_tab.cpp"
    break;

  case 57: /* relational_expression: relational_expression LEFT_ANGLE shift_expression  */
#line 686 "MachineIndependent/glslang.y"
                                                        {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<", EOpLessThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6345 "MachineIndependent/glslang_tab.cpp"
    break;

  case 58: /* relational_expression: relational_expression RIGHT_ANGLE shift_expression  */
#line 691 "MachineIndependent/glslang.y"
                                                          {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">", EOpGreaterThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6355 "MachineIndependent/glslang_tab.cpp"
    break;

  case 59: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 696 "MachineIndependent/glslang.y"
                                                    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<=", EOpLessThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6365 "MachineIndependent/glslang_tab.cpp"
    break;

  case 60: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 701 "MachineIndependent/glslang.y"
                                                    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">=", EOpGreaterThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6375 "MachineIndependent/glslang_tab.cpp"
    break;

  case 61: /* equality_expression: relational_expression  */
#line 709 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6381 "MachineIndependent/glslang_tab.cpp"
    break;

  case 62: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 710 "MachineIndependent/glslang.y"
                                                       {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        parseContext.referenceCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "==", EOpEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6395 "MachineIndependent/glslang_tab.cpp"
    break;

  case 63: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 719 "MachineIndependent/glslang.y"
                                                      {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        parseContext.referenceCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "!=", EOpNotEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6409 "MachineIndependent/glslang_tab.cpp"
    break;

  case 64: /* and_expression: equality_expression  */
#line 731 "MachineIndependent/glslang.y"
                          { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6415 "MachineIndependent/glslang_tab.cpp"
    break;

  case 65: /* and_expression: and_expression AMPERSAND equality_expression  */
#line 732 "MachineIndependent/glslang.y"
                                                   {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise and");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&", EOpAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6426 "MachineIndependent/glslang_tab.cpp"
    break;

  case 66: /* exclusive_or_expression: and_expression  */
#line 741 "MachineIndependent/glslang.y"
                     { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6432 "MachineIndependent/glslang_tab.cpp"
    break;

  case 67: /* exclusive_or_expression: exclusive_or_expression CARET and_expression  */
#line 742 "MachineIndependent/glslang.y"
                                                   {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise exclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^", EOpExclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6443 "MachineIndependent/glslang_tab.cpp"
    break;

  case 68: /* inclusive_or_expression: exclusive_or_expression  */
#line 751 "MachineIndependent/glslang.y"
                              { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6449 "MachineIndependent/glslang_tab.cpp"
    break;

  case 69: /* inclusive_or_expression: inclusive_or_expression VERTICAL_BAR exclusive_or_expression  */
#line 752 "MachineIndependent/glslang.y"
                                                                   {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise inclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "|", EOpInclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 6460 "MachineIndependent/glslang_tab.cpp"
    break;

  case 70: /* logical_and_expression: inclusive_or_expression  */
#line 761 "MachineIndependent/glslang.y"
                              { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6466 "MachineIndependent/glslang_tab.cpp"
    break;

  case 71: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 762 "MachineIndependent/glslang.y"
                                                            {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&&", EOpLogicalAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6476 "MachineIndependent/glslang_tab.cpp"
    break;

  case 72: /* logical_xor_expression: logical_and_expression  */
#line 770 "MachineIndependent/glslang.y"
                             { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6482 "MachineIndependent/glslang_tab.cpp"
    break;

  case 73: /* logical_xor_expression: logical_xor_expression XOR_OP logical_and_expression  */
#line 771 "MachineIndependent/glslang.y"
                                                            {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^^", EOpLogicalXor, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6492 "MachineIndependent/glslang_tab.cpp"
    break;

  case 74: /* logical_or_expression: logical_xor_expression  */
#line 779 "MachineIndependent/glslang.y"
                             { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6498 "MachineIndependent/glslang_tab.cpp"
    break;

  case 75: /* logical_or_expression: logical_or_expression OR_OP logical_xor_expression  */
#line 780 "MachineIndependent/glslang.y"
                                                          {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "||", EOpLogicalOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 6508 "MachineIndependent/glslang_tab.cpp"
    break;

  case 76: /* conditional_expression: logical_or_expression  */
#line 788 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6514 "MachineIndependent/glslang_tab.cpp"
    break;

  case 77: /* $@1: %empty  */
#line 789 "MachineIndependent/glslang.y"
                                     {
        ++parseContext.controlFlowNestingLevel;
    }
#line 6522 "MachineIndependent/glslang_tab.cpp"
    break;

  case 78: /* conditional_expression: logical_or_expression QUESTION $@1 expression COLON assignment_expression  */
#line 792 "MachineIndependent/glslang.y"
                                             {
        --parseContext.controlFlowNestingLevel;
        parseContext.boolCheck((yyvsp[-4].lex).loc, (yyvsp[-5].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-4].lex).loc, "?", (yyvsp[-5].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].lex).loc, ":", (yyvsp[-2].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].lex).loc, ":", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addSelection((yyvsp[-5].interm.intermTypedNode), (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-4].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[-4].lex).loc, ":", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()), (yyvsp[0].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()));
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 6539 "MachineIndependent/glslang_tab.cpp"
    break;

  case 79: /* assignment_expression: conditional_expression  */
#line 807 "MachineIndependent/glslang.y"
                             { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 6545 "MachineIndependent/glslang_tab.cpp"
    break;

  case 80: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 808 "MachineIndependent/glslang.y"
                                                                 {
        parseContext.arrayObjectCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array assignment");
        parseContext.opaqueCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.storage16BitAssignmentCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.specializationCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.lValueErrorCheck((yyvsp[-1].interm).loc, "assign", (yyvsp[-2].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].interm).loc, "assign", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.addAssign((yyvsp[-1].interm).loc, (yyvsp[-1].interm).op, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.assignError((yyvsp[-1].interm).loc, "assign", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()), (yyvsp[0].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()));
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
        }
    }
#line 6563 "MachineIndependent/glslang_tab.cpp"
    break;

  case 81: /* assignment_operator: EQUAL  */
#line 824 "MachineIndependent/glslang.y"
            {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAssign;
    }
#line 6572 "MachineIndependent/glslang_tab.cpp"
    break;

  case 82: /* assignment_operator: MUL_ASSIGN  */
#line 828 "MachineIndependent/glslang.y"
                 {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpMulAssign;
    }
#line 6581 "MachineIndependent/glslang_tab.cpp"
    break;

  case 83: /* assignment_operator: DIV_ASSIGN  */
#line 832 "MachineIndependent/glslang.y"
                 {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpDivAssign;
    }
#line 6590 "MachineIndependent/glslang_tab.cpp"
    break;

  case 84: /* assignment_operator: MOD_ASSIGN  */
#line 836 "MachineIndependent/glslang.y"
                 {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "%=");
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpModAssign;
    }
#line 6600 "MachineIndependent/glslang_tab.cpp"
    break;

  case 85: /* assignment_operator: ADD_ASSIGN  */
#line 841 "MachineIndependent/glslang.y"
                 {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAddAssign;
    }
#line 6609 "MachineIndependent/glslang_tab.cpp"
    break;

  case 86: /* assignment_operator: SUB_ASSIGN  */
#line 845 "MachineIndependent/glslang.y"
                 {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpSubAssign;
    }
#line 6618 "MachineIndependent/glslang_tab.cpp"
    break;

  case 87: /* assignment_operator: LEFT_ASSIGN  */
#line 849 "MachineIndependent/glslang.y"
                  {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift left assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLeftShiftAssign;
    }
#line 6627 "MachineIndependent/glslang_tab.cpp"
    break;

  case 88: /* assignment_operator: RIGHT_ASSIGN  */
#line 853 "MachineIndependent/glslang.y"
                   {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift right assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpRightShiftAssign;
    }
#line 6636 "MachineIndependent/glslang_tab.cpp"
    break;

  case 89: /* assignment_operator: AND_ASSIGN  */
#line 857 "MachineIndependent/glslang.y"
                 {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-and assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpAndAssign;
    }
#line 6645 "MachineIndependent/glslang_tab.cpp"
    break;

  case 90: /* assignment_operator: XOR_ASSIGN  */
#line 861 "MachineIndependent/glslang.y"
                 {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-xor assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpExclusiveOrAssign;
    }
#line 6654 "MachineIndependent/glslang_tab.cpp"
    break;

  case 91: /* assignment_operator: OR_ASSIGN  */
#line 865 "MachineIndependent/glslang.y"
                {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-or assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpInclusiveOrAssign;
    }
#line 6663 "MachineIndependent/glslang_tab.cpp"
    break;

  case 92: /* expression: assignment_expression  */
#line 872 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 6671 "MachineIndependent/glslang_tab.cpp"
    break;

  case 93: /* expression: expression COMMA assignment_expression  */
#line 875 "MachineIndependent/glslang.y"
                                             {
        parseContext.samplerConstructorLocationCheck((yyvsp[-1].lex).loc, ",", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addComma((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[-1].lex).loc, ",", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()), (yyvsp[0].interm.intermTypedNode)->getCompleteString(parseContext.intermediate.getEnhancedMsgs()));
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 6684 "MachineIndependent/glslang_tab.cpp"
    break;

  case 94: /* constant_expression: conditional_expression  */
#line 886 "MachineIndependent/glslang.y"
                             {
        parseContext.constantValueCheck((yyvsp[0].interm.intermTypedNode), "");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 6693 "MachineIndependent/glslang_tab.cpp"
    break;

  case 95: /* declaration: function_prototype SEMICOLON  */
#line 893 "MachineIndependent/glslang.y"
                                   {
        parseContext.handleFunctionDeclarator((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).function, true /* prototype */);
        (yyval.interm.intermNode) = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
#line 6703 "MachineIndependent/glslang_tab.cpp"
    break;

  case 96: /* declaration: spirv_instruction_qualifier function_prototype SEMICOLON  */
#line 898 "MachineIndependent/glslang.y"
                                                               {
        parseContext.requireExtensions((yyvsp[-1].interm).loc, 1, &E_GL_EXT_spirv_intrinsics, "SPIR-V instruction qualifier");
        (yyvsp[-1].interm).function->setSpirvInstruction(*(yyvsp[-2].interm.spirvInst)); // Attach SPIR-V intruction qualifier
        parseContext.handleFunctionDeclarator((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).function, true /* prototype */);
        (yyval.interm.intermNode) = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
#line 6715 "MachineIndependent/glslang_tab.cpp"
    break;

  case 97: /* declaration: spirv_instruction_qualifier function_prototype_with_spirv_variadic_tail SEMICOLON  */
#line 905 "MachineIndependent/glslang.y"
                                                                                        {
        parseContext.requireExtensions((yyvsp[-1].interm).loc, 1, &E_GL_EXT_spirv_intrinsics, "SPIR-V instruction qualifier");
        (yyvsp[-1].interm).function->setSpirvInstruction(*(yyvsp[-2].interm.spirvInst)); // Attach SPIR-V intruction qualifier
        parseContext.handleFunctionDeclarator((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).function, true /* prototype */);
        (yyval.interm.intermNode) = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
#line 6727 "MachineIndependent/glslang_tab.cpp"
    break;

  case 98: /* declaration: spirv_execution_mode_qualifier SEMICOLON  */
#line 912 "MachineIndependent/glslang.y"
                                               {
        parseContext.globalCheck((yyvsp[0].lex).loc, "SPIR-V execution mode qualifier");
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_EXT_spirv_intrinsics, "SPIR-V execution mode qualifier");
        (yyval.interm.intermNode) = 0;
    }
#line 6737 "MachineIndependent/glslang_tab.cpp"
    break;

  case 99: /* declaration: init_declarator_list SEMICOLON  */
#line 917 "MachineIndependent/glslang.y"
                                     {
        if ((yyvsp[-1].interm).intermNode && (yyvsp[-1].interm).intermNode->getAsAggregate())
            (yyvsp[-1].interm).intermNode->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-1].interm).intermNode;
    }
#line 6747 "MachineIndependent/glslang_tab.cpp"
    break;

  case 100: /* declaration: PRECISION precision_qualifier type_specifier SEMICOLON  */
#line 922 "MachineIndependent/glslang.y"
                                                             {
        parseContext.profileRequires((yyvsp[-3].lex).loc, ENoProfile, 130, 0, "precision statement");
        // lazy setting of the previous scope's defaults, has effect only the first time it is called in a particular scope
        parseContext.symbolTable.setPreviousDefaultPrecisions(&parseContext.defaultPrecision[0]);
        parseContext.setDefaultPrecision((yyvsp[-3].lex).loc, (yyvsp[-1].interm.type), (yyvsp[-2].interm.type).qualifier.precision);
        (yyval.interm.intermNode) = 0;
    }
#line 6759 "MachineIndependent/glslang_tab.cpp"
    break;

  case 101: /* declaration: block_structure SEMICOLON  */
#line 929 "MachineIndependent/glslang.y"
                                {
        (yyval.interm.intermNode) = parseContext.declareBlock((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).typeList);
    }
#line 6767 "MachineIndependent/glslang_tab.cpp"
    break;

  case 102: /* declaration: block_structure IDENTIFIER SEMICOLON  */
#line 932 "MachineIndependent/glslang.y"
                                           {
        (yyval.interm.intermNode) = parseContext.declareBlock((yyvsp[-2].interm).loc, *(yyvsp[-2].interm).typeList, (yyvsp[-1].lex).string);
    }
#line 6775 "MachineIndependent/glslang_tab.cpp"
    break;

  case 103: /* declaration: block_structure IDENTIFIER array_specifier SEMICOLON  */
#line 935 "MachineIndependent/glslang.y"
                                                           {
        (yyval.interm.intermNode) = parseContext.declareBlock((yyvsp[-3].interm).loc, *(yyvsp[-3].interm).typeList, (yyvsp[-2].lex).string, (yyvsp[-1].interm).arraySizes);
    }
#line 6783 "MachineIndependent/glslang_tab.cpp"
    break;

  case 104: /* declaration: type_qualifier SEMICOLON  */
#line 938 "MachineIndependent/glslang.y"
                               {
        parseContext.globalQualifierFixCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier);
        parseContext.updateStandaloneQualifierDefaults((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type));
        (yyval.interm.intermNode) = 0;
    }
#line 6793 "MachineIndependent/glslang_tab.cpp"
    break;

  case 105: /* declaration: type_qualifier identifier_list SEMICOLON  */
#line 943 "MachineIndependent/glslang.y"
                                               {
        parseContext.checkNoShaderLayouts((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).shaderQualifiers);
        parseContext.addQualifierToExisting((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).qualifier, *(yyvsp[-1].interm.identifierList));
        (yyval.interm.intermNode) = 0;
    }
#line 6803 "MachineIndependent/glslang_tab.cpp"
    break;

  case 106: /* $@2: %empty  */
#line 951 "MachineIndependent/glslang.y"
                                           { parseContext.nestedBlockCheck((yyvsp[-2].interm.type).loc); }
#line 6809 "MachineIndependent/glslang_tab.cpp"
    break;

  case 107: /* block_structure: type_qualifier IDENTIFIER LEFT_BRACE $@2 struct_declaration_without_heap RIGHT_BRACE  */
#line 951 "MachineIndependent/glslang.y"
                                                                                                                                  {
        --parseContext.blockNestingLevel;
        parseContext.blockName = (yyvsp[-4].lex).string;
        parseContext.globalQualifierFixCheck((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).qualifier);
        parseContext.checkNoShaderLayouts((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).shaderQualifiers);
        parseContext.currentBlockQualifier = (yyvsp[-5].interm.type).qualifier;
        (yyval.interm).loc = (yyvsp[-5].interm.type).loc;
        (yyval.interm).typeList = (yyvsp[-1].interm.typeList);
    }
#line 6823 "MachineIndependent/glslang_tab.cpp"
    break;

  case 108: /* identifier_list: IDENTIFIER  */
#line 963 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.identifierList) = new TIdentifierList;
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 6832 "MachineIndependent/glslang_tab.cpp"
    break;

  case 109: /* identifier_list: identifier_list COMMA IDENTIFIER  */
#line 967 "MachineIndependent/glslang.y"
                                       {
        (yyval.interm.identifierList) = (yyvsp[-2].interm.identifierList);
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 6841 "MachineIndependent/glslang_tab.cpp"
    break;

  case 110: /* function_prototype: function_declarator RIGHT_PAREN  */
#line 974 "MachineIndependent/glslang.y"
                                       {
        (yyval.interm).function = (yyvsp[-1].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6851 "MachineIndependent/glslang_tab.cpp"
    break;

  case 111: /* function_prototype: function_declarator RIGHT_PAREN attribute  */
#line 979 "MachineIndependent/glslang.y"
                                                {
        (yyval.interm).function = (yyvsp[-2].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        const char * extensions[2] = { E_GL_EXT_subgroup_uniform_control_flow, E_GL_EXT_maximal_reconvergence };
        parseContext.requireExtensions((yyvsp[-1].lex).loc, 2, extensions, "attribute");
        parseContext.handleFunctionAttributes((yyvsp[-1].lex).loc, *(yyvsp[0].interm.attributes));
    }
#line 6864 "MachineIndependent/glslang_tab.cpp"
    break;

  case 112: /* function_prototype: attribute function_declarator RIGHT_PAREN  */
#line 987 "MachineIndependent/glslang.y"
                                                {
        (yyval.interm).function = (yyvsp[-1].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        const char * extensions[2] = { E_GL_EXT_subgroup_uniform_control_flow, E_GL_EXT_maximal_reconvergence };
        parseContext.requireExtensions((yyvsp[0].lex).loc, 2, extensions, "attribute");
        parseContext.handleFunctionAttributes((yyvsp[0].lex).loc, *(yyvsp[-2].interm.attributes));
    }
#line 6877 "MachineIndependent/glslang_tab.cpp"
    break;

  case 113: /* function_prototype: attribute function_declarator RIGHT_PAREN attribute  */
#line 995 "MachineIndependent/glslang.y"
                                                          {
        (yyval.interm).function = (yyvsp[-2].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        const char * extensions[2] = { E_GL_EXT_subgroup_uniform_control_flow, E_GL_EXT_maximal_reconvergence };
        parseContext.requireExtensions((yyvsp[-1].lex).loc, 2, extensions, "attribute");
        parseContext.handleFunctionAttributes((yyvsp[-1].lex).loc, *(yyvsp[-3].interm.attributes));
        parseContext.handleFunctionAttributes((yyvsp[-1].lex).loc, *(yyvsp[0].interm.attributes));
    }
#line 6891 "MachineIndependent/glslang_tab.cpp"
    break;

  case 114: /* function_prototype: function_header ELLIPSIS RIGHT_PAREN  */
#line 1004 "MachineIndependent/glslang.y"
                                           {
        parseContext.makeVariadic((yyvsp[-2].interm.function), (yyvsp[-1].lex).loc);
        (yyval.interm).function = (yyvsp[-2].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6902 "MachineIndependent/glslang_tab.cpp"
    break;

  case 115: /* function_prototype: function_header_with_parameters COMMA ELLIPSIS RIGHT_PAREN  */
#line 1010 "MachineIndependent/glslang.y"
                                                                 {
        parseContext.makeVariadic((yyvsp[-3].interm.function), (yyvsp[-1].lex).loc);
        (yyval.interm).function = (yyvsp[-3].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6913 "MachineIndependent/glslang_tab.cpp"
    break;

  case 116: /* function_prototype_with_spirv_variadic_tail: function_header SPIRV_LITERAL ELLIPSIS RIGHT_PAREN  */
#line 1019 "MachineIndependent/glslang.y"
                                                         {
        parseContext.makeVariadic((yyvsp[-3].interm.function), (yyvsp[-2].lex).loc, true /* spirvLiteral */, false /* spirvByReference */);
        (yyval.interm).function = (yyvsp[-3].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6924 "MachineIndependent/glslang_tab.cpp"
    break;

  case 117: /* function_prototype_with_spirv_variadic_tail: function_header SPIRV_BY_REFERENCE ELLIPSIS RIGHT_PAREN  */
#line 1025 "MachineIndependent/glslang.y"
                                                              {
        parseContext.makeVariadic((yyvsp[-3].interm.function), (yyvsp[-2].lex).loc, false /* spirvLiteral */, true /* spirvByReference */);
        (yyval.interm).function = (yyvsp[-3].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6935 "MachineIndependent/glslang_tab.cpp"
    break;

  case 118: /* function_prototype_with_spirv_variadic_tail: function_header_with_parameters COMMA SPIRV_LITERAL ELLIPSIS RIGHT_PAREN  */
#line 1031 "MachineIndependent/glslang.y"
                                                                               {
        parseContext.makeVariadic((yyvsp[-4].interm.function), (yyvsp[-2].lex).loc, true /* spirvLiteral */, false /* spirvByReference */);
        (yyval.interm).function = (yyvsp[-4].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6946 "MachineIndependent/glslang_tab.cpp"
    break;

  case 119: /* function_prototype_with_spirv_variadic_tail: function_header_with_parameters COMMA SPIRV_BY_REFERENCE ELLIPSIS RIGHT_PAREN  */
#line 1037 "MachineIndependent/glslang.y"
                                                                                    {
        parseContext.makeVariadic((yyvsp[-4].interm.function), (yyvsp[-2].lex).loc, false /* spirvLiteral */, true /* spirvByReference */);
        (yyval.interm).function = (yyvsp[-4].interm.function);
        if (parseContext.compileOnly) (yyval.interm).function->setExport();
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 6957 "MachineIndependent/glslang_tab.cpp"
    break;

  case 120: /* function_declarator: function_header  */
#line 1046 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 6965 "MachineIndependent/glslang_tab.cpp"
    break;

  case 121: /* function_declarator: function_header_with_parameters  */
#line 1049 "MachineIndependent/glslang.y"
                                      {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 6973 "MachineIndependent/glslang_tab.cpp"
    break;

  case 122: /* function_header_with_parameters: function_header parameter_declaration  */
#line 1056 "MachineIndependent/glslang.y"
                                            {
        // Add the parameter
        (yyval.interm.function) = (yyvsp[-1].interm.function);
        if ((yyvsp[0].interm).param.type->getBasicType() != EbtVoid)
        {
            if (!(parseContext.spvVersion.vulkan > 0 && parseContext.spvVersion.vulkanRelaxed))
                (yyvsp[-1].interm.function)->addParameter((yyvsp[0].interm).param);
            else
                parseContext.vkRelaxedRemapFunctionParameter((yyvsp[-1].interm.function), (yyvsp[0].interm).param);
        }
        else
            delete (yyvsp[0].interm).param.type;
    }
#line 6991 "MachineIndependent/glslang_tab.cpp"
    break;

  case 123: /* function_header_with_parameters: function_header_with_parameters COMMA parameter_declaration  */
#line 1069 "MachineIndependent/glslang.y"
                                                                  {
        //
        // Only first parameter of one-parameter functions can be void
        // The check for named parameters not being void is done in parameter_declarator
        //
        if ((yyvsp[0].interm).param.type->getBasicType() == EbtVoid) {
            //
            // This parameter > first is void
            //
            parseContext.error((yyvsp[-1].lex).loc, "cannot be an argument type except for '(void)'", "void", "");
            delete (yyvsp[0].interm).param.type;
        } else {
            // Add the parameter
            (yyval.interm.function) = (yyvsp[-2].interm.function);
            if (!(parseContext.spvVersion.vulkan > 0 && parseContext.spvVersion.vulkanRelaxed))
                (yyvsp[-2].interm.function)->addParameter((yyvsp[0].interm).param);
            else
                parseContext.vkRelaxedRemapFunctionParameter((yyvsp[-2].interm.function), (yyvsp[0].interm).param);
        }
    }
#line 7016 "MachineIndependent/glslang_tab.cpp"
    break;

  case 124: /* function_header: fully_specified_type IDENTIFIER LEFT_PAREN  */
#line 1092 "MachineIndependent/glslang.y"
                                                 {
        if ((yyvsp[-2].interm.type).qualifier.storage != EvqGlobal && (yyvsp[-2].interm.type).qualifier.storage != EvqTemporary) {
            parseContext.error((yyvsp[-1].lex).loc, "no qualifiers allowed for function return",
                               GetStorageQualifierString((yyvsp[-2].interm.type).qualifier.storage), "");
        }
        if ((yyvsp[-2].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);

        // Add the function as a prototype after parsing it (we do not support recursion)
        TFunction *function;
        TType type((yyvsp[-2].interm.type));

        // Potentially rename shader entry point function.  No-op most of the time.
        parseContext.renameShaderFunction((yyvsp[-1].lex).string);

        // Make the function
        function = new TFunction((yyvsp[-1].lex).string, type);
        (yyval.interm.function) = function;
    }
#line 7040 "MachineIndependent/glslang_tab.cpp"
    break;

  case 125: /* parameter_declarator: type_specifier IDENTIFIER  */
#line 1115 "MachineIndependent/glslang.y"
                                {
        if ((yyvsp[-1].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-1].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-1].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck((yyvsp[-1].interm.type).loc, *(yyvsp[-1].interm.type).arraySizes);
        }
        if ((yyvsp[-1].interm.type).basicType == EbtVoid) {
            parseContext.error((yyvsp[0].lex).loc, "illegal use of type 'void'", (yyvsp[0].lex).string->c_str(), "");
        }
        parseContext.reservedErrorCheck((yyvsp[0].lex).loc, *(yyvsp[0].lex).string);

        TParameter param = {(yyvsp[0].lex).string, new TType((yyvsp[-1].interm.type)), {}};
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).param = param;
    }
#line 7060 "MachineIndependent/glslang_tab.cpp"
    break;

  case 126: /* parameter_declarator: type_specifier IDENTIFIER array_specifier  */
#line 1130 "MachineIndependent/glslang.y"
                                                {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }
        TType* type = new TType((yyvsp[-2].interm.type));
        type->transferArraySizes((yyvsp[0].interm).arraySizes);
        type->copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);

        parseContext.arrayOfArrayVersionCheck((yyvsp[-1].lex).loc, type->getArraySizes());
        parseContext.arraySizeRequiredCheck((yyvsp[0].interm).loc, *(yyvsp[0].interm).arraySizes);
        parseContext.reservedErrorCheck((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string);

        TParameter param = { (yyvsp[-1].lex).string, type, {} };

        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        (yyval.interm).param = param;
    }
#line 7084 "MachineIndependent/glslang_tab.cpp"
    break;

  case 127: /* parameter_declarator: type_specifier IDENTIFIER EQUAL initializer  */
#line 1149 "MachineIndependent/glslang.y"
                                                  {
        TParameter param = parseContext.getParamWithDefault((yyvsp[-3].interm.type), (yyvsp[-2].lex).string, (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
        (yyval.interm).loc = (yyvsp[-2].lex).loc;
        (yyval.interm).param = param;
    }
#line 7094 "MachineIndependent/glslang_tab.cpp"
    break;

  case 128: /* parameter_declaration: type_qualifier parameter_declarator  */
#line 1160 "MachineIndependent/glslang.y"
                                          {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier(), (yyval.interm).param.type->hasTypeParameter());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);

    }
#line 7110 "MachineIndependent/glslang_tab.cpp"
    break;

  case 129: /* parameter_declaration: parameter_declarator  */
#line 1171 "MachineIndependent/glslang.y"
                           {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFixStorage((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier(), (yyval.interm).param.type->hasTypeParameter());
    }
#line 7122 "MachineIndependent/glslang_tab.cpp"
    break;

  case 130: /* parameter_declaration: type_qualifier parameter_type_specifier  */
#line 1181 "MachineIndependent/glslang.y"
                                              {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyvsp[-1].interm.type).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier(), (yyval.interm).param.type->hasTypeParameter());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);
    }
#line 7137 "MachineIndependent/glslang_tab.cpp"
    break;

  case 131: /* parameter_declaration: parameter_type_specifier  */
#line 1191 "MachineIndependent/glslang.y"
                               {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFixStorage((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier(), (yyval.interm).param.type->hasTypeParameter());
    }
#line 7149 "MachineIndependent/glslang_tab.cpp"
    break;

  case 132: /* parameter_type_specifier: type_specifier  */
#line 1201 "MachineIndependent/glslang.y"
                     {
        TParameter param = { 0, new TType((yyvsp[0].interm.type)), {} };
        (yyval.interm).param = param;
        if ((yyvsp[0].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[0].interm.type).loc, *(yyvsp[0].interm.type).arraySizes);
    }
#line 7160 "MachineIndependent/glslang_tab.cpp"
    break;

  case 133: /* init_declarator_list: single_declaration  */
#line 1210 "MachineIndependent/glslang.y"
                         {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 7168 "MachineIndependent/glslang_tab.cpp"
    break;

  case 134: /* init_declarator_list: init_declarator_list COMMA IDENTIFIER  */
#line 1213 "MachineIndependent/glslang.y"
                                            {
        (yyval.interm) = (yyvsp[-2].interm);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-2].interm).type);
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, declNode, (yyvsp[0].lex).loc);
    }
#line 7178 "MachineIndependent/glslang_tab.cpp"
    break;

  case 135: /* init_declarator_list: init_declarator_list COMMA IDENTIFIER array_specifier  */
#line 1218 "MachineIndependent/glslang.y"
                                                            {
        (yyval.interm) = (yyvsp[-3].interm);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-3].interm).type, (yyvsp[0].interm).arraySizes);
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-3].interm).intermNode, declNode, (yyvsp[-1].lex).loc);
    }
#line 7188 "MachineIndependent/glslang_tab.cpp"
    break;

  case 136: /* init_declarator_list: init_declarator_list COMMA IDENTIFIER array_specifier EQUAL initializer  */
#line 1223 "MachineIndependent/glslang.y"
                                                                              {
        (yyval.interm).type = (yyvsp[-5].interm).type;
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-5].interm).type, (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-5].interm).intermNode, declNode, (yyvsp[-1].lex).loc);
    }
#line 7198 "MachineIndependent/glslang_tab.cpp"
    break;

  case 137: /* init_declarator_list: init_declarator_list COMMA IDENTIFIER EQUAL initializer  */
#line 1228 "MachineIndependent/glslang.y"
                                                              {
        (yyval.interm).type = (yyvsp[-4].interm).type;
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-4].interm).type, 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-4].interm).intermNode, declNode, (yyvsp[-1].lex).loc);
    }
#line 7208 "MachineIndependent/glslang_tab.cpp"
    break;

  case 138: /* single_declaration: fully_specified_type  */
#line 1236 "MachineIndependent/glslang.y"
                           {
        (yyval.interm).type = (yyvsp[0].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareTypeDefaults((yyval.interm).loc, (yyval.interm).type);
    }
#line 7218 "MachineIndependent/glslang_tab.cpp"
    break;

  case 139: /* single_declaration: fully_specified_type IDENTIFIER  */
#line 1241 "MachineIndependent/glslang.y"
                                      {
        (yyval.interm).type = (yyvsp[-1].interm.type);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-1].interm.type));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(nullptr, declNode, (yyvsp[0].lex).loc);

    }
#line 7229 "MachineIndependent/glslang_tab.cpp"
    break;

  case 140: /* single_declaration: fully_specified_type IDENTIFIER array_specifier  */
#line 1247 "MachineIndependent/glslang.y"
                                                      {
        (yyval.interm).type = (yyvsp[-2].interm.type);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-2].interm.type), (yyvsp[0].interm).arraySizes);
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(nullptr, declNode, (yyvsp[-1].lex).loc);
    }
#line 7239 "MachineIndependent/glslang_tab.cpp"
    break;

  case 141: /* single_declaration: fully_specified_type IDENTIFIER array_specifier EQUAL initializer  */
#line 1252 "MachineIndependent/glslang.y"
                                                                        {
        (yyval.interm).type = (yyvsp[-4].interm.type);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-4].interm.type), (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(nullptr, declNode, (yyvsp[-3].lex).loc);
    }
#line 7249 "MachineIndependent/glslang_tab.cpp"
    break;

  case 142: /* single_declaration: fully_specified_type IDENTIFIER EQUAL initializer  */
#line 1257 "MachineIndependent/glslang.y"
                                                        {
        (yyval.interm).type = (yyvsp[-3].interm.type);
        TIntermNode* declNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(nullptr, declNode, (yyvsp[-2].lex).loc);
    }
#line 7259 "MachineIndependent/glslang_tab.cpp"
    break;

  case 143: /* fully_specified_type: type_specifier  */
#line 1266 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type) = (yyvsp[0].interm.type);

        parseContext.globalQualifierTypeCheck((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier, (yyval.interm.type));
        if ((yyvsp[0].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[0].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[0].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }
        parseContext.precisionQualifierCheck((yyval.interm.type).loc, (yyval.interm.type).basicType, (yyval.interm.type).qualifier, (yyval.interm.type).hasTypeParameter());
    }
#line 7274 "MachineIndependent/glslang_tab.cpp"
    break;

  case 144: /* fully_specified_type: type_qualifier type_specifier  */
#line 1276 "MachineIndependent/glslang.y"
                                     {
        parseContext.globalQualifierFixCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, false, &(yyvsp[0].interm.type));
        parseContext.globalQualifierTypeCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, (yyvsp[0].interm.type));

        if ((yyvsp[0].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[0].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[0].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        if ((yyvsp[0].interm.type).arraySizes && parseContext.arrayQualifierError((yyvsp[0].interm.type).loc, (yyvsp[-1].interm.type).qualifier))
            (yyvsp[0].interm.type).arraySizes = nullptr;

        parseContext.checkNoShaderLayouts((yyvsp[0].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        (yyvsp[0].interm.type).shaderQualifiers.merge((yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier, (yyvsp[-1].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).basicType, (yyvsp[0].interm.type).qualifier, (yyvsp[0].interm.type).hasTypeParameter());

        (yyval.interm.type) = (yyvsp[0].interm.type);

        if (! (yyval.interm.type).qualifier.isInterpolation() &&
            ((parseContext.language == EShLangVertex   && (yyval.interm.type).qualifier.storage == EvqVaryingOut) ||
             (parseContext.language == EShLangFragment && (yyval.interm.type).qualifier.storage == EvqVaryingIn)))
            (yyval.interm.type).qualifier.smooth = true;
    }
#line 7303 "MachineIndependent/glslang_tab.cpp"
    break;

  case 145: /* invariant_qualifier: INVARIANT  */
#line 1303 "MachineIndependent/glslang.y"
                {
        parseContext.globalCheck((yyvsp[0].lex).loc, "invariant");
        parseContext.profileRequires((yyval.interm.type).loc, ENoProfile, 120, 0, "invariant");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.invariant = true;
    }
#line 7314 "MachineIndependent/glslang_tab.cpp"
    break;

  case 146: /* interpolation_qualifier: SMOOTH  */
#line 1312 "MachineIndependent/glslang.y"
             {
        parseContext.globalCheck((yyvsp[0].lex).loc, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "smooth");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.smooth = true;
    }
#line 7326 "MachineIndependent/glslang_tab.cpp"
    break;

  case 147: /* interpolation_qualifier: FLAT  */
#line 1319 "MachineIndependent/glslang.y"
           {
        parseContext.globalCheck((yyvsp[0].lex).loc, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "flat");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.flat = true;
    }
#line 7338 "MachineIndependent/glslang_tab.cpp"
    break;

  case 148: /* interpolation_qualifier: NOPERSPECTIVE  */
#line 1326 "MachineIndependent/glslang.y"
                    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "noperspective");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 0, E_GL_NV_shader_noperspective_interpolation, "noperspective");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "noperspective");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.nopersp = true;
    }
#line 7350 "MachineIndependent/glslang_tab.cpp"
    break;

  case 149: /* interpolation_qualifier: EXPLICITINTERPAMD  */
#line 1333 "MachineIndependent/glslang.y"
                        {
        parseContext.globalCheck((yyvsp[0].lex).loc, "__explicitInterpAMD");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.explicitInterp = true;
    }
#line 7362 "MachineIndependent/glslang_tab.cpp"
    break;

  case 150: /* interpolation_qualifier: PERVERTEXNV  */
#line 1340 "MachineIndependent/glslang.y"
                  {
        parseContext.globalCheck((yyvsp[0].lex).loc, "pervertexNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.pervertexNV = true;
    }
#line 7375 "MachineIndependent/glslang_tab.cpp"
    break;

  case 151: /* interpolation_qualifier: PERVERTEXEXT  */
#line 1348 "MachineIndependent/glslang.y"
                   {
        parseContext.globalCheck((yyvsp[0].lex).loc, "pervertexEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 0, E_GL_EXT_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 0, E_GL_EXT_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 0, E_GL_EXT_fragment_shader_barycentric, "fragment shader barycentric");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.pervertexEXT = true;
    }
#line 7388 "MachineIndependent/glslang_tab.cpp"
    break;

  case 152: /* interpolation_qualifier: PERPRIMITIVENV  */
#line 1356 "MachineIndependent/glslang.y"
                     {
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "perprimitiveNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangFragmentMask | EShLangMeshMask), "perprimitiveNV");
        // Fragment shader stage doesn't check for extension. So we explicitly add below extension check.
        if (parseContext.language == EShLangFragment)
            parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_NV_mesh_shader, "perprimitiveNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perPrimitiveNV = true;
    }
#line 7403 "MachineIndependent/glslang_tab.cpp"
    break;

  case 153: /* interpolation_qualifier: PERPRIMITIVEEXT  */
#line 1366 "MachineIndependent/glslang.y"
                      {
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "perprimitiveEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangFragmentMask | EShLangMeshMask), "perprimitiveEXT");
        // Fragment shader stage doesn't check for extension. So we explicitly add below extension check.
        if (parseContext.language == EShLangFragment)
            parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_EXT_mesh_shader, "perprimitiveEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perPrimitiveNV = true;
    }
#line 7418 "MachineIndependent/glslang_tab.cpp"
    break;

  case 154: /* interpolation_qualifier: PERVIEWNV  */
#line 1376 "MachineIndependent/glslang.y"
                {
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "perviewNV");
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangMesh, "perviewNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perViewNV = true;
    }
#line 7430 "MachineIndependent/glslang_tab.cpp"
    break;

  case 155: /* interpolation_qualifier: PERTASKNV  */
#line 1383 "MachineIndependent/glslang.y"
                {
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "taskNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTaskMask | EShLangMeshMask), "taskNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perTaskNV = true;
    }
#line 7442 "MachineIndependent/glslang_tab.cpp"
    break;

  case 156: /* layout_qualifier: LAYOUT LEFT_PAREN layout_qualifier_id_list RIGHT_PAREN  */
#line 1393 "MachineIndependent/glslang.y"
                                                             {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
    }
#line 7450 "MachineIndependent/glslang_tab.cpp"
    break;

  case 157: /* layout_qualifier_id_list: layout_qualifier_id  */
#line 1399 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7458 "MachineIndependent/glslang_tab.cpp"
    break;

  case 158: /* layout_qualifier_id_list: layout_qualifier_id_list COMMA layout_qualifier_id  */
#line 1402 "MachineIndependent/glslang.y"
                                                         {
        (yyval.interm.type) = (yyvsp[-2].interm.type);
        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeObjectLayoutQualifiers((yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 7468 "MachineIndependent/glslang_tab.cpp"
    break;

  case 159: /* layout_qualifier_id: IDENTIFIER  */
#line 1409 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), *(yyvsp[0].lex).string);
    }
#line 7477 "MachineIndependent/glslang_tab.cpp"
    break;

  case 160: /* layout_qualifier_id: IDENTIFIER EQUAL constant_expression  */
#line 1413 "MachineIndependent/glslang.y"
                                           {
        (yyval.interm.type).init((yyvsp[-2].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[-2].lex).loc, (yyval.interm.type), *(yyvsp[-2].lex).string, (yyvsp[0].interm.intermTypedNode));
    }
#line 7486 "MachineIndependent/glslang_tab.cpp"
    break;

  case 161: /* layout_qualifier_id: SHARED  */
#line 1417 "MachineIndependent/glslang.y"
             { // because "shared" is both an identifier and a keyword
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        TString strShared("shared");
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), strShared);
    }
#line 7496 "MachineIndependent/glslang_tab.cpp"
    break;

  case 162: /* precise_qualifier: PRECISE  */
#line 1425 "MachineIndependent/glslang.y"
              {
        parseContext.profileRequires((yyval.interm.type).loc, ECoreProfile | ECompatibilityProfile, 400, E_GL_ARB_gpu_shader5, "precise");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 320, Num_AEP_gpu_shader5, AEP_gpu_shader5, "precise");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.noContraction = true;
    }
#line 7507 "MachineIndependent/glslang_tab.cpp"
    break;

  case 163: /* type_qualifier: single_type_qualifier  */
#line 1434 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7515 "MachineIndependent/glslang_tab.cpp"
    break;

  case 164: /* type_qualifier: type_qualifier single_type_qualifier  */
#line 1437 "MachineIndependent/glslang.y"
                                           {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        if ((yyval.interm.type).basicType == EbtVoid)
            (yyval.interm.type).basicType = (yyvsp[0].interm.type).basicType;

        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyval.interm.type).loc, (yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 7528 "MachineIndependent/glslang_tab.cpp"
    break;

  case 165: /* single_type_qualifier: storage_qualifier  */
#line 1448 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7536 "MachineIndependent/glslang_tab.cpp"
    break;

  case 166: /* single_type_qualifier: layout_qualifier  */
#line 1451 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7544 "MachineIndependent/glslang_tab.cpp"
    break;

  case 167: /* single_type_qualifier: precision_qualifier  */
#line 1454 "MachineIndependent/glslang.y"
                          {
        parseContext.checkPrecisionQualifier((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier.precision);
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7553 "MachineIndependent/glslang_tab.cpp"
    break;

  case 168: /* single_type_qualifier: interpolation_qualifier  */
#line 1458 "MachineIndependent/glslang.y"
                              {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7562 "MachineIndependent/glslang_tab.cpp"
    break;

  case 169: /* single_type_qualifier: invariant_qualifier  */
#line 1462 "MachineIndependent/glslang.y"
                          {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7571 "MachineIndependent/glslang_tab.cpp"
    break;

  case 170: /* single_type_qualifier: precise_qualifier  */
#line 1466 "MachineIndependent/glslang.y"
                        {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7580 "MachineIndependent/glslang_tab.cpp"
    break;

  case 171: /* single_type_qualifier: non_uniform_qualifier  */
#line 1470 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7588 "MachineIndependent/glslang_tab.cpp"
    break;

  case 172: /* single_type_qualifier: spirv_storage_class_qualifier  */
#line 1473 "MachineIndependent/glslang.y"
                                    {
        parseContext.globalCheck((yyvsp[0].interm.type).loc, "spirv_storage_class");
        parseContext.requireExtensions((yyvsp[0].interm.type).loc, 1, &E_GL_EXT_spirv_intrinsics, "SPIR-V storage class qualifier");
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7598 "MachineIndependent/glslang_tab.cpp"
    break;

  case 173: /* single_type_qualifier: spirv_decorate_qualifier  */
#line 1478 "MachineIndependent/glslang.y"
                               {
        parseContext.requireExtensions((yyvsp[0].interm.type).loc, 1, &E_GL_EXT_spirv_intrinsics, "SPIR-V decorate qualifier");
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 7607 "MachineIndependent/glslang_tab.cpp"
    break;

  case 174: /* single_type_qualifier: SPIRV_BY_REFERENCE  */
#line 1482 "MachineIndependent/glslang.y"
                         {
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_EXT_spirv_intrinsics, "spirv_by_reference");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.setSpirvByReference();
    }
#line 7617 "MachineIndependent/glslang_tab.cpp"
    break;

  case 175: /* single_type_qualifier: SPIRV_LITERAL  */
#line 1487 "MachineIndependent/glslang.y"
                    {
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_EXT_spirv_intrinsics, "spirv_by_literal");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.setSpirvLiteral();
    }
#line 7627 "MachineIndependent/glslang_tab.cpp"
    break;

  case 176: /* storage_qualifier: CONST  */
#line 1495 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqConst;  // will later turn into EvqConstReadOnly, if the initializer is not constant
    }
#line 7636 "MachineIndependent/glslang_tab.cpp"
    break;

  case 177: /* storage_qualifier: INOUT  */
#line 1499 "MachineIndependent/glslang.y"
            {
        parseContext.globalCheck((yyvsp[0].lex).loc, "inout");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqInOut;
    }
#line 7646 "MachineIndependent/glslang_tab.cpp"
    break;

  case 178: /* storage_qualifier: IN  */
#line 1504 "MachineIndependent/glslang.y"
         {
        parseContext.globalCheck((yyvsp[0].lex).loc, "in");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "in" or a pipeline "in" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqIn;
    }
#line 7657 "MachineIndependent/glslang_tab.cpp"
    break;

  case 179: /* storage_qualifier: OUT  */
#line 1510 "MachineIndependent/glslang.y"
          {
        parseContext.globalCheck((yyvsp[0].lex).loc, "out");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "out" or a pipeline "out" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqOut;
    }
#line 7668 "MachineIndependent/glslang_tab.cpp"
    break;

  case 180: /* storage_qualifier: CENTROID  */
#line 1516 "MachineIndependent/glslang.y"
               {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 120, 0, "centroid");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "centroid");
        parseContext.globalCheck((yyvsp[0].lex).loc, "centroid");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.centroid = true;
    }
#line 7680 "MachineIndependent/glslang_tab.cpp"
    break;

  case 181: /* storage_qualifier: UNIFORM  */
#line 1523 "MachineIndependent/glslang.y"
              {
        parseContext.globalCheck((yyvsp[0].lex).loc, "uniform");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqUniform;
    }
#line 7690 "MachineIndependent/glslang_tab.cpp"
    break;

  case 182: /* storage_qualifier: TILEIMAGEEXT  */
#line 1528 "MachineIndependent/glslang.y"
                   {
        parseContext.globalCheck((yyvsp[0].lex).loc, "tileImageEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqTileImageEXT;
    }
#line 7700 "MachineIndependent/glslang_tab.cpp"
    break;

  case 183: /* storage_qualifier: SHARED  */
#line 1533 "MachineIndependent/glslang.y"
             {
        parseContext.globalCheck((yyvsp[0].lex).loc, "shared");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, 430, E_GL_ARB_compute_shader, "shared");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 310, 0, "shared");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangComputeMask | EShLangMeshMask | EShLangTaskMask), "shared");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqShared;
    }
#line 7713 "MachineIndependent/glslang_tab.cpp"
    break;

  case 184: /* storage_qualifier: BUFFER  */
#line 1541 "MachineIndependent/glslang.y"
             {
        parseContext.globalCheck((yyvsp[0].lex).loc, "buffer");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqBuffer;
    }
#line 7723 "MachineIndependent/glslang_tab.cpp"
    break;

  case 185: /* storage_qualifier: ATTRIBUTE  */
#line 1546 "MachineIndependent/glslang.y"
                {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangVertex, "attribute");
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ECoreProfile, 130, "attribute");
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ENoProfile, 130, "attribute");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, ECoreProfile, 420, "attribute");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, EEsProfile, 300, "attribute");

        parseContext.globalCheck((yyvsp[0].lex).loc, "attribute");

        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqVaryingIn;
    }
#line 7740 "MachineIndependent/glslang_tab.cpp"
    break;

  case 186: /* storage_qualifier: VARYING  */
#line 1558 "MachineIndependent/glslang.y"
              {
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ENoProfile, 130, "varying");
        parseContext.checkDeprecated((yyvsp[0].lex).loc, ECoreProfile, 130, "varying");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, ECoreProfile, 420, "varying");
        parseContext.requireNotRemoved((yyvsp[0].lex).loc, EEsProfile, 300, "varying");

        parseContext.globalCheck((yyvsp[0].lex).loc, "varying");

        (yyval.interm.type).init((yyvsp[0].lex).loc);
        if (parseContext.language == EShLangVertex)
            (yyval.interm.type).qualifier.storage = EvqVaryingOut;
        else
            (yyval.interm.type).qualifier.storage = EvqVaryingIn;
    }
#line 7759 "MachineIndependent/glslang_tab.cpp"
    break;

  case 187: /* storage_qualifier: PATCH  */
#line 1572 "MachineIndependent/glslang.y"
            {
        parseContext.globalCheck((yyvsp[0].lex).loc, "patch");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTessControlMask | EShLangTessEvaluationMask), "patch");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.patch = true;
    }
#line 7770 "MachineIndependent/glslang_tab.cpp"
    break;

  case 188: /* storage_qualifier: SAMPLE  */
#line 1578 "MachineIndependent/glslang.y"
             {
        parseContext.globalCheck((yyvsp[0].lex).loc, "sample");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.sample = true;
    }
#line 7780 "MachineIndependent/glslang_tab.cpp"
    break;

  case 189: /* storage_qualifier: RESOURCEHEAP  */
#line 1583 "MachineIndependent/glslang.y"
                   {
        parseContext.globalCheck((yyvsp[0].lex).loc, "resourceHeap");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqResourceHeap;
    }
#line 7790 "MachineIndependent/glslang_tab.cpp"
    break;

  case 190: /* storage_qualifier: SAMPLERHEAP  */
#line 1588 "MachineIndependent/glslang.y"
                  {
        parseContext.globalCheck((yyvsp[0].lex).loc, "samplerHeap");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqSamplerHeap;
    }
#line 7800 "MachineIndependent/glslang_tab.cpp"
    break;

  case 191: /* storage_qualifier: HITATTRNV  */
#line 1593 "MachineIndependent/glslang.y"
                {
        parseContext.globalCheck((yyvsp[0].lex).loc, "hitAttributeNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangIntersectMask | EShLangClosestHitMask
            | EShLangAnyHitMask), "hitAttributeNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "hitAttributeNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqHitAttr;
    }
#line 7813 "MachineIndependent/glslang_tab.cpp"
    break;

  case 192: /* storage_qualifier: HITOBJECTATTRNV  */
#line 1601 "MachineIndependent/glslang.y"
                      {
        parseContext.globalCheck((yyvsp[0].lex).loc, "hitAttributeNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask | EShLangClosestHitMask
            | EShLangMissMask), "hitObjectAttributeNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_shader_invocation_reorder, "hitObjectAttributeNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqHitObjectAttrNV;
    }
#line 7826 "MachineIndependent/glslang_tab.cpp"
    break;

  case 193: /* storage_qualifier: HITOBJECTATTREXT  */
#line 1609 "MachineIndependent/glslang.y"
                       {
        parseContext.globalCheck((yyvsp[0].lex).loc, "hitAttributeEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask | EShLangClosestHitMask
            | EShLangMissMask), "hitObjectAttributeEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_shader_invocation_reorder, "hitObjectAttributeEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqHitObjectAttrEXT;
    }
#line 7839 "MachineIndependent/glslang_tab.cpp"
    break;

  case 194: /* storage_qualifier: HITATTREXT  */
#line 1617 "MachineIndependent/glslang.y"
                 {
        parseContext.globalCheck((yyvsp[0].lex).loc, "hitAttributeEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangIntersectMask | EShLangClosestHitMask
            | EShLangAnyHitMask), "hitAttributeEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_ray_tracing, "hitAttributeNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqHitAttr;
    }
#line 7852 "MachineIndependent/glslang_tab.cpp"
    break;

  case 195: /* storage_qualifier: PAYLOADNV  */
#line 1625 "MachineIndependent/glslang.y"
                {
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask | EShLangClosestHitMask |
            EShLangAnyHitMask | EShLangMissMask), "rayPayloadNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "rayPayloadNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayload;
    }
#line 7865 "MachineIndependent/glslang_tab.cpp"
    break;

  case 196: /* storage_qualifier: PAYLOADEXT  */
#line 1633 "MachineIndependent/glslang.y"
                 {
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask | EShLangClosestHitMask |
            EShLangAnyHitMask | EShLangMissMask), "rayPayloadEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_ray_tracing, "rayPayloadEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayload;
    }
#line 7878 "MachineIndependent/glslang_tab.cpp"
    break;

  case 197: /* storage_qualifier: PAYLOADINNV  */
#line 1641 "MachineIndependent/glslang.y"
                  {
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadInNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangClosestHitMask |
            EShLangAnyHitMask | EShLangMissMask), "rayPayloadInNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "rayPayloadInNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayloadIn;
    }
#line 7891 "MachineIndependent/glslang_tab.cpp"
    break;

  case 198: /* storage_qualifier: PAYLOADINEXT  */
#line 1649 "MachineIndependent/glslang.y"
                   {
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadInEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangClosestHitMask |
            EShLangAnyHitMask | EShLangMissMask), "rayPayloadInEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_ray_tracing, "rayPayloadInEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayloadIn;
    }
#line 7904 "MachineIndependent/glslang_tab.cpp"
    break;

  case 199: /* storage_qualifier: CALLDATANV  */
#line 1657 "MachineIndependent/glslang.y"
                 {
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask |
            EShLangClosestHitMask | EShLangMissMask | EShLangCallableMask), "callableDataNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "callableDataNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableData;
    }
#line 7917 "MachineIndependent/glslang_tab.cpp"
    break;

  case 200: /* storage_qualifier: CALLDATAEXT  */
#line 1665 "MachineIndependent/glslang.y"
                  {
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenMask |
            EShLangClosestHitMask | EShLangMissMask | EShLangCallableMask), "callableDataEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_ray_tracing, "callableDataEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableData;
    }
#line 7930 "MachineIndependent/glslang_tab.cpp"
    break;

  case 201: /* storage_qualifier: CALLDATAINNV  */
#line 1673 "MachineIndependent/glslang.y"
                   {
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataInNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangCallableMask), "callableDataInNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "callableDataInNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableDataIn;
    }
#line 7942 "MachineIndependent/glslang_tab.cpp"
    break;

  case 202: /* storage_qualifier: CALLDATAINEXT  */
#line 1680 "MachineIndependent/glslang.y"
                    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataInEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangCallableMask), "callableDataInEXT");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_EXT_ray_tracing, "callableDataInEXT");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableDataIn;
    }
#line 7954 "MachineIndependent/glslang_tab.cpp"
    break;

  case 203: /* storage_qualifier: COHERENT  */
#line 1687 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.coherent = true;
    }
#line 7963 "MachineIndependent/glslang_tab.cpp"
    break;

  case 204: /* storage_qualifier: DEVICECOHERENT  */
#line 1691 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "devicecoherent");
        (yyval.interm.type).qualifier.devicecoherent = true;
    }
#line 7973 "MachineIndependent/glslang_tab.cpp"
    break;

  case 205: /* storage_qualifier: QUEUEFAMILYCOHERENT  */
#line 1696 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "queuefamilycoherent");
        (yyval.interm.type).qualifier.queuefamilycoherent = true;
    }
#line 7983 "MachineIndependent/glslang_tab.cpp"
    break;

  case 206: /* storage_qualifier: WORKGROUPCOHERENT  */
#line 1701 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "workgroupcoherent");
        (yyval.interm.type).qualifier.workgroupcoherent = true;
    }
#line 7993 "MachineIndependent/glslang_tab.cpp"
    break;

  case 207: /* storage_qualifier: SUBGROUPCOHERENT  */
#line 1706 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "subgroupcoherent");
        (yyval.interm.type).qualifier.subgroupcoherent = true;
    }
#line 8003 "MachineIndependent/glslang_tab.cpp"
    break;

  case 208: /* storage_qualifier: NONPRIVATE  */
#line 1711 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "nonprivate");
        (yyval.interm.type).qualifier.nonprivate = true;
    }
#line 8013 "MachineIndependent/glslang_tab.cpp"
    break;

  case 209: /* storage_qualifier: SHADERCALLCOHERENT  */
#line 1716 "MachineIndependent/glslang.y"
                         {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_EXT_ray_tracing, "shadercallcoherent");
        (yyval.interm.type).qualifier.shadercallcoherent = true;
    }
#line 8023 "MachineIndependent/glslang_tab.cpp"
    break;

  case 210: /* storage_qualifier: VOLATILE  */
#line 1721 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.volatil = true;
    }
#line 8032 "MachineIndependent/glslang_tab.cpp"
    break;

  case 211: /* storage_qualifier: RESTRICT  */
#line 1725 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.restrict = true;
    }
#line 8041 "MachineIndependent/glslang_tab.cpp"
    break;

  case 212: /* storage_qualifier: READONLY  */
#line 1729 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.readonly = true;
    }
#line 8050 "MachineIndependent/glslang_tab.cpp"
    break;

  case 213: /* storage_qualifier: WRITEONLY  */
#line 1733 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.writeonly = true;
    }
#line 8059 "MachineIndependent/glslang_tab.cpp"
    break;

  case 214: /* storage_qualifier: NONTEMPORAL  */
#line 1737 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.nontemporal  = true;
    }
#line 8068 "MachineIndependent/glslang_tab.cpp"
    break;

  case 215: /* storage_qualifier: SUBROUTINE  */
#line 1741 "MachineIndependent/glslang.y"
                 {
        parseContext.spvRemoved((yyvsp[0].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[0].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[0].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
    }
#line 8079 "MachineIndependent/glslang_tab.cpp"
    break;

  case 216: /* storage_qualifier: SUBROUTINE LEFT_PAREN type_name_list RIGHT_PAREN  */
#line 1747 "MachineIndependent/glslang.y"
                                                       {
        parseContext.spvRemoved((yyvsp[-3].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[-3].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[-3].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[-3].lex).loc);
    }
#line 8090 "MachineIndependent/glslang_tab.cpp"
    break;

  case 217: /* storage_qualifier: TASKPAYLOADWORKGROUPEXT  */
#line 1753 "MachineIndependent/glslang.y"
                              {
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "taskPayloadSharedEXT");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTaskMask | EShLangMeshMask), "taskPayloadSharedEXT  ");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqtaskPayloadSharedEXT;
    }
#line 8102 "MachineIndependent/glslang_tab.cpp"
    break;

  case 218: /* non_uniform_qualifier: NONUNIFORM  */
#line 1763 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.nonUniform = true;
    }
#line 8111 "MachineIndependent/glslang_tab.cpp"
    break;

  case 219: /* type_name_list: IDENTIFIER  */
#line 1770 "MachineIndependent/glslang.y"
                 {
        // TODO
    }
#line 8119 "MachineIndependent/glslang_tab.cpp"
    break;

  case 220: /* type_name_list: type_name_list COMMA IDENTIFIER  */
#line 1773 "MachineIndependent/glslang.y"
                                      {
        // TODO: 4.0 semantics: subroutines
        // 1) make sure each identifier is a type declared earlier with SUBROUTINE
        // 2) save all of the identifiers for future comparison with the declared function
    }
#line 8129 "MachineIndependent/glslang_tab.cpp"
    break;

  case 221: /* type_specifier: type_specifier_nonarray type_parameter_specifier_opt  */
#line 1781 "MachineIndependent/glslang.y"
                                                           {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).typeParameters = (yyvsp[0].interm.typeParameters);
        parseContext.typeParametersCheck((yyvsp[-1].interm.type).loc, (yyval.interm.type));

    }
#line 8141 "MachineIndependent/glslang_tab.cpp"
    break;

  case 222: /* type_specifier: type_specifier_nonarray type_parameter_specifier_opt array_specifier  */
#line 1788 "MachineIndependent/glslang.y"
                                                                           {
        parseContext.arrayOfArrayVersionCheck((yyvsp[0].interm).loc, (yyvsp[0].interm).arraySizes);
        (yyval.interm.type) = (yyvsp[-2].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).typeParameters = (yyvsp[-1].interm.typeParameters);
        (yyval.interm.type).arraySizes = (yyvsp[0].interm).arraySizes;
        parseContext.typeParametersCheck((yyvsp[-2].interm.type).loc, (yyval.interm.type));
    }
#line 8154 "MachineIndependent/glslang_tab.cpp"
    break;

  case 223: /* array_specifier: LEFT_BRACKET RIGHT_BRACKET  */
#line 1799 "MachineIndependent/glslang.y"
                                 {
        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 8164 "MachineIndependent/glslang_tab.cpp"
    break;

  case 224: /* array_specifier: LEFT_BRACKET conditional_expression RIGHT_BRACKET  */
#line 1804 "MachineIndependent/glslang.y"
                                                        {
        (yyval.interm).loc = (yyvsp[-2].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size, "array size");
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 8177 "MachineIndependent/glslang_tab.cpp"
    break;

  case 225: /* array_specifier: array_specifier LEFT_BRACKET RIGHT_BRACKET  */
#line 1812 "MachineIndependent/glslang.y"
                                                 {
        (yyval.interm) = (yyvsp[-2].interm);
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 8186 "MachineIndependent/glslang_tab.cpp"
    break;

  case 226: /* array_specifier: array_specifier LEFT_BRACKET conditional_expression RIGHT_BRACKET  */
#line 1816 "MachineIndependent/glslang.y"
                                                                        {
        (yyval.interm) = (yyvsp[-3].interm);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size, "array size");
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 8198 "MachineIndependent/glslang_tab.cpp"
    break;

  case 227: /* type_parameter_specifier_opt: type_parameter_specifier  */
#line 1826 "MachineIndependent/glslang.y"
                               {
        (yyval.interm.typeParameters) = (yyvsp[0].interm.typeParameters);
    }
#line 8206 "MachineIndependent/glslang_tab.cpp"
    break;

  case 228: /* type_parameter_specifier_opt: %empty  */
#line 1829 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.typeParameters) = 0;
    }
#line 8214 "MachineIndependent/glslang_tab.cpp"
    break;

  case 229: /* type_parameter_specifier: LEFT_ANGLE type_parameter_specifier_list RIGHT_ANGLE  */
#line 1835 "MachineIndependent/glslang.y"
                                                           {
        (yyval.interm.typeParameters) = (yyvsp[-1].interm.typeParameters);
    }
#line 8222 "MachineIndependent/glslang_tab.cpp"
    break;

  case 230: /* type_parameter_specifier_list: type_specifier  */
#line 1841 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.typeParameters) = new TTypeParameters;
        (yyval.interm.typeParameters)->arraySizes = new TArraySizes;
        (yyval.interm.typeParameters)->spirvType = (yyvsp[0].interm.type).spirvType;
        (yyval.interm.typeParameters)->basicType = (yyvsp[0].interm.type).basicType;
    }
#line 8233 "MachineIndependent/glslang_tab.cpp"
    break;

  case 231: /* type_parameter_specifier_list: unary_expression  */
#line 1847 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.typeParameters) = new TTypeParameters;
        (yyval.interm.typeParameters)->arraySizes = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode), size, "type parameter", true);
        (yyval.interm.typeParameters)->arraySizes->addInnerSize(size);
    }
#line 8246 "MachineIndependent/glslang_tab.cpp"
    break;

  case 232: /* type_parameter_specifier_list: type_parameter_specifier_list COMMA unary_expression  */
#line 1855 "MachineIndependent/glslang.y"
                                                           {
        (yyval.interm.typeParameters) = (yyvsp[-2].interm.typeParameters);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode), size, "type parameter", true);
        (yyval.interm.typeParameters)->arraySizes->addInnerSize(size);
    }
#line 8258 "MachineIndependent/glslang_tab.cpp"
    break;

  case 233: /* type_specifier_nonarray: VOID  */
#line 1865 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtVoid;
    }
#line 8267 "MachineIndependent/glslang_tab.cpp"
    break;

  case 234: /* type_specifier_nonarray: FLOAT  */
#line 1869 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
#line 8276 "MachineIndependent/glslang_tab.cpp"
    break;

  case 235: /* type_specifier_nonarray: INT  */
#line 1873 "MachineIndependent/glslang.y"
          {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
#line 8285 "MachineIndependent/glslang_tab.cpp"
    break;

  case 236: /* type_specifier_nonarray: UINT  */
#line 1877 "MachineIndependent/glslang.y"
           {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
#line 8295 "MachineIndependent/glslang_tab.cpp"
    break;

  case 237: /* type_specifier_nonarray: BOOL  */
#line 1882 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
    }
#line 8304 "MachineIndependent/glslang_tab.cpp"
    break;

  case 238: /* type_specifier_nonarray: VEC2  */
#line 1886 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
#line 8314 "MachineIndependent/glslang_tab.cpp"
    break;

  case 239: /* type_specifier_nonarray: VEC3  */
#line 1891 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
#line 8324 "MachineIndependent/glslang_tab.cpp"
    break;

  case 240: /* type_specifier_nonarray: VEC4  */
#line 1896 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
#line 8334 "MachineIndependent/glslang_tab.cpp"
    break;

  case 241: /* type_specifier_nonarray: BVEC2  */
#line 1901 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(2);
    }
#line 8344 "MachineIndependent/glslang_tab.cpp"
    break;

  case 242: /* type_specifier_nonarray: BVEC3  */
#line 1906 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(3);
    }
#line 8354 "MachineIndependent/glslang_tab.cpp"
    break;

  case 243: /* type_specifier_nonarray: BVEC4  */
#line 1911 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(4);
    }
#line 8364 "MachineIndependent/glslang_tab.cpp"
    break;

  case 244: /* type_specifier_nonarray: IVEC2  */
#line 1916 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
#line 8374 "MachineIndependent/glslang_tab.cpp"
    break;

  case 245: /* type_specifier_nonarray: IVEC3  */
#line 1921 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
#line 8384 "MachineIndependent/glslang_tab.cpp"
    break;

  case 246: /* type_specifier_nonarray: IVEC4  */
#line 1926 "MachineIndependent/glslang.y"
            {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
#line 8394 "MachineIndependent/glslang_tab.cpp"
    break;

  case 247: /* type_specifier_nonarray: UVEC2  */
#line 1931 "MachineIndependent/glslang.y"
            {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
#line 8405 "MachineIndependent/glslang_tab.cpp"
    break;

  case 248: /* type_specifier_nonarray: UVEC3  */
#line 1937 "MachineIndependent/glslang.y"
            {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
#line 8416 "MachineIndependent/glslang_tab.cpp"
    break;

  case 249: /* type_specifier_nonarray: UVEC4  */
#line 1943 "MachineIndependent/glslang.y"
            {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
#line 8427 "MachineIndependent/glslang_tab.cpp"
    break;

  case 250: /* type_specifier_nonarray: MAT2  */
#line 1949 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 8437 "MachineIndependent/glslang_tab.cpp"
    break;

  case 251: /* type_specifier_nonarray: MAT3  */
#line 1954 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 8447 "MachineIndependent/glslang_tab.cpp"
    break;

  case 252: /* type_specifier_nonarray: MAT4  */
#line 1959 "MachineIndependent/glslang.y"
           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 8457 "MachineIndependent/glslang_tab.cpp"
    break;

  case 253: /* type_specifier_nonarray: MAT2X2  */
#line 1964 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 8467 "MachineIndependent/glslang_tab.cpp"
    break;

  case 254: /* type_specifier_nonarray: MAT2X3  */
#line 1969 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 8477 "MachineIndependent/glslang_tab.cpp"
    break;

  case 255: /* type_specifier_nonarray: MAT2X4  */
#line 1974 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 8487 "MachineIndependent/glslang_tab.cpp"
    break;

  case 256: /* type_specifier_nonarray: MAT3X2  */
#line 1979 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 8497 "MachineIndependent/glslang_tab.cpp"
    break;

  case 257: /* type_specifier_nonarray: MAT3X3  */
#line 1984 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 8507 "MachineIndependent/glslang_tab.cpp"
    break;

  case 258: /* type_specifier_nonarray: MAT3X4  */
#line 1989 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 8517 "MachineIndependent/glslang_tab.cpp"
    break;

  case 259: /* type_specifier_nonarray: MAT4X2  */
#line 1994 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 8527 "MachineIndependent/glslang_tab.cpp"
    break;

  case 260: /* type_specifier_nonarray: MAT4X3  */
#line 1999 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 8537 "MachineIndependent/glslang_tab.cpp"
    break;

  case 261: /* type_specifier_nonarray: MAT4X4  */
#line 2004 "MachineIndependent/glslang.y"
             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 8547 "MachineIndependent/glslang_tab.cpp"
    break;

  case 262: /* type_specifier_nonarray: DOUBLE  */
#line 2009 "MachineIndependent/glslang.y"
             {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
#line 8559 "MachineIndependent/glslang_tab.cpp"
    break;

  case 263: /* type_specifier_nonarray: BFLOAT16_T  */
#line 2016 "MachineIndependent/glslang.y"
                 {
        parseContext.bfloat16ScalarVectorCheck((yyvsp[0].lex).loc, "bfloat16_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBFloat16;
    }
#line 8569 "MachineIndependent/glslang_tab.cpp"
    break;

  case 264: /* type_specifier_nonarray: FLOATE5M2_T  */
#line 2021 "MachineIndependent/glslang.y"
                  {
        parseContext.floate5m2ScalarVectorCheck((yyvsp[0].lex).loc, "floate5m2_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE5M2;
    }
#line 8579 "MachineIndependent/glslang_tab.cpp"
    break;

  case 265: /* type_specifier_nonarray: FLOATE4M3_T  */
#line 2026 "MachineIndependent/glslang.y"
                  {
        parseContext.floate4m3ScalarVectorCheck((yyvsp[0].lex).loc, "floate4m3_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE4M3;
    }
#line 8589 "MachineIndependent/glslang_tab.cpp"
    break;

  case 266: /* type_specifier_nonarray: FLOAT16_T  */
#line 2031 "MachineIndependent/glslang.y"
                {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "float16_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
    }
#line 8599 "MachineIndependent/glslang_tab.cpp"
    break;

  case 267: /* type_specifier_nonarray: FLOAT32_T  */
#line 2036 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
#line 8609 "MachineIndependent/glslang_tab.cpp"
    break;

  case 268: /* type_specifier_nonarray: FLOAT64_T  */
#line 2041 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
#line 8619 "MachineIndependent/glslang_tab.cpp"
    break;

  case 269: /* type_specifier_nonarray: INT8_T  */
#line 2046 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
    }
#line 8629 "MachineIndependent/glslang_tab.cpp"
    break;

  case 270: /* type_specifier_nonarray: UINT8_T  */
#line 2051 "MachineIndependent/glslang.y"
              {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
    }
#line 8639 "MachineIndependent/glslang_tab.cpp"
    break;

  case 271: /* type_specifier_nonarray: INT16_T  */
#line 2056 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
    }
#line 8649 "MachineIndependent/glslang_tab.cpp"
    break;

  case 272: /* type_specifier_nonarray: UINT16_T  */
#line 2061 "MachineIndependent/glslang.y"
               {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
    }
#line 8659 "MachineIndependent/glslang_tab.cpp"
    break;

  case 273: /* type_specifier_nonarray: INT32_T  */
#line 2066 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
#line 8669 "MachineIndependent/glslang_tab.cpp"
    break;

  case 274: /* type_specifier_nonarray: UINT32_T  */
#line 2071 "MachineIndependent/glslang.y"
               {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
#line 8679 "MachineIndependent/glslang_tab.cpp"
    break;

  case 275: /* type_specifier_nonarray: INT64_T  */
#line 2076 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
    }
#line 8689 "MachineIndependent/glslang_tab.cpp"
    break;

  case 276: /* type_specifier_nonarray: UINT64_T  */
#line 2081 "MachineIndependent/glslang.y"
               {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
    }
#line 8699 "MachineIndependent/glslang_tab.cpp"
    break;

  case 277: /* type_specifier_nonarray: DVEC2  */
#line 2086 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double vector");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
#line 8712 "MachineIndependent/glslang_tab.cpp"
    break;

  case 278: /* type_specifier_nonarray: DVEC3  */
#line 2094 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double vector");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
#line 8725 "MachineIndependent/glslang_tab.cpp"
    break;

  case 279: /* type_specifier_nonarray: DVEC4  */
#line 2102 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double vector");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
#line 8738 "MachineIndependent/glslang_tab.cpp"
    break;

  case 280: /* type_specifier_nonarray: BF16VEC2  */
#line 2110 "MachineIndependent/glslang.y"
               {
        parseContext.bfloat16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBFloat16;
        (yyval.interm.type).setVector(2);
    }
#line 8749 "MachineIndependent/glslang_tab.cpp"
    break;

  case 281: /* type_specifier_nonarray: BF16VEC3  */
#line 2116 "MachineIndependent/glslang.y"
               {
        parseContext.bfloat16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBFloat16;
        (yyval.interm.type).setVector(3);
    }
#line 8760 "MachineIndependent/glslang_tab.cpp"
    break;

  case 282: /* type_specifier_nonarray: BF16VEC4  */
#line 2122 "MachineIndependent/glslang.y"
               {
        parseContext.bfloat16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBFloat16;
        (yyval.interm.type).setVector(4);
    }
#line 8771 "MachineIndependent/glslang_tab.cpp"
    break;

  case 283: /* type_specifier_nonarray: FE5M2VEC2  */
#line 2128 "MachineIndependent/glslang.y"
                {
        parseContext.floate5m2ScalarVectorCheck((yyvsp[0].lex).loc, "fe5m2 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE5M2;
        (yyval.interm.type).setVector(2);
    }
#line 8782 "MachineIndependent/glslang_tab.cpp"
    break;

  case 284: /* type_specifier_nonarray: FE5M2VEC3  */
#line 2134 "MachineIndependent/glslang.y"
                {
        parseContext.floate5m2ScalarVectorCheck((yyvsp[0].lex).loc, "fe5m2 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE5M2;
        (yyval.interm.type).setVector(3);
    }
#line 8793 "MachineIndependent/glslang_tab.cpp"
    break;

  case 285: /* type_specifier_nonarray: FE5M2VEC4  */
#line 2140 "MachineIndependent/glslang.y"
                {
        parseContext.floate5m2ScalarVectorCheck((yyvsp[0].lex).loc, "fe5m2 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE5M2;
        (yyval.interm.type).setVector(4);
    }
#line 8804 "MachineIndependent/glslang_tab.cpp"
    break;

  case 286: /* type_specifier_nonarray: FE4M3VEC2  */
#line 2146 "MachineIndependent/glslang.y"
                {
        parseContext.floate4m3ScalarVectorCheck((yyvsp[0].lex).loc, "fe4m3 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE4M3;
        (yyval.interm.type).setVector(2);
    }
#line 8815 "MachineIndependent/glslang_tab.cpp"
    break;

  case 287: /* type_specifier_nonarray: FE4M3VEC3  */
#line 2152 "MachineIndependent/glslang.y"
                {
        parseContext.floate4m3ScalarVectorCheck((yyvsp[0].lex).loc, "fe4m3 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE4M3;
        (yyval.interm.type).setVector(3);
    }
#line 8826 "MachineIndependent/glslang_tab.cpp"
    break;

  case 288: /* type_specifier_nonarray: FE4M3VEC4  */
#line 2158 "MachineIndependent/glslang.y"
                {
        parseContext.floate4m3ScalarVectorCheck((yyvsp[0].lex).loc, "fe4m3 vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloatE4M3;
        (yyval.interm.type).setVector(4);
    }
#line 8837 "MachineIndependent/glslang_tab.cpp"
    break;

  case 289: /* type_specifier_nonarray: F16VEC2  */
#line 2164 "MachineIndependent/glslang.y"
              {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(2);
    }
#line 8848 "MachineIndependent/glslang_tab.cpp"
    break;

  case 290: /* type_specifier_nonarray: F16VEC3  */
#line 2170 "MachineIndependent/glslang.y"
              {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(3);
    }
#line 8859 "MachineIndependent/glslang_tab.cpp"
    break;

  case 291: /* type_specifier_nonarray: F16VEC4  */
#line 2176 "MachineIndependent/glslang.y"
              {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(4);
    }
#line 8870 "MachineIndependent/glslang_tab.cpp"
    break;

  case 292: /* type_specifier_nonarray: F32VEC2  */
#line 2182 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
#line 8881 "MachineIndependent/glslang_tab.cpp"
    break;

  case 293: /* type_specifier_nonarray: F32VEC3  */
#line 2188 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
#line 8892 "MachineIndependent/glslang_tab.cpp"
    break;

  case 294: /* type_specifier_nonarray: F32VEC4  */
#line 2194 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
#line 8903 "MachineIndependent/glslang_tab.cpp"
    break;

  case 295: /* type_specifier_nonarray: F64VEC2  */
#line 2200 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
#line 8914 "MachineIndependent/glslang_tab.cpp"
    break;

  case 296: /* type_specifier_nonarray: F64VEC3  */
#line 2206 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
#line 8925 "MachineIndependent/glslang_tab.cpp"
    break;

  case 297: /* type_specifier_nonarray: F64VEC4  */
#line 2212 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
#line 8936 "MachineIndependent/glslang_tab.cpp"
    break;

  case 298: /* type_specifier_nonarray: I8VEC2  */
#line 2218 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(2);
    }
#line 8947 "MachineIndependent/glslang_tab.cpp"
    break;

  case 299: /* type_specifier_nonarray: I8VEC3  */
#line 2224 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(3);
    }
#line 8958 "MachineIndependent/glslang_tab.cpp"
    break;

  case 300: /* type_specifier_nonarray: I8VEC4  */
#line 2230 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(4);
    }
#line 8969 "MachineIndependent/glslang_tab.cpp"
    break;

  case 301: /* type_specifier_nonarray: I16VEC2  */
#line 2236 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(2);
    }
#line 8980 "MachineIndependent/glslang_tab.cpp"
    break;

  case 302: /* type_specifier_nonarray: I16VEC3  */
#line 2242 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(3);
    }
#line 8991 "MachineIndependent/glslang_tab.cpp"
    break;

  case 303: /* type_specifier_nonarray: I16VEC4  */
#line 2248 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(4);
    }
#line 9002 "MachineIndependent/glslang_tab.cpp"
    break;

  case 304: /* type_specifier_nonarray: I32VEC2  */
#line 2254 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
#line 9013 "MachineIndependent/glslang_tab.cpp"
    break;

  case 305: /* type_specifier_nonarray: I32VEC3  */
#line 2260 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
#line 9024 "MachineIndependent/glslang_tab.cpp"
    break;

  case 306: /* type_specifier_nonarray: I32VEC4  */
#line 2266 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
#line 9035 "MachineIndependent/glslang_tab.cpp"
    break;

  case 307: /* type_specifier_nonarray: I64VEC2  */
#line 2272 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(2);
    }
#line 9046 "MachineIndependent/glslang_tab.cpp"
    break;

  case 308: /* type_specifier_nonarray: I64VEC3  */
#line 2278 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(3);
    }
#line 9057 "MachineIndependent/glslang_tab.cpp"
    break;

  case 309: /* type_specifier_nonarray: I64VEC4  */
#line 2284 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(4);
    }
#line 9068 "MachineIndependent/glslang_tab.cpp"
    break;

  case 310: /* type_specifier_nonarray: U8VEC2  */
#line 2290 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(2);
    }
#line 9079 "MachineIndependent/glslang_tab.cpp"
    break;

  case 311: /* type_specifier_nonarray: U8VEC3  */
#line 2296 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(3);
    }
#line 9090 "MachineIndependent/glslang_tab.cpp"
    break;

  case 312: /* type_specifier_nonarray: U8VEC4  */
#line 2302 "MachineIndependent/glslang.y"
             {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(4);
    }
#line 9101 "MachineIndependent/glslang_tab.cpp"
    break;

  case 313: /* type_specifier_nonarray: U16VEC2  */
#line 2308 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(2);
    }
#line 9112 "MachineIndependent/glslang_tab.cpp"
    break;

  case 314: /* type_specifier_nonarray: U16VEC3  */
#line 2314 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(3);
    }
#line 9123 "MachineIndependent/glslang_tab.cpp"
    break;

  case 315: /* type_specifier_nonarray: U16VEC4  */
#line 2320 "MachineIndependent/glslang.y"
              {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(4);
    }
#line 9134 "MachineIndependent/glslang_tab.cpp"
    break;

  case 316: /* type_specifier_nonarray: U32VEC2  */
#line 2326 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
#line 9145 "MachineIndependent/glslang_tab.cpp"
    break;

  case 317: /* type_specifier_nonarray: U32VEC3  */
#line 2332 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
#line 9156 "MachineIndependent/glslang_tab.cpp"
    break;

  case 318: /* type_specifier_nonarray: U32VEC4  */
#line 2338 "MachineIndependent/glslang.y"
              {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
#line 9167 "MachineIndependent/glslang_tab.cpp"
    break;

  case 319: /* type_specifier_nonarray: U64VEC2  */
#line 2344 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(2);
    }
#line 9178 "MachineIndependent/glslang_tab.cpp"
    break;

  case 320: /* type_specifier_nonarray: U64VEC3  */
#line 2350 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(3);
    }
#line 9189 "MachineIndependent/glslang_tab.cpp"
    break;

  case 321: /* type_specifier_nonarray: U64VEC4  */
#line 2356 "MachineIndependent/glslang.y"
              {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(4);
    }
#line 9200 "MachineIndependent/glslang_tab.cpp"
    break;

  case 322: /* type_specifier_nonarray: DMAT2  */
#line 2362 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9213 "MachineIndependent/glslang_tab.cpp"
    break;

  case 323: /* type_specifier_nonarray: DMAT3  */
#line 2370 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9226 "MachineIndependent/glslang_tab.cpp"
    break;

  case 324: /* type_specifier_nonarray: DMAT4  */
#line 2378 "MachineIndependent/glslang.y"
            {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9239 "MachineIndependent/glslang_tab.cpp"
    break;

  case 325: /* type_specifier_nonarray: DMAT2X2  */
#line 2386 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9252 "MachineIndependent/glslang_tab.cpp"
    break;

  case 326: /* type_specifier_nonarray: DMAT2X3  */
#line 2394 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 9265 "MachineIndependent/glslang_tab.cpp"
    break;

  case 327: /* type_specifier_nonarray: DMAT2X4  */
#line 2402 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 9278 "MachineIndependent/glslang_tab.cpp"
    break;

  case 328: /* type_specifier_nonarray: DMAT3X2  */
#line 2410 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 9291 "MachineIndependent/glslang_tab.cpp"
    break;

  case 329: /* type_specifier_nonarray: DMAT3X3  */
#line 2418 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9304 "MachineIndependent/glslang_tab.cpp"
    break;

  case 330: /* type_specifier_nonarray: DMAT3X4  */
#line 2426 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 9317 "MachineIndependent/glslang_tab.cpp"
    break;

  case 331: /* type_specifier_nonarray: DMAT4X2  */
#line 2434 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 9330 "MachineIndependent/glslang_tab.cpp"
    break;

  case 332: /* type_specifier_nonarray: DMAT4X3  */
#line 2442 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 9343 "MachineIndependent/glslang_tab.cpp"
    break;

  case 333: /* type_specifier_nonarray: DMAT4X4  */
#line 2450 "MachineIndependent/glslang.y"
              {
        parseContext.requireProfile((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, "double matrix");
        if (! parseContext.symbolTable.atBuiltInLevel())
            parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9356 "MachineIndependent/glslang_tab.cpp"
    break;

  case 334: /* type_specifier_nonarray: F16MAT2  */
#line 2458 "MachineIndependent/glslang.y"
              {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9367 "MachineIndependent/glslang_tab.cpp"
    break;

  case 335: /* type_specifier_nonarray: F16MAT3  */
#line 2464 "MachineIndependent/glslang.y"
              {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9378 "MachineIndependent/glslang_tab.cpp"
    break;

  case 336: /* type_specifier_nonarray: F16MAT4  */
#line 2470 "MachineIndependent/glslang.y"
              {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9389 "MachineIndependent/glslang_tab.cpp"
    break;

  case 337: /* type_specifier_nonarray: F16MAT2X2  */
#line 2476 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9400 "MachineIndependent/glslang_tab.cpp"
    break;

  case 338: /* type_specifier_nonarray: F16MAT2X3  */
#line 2482 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 9411 "MachineIndependent/glslang_tab.cpp"
    break;

  case 339: /* type_specifier_nonarray: F16MAT2X4  */
#line 2488 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 9422 "MachineIndependent/glslang_tab.cpp"
    break;

  case 340: /* type_specifier_nonarray: F16MAT3X2  */
#line 2494 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 9433 "MachineIndependent/glslang_tab.cpp"
    break;

  case 341: /* type_specifier_nonarray: F16MAT3X3  */
#line 2500 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9444 "MachineIndependent/glslang_tab.cpp"
    break;

  case 342: /* type_specifier_nonarray: F16MAT3X4  */
#line 2506 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 9455 "MachineIndependent/glslang_tab.cpp"
    break;

  case 343: /* type_specifier_nonarray: F16MAT4X2  */
#line 2512 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 9466 "MachineIndependent/glslang_tab.cpp"
    break;

  case 344: /* type_specifier_nonarray: F16MAT4X3  */
#line 2518 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 9477 "MachineIndependent/glslang_tab.cpp"
    break;

  case 345: /* type_specifier_nonarray: F16MAT4X4  */
#line 2524 "MachineIndependent/glslang.y"
                {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9488 "MachineIndependent/glslang_tab.cpp"
    break;

  case 346: /* type_specifier_nonarray: F32MAT2  */
#line 2530 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9499 "MachineIndependent/glslang_tab.cpp"
    break;

  case 347: /* type_specifier_nonarray: F32MAT3  */
#line 2536 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9510 "MachineIndependent/glslang_tab.cpp"
    break;

  case 348: /* type_specifier_nonarray: F32MAT4  */
#line 2542 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9521 "MachineIndependent/glslang_tab.cpp"
    break;

  case 349: /* type_specifier_nonarray: F32MAT2X2  */
#line 2548 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9532 "MachineIndependent/glslang_tab.cpp"
    break;

  case 350: /* type_specifier_nonarray: F32MAT2X3  */
#line 2554 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 9543 "MachineIndependent/glslang_tab.cpp"
    break;

  case 351: /* type_specifier_nonarray: F32MAT2X4  */
#line 2560 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 9554 "MachineIndependent/glslang_tab.cpp"
    break;

  case 352: /* type_specifier_nonarray: F32MAT3X2  */
#line 2566 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 9565 "MachineIndependent/glslang_tab.cpp"
    break;

  case 353: /* type_specifier_nonarray: F32MAT3X3  */
#line 2572 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9576 "MachineIndependent/glslang_tab.cpp"
    break;

  case 354: /* type_specifier_nonarray: F32MAT3X4  */
#line 2578 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 9587 "MachineIndependent/glslang_tab.cpp"
    break;

  case 355: /* type_specifier_nonarray: F32MAT4X2  */
#line 2584 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 9598 "MachineIndependent/glslang_tab.cpp"
    break;

  case 356: /* type_specifier_nonarray: F32MAT4X3  */
#line 2590 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 9609 "MachineIndependent/glslang_tab.cpp"
    break;

  case 357: /* type_specifier_nonarray: F32MAT4X4  */
#line 2596 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9620 "MachineIndependent/glslang_tab.cpp"
    break;

  case 358: /* type_specifier_nonarray: F64MAT2  */
#line 2602 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9631 "MachineIndependent/glslang_tab.cpp"
    break;

  case 359: /* type_specifier_nonarray: F64MAT3  */
#line 2608 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9642 "MachineIndependent/glslang_tab.cpp"
    break;

  case 360: /* type_specifier_nonarray: F64MAT4  */
#line 2614 "MachineIndependent/glslang.y"
              {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9653 "MachineIndependent/glslang_tab.cpp"
    break;

  case 361: /* type_specifier_nonarray: F64MAT2X2  */
#line 2620 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 9664 "MachineIndependent/glslang_tab.cpp"
    break;

  case 362: /* type_specifier_nonarray: F64MAT2X3  */
#line 2626 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 9675 "MachineIndependent/glslang_tab.cpp"
    break;

  case 363: /* type_specifier_nonarray: F64MAT2X4  */
#line 2632 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 9686 "MachineIndependent/glslang_tab.cpp"
    break;

  case 364: /* type_specifier_nonarray: F64MAT3X2  */
#line 2638 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 9697 "MachineIndependent/glslang_tab.cpp"
    break;

  case 365: /* type_specifier_nonarray: F64MAT3X3  */
#line 2644 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 9708 "MachineIndependent/glslang_tab.cpp"
    break;

  case 366: /* type_specifier_nonarray: F64MAT3X4  */
#line 2650 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 9719 "MachineIndependent/glslang_tab.cpp"
    break;

  case 367: /* type_specifier_nonarray: F64MAT4X2  */
#line 2656 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 9730 "MachineIndependent/glslang_tab.cpp"
    break;

  case 368: /* type_specifier_nonarray: F64MAT4X3  */
#line 2662 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 9741 "MachineIndependent/glslang_tab.cpp"
    break;

  case 369: /* type_specifier_nonarray: F64MAT4X4  */
#line 2668 "MachineIndependent/glslang.y"
                {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 9752 "MachineIndependent/glslang_tab.cpp"
    break;

  case 370: /* type_specifier_nonarray: ACCSTRUCTNV  */
#line 2674 "MachineIndependent/glslang.y"
                  {
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtAccStruct;
    }
#line 9761 "MachineIndependent/glslang_tab.cpp"
    break;

  case 371: /* type_specifier_nonarray: ACCSTRUCTEXT  */
#line 2678 "MachineIndependent/glslang.y"
                   {
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtAccStruct;
    }
#line 9770 "MachineIndependent/glslang_tab.cpp"
    break;

  case 372: /* type_specifier_nonarray: RAYQUERYEXT  */
#line 2682 "MachineIndependent/glslang.y"
                  {
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtRayQuery;
    }
#line 9779 "MachineIndependent/glslang_tab.cpp"
    break;

  case 373: /* type_specifier_nonarray: ATOMIC_UINT  */
#line 2686 "MachineIndependent/glslang.y"
                  {
        parseContext.vulkanRemoved((yyvsp[0].lex).loc, "atomic counter types");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtAtomicUint;
    }
#line 9789 "MachineIndependent/glslang_tab.cpp"
    break;

  case 374: /* type_specifier_nonarray: SAMPLER1D  */
#line 2691 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D);
    }
#line 9799 "MachineIndependent/glslang_tab.cpp"
    break;

  case 375: /* type_specifier_nonarray: SAMPLER2D  */
#line 2696 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
    }
#line 9809 "MachineIndependent/glslang_tab.cpp"
    break;

  case 376: /* type_specifier_nonarray: SAMPLER3D  */
#line 2701 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd3D);
    }
#line 9819 "MachineIndependent/glslang_tab.cpp"
    break;

  case 377: /* type_specifier_nonarray: SAMPLERCUBE  */
#line 2706 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube);
    }
#line 9829 "MachineIndependent/glslang_tab.cpp"
    break;

  case 378: /* type_specifier_nonarray: SAMPLER2DSHADOW  */
#line 2711 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, true);
    }
#line 9839 "MachineIndependent/glslang_tab.cpp"
    break;

  case 379: /* type_specifier_nonarray: SAMPLERCUBESHADOW  */
#line 2716 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, false, true);
    }
#line 9849 "MachineIndependent/glslang_tab.cpp"
    break;

  case 380: /* type_specifier_nonarray: SAMPLER2DARRAY  */
#line 2721 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true);
    }
#line 9859 "MachineIndependent/glslang_tab.cpp"
    break;

  case 381: /* type_specifier_nonarray: SAMPLER2DARRAYSHADOW  */
#line 2726 "MachineIndependent/glslang.y"
                           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, true);
    }
#line 9869 "MachineIndependent/glslang_tab.cpp"
    break;

  case 382: /* type_specifier_nonarray: SAMPLER1DSHADOW  */
#line 2731 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, false, true);
    }
#line 9879 "MachineIndependent/glslang_tab.cpp"
    break;

  case 383: /* type_specifier_nonarray: SAMPLER1DARRAY  */
#line 2736 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true);
    }
#line 9889 "MachineIndependent/glslang_tab.cpp"
    break;

  case 384: /* type_specifier_nonarray: SAMPLER1DARRAYSHADOW  */
#line 2741 "MachineIndependent/glslang.y"
                           {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true, true);
    }
#line 9899 "MachineIndependent/glslang_tab.cpp"
    break;

  case 385: /* type_specifier_nonarray: SAMPLERCUBEARRAY  */
#line 2746 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true);
    }
#line 9909 "MachineIndependent/glslang_tab.cpp"
    break;

  case 386: /* type_specifier_nonarray: SAMPLERCUBEARRAYSHADOW  */
#line 2751 "MachineIndependent/glslang.y"
                             {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true, true);
    }
#line 9919 "MachineIndependent/glslang_tab.cpp"
    break;

  case 387: /* type_specifier_nonarray: F16SAMPLER1D  */
#line 2756 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D);
    }
#line 9930 "MachineIndependent/glslang_tab.cpp"
    break;

  case 388: /* type_specifier_nonarray: F16SAMPLER2D  */
#line 2762 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D);
    }
#line 9941 "MachineIndependent/glslang_tab.cpp"
    break;

  case 389: /* type_specifier_nonarray: F16SAMPLER3D  */
#line 2768 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd3D);
    }
#line 9952 "MachineIndependent/glslang_tab.cpp"
    break;

  case 390: /* type_specifier_nonarray: F16SAMPLERCUBE  */
#line 2774 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube);
    }
#line 9963 "MachineIndependent/glslang_tab.cpp"
    break;

  case 391: /* type_specifier_nonarray: F16SAMPLER1DSHADOW  */
#line 2780 "MachineIndependent/glslang.y"
                         {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, false, true);
    }
#line 9974 "MachineIndependent/glslang_tab.cpp"
    break;

  case 392: /* type_specifier_nonarray: F16SAMPLER2DSHADOW  */
#line 2786 "MachineIndependent/glslang.y"
                         {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, true);
    }
#line 9985 "MachineIndependent/glslang_tab.cpp"
    break;

  case 393: /* type_specifier_nonarray: F16SAMPLERCUBESHADOW  */
#line 2792 "MachineIndependent/glslang.y"
                           {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, false, true);
    }
#line 9996 "MachineIndependent/glslang_tab.cpp"
    break;

  case 394: /* type_specifier_nonarray: F16SAMPLER1DARRAY  */
#line 2798 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true);
    }
#line 10007 "MachineIndependent/glslang_tab.cpp"
    break;

  case 395: /* type_specifier_nonarray: F16SAMPLER2DARRAY  */
#line 2804 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true);
    }
#line 10018 "MachineIndependent/glslang_tab.cpp"
    break;

  case 396: /* type_specifier_nonarray: F16SAMPLER1DARRAYSHADOW  */
#line 2810 "MachineIndependent/glslang.y"
                              {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true, true);
    }
#line 10029 "MachineIndependent/glslang_tab.cpp"
    break;

  case 397: /* type_specifier_nonarray: F16SAMPLER2DARRAYSHADOW  */
#line 2816 "MachineIndependent/glslang.y"
                              {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, true);
    }
#line 10040 "MachineIndependent/glslang_tab.cpp"
    break;

  case 398: /* type_specifier_nonarray: F16SAMPLERCUBEARRAY  */
#line 2822 "MachineIndependent/glslang.y"
                          {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true);
    }
#line 10051 "MachineIndependent/glslang_tab.cpp"
    break;

  case 399: /* type_specifier_nonarray: F16SAMPLERCUBEARRAYSHADOW  */
#line 2828 "MachineIndependent/glslang.y"
                                {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true, true);
    }
#line 10062 "MachineIndependent/glslang_tab.cpp"
    break;

  case 400: /* type_specifier_nonarray: ISAMPLER1D  */
#line 2834 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D);
    }
#line 10072 "MachineIndependent/glslang_tab.cpp"
    break;

  case 401: /* type_specifier_nonarray: ISAMPLER2D  */
#line 2839 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D);
    }
#line 10082 "MachineIndependent/glslang_tab.cpp"
    break;

  case 402: /* type_specifier_nonarray: ISAMPLER3D  */
#line 2844 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd3D);
    }
#line 10092 "MachineIndependent/glslang_tab.cpp"
    break;

  case 403: /* type_specifier_nonarray: ISAMPLERCUBE  */
#line 2849 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube);
    }
#line 10102 "MachineIndependent/glslang_tab.cpp"
    break;

  case 404: /* type_specifier_nonarray: ISAMPLER2DARRAY  */
#line 2854 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true);
    }
#line 10112 "MachineIndependent/glslang_tab.cpp"
    break;

  case 405: /* type_specifier_nonarray: USAMPLER2D  */
#line 2859 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D);
    }
#line 10122 "MachineIndependent/glslang_tab.cpp"
    break;

  case 406: /* type_specifier_nonarray: USAMPLER3D  */
#line 2864 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd3D);
    }
#line 10132 "MachineIndependent/glslang_tab.cpp"
    break;

  case 407: /* type_specifier_nonarray: USAMPLERCUBE  */
#line 2869 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube);
    }
#line 10142 "MachineIndependent/glslang_tab.cpp"
    break;

  case 408: /* type_specifier_nonarray: ISAMPLER1DARRAY  */
#line 2874 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D, true);
    }
#line 10152 "MachineIndependent/glslang_tab.cpp"
    break;

  case 409: /* type_specifier_nonarray: ISAMPLERCUBEARRAY  */
#line 2879 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube, true);
    }
#line 10162 "MachineIndependent/glslang_tab.cpp"
    break;

  case 410: /* type_specifier_nonarray: USAMPLER1D  */
#line 2884 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D);
    }
#line 10172 "MachineIndependent/glslang_tab.cpp"
    break;

  case 411: /* type_specifier_nonarray: USAMPLER1DARRAY  */
#line 2889 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D, true);
    }
#line 10182 "MachineIndependent/glslang_tab.cpp"
    break;

  case 412: /* type_specifier_nonarray: USAMPLERCUBEARRAY  */
#line 2894 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube, true);
    }
#line 10192 "MachineIndependent/glslang_tab.cpp"
    break;

  case 413: /* type_specifier_nonarray: TEXTURECUBEARRAY  */
#line 2899 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube, true);
    }
#line 10202 "MachineIndependent/glslang_tab.cpp"
    break;

  case 414: /* type_specifier_nonarray: ITEXTURECUBEARRAY  */
#line 2904 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube, true);
    }
#line 10212 "MachineIndependent/glslang_tab.cpp"
    break;

  case 415: /* type_specifier_nonarray: UTEXTURECUBEARRAY  */
#line 2909 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube, true);
    }
#line 10222 "MachineIndependent/glslang_tab.cpp"
    break;

  case 416: /* type_specifier_nonarray: USAMPLER2DARRAY  */
#line 2914 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true);
    }
#line 10232 "MachineIndependent/glslang_tab.cpp"
    break;

  case 417: /* type_specifier_nonarray: TEXTURE2D  */
#line 2919 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D);
    }
#line 10242 "MachineIndependent/glslang_tab.cpp"
    break;

  case 418: /* type_specifier_nonarray: TEXTURE3D  */
#line 2924 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd3D);
    }
#line 10252 "MachineIndependent/glslang_tab.cpp"
    break;

  case 419: /* type_specifier_nonarray: TEXTURE2DARRAY  */
#line 2929 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true);
    }
#line 10262 "MachineIndependent/glslang_tab.cpp"
    break;

  case 420: /* type_specifier_nonarray: TEXTURECUBE  */
#line 2934 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube);
    }
#line 10272 "MachineIndependent/glslang_tab.cpp"
    break;

  case 421: /* type_specifier_nonarray: ITEXTURE2D  */
#line 2939 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D);
    }
#line 10282 "MachineIndependent/glslang_tab.cpp"
    break;

  case 422: /* type_specifier_nonarray: ITEXTURE3D  */
#line 2944 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd3D);
    }
#line 10292 "MachineIndependent/glslang_tab.cpp"
    break;

  case 423: /* type_specifier_nonarray: ITEXTURECUBE  */
#line 2949 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube);
    }
#line 10302 "MachineIndependent/glslang_tab.cpp"
    break;

  case 424: /* type_specifier_nonarray: ITEXTURE2DARRAY  */
#line 2954 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true);
    }
#line 10312 "MachineIndependent/glslang_tab.cpp"
    break;

  case 425: /* type_specifier_nonarray: UTEXTURE2D  */
#line 2959 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D);
    }
#line 10322 "MachineIndependent/glslang_tab.cpp"
    break;

  case 426: /* type_specifier_nonarray: UTEXTURE3D  */
#line 2964 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd3D);
    }
#line 10332 "MachineIndependent/glslang_tab.cpp"
    break;

  case 427: /* type_specifier_nonarray: UTEXTURECUBE  */
#line 2969 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube);
    }
#line 10342 "MachineIndependent/glslang_tab.cpp"
    break;

  case 428: /* type_specifier_nonarray: UTEXTURE2DARRAY  */
#line 2974 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true);
    }
#line 10352 "MachineIndependent/glslang_tab.cpp"
    break;

  case 429: /* type_specifier_nonarray: SAMPLER  */
#line 2979 "MachineIndependent/glslang.y"
              {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(false);
    }
#line 10362 "MachineIndependent/glslang_tab.cpp"
    break;

  case 430: /* type_specifier_nonarray: SAMPLERSHADOW  */
#line 2984 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(true);
    }
#line 10372 "MachineIndependent/glslang_tab.cpp"
    break;

  case 431: /* type_specifier_nonarray: SAMPLER2DRECT  */
#line 2989 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect);
    }
#line 10382 "MachineIndependent/glslang_tab.cpp"
    break;

  case 432: /* type_specifier_nonarray: SAMPLER2DRECTSHADOW  */
#line 2994 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect, false, true);
    }
#line 10392 "MachineIndependent/glslang_tab.cpp"
    break;

  case 433: /* type_specifier_nonarray: F16SAMPLER2DRECT  */
#line 2999 "MachineIndependent/glslang.y"
                       {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect);
    }
#line 10403 "MachineIndependent/glslang_tab.cpp"
    break;

  case 434: /* type_specifier_nonarray: F16SAMPLER2DRECTSHADOW  */
#line 3005 "MachineIndependent/glslang.y"
                             {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect, false, true);
    }
#line 10414 "MachineIndependent/glslang_tab.cpp"
    break;

  case 435: /* type_specifier_nonarray: ISAMPLER2DRECT  */
#line 3011 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdRect);
    }
#line 10424 "MachineIndependent/glslang_tab.cpp"
    break;

  case 436: /* type_specifier_nonarray: USAMPLER2DRECT  */
#line 3016 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdRect);
    }
#line 10434 "MachineIndependent/glslang_tab.cpp"
    break;

  case 437: /* type_specifier_nonarray: SAMPLERBUFFER  */
#line 3021 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdBuffer);
    }
#line 10444 "MachineIndependent/glslang_tab.cpp"
    break;

  case 438: /* type_specifier_nonarray: F16SAMPLERBUFFER  */
#line 3026 "MachineIndependent/glslang.y"
                       {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdBuffer);
    }
#line 10455 "MachineIndependent/glslang_tab.cpp"
    break;

  case 439: /* type_specifier_nonarray: ISAMPLERBUFFER  */
#line 3032 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdBuffer);
    }
#line 10465 "MachineIndependent/glslang_tab.cpp"
    break;

  case 440: /* type_specifier_nonarray: USAMPLERBUFFER  */
#line 3037 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdBuffer);
    }
#line 10475 "MachineIndependent/glslang_tab.cpp"
    break;

  case 441: /* type_specifier_nonarray: SAMPLER2DMS  */
#line 3042 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, false, true);
    }
#line 10485 "MachineIndependent/glslang_tab.cpp"
    break;

  case 442: /* type_specifier_nonarray: F16SAMPLER2DMS  */
#line 3047 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, false, true);
    }
#line 10496 "MachineIndependent/glslang_tab.cpp"
    break;

  case 443: /* type_specifier_nonarray: ISAMPLER2DMS  */
#line 3053 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, false, false, true);
    }
#line 10506 "MachineIndependent/glslang_tab.cpp"
    break;

  case 444: /* type_specifier_nonarray: USAMPLER2DMS  */
#line 3058 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, false, false, true);
    }
#line 10516 "MachineIndependent/glslang_tab.cpp"
    break;

  case 445: /* type_specifier_nonarray: SAMPLER2DMSARRAY  */
#line 3063 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, false, true);
    }
#line 10526 "MachineIndependent/glslang_tab.cpp"
    break;

  case 446: /* type_specifier_nonarray: F16SAMPLER2DMSARRAY  */
#line 3068 "MachineIndependent/glslang.y"
                          {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, false, true);
    }
#line 10537 "MachineIndependent/glslang_tab.cpp"
    break;

  case 447: /* type_specifier_nonarray: ISAMPLER2DMSARRAY  */
#line 3074 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true, false, true);
    }
#line 10547 "MachineIndependent/glslang_tab.cpp"
    break;

  case 448: /* type_specifier_nonarray: USAMPLER2DMSARRAY  */
#line 3079 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true, false, true);
    }
#line 10557 "MachineIndependent/glslang_tab.cpp"
    break;

  case 449: /* type_specifier_nonarray: TEXTURE1D  */
#line 3084 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D);
    }
#line 10567 "MachineIndependent/glslang_tab.cpp"
    break;

  case 450: /* type_specifier_nonarray: F16TEXTURE1D  */
#line 3089 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D);
    }
#line 10578 "MachineIndependent/glslang_tab.cpp"
    break;

  case 451: /* type_specifier_nonarray: F16TEXTURE2D  */
#line 3095 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D);
    }
#line 10589 "MachineIndependent/glslang_tab.cpp"
    break;

  case 452: /* type_specifier_nonarray: F16TEXTURE3D  */
#line 3101 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd3D);
    }
#line 10600 "MachineIndependent/glslang_tab.cpp"
    break;

  case 453: /* type_specifier_nonarray: F16TEXTURECUBE  */
#line 3107 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube);
    }
#line 10611 "MachineIndependent/glslang_tab.cpp"
    break;

  case 454: /* type_specifier_nonarray: TEXTURE1DARRAY  */
#line 3113 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D, true);
    }
#line 10621 "MachineIndependent/glslang_tab.cpp"
    break;

  case 455: /* type_specifier_nonarray: F16TEXTURE1DARRAY  */
#line 3118 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D, true);
    }
#line 10632 "MachineIndependent/glslang_tab.cpp"
    break;

  case 456: /* type_specifier_nonarray: F16TEXTURE2DARRAY  */
#line 3124 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true);
    }
#line 10643 "MachineIndependent/glslang_tab.cpp"
    break;

  case 457: /* type_specifier_nonarray: F16TEXTURECUBEARRAY  */
#line 3130 "MachineIndependent/glslang.y"
                          {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube, true);
    }
#line 10654 "MachineIndependent/glslang_tab.cpp"
    break;

  case 458: /* type_specifier_nonarray: ITEXTURE1D  */
#line 3136 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D);
    }
#line 10664 "MachineIndependent/glslang_tab.cpp"
    break;

  case 459: /* type_specifier_nonarray: ITEXTURE1DARRAY  */
#line 3141 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D, true);
    }
#line 10674 "MachineIndependent/glslang_tab.cpp"
    break;

  case 460: /* type_specifier_nonarray: UTEXTURE1D  */
#line 3146 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D);
    }
#line 10684 "MachineIndependent/glslang_tab.cpp"
    break;

  case 461: /* type_specifier_nonarray: UTEXTURE1DARRAY  */
#line 3151 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D, true);
    }
#line 10694 "MachineIndependent/glslang_tab.cpp"
    break;

  case 462: /* type_specifier_nonarray: TEXTURE2DRECT  */
#line 3156 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdRect);
    }
#line 10704 "MachineIndependent/glslang_tab.cpp"
    break;

  case 463: /* type_specifier_nonarray: F16TEXTURE2DRECT  */
#line 3161 "MachineIndependent/glslang.y"
                       {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdRect);
    }
#line 10715 "MachineIndependent/glslang_tab.cpp"
    break;

  case 464: /* type_specifier_nonarray: ITEXTURE2DRECT  */
#line 3167 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdRect);
    }
#line 10725 "MachineIndependent/glslang_tab.cpp"
    break;

  case 465: /* type_specifier_nonarray: UTEXTURE2DRECT  */
#line 3172 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdRect);
    }
#line 10735 "MachineIndependent/glslang_tab.cpp"
    break;

  case 466: /* type_specifier_nonarray: TEXTUREBUFFER  */
#line 3177 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdBuffer);
    }
#line 10745 "MachineIndependent/glslang_tab.cpp"
    break;

  case 467: /* type_specifier_nonarray: F16TEXTUREBUFFER  */
#line 3182 "MachineIndependent/glslang.y"
                       {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdBuffer);
    }
#line 10756 "MachineIndependent/glslang_tab.cpp"
    break;

  case 468: /* type_specifier_nonarray: ITEXTUREBUFFER  */
#line 3188 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdBuffer);
    }
#line 10766 "MachineIndependent/glslang_tab.cpp"
    break;

  case 469: /* type_specifier_nonarray: UTEXTUREBUFFER  */
#line 3193 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdBuffer);
    }
#line 10776 "MachineIndependent/glslang_tab.cpp"
    break;

  case 470: /* type_specifier_nonarray: TEXTURE2DMS  */
#line 3198 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, false, false, true);
    }
#line 10786 "MachineIndependent/glslang_tab.cpp"
    break;

  case 471: /* type_specifier_nonarray: F16TEXTURE2DMS  */
#line 3203 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, false, false, true);
    }
#line 10797 "MachineIndependent/glslang_tab.cpp"
    break;

  case 472: /* type_specifier_nonarray: ITEXTURE2DMS  */
#line 3209 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, false, false, true);
    }
#line 10807 "MachineIndependent/glslang_tab.cpp"
    break;

  case 473: /* type_specifier_nonarray: UTEXTURE2DMS  */
#line 3214 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, false, false, true);
    }
#line 10817 "MachineIndependent/glslang_tab.cpp"
    break;

  case 474: /* type_specifier_nonarray: TEXTURE2DMSARRAY  */
#line 3219 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true, false, true);
    }
#line 10827 "MachineIndependent/glslang_tab.cpp"
    break;

  case 475: /* type_specifier_nonarray: F16TEXTURE2DMSARRAY  */
#line 3224 "MachineIndependent/glslang.y"
                          {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true, false, true);
    }
#line 10838 "MachineIndependent/glslang_tab.cpp"
    break;

  case 476: /* type_specifier_nonarray: ITEXTURE2DMSARRAY  */
#line 3230 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true, false, true);
    }
#line 10848 "MachineIndependent/glslang_tab.cpp"
    break;

  case 477: /* type_specifier_nonarray: UTEXTURE2DMSARRAY  */
#line 3235 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true, false, true);
    }
#line 10858 "MachineIndependent/glslang_tab.cpp"
    break;

  case 478: /* type_specifier_nonarray: IMAGE1D  */
#line 3240 "MachineIndependent/glslang.y"
              {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D);
    }
#line 10868 "MachineIndependent/glslang_tab.cpp"
    break;

  case 479: /* type_specifier_nonarray: F16IMAGE1D  */
#line 3245 "MachineIndependent/glslang.y"
                 {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D);
    }
#line 10879 "MachineIndependent/glslang_tab.cpp"
    break;

  case 480: /* type_specifier_nonarray: IIMAGE1D  */
#line 3251 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D);
    }
#line 10889 "MachineIndependent/glslang_tab.cpp"
    break;

  case 481: /* type_specifier_nonarray: UIMAGE1D  */
#line 3256 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D);
    }
#line 10899 "MachineIndependent/glslang_tab.cpp"
    break;

  case 482: /* type_specifier_nonarray: IMAGE2D  */
#line 3261 "MachineIndependent/glslang.y"
              {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D);
    }
#line 10909 "MachineIndependent/glslang_tab.cpp"
    break;

  case 483: /* type_specifier_nonarray: F16IMAGE2D  */
#line 3266 "MachineIndependent/glslang.y"
                 {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D);
    }
#line 10920 "MachineIndependent/glslang_tab.cpp"
    break;

  case 484: /* type_specifier_nonarray: IIMAGE2D  */
#line 3272 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D);
    }
#line 10930 "MachineIndependent/glslang_tab.cpp"
    break;

  case 485: /* type_specifier_nonarray: UIMAGE2D  */
#line 3277 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D);
    }
#line 10940 "MachineIndependent/glslang_tab.cpp"
    break;

  case 486: /* type_specifier_nonarray: IMAGE3D  */
#line 3282 "MachineIndependent/glslang.y"
              {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd3D);
    }
#line 10950 "MachineIndependent/glslang_tab.cpp"
    break;

  case 487: /* type_specifier_nonarray: F16IMAGE3D  */
#line 3287 "MachineIndependent/glslang.y"
                 {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd3D);
    }
#line 10961 "MachineIndependent/glslang_tab.cpp"
    break;

  case 488: /* type_specifier_nonarray: IIMAGE3D  */
#line 3293 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd3D);
    }
#line 10971 "MachineIndependent/glslang_tab.cpp"
    break;

  case 489: /* type_specifier_nonarray: UIMAGE3D  */
#line 3298 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd3D);
    }
#line 10981 "MachineIndependent/glslang_tab.cpp"
    break;

  case 490: /* type_specifier_nonarray: IMAGE2DRECT  */
#line 3303 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdRect);
    }
#line 10991 "MachineIndependent/glslang_tab.cpp"
    break;

  case 491: /* type_specifier_nonarray: F16IMAGE2DRECT  */
#line 3308 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdRect);
    }
#line 11002 "MachineIndependent/glslang_tab.cpp"
    break;

  case 492: /* type_specifier_nonarray: IIMAGE2DRECT  */
#line 3314 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdRect);
    }
#line 11012 "MachineIndependent/glslang_tab.cpp"
    break;

  case 493: /* type_specifier_nonarray: UIMAGE2DRECT  */
#line 3319 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdRect);
    }
#line 11022 "MachineIndependent/glslang_tab.cpp"
    break;

  case 494: /* type_specifier_nonarray: IMAGECUBE  */
#line 3324 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube);
    }
#line 11032 "MachineIndependent/glslang_tab.cpp"
    break;

  case 495: /* type_specifier_nonarray: F16IMAGECUBE  */
#line 3329 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube);
    }
#line 11043 "MachineIndependent/glslang_tab.cpp"
    break;

  case 496: /* type_specifier_nonarray: IIMAGECUBE  */
#line 3335 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube);
    }
#line 11053 "MachineIndependent/glslang_tab.cpp"
    break;

  case 497: /* type_specifier_nonarray: UIMAGECUBE  */
#line 3340 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube);
    }
#line 11063 "MachineIndependent/glslang_tab.cpp"
    break;

  case 498: /* type_specifier_nonarray: IMAGEBUFFER  */
#line 3345 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdBuffer);
    }
#line 11073 "MachineIndependent/glslang_tab.cpp"
    break;

  case 499: /* type_specifier_nonarray: F16IMAGEBUFFER  */
#line 3350 "MachineIndependent/glslang.y"
                     {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdBuffer);
    }
#line 11084 "MachineIndependent/glslang_tab.cpp"
    break;

  case 500: /* type_specifier_nonarray: IIMAGEBUFFER  */
#line 3356 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdBuffer);
    }
#line 11094 "MachineIndependent/glslang_tab.cpp"
    break;

  case 501: /* type_specifier_nonarray: UIMAGEBUFFER  */
#line 3361 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdBuffer);
    }
#line 11104 "MachineIndependent/glslang_tab.cpp"
    break;

  case 502: /* type_specifier_nonarray: IMAGE1DARRAY  */
#line 3366 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D, true);
    }
#line 11114 "MachineIndependent/glslang_tab.cpp"
    break;

  case 503: /* type_specifier_nonarray: F16IMAGE1DARRAY  */
#line 3371 "MachineIndependent/glslang.y"
                      {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D, true);
    }
#line 11125 "MachineIndependent/glslang_tab.cpp"
    break;

  case 504: /* type_specifier_nonarray: IIMAGE1DARRAY  */
#line 3377 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D, true);
    }
#line 11135 "MachineIndependent/glslang_tab.cpp"
    break;

  case 505: /* type_specifier_nonarray: UIMAGE1DARRAY  */
#line 3382 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D, true);
    }
#line 11145 "MachineIndependent/glslang_tab.cpp"
    break;

  case 506: /* type_specifier_nonarray: IMAGE2DARRAY  */
#line 3387 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true);
    }
#line 11155 "MachineIndependent/glslang_tab.cpp"
    break;

  case 507: /* type_specifier_nonarray: F16IMAGE2DARRAY  */
#line 3392 "MachineIndependent/glslang.y"
                      {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true);
    }
#line 11166 "MachineIndependent/glslang_tab.cpp"
    break;

  case 508: /* type_specifier_nonarray: IIMAGE2DARRAY  */
#line 3398 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true);
    }
#line 11176 "MachineIndependent/glslang_tab.cpp"
    break;

  case 509: /* type_specifier_nonarray: UIMAGE2DARRAY  */
#line 3403 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true);
    }
#line 11186 "MachineIndependent/glslang_tab.cpp"
    break;

  case 510: /* type_specifier_nonarray: IMAGECUBEARRAY  */
#line 3408 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube, true);
    }
#line 11196 "MachineIndependent/glslang_tab.cpp"
    break;

  case 511: /* type_specifier_nonarray: F16IMAGECUBEARRAY  */
#line 3413 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube, true);
    }
#line 11207 "MachineIndependent/glslang_tab.cpp"
    break;

  case 512: /* type_specifier_nonarray: IIMAGECUBEARRAY  */
#line 3419 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube, true);
    }
#line 11217 "MachineIndependent/glslang_tab.cpp"
    break;

  case 513: /* type_specifier_nonarray: UIMAGECUBEARRAY  */
#line 3424 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube, true);
    }
#line 11227 "MachineIndependent/glslang_tab.cpp"
    break;

  case 514: /* type_specifier_nonarray: IMAGE2DMS  */
#line 3429 "MachineIndependent/glslang.y"
                {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, false, false, true);
    }
#line 11237 "MachineIndependent/glslang_tab.cpp"
    break;

  case 515: /* type_specifier_nonarray: F16IMAGE2DMS  */
#line 3434 "MachineIndependent/glslang.y"
                   {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, false, false, true);
    }
#line 11248 "MachineIndependent/glslang_tab.cpp"
    break;

  case 516: /* type_specifier_nonarray: IIMAGE2DMS  */
#line 3440 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, false, false, true);
    }
#line 11258 "MachineIndependent/glslang_tab.cpp"
    break;

  case 517: /* type_specifier_nonarray: UIMAGE2DMS  */
#line 3445 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, false, false, true);
    }
#line 11268 "MachineIndependent/glslang_tab.cpp"
    break;

  case 518: /* type_specifier_nonarray: IMAGE2DMSARRAY  */
#line 3450 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true, false, true);
    }
#line 11278 "MachineIndependent/glslang_tab.cpp"
    break;

  case 519: /* type_specifier_nonarray: F16IMAGE2DMSARRAY  */
#line 3455 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true, false, true);
    }
#line 11289 "MachineIndependent/glslang_tab.cpp"
    break;

  case 520: /* type_specifier_nonarray: IIMAGE2DMSARRAY  */
#line 3461 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true, false, true);
    }
#line 11299 "MachineIndependent/glslang_tab.cpp"
    break;

  case 521: /* type_specifier_nonarray: UIMAGE2DMSARRAY  */
#line 3466 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true, false, true);
    }
#line 11309 "MachineIndependent/glslang_tab.cpp"
    break;

  case 522: /* type_specifier_nonarray: I64IMAGE1D  */
#line 3471 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd1D);
    }
#line 11319 "MachineIndependent/glslang_tab.cpp"
    break;

  case 523: /* type_specifier_nonarray: U64IMAGE1D  */
#line 3476 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd1D);
    }
#line 11329 "MachineIndependent/glslang_tab.cpp"
    break;

  case 524: /* type_specifier_nonarray: I64IMAGE2D  */
#line 3481 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd2D);
    }
#line 11339 "MachineIndependent/glslang_tab.cpp"
    break;

  case 525: /* type_specifier_nonarray: U64IMAGE2D  */
#line 3486 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd2D);
    }
#line 11349 "MachineIndependent/glslang_tab.cpp"
    break;

  case 526: /* type_specifier_nonarray: I64IMAGE3D  */
#line 3491 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd3D);
    }
#line 11359 "MachineIndependent/glslang_tab.cpp"
    break;

  case 527: /* type_specifier_nonarray: U64IMAGE3D  */
#line 3496 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd3D);
    }
#line 11369 "MachineIndependent/glslang_tab.cpp"
    break;

  case 528: /* type_specifier_nonarray: I64IMAGE2DRECT  */
#line 3501 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, EsdRect);
    }
#line 11379 "MachineIndependent/glslang_tab.cpp"
    break;

  case 529: /* type_specifier_nonarray: U64IMAGE2DRECT  */
#line 3506 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, EsdRect);
    }
#line 11389 "MachineIndependent/glslang_tab.cpp"
    break;

  case 530: /* type_specifier_nonarray: I64IMAGECUBE  */
#line 3511 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, EsdCube);
    }
#line 11399 "MachineIndependent/glslang_tab.cpp"
    break;

  case 531: /* type_specifier_nonarray: U64IMAGECUBE  */
#line 3516 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, EsdCube);
    }
#line 11409 "MachineIndependent/glslang_tab.cpp"
    break;

  case 532: /* type_specifier_nonarray: I64IMAGEBUFFER  */
#line 3521 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, EsdBuffer);
    }
#line 11419 "MachineIndependent/glslang_tab.cpp"
    break;

  case 533: /* type_specifier_nonarray: U64IMAGEBUFFER  */
#line 3526 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, EsdBuffer);
    }
#line 11429 "MachineIndependent/glslang_tab.cpp"
    break;

  case 534: /* type_specifier_nonarray: I64IMAGE1DARRAY  */
#line 3531 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd1D, true);
    }
#line 11439 "MachineIndependent/glslang_tab.cpp"
    break;

  case 535: /* type_specifier_nonarray: U64IMAGE1DARRAY  */
#line 3536 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd1D, true);
    }
#line 11449 "MachineIndependent/glslang_tab.cpp"
    break;

  case 536: /* type_specifier_nonarray: I64IMAGE2DARRAY  */
#line 3541 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd2D, true);
    }
#line 11459 "MachineIndependent/glslang_tab.cpp"
    break;

  case 537: /* type_specifier_nonarray: U64IMAGE2DARRAY  */
#line 3546 "MachineIndependent/glslang.y"
                      {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd2D, true);
    }
#line 11469 "MachineIndependent/glslang_tab.cpp"
    break;

  case 538: /* type_specifier_nonarray: I64IMAGECUBEARRAY  */
#line 3551 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, EsdCube, true);
    }
#line 11479 "MachineIndependent/glslang_tab.cpp"
    break;

  case 539: /* type_specifier_nonarray: U64IMAGECUBEARRAY  */
#line 3556 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, EsdCube, true);
    }
#line 11489 "MachineIndependent/glslang_tab.cpp"
    break;

  case 540: /* type_specifier_nonarray: I64IMAGE2DMS  */
#line 3561 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd2D, false, false, true);
    }
#line 11499 "MachineIndependent/glslang_tab.cpp"
    break;

  case 541: /* type_specifier_nonarray: U64IMAGE2DMS  */
#line 3566 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd2D, false, false, true);
    }
#line 11509 "MachineIndependent/glslang_tab.cpp"
    break;

  case 542: /* type_specifier_nonarray: I64IMAGE2DMSARRAY  */
#line 3571 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt64, Esd2D, true, false, true);
    }
#line 11519 "MachineIndependent/glslang_tab.cpp"
    break;

  case 543: /* type_specifier_nonarray: U64IMAGE2DMSARRAY  */
#line 3576 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint64, Esd2D, true, false, true);
    }
#line 11529 "MachineIndependent/glslang_tab.cpp"
    break;

  case 544: /* type_specifier_nonarray: SAMPLEREXTERNALOES  */
#line 3581 "MachineIndependent/glslang.y"
                         {  // GL_OES_EGL_image_external
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.external = true;
    }
#line 11540 "MachineIndependent/glslang_tab.cpp"
    break;

  case 545: /* type_specifier_nonarray: SAMPLEREXTERNAL2DY2YEXT  */
#line 3587 "MachineIndependent/glslang.y"
                              { // GL_EXT_YUV_target
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.yuv = true;
    }
#line 11551 "MachineIndependent/glslang_tab.cpp"
    break;

  case 546: /* type_specifier_nonarray: ATTACHMENTEXT  */
#line 3593 "MachineIndependent/glslang.y"
                    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "attachmentEXT input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setAttachmentEXT(EbtFloat);
    }
#line 11562 "MachineIndependent/glslang_tab.cpp"
    break;

  case 547: /* type_specifier_nonarray: IATTACHMENTEXT  */
#line 3599 "MachineIndependent/glslang.y"
                     {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "attachmentEXT input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setAttachmentEXT(EbtInt);
    }
#line 11573 "MachineIndependent/glslang_tab.cpp"
    break;

  case 548: /* type_specifier_nonarray: UATTACHMENTEXT  */
#line 3605 "MachineIndependent/glslang.y"
                     {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "attachmentEXT input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setAttachmentEXT(EbtUint);
    }
#line 11584 "MachineIndependent/glslang_tab.cpp"
    break;

  case 549: /* type_specifier_nonarray: SUBPASSINPUT  */
#line 3611 "MachineIndependent/glslang.y"
                   {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat);
    }
#line 11595 "MachineIndependent/glslang_tab.cpp"
    break;

  case 550: /* type_specifier_nonarray: SUBPASSINPUTMS  */
#line 3617 "MachineIndependent/glslang.y"
                     {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat, true);
    }
#line 11606 "MachineIndependent/glslang_tab.cpp"
    break;

  case 551: /* type_specifier_nonarray: F16SUBPASSINPUT  */
#line 3623 "MachineIndependent/glslang.y"
                      {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16);
    }
#line 11618 "MachineIndependent/glslang_tab.cpp"
    break;

  case 552: /* type_specifier_nonarray: F16SUBPASSINPUTMS  */
#line 3630 "MachineIndependent/glslang.y"
                        {
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16, true);
    }
#line 11630 "MachineIndependent/glslang_tab.cpp"
    break;

  case 553: /* type_specifier_nonarray: ISUBPASSINPUT  */
#line 3637 "MachineIndependent/glslang.y"
                    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt);
    }
#line 11641 "MachineIndependent/glslang_tab.cpp"
    break;

  case 554: /* type_specifier_nonarray: ISUBPASSINPUTMS  */
#line 3643 "MachineIndependent/glslang.y"
                      {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt, true);
    }
#line 11652 "MachineIndependent/glslang_tab.cpp"
    break;

  case 555: /* type_specifier_nonarray: USUBPASSINPUT  */
#line 3649 "MachineIndependent/glslang.y"
                    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint);
    }
#line 11663 "MachineIndependent/glslang_tab.cpp"
    break;

  case 556: /* type_specifier_nonarray: USUBPASSINPUTMS  */
#line 3655 "MachineIndependent/glslang.y"
                      {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint, true);
    }
#line 11674 "MachineIndependent/glslang_tab.cpp"
    break;

  case 557: /* type_specifier_nonarray: FCOOPMATNV  */
#line 3661 "MachineIndependent/glslang.y"
                 {
        parseContext.fcoopmatCheckNV((yyvsp[0].lex).loc, "fcoopmatNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).coopmatNV = true;
        (yyval.interm.type).coopmatKHR = false;
    }
#line 11686 "MachineIndependent/glslang_tab.cpp"
    break;

  case 558: /* type_specifier_nonarray: ICOOPMATNV  */
#line 3668 "MachineIndependent/glslang.y"
                 {
        parseContext.intcoopmatCheckNV((yyvsp[0].lex).loc, "icoopmatNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).coopmatNV = true;
        (yyval.interm.type).coopmatKHR = false;
    }
#line 11698 "MachineIndependent/glslang_tab.cpp"
    break;

  case 559: /* type_specifier_nonarray: UCOOPMATNV  */
#line 3675 "MachineIndependent/glslang.y"
                 {
        parseContext.intcoopmatCheckNV((yyvsp[0].lex).loc, "ucoopmatNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).coopmatNV = true;
        (yyval.interm.type).coopmatKHR = false;
    }
#line 11710 "MachineIndependent/glslang_tab.cpp"
    break;

  case 560: /* type_specifier_nonarray: COOPMAT  */
#line 3682 "MachineIndependent/glslang.y"
              {
        parseContext.coopmatCheck((yyvsp[0].lex).loc, "coopmat", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtCoopmat;
        (yyval.interm.type).coopmatNV = false;
        (yyval.interm.type).coopmatKHR = true;
    }
#line 11722 "MachineIndependent/glslang_tab.cpp"
    break;

  case 561: /* type_specifier_nonarray: TENSORLAYOUTNV  */
#line 3689 "MachineIndependent/glslang.y"
                     {
        parseContext.tensorLayoutViewCheck((yyvsp[0].lex).loc, "tensorLayoutNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtTensorLayoutNV;
    }
#line 11732 "MachineIndependent/glslang_tab.cpp"
    break;

  case 562: /* type_specifier_nonarray: TENSORVIEWNV  */
#line 3694 "MachineIndependent/glslang.y"
                   {
        parseContext.tensorLayoutViewCheck((yyvsp[0].lex).loc, "tensorViewNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtTensorViewNV;
    }
#line 11742 "MachineIndependent/glslang_tab.cpp"
    break;

  case 563: /* type_specifier_nonarray: FUNCTION  */
#line 3699 "MachineIndependent/glslang.y"
               {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).basicType = EbtFunction;
    }
#line 11751 "MachineIndependent/glslang_tab.cpp"
    break;

  case 564: /* type_specifier_nonarray: COOPVECNV  */
#line 3703 "MachineIndependent/glslang.y"
                {
        parseContext.coopvecCheck((yyvsp[0].lex).loc, "coopvecNV", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtCoopvecNV;
        (yyval.interm.type).coopvecNV = true;
    }
#line 11762 "MachineIndependent/glslang_tab.cpp"
    break;

  case 565: /* type_specifier_nonarray: TENSORARM  */
#line 3709 "MachineIndependent/glslang.y"
                {
        parseContext.tensorCheckARM((yyvsp[0].lex).loc, "tensorARM", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).tensorRankARM = 1; // placeholder value
        (yyval.interm.type).basicType = EbtTensorARM;
    }
#line 11773 "MachineIndependent/glslang_tab.cpp"
    break;

  case 566: /* type_specifier_nonarray: VECTOR  */
#line 3715 "MachineIndependent/glslang.y"
             {
        parseContext.longVectorCheck((yyvsp[0].lex).loc, "vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtLongVector;
        (yyval.interm.type).longVector = true;
    }
#line 11784 "MachineIndependent/glslang_tab.cpp"
    break;

  case 567: /* type_specifier_nonarray: spirv_type_specifier  */
#line 3721 "MachineIndependent/glslang.y"
                           {
        parseContext.requireExtensions((yyvsp[0].interm.type).loc, 1, &E_GL_EXT_spirv_intrinsics, "SPIR-V type specifier");
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 11793 "MachineIndependent/glslang_tab.cpp"
    break;

  case 568: /* type_specifier_nonarray: HITOBJECTNV  */
#line 3725 "MachineIndependent/glslang.y"
                  {
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtHitObjectNV;
    }
#line 11802 "MachineIndependent/glslang_tab.cpp"
    break;

  case 569: /* type_specifier_nonarray: HITOBJECTEXT  */
#line 3729 "MachineIndependent/glslang.y"
                   {
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtHitObjectEXT;
    }
#line 11811 "MachineIndependent/glslang_tab.cpp"
    break;

  case 570: /* type_specifier_nonarray: struct_specifier  */
#line 3733 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.type) = (yyvsp[0].interm.type);
        (yyval.interm.type).qualifier.storage = parseContext.symbolTable.atGlobalLevel() ? EvqGlobal : EvqTemporary;
        parseContext.structTypeCheck((yyval.interm.type).loc, (yyval.interm.type));
    }
#line 11821 "MachineIndependent/glslang_tab.cpp"
    break;

  case 571: /* type_specifier_nonarray: TYPE_NAME  */
#line 3738 "MachineIndependent/glslang.y"
                {
        //
        // This is for user defined type names.  The lexical phase looked up the
        // type.
        //
        if (const TVariable* variable = ((yyvsp[0].lex).symbol)->getAsVariable()) {
            const TType& structure = variable->getType();
            (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
            (yyval.interm.type).basicType = EbtStruct;
            (yyval.interm.type).userDef = &structure;
        } else
            parseContext.error((yyvsp[0].lex).loc, "expected type name", (yyvsp[0].lex).string->c_str(), "");
    }
#line 11839 "MachineIndependent/glslang_tab.cpp"
    break;

  case 572: /* precision_qualifier: HIGH_PRECISION  */
#line 3754 "MachineIndependent/glslang.y"
                     {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "highp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqHigh);
    }
#line 11849 "MachineIndependent/glslang_tab.cpp"
    break;

  case 573: /* precision_qualifier: MEDIUM_PRECISION  */
#line 3759 "MachineIndependent/glslang.y"
                       {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "mediump precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqMedium);
    }
#line 11859 "MachineIndependent/glslang_tab.cpp"
    break;

  case 574: /* precision_qualifier: LOW_PRECISION  */
#line 3764 "MachineIndependent/glslang.y"
                    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "lowp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqLow);
    }
#line 11869 "MachineIndependent/glslang_tab.cpp"
    break;

  case 575: /* $@3: %empty  */
#line 3772 "MachineIndependent/glslang.y"
                                   { parseContext.nestedStructCheck((yyvsp[-2].lex).loc); }
#line 11875 "MachineIndependent/glslang_tab.cpp"
    break;

  case 576: /* struct_specifier: STRUCT IDENTIFIER LEFT_BRACE $@3 struct_declaration_list RIGHT_BRACE  */
#line 3772 "MachineIndependent/glslang.y"
                                                                                                                   {
        TType* structure = new TType((yyvsp[-1].interm.typeList), *(yyvsp[-4].lex).string);
        parseContext.structArrayCheck((yyvsp[-4].lex).loc, *structure);

        TVariable* userTypeDef = new TVariable((yyvsp[-4].lex).string, *structure, true);
        if (! parseContext.symbolTable.insert(*userTypeDef))
            parseContext.error((yyvsp[-4].lex).loc, "redefinition", (yyvsp[-4].lex).string->c_str(), "struct");
        else if (parseContext.spvVersion.vulkanRelaxed
                 && structure->containsOpaque())
            parseContext.relaxedSymbols.push_back(structure->getTypeName());

        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
#line 11896 "MachineIndependent/glslang_tab.cpp"
    break;

  case 577: /* $@4: %empty  */
#line 3788 "MachineIndependent/glslang.y"
                        { parseContext.nestedStructCheck((yyvsp[-1].lex).loc); }
#line 11902 "MachineIndependent/glslang_tab.cpp"
    break;

  case 578: /* struct_specifier: STRUCT LEFT_BRACE $@4 struct_declaration_list RIGHT_BRACE  */
#line 3788 "MachineIndependent/glslang.y"
                                                                                                        {
        TType* structure = new TType((yyvsp[-1].interm.typeList), TString(""));
        (yyval.interm.type).init((yyvsp[-4].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
#line 11914 "MachineIndependent/glslang_tab.cpp"
    break;

  case 579: /* struct_declaration_list: struct_declaration_without_heap  */
#line 3798 "MachineIndependent/glslang.y"
                                      {
        (yyval.interm.typeList) = (yyvsp[0].interm.typeList);
    }
#line 11922 "MachineIndependent/glslang_tab.cpp"
    break;

  case 580: /* struct_declaration_list: struct_declaration_with_heap  */
#line 3801 "MachineIndependent/glslang.y"
                                   {
        (yyval.interm.typeList) = (yyvsp[0].interm.typeList);
    }
#line 11930 "MachineIndependent/glslang_tab.cpp"
    break;

  case 581: /* struct_declaration_list: struct_declaration_with_heap struct_declaration_without_heap  */
#line 3804 "MachineIndependent/glslang.y"
                                                                   {
        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);
        for (unsigned int i = 0; i < (yyvsp[0].interm.typeList)->size(); ++i) {
            for (unsigned int j = 0; j < (yyval.interm.typeList)->size(); ++j) {
                if ((*(yyval.interm.typeList))[j].type->getFieldName() == (*(yyvsp[0].interm.typeList))[i].type->getFieldName())
                    parseContext.error((*(yyvsp[0].interm.typeList))[i].loc, "duplicate member name:", "", (*(yyvsp[0].interm.typeList))[i].type->getFieldName().c_str());
            }
            (yyval.interm.typeList)->push_back((*(yyvsp[0].interm.typeList))[i]);
        }
    }
#line 11945 "MachineIndependent/glslang_tab.cpp"
    break;

  case 582: /* struct_declaration_list: struct_declaration_without_heap struct_declaration_with_heap  */
#line 3814 "MachineIndependent/glslang.y"
                                                                   {
        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);
        for (unsigned int i = 0; i < (yyvsp[0].interm.typeList)->size(); ++i) {
            for (unsigned int j = 0; j < (yyval.interm.typeList)->size(); ++j) {
                if ((*(yyval.interm.typeList))[j].type->getFieldName() == (*(yyvsp[0].interm.typeList))[i].type->getFieldName())
                    parseContext.error((*(yyvsp[0].interm.typeList))[i].loc, "duplicate member name:", "", (*(yyvsp[0].interm.typeList))[i].type->getFieldName().c_str());
            }
            (yyval.interm.typeList)->push_back((*(yyvsp[0].interm.typeList))[i]);
        }
    }
#line 11960 "MachineIndependent/glslang_tab.cpp"
    break;

  case 583: /* struct_declaration_with_heap: block_heap_inner_structure struct_declarator_list SEMICOLON  */
#line 3827 "MachineIndependent/glslang.y"
                                                                  {
        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);
        parseContext.voidErrorCheck((yyvsp[-2].interm.type).loc, (*(yyvsp[-1].interm.typeList))[0].type->getFieldName(), (yyvsp[-2].interm.type).basicType);
        parseContext.precisionQualifierCheck((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).basicType, (yyvsp[-2].interm.type).qualifier, (yyvsp[-2].interm.type).hasTypeParameter());

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            TType type((yyvsp[-2].interm.type));
            type.setFieldName((*(yyval.interm.typeList))[i].type->getFieldName());
            type.transferArraySizes((*(yyval.interm.typeList))[i].type->getArraySizes());
            type.copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);
            parseContext.arrayOfArrayVersionCheck((*(yyval.interm.typeList))[i].loc, type.getArraySizes());
            (*(yyval.interm.typeList))[i].type->shallowCopy(type);
        }
    }
#line 11979 "MachineIndependent/glslang_tab.cpp"
    break;

  case 584: /* $@5: %empty  */
#line 3844 "MachineIndependent/glslang.y"
                                { parseContext.nestedBlockCheck((yyvsp[-1].interm.type).loc, true); }
#line 11985 "MachineIndependent/glslang_tab.cpp"
    break;

  case 585: /* block_heap_inner_structure: type_qualifier LEFT_BRACE $@5 struct_declaration_without_heap RIGHT_BRACE  */
#line 3844 "MachineIndependent/glslang.y"
                                                                                                                             {
        --parseContext.blockNestingLevel;
        parseContext.globalQualifierFixCheck((yyvsp[-4].interm.type).loc, (yyvsp[-4].interm.type).qualifier);
        parseContext.checkNoShaderLayouts((yyvsp[-4].interm.type).loc, (yyvsp[-4].interm.type).shaderQualifiers);
        (yyval.interm.type).init((yyvsp[-4].interm.type).loc);
        TType* innerStructure = new TType((yyvsp[-1].interm.typeList), TString(""));
        (yyval.interm.type).basicType = EbtBlock;
        (yyval.interm.type).userDef = innerStructure;
        (yyval.interm.type).qualifier = (yyvsp[-4].interm.type).qualifier;
        (yyval.interm.type).qualifier.layoutDescriptorHeap = true;
        (yyval.interm.type).qualifier.layoutDescriptorInnerBlock = true;
    }
#line 12002 "MachineIndependent/glslang_tab.cpp"
    break;

  case 586: /* struct_declaration_without_heap: struct_declaration  */
#line 3859 "MachineIndependent/glslang.y"
                         {
        (yyval.interm.typeList) = (yyvsp[0].interm.typeList);
    }
#line 12010 "MachineIndependent/glslang_tab.cpp"
    break;

  case 587: /* struct_declaration_without_heap: struct_declaration_without_heap struct_declaration  */
#line 3862 "MachineIndependent/glslang.y"
                                                         {
        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);
        for (unsigned int i = 0; i < (yyvsp[0].interm.typeList)->size(); ++i) {
            for (unsigned int j = 0; j < (yyval.interm.typeList)->size(); ++j) {
                if ((*(yyval.interm.typeList))[j].type->getFieldName() == (*(yyvsp[0].interm.typeList))[i].type->getFieldName())
                    parseContext.error((*(yyvsp[0].interm.typeList))[i].loc, "duplicate member name:", "", (*(yyvsp[0].interm.typeList))[i].type->getFieldName().c_str());
            }
            (yyval.interm.typeList)->push_back((*(yyvsp[0].interm.typeList))[i]);
        }
    }
#line 12025 "MachineIndependent/glslang_tab.cpp"
    break;

  case 588: /* struct_declaration: type_specifier struct_declarator_list SEMICOLON  */
#line 3875 "MachineIndependent/glslang.y"
                                                      {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.isEsProfile())
                parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);

        parseContext.voidErrorCheck((yyvsp[-2].interm.type).loc, (*(yyvsp[-1].interm.typeList))[0].type->getFieldName(), (yyvsp[-2].interm.type).basicType);
        parseContext.precisionQualifierCheck((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).basicType, (yyvsp[-2].interm.type).qualifier, (yyvsp[-2].interm.type).hasTypeParameter());

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            TType type((yyvsp[-2].interm.type));
            type.setFieldName((*(yyval.interm.typeList))[i].type->getFieldName());
            type.transferArraySizes((*(yyval.interm.typeList))[i].type->getArraySizes());
            type.copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);
            parseContext.arrayOfArrayVersionCheck((*(yyval.interm.typeList))[i].loc, type.getArraySizes());
            (*(yyval.interm.typeList))[i].type->shallowCopy(type);
        }
    }
#line 12052 "MachineIndependent/glslang_tab.cpp"
    break;

  case 589: /* struct_declaration: type_qualifier type_specifier struct_declarator_list SEMICOLON  */
#line 3897 "MachineIndependent/glslang.y"
                                                                     {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.isEsProfile())
                parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);

        parseContext.memberQualifierCheck((yyvsp[-3].interm.type));
        parseContext.voidErrorCheck((yyvsp[-2].interm.type).loc, (*(yyvsp[-1].interm.typeList))[0].type->getFieldName(), (yyvsp[-2].interm.type).basicType);
        parseContext.mergeQualifiers((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).qualifier, (yyvsp[-3].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).basicType, (yyvsp[-2].interm.type).qualifier, (yyvsp[-2].interm.type).hasTypeParameter());

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            TType type((yyvsp[-2].interm.type));
            type.setFieldName((*(yyval.interm.typeList))[i].type->getFieldName());
            type.transferArraySizes((*(yyval.interm.typeList))[i].type->getArraySizes());
            type.copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);
            parseContext.arrayOfArrayVersionCheck((*(yyval.interm.typeList))[i].loc, type.getArraySizes());
            (*(yyval.interm.typeList))[i].type->shallowCopy(type);
        }
    }
#line 12081 "MachineIndependent/glslang_tab.cpp"
    break;

  case 590: /* struct_declarator_list: struct_declarator  */
#line 3924 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.typeList) = new TTypeList;
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 12090 "MachineIndependent/glslang_tab.cpp"
    break;

  case 591: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 3928 "MachineIndependent/glslang.y"
                                                     {
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 12098 "MachineIndependent/glslang_tab.cpp"
    break;

  case 592: /* struct_declarator: IDENTIFIER  */
#line 3934 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[0].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[0].lex).string);
    }
#line 12108 "MachineIndependent/glslang_tab.cpp"
    break;

  case 593: /* struct_declarator: IDENTIFIER array_specifier  */
#line 3939 "MachineIndependent/glslang.y"
                                 {
        parseContext.arrayOfArrayVersionCheck((yyvsp[-1].lex).loc, (yyvsp[0].interm).arraySizes);

        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[-1].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[-1].lex).string);
        (yyval.interm.typeLine).type->transferArraySizes((yyvsp[0].interm).arraySizes);
    }
#line 12121 "MachineIndependent/glslang_tab.cpp"
    break;

  case 594: /* initializer: assignment_expression  */
#line 3950 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 12129 "MachineIndependent/glslang_tab.cpp"
    break;

  case 595: /* initializer: LEFT_BRACE initializer_list RIGHT_BRACE  */
#line 3953 "MachineIndependent/glslang.y"
                                              {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-2].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-2].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
    }
#line 12140 "MachineIndependent/glslang_tab.cpp"
    break;

  case 596: /* initializer: LEFT_BRACE initializer_list COMMA RIGHT_BRACE  */
#line 3959 "MachineIndependent/glslang.y"
                                                    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-3].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-3].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 12151 "MachineIndependent/glslang_tab.cpp"
    break;

  case 597: /* initializer: LEFT_BRACE RIGHT_BRACE  */
#line 3965 "MachineIndependent/glslang.y"
                             {
        const char* initFeature = "empty { } initializer";
        parseContext.profileRequires((yyvsp[-1].lex).loc, EEsProfile, 0, E_GL_EXT_null_initializer, initFeature);
        parseContext.profileRequires((yyvsp[-1].lex).loc, ~EEsProfile, 0, E_GL_EXT_null_initializer, initFeature);
        (yyval.interm.intermTypedNode) = parseContext.intermediate.makeAggregate((yyvsp[-1].lex).loc);
    }
#line 12162 "MachineIndependent/glslang_tab.cpp"
    break;

  case 598: /* initializer_list: initializer  */
#line 3974 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate(0, (yyvsp[0].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode)->getLoc());
    }
#line 12170 "MachineIndependent/glslang_tab.cpp"
    break;

  case 599: /* initializer_list: initializer_list COMMA initializer  */
#line 3977 "MachineIndependent/glslang.y"
                                         {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
    }
#line 12178 "MachineIndependent/glslang_tab.cpp"
    break;

  case 600: /* declaration_statement: declaration  */
#line 3983 "MachineIndependent/glslang.y"
                  { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12184 "MachineIndependent/glslang_tab.cpp"
    break;

  case 601: /* statement: compound_statement  */
#line 3987 "MachineIndependent/glslang.y"
                          { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12190 "MachineIndependent/glslang_tab.cpp"
    break;

  case 602: /* statement: simple_statement  */
#line 3988 "MachineIndependent/glslang.y"
                          { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12196 "MachineIndependent/glslang_tab.cpp"
    break;

  case 603: /* simple_statement: declaration_statement  */
#line 3994 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12202 "MachineIndependent/glslang_tab.cpp"
    break;

  case 604: /* simple_statement: expression_statement  */
#line 3995 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12208 "MachineIndependent/glslang_tab.cpp"
    break;

  case 605: /* simple_statement: selection_statement  */
#line 3996 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12214 "MachineIndependent/glslang_tab.cpp"
    break;

  case 606: /* simple_statement: switch_statement  */
#line 3997 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12220 "MachineIndependent/glslang_tab.cpp"
    break;

  case 607: /* simple_statement: case_label  */
#line 3998 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12226 "MachineIndependent/glslang_tab.cpp"
    break;

  case 608: /* simple_statement: iteration_statement  */
#line 3999 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12232 "MachineIndependent/glslang_tab.cpp"
    break;

  case 609: /* simple_statement: jump_statement  */
#line 4000 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12238 "MachineIndependent/glslang_tab.cpp"
    break;

  case 610: /* simple_statement: demote_statement  */
#line 4001 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12244 "MachineIndependent/glslang_tab.cpp"
    break;

  case 611: /* demote_statement: DEMOTE SEMICOLON  */
#line 4005 "MachineIndependent/glslang.y"
                       {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangFragment, "demote");
        parseContext.requireExtensions((yyvsp[-1].lex).loc, 1, &E_GL_EXT_demote_to_helper_invocation, "demote");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpDemote, (yyvsp[-1].lex).loc);
    }
#line 12254 "MachineIndependent/glslang_tab.cpp"
    break;

  case 612: /* compound_statement: LEFT_BRACE RIGHT_BRACE  */
#line 4013 "MachineIndependent/glslang.y"
                             { (yyval.interm.intermNode) = 0; }
#line 12260 "MachineIndependent/glslang_tab.cpp"
    break;

  case 613: /* $@6: %empty  */
#line 4014 "MachineIndependent/glslang.y"
                 {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
    }
#line 12269 "MachineIndependent/glslang_tab.cpp"
    break;

  case 614: /* $@7: %empty  */
#line 4018 "MachineIndependent/glslang.y"
                     {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
    }
#line 12278 "MachineIndependent/glslang_tab.cpp"
    break;

  case 615: /* compound_statement: LEFT_BRACE $@6 statement_list $@7 RIGHT_BRACE  */
#line 4022 "MachineIndependent/glslang.y"
                  {
        if ((yyvsp[-2].interm.intermNode) && (yyvsp[-2].interm.intermNode)->getAsAggregate()) {
            (yyvsp[-2].interm.intermNode)->getAsAggregate()->setOperator(parseContext.intermediate.getDebugInfo() ? EOpScope : EOpSequence);
            (yyvsp[-2].interm.intermNode)->getAsAggregate()->setEndLoc((yyvsp[0].lex).loc);
        }
        (yyval.interm.intermNode) = (yyvsp[-2].interm.intermNode);
    }
#line 12290 "MachineIndependent/glslang_tab.cpp"
    break;

  case 616: /* statement_no_new_scope: compound_statement_no_new_scope  */
#line 4032 "MachineIndependent/glslang.y"
                                      { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12296 "MachineIndependent/glslang_tab.cpp"
    break;

  case 617: /* statement_no_new_scope: simple_statement  */
#line 4033 "MachineIndependent/glslang.y"
                                      { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 12302 "MachineIndependent/glslang_tab.cpp"
    break;

  case 618: /* $@8: %empty  */
#line 4037 "MachineIndependent/glslang.y"
      {
        ++parseContext.controlFlowNestingLevel;
    }
#line 12310 "MachineIndependent/glslang_tab.cpp"
    break;

  case 619: /* statement_scoped: $@8 compound_statement  */
#line 4040 "MachineIndependent/glslang.y"
                          {
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12319 "MachineIndependent/glslang_tab.cpp"
    break;

  case 620: /* $@9: %empty  */
#line 4044 "MachineIndependent/glslang.y"
      {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 12329 "MachineIndependent/glslang_tab.cpp"
    break;

  case 621: /* statement_scoped: $@9 simple_statement  */
#line 4049 "MachineIndependent/glslang.y"
                       {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12340 "MachineIndependent/glslang_tab.cpp"
    break;

  case 622: /* compound_statement_no_new_scope: LEFT_BRACE RIGHT_BRACE  */
#line 4058 "MachineIndependent/glslang.y"
                             {
        (yyval.interm.intermNode) = 0;
    }
#line 12348 "MachineIndependent/glslang_tab.cpp"
    break;

  case 623: /* compound_statement_no_new_scope: LEFT_BRACE statement_list RIGHT_BRACE  */
#line 4061 "MachineIndependent/glslang.y"
                                            {
        if ((yyvsp[-1].interm.intermNode) && (yyvsp[-1].interm.intermNode)->getAsAggregate()) {
            (yyvsp[-1].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
            (yyvsp[-1].interm.intermNode)->getAsAggregate()->setEndLoc((yyvsp[0].lex).loc);
        }
        (yyval.interm.intermNode) = (yyvsp[-1].interm.intermNode);
    }
#line 12360 "MachineIndependent/glslang_tab.cpp"
    break;

  case 624: /* statement_list: statement  */
#line 4071 "MachineIndependent/glslang.y"
                {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence(0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        }
    }
#line 12373 "MachineIndependent/glslang_tab.cpp"
    break;

  case 625: /* statement_list: statement_list statement  */
#line 4079 "MachineIndependent/glslang.y"
                               {
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence((yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        } else
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 12386 "MachineIndependent/glslang_tab.cpp"
    break;

  case 626: /* expression_statement: SEMICOLON  */
#line 4090 "MachineIndependent/glslang.y"
                 { (yyval.interm.intermNode) = 0; }
#line 12392 "MachineIndependent/glslang_tab.cpp"
    break;

  case 627: /* expression_statement: expression SEMICOLON  */
#line 4091 "MachineIndependent/glslang.y"
                            { (yyval.interm.intermNode) = static_cast<TIntermNode*>((yyvsp[-1].interm.intermTypedNode)); }
#line 12398 "MachineIndependent/glslang_tab.cpp"
    break;

  case 628: /* selection_statement: selection_statement_nonattributed  */
#line 4095 "MachineIndependent/glslang.y"
                                        {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12406 "MachineIndependent/glslang_tab.cpp"
    break;

  case 629: /* selection_statement: attribute selection_statement_nonattributed  */
#line 4098 "MachineIndependent/glslang.y"
                                                  {
        parseContext.requireExtensions((yyvsp[0].interm.intermNode)->getLoc(), 1, &E_GL_EXT_control_flow_attributes, "attribute");
        parseContext.handleSelectionAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12416 "MachineIndependent/glslang_tab.cpp"
    break;

  case 630: /* selection_statement_nonattributed: IF LEFT_PAREN expression RIGHT_PAREN selection_rest_statement  */
#line 4105 "MachineIndependent/glslang.y"
                                                                    {
        parseContext.boolCheck((yyvsp[-4].lex).loc, (yyvsp[-2].interm.intermTypedNode));
        (yyval.interm.intermNode) = parseContext.intermediate.addSelection((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.nodePair), (yyvsp[-4].lex).loc);
    }
#line 12425 "MachineIndependent/glslang_tab.cpp"
    break;

  case 631: /* selection_rest_statement: statement_scoped ELSE statement_scoped  */
#line 4112 "MachineIndependent/glslang.y"
                                             {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermNode);
    }
#line 12434 "MachineIndependent/glslang_tab.cpp"
    break;

  case 632: /* selection_rest_statement: statement_scoped  */
#line 4116 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.nodePair).node1 = (yyvsp[0].interm.intermNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 12443 "MachineIndependent/glslang_tab.cpp"
    break;

  case 633: /* condition: expression  */
#line 4124 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermTypedNode);
        parseContext.boolCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode));
    }
#line 12452 "MachineIndependent/glslang_tab.cpp"
    break;

  case 634: /* condition: fully_specified_type IDENTIFIER EQUAL initializer  */
#line 4128 "MachineIndependent/glslang.y"
                                                        {
        parseContext.boolCheck((yyvsp[-2].lex).loc, (yyvsp[-3].interm.type));

        TType type((yyvsp[-3].interm.type));
        (yyval.interm.intermNode) = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
    }
#line 12463 "MachineIndependent/glslang_tab.cpp"
    break;

  case 635: /* switch_statement: switch_statement_nonattributed  */
#line 4137 "MachineIndependent/glslang.y"
                                     {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12471 "MachineIndependent/glslang_tab.cpp"
    break;

  case 636: /* switch_statement: attribute switch_statement_nonattributed  */
#line 4140 "MachineIndependent/glslang.y"
                                               {
        parseContext.requireExtensions((yyvsp[0].interm.intermNode)->getLoc(), 1, &E_GL_EXT_control_flow_attributes, "attribute");
        parseContext.handleSwitchAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12481 "MachineIndependent/glslang_tab.cpp"
    break;

  case 637: /* $@10: %empty  */
#line 4147 "MachineIndependent/glslang.y"
                                               {
        // start new switch sequence on the switch stack
        ++parseContext.controlFlowNestingLevel;
        ++parseContext.statementNestingLevel;
        parseContext.switchSequenceStack.push_back(new TIntermSequence);
        parseContext.switchLevel.push_back(parseContext.statementNestingLevel);
        parseContext.symbolTable.push();
    }
#line 12494 "MachineIndependent/glslang_tab.cpp"
    break;

  case 638: /* switch_statement_nonattributed: SWITCH LEFT_PAREN expression RIGHT_PAREN $@10 LEFT_BRACE switch_statement_list RIGHT_BRACE  */
#line 4155 "MachineIndependent/glslang.y"
                                                 {
        (yyval.interm.intermNode) = parseContext.addSwitch((yyvsp[-7].lex).loc, (yyvsp[-5].interm.intermTypedNode), (yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0);
        delete parseContext.switchSequenceStack.back();
        parseContext.switchSequenceStack.pop_back();
        parseContext.switchLevel.pop_back();
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 12508 "MachineIndependent/glslang_tab.cpp"
    break;

  case 639: /* switch_statement_list: %empty  */
#line 4167 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermNode) = 0;
    }
#line 12516 "MachineIndependent/glslang_tab.cpp"
    break;

  case 640: /* switch_statement_list: statement_list  */
#line 4170 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12524 "MachineIndependent/glslang_tab.cpp"
    break;

  case 641: /* case_label: CASE expression COLON  */
#line 4176 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[-2].lex).loc, "cannot appear outside switch statement", "case", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[-2].lex).loc, "cannot be nested inside control flow", "case", "");
        else {
            parseContext.constantValueCheck((yyvsp[-1].interm.intermTypedNode), "case");
            parseContext.integerCheck((yyvsp[-1].interm.intermTypedNode), "case");
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpCase, (yyvsp[-1].interm.intermTypedNode), (yyvsp[-2].lex).loc);
        }
    }
#line 12541 "MachineIndependent/glslang_tab.cpp"
    break;

  case 642: /* case_label: DEFAULT COLON  */
#line 4188 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[-1].lex).loc, "cannot appear outside switch statement", "default", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[-1].lex).loc, "cannot be nested inside control flow", "default", "");
        else
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpDefault, (yyvsp[-1].lex).loc);
    }
#line 12555 "MachineIndependent/glslang_tab.cpp"
    break;

  case 643: /* iteration_statement: iteration_statement_nonattributed  */
#line 4200 "MachineIndependent/glslang.y"
                                        {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12563 "MachineIndependent/glslang_tab.cpp"
    break;

  case 644: /* iteration_statement: attribute iteration_statement_nonattributed  */
#line 4203 "MachineIndependent/glslang.y"
                                                  {
        const char * extensions[2] = { E_GL_EXT_control_flow_attributes, E_GL_EXT_control_flow_attributes2 };
        parseContext.requireExtensions((yyvsp[0].interm.intermNode)->getLoc(), 2, extensions, "attribute");
        parseContext.handleLoopAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12574 "MachineIndependent/glslang_tab.cpp"
    break;

  case 645: /* $@11: %empty  */
#line 4211 "MachineIndependent/glslang.y"
                       {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-1].lex).loc, "while loops not available", "limitation", "");
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 12587 "MachineIndependent/glslang_tab.cpp"
    break;

  case 646: /* iteration_statement_nonattributed: WHILE LEFT_PAREN $@11 condition RIGHT_PAREN statement_no_new_scope  */
#line 4219 "MachineIndependent/glslang.y"
                                                   {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[0].interm.intermNode), (yyvsp[-2].interm.intermNode), 0, true, (yyvsp[-5].lex).loc);
        if (parseContext.intermediate.getDebugInfo()) {
            (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyval.interm.intermNode), (yyvsp[-5].lex).loc);
            (yyval.interm.intermNode)->getAsAggregate()->setOperator(EOpScope);
        }
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 12603 "MachineIndependent/glslang_tab.cpp"
    break;

  case 647: /* $@12: %empty  */
#line 4230 "MachineIndependent/glslang.y"
         {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 12614 "MachineIndependent/glslang_tab.cpp"
    break;

  case 648: /* iteration_statement_nonattributed: DO $@12 statement WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON  */
#line 4236 "MachineIndependent/glslang.y"
                                                                  {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-7].lex).loc, "do-while loops not available", "limitation", "");

        parseContext.boolCheck((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode));

        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[-5].interm.intermNode), (yyvsp[-2].interm.intermTypedNode), 0, false, (yyvsp[-4].lex).loc);
        if (parseContext.intermediate.getDebugInfo()) {
            (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyval.interm.intermNode), (yyvsp[-4].lex).loc);
            (yyval.interm.intermNode)->getAsAggregate()->setOperator(EOpScope);
        }
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 12635 "MachineIndependent/glslang_tab.cpp"
    break;

  case 649: /* $@13: %empty  */
#line 4252 "MachineIndependent/glslang.y"
                     {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 12646 "MachineIndependent/glslang_tab.cpp"
    break;

  case 650: /* iteration_statement_nonattributed: FOR LEFT_PAREN $@13 for_init_statement for_rest_statement RIGHT_PAREN statement_no_new_scope  */
#line 4258 "MachineIndependent/glslang.y"
                                                                               {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[-3].interm.intermNode), (yyvsp[-5].lex).loc);
        TIntermLoop* forLoop = parseContext.intermediate.addLoop((yyvsp[0].interm.intermNode), reinterpret_cast<TIntermTyped*>((yyvsp[-2].interm.nodePair).node1), reinterpret_cast<TIntermTyped*>((yyvsp[-2].interm.nodePair).node2), true, (yyvsp[-6].lex).loc);
        if (! parseContext.limits.nonInductiveForLoops)
            parseContext.inductiveLoopCheck((yyvsp[-6].lex).loc, (yyvsp[-3].interm.intermNode), forLoop);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyval.interm.intermNode), forLoop, (yyvsp[-6].lex).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setOperator(parseContext.intermediate.getDebugInfo() ? EOpScope : EOpSequence);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 12663 "MachineIndependent/glslang_tab.cpp"
    break;

  case 651: /* for_init_statement: expression_statement  */
#line 4273 "MachineIndependent/glslang.y"
                           {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12671 "MachineIndependent/glslang_tab.cpp"
    break;

  case 652: /* for_init_statement: declaration_statement  */
#line 4276 "MachineIndependent/glslang.y"
                            {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12679 "MachineIndependent/glslang_tab.cpp"
    break;

  case 653: /* conditionopt: condition  */
#line 4282 "MachineIndependent/glslang.y"
                {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12687 "MachineIndependent/glslang_tab.cpp"
    break;

  case 654: /* conditionopt: %empty  */
#line 4285 "MachineIndependent/glslang.y"
                        {
        (yyval.interm.intermNode) = 0;
    }
#line 12695 "MachineIndependent/glslang_tab.cpp"
    break;

  case 655: /* for_rest_statement: conditionopt SEMICOLON  */
#line 4291 "MachineIndependent/glslang.y"
                             {
        (yyval.interm.nodePair).node1 = (yyvsp[-1].interm.intermNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 12704 "MachineIndependent/glslang_tab.cpp"
    break;

  case 656: /* for_rest_statement: conditionopt SEMICOLON expression  */
#line 4295 "MachineIndependent/glslang.y"
                                         {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermTypedNode);
    }
#line 12713 "MachineIndependent/glslang_tab.cpp"
    break;

  case 657: /* jump_statement: CONTINUE SEMICOLON  */
#line 4302 "MachineIndependent/glslang.y"
                         {
        if (parseContext.loopNestingLevel <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "continue statement only allowed in loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpContinue, (yyvsp[-1].lex).loc);
    }
#line 12723 "MachineIndependent/glslang_tab.cpp"
    break;

  case 658: /* jump_statement: BREAK SEMICOLON  */
#line 4307 "MachineIndependent/glslang.y"
                      {
        if (parseContext.loopNestingLevel + parseContext.switchSequenceStack.size() <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "break statement only allowed in switch and loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpBreak, (yyvsp[-1].lex).loc);
    }
#line 12733 "MachineIndependent/glslang_tab.cpp"
    break;

  case 659: /* jump_statement: RETURN SEMICOLON  */
#line 4312 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpReturn, (yyvsp[-1].lex).loc);
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid)
            parseContext.error((yyvsp[-1].lex).loc, "non-void function must return a value", "return", "");
        if (parseContext.inMain)
            parseContext.postEntryPointReturn = true;
    }
#line 12745 "MachineIndependent/glslang_tab.cpp"
    break;

  case 660: /* jump_statement: RETURN expression SEMICOLON  */
#line 4319 "MachineIndependent/glslang.y"
                                  {
        (yyval.interm.intermNode) = parseContext.handleReturnValue((yyvsp[-2].lex).loc, (yyvsp[-1].interm.intermTypedNode));
    }
#line 12753 "MachineIndependent/glslang_tab.cpp"
    break;

  case 661: /* jump_statement: DISCARD SEMICOLON  */
#line 4322 "MachineIndependent/glslang.y"
                        {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangFragment, "discard");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpKill, (yyvsp[-1].lex).loc);
    }
#line 12762 "MachineIndependent/glslang_tab.cpp"
    break;

  case 662: /* jump_statement: TERMINATE_INVOCATION SEMICOLON  */
#line 4326 "MachineIndependent/glslang.y"
                                     {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangFragment, "terminateInvocation");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpTerminateInvocation, (yyvsp[-1].lex).loc);
    }
#line 12771 "MachineIndependent/glslang_tab.cpp"
    break;

  case 663: /* jump_statement: TERMINATE_RAY SEMICOLON  */
#line 4330 "MachineIndependent/glslang.y"
                              {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangAnyHit, "terminateRayEXT");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpTerminateRayKHR, (yyvsp[-1].lex).loc);
    }
#line 12780 "MachineIndependent/glslang_tab.cpp"
    break;

  case 664: /* jump_statement: IGNORE_INTERSECTION SEMICOLON  */
#line 4334 "MachineIndependent/glslang.y"
                                    {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangAnyHit, "ignoreIntersectionEXT");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpIgnoreIntersectionKHR, (yyvsp[-1].lex).loc);
    }
#line 12789 "MachineIndependent/glslang_tab.cpp"
    break;

  case 665: /* translation_unit: external_declaration  */
#line 4343 "MachineIndependent/glslang.y"
                           {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
        parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
    }
#line 12798 "MachineIndependent/glslang_tab.cpp"
    break;

  case 666: /* translation_unit: translation_unit external_declaration  */
#line 4347 "MachineIndependent/glslang.y"
                                            {
        if ((yyvsp[0].interm.intermNode) != nullptr) {
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
            parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
        }
    }
#line 12809 "MachineIndependent/glslang_tab.cpp"
    break;

  case 667: /* external_declaration: function_definition  */
#line 4356 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12817 "MachineIndependent/glslang_tab.cpp"
    break;

  case 668: /* external_declaration: declaration  */
#line 4359 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 12825 "MachineIndependent/glslang_tab.cpp"
    break;

  case 669: /* external_declaration: SEMICOLON  */
#line 4362 "MachineIndependent/glslang.y"
                {
        parseContext.requireProfile((yyvsp[0].lex).loc, ~EEsProfile, "extraneous semicolon");
        parseContext.profileRequires((yyvsp[0].lex).loc, ~EEsProfile, 460, nullptr, "extraneous semicolon");
        (yyval.interm.intermNode) = nullptr;
    }
#line 12835 "MachineIndependent/glslang_tab.cpp"
    break;

  case 670: /* $@14: %empty  */
#line 4370 "MachineIndependent/glslang.y"
                         {
        (yyvsp[0].interm).function = parseContext.handleFunctionDeclarator((yyvsp[0].interm).loc, *(yyvsp[0].interm).function, false /* not prototype */);
        (yyvsp[0].interm).intermNode = parseContext.handleFunctionDefinition((yyvsp[0].interm).loc, *(yyvsp[0].interm).function);

        // For ES 100 only, according to ES shading language 100 spec: A function
        // body has a scope nested inside the function's definition.
        if (parseContext.profile == EEsProfile && parseContext.version == 100)
        {
            parseContext.symbolTable.push();
            ++parseContext.statementNestingLevel;
        }
    }
#line 12852 "MachineIndependent/glslang_tab.cpp"
    break;

  case 671: /* function_definition: function_prototype $@14 compound_statement_no_new_scope  */
#line 4382 "MachineIndependent/glslang.y"
                                    {
        //   May be best done as post process phase on intermediate code
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid && ! parseContext.functionReturnsValue)
            parseContext.error((yyvsp[-2].interm).loc, "function does not return a value:", "", (yyvsp[-2].interm).function->getName().c_str());
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode)->getAsAggregate()->setLinkType((yyvsp[-2].interm).function->getLinkType());
        parseContext.intermediate.setAggregateOperator((yyval.interm.intermNode), EOpFunction, (yyvsp[-2].interm).function->getType(), (yyvsp[-2].interm).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setName((yyvsp[-2].interm).function->getMangledName().c_str());

        // store the pragma information for debug and optimize and other vendor specific
        // information. This information can be queried from the parse tree
        (yyval.interm.intermNode)->getAsAggregate()->setOptimize(parseContext.contextPragma.optimize);
        (yyval.interm.intermNode)->getAsAggregate()->setDebug(parseContext.contextPragma.debug);
        (yyval.interm.intermNode)->getAsAggregate()->setPragmaTable(parseContext.contextPragma.pragmaTable);

        // Set currentFunctionType to empty pointer when goes outside of the function
        parseContext.currentFunctionType = nullptr;

        // For ES 100 only, according to ES shading language 100 spec: A function
        // body has a scope nested inside the function's definition.
        if (parseContext.profile == EEsProfile && parseContext.version == 100)
        {
            parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
            --parseContext.statementNestingLevel;
        }
    }
#line 12884 "MachineIndependent/glslang_tab.cpp"
    break;

  case 672: /* attribute: LEFT_BRACKET LEFT_BRACKET attribute_list RIGHT_BRACKET RIGHT_BRACKET  */
#line 4412 "MachineIndependent/glslang.y"
                                                                           {
        (yyval.interm.attributes) = (yyvsp[-2].interm.attributes);
    }
#line 12892 "MachineIndependent/glslang_tab.cpp"
    break;

  case 673: /* attribute_list: single_attribute  */
#line 4417 "MachineIndependent/glslang.y"
                       {
        (yyval.interm.attributes) = (yyvsp[0].interm.attributes);
    }
#line 12900 "MachineIndependent/glslang_tab.cpp"
    break;

  case 674: /* attribute_list: attribute_list COMMA single_attribute  */
#line 4420 "MachineIndependent/glslang.y"
                                            {
        (yyval.interm.attributes) = parseContext.mergeAttributes((yyvsp[-2].interm.attributes), (yyvsp[0].interm.attributes));
    }
#line 12908 "MachineIndependent/glslang_tab.cpp"
    break;

  case 675: /* single_attribute: IDENTIFIER  */
#line 4425 "MachineIndependent/glslang.y"
                 {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[0].lex).string);
    }
#line 12916 "MachineIndependent/glslang_tab.cpp"
    break;

  case 676: /* single_attribute: IDENTIFIER LEFT_PAREN constant_expression RIGHT_PAREN  */
#line 4428 "MachineIndependent/glslang.y"
                                                            {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[-3].lex).string, (yyvsp[-1].interm.intermTypedNode));
    }
#line 12924 "MachineIndependent/glslang_tab.cpp"
    break;

  case 677: /* spirv_requirements_list: spirv_requirements_parameter  */
#line 4433 "MachineIndependent/glslang.y"
                                   {
        (yyval.interm.spirvReq) = (yyvsp[0].interm.spirvReq);
    }
#line 12932 "MachineIndependent/glslang_tab.cpp"
    break;

  case 678: /* spirv_requirements_list: spirv_requirements_list COMMA spirv_requirements_parameter  */
#line 4436 "MachineIndependent/glslang.y"
                                                                 {
        (yyval.interm.spirvReq) = parseContext.mergeSpirvRequirements((yyvsp[-1].lex).loc, (yyvsp[-2].interm.spirvReq), (yyvsp[0].interm.spirvReq));
    }
#line 12940 "MachineIndependent/glslang_tab.cpp"
    break;

  case 679: /* spirv_requirements_parameter: IDENTIFIER EQUAL LEFT_BRACKET spirv_extension_list RIGHT_BRACKET  */
#line 4441 "MachineIndependent/glslang.y"
                                                                       {
        (yyval.interm.spirvReq) = parseContext.makeSpirvRequirement((yyvsp[-3].lex).loc, *(yyvsp[-4].lex).string, (yyvsp[-1].interm.intermNode)->getAsAggregate(), nullptr);
    }
#line 12948 "MachineIndependent/glslang_tab.cpp"
    break;

  case 680: /* spirv_requirements_parameter: IDENTIFIER EQUAL LEFT_BRACKET spirv_capability_list RIGHT_BRACKET  */
#line 4444 "MachineIndependent/glslang.y"
                                                                        {
        (yyval.interm.spirvReq) = parseContext.makeSpirvRequirement((yyvsp[-3].lex).loc, *(yyvsp[-4].lex).string, nullptr, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 12956 "MachineIndependent/glslang_tab.cpp"
    break;

  case 681: /* spirv_extension_list: STRING_LITERAL  */
#line 4449 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate(parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true));
    }
#line 12964 "MachineIndependent/glslang_tab.cpp"
    break;

  case 682: /* spirv_extension_list: spirv_extension_list COMMA STRING_LITERAL  */
#line 4452 "MachineIndependent/glslang.y"
                                                {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true));
    }
#line 12972 "MachineIndependent/glslang_tab.cpp"
    break;

  case 683: /* spirv_capability_list: INTCONSTANT  */
#line 4457 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate(parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true));
    }
#line 12980 "MachineIndependent/glslang_tab.cpp"
    break;

  case 684: /* spirv_capability_list: spirv_capability_list COMMA INTCONSTANT  */
#line 4460 "MachineIndependent/glslang.y"
                                              {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true));
    }
#line 12988 "MachineIndependent/glslang_tab.cpp"
    break;

  case 685: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE LEFT_PAREN INTCONSTANT RIGHT_PAREN  */
#line 4465 "MachineIndependent/glslang.y"
                                                              {
        parseContext.intermediate.insertSpirvExecutionMode((yyvsp[-1].lex).i);
        (yyval.interm.intermNode) = 0;
    }
#line 12997 "MachineIndependent/glslang_tab.cpp"
    break;

  case 686: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT RIGHT_PAREN  */
#line 4469 "MachineIndependent/glslang.y"
                                                                                            {
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-3].interm.spirvReq));
        parseContext.intermediate.insertSpirvExecutionMode((yyvsp[-1].lex).i);
        (yyval.interm.intermNode) = 0;
    }
#line 13007 "MachineIndependent/glslang_tab.cpp"
    break;

  case 687: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE LEFT_PAREN INTCONSTANT COMMA spirv_execution_mode_parameter_list RIGHT_PAREN  */
#line 4474 "MachineIndependent/glslang.y"
                                                                                                        {
        parseContext.intermediate.insertSpirvExecutionMode((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
        (yyval.interm.intermNode) = 0;
    }
#line 13016 "MachineIndependent/glslang_tab.cpp"
    break;

  case 688: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT COMMA spirv_execution_mode_parameter_list RIGHT_PAREN  */
#line 4478 "MachineIndependent/glslang.y"
                                                                                                                                      {
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        parseContext.intermediate.insertSpirvExecutionMode((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
        (yyval.interm.intermNode) = 0;
    }
#line 13026 "MachineIndependent/glslang_tab.cpp"
    break;

  case 689: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE_ID LEFT_PAREN INTCONSTANT COMMA spirv_execution_mode_id_parameter_list RIGHT_PAREN  */
#line 4483 "MachineIndependent/glslang.y"
                                                                                                              {
        parseContext.intermediate.insertSpirvExecutionModeId((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
        (yyval.interm.intermNode) = 0;
    }
#line 13035 "MachineIndependent/glslang_tab.cpp"
    break;

  case 690: /* spirv_execution_mode_qualifier: SPIRV_EXECUTION_MODE_ID LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT COMMA spirv_execution_mode_id_parameter_list RIGHT_PAREN  */
#line 4487 "MachineIndependent/glslang.y"
                                                                                                                                            {
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        parseContext.intermediate.insertSpirvExecutionModeId((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
        (yyval.interm.intermNode) = 0;
    }
#line 13045 "MachineIndependent/glslang_tab.cpp"
    break;

  case 691: /* spirv_execution_mode_parameter_list: spirv_execution_mode_parameter  */
#line 4494 "MachineIndependent/glslang.y"
                                     {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
    }
#line 13053 "MachineIndependent/glslang_tab.cpp"
    break;

  case 692: /* spirv_execution_mode_parameter_list: spirv_execution_mode_parameter_list COMMA spirv_execution_mode_parameter  */
#line 4497 "MachineIndependent/glslang.y"
                                                                               {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 13061 "MachineIndependent/glslang_tab.cpp"
    break;

  case 693: /* spirv_execution_mode_parameter: FLOATCONSTANT  */
#line 4502 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 13069 "MachineIndependent/glslang_tab.cpp"
    break;

  case 694: /* spirv_execution_mode_parameter: INTCONSTANT  */
#line 4505 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 13077 "MachineIndependent/glslang_tab.cpp"
    break;

  case 695: /* spirv_execution_mode_parameter: UINTCONSTANT  */
#line 4508 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 13085 "MachineIndependent/glslang_tab.cpp"
    break;

  case 696: /* spirv_execution_mode_parameter: BOOLCONSTANT  */
#line 4511 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 13093 "MachineIndependent/glslang_tab.cpp"
    break;

  case 697: /* spirv_execution_mode_parameter: STRING_LITERAL  */
#line 4514 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true);
    }
#line 13101 "MachineIndependent/glslang_tab.cpp"
    break;

  case 698: /* spirv_execution_mode_id_parameter_list: constant_expression  */
#line 4519 "MachineIndependent/glslang.y"
                          {
        if ((yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtFloat &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtInt &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtUint &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtBool &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtString)
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "this type not allowed", (yyvsp[0].interm.intermTypedNode)->getType().getBasicString(), "");
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermTypedNode));
    }
#line 13115 "MachineIndependent/glslang_tab.cpp"
    break;

  case 699: /* spirv_execution_mode_id_parameter_list: spirv_execution_mode_id_parameter_list COMMA constant_expression  */
#line 4528 "MachineIndependent/glslang.y"
                                                                       {
        if ((yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtFloat &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtInt &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtUint &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtBool &&
            (yyvsp[0].interm.intermTypedNode)->getBasicType() != EbtString)
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "this type not allowed", (yyvsp[0].interm.intermTypedNode)->getType().getBasicString(), "");
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), (yyvsp[0].interm.intermTypedNode));
    }
#line 13129 "MachineIndependent/glslang_tab.cpp"
    break;

  case 700: /* spirv_storage_class_qualifier: SPIRV_STORAGE_CLASS LEFT_PAREN INTCONSTANT RIGHT_PAREN  */
#line 4539 "MachineIndependent/glslang.y"
                                                             {
        (yyval.interm.type).init((yyvsp[-3].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqSpirvStorageClass;
        (yyval.interm.type).qualifier.spirvStorageClass = (yyvsp[-1].lex).i;
    }
#line 13139 "MachineIndependent/glslang_tab.cpp"
    break;

  case 701: /* spirv_storage_class_qualifier: SPIRV_STORAGE_CLASS LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT RIGHT_PAREN  */
#line 4544 "MachineIndependent/glslang.y"
                                                                                           {
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-3].interm.spirvReq));
        (yyval.interm.type).qualifier.storage = EvqSpirvStorageClass;
        (yyval.interm.type).qualifier.spirvStorageClass = (yyvsp[-1].lex).i;
    }
#line 13150 "MachineIndependent/glslang_tab.cpp"
    break;

  case 702: /* spirv_decorate_qualifier: SPIRV_DECORATE LEFT_PAREN INTCONSTANT RIGHT_PAREN  */
#line 4552 "MachineIndependent/glslang.y"
                                                       {
        (yyval.interm.type).init((yyvsp[-3].lex).loc);
        (yyval.interm.type).qualifier.setSpirvDecorate((yyvsp[-1].lex).i);
    }
#line 13159 "MachineIndependent/glslang_tab.cpp"
    break;

  case 703: /* spirv_decorate_qualifier: SPIRV_DECORATE LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT RIGHT_PAREN  */
#line 4556 "MachineIndependent/glslang.y"
                                                                                     {
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-3].interm.spirvReq));
        (yyval.interm.type).qualifier.setSpirvDecorate((yyvsp[-1].lex).i);
    }
#line 13169 "MachineIndependent/glslang_tab.cpp"
    break;

  case 704: /* spirv_decorate_qualifier: SPIRV_DECORATE LEFT_PAREN INTCONSTANT COMMA spirv_decorate_parameter_list RIGHT_PAREN  */
#line 4561 "MachineIndependent/glslang.y"
                                                                                            {
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        (yyval.interm.type).qualifier.setSpirvDecorate((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13178 "MachineIndependent/glslang_tab.cpp"
    break;

  case 705: /* spirv_decorate_qualifier: SPIRV_DECORATE LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT COMMA spirv_decorate_parameter_list RIGHT_PAREN  */
#line 4565 "MachineIndependent/glslang.y"
                                                                                                                          {
        (yyval.interm.type).init((yyvsp[-7].lex).loc);
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        (yyval.interm.type).qualifier.setSpirvDecorate((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13188 "MachineIndependent/glslang_tab.cpp"
    break;

  case 706: /* spirv_decorate_qualifier: SPIRV_DECORATE_ID LEFT_PAREN INTCONSTANT COMMA spirv_decorate_id_parameter_list RIGHT_PAREN  */
#line 4570 "MachineIndependent/glslang.y"
                                                                                                  {
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        (yyval.interm.type).qualifier.setSpirvDecorateId((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13197 "MachineIndependent/glslang_tab.cpp"
    break;

  case 707: /* spirv_decorate_qualifier: SPIRV_DECORATE_ID LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT COMMA spirv_decorate_id_parameter_list RIGHT_PAREN  */
#line 4574 "MachineIndependent/glslang.y"
                                                                                                                                {
        (yyval.interm.type).init((yyvsp[-7].lex).loc);
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        (yyval.interm.type).qualifier.setSpirvDecorateId((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13207 "MachineIndependent/glslang_tab.cpp"
    break;

  case 708: /* spirv_decorate_qualifier: SPIRV_DECORATE_STRING LEFT_PAREN INTCONSTANT COMMA spirv_decorate_string_parameter_list RIGHT_PAREN  */
#line 4579 "MachineIndependent/glslang.y"
                                                                                                          {
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        (yyval.interm.type).qualifier.setSpirvDecorateString((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13216 "MachineIndependent/glslang_tab.cpp"
    break;

  case 709: /* spirv_decorate_qualifier: SPIRV_DECORATE_STRING LEFT_PAREN spirv_requirements_list COMMA INTCONSTANT COMMA spirv_decorate_string_parameter_list RIGHT_PAREN  */
#line 4583 "MachineIndependent/glslang.y"
                                                                                                                                        {
        (yyval.interm.type).init((yyvsp[-7].lex).loc);
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        (yyval.interm.type).qualifier.setSpirvDecorateString((yyvsp[-3].lex).i, (yyvsp[-1].interm.intermNode)->getAsAggregate());
    }
#line 13226 "MachineIndependent/glslang_tab.cpp"
    break;

  case 710: /* spirv_decorate_parameter_list: spirv_decorate_parameter  */
#line 4590 "MachineIndependent/glslang.y"
                               {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
    }
#line 13234 "MachineIndependent/glslang_tab.cpp"
    break;

  case 711: /* spirv_decorate_parameter_list: spirv_decorate_parameter_list COMMA spirv_decorate_parameter  */
#line 4593 "MachineIndependent/glslang.y"
                                                                   {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 13242 "MachineIndependent/glslang_tab.cpp"
    break;

  case 712: /* spirv_decorate_parameter: FLOATCONSTANT  */
#line 4598 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 13250 "MachineIndependent/glslang_tab.cpp"
    break;

  case 713: /* spirv_decorate_parameter: INTCONSTANT  */
#line 4601 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 13258 "MachineIndependent/glslang_tab.cpp"
    break;

  case 714: /* spirv_decorate_parameter: UINTCONSTANT  */
#line 4604 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 13266 "MachineIndependent/glslang_tab.cpp"
    break;

  case 715: /* spirv_decorate_parameter: BOOLCONSTANT  */
#line 4607 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 13274 "MachineIndependent/glslang_tab.cpp"
    break;

  case 716: /* spirv_decorate_id_parameter_list: spirv_decorate_id_parameter  */
#line 4612 "MachineIndependent/glslang.y"
                                  {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
    }
#line 13282 "MachineIndependent/glslang_tab.cpp"
    break;

  case 717: /* spirv_decorate_id_parameter_list: spirv_decorate_id_parameter_list COMMA spirv_decorate_id_parameter  */
#line 4615 "MachineIndependent/glslang.y"
                                                                         {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 13290 "MachineIndependent/glslang_tab.cpp"
    break;

  case 718: /* spirv_decorate_id_parameter: variable_identifier  */
#line 4620 "MachineIndependent/glslang.y"
                          {
        if ((yyvsp[0].interm.intermTypedNode)->getAsConstantUnion() || (yyvsp[0].interm.intermTypedNode)->getAsSymbolNode())
            (yyval.interm.intermNode) = (yyvsp[0].interm.intermTypedNode);
        else
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "only allow constants or variables which are not elements of a composite", "", "");
    }
#line 13301 "MachineIndependent/glslang_tab.cpp"
    break;

  case 719: /* spirv_decorate_id_parameter: FLOATCONSTANT  */
#line 4626 "MachineIndependent/glslang.y"
                    {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 13309 "MachineIndependent/glslang_tab.cpp"
    break;

  case 720: /* spirv_decorate_id_parameter: INTCONSTANT  */
#line 4629 "MachineIndependent/glslang.y"
                  {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 13317 "MachineIndependent/glslang_tab.cpp"
    break;

  case 721: /* spirv_decorate_id_parameter: UINTCONSTANT  */
#line 4632 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 13325 "MachineIndependent/glslang_tab.cpp"
    break;

  case 722: /* spirv_decorate_id_parameter: BOOLCONSTANT  */
#line 4635 "MachineIndependent/glslang.y"
                   {
        (yyval.interm.intermNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 13333 "MachineIndependent/glslang_tab.cpp"
    break;

  case 723: /* spirv_decorate_string_parameter_list: STRING_LITERAL  */
#line 4640 "MachineIndependent/glslang.y"
                     {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate(
            parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true));
    }
#line 13342 "MachineIndependent/glslang_tab.cpp"
    break;

  case 724: /* spirv_decorate_string_parameter_list: spirv_decorate_string_parameter_list COMMA STRING_LITERAL  */
#line 4644 "MachineIndependent/glslang.y"
                                                                {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermNode), parseContext.intermediate.addConstantUnion((yyvsp[0].lex).string, (yyvsp[0].lex).loc, true));
    }
#line 13350 "MachineIndependent/glslang_tab.cpp"
    break;

  case 725: /* spirv_type_specifier: SPIRV_TYPE LEFT_PAREN spirv_instruction_qualifier_list COMMA spirv_type_parameter_list RIGHT_PAREN  */
#line 4649 "MachineIndependent/glslang.y"
                                                                                                         {
        (yyval.interm.type).init((yyvsp[-5].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).setSpirvType(*(yyvsp[-3].interm.spirvInst), (yyvsp[-1].interm.spirvTypeParams));
    }
#line 13359 "MachineIndependent/glslang_tab.cpp"
    break;

  case 726: /* spirv_type_specifier: SPIRV_TYPE LEFT_PAREN spirv_requirements_list COMMA spirv_instruction_qualifier_list COMMA spirv_type_parameter_list RIGHT_PAREN  */
#line 4653 "MachineIndependent/glslang.y"
                                                                                                                                       {
        (yyval.interm.type).init((yyvsp[-7].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-5].interm.spirvReq));
        (yyval.interm.type).setSpirvType(*(yyvsp[-3].interm.spirvInst), (yyvsp[-1].interm.spirvTypeParams));
    }
#line 13369 "MachineIndependent/glslang_tab.cpp"
    break;

  case 727: /* spirv_type_specifier: SPIRV_TYPE LEFT_PAREN spirv_instruction_qualifier_list RIGHT_PAREN  */
#line 4658 "MachineIndependent/glslang.y"
                                                                         {
        (yyval.interm.type).init((yyvsp[-3].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).setSpirvType(*(yyvsp[-1].interm.spirvInst));
    }
#line 13378 "MachineIndependent/glslang_tab.cpp"
    break;

  case 728: /* spirv_type_specifier: SPIRV_TYPE LEFT_PAREN spirv_requirements_list COMMA spirv_instruction_qualifier_list RIGHT_PAREN  */
#line 4662 "MachineIndependent/glslang.y"
                                                                                                       {
        (yyval.interm.type).init((yyvsp[-5].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-3].interm.spirvReq));
        (yyval.interm.type).setSpirvType(*(yyvsp[-1].interm.spirvInst));
    }
#line 13388 "MachineIndependent/glslang_tab.cpp"
    break;

  case 729: /* spirv_type_parameter_list: spirv_type_parameter  */
#line 4669 "MachineIndependent/glslang.y"
                           {
        (yyval.interm.spirvTypeParams) = (yyvsp[0].interm.spirvTypeParams);
    }
#line 13396 "MachineIndependent/glslang_tab.cpp"
    break;

  case 730: /* spirv_type_parameter_list: spirv_type_parameter_list COMMA spirv_type_parameter  */
#line 4672 "MachineIndependent/glslang.y"
                                                           {
        (yyval.interm.spirvTypeParams) = parseContext.mergeSpirvTypeParameters((yyvsp[-2].interm.spirvTypeParams), (yyvsp[0].interm.spirvTypeParams));
    }
#line 13404 "MachineIndependent/glslang_tab.cpp"
    break;

  case 731: /* spirv_type_parameter: constant_expression  */
#line 4677 "MachineIndependent/glslang.y"
                          {
        (yyval.interm.spirvTypeParams) = parseContext.makeSpirvTypeParameters((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode)->getAsConstantUnion());
    }
#line 13412 "MachineIndependent/glslang_tab.cpp"
    break;

  case 732: /* spirv_type_parameter: type_specifier_nonarray  */
#line 4680 "MachineIndependent/glslang.y"
                              {
        (yyval.interm.spirvTypeParams) = parseContext.makeSpirvTypeParameters((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 13420 "MachineIndependent/glslang_tab.cpp"
    break;

  case 733: /* spirv_instruction_qualifier: SPIRV_INSTRUCTION LEFT_PAREN spirv_instruction_qualifier_list RIGHT_PAREN  */
#line 4685 "MachineIndependent/glslang.y"
                                                                                {
        (yyval.interm.spirvInst) = (yyvsp[-1].interm.spirvInst);
    }
#line 13428 "MachineIndependent/glslang_tab.cpp"
    break;

  case 734: /* spirv_instruction_qualifier: SPIRV_INSTRUCTION LEFT_PAREN spirv_requirements_list COMMA spirv_instruction_qualifier_list RIGHT_PAREN  */
#line 4688 "MachineIndependent/glslang.y"
                                                                                                              {
        parseContext.intermediate.insertSpirvRequirement((yyvsp[-3].interm.spirvReq));
        (yyval.interm.spirvInst) = (yyvsp[-1].interm.spirvInst);
    }
#line 13437 "MachineIndependent/glslang_tab.cpp"
    break;

  case 735: /* spirv_instruction_qualifier_list: spirv_instruction_qualifier_id  */
#line 4694 "MachineIndependent/glslang.y"
                                     {
        (yyval.interm.spirvInst) = (yyvsp[0].interm.spirvInst);
    }
#line 13445 "MachineIndependent/glslang_tab.cpp"
    break;

  case 736: /* spirv_instruction_qualifier_list: spirv_instruction_qualifier_list COMMA spirv_instruction_qualifier_id  */
#line 4697 "MachineIndependent/glslang.y"
                                                                            {
        (yyval.interm.spirvInst) = parseContext.mergeSpirvInstruction((yyvsp[-1].lex).loc, (yyvsp[-2].interm.spirvInst), (yyvsp[0].interm.spirvInst));
    }
#line 13453 "MachineIndependent/glslang_tab.cpp"
    break;

  case 737: /* spirv_instruction_qualifier_id: IDENTIFIER EQUAL STRING_LITERAL  */
#line 4702 "MachineIndependent/glslang.y"
                                      {
        (yyval.interm.spirvInst) = parseContext.makeSpirvInstruction((yyvsp[-1].lex).loc, *(yyvsp[-2].lex).string, *(yyvsp[0].lex).string);
    }
#line 13461 "MachineIndependent/glslang_tab.cpp"
    break;

  case 738: /* spirv_instruction_qualifier_id: IDENTIFIER EQUAL INTCONSTANT  */
#line 4705 "MachineIndependent/glslang.y"
                                   {
        (yyval.interm.spirvInst) = parseContext.makeSpirvInstruction((yyvsp[-1].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[0].lex).i);
    }
#line 13469 "MachineIndependent/glslang_tab.cpp"
    break;


#line 13473 "MachineIndependent/glslang_tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (pParseContext, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, pParseContext);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, pParseContext);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (pParseContext, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, pParseContext);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, pParseContext);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 4709 "MachineIndependent/glslang.y"

