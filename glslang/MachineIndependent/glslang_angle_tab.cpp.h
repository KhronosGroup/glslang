/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_MACHINEINDEPENDENT_GLSLANG_ANGLE_TAB_CPP_H_INCLUDED
# define YY_YY_MACHINEINDEPENDENT_GLSLANG_ANGLE_TAB_CPP_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CONST = 258,
    BOOL = 259,
    INT = 260,
    UINT = 261,
    FLOAT = 262,
    BVEC2 = 263,
    BVEC3 = 264,
    BVEC4 = 265,
    IVEC2 = 266,
    IVEC3 = 267,
    IVEC4 = 268,
    UVEC2 = 269,
    UVEC3 = 270,
    UVEC4 = 271,
    VEC2 = 272,
    VEC3 = 273,
    VEC4 = 274,
    MAT2 = 275,
    MAT3 = 276,
    MAT4 = 277,
    MAT2X2 = 278,
    MAT2X3 = 279,
    MAT2X4 = 280,
    MAT3X2 = 281,
    MAT3X3 = 282,
    MAT3X4 = 283,
    MAT4X2 = 284,
    MAT4X3 = 285,
    MAT4X4 = 286,
    SAMPLER2D = 287,
    SAMPLER3D = 288,
    SAMPLERCUBE = 289,
    SAMPLER2DSHADOW = 290,
    SAMPLERCUBESHADOW = 291,
    SAMPLER2DARRAY = 292,
    SAMPLER2DARRAYSHADOW = 293,
    ISAMPLER2D = 294,
    ISAMPLER3D = 295,
    ISAMPLERCUBE = 296,
    ISAMPLER2DARRAY = 297,
    USAMPLER2D = 298,
    USAMPLER3D = 299,
    USAMPLERCUBE = 300,
    USAMPLER2DARRAY = 301,
    SAMPLER = 302,
    SAMPLERSHADOW = 303,
    TEXTURE2D = 304,
    TEXTURE3D = 305,
    TEXTURECUBE = 306,
    TEXTURE2DARRAY = 307,
    ITEXTURE2D = 308,
    ITEXTURE3D = 309,
    ITEXTURECUBE = 310,
    ITEXTURE2DARRAY = 311,
    UTEXTURE2D = 312,
    UTEXTURE3D = 313,
    UTEXTURECUBE = 314,
    UTEXTURE2DARRAY = 315,
    ATTRIBUTE = 316,
    VARYING = 317,
    SAMPLERCUBEARRAY = 318,
    SAMPLERCUBEARRAYSHADOW = 319,
    ISAMPLERCUBEARRAY = 320,
    USAMPLERCUBEARRAY = 321,
    SAMPLER2DRECT = 322,
    SAMPLER2DRECTSHADOW = 323,
    ISAMPLER2DRECT = 324,
    USAMPLER2DRECT = 325,
    SAMPLERBUFFER = 326,
    ISAMPLERBUFFER = 327,
    USAMPLERBUFFER = 328,
    SAMPLER2DMS = 329,
    ISAMPLER2DMS = 330,
    USAMPLER2DMS = 331,
    SAMPLER2DMSARRAY = 332,
    ISAMPLER2DMSARRAY = 333,
    USAMPLER2DMSARRAY = 334,
    SAMPLEREXTERNALOES = 335,
    SAMPLEREXTERNAL2DY2YEXT = 336,
    IMAGE1D = 337,
    IIMAGE1D = 338,
    UIMAGE1D = 339,
    IMAGE2D = 340,
    IIMAGE2D = 341,
    UIMAGE2D = 342,
    IMAGE3D = 343,
    IIMAGE3D = 344,
    UIMAGE3D = 345,
    IMAGE2DRECT = 346,
    IIMAGE2DRECT = 347,
    UIMAGE2DRECT = 348,
    IMAGECUBE = 349,
    IIMAGECUBE = 350,
    UIMAGECUBE = 351,
    IMAGEBUFFER = 352,
    IIMAGEBUFFER = 353,
    UIMAGEBUFFER = 354,
    IMAGE1DARRAY = 355,
    IIMAGE1DARRAY = 356,
    UIMAGE1DARRAY = 357,
    IMAGE2DARRAY = 358,
    IIMAGE2DARRAY = 359,
    UIMAGE2DARRAY = 360,
    IMAGECUBEARRAY = 361,
    IIMAGECUBEARRAY = 362,
    UIMAGECUBEARRAY = 363,
    IMAGE2DMS = 364,
    IIMAGE2DMS = 365,
    UIMAGE2DMS = 366,
    IMAGE2DMSARRAY = 367,
    IIMAGE2DMSARRAY = 368,
    UIMAGE2DMSARRAY = 369,
    TEXTURECUBEARRAY = 370,
    ITEXTURECUBEARRAY = 371,
    UTEXTURECUBEARRAY = 372,
    TEXTURE1D = 373,
    ITEXTURE1D = 374,
    UTEXTURE1D = 375,
    TEXTURE1DARRAY = 376,
    ITEXTURE1DARRAY = 377,
    UTEXTURE1DARRAY = 378,
    TEXTURE2DRECT = 379,
    ITEXTURE2DRECT = 380,
    UTEXTURE2DRECT = 381,
    TEXTUREBUFFER = 382,
    ITEXTUREBUFFER = 383,
    UTEXTUREBUFFER = 384,
    TEXTURE2DMS = 385,
    ITEXTURE2DMS = 386,
    UTEXTURE2DMS = 387,
    TEXTURE2DMSARRAY = 388,
    ITEXTURE2DMSARRAY = 389,
    UTEXTURE2DMSARRAY = 390,
    LEFT_OP = 391,
    RIGHT_OP = 392,
    INC_OP = 393,
    DEC_OP = 394,
    LE_OP = 395,
    GE_OP = 396,
    EQ_OP = 397,
    NE_OP = 398,
    AND_OP = 399,
    OR_OP = 400,
    XOR_OP = 401,
    MUL_ASSIGN = 402,
    DIV_ASSIGN = 403,
    ADD_ASSIGN = 404,
    MOD_ASSIGN = 405,
    LEFT_ASSIGN = 406,
    RIGHT_ASSIGN = 407,
    AND_ASSIGN = 408,
    XOR_ASSIGN = 409,
    OR_ASSIGN = 410,
    SUB_ASSIGN = 411,
    STRING_LITERAL = 412,
    LEFT_PAREN = 413,
    RIGHT_PAREN = 414,
    LEFT_BRACKET = 415,
    RIGHT_BRACKET = 416,
    LEFT_BRACE = 417,
    RIGHT_BRACE = 418,
    DOT = 419,
    COMMA = 420,
    COLON = 421,
    EQUAL = 422,
    SEMICOLON = 423,
    BANG = 424,
    DASH = 425,
    TILDE = 426,
    PLUS = 427,
    STAR = 428,
    SLASH = 429,
    PERCENT = 430,
    LEFT_ANGLE = 431,
    RIGHT_ANGLE = 432,
    VERTICAL_BAR = 433,
    CARET = 434,
    AMPERSAND = 435,
    QUESTION = 436,
    INVARIANT = 437,
    HIGH_PRECISION = 438,
    MEDIUM_PRECISION = 439,
    LOW_PRECISION = 440,
    PRECISION = 441,
    PACKED = 442,
    RESOURCE = 443,
    SUPERP = 444,
    FLOATCONSTANT = 445,
    INTCONSTANT = 446,
    UINTCONSTANT = 447,
    BOOLCONSTANT = 448,
    IDENTIFIER = 449,
    TYPE_NAME = 450,
    CENTROID = 451,
    IN = 452,
    OUT = 453,
    INOUT = 454,
    STRUCT = 455,
    VOID = 456,
    WHILE = 457,
    BREAK = 458,
    CONTINUE = 459,
    DO = 460,
    ELSE = 461,
    FOR = 462,
    IF = 463,
    DISCARD = 464,
    RETURN = 465,
    SWITCH = 466,
    CASE = 467,
    DEFAULT = 468,
    UNIFORM = 469,
    SHARED = 470,
    BUFFER = 471,
    FLAT = 472,
    SMOOTH = 473,
    LAYOUT = 474,
    PATCH = 475,
    SAMPLE = 476,
    COHERENT = 477,
    VOLATILE = 478,
    RESTRICT = 479,
    READONLY = 480,
    WRITEONLY = 481,
    NOPERSPECTIVE = 482,
    PRECISE = 483
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 103 "MachineIndependent/glslang_angle.y"

    struct {
        glslang::TSourceLoc loc;
        union {
            glslang::TString *string;
            int i;
            unsigned int u;
            long long i64;
            unsigned long long u64;
            bool b;
            double d;
        };
        glslang::TSymbol* symbol;
    } lex;
    struct {
        glslang::TSourceLoc loc;
        glslang::TOperator op;
        union {
            TIntermNode* intermNode;
            glslang::TIntermNodePair nodePair;
            glslang::TIntermTyped* intermTypedNode;
            glslang::TAttributes* attributes;
        };
        union {
            glslang::TPublicType type;
            glslang::TFunction* function;
            glslang::TParameter param;
            glslang::TTypeLoc typeLine;
            glslang::TTypeList* typeList;
            glslang::TArraySizes* arraySizes;
            glslang::TIdentifierList* identifierList;
        };
        glslang::TArraySizes* typeParameters;
    } interm;

#line 322 "MachineIndependent/glslang_angle_tab.cpp.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_ANGLE_TAB_CPP_H_INCLUDED  */
