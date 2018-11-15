/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

#ifndef YY_YY_USERS_NEIL_CODE_GLSLANG_GLSLANG_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED
# define YY_YY_USERS_NEIL_CODE_GLSLANG_GLSLANG_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED
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
    PAYLOADNV = 338,
    PAYLOADINNV = 339,
    HITATTRNV = 340,
    CALLDATANV = 341,
    CALLDATAINNV = 342,
    SUBGROUPUNIFORM = 343,
    COHERENT = 344,
    VOLATILE = 345,
    RESTRICT = 346,
    READONLY = 347,
    WRITEONLY = 348,
    DEVICECOHERENT = 349,
    QUEUEFAMILYCOHERENT = 350,
    WORKGROUPCOHERENT = 351,
    SUBGROUPCOHERENT = 352,
    NONPRIVATE = 353,
    DVEC2 = 354,
    DVEC3 = 355,
    DVEC4 = 356,
    DMAT2 = 357,
    DMAT3 = 358,
    DMAT4 = 359,
    F16VEC2 = 360,
    F16VEC3 = 361,
    F16VEC4 = 362,
    F16MAT2 = 363,
    F16MAT3 = 364,
    F16MAT4 = 365,
    F32VEC2 = 366,
    F32VEC3 = 367,
    F32VEC4 = 368,
    F32MAT2 = 369,
    F32MAT3 = 370,
    F32MAT4 = 371,
    F64VEC2 = 372,
    F64VEC3 = 373,
    F64VEC4 = 374,
    F64MAT2 = 375,
    F64MAT3 = 376,
    F64MAT4 = 377,
    NOPERSPECTIVE = 378,
    FLAT = 379,
    SMOOTH = 380,
    LAYOUT = 381,
    EXPLICITINTERPAMD = 382,
    PERVERTEXNV = 383,
    PERPRIMITIVENV = 384,
    PERVIEWNV = 385,
    PERTASKNV = 386,
    MAT2X2 = 387,
    MAT2X3 = 388,
    MAT2X4 = 389,
    MAT3X2 = 390,
    MAT3X3 = 391,
    MAT3X4 = 392,
    MAT4X2 = 393,
    MAT4X3 = 394,
    MAT4X4 = 395,
    DMAT2X2 = 396,
    DMAT2X3 = 397,
    DMAT2X4 = 398,
    DMAT3X2 = 399,
    DMAT3X3 = 400,
    DMAT3X4 = 401,
    DMAT4X2 = 402,
    DMAT4X3 = 403,
    DMAT4X4 = 404,
    F16MAT2X2 = 405,
    F16MAT2X3 = 406,
    F16MAT2X4 = 407,
    F16MAT3X2 = 408,
    F16MAT3X3 = 409,
    F16MAT3X4 = 410,
    F16MAT4X2 = 411,
    F16MAT4X3 = 412,
    F16MAT4X4 = 413,
    F32MAT2X2 = 414,
    F32MAT2X3 = 415,
    F32MAT2X4 = 416,
    F32MAT3X2 = 417,
    F32MAT3X3 = 418,
    F32MAT3X4 = 419,
    F32MAT4X2 = 420,
    F32MAT4X3 = 421,
    F32MAT4X4 = 422,
    F64MAT2X2 = 423,
    F64MAT2X3 = 424,
    F64MAT2X4 = 425,
    F64MAT3X2 = 426,
    F64MAT3X3 = 427,
    F64MAT3X4 = 428,
    F64MAT4X2 = 429,
    F64MAT4X3 = 430,
    F64MAT4X4 = 431,
    ATOMIC_UINT = 432,
    ACCSTRUCTNV = 433,
    SAMPLER1D = 434,
    SAMPLER2D = 435,
    SAMPLER3D = 436,
    SAMPLERCUBE = 437,
    SAMPLER1DSHADOW = 438,
    SAMPLER2DSHADOW = 439,
    SAMPLERCUBESHADOW = 440,
    SAMPLER1DARRAY = 441,
    SAMPLER2DARRAY = 442,
    SAMPLER1DARRAYSHADOW = 443,
    SAMPLER2DARRAYSHADOW = 444,
    ISAMPLER1D = 445,
    ISAMPLER2D = 446,
    ISAMPLER3D = 447,
    ISAMPLERCUBE = 448,
    ISAMPLER1DARRAY = 449,
    ISAMPLER2DARRAY = 450,
    USAMPLER1D = 451,
    USAMPLER2D = 452,
    USAMPLER3D = 453,
    USAMPLERCUBE = 454,
    USAMPLER1DARRAY = 455,
    USAMPLER2DARRAY = 456,
    SAMPLER2DRECT = 457,
    SAMPLER2DRECTSHADOW = 458,
    ISAMPLER2DRECT = 459,
    USAMPLER2DRECT = 460,
    SAMPLERBUFFER = 461,
    ISAMPLERBUFFER = 462,
    USAMPLERBUFFER = 463,
    SAMPLERCUBEARRAY = 464,
    SAMPLERCUBEARRAYSHADOW = 465,
    ISAMPLERCUBEARRAY = 466,
    USAMPLERCUBEARRAY = 467,
    SAMPLER2DMS = 468,
    ISAMPLER2DMS = 469,
    USAMPLER2DMS = 470,
    SAMPLER2DMSARRAY = 471,
    ISAMPLER2DMSARRAY = 472,
    USAMPLER2DMSARRAY = 473,
    SAMPLEREXTERNALOES = 474,
    F16SAMPLER1D = 475,
    F16SAMPLER2D = 476,
    F16SAMPLER3D = 477,
    F16SAMPLER2DRECT = 478,
    F16SAMPLERCUBE = 479,
    F16SAMPLER1DARRAY = 480,
    F16SAMPLER2DARRAY = 481,
    F16SAMPLERCUBEARRAY = 482,
    F16SAMPLERBUFFER = 483,
    F16SAMPLER2DMS = 484,
    F16SAMPLER2DMSARRAY = 485,
    F16SAMPLER1DSHADOW = 486,
    F16SAMPLER2DSHADOW = 487,
    F16SAMPLER1DARRAYSHADOW = 488,
    F16SAMPLER2DARRAYSHADOW = 489,
    F16SAMPLER2DRECTSHADOW = 490,
    F16SAMPLERCUBESHADOW = 491,
    F16SAMPLERCUBEARRAYSHADOW = 492,
    SAMPLER = 493,
    SAMPLERSHADOW = 494,
    TEXTURE1D = 495,
    TEXTURE2D = 496,
    TEXTURE3D = 497,
    TEXTURECUBE = 498,
    TEXTURE1DARRAY = 499,
    TEXTURE2DARRAY = 500,
    ITEXTURE1D = 501,
    ITEXTURE2D = 502,
    ITEXTURE3D = 503,
    ITEXTURECUBE = 504,
    ITEXTURE1DARRAY = 505,
    ITEXTURE2DARRAY = 506,
    UTEXTURE1D = 507,
    UTEXTURE2D = 508,
    UTEXTURE3D = 509,
    UTEXTURECUBE = 510,
    UTEXTURE1DARRAY = 511,
    UTEXTURE2DARRAY = 512,
    TEXTURE2DRECT = 513,
    ITEXTURE2DRECT = 514,
    UTEXTURE2DRECT = 515,
    TEXTUREBUFFER = 516,
    ITEXTUREBUFFER = 517,
    UTEXTUREBUFFER = 518,
    TEXTURECUBEARRAY = 519,
    ITEXTURECUBEARRAY = 520,
    UTEXTURECUBEARRAY = 521,
    TEXTURE2DMS = 522,
    ITEXTURE2DMS = 523,
    UTEXTURE2DMS = 524,
    TEXTURE2DMSARRAY = 525,
    ITEXTURE2DMSARRAY = 526,
    UTEXTURE2DMSARRAY = 527,
    F16TEXTURE1D = 528,
    F16TEXTURE2D = 529,
    F16TEXTURE3D = 530,
    F16TEXTURE2DRECT = 531,
    F16TEXTURECUBE = 532,
    F16TEXTURE1DARRAY = 533,
    F16TEXTURE2DARRAY = 534,
    F16TEXTURECUBEARRAY = 535,
    F16TEXTUREBUFFER = 536,
    F16TEXTURE2DMS = 537,
    F16TEXTURE2DMSARRAY = 538,
    SUBPASSINPUT = 539,
    SUBPASSINPUTMS = 540,
    ISUBPASSINPUT = 541,
    ISUBPASSINPUTMS = 542,
    USUBPASSINPUT = 543,
    USUBPASSINPUTMS = 544,
    F16SUBPASSINPUT = 545,
    F16SUBPASSINPUTMS = 546,
    IMAGE1D = 547,
    IIMAGE1D = 548,
    UIMAGE1D = 549,
    IMAGE2D = 550,
    IIMAGE2D = 551,
    UIMAGE2D = 552,
    IMAGE3D = 553,
    IIMAGE3D = 554,
    UIMAGE3D = 555,
    IMAGE2DRECT = 556,
    IIMAGE2DRECT = 557,
    UIMAGE2DRECT = 558,
    IMAGECUBE = 559,
    IIMAGECUBE = 560,
    UIMAGECUBE = 561,
    IMAGEBUFFER = 562,
    IIMAGEBUFFER = 563,
    UIMAGEBUFFER = 564,
    IMAGE1DARRAY = 565,
    IIMAGE1DARRAY = 566,
    UIMAGE1DARRAY = 567,
    IMAGE2DARRAY = 568,
    IIMAGE2DARRAY = 569,
    UIMAGE2DARRAY = 570,
    IMAGECUBEARRAY = 571,
    IIMAGECUBEARRAY = 572,
    UIMAGECUBEARRAY = 573,
    IMAGE2DMS = 574,
    IIMAGE2DMS = 575,
    UIMAGE2DMS = 576,
    IMAGE2DMSARRAY = 577,
    IIMAGE2DMSARRAY = 578,
    UIMAGE2DMSARRAY = 579,
    F16IMAGE1D = 580,
    F16IMAGE2D = 581,
    F16IMAGE3D = 582,
    F16IMAGE2DRECT = 583,
    F16IMAGECUBE = 584,
    F16IMAGE1DARRAY = 585,
    F16IMAGE2DARRAY = 586,
    F16IMAGECUBEARRAY = 587,
    F16IMAGEBUFFER = 588,
    F16IMAGE2DMS = 589,
    F16IMAGE2DMSARRAY = 590,
    STRUCT = 591,
    VOID = 592,
    WHILE = 593,
    IDENTIFIER = 594,
    TYPE_NAME = 595,
    FLOATCONSTANT = 596,
    DOUBLECONSTANT = 597,
    INT16CONSTANT = 598,
    UINT16CONSTANT = 599,
    INT32CONSTANT = 600,
    UINT32CONSTANT = 601,
    INTCONSTANT = 602,
    UINTCONSTANT = 603,
    INT64CONSTANT = 604,
    UINT64CONSTANT = 605,
    BOOLCONSTANT = 606,
    FLOAT16CONSTANT = 607,
    LEFT_OP = 608,
    RIGHT_OP = 609,
    INC_OP = 610,
    DEC_OP = 611,
    LE_OP = 612,
    GE_OP = 613,
    EQ_OP = 614,
    NE_OP = 615,
    AND_OP = 616,
    OR_OP = 617,
    XOR_OP = 618,
    MUL_ASSIGN = 619,
    DIV_ASSIGN = 620,
    ADD_ASSIGN = 621,
    MOD_ASSIGN = 622,
    LEFT_ASSIGN = 623,
    RIGHT_ASSIGN = 624,
    AND_ASSIGN = 625,
    XOR_ASSIGN = 626,
    OR_ASSIGN = 627,
    SUB_ASSIGN = 628,
    LEFT_PAREN = 629,
    RIGHT_PAREN = 630,
    LEFT_BRACKET = 631,
    RIGHT_BRACKET = 632,
    LEFT_BRACE = 633,
    RIGHT_BRACE = 634,
    DOT = 635,
    COMMA = 636,
    COLON = 637,
    EQUAL = 638,
    SEMICOLON = 639,
    BANG = 640,
    DASH = 641,
    TILDE = 642,
    PLUS = 643,
    STAR = 644,
    SLASH = 645,
    PERCENT = 646,
    LEFT_ANGLE = 647,
    RIGHT_ANGLE = 648,
    VERTICAL_BAR = 649,
    CARET = 650,
    AMPERSAND = 651,
    QUESTION = 652,
    INVARIANT = 653,
    PRECISE = 654,
    HIGH_PRECISION = 655,
    MEDIUM_PRECISION = 656,
    LOW_PRECISION = 657,
    PRECISION = 658,
    PACKED = 659,
    RESOURCE = 660,
    SUPERP = 661
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 70 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1919  */

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

#line 496 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp.h" /* yacc.c:1919  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_USERS_NEIL_CODE_GLSLANG_GLSLANG_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */
