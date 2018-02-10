/* A Bison parser, made by GNU Bison 3.0.  */

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

#ifndef YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED
# define YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED
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
    FLOAT16_T = 260,
    FLOAT = 261,
    FLOAT32_T = 262,
    DOUBLE = 263,
    FLOAT64_T = 264,
    CONST = 265,
    BOOL = 266,
    INT = 267,
    UINT = 268,
    INT64_T = 269,
    UINT64_T = 270,
    INT32_T = 271,
    UINT32_T = 272,
    INT16_T = 273,
    UINT16_T = 274,
    INT8_T = 275,
    UINT8_T = 276,
    BREAK = 277,
    CONTINUE = 278,
    DO = 279,
    ELSE = 280,
    FOR = 281,
    IF = 282,
    DISCARD = 283,
    RETURN = 284,
    SWITCH = 285,
    CASE = 286,
    DEFAULT = 287,
    SUBROUTINE = 288,
    BVEC2 = 289,
    BVEC3 = 290,
    BVEC4 = 291,
    IVEC2 = 292,
    IVEC3 = 293,
    IVEC4 = 294,
    UVEC2 = 295,
    UVEC3 = 296,
    UVEC4 = 297,
    I64VEC2 = 298,
    I64VEC3 = 299,
    I64VEC4 = 300,
    U64VEC2 = 301,
    U64VEC3 = 302,
    U64VEC4 = 303,
    I32VEC2 = 304,
    I32VEC3 = 305,
    I32VEC4 = 306,
    U32VEC2 = 307,
    U32VEC3 = 308,
    U32VEC4 = 309,
    I16VEC2 = 310,
    I16VEC3 = 311,
    I16VEC4 = 312,
    U16VEC2 = 313,
    U16VEC3 = 314,
    U16VEC4 = 315,
    I8VEC2 = 316,
    I8VEC3 = 317,
    I8VEC4 = 318,
    U8VEC2 = 319,
    U8VEC3 = 320,
    U8VEC4 = 321,
    VEC2 = 322,
    VEC3 = 323,
    VEC4 = 324,
    MAT2 = 325,
    MAT3 = 326,
    MAT4 = 327,
    CENTROID = 328,
    IN = 329,
    OUT = 330,
    INOUT = 331,
    UNIFORM = 332,
    PATCH = 333,
    SAMPLE = 334,
    BUFFER = 335,
    SHARED = 336,
    COHERENT = 337,
    VOLATILE = 338,
    RESTRICT = 339,
    READONLY = 340,
    WRITEONLY = 341,
    DVEC2 = 342,
    DVEC3 = 343,
    DVEC4 = 344,
    DMAT2 = 345,
    DMAT3 = 346,
    DMAT4 = 347,
    F16VEC2 = 348,
    F16VEC3 = 349,
    F16VEC4 = 350,
    F16MAT2 = 351,
    F16MAT3 = 352,
    F16MAT4 = 353,
    F32VEC2 = 354,
    F32VEC3 = 355,
    F32VEC4 = 356,
    F32MAT2 = 357,
    F32MAT3 = 358,
    F32MAT4 = 359,
    F64VEC2 = 360,
    F64VEC3 = 361,
    F64VEC4 = 362,
    F64MAT2 = 363,
    F64MAT3 = 364,
    F64MAT4 = 365,
    NOPERSPECTIVE = 366,
    FLAT = 367,
    SMOOTH = 368,
    LAYOUT = 369,
    __EXPLICITINTERPAMD = 370,
    MAT2X2 = 371,
    MAT2X3 = 372,
    MAT2X4 = 373,
    MAT3X2 = 374,
    MAT3X3 = 375,
    MAT3X4 = 376,
    MAT4X2 = 377,
    MAT4X3 = 378,
    MAT4X4 = 379,
    DMAT2X2 = 380,
    DMAT2X3 = 381,
    DMAT2X4 = 382,
    DMAT3X2 = 383,
    DMAT3X3 = 384,
    DMAT3X4 = 385,
    DMAT4X2 = 386,
    DMAT4X3 = 387,
    DMAT4X4 = 388,
    F16MAT2X2 = 389,
    F16MAT2X3 = 390,
    F16MAT2X4 = 391,
    F16MAT3X2 = 392,
    F16MAT3X3 = 393,
    F16MAT3X4 = 394,
    F16MAT4X2 = 395,
    F16MAT4X3 = 396,
    F16MAT4X4 = 397,
    F32MAT2X2 = 398,
    F32MAT2X3 = 399,
    F32MAT2X4 = 400,
    F32MAT3X2 = 401,
    F32MAT3X3 = 402,
    F32MAT3X4 = 403,
    F32MAT4X2 = 404,
    F32MAT4X3 = 405,
    F32MAT4X4 = 406,
    F64MAT2X2 = 407,
    F64MAT2X3 = 408,
    F64MAT2X4 = 409,
    F64MAT3X2 = 410,
    F64MAT3X3 = 411,
    F64MAT3X4 = 412,
    F64MAT4X2 = 413,
    F64MAT4X3 = 414,
    F64MAT4X4 = 415,
    ATOMIC_UINT = 416,
    SAMPLER1D = 417,
    SAMPLER2D = 418,
    SAMPLER3D = 419,
    SAMPLERCUBE = 420,
    SAMPLER1DSHADOW = 421,
    SAMPLER2DSHADOW = 422,
    SAMPLERCUBESHADOW = 423,
    SAMPLER1DARRAY = 424,
    SAMPLER2DARRAY = 425,
    SAMPLER1DARRAYSHADOW = 426,
    SAMPLER2DARRAYSHADOW = 427,
    ISAMPLER1D = 428,
    ISAMPLER2D = 429,
    ISAMPLER3D = 430,
    ISAMPLERCUBE = 431,
    ISAMPLER1DARRAY = 432,
    ISAMPLER2DARRAY = 433,
    USAMPLER1D = 434,
    USAMPLER2D = 435,
    USAMPLER3D = 436,
    USAMPLERCUBE = 437,
    USAMPLER1DARRAY = 438,
    USAMPLER2DARRAY = 439,
    SAMPLER2DRECT = 440,
    SAMPLER2DRECTSHADOW = 441,
    ISAMPLER2DRECT = 442,
    USAMPLER2DRECT = 443,
    SAMPLERBUFFER = 444,
    ISAMPLERBUFFER = 445,
    USAMPLERBUFFER = 446,
    SAMPLERCUBEARRAY = 447,
    SAMPLERCUBEARRAYSHADOW = 448,
    ISAMPLERCUBEARRAY = 449,
    USAMPLERCUBEARRAY = 450,
    SAMPLER2DMS = 451,
    ISAMPLER2DMS = 452,
    USAMPLER2DMS = 453,
    SAMPLER2DMSARRAY = 454,
    ISAMPLER2DMSARRAY = 455,
    USAMPLER2DMSARRAY = 456,
    SAMPLEREXTERNALOES = 457,
    SAMPLER = 458,
    SAMPLERSHADOW = 459,
    TEXTURE1D = 460,
    TEXTURE2D = 461,
    TEXTURE3D = 462,
    TEXTURECUBE = 463,
    TEXTURE1DARRAY = 464,
    TEXTURE2DARRAY = 465,
    ITEXTURE1D = 466,
    ITEXTURE2D = 467,
    ITEXTURE3D = 468,
    ITEXTURECUBE = 469,
    ITEXTURE1DARRAY = 470,
    ITEXTURE2DARRAY = 471,
    UTEXTURE1D = 472,
    UTEXTURE2D = 473,
    UTEXTURE3D = 474,
    UTEXTURECUBE = 475,
    UTEXTURE1DARRAY = 476,
    UTEXTURE2DARRAY = 477,
    TEXTURE2DRECT = 478,
    ITEXTURE2DRECT = 479,
    UTEXTURE2DRECT = 480,
    TEXTUREBUFFER = 481,
    ITEXTUREBUFFER = 482,
    UTEXTUREBUFFER = 483,
    TEXTURECUBEARRAY = 484,
    ITEXTURECUBEARRAY = 485,
    UTEXTURECUBEARRAY = 486,
    TEXTURE2DMS = 487,
    ITEXTURE2DMS = 488,
    UTEXTURE2DMS = 489,
    TEXTURE2DMSARRAY = 490,
    ITEXTURE2DMSARRAY = 491,
    UTEXTURE2DMSARRAY = 492,
    SUBPASSINPUT = 493,
    SUBPASSINPUTMS = 494,
    ISUBPASSINPUT = 495,
    ISUBPASSINPUTMS = 496,
    USUBPASSINPUT = 497,
    USUBPASSINPUTMS = 498,
    IMAGE1D = 499,
    IIMAGE1D = 500,
    UIMAGE1D = 501,
    IMAGE2D = 502,
    IIMAGE2D = 503,
    UIMAGE2D = 504,
    IMAGE3D = 505,
    IIMAGE3D = 506,
    UIMAGE3D = 507,
    IMAGE2DRECT = 508,
    IIMAGE2DRECT = 509,
    UIMAGE2DRECT = 510,
    IMAGECUBE = 511,
    IIMAGECUBE = 512,
    UIMAGECUBE = 513,
    IMAGEBUFFER = 514,
    IIMAGEBUFFER = 515,
    UIMAGEBUFFER = 516,
    IMAGE1DARRAY = 517,
    IIMAGE1DARRAY = 518,
    UIMAGE1DARRAY = 519,
    IMAGE2DARRAY = 520,
    IIMAGE2DARRAY = 521,
    UIMAGE2DARRAY = 522,
    IMAGECUBEARRAY = 523,
    IIMAGECUBEARRAY = 524,
    UIMAGECUBEARRAY = 525,
    IMAGE2DMS = 526,
    IIMAGE2DMS = 527,
    UIMAGE2DMS = 528,
    IMAGE2DMSARRAY = 529,
    IIMAGE2DMSARRAY = 530,
    UIMAGE2DMSARRAY = 531,
    STRUCT = 532,
    VOID = 533,
    WHILE = 534,
    IDENTIFIER = 535,
    TYPE_NAME = 536,
    FLOATCONSTANT = 537,
    DOUBLECONSTANT = 538,
    INT16CONSTANT = 539,
    UINT16CONSTANT = 540,
    INT32CONSTANT = 541,
    UINT32CONSTANT = 542,
    INTCONSTANT = 543,
    UINTCONSTANT = 544,
    INT64CONSTANT = 545,
    UINT64CONSTANT = 546,
    BOOLCONSTANT = 547,
    FLOAT16CONSTANT = 548,
    LEFT_OP = 549,
    RIGHT_OP = 550,
    INC_OP = 551,
    DEC_OP = 552,
    LE_OP = 553,
    GE_OP = 554,
    EQ_OP = 555,
    NE_OP = 556,
    AND_OP = 557,
    OR_OP = 558,
    XOR_OP = 559,
    MUL_ASSIGN = 560,
    DIV_ASSIGN = 561,
    ADD_ASSIGN = 562,
    MOD_ASSIGN = 563,
    LEFT_ASSIGN = 564,
    RIGHT_ASSIGN = 565,
    AND_ASSIGN = 566,
    XOR_ASSIGN = 567,
    OR_ASSIGN = 568,
    SUB_ASSIGN = 569,
    LEFT_PAREN = 570,
    RIGHT_PAREN = 571,
    LEFT_BRACKET = 572,
    RIGHT_BRACKET = 573,
    LEFT_BRACE = 574,
    RIGHT_BRACE = 575,
    DOT = 576,
    COMMA = 577,
    COLON = 578,
    EQUAL = 579,
    SEMICOLON = 580,
    BANG = 581,
    DASH = 582,
    TILDE = 583,
    PLUS = 584,
    STAR = 585,
    SLASH = 586,
    PERCENT = 587,
    LEFT_ANGLE = 588,
    RIGHT_ANGLE = 589,
    VERTICAL_BAR = 590,
    CARET = 591,
    AMPERSAND = 592,
    QUESTION = 593,
    INVARIANT = 594,
    PRECISE = 595,
    HIGH_PRECISION = 596,
    MEDIUM_PRECISION = 597,
    LOW_PRECISION = 598,
    PRECISION = 599,
    PACKED = 600,
    RESOURCE = 601,
    SUPERP = 602
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 70 "MachineIndependent/glslang.y" /* yacc.c:1909  */

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
    } interm;

#line 437 "MachineIndependent/glslang_tab.cpp.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */
