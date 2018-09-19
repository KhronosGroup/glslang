/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
    NONUNIFORM = 337,
    COHERENT = 338,
    VOLATILE = 339,
    RESTRICT = 340,
    READONLY = 341,
    WRITEONLY = 342,
    DEVICECOHERENT = 343,
    QUEUEFAMILYCOHERENT = 344,
    WORKGROUPCOHERENT = 345,
    SUBGROUPCOHERENT = 346,
    NONPRIVATE = 347,
    DVEC2 = 348,
    DVEC3 = 349,
    DVEC4 = 350,
    DMAT2 = 351,
    DMAT3 = 352,
    DMAT4 = 353,
    F16VEC2 = 354,
    F16VEC3 = 355,
    F16VEC4 = 356,
    F16MAT2 = 357,
    F16MAT3 = 358,
    F16MAT4 = 359,
    F32VEC2 = 360,
    F32VEC3 = 361,
    F32VEC4 = 362,
    F32MAT2 = 363,
    F32MAT3 = 364,
    F32MAT4 = 365,
    F64VEC2 = 366,
    F64VEC3 = 367,
    F64VEC4 = 368,
    F64MAT2 = 369,
    F64MAT3 = 370,
    F64MAT4 = 371,
    NOPERSPECTIVE = 372,
    FLAT = 373,
    SMOOTH = 374,
    LAYOUT = 375,
    EXPLICITINTERPAMD = 376,
    PERVERTEXNV = 377,
    PERPRIMITIVENV = 378,
    PERVIEWNV = 379,
    PERTASKNV = 380,
    MAT2X2 = 381,
    MAT2X3 = 382,
    MAT2X4 = 383,
    MAT3X2 = 384,
    MAT3X3 = 385,
    MAT3X4 = 386,
    MAT4X2 = 387,
    MAT4X3 = 388,
    MAT4X4 = 389,
    DMAT2X2 = 390,
    DMAT2X3 = 391,
    DMAT2X4 = 392,
    DMAT3X2 = 393,
    DMAT3X3 = 394,
    DMAT3X4 = 395,
    DMAT4X2 = 396,
    DMAT4X3 = 397,
    DMAT4X4 = 398,
    F16MAT2X2 = 399,
    F16MAT2X3 = 400,
    F16MAT2X4 = 401,
    F16MAT3X2 = 402,
    F16MAT3X3 = 403,
    F16MAT3X4 = 404,
    F16MAT4X2 = 405,
    F16MAT4X3 = 406,
    F16MAT4X4 = 407,
    F32MAT2X2 = 408,
    F32MAT2X3 = 409,
    F32MAT2X4 = 410,
    F32MAT3X2 = 411,
    F32MAT3X3 = 412,
    F32MAT3X4 = 413,
    F32MAT4X2 = 414,
    F32MAT4X3 = 415,
    F32MAT4X4 = 416,
    F64MAT2X2 = 417,
    F64MAT2X3 = 418,
    F64MAT2X4 = 419,
    F64MAT3X2 = 420,
    F64MAT3X3 = 421,
    F64MAT3X4 = 422,
    F64MAT4X2 = 423,
    F64MAT4X3 = 424,
    F64MAT4X4 = 425,
    ATOMIC_UINT = 426,
    SAMPLER1D = 427,
    SAMPLER2D = 428,
    SAMPLER3D = 429,
    SAMPLERCUBE = 430,
    SAMPLER1DSHADOW = 431,
    SAMPLER2DSHADOW = 432,
    SAMPLERCUBESHADOW = 433,
    SAMPLER1DARRAY = 434,
    SAMPLER2DARRAY = 435,
    SAMPLER1DARRAYSHADOW = 436,
    SAMPLER2DARRAYSHADOW = 437,
    ISAMPLER1D = 438,
    ISAMPLER2D = 439,
    ISAMPLER3D = 440,
    ISAMPLERCUBE = 441,
    ISAMPLER1DARRAY = 442,
    ISAMPLER2DARRAY = 443,
    USAMPLER1D = 444,
    USAMPLER2D = 445,
    USAMPLER3D = 446,
    USAMPLERCUBE = 447,
    USAMPLER1DARRAY = 448,
    USAMPLER2DARRAY = 449,
    SAMPLER2DRECT = 450,
    SAMPLER2DRECTSHADOW = 451,
    ISAMPLER2DRECT = 452,
    USAMPLER2DRECT = 453,
    SAMPLERBUFFER = 454,
    ISAMPLERBUFFER = 455,
    USAMPLERBUFFER = 456,
    SAMPLERCUBEARRAY = 457,
    SAMPLERCUBEARRAYSHADOW = 458,
    ISAMPLERCUBEARRAY = 459,
    USAMPLERCUBEARRAY = 460,
    SAMPLER2DMS = 461,
    ISAMPLER2DMS = 462,
    USAMPLER2DMS = 463,
    SAMPLER2DMSARRAY = 464,
    ISAMPLER2DMSARRAY = 465,
    USAMPLER2DMSARRAY = 466,
    SAMPLEREXTERNALOES = 467,
    F16SAMPLER1D = 468,
    F16SAMPLER2D = 469,
    F16SAMPLER3D = 470,
    F16SAMPLER2DRECT = 471,
    F16SAMPLERCUBE = 472,
    F16SAMPLER1DARRAY = 473,
    F16SAMPLER2DARRAY = 474,
    F16SAMPLERCUBEARRAY = 475,
    F16SAMPLERBUFFER = 476,
    F16SAMPLER2DMS = 477,
    F16SAMPLER2DMSARRAY = 478,
    F16SAMPLER1DSHADOW = 479,
    F16SAMPLER2DSHADOW = 480,
    F16SAMPLER1DARRAYSHADOW = 481,
    F16SAMPLER2DARRAYSHADOW = 482,
    F16SAMPLER2DRECTSHADOW = 483,
    F16SAMPLERCUBESHADOW = 484,
    F16SAMPLERCUBEARRAYSHADOW = 485,
    SAMPLER = 486,
    SAMPLERSHADOW = 487,
    TEXTURE1D = 488,
    TEXTURE2D = 489,
    TEXTURE3D = 490,
    TEXTURECUBE = 491,
    TEXTURE1DARRAY = 492,
    TEXTURE2DARRAY = 493,
    ITEXTURE1D = 494,
    ITEXTURE2D = 495,
    ITEXTURE3D = 496,
    ITEXTURECUBE = 497,
    ITEXTURE1DARRAY = 498,
    ITEXTURE2DARRAY = 499,
    UTEXTURE1D = 500,
    UTEXTURE2D = 501,
    UTEXTURE3D = 502,
    UTEXTURECUBE = 503,
    UTEXTURE1DARRAY = 504,
    UTEXTURE2DARRAY = 505,
    TEXTURE2DRECT = 506,
    ITEXTURE2DRECT = 507,
    UTEXTURE2DRECT = 508,
    TEXTUREBUFFER = 509,
    ITEXTUREBUFFER = 510,
    UTEXTUREBUFFER = 511,
    TEXTURECUBEARRAY = 512,
    ITEXTURECUBEARRAY = 513,
    UTEXTURECUBEARRAY = 514,
    TEXTURE2DMS = 515,
    ITEXTURE2DMS = 516,
    UTEXTURE2DMS = 517,
    TEXTURE2DMSARRAY = 518,
    ITEXTURE2DMSARRAY = 519,
    UTEXTURE2DMSARRAY = 520,
    F16TEXTURE1D = 521,
    F16TEXTURE2D = 522,
    F16TEXTURE3D = 523,
    F16TEXTURE2DRECT = 524,
    F16TEXTURECUBE = 525,
    F16TEXTURE1DARRAY = 526,
    F16TEXTURE2DARRAY = 527,
    F16TEXTURECUBEARRAY = 528,
    F16TEXTUREBUFFER = 529,
    F16TEXTURE2DMS = 530,
    F16TEXTURE2DMSARRAY = 531,
    SUBPASSINPUT = 532,
    SUBPASSINPUTMS = 533,
    ISUBPASSINPUT = 534,
    ISUBPASSINPUTMS = 535,
    USUBPASSINPUT = 536,
    USUBPASSINPUTMS = 537,
    F16SUBPASSINPUT = 538,
    F16SUBPASSINPUTMS = 539,
    IMAGE1D = 540,
    IIMAGE1D = 541,
    UIMAGE1D = 542,
    IMAGE2D = 543,
    IIMAGE2D = 544,
    UIMAGE2D = 545,
    IMAGE3D = 546,
    IIMAGE3D = 547,
    UIMAGE3D = 548,
    IMAGE2DRECT = 549,
    IIMAGE2DRECT = 550,
    UIMAGE2DRECT = 551,
    IMAGECUBE = 552,
    IIMAGECUBE = 553,
    UIMAGECUBE = 554,
    IMAGEBUFFER = 555,
    IIMAGEBUFFER = 556,
    UIMAGEBUFFER = 557,
    IMAGE1DARRAY = 558,
    IIMAGE1DARRAY = 559,
    UIMAGE1DARRAY = 560,
    IMAGE2DARRAY = 561,
    IIMAGE2DARRAY = 562,
    UIMAGE2DARRAY = 563,
    IMAGECUBEARRAY = 564,
    IIMAGECUBEARRAY = 565,
    UIMAGECUBEARRAY = 566,
    IMAGE2DMS = 567,
    IIMAGE2DMS = 568,
    UIMAGE2DMS = 569,
    IMAGE2DMSARRAY = 570,
    IIMAGE2DMSARRAY = 571,
    UIMAGE2DMSARRAY = 572,
    F16IMAGE1D = 573,
    F16IMAGE2D = 574,
    F16IMAGE3D = 575,
    F16IMAGE2DRECT = 576,
    F16IMAGECUBE = 577,
    F16IMAGE1DARRAY = 578,
    F16IMAGE2DARRAY = 579,
    F16IMAGECUBEARRAY = 580,
    F16IMAGEBUFFER = 581,
    F16IMAGE2DMS = 582,
    F16IMAGE2DMSARRAY = 583,
    STRUCT = 584,
    VOID = 585,
    WHILE = 586,
    IDENTIFIER = 587,
    TYPE_NAME = 588,
    FLOATCONSTANT = 589,
    DOUBLECONSTANT = 590,
    INT16CONSTANT = 591,
    UINT16CONSTANT = 592,
    INT32CONSTANT = 593,
    UINT32CONSTANT = 594,
    INTCONSTANT = 595,
    UINTCONSTANT = 596,
    INT64CONSTANT = 597,
    UINT64CONSTANT = 598,
    BOOLCONSTANT = 599,
    FLOAT16CONSTANT = 600,
    LEFT_OP = 601,
    RIGHT_OP = 602,
    INC_OP = 603,
    DEC_OP = 604,
    LE_OP = 605,
    GE_OP = 606,
    EQ_OP = 607,
    NE_OP = 608,
    AND_OP = 609,
    OR_OP = 610,
    XOR_OP = 611,
    MUL_ASSIGN = 612,
    DIV_ASSIGN = 613,
    ADD_ASSIGN = 614,
    MOD_ASSIGN = 615,
    LEFT_ASSIGN = 616,
    RIGHT_ASSIGN = 617,
    AND_ASSIGN = 618,
    XOR_ASSIGN = 619,
    OR_ASSIGN = 620,
    SUB_ASSIGN = 621,
    LEFT_PAREN = 622,
    RIGHT_PAREN = 623,
    LEFT_BRACKET = 624,
    RIGHT_BRACKET = 625,
    LEFT_BRACE = 626,
    RIGHT_BRACE = 627,
    DOT = 628,
    COMMA = 629,
    COLON = 630,
    EQUAL = 631,
    SEMICOLON = 632,
    BANG = 633,
    DASH = 634,
    TILDE = 635,
    PLUS = 636,
    STAR = 637,
    SLASH = 638,
    PERCENT = 639,
    LEFT_ANGLE = 640,
    RIGHT_ANGLE = 641,
    VERTICAL_BAR = 642,
    CARET = 643,
    AMPERSAND = 644,
    QUESTION = 645,
    INVARIANT = 646,
    PRECISE = 647,
    HIGH_PRECISION = 648,
    MEDIUM_PRECISION = 649,
    LOW_PRECISION = 650,
    PRECISION = 651,
    PACKED = 652,
    RESOURCE = 653,
    SUPERP = 654
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

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

#line 489 "MachineIndependent/glslang_tab.cpp.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */
