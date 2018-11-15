/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 42 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:339  */


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


#line 92 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "glslang_tab.cpp.h".  */
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
#line 70 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:355  */

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

#line 574 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_USERS_NEIL_CODE_GLSLANG_GLSLANG_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 105 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:358  */


/* windows only pragma */
#ifdef _MSC_VER
    #pragma warning(disable : 4065)
    #pragma warning(disable : 4127)
    #pragma warning(disable : 4244)
#endif

#define parseContext (*pParseContext)
#define yyerror(context, msg) context->parserError(msg)

extern int yylex(YYSTYPE*, TParseContext&);


#line 605 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  383
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   9381

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  407
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  108
/* YYNRULES -- Number of rules.  */
#define YYNRULES  574
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  716

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   661

#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
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
     405,   406
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   295,   295,   301,   304,   308,   312,   315,   319,   323,
     327,   331,   335,   338,   342,   346,   349,   357,   360,   363,
     366,   369,   374,   382,   389,   396,   402,   406,   413,   416,
     422,   429,   439,   447,   452,   479,   484,   492,   498,   502,
     506,   526,   527,   528,   529,   535,   536,   541,   546,   555,
     556,   561,   569,   570,   576,   585,   586,   591,   596,   601,
     609,   610,   618,   629,   630,   639,   640,   649,   650,   659,
     660,   668,   669,   677,   678,   686,   687,   687,   705,   706,
     723,   727,   731,   735,   740,   744,   748,   752,   756,   760,
     764,   771,   774,   785,   792,   797,   802,   810,   814,   818,
     822,   827,   832,   841,   841,   852,   856,   863,   870,   873,
     880,   888,   908,   931,   946,   971,   982,   992,  1002,  1012,
    1021,  1024,  1028,  1032,  1037,  1045,  1050,  1055,  1060,  1065,
    1074,  1085,  1112,  1121,  1128,  1135,  1146,  1155,  1165,  1177,
    1186,  1198,  1204,  1207,  1214,  1218,  1222,  1230,  1239,  1242,
    1253,  1256,  1259,  1263,  1267,  1271,  1275,  1278,  1284,  1288,
    1300,  1314,  1319,  1325,  1331,  1338,  1344,  1349,  1354,  1359,
    1369,  1379,  1389,  1399,  1408,  1420,  1424,  1429,  1434,  1439,
    1444,  1449,  1453,  1457,  1461,  1465,  1471,  1480,  1487,  1494,
    1497,  1505,  1509,  1518,  1523,  1531,  1535,  1545,  1549,  1553,
    1558,  1563,  1568,  1573,  1577,  1582,  1587,  1592,  1597,  1602,
    1607,  1612,  1617,  1622,  1626,  1631,  1636,  1641,  1647,  1653,
    1659,  1665,  1671,  1677,  1683,  1689,  1695,  1701,  1707,  1713,
    1718,  1723,  1728,  1733,  1738,  1743,  1749,  1755,  1761,  1767,
    1773,  1779,  1785,  1791,  1797,  1803,  1809,  1815,  1821,  1827,
    1833,  1839,  1845,  1851,  1857,  1863,  1869,  1875,  1881,  1887,
    1893,  1899,  1905,  1910,  1915,  1920,  1925,  1930,  1935,  1940,
    1945,  1950,  1955,  1960,  1965,  1971,  1977,  1983,  1989,  1995,
    2001,  2007,  2013,  2019,  2025,  2031,  2037,  2043,  2049,  2055,
    2061,  2067,  2073,  2079,  2085,  2091,  2097,  2103,  2109,  2115,
    2121,  2127,  2133,  2139,  2145,  2151,  2157,  2163,  2169,  2175,
    2181,  2187,  2193,  2199,  2205,  2211,  2217,  2223,  2229,  2235,
    2241,  2247,  2253,  2259,  2264,  2269,  2274,  2279,  2284,  2289,
    2294,  2299,  2304,  2309,  2314,  2319,  2324,  2329,  2337,  2345,
    2353,  2361,  2369,  2377,  2385,  2393,  2401,  2409,  2417,  2425,
    2433,  2438,  2443,  2448,  2453,  2458,  2463,  2468,  2473,  2478,
    2483,  2488,  2493,  2498,  2503,  2508,  2513,  2521,  2529,  2534,
    2539,  2544,  2552,  2557,  2562,  2567,  2575,  2580,  2585,  2590,
    2598,  2603,  2608,  2613,  2618,  2623,  2631,  2636,  2644,  2649,
    2657,  2662,  2670,  2675,  2683,  2688,  2696,  2701,  2709,  2714,
    2719,  2724,  2729,  2734,  2739,  2744,  2749,  2754,  2759,  2764,
    2769,  2774,  2779,  2784,  2792,  2797,  2802,  2807,  2815,  2820,
    2825,  2830,  2838,  2843,  2848,  2853,  2861,  2866,  2871,  2876,
    2884,  2889,  2894,  2899,  2907,  2912,  2917,  2922,  2930,  2935,
    2940,  2945,  2953,  2958,  2963,  2968,  2976,  2981,  2986,  2991,
    2999,  3004,  3009,  3014,  3022,  3027,  3032,  3037,  3045,  3050,
    3055,  3060,  3068,  3073,  3078,  3083,  3091,  3096,  3101,  3106,
    3114,  3119,  3124,  3130,  3136,  3142,  3151,  3160,  3166,  3172,
    3178,  3184,  3189,  3205,  3210,  3215,  3223,  3223,  3234,  3234,
    3244,  3247,  3260,  3282,  3309,  3313,  3319,  3324,  3335,  3338,
    3344,  3353,  3356,  3362,  3366,  3367,  3373,  3374,  3375,  3376,
    3377,  3378,  3379,  3383,  3384,  3388,  3384,  3400,  3401,  3405,
    3405,  3412,  3412,  3426,  3429,  3437,  3445,  3456,  3457,  3461,
    3464,  3470,  3477,  3481,  3489,  3493,  3506,  3509,  3515,  3515,
    3535,  3538,  3544,  3556,  3568,  3571,  3577,  3577,  3592,  3592,
    3608,  3608,  3629,  3632,  3638,  3641,  3647,  3651,  3658,  3663,
    3668,  3675,  3678,  3687,  3691,  3700,  3703,  3706,  3714,  3714,
    3736,  3742,  3745,  3750,  3753
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ATTRIBUTE", "VARYING", "FLOAT16_T",
  "FLOAT", "FLOAT32_T", "DOUBLE", "FLOAT64_T", "CONST", "BOOL", "INT",
  "UINT", "INT64_T", "UINT64_T", "INT32_T", "UINT32_T", "INT16_T",
  "UINT16_T", "INT8_T", "UINT8_T", "BREAK", "CONTINUE", "DO", "ELSE",
  "FOR", "IF", "DISCARD", "RETURN", "SWITCH", "CASE", "DEFAULT",
  "SUBROUTINE", "BVEC2", "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4",
  "UVEC2", "UVEC3", "UVEC4", "I64VEC2", "I64VEC3", "I64VEC4", "U64VEC2",
  "U64VEC3", "U64VEC4", "I32VEC2", "I32VEC3", "I32VEC4", "U32VEC2",
  "U32VEC3", "U32VEC4", "I16VEC2", "I16VEC3", "I16VEC4", "U16VEC2",
  "U16VEC3", "U16VEC4", "I8VEC2", "I8VEC3", "I8VEC4", "U8VEC2", "U8VEC3",
  "U8VEC4", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4", "CENTROID",
  "IN", "OUT", "INOUT", "UNIFORM", "PATCH", "SAMPLE", "BUFFER", "SHARED",
  "NONUNIFORM", "PAYLOADNV", "PAYLOADINNV", "HITATTRNV", "CALLDATANV",
  "CALLDATAINNV", "SUBGROUPUNIFORM", "COHERENT", "VOLATILE", "RESTRICT",
  "READONLY", "WRITEONLY", "DEVICECOHERENT", "QUEUEFAMILYCOHERENT",
  "WORKGROUPCOHERENT", "SUBGROUPCOHERENT", "NONPRIVATE", "DVEC2", "DVEC3",
  "DVEC4", "DMAT2", "DMAT3", "DMAT4", "F16VEC2", "F16VEC3", "F16VEC4",
  "F16MAT2", "F16MAT3", "F16MAT4", "F32VEC2", "F32VEC3", "F32VEC4",
  "F32MAT2", "F32MAT3", "F32MAT4", "F64VEC2", "F64VEC3", "F64VEC4",
  "F64MAT2", "F64MAT3", "F64MAT4", "NOPERSPECTIVE", "FLAT", "SMOOTH",
  "LAYOUT", "EXPLICITINTERPAMD", "PERVERTEXNV", "PERPRIMITIVENV",
  "PERVIEWNV", "PERTASKNV", "MAT2X2", "MAT2X3", "MAT2X4", "MAT3X2",
  "MAT3X3", "MAT3X4", "MAT4X2", "MAT4X3", "MAT4X4", "DMAT2X2", "DMAT2X3",
  "DMAT2X4", "DMAT3X2", "DMAT3X3", "DMAT3X4", "DMAT4X2", "DMAT4X3",
  "DMAT4X4", "F16MAT2X2", "F16MAT2X3", "F16MAT2X4", "F16MAT3X2",
  "F16MAT3X3", "F16MAT3X4", "F16MAT4X2", "F16MAT4X3", "F16MAT4X4",
  "F32MAT2X2", "F32MAT2X3", "F32MAT2X4", "F32MAT3X2", "F32MAT3X3",
  "F32MAT3X4", "F32MAT4X2", "F32MAT4X3", "F32MAT4X4", "F64MAT2X2",
  "F64MAT2X3", "F64MAT2X4", "F64MAT3X2", "F64MAT3X3", "F64MAT3X4",
  "F64MAT4X2", "F64MAT4X3", "F64MAT4X4", "ATOMIC_UINT", "ACCSTRUCTNV",
  "SAMPLER1D", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE", "SAMPLER1DSHADOW",
  "SAMPLER2DSHADOW", "SAMPLERCUBESHADOW", "SAMPLER1DARRAY",
  "SAMPLER2DARRAY", "SAMPLER1DARRAYSHADOW", "SAMPLER2DARRAYSHADOW",
  "ISAMPLER1D", "ISAMPLER2D", "ISAMPLER3D", "ISAMPLERCUBE",
  "ISAMPLER1DARRAY", "ISAMPLER2DARRAY", "USAMPLER1D", "USAMPLER2D",
  "USAMPLER3D", "USAMPLERCUBE", "USAMPLER1DARRAY", "USAMPLER2DARRAY",
  "SAMPLER2DRECT", "SAMPLER2DRECTSHADOW", "ISAMPLER2DRECT",
  "USAMPLER2DRECT", "SAMPLERBUFFER", "ISAMPLERBUFFER", "USAMPLERBUFFER",
  "SAMPLERCUBEARRAY", "SAMPLERCUBEARRAYSHADOW", "ISAMPLERCUBEARRAY",
  "USAMPLERCUBEARRAY", "SAMPLER2DMS", "ISAMPLER2DMS", "USAMPLER2DMS",
  "SAMPLER2DMSARRAY", "ISAMPLER2DMSARRAY", "USAMPLER2DMSARRAY",
  "SAMPLEREXTERNALOES", "F16SAMPLER1D", "F16SAMPLER2D", "F16SAMPLER3D",
  "F16SAMPLER2DRECT", "F16SAMPLERCUBE", "F16SAMPLER1DARRAY",
  "F16SAMPLER2DARRAY", "F16SAMPLERCUBEARRAY", "F16SAMPLERBUFFER",
  "F16SAMPLER2DMS", "F16SAMPLER2DMSARRAY", "F16SAMPLER1DSHADOW",
  "F16SAMPLER2DSHADOW", "F16SAMPLER1DARRAYSHADOW",
  "F16SAMPLER2DARRAYSHADOW", "F16SAMPLER2DRECTSHADOW",
  "F16SAMPLERCUBESHADOW", "F16SAMPLERCUBEARRAYSHADOW", "SAMPLER",
  "SAMPLERSHADOW", "TEXTURE1D", "TEXTURE2D", "TEXTURE3D", "TEXTURECUBE",
  "TEXTURE1DARRAY", "TEXTURE2DARRAY", "ITEXTURE1D", "ITEXTURE2D",
  "ITEXTURE3D", "ITEXTURECUBE", "ITEXTURE1DARRAY", "ITEXTURE2DARRAY",
  "UTEXTURE1D", "UTEXTURE2D", "UTEXTURE3D", "UTEXTURECUBE",
  "UTEXTURE1DARRAY", "UTEXTURE2DARRAY", "TEXTURE2DRECT", "ITEXTURE2DRECT",
  "UTEXTURE2DRECT", "TEXTUREBUFFER", "ITEXTUREBUFFER", "UTEXTUREBUFFER",
  "TEXTURECUBEARRAY", "ITEXTURECUBEARRAY", "UTEXTURECUBEARRAY",
  "TEXTURE2DMS", "ITEXTURE2DMS", "UTEXTURE2DMS", "TEXTURE2DMSARRAY",
  "ITEXTURE2DMSARRAY", "UTEXTURE2DMSARRAY", "F16TEXTURE1D", "F16TEXTURE2D",
  "F16TEXTURE3D", "F16TEXTURE2DRECT", "F16TEXTURECUBE",
  "F16TEXTURE1DARRAY", "F16TEXTURE2DARRAY", "F16TEXTURECUBEARRAY",
  "F16TEXTUREBUFFER", "F16TEXTURE2DMS", "F16TEXTURE2DMSARRAY",
  "SUBPASSINPUT", "SUBPASSINPUTMS", "ISUBPASSINPUT", "ISUBPASSINPUTMS",
  "USUBPASSINPUT", "USUBPASSINPUTMS", "F16SUBPASSINPUT",
  "F16SUBPASSINPUTMS", "IMAGE1D", "IIMAGE1D", "UIMAGE1D", "IMAGE2D",
  "IIMAGE2D", "UIMAGE2D", "IMAGE3D", "IIMAGE3D", "UIMAGE3D", "IMAGE2DRECT",
  "IIMAGE2DRECT", "UIMAGE2DRECT", "IMAGECUBE", "IIMAGECUBE", "UIMAGECUBE",
  "IMAGEBUFFER", "IIMAGEBUFFER", "UIMAGEBUFFER", "IMAGE1DARRAY",
  "IIMAGE1DARRAY", "UIMAGE1DARRAY", "IMAGE2DARRAY", "IIMAGE2DARRAY",
  "UIMAGE2DARRAY", "IMAGECUBEARRAY", "IIMAGECUBEARRAY", "UIMAGECUBEARRAY",
  "IMAGE2DMS", "IIMAGE2DMS", "UIMAGE2DMS", "IMAGE2DMSARRAY",
  "IIMAGE2DMSARRAY", "UIMAGE2DMSARRAY", "F16IMAGE1D", "F16IMAGE2D",
  "F16IMAGE3D", "F16IMAGE2DRECT", "F16IMAGECUBE", "F16IMAGE1DARRAY",
  "F16IMAGE2DARRAY", "F16IMAGECUBEARRAY", "F16IMAGEBUFFER", "F16IMAGE2DMS",
  "F16IMAGE2DMSARRAY", "STRUCT", "VOID", "WHILE", "IDENTIFIER",
  "TYPE_NAME", "FLOATCONSTANT", "DOUBLECONSTANT", "INT16CONSTANT",
  "UINT16CONSTANT", "INT32CONSTANT", "UINT32CONSTANT", "INTCONSTANT",
  "UINTCONSTANT", "INT64CONSTANT", "UINT64CONSTANT", "BOOLCONSTANT",
  "FLOAT16CONSTANT", "LEFT_OP", "RIGHT_OP", "INC_OP", "DEC_OP", "LE_OP",
  "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "XOR_OP", "MUL_ASSIGN",
  "DIV_ASSIGN", "ADD_ASSIGN", "MOD_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "SUB_ASSIGN", "LEFT_PAREN",
  "RIGHT_PAREN", "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_BRACE",
  "RIGHT_BRACE", "DOT", "COMMA", "COLON", "EQUAL", "SEMICOLON", "BANG",
  "DASH", "TILDE", "PLUS", "STAR", "SLASH", "PERCENT", "LEFT_ANGLE",
  "RIGHT_ANGLE", "VERTICAL_BAR", "CARET", "AMPERSAND", "QUESTION",
  "INVARIANT", "PRECISE", "HIGH_PRECISION", "MEDIUM_PRECISION",
  "LOW_PRECISION", "PRECISION", "PACKED", "RESOURCE", "SUPERP", "$accept",
  "variable_identifier", "primary_expression", "postfix_expression",
  "integer_expression", "function_call", "function_call_or_method",
  "function_call_generic", "function_call_header_no_parameters",
  "function_call_header_with_parameters", "function_call_header",
  "function_identifier", "unary_expression", "unary_operator",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_xor_expression",
  "logical_or_expression", "conditional_expression", "$@1",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "block_structure", "$@2",
  "identifier_list", "function_prototype", "function_declarator",
  "function_header_with_parameters", "function_header",
  "parameter_declarator", "parameter_declaration",
  "parameter_type_specifier", "init_declarator_list", "single_declaration",
  "fully_specified_type", "invariant_qualifier", "interpolation_qualifier",
  "layout_qualifier", "layout_qualifier_id_list", "layout_qualifier_id",
  "precise_qualifier", "type_qualifier", "single_type_qualifier",
  "storage_qualifier", "non_uniform_qualifier",
  "subgroup_uniform_qualifier", "type_name_list", "type_specifier",
  "array_specifier", "type_specifier_nonarray", "precision_qualifier",
  "struct_specifier", "$@3", "$@4", "struct_declaration_list",
  "struct_declaration", "struct_declarator_list", "struct_declarator",
  "initializer", "initializer_list", "declaration_statement", "statement",
  "simple_statement", "compound_statement", "$@5", "$@6",
  "statement_no_new_scope", "statement_scoped", "$@7", "$@8",
  "compound_statement_no_new_scope", "statement_list",
  "expression_statement", "selection_statement",
  "selection_statement_nonattributed", "selection_rest_statement",
  "condition", "switch_statement", "switch_statement_nonattributed", "$@9",
  "switch_statement_list", "case_label", "iteration_statement",
  "iteration_statement_nonattributed", "$@10", "$@11", "$@12",
  "for_init_statement", "conditionopt", "for_rest_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "function_definition", "$@13", "attribute", "attribute_list",
  "single_attribute", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
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
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,   636,   637,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
     655,   656,   657,   658,   659,   660,   661
};
# endif

#define YYPACT_NINF -658

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-658)))

#define YYTABLE_NINF -520

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    3583,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -348,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -277,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -317,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -263,  -658,  -318,  -315,  -276,  -268,  5984,  -343,
    -658,  -217,  -658,  -658,  -658,  -658,  4384,  -658,  -658,  -658,
    -658,  -658,  -271,  -658,  -658,   776,  -658,  -658,  -211,   -69,
    -232,  -658,  9041,  -345,  -658,  -658,  -226,  -658,  5984,  -658,
    -658,  -658,  5984,  -186,  -185,  -658,  -340,  -305,  -658,  -658,
    -658,  6737,  -221,  -658,  -658,  -658,  -310,  -658,  -227,  -300,
    -658,  -658,  5984,  -223,  -658,  -339,  1177,  -658,  -658,  -658,
    -658,  -271,  -341,  -658,  7121,  -328,  -658,  -181,  -658,  -330,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  8273,  8273,  8273,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -306,  -658,  -658,  -658,  -212,  -298,  8657,
    -210,  -658,  8273,  -249,  -324,  -234,  -334,  -233,  -220,  -218,
    -216,  -182,  -183,  -337,  -196,  -658,  -658,  -658,  7505,  -658,
    -156,  8273,  -658,   -69,  5984,  5984,  -155,  4784,  -658,  -658,
    -658,  -197,  -195,  -658,  -188,  -184,  -193,  7889,  -179,  8273,
    -194,  -178,  -177,  -187,  -658,  -658,  -198,  -658,  -658,  -275,
    -658,  -315,  -172,  -171,  -170,  -658,  -658,  -658,  -658,  1578,
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,   -19,
    -221,  7121,  -320,  7121,  -658,  -658,  7121,  5984,  -658,  -146,
    -658,  -658,  -658,  -297,  -658,  -658,  8273,  -142,  -658,  -658,
    8273,  -168,  -658,  -658,  -658,  8273,  8273,  8273,  8273,  8273,
    8273,  8273,  8273,  8273,  8273,  8273,  8273,  8273,  8273,  8273,
    8273,  8273,  8273,  8273,  -658,  -658,  -658,  -169,  -658,  -658,
    -658,  -658,  5184,  -155,  -271,  -274,  -658,  -658,  -658,  -658,
    -658,  1979,  -658,  8273,  -658,  -658,  -269,  8273,  -251,  -658,
    -658,  -134,  -658,  1979,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  -658,  8273,  8273,  -658,  -658,  -658,
    -658,  -658,  -658,  -658,  7121,  -658,  -288,  -658,  5584,  -658,
    -658,  -167,  -165,  -658,  -658,  -658,  -658,  -658,  -249,  -249,
    -324,  -324,  -234,  -234,  -234,  -234,  -334,  -334,  -233,  -220,
    -218,  -216,  -182,  -183,  8273,  -658,  -658,  -267,  -221,  -155,
    -658,  -127,  3182,  -295,  -658,  -287,  -658,  3984,  -162,  -285,
    -658,  1979,  -658,  -658,  -658,  -658,  6353,  -658,  -658,  -248,
    -658,  -658,  -161,  -658,  -658,  3984,  -164,  -658,  -165,  -122,
    5984,  -157,  8273,  -158,  -134,  -159,  -658,  -658,  8273,  8273,
    -658,  -163,  -153,   198,  -154,  2781,  -658,  -152,  -151,  2380,
    -147,  -658,  -658,  -658,  -658,  -286,  8273,  2380,  -164,  -658,
    -658,  1979,  7121,  -658,  -658,  -658,  -658,  -150,  -165,  -658,
    -658,  1979,  -149,  -658,  -658,  -658
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   159,   160,   200,   198,   201,   199,   202,   158,   213,
     203,   204,   211,   212,   209,   210,   207,   208,   205,   206,
     185,   229,   230,   231,   232,   233,   234,   247,   248,   249,
     244,   245,   246,   259,   260,   261,   241,   242,   243,   256,
     257,   258,   238,   239,   240,   253,   254,   255,   235,   236,
     237,   250,   251,   252,   214,   215,   216,   262,   263,   264,
     164,   162,   163,   161,   167,   165,   166,   168,   174,   187,
     170,   171,   169,   172,   173,   188,   175,   181,   182,   183,
     184,   176,   177,   178,   179,   180,   217,   218,   219,   274,
     275,   276,   220,   221,   222,   286,   287,   288,   223,   224,
     225,   298,   299,   300,   226,   227,   228,   310,   311,   312,
     135,   134,   133,     0,   136,   137,   138,   139,   140,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   323,   322,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   350,   351,   352,
     353,   354,   355,   357,   358,   359,   360,   361,   362,   364,
     365,   368,   369,   370,   372,   373,   335,   336,   356,   363,
     374,   376,   377,   378,   380,   381,   472,   337,   338,   339,
     366,   340,   344,   345,   348,   371,   375,   379,   341,   342,
     346,   347,   367,   343,   349,   382,   383,   384,   386,   388,
     390,   392,   394,   398,   399,   400,   401,   402,   403,   405,
     406,   407,   408,   409,   410,   412,   414,   415,   416,   418,
     419,   396,   404,   411,   420,   422,   423,   424,   426,   427,
     385,   387,   389,   413,   391,   393,   395,   397,   417,   421,
     425,   473,   474,   477,   478,   479,   480,   475,   476,   428,
     430,   431,   432,   434,   435,   436,   438,   439,   440,   442,
     443,   444,   446,   447,   448,   450,   451,   452,   454,   455,
     456,   458,   459,   460,   462,   463,   464,   466,   467,   468,
     470,   471,   429,   433,   437,   441,   445,   453,   457,   461,
     449,   465,   469,     0,   197,   482,   567,   132,   147,   483,
     484,   485,     0,   566,     0,   568,     0,   109,   108,     0,
     120,   125,   154,   153,   151,   155,     0,   148,   150,   156,
     157,   130,   191,   152,   481,     0,   563,   565,     0,     0,
       0,   488,     0,     0,    97,    94,     0,   107,     0,   116,
     110,   118,     0,   119,     0,    95,   126,     0,   100,   149,
     131,     0,   192,     1,   564,   189,     0,   146,   144,     0,
     142,   486,     0,     0,    98,     0,     0,   569,   111,   115,
     117,   113,   121,   112,     0,   127,   103,     0,   101,     0,
       2,    12,    13,    10,    11,     4,     5,     6,     7,     8,
       9,    15,    14,     0,     0,     0,   193,    43,    42,    44,
      41,     3,    17,    37,    19,    24,    25,     0,     0,    29,
       0,    45,     0,    49,    52,    55,    60,    63,    65,    67,
      69,    71,    73,    75,     0,    35,    36,    33,     0,   186,
       0,     0,   141,     0,     0,     0,     0,     0,   490,    96,
      99,     0,     0,   548,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   514,   523,   527,    45,    78,    91,     0,
     503,     0,   156,   157,   130,   506,   525,   505,   504,     0,
     507,   508,   529,   509,   536,   510,   511,   544,   512,     0,
     114,     0,   122,     0,   498,   129,     0,     0,   105,     0,
     102,    38,    39,     0,    21,    22,     0,     0,    27,    26,
       0,   197,    30,    32,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    76,   194,   195,     0,   190,    93,
     145,   143,     0,     0,   496,     0,   494,   489,   491,   559,
     558,     0,   550,     0,   562,   560,     0,     0,     0,   543,
     546,     0,   513,     0,    81,    82,    84,    83,    86,    87,
      88,    89,    90,    85,    80,     0,     0,   528,   524,   526,
     530,   537,   545,   124,     0,   501,     0,   128,     0,   106,
      16,     0,    23,    20,    31,    46,    47,    48,    51,    50,
      53,    54,    58,    59,    56,    57,    61,    62,    64,    66,
      68,    70,    72,    74,     0,   196,   487,     0,   497,     0,
     492,     0,     0,     0,   561,     0,   542,     0,   573,     0,
     571,   515,    79,    92,   123,   499,     0,   104,    18,     0,
     493,   495,     0,   553,   552,   555,   521,   538,   534,     0,
       0,     0,     0,     0,     0,     0,   500,   502,     0,     0,
     554,     0,     0,   533,     0,     0,   531,     0,     0,     0,
       0,   570,   572,   516,    77,     0,   556,     0,   521,   520,
     522,   540,     0,   518,   547,   517,   574,     0,   557,   551,
     532,   541,     0,   535,   549,   539
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,  -299,  -658,  -394,  -392,  -441,  -396,  -319,  -316,
    -294,  -293,  -321,  -296,  -658,  -371,  -658,  -395,  -658,  -379,
    -437,     1,  -658,  -658,  -658,     2,  -658,  -658,  -658,  -113,
    -108,  -110,  -658,  -658,  -618,  -658,  -658,  -658,  -658,  -200,
    -658,  -335,  -342,  -658,     6,    67,  -658,     0,  -349,  -658,
     -68,  -658,  -658,  -658,  -445,  -451,  -292,  -374,  -496,  -658,
    -376,  -486,  -657,  -417,  -658,  -658,  -428,  -426,  -658,  -658,
     -92,  -565,  -367,  -658,  -231,  -658,  -389,  -658,  -230,  -658,
    -658,  -658,  -658,  -229,  -658,  -658,  -658,  -658,  -658,  -658,
    -658,  -658,   -78,  -658,  -658,  -658,  -658,  -393
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   431,   432,   433,   611,   434,   435,   436,   437,   438,
     439,   440,   486,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   487,   634,   488,   595,   489,
     560,   490,   334,   517,   409,   491,   336,   337,   338,   369,
     370,   371,   339,   340,   341,   342,   343,   344,   389,   390,
     345,   346,   347,   348,   455,   456,   386,   457,   382,   352,
     353,   354,   464,   392,   467,   468,   565,   566,   515,   606,
     495,   496,   497,   498,   583,   675,   704,   683,   684,   685,
     705,   499,   500,   501,   502,   686,   671,   503,   504,   687,
     712,   505,   506,   507,   647,   571,   642,   665,   681,   682,
     508,   355,   356,   357,   366,   509,   649,   650
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     351,   333,   335,   372,   379,   473,   349,   474,   475,   514,
     454,   478,   387,   599,   395,   603,   568,   605,   651,   562,
     607,   363,   360,   542,   543,   553,   358,   405,   700,   669,
     379,   381,   703,   372,   403,   381,   381,   458,   374,   394,
     703,   375,   511,   404,   532,   470,   523,   669,   458,   524,
     525,   519,   510,   512,   520,   516,   458,   465,   544,   545,
     554,   361,   538,   604,   539,   459,   364,   350,   -34,   365,
     526,   460,   608,   406,   527,   462,   407,   529,   610,   408,
     666,   463,   441,   530,   596,   641,   596,   557,   667,   707,
     559,   655,   673,   656,   596,   596,   674,   359,   576,   367,
     578,   622,   623,   624,   625,   381,   596,   639,   654,   597,
     640,   568,   596,   368,   639,   644,   514,   660,   514,   540,
     541,   514,   376,   379,   521,   522,   546,   547,   385,   465,
     596,   646,   465,   596,   678,   614,   711,   329,   330,   331,
     535,   536,   537,   534,   618,   619,   391,   612,   620,   621,
     626,   627,   396,   401,   402,   458,   461,   568,   518,   441,
     677,   469,   441,   528,   533,   599,   584,   585,   586,   587,
     588,   589,   590,   591,   592,   593,   548,   549,   550,   551,
     552,   555,   465,   558,   564,   594,   572,   569,   579,   570,
     573,   574,   582,   609,   643,   577,   580,   613,   645,   581,
     652,   653,   -35,   -36,   -33,   648,   713,   -28,   635,   514,
     658,   662,   672,   679,  -519,   638,   596,   688,   689,   691,
     693,   696,   697,   698,   483,   599,   701,   465,   706,   628,
     715,   632,   702,   629,   714,   690,   615,   616,   617,   441,
     441,   441,   441,   441,   441,   441,   441,   441,   441,   441,
     441,   441,   441,   441,   441,   659,   630,   633,   631,   399,
     398,   514,   400,   561,   362,   661,   663,   699,   668,   709,
     388,   637,   710,   465,   397,   664,   680,   384,   600,   601,
     602,   692,     0,   694,     0,     0,   668,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     695,   559,     0,     0,     0,     0,     0,   514,     0,     0,
       0,     0,   670,     0,     0,     0,     0,   708,     0,   481,
       0,     0,     0,     0,     0,     0,     0,     0,   379,     0,
     670,     0,     0,     0,     0,     0,     0,     0,   373,     0,
       0,     0,     0,     0,   349,     0,   380,     0,     0,     0,
       0,     0,   349,     0,     0,   351,   333,   335,     0,     0,
       0,   349,   393,     0,     0,     0,     0,     0,   373,     0,
       0,     0,   373,   441,   349,     0,     0,     0,   349,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   466,     0,     0,     0,   494,     0,   349,     0,
       0,     0,   492,     0,     0,   350,     0,     0,     0,     0,
       0,     0,     0,   350,     0,     0,     0,     0,     0,     0,
       0,     0,   350,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   350,     0,     0,     0,   350,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   350,
       0,     0,     0,   493,   466,   563,     0,   466,     0,     0,
     349,   349,     0,   349,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   494,
       0,     0,     0,     0,     0,   492,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   466,     0,     0,
       0,     0,     0,   349,     0,     0,     0,     0,     0,     0,
       0,   350,   350,     0,   350,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   466,     0,     0,     0,   493,     0,   349,     0,
       0,   494,     0,     0,     0,     0,     0,   492,     0,     0,
       0,     0,     0,   494,   350,     0,     0,     0,     0,   492,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   466,     0,
       0,     0,     0,     0,   349,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   350,
       0,     0,     0,     0,     0,     0,     0,     0,   493,     0,
       0,     0,   494,     0,     0,     0,     0,   494,   492,     0,
     493,   494,     0,   492,     0,     0,     0,   492,     0,     0,
       0,     0,     0,     0,     0,   494,     0,     0,     0,     0,
     380,   492,     0,     0,     0,   350,   349,     0,     0,     0,
       0,     0,     0,     0,     0,   494,     0,     0,     0,   494,
       0,   492,     0,     0,     0,   492,     0,   494,     0,     0,
       0,   494,     0,   492,     0,     0,     0,   492,     0,   493,
       0,   494,     0,     0,   493,     0,     0,   492,   493,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   493,     0,     0,     0,     0,   350,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   493,     0,     0,     0,   493,     0,     0,     0,
       0,     0,     0,     0,   493,     0,     0,     0,   493,     0,
       0,     0,     0,     0,     0,     0,   383,     0,   493,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
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
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
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
     321,   322,   323,   324,     0,     0,   325,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     326,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   327,   328,   329,   330,   331,   332,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,   471,
     472,   473,     0,   474,   475,   476,   477,   478,   479,   480,
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
     320,   321,   322,   323,   324,   481,   410,   325,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
       0,     0,   423,   424,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   425,     0,   482,     0,   483,   484,     0,     0,     0,
       0,   485,   427,   428,   429,   430,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   327,   328,   329,   330,   331,
     332,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
     471,   472,   473,     0,   474,   475,   476,   477,   478,   479,
     480,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
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
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
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
     319,   320,   321,   322,   323,   324,   481,   410,   325,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,     0,     0,   423,   424,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   425,     0,   482,     0,   483,   598,     0,     0,
       0,     0,   485,   427,   428,   429,   430,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   327,   328,   329,   330,
     331,   332,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,   471,   472,   473,     0,   474,   475,   476,   477,   478,
     479,   480,    20,    21,    22,    23,    24,    25,    26,    27,
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
     318,   319,   320,   321,   322,   323,   324,   481,   410,   325,
     411,   412,   413,   414,   415,   416,   417,   418,   419,   420,
     421,   422,     0,     0,   423,   424,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   425,     0,   482,     0,   483,     0,     0,
       0,     0,     0,   485,   427,   428,   429,   430,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   327,   328,   329,
     330,   331,   332,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,   471,   472,   473,     0,   474,   475,   476,   477,
     478,   479,   480,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
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
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
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
     317,   318,   319,   320,   321,   322,   323,   324,   481,   410,
     325,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,     0,     0,   423,   424,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   425,     0,   482,     0,   396,     0,
       0,     0,     0,     0,   485,   427,   428,   429,   430,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   327,   328,
     329,   330,   331,   332,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,   471,   472,   473,     0,   474,   475,   476,
     477,   478,   479,   480,    20,    21,    22,    23,    24,    25,
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
     316,   317,   318,   319,   320,   321,   322,   323,   324,   481,
     410,   325,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,     0,     0,   423,   424,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   425,     0,   482,     0,     0,
       0,     0,     0,     0,     0,   485,   427,   428,   429,   430,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   327,
     328,   329,   330,   331,   332,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
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
       0,   410,   325,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,     0,     0,   423,   424,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   425,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   485,   427,   428,   429,
     430,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     327,   328,   329,   330,   331,   332,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,    21,    22,    23,
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
     324,     0,     0,   325,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   326,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   327,   328,   329,   330,   331,   332,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
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
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
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
     323,   324,     0,   410,   325,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,     0,     0,   423,
     424,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   425,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   427,
     428,   429,   430,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   327,   328,   329,   330,   331,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
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
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
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
     323,   324,     0,   377,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   378,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   327,   328,   329,   330,   331,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
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
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
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
     323,   324,     0,     0,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   567,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   327,   328,   329,   330,   331,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
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
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
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
     323,   324,     0,     0,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   636,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   327,   328,   329,   330,   331,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
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
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
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
     323,   324,     0,     0,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   657,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   327,   328,   329,   330,   331,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
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
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
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
     323,   324,     0,     0,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     4,
       5,     6,     7,     0,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
       0,     0,   327,   328,   329,   330,   331,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    69,     0,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   119,   120,   121,   122,   123,
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
     324,     0,   410,   325,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,     0,     0,   423,   424,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   425,     0,     0,
       0,   513,   676,     0,     0,     0,     0,     0,   427,   428,
     429,   430,     3,     4,     5,     6,     7,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,    75,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   119,
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
     320,   321,   322,   323,   324,     0,   410,   325,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
       0,     0,   423,   424,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   425,     0,     0,   426,     0,     0,     0,     0,     0,
       0,     0,   427,   428,   429,   430,     3,     4,     5,     6,
       7,     0,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,    75,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   119,   120,   121,   122,   123,   124,   125,
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
     316,   317,   318,   319,   320,   321,   322,   323,   324,     0,
     410,   325,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,     0,     0,   423,   424,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   425,     0,     0,     0,   513,
       0,     0,     0,     0,     0,     0,   427,   428,   429,   430,
       3,     4,     5,     6,     7,     0,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    69,     0,     0,
       0,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   119,   120,   121,
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
     322,   323,   324,     0,   410,   325,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,     0,     0,
     423,   424,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   425,
       0,     0,   556,     0,     0,     0,     0,     0,     0,     0,
     427,   428,   429,   430,     3,     4,     5,     6,     7,     0,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,     0,     0,     0,     0,     0,    75,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   119,   120,   121,   122,   123,   124,   125,   126,   127,
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
     318,   319,   320,   321,   322,   323,   324,     0,   410,   325,
     411,   412,   413,   414,   415,   416,   417,   418,   419,   420,
     421,   422,     0,     0,   423,   424,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   425,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   575,   427,   428,   429,   430,     3,     4,
       5,     6,     7,     0,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    69,     0,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   119,   120,   121,   122,   123,
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
     324,     0,   410,   325,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,     0,     0,   423,   424,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   425,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   427,   428,
     429,   430,     3,     4,     5,     6,     7,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,    75,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   119,
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
     320,   321,   322,   323,   531,     0,   410,   325,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
       0,     0,   423,   424,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   425,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   427,   428,   429,   430,     3,     4,     5,     6,
       7,     0,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   119,   120,   121,   122,   123,   124,   125,
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
     316,   317,   318,   319,   320,   321,   322,   323,   324,     0,
       0,   325
};

static const yytype_int16 yycheck[] =
{
       0,     0,     0,   338,   346,    24,     0,    26,    27,   404,
     381,    30,    81,   499,   363,   511,   467,   513,   583,   464,
     516,   339,   339,   357,   358,   362,   374,   376,   685,   647,
     372,   376,   689,   368,   374,   376,   376,   376,   381,   384,
     697,   384,   383,   383,   439,   384,   425,   665,   376,   355,
     356,   381,   401,   402,   384,   383,   376,   392,   392,   393,
     397,   378,   386,   383,   388,   375,   384,     0,   374,   384,
     376,   381,   517,   378,   380,   375,   381,   375,   375,   384,
     375,   381,   381,   381,   381,   571,   381,   458,   375,   375,
     461,   379,   377,   381,   381,   381,   381,   374,   477,   375,
     479,   542,   543,   544,   545,   376,   381,   381,   604,   384,
     384,   562,   381,   381,   381,   384,   511,   384,   513,   353,
     354,   516,   339,   465,   423,   424,   359,   360,   339,   464,
     381,   382,   467,   381,   382,   530,   701,   400,   401,   402,
     389,   390,   391,   442,   538,   539,   378,   526,   540,   541,
     546,   547,   378,   339,   339,   376,   383,   608,   339,   458,
     656,   384,   461,   375,   374,   651,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   396,   395,   394,   361,
     363,   377,   517,   339,   339,   383,   374,   384,   382,   384,
     374,   384,   379,   339,   573,   374,   374,   339,   577,   376,
     595,   596,   374,   374,   374,   339,   702,   375,   377,   604,
     377,   338,   374,   374,   378,   564,   381,   339,   375,   377,
     379,   384,   375,    25,   378,   711,   378,   562,   375,   548,
     379,   552,   383,   549,   384,   672,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   634,   550,   553,   551,   372,
     368,   656,   372,   463,   332,   639,   642,   684,   647,   697,
     339,   563,   698,   608,   366,   642,   665,   355,   509,   509,
     509,   674,    -1,   678,    -1,    -1,   665,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     679,   672,    -1,    -1,    -1,    -1,    -1,   702,    -1,    -1,
      -1,    -1,   647,    -1,    -1,    -1,    -1,   696,    -1,   338,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   670,    -1,
     665,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   338,    -1,
      -1,    -1,    -1,    -1,   338,    -1,   346,    -1,    -1,    -1,
      -1,    -1,   346,    -1,    -1,   355,   355,   355,    -1,    -1,
      -1,   355,   362,    -1,    -1,    -1,    -1,    -1,   368,    -1,
      -1,    -1,   372,   672,   368,    -1,    -1,    -1,   372,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   392,    -1,    -1,    -1,   396,    -1,   392,    -1,
      -1,    -1,   396,    -1,    -1,   338,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   346,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   355,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   368,    -1,    -1,    -1,   372,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   392,
      -1,    -1,    -1,   396,   464,   465,    -1,   467,    -1,    -1,
     464,   465,    -1,   467,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   499,
      -1,    -1,    -1,    -1,    -1,   499,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   517,    -1,    -1,
      -1,    -1,    -1,   517,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   464,   465,    -1,   467,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   562,    -1,    -1,    -1,   499,    -1,   562,    -1,
      -1,   571,    -1,    -1,    -1,    -1,    -1,   571,    -1,    -1,
      -1,    -1,    -1,   583,   517,    -1,    -1,    -1,    -1,   583,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   608,    -1,
      -1,    -1,    -1,    -1,   608,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   562,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   571,    -1,
      -1,    -1,   642,    -1,    -1,    -1,    -1,   647,   642,    -1,
     583,   651,    -1,   647,    -1,    -1,    -1,   651,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   665,    -1,    -1,    -1,    -1,
     670,   665,    -1,    -1,    -1,   608,   670,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   685,    -1,    -1,    -1,   689,
      -1,   685,    -1,    -1,    -1,   689,    -1,   697,    -1,    -1,
      -1,   701,    -1,   697,    -1,    -1,    -1,   701,    -1,   642,
      -1,   711,    -1,    -1,   647,    -1,    -1,   711,   651,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   665,    -1,    -1,    -1,    -1,   670,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   685,    -1,    -1,    -1,   689,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   697,    -1,    -1,    -1,   701,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     0,    -1,   711,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
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
     334,   335,   336,   337,    -1,    -1,   340,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     384,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   398,   399,   400,   401,   402,   403,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
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
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
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
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
      -1,    -1,   355,   356,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   374,    -1,   376,    -1,   378,   379,    -1,    -1,    -1,
      -1,   384,   385,   386,   387,   388,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   398,   399,   400,   401,   402,
     403,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
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
     352,    -1,    -1,   355,   356,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   374,    -1,   376,    -1,   378,   379,    -1,    -1,
      -1,    -1,   384,   385,   386,   387,   388,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   398,   399,   400,   401,
     402,   403,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
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
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
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
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,    -1,    -1,   355,   356,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   374,    -1,   376,    -1,   378,    -1,    -1,
      -1,    -1,    -1,   384,   385,   386,   387,   388,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   398,   399,   400,
     401,   402,   403,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    -1,    26,    27,    28,    29,
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
     350,   351,   352,    -1,    -1,   355,   356,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   374,    -1,   376,    -1,   378,    -1,
      -1,    -1,    -1,    -1,   384,   385,   386,   387,   388,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   398,   399,
     400,   401,   402,   403,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
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
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
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
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,    -1,    -1,   355,   356,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   374,    -1,   376,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   384,   385,   386,   387,   388,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   398,
     399,   400,   401,   402,   403,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
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
      -1,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,    -1,    -1,   355,   356,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   374,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   384,   385,   386,   387,
     388,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     398,   399,   400,   401,   402,   403,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
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
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
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
     337,    -1,    -1,   340,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   384,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   398,   399,   400,   401,   402,   403,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
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
     336,   337,    -1,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,    -1,    -1,   355,
     356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   374,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   385,
     386,   387,   388,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   398,   399,   400,   401,   402,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
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
     336,   337,    -1,   339,   340,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   384,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   398,   399,   400,   401,   402,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
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
     336,   337,    -1,    -1,   340,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   379,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   398,   399,   400,   401,   402,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
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
     336,   337,    -1,    -1,   340,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   379,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   398,   399,   400,   401,   402,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
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
     336,   337,    -1,    -1,   340,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   379,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   398,   399,   400,   401,   402,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
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
     336,   337,    -1,    -1,   340,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   398,   399,   400,   401,   402,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
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
     337,    -1,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,    -1,    -1,   355,   356,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   374,    -1,    -1,
      -1,   378,   379,    -1,    -1,    -1,    -1,    -1,   385,   386,
     387,   388,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
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
     333,   334,   335,   336,   337,    -1,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
      -1,    -1,   355,   356,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   374,    -1,    -1,   377,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   385,   386,   387,   388,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
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
     329,   330,   331,   332,   333,   334,   335,   336,   337,    -1,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,    -1,    -1,   355,   356,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   374,    -1,    -1,    -1,   378,
      -1,    -1,    -1,    -1,    -1,    -1,   385,   386,   387,   388,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,   133,   134,
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
     335,   336,   337,    -1,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,    -1,    -1,
     355,   356,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   374,
      -1,    -1,   377,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     385,   386,   387,   388,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
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
     331,   332,   333,   334,   335,   336,   337,    -1,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,    -1,    -1,   355,   356,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   374,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   384,   385,   386,   387,   388,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
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
     337,    -1,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,    -1,    -1,   355,   356,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   374,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   385,   386,
     387,   388,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
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
     333,   334,   335,   336,   337,    -1,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
      -1,    -1,   355,   356,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   374,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   385,   386,   387,   388,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
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
     329,   330,   331,   332,   333,   334,   335,   336,   337,    -1,
      -1,   340
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
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
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
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
     333,   334,   335,   336,   337,   340,   384,   398,   399,   400,
     401,   402,   403,   438,   439,   442,   443,   444,   445,   449,
     450,   451,   452,   453,   454,   457,   458,   459,   460,   461,
     462,   464,   466,   467,   468,   508,   509,   510,   374,   374,
     339,   378,   467,   339,   384,   384,   511,   375,   381,   446,
     447,   448,   458,   464,   381,   384,   339,   339,   384,   459,
     464,   376,   465,     0,   509,   339,   463,    81,   339,   455,
     456,   378,   470,   464,   384,   465,   378,   487,   447,   446,
     448,   339,   339,   374,   383,   465,   378,   381,   384,   441,
     339,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   355,   356,   374,   377,   385,   386,   387,
     388,   408,   409,   410,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   461,   462,   464,   376,   375,
     381,   383,   375,   381,   469,   458,   464,   471,   472,   384,
     384,    22,    23,    24,    26,    27,    28,    29,    30,    31,
      32,   338,   376,   378,   379,   384,   419,   432,   434,   436,
     438,   442,   461,   462,   464,   477,   478,   479,   480,   488,
     489,   490,   491,   494,   495,   498,   499,   500,   507,   512,
     465,   383,   465,   378,   434,   475,   383,   440,   339,   381,
     384,   419,   419,   436,   355,   356,   376,   380,   375,   375,
     381,   337,   434,   374,   419,   389,   390,   391,   386,   388,
     353,   354,   357,   358,   392,   393,   359,   360,   396,   395,
     394,   361,   363,   362,   397,   377,   377,   432,   339,   432,
     437,   456,   471,   464,   339,   473,   474,   379,   472,   384,
     384,   502,   374,   374,   384,   384,   436,   374,   436,   382,
     374,   376,   379,   481,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   383,   435,   381,   384,   379,   478,
     491,   495,   500,   475,   383,   475,   476,   475,   471,   339,
     375,   411,   436,   339,   434,   419,   419,   419,   421,   421,
     422,   422,   423,   423,   423,   423,   424,   424,   425,   426,
     427,   428,   429,   430,   433,   377,   379,   473,   465,   381,
     384,   478,   503,   436,   384,   436,   382,   501,   339,   513,
     514,   488,   434,   434,   475,   379,   381,   379,   377,   436,
     384,   474,   338,   477,   489,   504,   375,   375,   436,   451,
     458,   493,   374,   377,   381,   482,   379,   475,   382,   374,
     493,   505,   506,   484,   485,   486,   492,   496,   339,   375,
     437,   377,   514,   379,   434,   436,   384,   375,    25,   480,
     479,   378,   383,   479,   483,   487,   375,   375,   436,   483,
     484,   488,   497,   475,   384,   379
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   407,   408,   409,   409,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   409,   409,   410,   410,   410,
     410,   410,   410,   411,   412,   413,   414,   414,   415,   415,
     416,   416,   417,   418,   418,   418,   418,   419,   419,   419,
     419,   420,   420,   420,   420,   421,   421,   421,   421,   422,
     422,   422,   423,   423,   423,   424,   424,   424,   424,   424,
     425,   425,   425,   426,   426,   427,   427,   428,   428,   429,
     429,   430,   430,   431,   431,   432,   433,   432,   434,   434,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   436,   436,   437,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   440,   439,   441,   441,   442,   443,   443,
     444,   444,   445,   446,   446,   447,   447,   447,   447,   448,
     449,   449,   449,   449,   449,   450,   450,   450,   450,   450,
     451,   451,   452,   453,   453,   453,   453,   453,   453,   453,
     453,   454,   455,   455,   456,   456,   456,   457,   458,   458,
     459,   459,   459,   459,   459,   459,   459,   459,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   461,   462,   463,
     463,   464,   464,   465,   465,   465,   465,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   467,   467,   467,   469,   468,   470,   468,
     471,   471,   472,   472,   473,   473,   474,   474,   475,   475,
     475,   476,   476,   477,   478,   478,   479,   479,   479,   479,
     479,   479,   479,   480,   481,   482,   480,   483,   483,   485,
     484,   486,   484,   487,   487,   488,   488,   489,   489,   490,
     490,   491,   492,   492,   493,   493,   494,   494,   496,   495,
     497,   497,   498,   498,   499,   499,   501,   500,   502,   500,
     503,   500,   504,   504,   505,   505,   506,   506,   507,   507,
     507,   507,   507,   508,   508,   509,   509,   509,   511,   510,
     512,   513,   513,   514,   514
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     4,     1,
       3,     2,     2,     1,     1,     1,     2,     2,     2,     1,
       2,     3,     2,     1,     1,     1,     1,     1,     2,     2,
       2,     1,     1,     1,     1,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     2,     2,     4,     2,     3,     4,
       2,     3,     4,     0,     6,     2,     3,     2,     1,     1,
       2,     3,     3,     2,     3,     2,     1,     2,     1,     1,
       1,     3,     4,     6,     5,     1,     2,     3,     5,     4,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     3,     1,     3,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     1,     1,
       3,     1,     2,     2,     3,     3,     4,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     0,     6,     0,     5,
       1,     2,     3,     4,     1,     3,     1,     2,     1,     3,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     0,     0,     5,     1,     1,     0,
       2,     0,     2,     2,     3,     1,     2,     1,     2,     1,
       2,     5,     3,     1,     1,     4,     1,     2,     0,     8,
       0,     1,     3,     2,     1,     2,     0,     6,     0,     8,
       0,     7,     1,     1,     1,     0,     2,     3,     2,     2,
       2,     3,     2,     1,     2,     1,     1,     1,     0,     3,
       5,     1,     3,     1,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, pParseContext); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (pParseContext);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, pParseContext);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, glslang::TParseContext* pParseContext)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , pParseContext);
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, glslang::TParseContext* pParseContext)
{
  YYUSE (yyvaluep);
  YYUSE (pParseContext);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (glslang::TParseContext* pParseContext)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, parseContext);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 295 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleVariable((yyvsp[0].lex).loc, (yyvsp[0].lex).symbol, (yyvsp[0].lex).string);
    }
#line 4161 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 3:
#line 301 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4169 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 4:
#line 304 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 4178 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 5:
#line 308 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 4187 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 6:
#line 312 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 4195 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 7:
#line 315 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 4204 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 8:
#line 319 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).i64, (yyvsp[0].lex).loc, true);
    }
#line 4213 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 9:
#line 323 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).u64, (yyvsp[0].lex).loc, true);
    }
#line 4222 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 10:
#line 327 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt16Check((yyvsp[0].lex).loc, "16-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((short)(yyvsp[0].lex).i, (yyvsp[0].lex).loc, true);
    }
#line 4231 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 11:
#line 331 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt16Check((yyvsp[0].lex).loc, "16-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((unsigned short)(yyvsp[0].lex).u, (yyvsp[0].lex).loc, true);
    }
#line 4240 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 12:
#line 335 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat, (yyvsp[0].lex).loc, true);
    }
#line 4248 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 13:
#line 338 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtDouble, (yyvsp[0].lex).loc, true);
    }
#line 4257 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 14:
#line 342 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).d, EbtFloat16, (yyvsp[0].lex).loc, true);
    }
#line 4266 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 15:
#line 346 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[0].lex).b, (yyvsp[0].lex).loc, true);
    }
#line 4274 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 16:
#line 349 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
        if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
            (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
    }
#line 4284 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 17:
#line 357 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4292 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 18:
#line 360 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBracketDereference((yyvsp[-2].lex).loc, (yyvsp[-3].interm.intermTypedNode), (yyvsp[-1].interm.intermTypedNode));
    }
#line 4300 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 19:
#line 363 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4308 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 20:
#line 366 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleDotDereference((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode), *(yyvsp[0].lex).string);
    }
#line 4316 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 21:
#line 369 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "++", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "++", EOpPostIncrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 4326 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 22:
#line 374 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.variableCheck((yyvsp[-1].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[0].lex).loc, "--", (yyvsp[-1].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[0].lex).loc, "--", EOpPostDecrement, (yyvsp[-1].interm.intermTypedNode));
    }
#line 4336 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 23:
#line 382 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.integerCheck((yyvsp[0].interm.intermTypedNode), "[]");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4345 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 24:
#line 389 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleFunctionCall((yyvsp[0].interm).loc, (yyvsp[0].interm).function, (yyvsp[0].interm).intermNode);
        delete (yyvsp[0].interm).function;
    }
#line 4354 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 25:
#line 396 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 4362 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 26:
#line 402 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 4371 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 27:
#line 406 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 4380 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 28:
#line 413 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 4388 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 29:
#line 416 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 4396 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 30:
#line 422 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        TParameter param = { 0, new TType };
        param.type->shallowCopy((yyvsp[0].interm.intermTypedNode)->getType());
        (yyvsp[-1].interm).function->addParameter(param);
        (yyval.interm).function = (yyvsp[-1].interm).function;
        (yyval.interm).intermNode = (yyvsp[0].interm.intermTypedNode);
    }
#line 4408 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 31:
#line 429 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        TParameter param = { 0, new TType };
        param.type->shallowCopy((yyvsp[0].interm.intermTypedNode)->getType());
        (yyvsp[-2].interm).function->addParameter(param);
        (yyval.interm).function = (yyvsp[-2].interm).function;
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
    }
#line 4420 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 32:
#line 439 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[-1].interm);
    }
#line 4428 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 33:
#line 447 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 4438 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 34:
#line 452 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        //
        // Should be a method or subroutine call, but we haven't recognized the arguments yet.
        //
        (yyval.interm).function = 0;
        (yyval.interm).intermNode = 0;

        TIntermMethod* method = (yyvsp[0].interm.intermTypedNode)->getAsMethodNode();
        if (method) {
            (yyval.interm).function = new TFunction(&method->getMethodName(), TType(EbtInt), EOpArrayLength);
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
            TString empty("");
            (yyval.interm).function = new TFunction(&empty, TType(EbtVoid), EOpNull);
        }
    }
#line 4470 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 35:
#line 479 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 4480 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 36:
#line 484 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type));
    }
#line 4490 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 37:
#line 492 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.variableCheck((yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        if (TIntermMethod* method = (yyvsp[0].interm.intermTypedNode)->getAsMethodNode())
            parseContext.error((yyvsp[0].interm.intermTypedNode)->getLoc(), "incomplete method syntax", method->getMethodName().c_str(), "");
    }
#line 4501 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 38:
#line 498 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "++", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "++", EOpPreIncrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 4510 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 39:
#line 502 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.lValueErrorCheck((yyvsp[-1].lex).loc, "--", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[-1].lex).loc, "--", EOpPreDecrement, (yyvsp[0].interm.intermTypedNode));
    }
#line 4519 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 40:
#line 506 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
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
#line 4540 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 41:
#line 526 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNull; }
#line 4546 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 42:
#line 527 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpNegative; }
#line 4552 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 43:
#line 528 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLogicalNot; }
#line 4558 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 44:
#line 529 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpBitwiseNot;
              parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise not"); }
#line 4565 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 45:
#line 535 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4571 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 46:
#line 536 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "*", EOpMul, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4581 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 47:
#line 541 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "/", EOpDiv, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4591 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 48:
#line 546 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "%");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "%", EOpMod, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4602 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 49:
#line 555 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4608 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 50:
#line 556 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "+", EOpAdd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4618 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 51:
#line 561 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "-", EOpSub, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4628 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 52:
#line 569 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4634 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 53:
#line 570 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift left");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<<", EOpLeftShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4645 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 54:
#line 576 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bit shift right");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">>", EOpRightShift, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4656 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 55:
#line 585 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4662 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 56:
#line 586 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<", EOpLessThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4672 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 57:
#line 591 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">", EOpGreaterThan, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4682 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 58:
#line 596 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "<=", EOpLessThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4692 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 59:
#line 601 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, ">=", EOpGreaterThanEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4702 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 60:
#line 609 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4708 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 61:
#line 610 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "==");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "==", EOpEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4721 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 62:
#line 618 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.arrayObjectCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        parseContext.specializationCheck((yyvsp[-1].lex).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "!=");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "!=", EOpNotEqual, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4734 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 63:
#line 629 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4740 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 64:
#line 630 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise and");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&", EOpAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4751 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 65:
#line 639 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4757 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 66:
#line 640 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise exclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^", EOpExclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4768 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 67:
#line 649 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4774 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 68:
#line 650 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[-1].lex).loc, "bitwise inclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "|", EOpInclusiveOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 4785 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 69:
#line 659 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4791 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 70:
#line 660 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "&&", EOpLogicalAnd, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4801 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 71:
#line 668 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4807 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 72:
#line 669 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "^^", EOpLogicalXor, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4817 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 73:
#line 677 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4823 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 74:
#line 678 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[-1].lex).loc, "||", EOpLogicalOr, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[-1].lex).loc);
    }
#line 4833 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 75:
#line 686 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4839 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 76:
#line 687 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        ++parseContext.controlFlowNestingLevel;
    }
#line 4847 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 77:
#line 690 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        --parseContext.controlFlowNestingLevel;
        parseContext.boolCheck((yyvsp[-4].lex).loc, (yyvsp[-5].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-4].lex).loc, "?", (yyvsp[-5].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].lex).loc, ":", (yyvsp[-2].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].lex).loc, ":", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addSelection((yyvsp[-5].interm.intermTypedNode), (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-4].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[-4].lex).loc, ":", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(), (yyvsp[0].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 4864 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 78:
#line 705 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode); }
#line 4870 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 79:
#line 706 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.arrayObjectCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "array assignment");
        parseContext.opaqueCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.storage16BitAssignmentCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.specializationCheck((yyvsp[-1].interm).loc, (yyvsp[-2].interm.intermTypedNode)->getType(), "=");
        parseContext.lValueErrorCheck((yyvsp[-1].interm).loc, "assign", (yyvsp[-2].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[-1].interm).loc, "assign", (yyvsp[0].interm.intermTypedNode));
        parseContext.uniformityCheck((yyvsp[-1].interm).loc, "assign", (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addAssign((yyvsp[-1].interm).op, (yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].interm).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.assignError((yyvsp[-1].interm).loc, "assign", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(), (yyvsp[0].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
        }
    }
#line 4889 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 80:
#line 723 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAssign;
    }
#line 4898 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 81:
#line 727 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpMulAssign;
    }
#line 4907 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 82:
#line 731 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpDivAssign;
    }
#line 4916 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 83:
#line 735 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "%=");
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpModAssign;
    }
#line 4926 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 84:
#line 740 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpAddAssign;
    }
#line 4935 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 85:
#line 744 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).op = EOpSubAssign;
    }
#line 4944 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 86:
#line 748 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift left assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpLeftShiftAssign;
    }
#line 4953 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 87:
#line 752 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bit-shift right assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpRightShiftAssign;
    }
#line 4962 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 88:
#line 756 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-and assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpAndAssign;
    }
#line 4971 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 89:
#line 760 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-xor assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpExclusiveOrAssign;
    }
#line 4980 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 90:
#line 764 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "bitwise-or assign");
        (yyval.interm).loc = (yyvsp[0].lex).loc; (yyval.interm).op = EOpInclusiveOrAssign;
    }
#line 4989 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 91:
#line 771 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 4997 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 92:
#line 774 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.samplerConstructorLocationCheck((yyvsp[-1].lex).loc, ",", (yyvsp[0].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addComma((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode), (yyvsp[-1].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[-1].lex).loc, ",", (yyvsp[-2].interm.intermTypedNode)->getCompleteString(), (yyvsp[0].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        }
    }
#line 5010 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 93:
#line 785 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.constantValueCheck((yyvsp[0].interm.intermTypedNode), "");
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 5019 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 94:
#line 792 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.handleFunctionDeclarator((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).function, true /* prototype */);
        (yyval.interm.intermNode) = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    }
#line 5029 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 95:
#line 797 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        if ((yyvsp[-1].interm).intermNode && (yyvsp[-1].interm).intermNode->getAsAggregate())
            (yyvsp[-1].interm).intermNode->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-1].interm).intermNode;
    }
#line 5039 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 96:
#line 802 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.profileRequires((yyvsp[-3].lex).loc, ENoProfile, 130, 0, "precision statement");

        // lazy setting of the previous scope's defaults, has effect only the first time it is called in a particular scope
        parseContext.symbolTable.setPreviousDefaultPrecisions(&parseContext.defaultPrecision[0]);
        parseContext.setDefaultPrecision((yyvsp[-3].lex).loc, (yyvsp[-1].interm.type), (yyvsp[-2].interm.type).qualifier.precision);
        (yyval.interm.intermNode) = 0;
    }
#line 5052 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 97:
#line 810 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.declareBlock((yyvsp[-1].interm).loc, *(yyvsp[-1].interm).typeList);
        (yyval.interm.intermNode) = 0;
    }
#line 5061 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 98:
#line 814 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.declareBlock((yyvsp[-2].interm).loc, *(yyvsp[-2].interm).typeList, (yyvsp[-1].lex).string);
        (yyval.interm.intermNode) = 0;
    }
#line 5070 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 99:
#line 818 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.declareBlock((yyvsp[-3].interm).loc, *(yyvsp[-3].interm).typeList, (yyvsp[-2].lex).string, (yyvsp[-1].interm).arraySizes);
        (yyval.interm.intermNode) = 0;
    }
#line 5079 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 100:
#line 822 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalQualifierFixCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier);
        parseContext.updateStandaloneQualifierDefaults((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type));
        (yyval.interm.intermNode) = 0;
    }
#line 5089 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 101:
#line 827 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.checkNoShaderLayouts((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).shaderQualifiers);
        parseContext.addQualifierToExisting((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).qualifier, *(yyvsp[-1].lex).string);
        (yyval.interm.intermNode) = 0;
    }
#line 5099 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 102:
#line 832 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.checkNoShaderLayouts((yyvsp[-3].interm.type).loc, (yyvsp[-3].interm.type).shaderQualifiers);
        (yyvsp[-1].interm.identifierList)->push_back((yyvsp[-2].lex).string);
        parseContext.addQualifierToExisting((yyvsp[-3].interm.type).loc, (yyvsp[-3].interm.type).qualifier, *(yyvsp[-1].interm.identifierList));
        (yyval.interm.intermNode) = 0;
    }
#line 5110 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 103:
#line 841 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { parseContext.nestedBlockCheck((yyvsp[-2].interm.type).loc); }
#line 5116 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 104:
#line 841 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        --parseContext.structNestingLevel;
        parseContext.blockName = (yyvsp[-4].lex).string;
        parseContext.globalQualifierFixCheck((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).qualifier);
        parseContext.checkNoShaderLayouts((yyvsp[-5].interm.type).loc, (yyvsp[-5].interm.type).shaderQualifiers);
        parseContext.currentBlockQualifier = (yyvsp[-5].interm.type).qualifier;
        (yyval.interm).loc = (yyvsp[-5].interm.type).loc;
        (yyval.interm).typeList = (yyvsp[-1].interm.typeList);
    }
#line 5130 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 105:
#line 852 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.identifierList) = new TIdentifierList;
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 5139 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 106:
#line 856 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.identifierList) = (yyvsp[-2].interm.identifierList);
        (yyval.interm.identifierList)->push_back((yyvsp[0].lex).string);
    }
#line 5148 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 107:
#line 863 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).function = (yyvsp[-1].interm.function);
        (yyval.interm).loc = (yyvsp[0].lex).loc;
    }
#line 5157 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 108:
#line 870 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 5165 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 109:
#line 873 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.function) = (yyvsp[0].interm.function);
    }
#line 5173 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 110:
#line 880 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        // Add the parameter
        (yyval.interm.function) = (yyvsp[-1].interm.function);
        if ((yyvsp[0].interm).param.type->getBasicType() != EbtVoid)
            (yyvsp[-1].interm.function)->addParameter((yyvsp[0].interm).param);
        else
            delete (yyvsp[0].interm).param.type;
    }
#line 5186 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 111:
#line 888 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
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
            (yyvsp[-2].interm.function)->addParameter((yyvsp[0].interm).param);
        }
    }
#line 5208 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 112:
#line 908 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
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
#line 5232 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 113:
#line 931 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
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

        TParameter param = {(yyvsp[0].lex).string, new TType((yyvsp[-1].interm.type))};
        (yyval.interm).loc = (yyvsp[0].lex).loc;
        (yyval.interm).param = param;
    }
#line 5252 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 114:
#line 946 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
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

        TParameter param = { (yyvsp[-1].lex).string, type };

        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        (yyval.interm).param = param;
    }
#line 5276 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 115:
#line 971 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);

    }
#line 5292 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 116:
#line 982 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFixStorage((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    }
#line 5304 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 117:
#line 992 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[0].interm);
        if ((yyvsp[-1].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[-1].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyvsp[-1].interm.type).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, (yyvsp[-1].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier, *(yyval.interm).param.type);
    }
#line 5319 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 118:
#line 1002 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[0].interm);

        parseContext.parameterTypeCheck((yyvsp[0].interm).loc, EvqIn, *(yyvsp[0].interm).param.type);
        parseContext.paramCheckFixStorage((yyvsp[0].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    }
#line 5331 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 119:
#line 1012 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        TParameter param = { 0, new TType((yyvsp[0].interm.type)) };
        (yyval.interm).param = param;
        if ((yyvsp[0].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[0].interm.type).loc, *(yyvsp[0].interm.type).arraySizes);
    }
#line 5342 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 120:
#line 1021 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[0].interm);
    }
#line 5350 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 121:
#line 1024 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[-2].interm);
        parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-2].interm).type);
    }
#line 5359 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 122:
#line 1028 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[-3].interm);
        parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-3].interm).type, (yyvsp[0].interm).arraySizes);
    }
#line 5368 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 123:
#line 1032 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).type = (yyvsp[-5].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-5].interm).type, (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-5].interm).intermNode, initNode, (yyvsp[-1].lex).loc);
    }
#line 5378 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 124:
#line 1037 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).type = (yyvsp[-4].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-4].interm).type, 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[-4].interm).intermNode, initNode, (yyvsp[-1].lex).loc);
    }
#line 5388 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 125:
#line 1045 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).type = (yyvsp[0].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareTypeDefaults((yyval.interm).loc, (yyval.interm).type);
    }
#line 5398 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 126:
#line 1050 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).type = (yyvsp[-1].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[0].lex).loc, *(yyvsp[0].lex).string, (yyvsp[-1].interm.type));
    }
#line 5408 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 127:
#line 1055 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).type = (yyvsp[-2].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[-1].lex).loc, *(yyvsp[-1].lex).string, (yyvsp[-2].interm.type), (yyvsp[0].interm).arraySizes);
    }
#line 5418 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 128:
#line 1060 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).type = (yyvsp[-4].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-3].lex).loc, *(yyvsp[-3].lex).string, (yyvsp[-4].interm.type), (yyvsp[-2].interm).arraySizes, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[-1].lex).loc);
    }
#line 5428 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 129:
#line 1065 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).type = (yyvsp[-3].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[-1].lex).loc);
    }
#line 5438 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 130:
#line 1074 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);

        parseContext.globalQualifierTypeCheck((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier, (yyval.interm.type));
        if ((yyvsp[0].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[0].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[0].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        parseContext.precisionQualifierCheck((yyval.interm.type).loc, (yyval.interm.type).basicType, (yyval.interm.type).qualifier);
    }
#line 5454 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 131:
#line 1085 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalQualifierFixCheck((yyvsp[-1].interm.type).loc, (yyvsp[-1].interm.type).qualifier);
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
        parseContext.precisionQualifierCheck((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).basicType, (yyvsp[0].interm.type).qualifier);

        (yyval.interm.type) = (yyvsp[0].interm.type);

        if (! (yyval.interm.type).qualifier.isInterpolation() &&
            ((parseContext.language == EShLangVertex   && (yyval.interm.type).qualifier.storage == EvqVaryingOut) ||
             (parseContext.language == EShLangFragment && (yyval.interm.type).qualifier.storage == EvqVaryingIn)))
            (yyval.interm.type).qualifier.smooth = true;
    }
#line 5483 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 132:
#line 1112 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "invariant");
        parseContext.profileRequires((yyval.interm.type).loc, ENoProfile, 120, 0, "invariant");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.invariant = true;
    }
#line 5494 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 133:
#line 1121 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "smooth");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "smooth");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.smooth = true;
    }
#line 5506 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 134:
#line 1128 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "flat");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "flat");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.flat = true;
    }
#line 5518 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 135:
#line 1135 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "noperspective");
#ifdef NV_EXTENSIONS
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 0, E_GL_NV_shader_noperspective_interpolation, "noperspective");
#else
        parseContext.requireProfile((yyvsp[0].lex).loc, ~EEsProfile, "noperspective");
#endif
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "noperspective");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.nopersp = true;
    }
