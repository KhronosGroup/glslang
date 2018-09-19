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
    MAT2X2 = 378,
    MAT2X3 = 379,
    MAT2X4 = 380,
    MAT3X2 = 381,
    MAT3X3 = 382,
    MAT3X4 = 383,
    MAT4X2 = 384,
    MAT4X3 = 385,
    MAT4X4 = 386,
    DMAT2X2 = 387,
    DMAT2X3 = 388,
    DMAT2X4 = 389,
    DMAT3X2 = 390,
    DMAT3X3 = 391,
    DMAT3X4 = 392,
    DMAT4X2 = 393,
    DMAT4X3 = 394,
    DMAT4X4 = 395,
    F16MAT2X2 = 396,
    F16MAT2X3 = 397,
    F16MAT2X4 = 398,
    F16MAT3X2 = 399,
    F16MAT3X3 = 400,
    F16MAT3X4 = 401,
    F16MAT4X2 = 402,
    F16MAT4X3 = 403,
    F16MAT4X4 = 404,
    F32MAT2X2 = 405,
    F32MAT2X3 = 406,
    F32MAT2X4 = 407,
    F32MAT3X2 = 408,
    F32MAT3X3 = 409,
    F32MAT3X4 = 410,
    F32MAT4X2 = 411,
    F32MAT4X3 = 412,
    F32MAT4X4 = 413,
    F64MAT2X2 = 414,
    F64MAT2X3 = 415,
    F64MAT2X4 = 416,
    F64MAT3X2 = 417,
    F64MAT3X3 = 418,
    F64MAT3X4 = 419,
    F64MAT4X2 = 420,
    F64MAT4X3 = 421,
    F64MAT4X4 = 422,
    ATOMIC_UINT = 423,
    SAMPLER1D = 424,
    SAMPLER2D = 425,
    SAMPLER3D = 426,
    SAMPLERCUBE = 427,
    SAMPLER1DSHADOW = 428,
    SAMPLER2DSHADOW = 429,
    SAMPLERCUBESHADOW = 430,
    SAMPLER1DARRAY = 431,
    SAMPLER2DARRAY = 432,
    SAMPLER1DARRAYSHADOW = 433,
    SAMPLER2DARRAYSHADOW = 434,
    ISAMPLER1D = 435,
    ISAMPLER2D = 436,
    ISAMPLER3D = 437,
    ISAMPLERCUBE = 438,
    ISAMPLER1DARRAY = 439,
    ISAMPLER2DARRAY = 440,
    USAMPLER1D = 441,
    USAMPLER2D = 442,
    USAMPLER3D = 443,
    USAMPLERCUBE = 444,
    USAMPLER1DARRAY = 445,
    USAMPLER2DARRAY = 446,
    SAMPLER2DRECT = 447,
    SAMPLER2DRECTSHADOW = 448,
    ISAMPLER2DRECT = 449,
    USAMPLER2DRECT = 450,
    SAMPLERBUFFER = 451,
    ISAMPLERBUFFER = 452,
    USAMPLERBUFFER = 453,
    SAMPLERCUBEARRAY = 454,
    SAMPLERCUBEARRAYSHADOW = 455,
    ISAMPLERCUBEARRAY = 456,
    USAMPLERCUBEARRAY = 457,
    SAMPLER2DMS = 458,
    ISAMPLER2DMS = 459,
    USAMPLER2DMS = 460,
    SAMPLER2DMSARRAY = 461,
    ISAMPLER2DMSARRAY = 462,
    USAMPLER2DMSARRAY = 463,
    SAMPLEREXTERNALOES = 464,
    F16SAMPLER1D = 465,
    F16SAMPLER2D = 466,
    F16SAMPLER3D = 467,
    F16SAMPLER2DRECT = 468,
    F16SAMPLERCUBE = 469,
    F16SAMPLER1DARRAY = 470,
    F16SAMPLER2DARRAY = 471,
    F16SAMPLERCUBEARRAY = 472,
    F16SAMPLERBUFFER = 473,
    F16SAMPLER2DMS = 474,
    F16SAMPLER2DMSARRAY = 475,
    F16SAMPLER1DSHADOW = 476,
    F16SAMPLER2DSHADOW = 477,
    F16SAMPLER1DARRAYSHADOW = 478,
    F16SAMPLER2DARRAYSHADOW = 479,
    F16SAMPLER2DRECTSHADOW = 480,
    F16SAMPLERCUBESHADOW = 481,
    F16SAMPLERCUBEARRAYSHADOW = 482,
    SAMPLER = 483,
    SAMPLERSHADOW = 484,
    TEXTURE1D = 485,
    TEXTURE2D = 486,
    TEXTURE3D = 487,
    TEXTURECUBE = 488,
    TEXTURE1DARRAY = 489,
    TEXTURE2DARRAY = 490,
    ITEXTURE1D = 491,
    ITEXTURE2D = 492,
    ITEXTURE3D = 493,
    ITEXTURECUBE = 494,
    ITEXTURE1DARRAY = 495,
    ITEXTURE2DARRAY = 496,
    UTEXTURE1D = 497,
    UTEXTURE2D = 498,
    UTEXTURE3D = 499,
    UTEXTURECUBE = 500,
    UTEXTURE1DARRAY = 501,
    UTEXTURE2DARRAY = 502,
    TEXTURE2DRECT = 503,
    ITEXTURE2DRECT = 504,
    UTEXTURE2DRECT = 505,
    TEXTUREBUFFER = 506,
    ITEXTUREBUFFER = 507,
    UTEXTUREBUFFER = 508,
    TEXTURECUBEARRAY = 509,
    ITEXTURECUBEARRAY = 510,
    UTEXTURECUBEARRAY = 511,
    TEXTURE2DMS = 512,
    ITEXTURE2DMS = 513,
    UTEXTURE2DMS = 514,
    TEXTURE2DMSARRAY = 515,
    ITEXTURE2DMSARRAY = 516,
    UTEXTURE2DMSARRAY = 517,
    F16TEXTURE1D = 518,
    F16TEXTURE2D = 519,
    F16TEXTURE3D = 520,
    F16TEXTURE2DRECT = 521,
    F16TEXTURECUBE = 522,
    F16TEXTURE1DARRAY = 523,
    F16TEXTURE2DARRAY = 524,
    F16TEXTURECUBEARRAY = 525,
    F16TEXTUREBUFFER = 526,
    F16TEXTURE2DMS = 527,
    F16TEXTURE2DMSARRAY = 528,
    SUBPASSINPUT = 529,
    SUBPASSINPUTMS = 530,
    ISUBPASSINPUT = 531,
    ISUBPASSINPUTMS = 532,
    USUBPASSINPUT = 533,
    USUBPASSINPUTMS = 534,
    F16SUBPASSINPUT = 535,
    F16SUBPASSINPUTMS = 536,
    IMAGE1D = 537,
    IIMAGE1D = 538,
    UIMAGE1D = 539,
    IMAGE2D = 540,
    IIMAGE2D = 541,
    UIMAGE2D = 542,
    IMAGE3D = 543,
    IIMAGE3D = 544,
    UIMAGE3D = 545,
    IMAGE2DRECT = 546,
    IIMAGE2DRECT = 547,
    UIMAGE2DRECT = 548,
    IMAGECUBE = 549,
    IIMAGECUBE = 550,
    UIMAGECUBE = 551,
    IMAGEBUFFER = 552,
    IIMAGEBUFFER = 553,
    UIMAGEBUFFER = 554,
    IMAGE1DARRAY = 555,
    IIMAGE1DARRAY = 556,
    UIMAGE1DARRAY = 557,
    IMAGE2DARRAY = 558,
    IIMAGE2DARRAY = 559,
    UIMAGE2DARRAY = 560,
    IMAGECUBEARRAY = 561,
    IIMAGECUBEARRAY = 562,
    UIMAGECUBEARRAY = 563,
    IMAGE2DMS = 564,
    IIMAGE2DMS = 565,
    UIMAGE2DMS = 566,
    IMAGE2DMSARRAY = 567,
    IIMAGE2DMSARRAY = 568,
    UIMAGE2DMSARRAY = 569,
    F16IMAGE1D = 570,
    F16IMAGE2D = 571,
    F16IMAGE3D = 572,
    F16IMAGE2DRECT = 573,
    F16IMAGECUBE = 574,
    F16IMAGE1DARRAY = 575,
    F16IMAGE2DARRAY = 576,
    F16IMAGECUBEARRAY = 577,
    F16IMAGEBUFFER = 578,
    F16IMAGE2DMS = 579,
    F16IMAGE2DMSARRAY = 580,
    STRUCT = 581,
    VOID = 582,
    WHILE = 583,
    IDENTIFIER = 584,
    TYPE_NAME = 585,
    FLOATCONSTANT = 586,
    DOUBLECONSTANT = 587,
    INT16CONSTANT = 588,
    UINT16CONSTANT = 589,
    INT32CONSTANT = 590,
    UINT32CONSTANT = 591,
    INTCONSTANT = 592,
    UINTCONSTANT = 593,
    INT64CONSTANT = 594,
    UINT64CONSTANT = 595,
    BOOLCONSTANT = 596,
    FLOAT16CONSTANT = 597,
    LEFT_OP = 598,
    RIGHT_OP = 599,
    INC_OP = 600,
    DEC_OP = 601,
    LE_OP = 602,
    GE_OP = 603,
    EQ_OP = 604,
    NE_OP = 605,
    AND_OP = 606,
    OR_OP = 607,
    XOR_OP = 608,
    MUL_ASSIGN = 609,
    DIV_ASSIGN = 610,
    ADD_ASSIGN = 611,
    MOD_ASSIGN = 612,
    LEFT_ASSIGN = 613,
    RIGHT_ASSIGN = 614,
    AND_ASSIGN = 615,
    XOR_ASSIGN = 616,
    OR_ASSIGN = 617,
    SUB_ASSIGN = 618,
    LEFT_PAREN = 619,
    RIGHT_PAREN = 620,
    LEFT_BRACKET = 621,
    RIGHT_BRACKET = 622,
    LEFT_BRACE = 623,
    RIGHT_BRACE = 624,
    DOT = 625,
    COMMA = 626,
    COLON = 627,
    EQUAL = 628,
    SEMICOLON = 629,
    BANG = 630,
    DASH = 631,
    TILDE = 632,
    PLUS = 633,
    STAR = 634,
    SLASH = 635,
    PERCENT = 636,
    LEFT_ANGLE = 637,
    RIGHT_ANGLE = 638,
    VERTICAL_BAR = 639,
    CARET = 640,
    AMPERSAND = 641,
    QUESTION = 642,
    INVARIANT = 643,
    PRECISE = 644,
    HIGH_PRECISION = 645,
    MEDIUM_PRECISION = 646,
    LOW_PRECISION = 647,
    PRECISION = 648,
    PACKED = 649,
    RESOURCE = 650,
    SUPERP = 651
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

#line 486 "MachineIndependent/glslang_tab.cpp.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */
