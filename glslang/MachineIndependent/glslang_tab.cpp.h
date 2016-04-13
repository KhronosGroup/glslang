/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_GLSLANG_TAB_CPP_H_INCLUDED
# define YY_YY_GLSLANG_TAB_CPP_H_INCLUDED
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
    ATTRIBUTE = 258,
    VARYING = 259,
    CONST = 260,
    BOOL = 261,
    FLOAT = 262,
    DOUBLE = 263,
    INT = 264,
    UINT = 265,
    UINT64 = 266,
    INT64 = 267,
    BREAK = 268,
    CONTINUE = 269,
    DO = 270,
    ELSE = 271,
    FOR = 272,
    IF = 273,
    DISCARD = 274,
    RETURN = 275,
    SWITCH = 276,
    CASE = 277,
    DEFAULT = 278,
    SUBROUTINE = 279,
    BVEC2 = 280,
    BVEC3 = 281,
    BVEC4 = 282,
    IVEC2 = 283,
    IVEC3 = 284,
    IVEC4 = 285,
    UVEC2 = 286,
    UVEC3 = 287,
    UVEC4 = 288,
    VEC2 = 289,
    VEC3 = 290,
    VEC4 = 291,
    MAT2 = 292,
    MAT3 = 293,
    MAT4 = 294,
    CENTROID = 295,
    IN = 296,
    OUT = 297,
    INOUT = 298,
    UNIFORM = 299,
    PATCH = 300,
    SAMPLE = 301,
    BUFFER = 302,
    SHARED = 303,
    COHERENT = 304,
    VOLATILE = 305,
    RESTRICT = 306,
    READONLY = 307,
    WRITEONLY = 308,
    DVEC2 = 309,
    DVEC3 = 310,
    DVEC4 = 311,
    DMAT2 = 312,
    DMAT3 = 313,
    DMAT4 = 314,
    NOPERSPECTIVE = 315,
    FLAT = 316,
    SMOOTH = 317,
    LAYOUT = 318,
    MAT2X2 = 319,
    MAT2X3 = 320,
    MAT2X4 = 321,
    MAT3X2 = 322,
    MAT3X3 = 323,
    MAT3X4 = 324,
    MAT4X2 = 325,
    MAT4X3 = 326,
    MAT4X4 = 327,
    DMAT2X2 = 328,
    DMAT2X3 = 329,
    DMAT2X4 = 330,
    DMAT3X2 = 331,
    DMAT3X3 = 332,
    DMAT3X4 = 333,
    DMAT4X2 = 334,
    DMAT4X3 = 335,
    DMAT4X4 = 336,
    ATOMIC_UINT = 337,
    SAMPLER1D = 338,
    SAMPLER2D = 339,
    SAMPLER3D = 340,
    SAMPLERCUBE = 341,
    SAMPLER1DSHADOW = 342,
    SAMPLER2DSHADOW = 343,
    SAMPLERCUBESHADOW = 344,
    SAMPLER1DARRAY = 345,
    SAMPLER2DARRAY = 346,
    SAMPLER1DARRAYSHADOW = 347,
    SAMPLER2DARRAYSHADOW = 348,
    ISAMPLER1D = 349,
    ISAMPLER2D = 350,
    ISAMPLER3D = 351,
    ISAMPLERCUBE = 352,
    ISAMPLER1DARRAY = 353,
    ISAMPLER2DARRAY = 354,
    USAMPLER1D = 355,
    USAMPLER2D = 356,
    USAMPLER3D = 357,
    USAMPLERCUBE = 358,
    USAMPLER1DARRAY = 359,
    USAMPLER2DARRAY = 360,
    SAMPLER2DRECT = 361,
    SAMPLER2DRECTSHADOW = 362,
    ISAMPLER2DRECT = 363,
    USAMPLER2DRECT = 364,
    SAMPLERBUFFER = 365,
    ISAMPLERBUFFER = 366,
    USAMPLERBUFFER = 367,
    SAMPLERCUBEARRAY = 368,
    SAMPLERCUBEARRAYSHADOW = 369,
    ISAMPLERCUBEARRAY = 370,
    USAMPLERCUBEARRAY = 371,
    SAMPLER2DMS = 372,
    ISAMPLER2DMS = 373,
    USAMPLER2DMS = 374,
    SAMPLER2DMSARRAY = 375,
    ISAMPLER2DMSARRAY = 376,
    USAMPLER2DMSARRAY = 377,
    SAMPLEREXTERNALOES = 378,
    SAMPLER = 379,
    SAMPLERSHADOW = 380,
    TEXTURE1D = 381,
    TEXTURE2D = 382,
    TEXTURE3D = 383,
    TEXTURECUBE = 384,
    TEXTURE1DARRAY = 385,
    TEXTURE2DARRAY = 386,
    ITEXTURE1D = 387,
    ITEXTURE2D = 388,
    ITEXTURE3D = 389,
    ITEXTURECUBE = 390,
    ITEXTURE1DARRAY = 391,
    ITEXTURE2DARRAY = 392,
    UTEXTURE1D = 393,
    UTEXTURE2D = 394,
    UTEXTURE3D = 395,
    UTEXTURECUBE = 396,
    UTEXTURE1DARRAY = 397,
    UTEXTURE2DARRAY = 398,
    TEXTURE2DRECT = 399,
    ITEXTURE2DRECT = 400,
    UTEXTURE2DRECT = 401,
    TEXTUREBUFFER = 402,
    ITEXTUREBUFFER = 403,
    UTEXTUREBUFFER = 404,
    TEXTURECUBEARRAY = 405,
    ITEXTURECUBEARRAY = 406,
    UTEXTURECUBEARRAY = 407,
    TEXTURE2DMS = 408,
    ITEXTURE2DMS = 409,
    UTEXTURE2DMS = 410,
    TEXTURE2DMSARRAY = 411,
    ITEXTURE2DMSARRAY = 412,
    UTEXTURE2DMSARRAY = 413,
    SUBPASSINPUT = 414,
    SUBPASSINPUTMS = 415,
    ISUBPASSINPUT = 416,
    ISUBPASSINPUTMS = 417,
    USUBPASSINPUT = 418,
    USUBPASSINPUTMS = 419,
    IMAGE1D = 420,
    IIMAGE1D = 421,
    UIMAGE1D = 422,
    IMAGE2D = 423,
    IIMAGE2D = 424,
    UIMAGE2D = 425,
    IMAGE3D = 426,
    IIMAGE3D = 427,
    UIMAGE3D = 428,
    IMAGE2DRECT = 429,
    IIMAGE2DRECT = 430,
    UIMAGE2DRECT = 431,
    IMAGECUBE = 432,
    IIMAGECUBE = 433,
    UIMAGECUBE = 434,
    IMAGEBUFFER = 435,
    IIMAGEBUFFER = 436,
    UIMAGEBUFFER = 437,
    IMAGE1DARRAY = 438,
    IIMAGE1DARRAY = 439,
    UIMAGE1DARRAY = 440,
    IMAGE2DARRAY = 441,
    IIMAGE2DARRAY = 442,
    UIMAGE2DARRAY = 443,
    IMAGECUBEARRAY = 444,
    IIMAGECUBEARRAY = 445,
    UIMAGECUBEARRAY = 446,
    IMAGE2DMS = 447,
    IIMAGE2DMS = 448,
    UIMAGE2DMS = 449,
    IMAGE2DMSARRAY = 450,
    IIMAGE2DMSARRAY = 451,
    UIMAGE2DMSARRAY = 452,
    STRUCT = 453,
    VOID = 454,
    WHILE = 455,
    IDENTIFIER = 456,
    TYPE_NAME = 457,
    FLOATCONSTANT = 458,
    DOUBLECONSTANT = 459,
    INTCONSTANT = 460,
    UINTCONSTANT = 461,
    BOOLCONSTANT = 462,
    LEFT_OP = 463,
    RIGHT_OP = 464,
    INC_OP = 465,
    DEC_OP = 466,
    LE_OP = 467,
    GE_OP = 468,
    EQ_OP = 469,
    NE_OP = 470,
    AND_OP = 471,
    OR_OP = 472,
    XOR_OP = 473,
    MUL_ASSIGN = 474,
    DIV_ASSIGN = 475,
    ADD_ASSIGN = 476,
    MOD_ASSIGN = 477,
    LEFT_ASSIGN = 478,
    RIGHT_ASSIGN = 479,
    AND_ASSIGN = 480,
    XOR_ASSIGN = 481,
    OR_ASSIGN = 482,
    SUB_ASSIGN = 483,
    LEFT_PAREN = 484,
    RIGHT_PAREN = 485,
    LEFT_BRACKET = 486,
    RIGHT_BRACKET = 487,
    LEFT_BRACE = 488,
    RIGHT_BRACE = 489,
    DOT = 490,
    COMMA = 491,
    COLON = 492,
    EQUAL = 493,
    SEMICOLON = 494,
    BANG = 495,
    DASH = 496,
    TILDE = 497,
    PLUS = 498,
    STAR = 499,
    SLASH = 500,
    PERCENT = 501,
    LEFT_ANGLE = 502,
    RIGHT_ANGLE = 503,
    VERTICAL_BAR = 504,
    CARET = 505,
    AMPERSAND = 506,
    QUESTION = 507,
    INVARIANT = 508,
    PRECISE = 509,
    HIGH_PRECISION = 510,
    MEDIUM_PRECISION = 511,
    LOW_PRECISION = 512,
    PRECISION = 513,
    PACKED = 514,
    RESOURCE = 515,
    SUPERP = 516
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 66 "glslang.y" /* yacc.c:1909  */

    struct {
        glslang::TSourceLoc loc;
        union {
            glslang::TString *string;
            int i;
            unsigned int u;
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
    } interm;

#line 348 "glslang_tab.cpp.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_GLSLANG_TAB_CPP_H_INCLUDED  */