#line 5534 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 136:
#line 1146 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "__explicitInterpAMD");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.explicitInterp = true;
#endif
    }
#line 5548 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 137:
#line 1155 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "pervertexNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECompatibilityProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 0, E_GL_NV_fragment_shader_barycentric, "fragment shader barycentric");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.pervertexNV = true;
#endif
    }
#line 5563 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 138:
#line 1165 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef NV_EXTENSIONS
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "perprimitiveNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangFragmentMask | EShLangMeshNVMask), "perprimitiveNV");
        // Fragment shader stage doesn't check for extension. So we explicitly add below extension check.
        if (parseContext.language == EShLangFragment)
            parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_NV_mesh_shader, "perprimitiveNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perPrimitiveNV = true;
#endif
    }
#line 5580 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 139:
#line 1177 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef NV_EXTENSIONS
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "perviewNV");
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangMeshNV, "perviewNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perViewNV = true;
#endif
    }
#line 5594 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 140:
#line 1186 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef NV_EXTENSIONS
        // No need for profile version or extension check. Shader stage already checks both.
        parseContext.globalCheck((yyvsp[0].lex).loc, "taskNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTaskNVMask | EShLangMeshNVMask), "taskNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.perTaskNV = true;
#endif
    }
#line 5608 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 141:
#line 1198 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
    }
#line 5616 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 142:
#line 1204 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5624 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 143:
#line 1207 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[-2].interm.type);
        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeObjectLayoutQualifiers((yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 5634 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 144:
#line 1214 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), *(yyvsp[0].lex).string);
    }
#line 5643 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 145:
#line 1218 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[-2].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[-2].lex).loc, (yyval.interm.type), *(yyvsp[-2].lex).string, (yyvsp[0].interm.intermTypedNode));
    }
#line 5652 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 146:
#line 1222 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { // because "shared" is both an identifier and a keyword
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        TString strShared("shared");
        parseContext.setLayoutQualifier((yyvsp[0].lex).loc, (yyval.interm.type), strShared);
    }
#line 5662 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 147:
#line 1230 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.profileRequires((yyval.interm.type).loc, ECoreProfile | ECompatibilityProfile, 400, E_GL_ARB_gpu_shader5, "precise");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 320, Num_AEP_gpu_shader5, AEP_gpu_shader5, "precise");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.noContraction = true;
    }
#line 5673 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 148:
#line 1239 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5681 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 149:
#line 1242 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        if ((yyval.interm.type).basicType == EbtVoid)
            (yyval.interm.type).basicType = (yyvsp[0].interm.type).basicType;

        (yyval.interm.type).shaderQualifiers.merge((yyvsp[0].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyval.interm.type).loc, (yyval.interm.type).qualifier, (yyvsp[0].interm.type).qualifier, false);
    }
#line 5694 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 150:
#line 1253 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5702 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 151:
#line 1256 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5710 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 152:
#line 1259 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.checkPrecisionQualifier((yyvsp[0].interm.type).loc, (yyvsp[0].interm.type).qualifier.precision);
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5719 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 153:
#line 1263 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5728 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 154:
#line 1267 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5737 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 155:
#line 1271 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5746 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 156:
#line 1275 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5754 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 157:
#line 1278 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
    }
#line 5762 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 158:
#line 1284 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqConst;  // will later turn into EvqConstReadOnly, if the initializer is not constant
    }
#line 5771 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 159:
#line 1288 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
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
#line 5788 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 160:
#line 1300 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
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
#line 5807 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 161:
#line 1314 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "inout");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqInOut;
    }
#line 5817 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 162:
#line 1319 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "in");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "in" or a pipeline "in" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqIn;
    }
#line 5828 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 163:
#line 1325 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "out");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        // whether this is a parameter "out" or a pipeline "out" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqOut;
    }
#line 5839 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 164:
#line 1331 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 120, 0, "centroid");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 300, 0, "centroid");
        parseContext.globalCheck((yyvsp[0].lex).loc, "centroid");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.centroid = true;
    }
#line 5851 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 165:
#line 1338 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "patch");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangTessControlMask | EShLangTessEvaluationMask), "patch");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.patch = true;
    }
#line 5862 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 166:
#line 1344 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "sample");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.sample = true;
    }
#line 5872 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 167:
#line 1349 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "uniform");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqUniform;
    }
#line 5882 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 168:
#line 1354 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "buffer");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqBuffer;
    }
#line 5892 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 169:
#line 1359 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "hitAttributeNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangIntersectNVMask | EShLangClosestHitNVMask
            | EShLangAnyHitNVMask), "hitAttributeNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "hitAttributeNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqHitAttrNV;
#endif
    }
#line 5907 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 170:
#line 1369 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenNVMask | EShLangClosestHitNVMask |
            EShLangAnyHitNVMask | EShLangMissNVMask), "rayPayloadNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "rayPayloadNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayloadNV;
#endif
    }
#line 5922 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 171:
#line 1379 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "rayPayloadInNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangClosestHitNVMask |
            EShLangAnyHitNVMask | EShLangMissNVMask), "rayPayloadInNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "rayPayloadInNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqPayloadInNV;
#endif
    }
#line 5937 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 172:
#line 1389 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangRayGenNVMask |
            EShLangClosestHitNVMask | EShLangMissNVMask | EShLangCallableNVMask), "callableDataNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "callableDataNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableDataNV;
#endif
    }
#line 5952 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 173:
#line 1399 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef NV_EXTENSIONS
        parseContext.globalCheck((yyvsp[0].lex).loc, "callableDataInNV");
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangCallableNVMask), "callableDataInNV");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile, 460, E_GL_NV_ray_tracing, "callableDataInNV");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqCallableDataInNV;
#endif
    }
#line 5966 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 174:
#line 1408 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.globalCheck((yyvsp[0].lex).loc, "shared");
        parseContext.profileRequires((yyvsp[0].lex).loc, ECoreProfile | ECompatibilityProfile, 430, E_GL_ARB_compute_shader, "shared");
        parseContext.profileRequires((yyvsp[0].lex).loc, EEsProfile, 310, 0, "shared");
#ifdef NV_EXTENSIONS
        parseContext.requireStage((yyvsp[0].lex).loc, (EShLanguageMask)(EShLangComputeMask | EShLangMeshNVMask | EShLangTaskNVMask), "shared");
#else
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangCompute, "shared");
#endif
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqShared;
    }
#line 5983 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 175:
#line 1420 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.coherent = true;
    }
#line 5992 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 176:
#line 1424 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "devicecoherent");
        (yyval.interm.type).qualifier.devicecoherent = true;
    }
#line 6002 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 177:
#line 1429 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "queuefamilycoherent");
        (yyval.interm.type).qualifier.queuefamilycoherent = true;
    }
#line 6012 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 178:
#line 1434 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "workgroupcoherent");
        (yyval.interm.type).qualifier.workgroupcoherent = true;
    }
#line 6022 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 179:
#line 1439 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "subgroupcoherent");
        (yyval.interm.type).qualifier.subgroupcoherent = true;
    }
#line 6032 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 180:
#line 1444 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        parseContext.requireExtensions((yyvsp[0].lex).loc, 1, &E_GL_KHR_memory_scope_semantics, "nonprivate");
        (yyval.interm.type).qualifier.nonprivate = true;
    }
#line 6042 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 181:
#line 1449 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.volatil = true;
    }
#line 6051 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 182:
#line 1453 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.restrict = true;
    }
#line 6060 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 183:
#line 1457 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.readonly = true;
    }
#line 6069 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 184:
#line 1461 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.writeonly = true;
    }
#line 6078 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 185:
#line 1465 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.spvRemoved((yyvsp[0].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[0].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[0].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[0].lex).loc);
    }
#line 6089 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 186:
#line 1471 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.spvRemoved((yyvsp[-3].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[-3].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[-3].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[-3].lex).loc);
    }
#line 6100 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 187:
#line 1480 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.makeNonUniform();
    }
#line 6109 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 188:
#line 1487 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc);
        (yyval.interm.type).qualifier.makeSubgroupUniform();
    }
#line 6118 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 189:
#line 1494 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        // TODO
    }
#line 6126 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 190:
#line 1497 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        // TODO: 4.0 semantics: subroutines
        // 1) make sure each identifier is a type declared earlier with SUBROUTINE
        // 2) save all of the identifiers for future comparison with the declared function
    }
#line 6136 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 191:
#line 1505 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
    }
#line 6145 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 192:
#line 1509 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.arrayOfArrayVersionCheck((yyvsp[0].interm).loc, (yyvsp[0].interm).arraySizes);
        (yyval.interm.type) = (yyvsp[-1].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).arraySizes = (yyvsp[0].interm).arraySizes;
    }
#line 6156 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 193:
#line 1518 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).loc = (yyvsp[-1].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 6166 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 194:
#line 1523 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm).loc = (yyvsp[-2].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size);
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 6179 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 195:
#line 1531 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[-2].interm);
        (yyval.interm).arraySizes->addInnerSize();
    }
#line 6188 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 196:
#line 1535 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm) = (yyvsp[-3].interm);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[-1].interm.intermTypedNode)->getLoc(), (yyvsp[-1].interm.intermTypedNode), size);
        (yyval.interm).arraySizes->addInnerSize(size);
    }
#line 6200 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 197:
#line 1545 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtVoid;
    }
#line 6209 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 198:
#line 1549 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
#line 6218 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 199:
#line 1553 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
#line 6228 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 200:
#line 1558 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "float16_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
    }
#line 6238 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 201:
#line 1563 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    }
#line 6248 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 202:
#line 1568 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    }
#line 6258 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 203:
#line 1573 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
#line 6267 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 204:
#line 1577 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
#line 6277 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 205:
#line 1582 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
    }
#line 6287 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 206:
#line 1587 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
    }
#line 6297 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 207:
#line 1592 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
    }
#line 6307 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 208:
#line 1597 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
    }
#line 6317 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 209:
#line 1602 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    }
#line 6327 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 210:
#line 1607 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    }
#line 6337 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 211:
#line 1612 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
    }
#line 6347 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 212:
#line 1617 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
    }
#line 6357 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 213:
#line 1622 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
    }
#line 6366 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 214:
#line 1626 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
#line 6376 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 215:
#line 1631 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
#line 6386 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 216:
#line 1636 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
#line 6396 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 217:
#line 1641 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
#line 6407 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 218:
#line 1647 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
#line 6418 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 219:
#line 1653 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
#line 6429 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 220:
#line 1659 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(2);
    }
#line 6440 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 221:
#line 1665 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(3);
    }
#line 6451 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 222:
#line 1671 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16ScalarVectorCheck((yyvsp[0].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(4);
    }
#line 6462 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 223:
#line 1677 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    }
#line 6473 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 224:
#line 1683 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    }
#line 6484 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 225:
#line 1689 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    }
#line 6495 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 226:
#line 1695 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    }
#line 6506 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 227:
#line 1701 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    }
#line 6517 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 228:
#line 1707 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    }
#line 6528 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 229:
#line 1713 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(2);
    }
#line 6538 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 230:
#line 1718 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(3);
    }
#line 6548 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 231:
#line 1723 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(4);
    }
#line 6558 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 232:
#line 1728 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
#line 6568 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 233:
#line 1733 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
#line 6578 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 234:
#line 1738 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
#line 6588 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 235:
#line 1743 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(2);
    }
#line 6599 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 236:
#line 1749 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(3);
    }
#line 6610 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 237:
#line 1755 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt8;
        (yyval.interm.type).setVector(4);
    }
#line 6621 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 238:
#line 1761 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(2);
    }
#line 6632 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 239:
#line 1767 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(3);
    }
#line 6643 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 240:
#line 1773 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(4);
    }
#line 6654 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 241:
#line 1779 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    }
#line 6665 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 242:
#line 1785 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    }
#line 6676 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 243:
#line 1791 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit signed integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    }
#line 6687 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 244:
#line 1797 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(2);
    }
#line 6698 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 245:
#line 1803 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(3);
    }
#line 6709 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 246:
#line 1809 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(4);
    }
#line 6720 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 247:
#line 1815 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
#line 6731 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 248:
#line 1821 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
#line 6742 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 249:
#line 1827 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.fullIntegerCheck((yyvsp[0].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
#line 6753 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 250:
#line 1833 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(2);
    }
#line 6764 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 251:
#line 1839 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(3);
    }
#line 6775 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 252:
#line 1845 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int8ScalarVectorCheck((yyvsp[0].lex).loc, "8-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint8;
        (yyval.interm.type).setVector(4);
    }
#line 6786 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 253:
#line 1851 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(2);
    }
#line 6797 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 254:
#line 1857 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(3);
    }
#line 6808 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 255:
#line 1863 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int16ScalarVectorCheck((yyvsp[0].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(4);
    }
#line 6819 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 256:
#line 1869 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    }
#line 6830 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 257:
#line 1875 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    }
#line 6841 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 258:
#line 1881 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitInt32Check((yyvsp[0].lex).loc, "32-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    }
#line 6852 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 259:
#line 1887 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(2);
    }
#line 6863 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 260:
#line 1893 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(3);
    }
#line 6874 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 261:
#line 1899 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.int64Check((yyvsp[0].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(4);
    }
#line 6885 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 262:
#line 1905 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 6895 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 263:
#line 1910 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 6905 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 264:
#line 1915 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 6915 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 265:
#line 1920 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 6925 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 266:
#line 1925 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 6935 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 267:
#line 1930 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 6945 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 268:
#line 1935 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 6955 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 269:
#line 1940 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 6965 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 270:
#line 1945 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 6975 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 271:
#line 1950 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 6985 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 272:
#line 1955 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 6995 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 273:
#line 1960 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7005 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 274:
#line 1965 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7016 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 275:
#line 1971 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7027 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 276:
#line 1977 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7038 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 277:
#line 1983 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7049 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 278:
#line 1989 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7060 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 279:
#line 1995 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7071 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 280:
#line 2001 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7082 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 281:
#line 2007 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7093 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 282:
#line 2013 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7104 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 283:
#line 2019 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7115 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 284:
#line 2025 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7126 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 285:
#line 2031 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.doubleCheck((yyvsp[0].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7137 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 286:
#line 2037 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7148 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 287:
#line 2043 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7159 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 288:
#line 2049 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7170 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 289:
#line 2055 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7181 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 290:
#line 2061 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7192 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 291:
#line 2067 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7203 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 292:
#line 2073 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7214 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 293:
#line 2079 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7225 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 294:
#line 2085 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7236 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 295:
#line 2091 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7247 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 296:
#line 2097 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7258 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 297:
#line 2103 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.float16Check((yyvsp[0].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7269 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 298:
#line 2109 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7280 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 299:
#line 2115 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7291 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 300:
#line 2121 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7302 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 301:
#line 2127 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7313 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 302:
#line 2133 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7324 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 303:
#line 2139 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7335 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 304:
#line 2145 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7346 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 305:
#line 2151 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7357 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 306:
#line 2157 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7368 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 307:
#line 2163 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7379 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 308:
#line 2169 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7390 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 309:
#line 2175 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat32Check((yyvsp[0].lex).loc, "float32_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7401 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 310:
#line 2181 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7412 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 311:
#line 2187 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7423 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 312:
#line 2193 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7434 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 313:
#line 2199 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    }
#line 7445 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 314:
#line 2205 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    }
#line 7456 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 315:
#line 2211 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    }
#line 7467 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 316:
#line 2217 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    }
#line 7478 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 317:
#line 2223 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    }
#line 7489 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 318:
#line 2229 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    }
#line 7500 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 319:
#line 2235 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    }
#line 7511 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 320:
#line 2241 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    }
#line 7522 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 321:
#line 2247 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.explicitFloat64Check((yyvsp[0].lex).loc, "float64_t matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    }
#line 7533 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 322:
#line 2253 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef NV_EXTENSIONS
       (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
       (yyval.interm.type).basicType = EbtAccStructNV;
#endif
    }
#line 7544 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 323:
#line 2259 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.vulkanRemoved((yyvsp[0].lex).loc, "atomic counter types");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtAtomicUint;
    }
#line 7554 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 324:
#line 2264 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D);
    }
#line 7564 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 325:
#line 2269 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
    }
#line 7574 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 326:
#line 2274 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd3D);
    }
#line 7584 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 327:
#line 2279 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube);
    }
#line 7594 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 328:
#line 2284 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, false, true);
    }
#line 7604 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 329:
#line 2289 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, true);
    }
#line 7614 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 330:
#line 2294 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, false, true);
    }
#line 7624 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 331:
#line 2299 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true);
    }
#line 7634 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 332:
#line 2304 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true);
    }
#line 7644 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 333:
#line 2309 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true, true);
    }
#line 7654 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 334:
#line 2314 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, true);
    }
#line 7664 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 335:
#line 2319 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true);
    }
#line 7674 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 336:
#line 2324 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true, true);
    }
#line 7684 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 337:
#line 2329 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D);
#endif
    }
#line 7697 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 338:
#line 2337 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D);
#endif
    }
#line 7710 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 339:
#line 2345 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd3D);
#endif
    }
#line 7723 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 340:
#line 2353 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube);
#endif
    }
#line 7736 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 341:
#line 2361 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, false, true);
#endif
    }
#line 7749 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 342:
#line 2369 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, true);
#endif
    }
#line 7762 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 343:
#line 2377 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, false, true);
#endif
    }
#line 7775 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 344:
#line 2385 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true);
#endif
    }
#line 7788 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 345:
#line 2393 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true);
#endif
    }
#line 7801 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 346:
#line 2401 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd1D, true, true);
#endif
    }
#line 7814 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 347:
#line 2409 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, true);
#endif
    }
#line 7827 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 348:
#line 2417 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true);
#endif
    }
#line 7840 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 349:
#line 2425 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdCube, true, true);
#endif
    }
#line 7853 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 350:
#line 2433 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D);
    }
#line 7863 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 351:
#line 2438 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D);
    }
#line 7873 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 352:
#line 2443 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd3D);
    }
#line 7883 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 353:
#line 2448 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube);
    }
#line 7893 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 354:
#line 2453 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D, true);
    }
#line 7903 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 355:
#line 2458 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true);
    }
#line 7913 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 356:
#line 2463 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube, true);
    }
#line 7923 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 357:
#line 2468 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D);
    }
#line 7933 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 358:
#line 2473 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D);
    }
#line 7943 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 359:
#line 2478 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd3D);
    }
#line 7953 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 360:
#line 2483 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube);
    }
#line 7963 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 361:
#line 2488 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D, true);
    }
#line 7973 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 362:
#line 2493 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true);
    }
#line 7983 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 363:
#line 2498 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube, true);
    }
#line 7993 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 364:
#line 2503 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect);
    }
#line 8003 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 365:
#line 2508 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect, false, true);
    }
#line 8013 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 366:
#line 2513 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect);
#endif
    }
#line 8026 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 367:
#line 2521 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdRect, false, true);
#endif
    }
#line 8039 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 368:
#line 2529 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdRect);
    }
#line 8049 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 369:
#line 2534 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdRect);
    }
#line 8059 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 370:
#line 2539 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdBuffer);
    }
#line 8069 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 371:
#line 2544 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, EsdBuffer);
#endif
    }
#line 8082 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 372:
#line 2552 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdBuffer);
    }
#line 8092 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 373:
#line 2557 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdBuffer);
    }
#line 8102 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 374:
#line 2562 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, false, true);
    }
#line 8112 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 375:
#line 2567 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 8125 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 376:
#line 2575 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, false, false, true);
    }
#line 8135 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 377:
#line 2580 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, false, false, true);
    }
#line 8145 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 378:
#line 2585 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, false, true);
    }
#line 8155 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 379:
#line 2590 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float sampler", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 8168 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 380:
#line 2598 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true, false, true);
    }
#line 8178 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 381:
#line 2603 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true, false, true);
    }
#line 8188 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 382:
#line 2608 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(false);
    }
#line 8198 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 383:
#line 2613 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(true);
    }
#line 8208 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 384:
#line 2618 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D);
    }
#line 8218 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 385:
#line 2623 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D);
#endif
    }
#line 8231 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 386:
#line 2631 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D);
    }
#line 8241 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 387:
#line 2636 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D);
#endif
    }
#line 8254 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 388:
#line 2644 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd3D);
    }
#line 8264 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 389:
#line 2649 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd3D);
#endif
    }
#line 8277 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 390:
#line 2657 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube);
    }
#line 8287 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 391:
#line 2662 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube);
#endif
    }
#line 8300 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 392:
#line 2670 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D, true);
    }
#line 8310 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 393:
#line 2675 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd1D, true);
#endif
    }
#line 8323 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 394:
#line 2683 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true);
    }
#line 8333 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 395:
#line 2688 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true);
#endif
    }
#line 8346 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 396:
#line 2696 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube, true);
    }
#line 8356 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 397:
#line 2701 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdCube, true);
#endif
    }
#line 8369 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 398:
#line 2709 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D);
    }
#line 8379 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 399:
#line 2714 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D);
    }
#line 8389 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 400:
#line 2719 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd3D);
    }
#line 8399 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 401:
#line 2724 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube);
    }
#line 8409 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 402:
#line 2729 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D, true);
    }
#line 8419 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 403:
#line 2734 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true);
    }
#line 8429 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 404:
#line 2739 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube, true);
    }
#line 8439 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 405:
#line 2744 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D);
    }
#line 8449 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 406:
#line 2749 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D);
    }
#line 8459 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 407:
#line 2754 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd3D);
    }
#line 8469 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 408:
#line 2759 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube);
    }
#line 8479 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 409:
#line 2764 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D, true);
    }
#line 8489 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 410:
#line 2769 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true);
    }
#line 8499 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 411:
#line 2774 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube, true);
    }
#line 8509 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 412:
#line 2779 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdRect);
    }
#line 8519 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 413:
#line 2784 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdRect);
#endif
    }
#line 8532 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 414:
#line 2792 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdRect);
    }
#line 8542 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 415:
#line 2797 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdRect);
    }
#line 8552 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 416:
#line 2802 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdBuffer);
    }
#line 8562 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 417:
#line 2807 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, EsdBuffer);
#endif
    }
#line 8575 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 418:
#line 2815 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdBuffer);
    }
#line 8585 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 419:
#line 2820 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdBuffer);
    }
#line 8595 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 420:
#line 2825 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, false, false, true);
    }
#line 8605 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 421:
#line 2830 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 8618 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 422:
#line 2838 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, false, false, true);
    }
#line 8628 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 423:
#line 2843 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, false, false, true);
    }
#line 8638 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 424:
#line 2848 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true, false, true);
    }
#line 8648 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 425:
#line 2853 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float texture", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 8661 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 426:
#line 2861 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true, false, true);
    }
#line 8671 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 427:
#line 2866 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true, false, true);
    }
#line 8681 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 428:
#line 2871 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D);
    }
#line 8691 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 429:
#line 2876 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D);
#endif
    }
#line 8704 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 430:
#line 2884 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D);
    }
#line 8714 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 431:
#line 2889 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D);
    }
#line 8724 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 432:
#line 2894 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D);
    }
#line 8734 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 433:
#line 2899 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D);
#endif
    }
#line 8747 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 434:
#line 2907 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D);
    }
#line 8757 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 435:
#line 2912 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D);
    }
#line 8767 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 436:
#line 2917 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd3D);
    }
#line 8777 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 437:
#line 2922 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd3D);
#endif
    }
#line 8790 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 438:
#line 2930 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd3D);
    }
#line 8800 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 439:
#line 2935 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd3D);
    }
#line 8810 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 440:
#line 2940 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdRect);
    }
#line 8820 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 441:
#line 2945 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdRect);
#endif
    }
#line 8833 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 442:
#line 2953 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdRect);
    }
#line 8843 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 443:
#line 2958 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdRect);
    }
#line 8853 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 444:
#line 2963 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube);
    }
#line 8863 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 445:
#line 2968 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube);
#endif
    }
#line 8876 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 446:
#line 2976 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube);
    }
#line 8886 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 447:
#line 2981 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube);
    }
#line 8896 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 448:
#line 2986 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdBuffer);
    }
#line 8906 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 449:
#line 2991 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdBuffer);
#endif
    }
#line 8919 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 450:
#line 2999 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdBuffer);
    }
#line 8929 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 451:
#line 3004 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdBuffer);
    }
#line 8939 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 452:
#line 3009 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D, true);
    }
#line 8949 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 453:
#line 3014 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd1D, true);
#endif
    }
#line 8962 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 454:
#line 3022 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D, true);
    }
#line 8972 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 455:
#line 3027 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D, true);
    }
#line 8982 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 456:
#line 3032 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true);
    }
#line 8992 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 457:
#line 3037 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true);
#endif
    }
#line 9005 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 458:
#line 3045 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true);
    }
#line 9015 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 459:
#line 3050 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true);
    }
#line 9025 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 460:
#line 3055 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube, true);
    }
#line 9035 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 461:
#line 3060 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, EsdCube, true);
#endif
    }
#line 9048 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 462:
#line 3068 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube, true);
    }
#line 9058 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 463:
#line 3073 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube, true);
    }
#line 9068 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 464:
#line 3078 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, false, false, true);
    }
#line 9078 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 465:
#line 3083 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, false, false, true);
#endif
    }
#line 9091 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 466:
#line 3091 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, false, false, true);
    }
#line 9101 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 467:
#line 3096 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, false, false, true);
    }
#line 9111 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 468:
#line 3101 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true, false, true);
    }
#line 9121 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 469:
#line 3106 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float image", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat16, Esd2D, true, false, true);
#endif
    }
#line 9134 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 470:
#line 3114 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true, false, true);
    }
#line 9144 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 471:
#line 3119 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true, false, true);
    }
#line 9154 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 472:
#line 3124 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {  // GL_OES_EGL_image_external
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.external = true;
    }
#line 9165 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 473:
#line 3130 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat);
    }
#line 9176 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 474:
#line 3136 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat, true);
    }
#line 9187 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 475:
#line 3142 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16);
#endif
    }
#line 9201 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 476:
#line 3151 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16OpaqueCheck((yyvsp[0].lex).loc, "half float subpass input", parseContext.symbolTable.atBuiltInLevel());
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat16, true);
#endif
    }
#line 9215 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 477:
#line 3160 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt);
    }
#line 9226 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 478:
#line 3166 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt, true);
    }
#line 9237 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 479:
#line 3172 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint);
    }
#line 9248 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 480:
#line 3178 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.requireStage((yyvsp[0].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint, true);
    }
#line 9259 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 481:
#line 3184 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.type) = (yyvsp[0].interm.type);
        (yyval.interm.type).qualifier.storage = parseContext.symbolTable.atGlobalLevel() ? EvqGlobal : EvqTemporary;
        parseContext.structTypeCheck((yyval.interm.type).loc, (yyval.interm.type));
    }
#line 9269 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 482:
#line 3189 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
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
#line 9287 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 483:
#line 3205 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "highp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqHigh);
    }
#line 9297 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 484:
#line 3210 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "mediump precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqMedium);
    }
#line 9307 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 485:
#line 3215 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.profileRequires((yyvsp[0].lex).loc, ENoProfile, 130, 0, "lowp precision qualifier");
        (yyval.interm.type).init((yyvsp[0].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[0].lex).loc, (yyval.interm.type).qualifier, EpqLow);
    }
#line 9317 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 486:
#line 3223 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { parseContext.nestedStructCheck((yyvsp[-2].lex).loc); }
#line 9323 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 487:
#line 3223 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        TType* structure = new TType((yyvsp[-1].interm.typeList), *(yyvsp[-4].lex).string);
        parseContext.structArrayCheck((yyvsp[-4].lex).loc, *structure);
        TVariable* userTypeDef = new TVariable((yyvsp[-4].lex).string, *structure, true);
        if (! parseContext.symbolTable.insert(*userTypeDef))
            parseContext.error((yyvsp[-4].lex).loc, "redefinition", (yyvsp[-4].lex).string->c_str(), "struct");
        (yyval.interm.type).init((yyvsp[-5].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
#line 9339 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 488:
#line 3234 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { parseContext.nestedStructCheck((yyvsp[-1].lex).loc); }
#line 9345 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 489:
#line 3234 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        TType* structure = new TType((yyvsp[-1].interm.typeList), TString(""));
        (yyval.interm.type).init((yyvsp[-4].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    }
#line 9357 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 490:
#line 3244 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.typeList) = (yyvsp[0].interm.typeList);
    }
#line 9365 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 491:
#line 3247 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
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
#line 9380 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 492:
#line 3260 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);

        parseContext.voidErrorCheck((yyvsp[-2].interm.type).loc, (*(yyvsp[-1].interm.typeList))[0].type->getFieldName(), (yyvsp[-2].interm.type).basicType);
        parseContext.precisionQualifierCheck((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).basicType, (yyvsp[-2].interm.type).qualifier);

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            TType type((yyvsp[-2].interm.type));
            type.setFieldName((*(yyval.interm.typeList))[i].type->getFieldName());
            type.transferArraySizes((*(yyval.interm.typeList))[i].type->getArraySizes());
            type.copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);
            parseContext.arrayOfArrayVersionCheck((*(yyval.interm.typeList))[i].loc, type.getArraySizes());
            (*(yyval.interm.typeList))[i].type->shallowCopy(type);
        }
    }
#line 9407 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 493:
#line 3282 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        if ((yyvsp[-2].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[-2].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck((yyvsp[-2].interm.type).loc, *(yyvsp[-2].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[-1].interm.typeList);

        parseContext.memberQualifierCheck((yyvsp[-3].interm.type));
        parseContext.voidErrorCheck((yyvsp[-2].interm.type).loc, (*(yyvsp[-1].interm.typeList))[0].type->getFieldName(), (yyvsp[-2].interm.type).basicType);
        parseContext.mergeQualifiers((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).qualifier, (yyvsp[-3].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[-2].interm.type).loc, (yyvsp[-2].interm.type).basicType, (yyvsp[-2].interm.type).qualifier);

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            TType type((yyvsp[-2].interm.type));
            type.setFieldName((*(yyval.interm.typeList))[i].type->getFieldName());
            type.transferArraySizes((*(yyval.interm.typeList))[i].type->getArraySizes());
            type.copyArrayInnerSizes((yyvsp[-2].interm.type).arraySizes);
            parseContext.arrayOfArrayVersionCheck((*(yyval.interm.typeList))[i].loc, type.getArraySizes());
            (*(yyval.interm.typeList))[i].type->shallowCopy(type);
        }
    }
#line 9436 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 494:
#line 3309 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.typeList) = new TTypeList;
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 9445 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 495:
#line 3313 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.typeList)->push_back((yyvsp[0].interm.typeLine));
    }
#line 9453 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 496:
#line 3319 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[0].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[0].lex).string);
    }
#line 9463 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 497:
#line 3324 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.arrayOfArrayVersionCheck((yyvsp[-1].lex).loc, (yyvsp[0].interm).arraySizes);

        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[-1].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[-1].lex).string);
        (yyval.interm.typeLine).type->transferArraySizes((yyvsp[0].interm).arraySizes);
    }
#line 9476 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 498:
#line 3335 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 9484 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 499:
#line 3338 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-2].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-2].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-1].interm.intermTypedNode);
    }
#line 9495 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 500:
#line 3344 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[-3].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[-3].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[-2].interm.intermTypedNode);
    }
#line 9506 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 501:
#line 3353 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate(0, (yyvsp[0].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode)->getLoc());
    }
#line 9514 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 502:
#line 3356 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.intermTypedNode));
    }
#line 9522 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 503:
#line 3362 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9528 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 504:
#line 3366 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9534 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 505:
#line 3367 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9540 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 506:
#line 3373 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9546 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 507:
#line 3374 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9552 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 508:
#line 3375 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9558 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 509:
#line 3376 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9564 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 510:
#line 3377 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9570 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 511:
#line 3378 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9576 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 512:
#line 3379 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9582 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 513:
#line 3383 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = 0; }
#line 9588 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 514:
#line 3384 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
    }
#line 9597 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 515:
#line 3388 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
    }
#line 9606 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 516:
#line 3392 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        if ((yyvsp[-2].interm.intermNode) && (yyvsp[-2].interm.intermNode)->getAsAggregate())
            (yyvsp[-2].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-2].interm.intermNode);
    }
#line 9616 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 517:
#line 3400 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9622 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 518:
#line 3401 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode); }
#line 9628 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 519:
#line 3405 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        ++parseContext.controlFlowNestingLevel;
    }
#line 9636 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 520:
#line 3408 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9645 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 521:
#line 3412 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 9655 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 522:
#line 3417 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9666 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 523:
#line 3426 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = 0;
    }
#line 9674 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 524:
#line 3429 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        if ((yyvsp[-1].interm.intermNode) && (yyvsp[-1].interm.intermNode)->getAsAggregate())
            (yyvsp[-1].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[-1].interm.intermNode);
    }
#line 9684 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 525:
#line 3437 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[0].interm.intermNode));
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence(0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        }
    }
#line 9697 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 526:
#line 3445 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        if ((yyvsp[0].interm.intermNode) && (yyvsp[0].interm.intermNode)->getAsBranchNode() && ((yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[0].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence((yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0, (yyvsp[0].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        } else
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
    }
#line 9710 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 527:
#line 3456 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = 0; }
#line 9716 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 528:
#line 3457 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    { (yyval.interm.intermNode) = static_cast<TIntermNode*>((yyvsp[-1].interm.intermTypedNode)); }
#line 9722 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 529:
#line 3461 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9730 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 530:
#line 3464 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.handleSelectionAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9739 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 531:
#line 3470 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.boolCheck((yyvsp[-4].lex).loc, (yyvsp[-2].interm.intermTypedNode));
        (yyval.interm.intermNode) = parseContext.intermediate.addSelection((yyvsp[-2].interm.intermTypedNode), (yyvsp[0].interm.nodePair), (yyvsp[-4].lex).loc);
    }
#line 9748 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 532:
#line 3477 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermNode);
    }
#line 9757 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 533:
#line 3481 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[0].interm.intermNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 9766 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 534:
#line 3489 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
        parseContext.boolCheck((yyvsp[0].interm.intermTypedNode)->getLoc(), (yyvsp[0].interm.intermTypedNode));
    }
#line 9775 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 535:
#line 3493 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.boolCheck((yyvsp[-2].lex).loc, (yyvsp[-3].interm.type));

        TType type((yyvsp[-3].interm.type));
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[-2].lex).loc, *(yyvsp[-2].lex).string, (yyvsp[-3].interm.type), 0, (yyvsp[0].interm.intermTypedNode));
        if (initNode)
            (yyval.interm.intermTypedNode) = initNode->getAsTyped();
        else
            (yyval.interm.intermTypedNode) = 0;
    }
#line 9790 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 536:
#line 3506 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9798 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 537:
#line 3509 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.handleSwitchAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9807 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 538:
#line 3515 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        // start new switch sequence on the switch stack
        ++parseContext.controlFlowNestingLevel;
        ++parseContext.statementNestingLevel;
        parseContext.switchSequenceStack.push_back(new TIntermSequence);
        parseContext.switchLevel.push_back(parseContext.statementNestingLevel);
        parseContext.symbolTable.push();
    }
#line 9820 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 539:
#line 3523 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = parseContext.addSwitch((yyvsp[-7].lex).loc, (yyvsp[-5].interm.intermTypedNode), (yyvsp[-1].interm.intermNode) ? (yyvsp[-1].interm.intermNode)->getAsAggregate() : 0);
        delete parseContext.switchSequenceStack.back();
        parseContext.switchSequenceStack.pop_back();
        parseContext.switchLevel.pop_back();
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 9834 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 540:
#line 3535 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = 0;
    }
#line 9842 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 541:
#line 3538 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9850 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 542:
#line 3544 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
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
#line 9867 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 543:
#line 3556 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[-1].lex).loc, "cannot appear outside switch statement", "default", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[-1].lex).loc, "cannot be nested inside control flow", "default", "");
        else
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpDefault, (yyvsp[-1].lex).loc);
    }
#line 9881 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 544:
#line 3568 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9889 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 545:
#line 3571 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.handleLoopAttributes(*(yyvsp[-1].interm.attributes), (yyvsp[0].interm.intermNode));
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9898 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 546:
#line 3577 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-1].lex).loc, "while loops not available", "limitation", "");
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 9911 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 547:
#line 3585 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[0].interm.intermNode), (yyvsp[-2].interm.intermTypedNode), 0, true, (yyvsp[-5].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 9923 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 548:
#line 3592 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 9933 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 549:
#line 3597 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[-7].lex).loc, "do-while loops not available", "limitation", "");

        parseContext.boolCheck((yyvsp[0].lex).loc, (yyvsp[-2].interm.intermTypedNode));

        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[-5].interm.intermNode), (yyvsp[-2].interm.intermTypedNode), 0, false, (yyvsp[-4].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 9949 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 550:
#line 3608 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    }
#line 9960 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 551:
#line 3614 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[-3].interm.intermNode), (yyvsp[-5].lex).loc);
        TIntermLoop* forLoop = parseContext.intermediate.addLoop((yyvsp[0].interm.intermNode), reinterpret_cast<TIntermTyped*>((yyvsp[-2].interm.nodePair).node1), reinterpret_cast<TIntermTyped*>((yyvsp[-2].interm.nodePair).node2), true, (yyvsp[-6].lex).loc);
        if (! parseContext.limits.nonInductiveForLoops)
            parseContext.inductiveLoopCheck((yyvsp[-6].lex).loc, (yyvsp[-3].interm.intermNode), forLoop);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyval.interm.intermNode), forLoop, (yyvsp[-6].lex).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    }
#line 9977 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 552:
#line 3629 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9985 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 553:
#line 3632 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 9993 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 554:
#line 3638 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = (yyvsp[0].interm.intermTypedNode);
    }
#line 10001 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 555:
#line 3641 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermTypedNode) = 0;
    }
#line 10009 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 556:
#line 3647 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-1].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = 0;
    }
#line 10018 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 557:
#line 3651 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.nodePair).node1 = (yyvsp[-2].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = (yyvsp[0].interm.intermTypedNode);
    }
#line 10027 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 558:
#line 3658 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        if (parseContext.loopNestingLevel <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "continue statement only allowed in loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpContinue, (yyvsp[-1].lex).loc);
    }
#line 10037 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 559:
#line 3663 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        if (parseContext.loopNestingLevel + parseContext.switchSequenceStack.size() <= 0)
            parseContext.error((yyvsp[-1].lex).loc, "break statement only allowed in switch and loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpBreak, (yyvsp[-1].lex).loc);
    }
#line 10047 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 560:
#line 3668 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpReturn, (yyvsp[-1].lex).loc);
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid)
            parseContext.error((yyvsp[-1].lex).loc, "non-void function must return a value", "return", "");
        if (parseContext.inMain)
            parseContext.postEntryPointReturn = true;
    }
#line 10059 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 561:
#line 3675 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = parseContext.handleReturnValue((yyvsp[-2].lex).loc, (yyvsp[-1].interm.intermTypedNode));
    }
#line 10067 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 562:
#line 3678 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.requireStage((yyvsp[-1].lex).loc, EShLangFragment, "discard");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpKill, (yyvsp[-1].lex).loc);
    }
#line 10076 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 563:
#line 3687 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
        parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
    }
#line 10085 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 564:
#line 3691 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        if ((yyvsp[0].interm.intermNode) != nullptr) {
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-1].interm.intermNode), (yyvsp[0].interm.intermNode));
            parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
        }
    }
#line 10096 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 565:
#line 3700 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 10104 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 566:
#line 3703 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.intermNode) = (yyvsp[0].interm.intermNode);
    }
#line 10112 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 567:
#line 3706 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        parseContext.requireProfile((yyvsp[0].lex).loc, ~EEsProfile, "extraneous semicolon");
        parseContext.profileRequires((yyvsp[0].lex).loc, ~EEsProfile, 460, nullptr, "extraneous semicolon");
        (yyval.interm.intermNode) = nullptr;
    }
#line 10122 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 568:
#line 3714 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyvsp[0].interm).function = parseContext.handleFunctionDeclarator((yyvsp[0].interm).loc, *(yyvsp[0].interm).function, false /* not prototype */);
        (yyvsp[0].interm).intermNode = parseContext.handleFunctionDefinition((yyvsp[0].interm).loc, *(yyvsp[0].interm).function);
    }
#line 10131 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 569:
#line 3718 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        //   May be best done as post process phase on intermediate code
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid && ! parseContext.functionReturnsValue)
            parseContext.error((yyvsp[-2].interm).loc, "function does not return a value:", "", (yyvsp[-2].interm).function->getName().c_str());
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[-2].interm).intermNode, (yyvsp[0].interm.intermNode));
        parseContext.intermediate.setAggregateOperator((yyval.interm.intermNode), EOpFunction, (yyvsp[-2].interm).function->getType(), (yyvsp[-2].interm).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setName((yyvsp[-2].interm).function->getMangledName().c_str());

        // store the pragma information for debug and optimize and other vendor specific
        // information. This information can be queried from the parse tree
        (yyval.interm.intermNode)->getAsAggregate()->setOptimize(parseContext.contextPragma.optimize);
        (yyval.interm.intermNode)->getAsAggregate()->setDebug(parseContext.contextPragma.debug);
        (yyval.interm.intermNode)->getAsAggregate()->setPragmaTable(parseContext.contextPragma.pragmaTable);
    }
#line 10151 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 570:
#line 3736 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.attributes) = (yyvsp[-2].interm.attributes);
        parseContext.requireExtensions((yyvsp[-4].lex).loc, 1, &E_GL_EXT_control_flow_attributes, "attribute");
    }
#line 10160 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 571:
#line 3742 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.attributes) = (yyvsp[0].interm.attributes);
    }
#line 10168 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 572:
#line 3745 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.attributes) = parseContext.mergeAttributes((yyvsp[-2].interm.attributes), (yyvsp[0].interm.attributes));
    }
#line 10176 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 573:
#line 3750 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[0].lex).string);
    }
#line 10184 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;

  case 574:
#line 3753 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1666  */
    {
        (yyval.interm.attributes) = parseContext.makeAttributes(*(yyvsp[-3].lex).string, (yyvsp[-1].interm.intermTypedNode));
    }
#line 10192 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
    break;


#line 10196 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang_tab.cpp" /* yacc.c:1666  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (pParseContext, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (pParseContext, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, pParseContext);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (pParseContext, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp, pParseContext);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 3757 "/Users/neil/Code/glslang/glslang/MachineIndependent/glslang.y" /* yacc.c:1910  */

