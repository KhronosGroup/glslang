
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 41 "glslang.y"


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

using namespace glslang;



/* Line 189 of yacc.c  */
#line 99 "glslang_tab.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ATTRIBUTE = 258,
     VARYING = 259,
     CONST = 260,
     BOOL = 261,
     FLOAT = 262,
     DOUBLE = 263,
     INT = 264,
     UINT = 265,
     INT64_T = 266,
     UINT64_T = 267,
     INT16_T = 268,
     UINT16_T = 269,
     FLOAT16_T = 270,
     BREAK = 271,
     CONTINUE = 272,
     DO = 273,
     ELSE = 274,
     FOR = 275,
     IF = 276,
     DISCARD = 277,
     RETURN = 278,
     SWITCH = 279,
     CASE = 280,
     DEFAULT = 281,
     SUBROUTINE = 282,
     BVEC2 = 283,
     BVEC3 = 284,
     BVEC4 = 285,
     IVEC2 = 286,
     IVEC3 = 287,
     IVEC4 = 288,
     I64VEC2 = 289,
     I64VEC3 = 290,
     I64VEC4 = 291,
     UVEC2 = 292,
     UVEC3 = 293,
     UVEC4 = 294,
     U64VEC2 = 295,
     U64VEC3 = 296,
     U64VEC4 = 297,
     VEC2 = 298,
     VEC3 = 299,
     VEC4 = 300,
     MAT2 = 301,
     MAT3 = 302,
     MAT4 = 303,
     CENTROID = 304,
     IN = 305,
     OUT = 306,
     INOUT = 307,
     UNIFORM = 308,
     PATCH = 309,
     SAMPLE = 310,
     BUFFER = 311,
     SHARED = 312,
     COHERENT = 313,
     VOLATILE = 314,
     RESTRICT = 315,
     READONLY = 316,
     WRITEONLY = 317,
     DVEC2 = 318,
     DVEC3 = 319,
     DVEC4 = 320,
     DMAT2 = 321,
     DMAT3 = 322,
     DMAT4 = 323,
     F16VEC2 = 324,
     F16VEC3 = 325,
     F16VEC4 = 326,
     F16MAT2 = 327,
     F16MAT3 = 328,
     F16MAT4 = 329,
     I16VEC2 = 330,
     I16VEC3 = 331,
     I16VEC4 = 332,
     U16VEC2 = 333,
     U16VEC3 = 334,
     U16VEC4 = 335,
     NOPERSPECTIVE = 336,
     FLAT = 337,
     SMOOTH = 338,
     LAYOUT = 339,
     __EXPLICITINTERPAMD = 340,
     MAT2X2 = 341,
     MAT2X3 = 342,
     MAT2X4 = 343,
     MAT3X2 = 344,
     MAT3X3 = 345,
     MAT3X4 = 346,
     MAT4X2 = 347,
     MAT4X3 = 348,
     MAT4X4 = 349,
     DMAT2X2 = 350,
     DMAT2X3 = 351,
     DMAT2X4 = 352,
     DMAT3X2 = 353,
     DMAT3X3 = 354,
     DMAT3X4 = 355,
     DMAT4X2 = 356,
     DMAT4X3 = 357,
     DMAT4X4 = 358,
     F16MAT2X2 = 359,
     F16MAT2X3 = 360,
     F16MAT2X4 = 361,
     F16MAT3X2 = 362,
     F16MAT3X3 = 363,
     F16MAT3X4 = 364,
     F16MAT4X2 = 365,
     F16MAT4X3 = 366,
     F16MAT4X4 = 367,
     ATOMIC_UINT = 368,
     SAMPLER1D = 369,
     SAMPLER2D = 370,
     SAMPLER3D = 371,
     SAMPLERCUBE = 372,
     SAMPLER1DSHADOW = 373,
     SAMPLER2DSHADOW = 374,
     SAMPLERCUBESHADOW = 375,
     SAMPLER1DARRAY = 376,
     SAMPLER2DARRAY = 377,
     SAMPLER1DARRAYSHADOW = 378,
     SAMPLER2DARRAYSHADOW = 379,
     ISAMPLER1D = 380,
     ISAMPLER2D = 381,
     ISAMPLER3D = 382,
     ISAMPLERCUBE = 383,
     ISAMPLER1DARRAY = 384,
     ISAMPLER2DARRAY = 385,
     USAMPLER1D = 386,
     USAMPLER2D = 387,
     USAMPLER3D = 388,
     USAMPLERCUBE = 389,
     USAMPLER1DARRAY = 390,
     USAMPLER2DARRAY = 391,
     SAMPLER2DRECT = 392,
     SAMPLER2DRECTSHADOW = 393,
     ISAMPLER2DRECT = 394,
     USAMPLER2DRECT = 395,
     SAMPLERBUFFER = 396,
     ISAMPLERBUFFER = 397,
     USAMPLERBUFFER = 398,
     SAMPLERCUBEARRAY = 399,
     SAMPLERCUBEARRAYSHADOW = 400,
     ISAMPLERCUBEARRAY = 401,
     USAMPLERCUBEARRAY = 402,
     SAMPLER2DMS = 403,
     ISAMPLER2DMS = 404,
     USAMPLER2DMS = 405,
     SAMPLER2DMSARRAY = 406,
     ISAMPLER2DMSARRAY = 407,
     USAMPLER2DMSARRAY = 408,
     SAMPLEREXTERNALOES = 409,
     SAMPLER = 410,
     SAMPLERSHADOW = 411,
     TEXTURE1D = 412,
     TEXTURE2D = 413,
     TEXTURE3D = 414,
     TEXTURECUBE = 415,
     TEXTURE1DARRAY = 416,
     TEXTURE2DARRAY = 417,
     ITEXTURE1D = 418,
     ITEXTURE2D = 419,
     ITEXTURE3D = 420,
     ITEXTURECUBE = 421,
     ITEXTURE1DARRAY = 422,
     ITEXTURE2DARRAY = 423,
     UTEXTURE1D = 424,
     UTEXTURE2D = 425,
     UTEXTURE3D = 426,
     UTEXTURECUBE = 427,
     UTEXTURE1DARRAY = 428,
     UTEXTURE2DARRAY = 429,
     TEXTURE2DRECT = 430,
     ITEXTURE2DRECT = 431,
     UTEXTURE2DRECT = 432,
     TEXTUREBUFFER = 433,
     ITEXTUREBUFFER = 434,
     UTEXTUREBUFFER = 435,
     TEXTURECUBEARRAY = 436,
     ITEXTURECUBEARRAY = 437,
     UTEXTURECUBEARRAY = 438,
     TEXTURE2DMS = 439,
     ITEXTURE2DMS = 440,
     UTEXTURE2DMS = 441,
     TEXTURE2DMSARRAY = 442,
     ITEXTURE2DMSARRAY = 443,
     UTEXTURE2DMSARRAY = 444,
     SUBPASSINPUT = 445,
     SUBPASSINPUTMS = 446,
     ISUBPASSINPUT = 447,
     ISUBPASSINPUTMS = 448,
     USUBPASSINPUT = 449,
     USUBPASSINPUTMS = 450,
     IMAGE1D = 451,
     IIMAGE1D = 452,
     UIMAGE1D = 453,
     IMAGE2D = 454,
     IIMAGE2D = 455,
     UIMAGE2D = 456,
     IMAGE3D = 457,
     IIMAGE3D = 458,
     UIMAGE3D = 459,
     IMAGE2DRECT = 460,
     IIMAGE2DRECT = 461,
     UIMAGE2DRECT = 462,
     IMAGECUBE = 463,
     IIMAGECUBE = 464,
     UIMAGECUBE = 465,
     IMAGEBUFFER = 466,
     IIMAGEBUFFER = 467,
     UIMAGEBUFFER = 468,
     IMAGE1DARRAY = 469,
     IIMAGE1DARRAY = 470,
     UIMAGE1DARRAY = 471,
     IMAGE2DARRAY = 472,
     IIMAGE2DARRAY = 473,
     UIMAGE2DARRAY = 474,
     IMAGECUBEARRAY = 475,
     IIMAGECUBEARRAY = 476,
     UIMAGECUBEARRAY = 477,
     IMAGE2DMS = 478,
     IIMAGE2DMS = 479,
     UIMAGE2DMS = 480,
     IMAGE2DMSARRAY = 481,
     IIMAGE2DMSARRAY = 482,
     UIMAGE2DMSARRAY = 483,
     STRUCT = 484,
     VOID = 485,
     WHILE = 486,
     IDENTIFIER = 487,
     TYPE_NAME = 488,
     FLOATCONSTANT = 489,
     DOUBLECONSTANT = 490,
     INTCONSTANT = 491,
     UINTCONSTANT = 492,
     INT64CONSTANT = 493,
     UINT64CONSTANT = 494,
     INT16CONSTANT = 495,
     UINT16CONSTANT = 496,
     BOOLCONSTANT = 497,
     FLOAT16CONSTANT = 498,
     LEFT_OP = 499,
     RIGHT_OP = 500,
     INC_OP = 501,
     DEC_OP = 502,
     LE_OP = 503,
     GE_OP = 504,
     EQ_OP = 505,
     NE_OP = 506,
     AND_OP = 507,
     OR_OP = 508,
     XOR_OP = 509,
     MUL_ASSIGN = 510,
     DIV_ASSIGN = 511,
     ADD_ASSIGN = 512,
     MOD_ASSIGN = 513,
     LEFT_ASSIGN = 514,
     RIGHT_ASSIGN = 515,
     AND_ASSIGN = 516,
     XOR_ASSIGN = 517,
     OR_ASSIGN = 518,
     SUB_ASSIGN = 519,
     LEFT_PAREN = 520,
     RIGHT_PAREN = 521,
     LEFT_BRACKET = 522,
     RIGHT_BRACKET = 523,
     LEFT_BRACE = 524,
     RIGHT_BRACE = 525,
     DOT = 526,
     COMMA = 527,
     COLON = 528,
     EQUAL = 529,
     SEMICOLON = 530,
     BANG = 531,
     DASH = 532,
     TILDE = 533,
     PLUS = 534,
     STAR = 535,
     SLASH = 536,
     PERCENT = 537,
     LEFT_ANGLE = 538,
     RIGHT_ANGLE = 539,
     VERTICAL_BAR = 540,
     CARET = 541,
     AMPERSAND = 542,
     QUESTION = 543,
     INVARIANT = 544,
     PRECISE = 545,
     HIGH_PRECISION = 546,
     MEDIUM_PRECISION = 547,
     LOW_PRECISION = 548,
     PRECISION = 549,
     PACKED = 550,
     RESOURCE = 551,
     SUPERP = 552
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 68 "glslang.y"

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



/* Line 214 of yacc.c  */
#line 468 "glslang_tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */

/* Line 264 of yacc.c  */
#line 102 "glslang.y"


/* windows only pragma */
#ifdef _MSC_VER
    #pragma warning(disable : 4065)
    #pragma warning(disable : 4127)
    #pragma warning(disable : 4244)
#endif

#define parseContext (*pParseContext)
#define yyerror(context, msg) context->parserError(msg)

extern int yylex(YYSTYPE*, TParseContext&);



/* Line 264 of yacc.c  */
#line 497 "glslang_tab.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  273
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   6608

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  298
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  100
/* YYNRULES -- Number of rules.  */
#define YYNRULES  449
/* YYNRULES -- Number of states.  */
#define YYNSTATES  581

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   552

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
     295,   296,   297
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    31,    33,    38,    40,    44,
      47,    50,    52,    54,    56,    59,    62,    65,    67,    70,
      74,    77,    79,    81,    83,    86,    89,    92,    94,    96,
      98,   100,   102,   106,   110,   114,   116,   120,   124,   126,
     130,   134,   136,   140,   144,   148,   152,   154,   158,   162,
     164,   168,   170,   174,   176,   180,   182,   186,   188,   192,
     194,   198,   200,   201,   208,   210,   214,   216,   218,   220,
     222,   224,   226,   228,   230,   232,   234,   236,   238,   242,
     244,   247,   250,   255,   258,   262,   267,   270,   274,   279,
     280,   287,   290,   294,   297,   299,   301,   304,   308,   312,
     315,   319,   322,   324,   327,   329,   331,   333,   337,   342,
     349,   355,   357,   360,   364,   370,   375,   377,   380,   382,
     384,   386,   388,   390,   395,   397,   401,   403,   407,   409,
     411,   413,   416,   418,   420,   422,   424,   426,   428,   430,
     432,   434,   436,   438,   440,   442,   444,   446,   448,   450,
     452,   454,   456,   458,   460,   462,   464,   469,   471,   475,
     477,   480,   483,   487,   491,   496,   498,   500,   502,   504,
     506,   508,   510,   512,   514,   516,   518,   520,   522,   524,
     526,   528,   530,   532,   534,   536,   538,   540,   542,   544,
     546,   548,   550,   552,   554,   556,   558,   560,   562,   564,
     566,   568,   570,   572,   574,   576,   578,   580,   582,   584,
     586,   588,   590,   592,   594,   596,   598,   600,   602,   604,
     606,   608,   610,   612,   614,   616,   618,   620,   622,   624,
     626,   628,   630,   632,   634,   636,   638,   640,   642,   644,
     646,   648,   650,   652,   654,   656,   658,   660,   662,   664,
     666,   668,   670,   672,   674,   676,   678,   680,   682,   684,
     686,   688,   690,   692,   694,   696,   698,   700,   702,   704,
     706,   708,   710,   712,   714,   716,   718,   720,   722,   724,
     726,   728,   730,   732,   734,   736,   738,   740,   742,   744,
     746,   748,   750,   752,   754,   756,   758,   760,   762,   764,
     766,   768,   770,   772,   774,   776,   778,   780,   782,   784,
     786,   788,   790,   792,   794,   796,   798,   800,   802,   804,
     806,   808,   810,   812,   814,   816,   818,   820,   822,   824,
     826,   828,   830,   832,   834,   836,   838,   840,   842,   844,
     846,   848,   850,   852,   854,   856,   858,   860,   862,   864,
     866,   868,   870,   872,   874,   876,   878,   880,   882,   884,
     886,   888,   890,   892,   893,   900,   901,   907,   909,   912,
     916,   921,   923,   927,   929,   932,   934,   938,   943,   945,
     949,   951,   953,   955,   957,   959,   961,   963,   965,   967,
     969,   972,   973,   974,   980,   982,   984,   985,   988,   989,
     992,   995,   999,  1001,  1004,  1006,  1009,  1015,  1019,  1021,
    1023,  1028,  1029,  1038,  1039,  1041,  1045,  1048,  1049,  1056,
    1057,  1066,  1067,  1075,  1077,  1079,  1081,  1082,  1085,  1089,
    1092,  1095,  1098,  1102,  1105,  1107,  1110,  1112,  1114,  1115
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     394,     0,    -1,   232,    -1,   299,    -1,   236,    -1,   237,
      -1,   238,    -1,   239,    -1,   240,    -1,   241,    -1,   234,
      -1,   235,    -1,   243,    -1,   242,    -1,   265,   327,   266,
      -1,   300,    -1,   301,   267,   302,   268,    -1,   303,    -1,
     301,   271,   232,    -1,   301,   246,    -1,   301,   247,    -1,
     327,    -1,   304,    -1,   305,    -1,   307,   266,    -1,   306,
     266,    -1,   308,   230,    -1,   308,    -1,   308,   325,    -1,
     307,   272,   325,    -1,   309,   265,    -1,   353,    -1,   301,
      -1,   301,    -1,   246,   310,    -1,   247,   310,    -1,   311,
     310,    -1,   279,    -1,   277,    -1,   276,    -1,   278,    -1,
     310,    -1,   312,   280,   310,    -1,   312,   281,   310,    -1,
     312,   282,   310,    -1,   312,    -1,   313,   279,   312,    -1,
     313,   277,   312,    -1,   313,    -1,   314,   244,   313,    -1,
     314,   245,   313,    -1,   314,    -1,   315,   283,   314,    -1,
     315,   284,   314,    -1,   315,   248,   314,    -1,   315,   249,
     314,    -1,   315,    -1,   316,   250,   315,    -1,   316,   251,
     315,    -1,   316,    -1,   317,   287,   316,    -1,   317,    -1,
     318,   286,   317,    -1,   318,    -1,   319,   285,   318,    -1,
     319,    -1,   320,   252,   319,    -1,   320,    -1,   321,   254,
     320,    -1,   321,    -1,   322,   253,   321,    -1,   322,    -1,
      -1,   322,   288,   324,   327,   273,   325,    -1,   323,    -1,
     310,   326,   325,    -1,   274,    -1,   255,    -1,   256,    -1,
     258,    -1,   257,    -1,   264,    -1,   259,    -1,   260,    -1,
     261,    -1,   262,    -1,   263,    -1,   325,    -1,   327,   272,
     325,    -1,   323,    -1,   333,   275,    -1,   340,   275,    -1,
     294,   356,   353,   275,    -1,   330,   275,    -1,   330,   232,
     275,    -1,   330,   232,   354,   275,    -1,   349,   275,    -1,
     349,   232,   275,    -1,   349,   232,   332,   275,    -1,    -1,
     349,   232,   269,   331,   360,   270,    -1,   272,   232,    -1,
     332,   272,   232,    -1,   334,   266,    -1,   336,    -1,   335,
      -1,   336,   338,    -1,   335,   272,   338,    -1,   342,   232,
     265,    -1,   353,   232,    -1,   353,   232,   354,    -1,   349,
     337,    -1,   337,    -1,   349,   339,    -1,   339,    -1,   353,
      -1,   341,    -1,   340,   272,   232,    -1,   340,   272,   232,
     354,    -1,   340,   272,   232,   354,   274,   364,    -1,   340,
     272,   232,   274,   364,    -1,   342,    -1,   342,   232,    -1,
     342,   232,   354,    -1,   342,   232,   354,   274,   364,    -1,
     342,   232,   274,   364,    -1,   353,    -1,   349,   353,    -1,
     289,    -1,    83,    -1,    82,    -1,    81,    -1,    85,    -1,
      84,   265,   346,   266,    -1,   347,    -1,   346,   272,   347,
      -1,   232,    -1,   232,   274,   328,    -1,    57,    -1,   290,
      -1,   350,    -1,   349,   350,    -1,   351,    -1,   345,    -1,
     356,    -1,   344,    -1,   343,    -1,   348,    -1,     5,    -1,
       3,    -1,     4,    -1,    52,    -1,    50,    -1,    51,    -1,
      49,    -1,    54,    -1,    55,    -1,    53,    -1,    56,    -1,
      57,    -1,    58,    -1,    59,    -1,    60,    -1,    61,    -1,
      62,    -1,    27,    -1,    27,   265,   352,   266,    -1,   232,
      -1,   352,   272,   232,    -1,   355,    -1,   355,   354,    -1,
     267,   268,    -1,   267,   323,   268,    -1,   354,   267,   268,
      -1,   354,   267,   323,   268,    -1,   230,    -1,     7,    -1,
       8,    -1,    15,    -1,     9,    -1,    10,    -1,    11,    -1,
      12,    -1,    13,    -1,    14,    -1,     6,    -1,    43,    -1,
      44,    -1,    45,    -1,    63,    -1,    64,    -1,    65,    -1,
      69,    -1,    70,    -1,    71,    -1,    28,    -1,    29,    -1,
      30,    -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,
      35,    -1,    36,    -1,    75,    -1,    76,    -1,    77,    -1,
      37,    -1,    38,    -1,    39,    -1,    40,    -1,    41,    -1,
      42,    -1,    78,    -1,    79,    -1,    80,    -1,    46,    -1,
      47,    -1,    48,    -1,    86,    -1,    87,    -1,    88,    -1,
      89,    -1,    90,    -1,    91,    -1,    92,    -1,    93,    -1,
      94,    -1,    66,    -1,    67,    -1,    68,    -1,    95,    -1,
      96,    -1,    97,    -1,    98,    -1,    99,    -1,   100,    -1,
     101,    -1,   102,    -1,   103,    -1,    72,    -1,    73,    -1,
      74,    -1,   104,    -1,   105,    -1,   106,    -1,   107,    -1,
     108,    -1,   109,    -1,   110,    -1,   111,    -1,   112,    -1,
     113,    -1,   114,    -1,   115,    -1,   116,    -1,   117,    -1,
     118,    -1,   119,    -1,   120,    -1,   121,    -1,   122,    -1,
     123,    -1,   124,    -1,   144,    -1,   145,    -1,   125,    -1,
     126,    -1,   127,    -1,   128,    -1,   129,    -1,   130,    -1,
     146,    -1,   131,    -1,   132,    -1,   133,    -1,   134,    -1,
     135,    -1,   136,    -1,   147,    -1,   137,    -1,   138,    -1,
     139,    -1,   140,    -1,   141,    -1,   142,    -1,   143,    -1,
     148,    -1,   149,    -1,   150,    -1,   151,    -1,   152,    -1,
     153,    -1,   155,    -1,   156,    -1,   157,    -1,   158,    -1,
     159,    -1,   160,    -1,   161,    -1,   162,    -1,   181,    -1,
     163,    -1,   164,    -1,   165,    -1,   166,    -1,   167,    -1,
     168,    -1,   182,    -1,   169,    -1,   170,    -1,   171,    -1,
     172,    -1,   173,    -1,   174,    -1,   183,    -1,   175,    -1,
     176,    -1,   177,    -1,   178,    -1,   179,    -1,   180,    -1,
     184,    -1,   185,    -1,   186,    -1,   187,    -1,   188,    -1,
     189,    -1,   196,    -1,   197,    -1,   198,    -1,   199,    -1,
     200,    -1,   201,    -1,   202,    -1,   203,    -1,   204,    -1,
     205,    -1,   206,    -1,   207,    -1,   208,    -1,   209,    -1,
     210,    -1,   211,    -1,   212,    -1,   213,    -1,   214,    -1,
     215,    -1,   216,    -1,   217,    -1,   218,    -1,   219,    -1,
     220,    -1,   221,    -1,   222,    -1,   223,    -1,   224,    -1,
     225,    -1,   226,    -1,   227,    -1,   228,    -1,   154,    -1,
     190,    -1,   191,    -1,   192,    -1,   193,    -1,   194,    -1,
     195,    -1,   357,    -1,   233,    -1,   291,    -1,   292,    -1,
     293,    -1,    -1,   229,   232,   269,   358,   360,   270,    -1,
      -1,   229,   269,   359,   360,   270,    -1,   361,    -1,   360,
     361,    -1,   353,   362,   275,    -1,   349,   353,   362,   275,
      -1,   363,    -1,   362,   272,   363,    -1,   232,    -1,   232,
     354,    -1,   325,    -1,   269,   365,   270,    -1,   269,   365,
     272,   270,    -1,   364,    -1,   365,   272,   364,    -1,   329,
      -1,   369,    -1,   368,    -1,   366,    -1,   378,    -1,   379,
      -1,   382,    -1,   385,    -1,   386,    -1,   393,    -1,   269,
     270,    -1,    -1,    -1,   269,   370,   377,   371,   270,    -1,
     376,    -1,   368,    -1,    -1,   374,   369,    -1,    -1,   375,
     368,    -1,   269,   270,    -1,   269,   377,   270,    -1,   367,
      -1,   377,   367,    -1,   275,    -1,   327,   275,    -1,    21,
     265,   327,   266,   380,    -1,   373,    19,   373,    -1,   373,
      -1,   327,    -1,   342,   232,   274,   364,    -1,    -1,    24,
     265,   327,   266,   383,   269,   384,   270,    -1,    -1,   377,
      -1,    25,   327,   273,    -1,    26,   273,    -1,    -1,   231,
     265,   387,   381,   266,   372,    -1,    -1,    18,   388,   367,
     231,   265,   327,   266,   275,    -1,    -1,    20,   265,   389,
     390,   392,   266,   372,    -1,   378,    -1,   366,    -1,   381,
      -1,    -1,   391,   275,    -1,   391,   275,   327,    -1,    17,
     275,    -1,    16,   275,    -1,    23,   275,    -1,    23,   327,
     275,    -1,    22,   275,    -1,   395,    -1,   394,   395,    -1,
     396,    -1,   329,    -1,    -1,   333,   397,   376,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   253,   253,   259,   262,   265,   269,   273,   277,   283,
     289,   292,   296,   302,   305,   313,   316,   319,   322,   325,
     330,   338,   345,   352,   358,   362,   369,   372,   378,   385,
     395,   403,   408,   438,   444,   448,   452,   472,   473,   474,
     475,   481,   482,   487,   492,   501,   502,   507,   515,   516,
     522,   531,   532,   537,   542,   547,   555,   556,   564,   575,
     576,   585,   586,   595,   596,   605,   606,   614,   615,   623,
     624,   632,   633,   633,   651,   652,   667,   671,   675,   679,
     684,   688,   692,   696,   700,   704,   708,   715,   718,   729,
     736,   741,   746,   754,   758,   762,   766,   771,   776,   785,
     785,   796,   800,   807,   814,   817,   824,   832,   852,   870,
     885,   908,   919,   929,   939,   949,   958,   961,   965,   969,
     974,   982,   987,   992,   997,  1002,  1011,  1022,  1049,  1058,
    1065,  1072,  1079,  1091,  1097,  1100,  1107,  1111,  1115,  1123,
    1132,  1135,  1146,  1149,  1152,  1156,  1160,  1164,  1171,  1175,
    1187,  1201,  1206,  1212,  1218,  1225,  1231,  1236,  1241,  1246,
    1254,  1258,  1262,  1266,  1270,  1274,  1280,  1289,  1292,  1300,
    1304,  1313,  1318,  1326,  1330,  1340,  1344,  1348,  1353,  1360,
    1364,  1369,  1374,  1379,  1386,  1393,  1397,  1402,  1407,  1412,
    1418,  1424,  1430,  1438,  1446,  1454,  1459,  1464,  1469,  1474,
    1479,  1484,  1490,  1496,  1502,  1510,  1518,  1526,  1532,  1538,
    1544,  1550,  1556,  1562,  1570,  1578,  1586,  1591,  1596,  1601,
    1606,  1611,  1616,  1621,  1626,  1631,  1636,  1641,  1646,  1652,
    1658,  1664,  1670,  1676,  1682,  1688,  1694,  1700,  1706,  1712,
    1718,  1726,  1734,  1742,  1750,  1758,  1766,  1774,  1782,  1790,
    1798,  1806,  1814,  1819,  1824,  1829,  1834,  1839,  1844,  1849,
    1854,  1859,  1864,  1869,  1874,  1879,  1884,  1889,  1894,  1899,
    1904,  1909,  1914,  1919,  1924,  1929,  1934,  1939,  1944,  1949,
    1954,  1959,  1964,  1969,  1974,  1979,  1984,  1989,  1994,  1999,
    2004,  2009,  2014,  2019,  2024,  2029,  2034,  2039,  2044,  2049,
    2054,  2059,  2064,  2069,  2074,  2079,  2084,  2089,  2094,  2099,
    2104,  2109,  2114,  2119,  2124,  2129,  2134,  2139,  2144,  2149,
    2154,  2159,  2164,  2169,  2174,  2179,  2184,  2189,  2194,  2199,
    2204,  2209,  2214,  2219,  2224,  2229,  2234,  2239,  2244,  2249,
    2254,  2259,  2264,  2269,  2274,  2279,  2284,  2289,  2294,  2299,
    2304,  2309,  2314,  2319,  2324,  2329,  2334,  2339,  2344,  2349,
    2354,  2359,  2365,  2371,  2377,  2383,  2389,  2395,  2401,  2406,
    2422,  2427,  2432,  2440,  2440,  2451,  2451,  2461,  2464,  2477,
    2495,  2519,  2523,  2529,  2534,  2545,  2548,  2554,  2563,  2566,
    2572,  2576,  2577,  2583,  2584,  2585,  2586,  2587,  2588,  2589,
    2593,  2594,  2598,  2594,  2610,  2611,  2615,  2615,  2622,  2622,
    2636,  2639,  2647,  2655,  2666,  2667,  2671,  2678,  2682,  2690,
    2694,  2707,  2707,  2727,  2730,  2736,  2748,  2760,  2760,  2775,
    2775,  2791,  2791,  2812,  2815,  2821,  2824,  2830,  2834,  2841,
    2846,  2851,  2858,  2861,  2870,  2874,  2881,  2884,  2890,  2890
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ATTRIBUTE", "VARYING", "CONST", "BOOL",
  "FLOAT", "DOUBLE", "INT", "UINT", "INT64_T", "UINT64_T", "INT16_T",
  "UINT16_T", "FLOAT16_T", "BREAK", "CONTINUE", "DO", "ELSE", "FOR", "IF",
  "DISCARD", "RETURN", "SWITCH", "CASE", "DEFAULT", "SUBROUTINE", "BVEC2",
  "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4", "I64VEC2", "I64VEC3",
  "I64VEC4", "UVEC2", "UVEC3", "UVEC4", "U64VEC2", "U64VEC3", "U64VEC4",
  "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4", "CENTROID", "IN", "OUT",
  "INOUT", "UNIFORM", "PATCH", "SAMPLE", "BUFFER", "SHARED", "COHERENT",
  "VOLATILE", "RESTRICT", "READONLY", "WRITEONLY", "DVEC2", "DVEC3",
  "DVEC4", "DMAT2", "DMAT3", "DMAT4", "F16VEC2", "F16VEC3", "F16VEC4",
  "F16MAT2", "F16MAT3", "F16MAT4", "I16VEC2", "I16VEC3", "I16VEC4",
  "U16VEC2", "U16VEC3", "U16VEC4", "NOPERSPECTIVE", "FLAT", "SMOOTH",
  "LAYOUT", "__EXPLICITINTERPAMD", "MAT2X2", "MAT2X3", "MAT2X4", "MAT3X2",
  "MAT3X3", "MAT3X4", "MAT4X2", "MAT4X3", "MAT4X4", "DMAT2X2", "DMAT2X3",
  "DMAT2X4", "DMAT3X2", "DMAT3X3", "DMAT3X4", "DMAT4X2", "DMAT4X3",
  "DMAT4X4", "F16MAT2X2", "F16MAT2X3", "F16MAT2X4", "F16MAT3X2",
  "F16MAT3X3", "F16MAT3X4", "F16MAT4X2", "F16MAT4X3", "F16MAT4X4",
  "ATOMIC_UINT", "SAMPLER1D", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE",
  "SAMPLER1DSHADOW", "SAMPLER2DSHADOW", "SAMPLERCUBESHADOW",
  "SAMPLER1DARRAY", "SAMPLER2DARRAY", "SAMPLER1DARRAYSHADOW",
  "SAMPLER2DARRAYSHADOW", "ISAMPLER1D", "ISAMPLER2D", "ISAMPLER3D",
  "ISAMPLERCUBE", "ISAMPLER1DARRAY", "ISAMPLER2DARRAY", "USAMPLER1D",
  "USAMPLER2D", "USAMPLER3D", "USAMPLERCUBE", "USAMPLER1DARRAY",
  "USAMPLER2DARRAY", "SAMPLER2DRECT", "SAMPLER2DRECTSHADOW",
  "ISAMPLER2DRECT", "USAMPLER2DRECT", "SAMPLERBUFFER", "ISAMPLERBUFFER",
  "USAMPLERBUFFER", "SAMPLERCUBEARRAY", "SAMPLERCUBEARRAYSHADOW",
  "ISAMPLERCUBEARRAY", "USAMPLERCUBEARRAY", "SAMPLER2DMS", "ISAMPLER2DMS",
  "USAMPLER2DMS", "SAMPLER2DMSARRAY", "ISAMPLER2DMSARRAY",
  "USAMPLER2DMSARRAY", "SAMPLEREXTERNALOES", "SAMPLER", "SAMPLERSHADOW",
  "TEXTURE1D", "TEXTURE2D", "TEXTURE3D", "TEXTURECUBE", "TEXTURE1DARRAY",
  "TEXTURE2DARRAY", "ITEXTURE1D", "ITEXTURE2D", "ITEXTURE3D",
  "ITEXTURECUBE", "ITEXTURE1DARRAY", "ITEXTURE2DARRAY", "UTEXTURE1D",
  "UTEXTURE2D", "UTEXTURE3D", "UTEXTURECUBE", "UTEXTURE1DARRAY",
  "UTEXTURE2DARRAY", "TEXTURE2DRECT", "ITEXTURE2DRECT", "UTEXTURE2DRECT",
  "TEXTUREBUFFER", "ITEXTUREBUFFER", "UTEXTUREBUFFER", "TEXTURECUBEARRAY",
  "ITEXTURECUBEARRAY", "UTEXTURECUBEARRAY", "TEXTURE2DMS", "ITEXTURE2DMS",
  "UTEXTURE2DMS", "TEXTURE2DMSARRAY", "ITEXTURE2DMSARRAY",
  "UTEXTURE2DMSARRAY", "SUBPASSINPUT", "SUBPASSINPUTMS", "ISUBPASSINPUT",
  "ISUBPASSINPUTMS", "USUBPASSINPUT", "USUBPASSINPUTMS", "IMAGE1D",
  "IIMAGE1D", "UIMAGE1D", "IMAGE2D", "IIMAGE2D", "UIMAGE2D", "IMAGE3D",
  "IIMAGE3D", "UIMAGE3D", "IMAGE2DRECT", "IIMAGE2DRECT", "UIMAGE2DRECT",
  "IMAGECUBE", "IIMAGECUBE", "UIMAGECUBE", "IMAGEBUFFER", "IIMAGEBUFFER",
  "UIMAGEBUFFER", "IMAGE1DARRAY", "IIMAGE1DARRAY", "UIMAGE1DARRAY",
  "IMAGE2DARRAY", "IIMAGE2DARRAY", "UIMAGE2DARRAY", "IMAGECUBEARRAY",
  "IIMAGECUBEARRAY", "UIMAGECUBEARRAY", "IMAGE2DMS", "IIMAGE2DMS",
  "UIMAGE2DMS", "IMAGE2DMSARRAY", "IIMAGE2DMSARRAY", "UIMAGE2DMSARRAY",
  "STRUCT", "VOID", "WHILE", "IDENTIFIER", "TYPE_NAME", "FLOATCONSTANT",
  "DOUBLECONSTANT", "INTCONSTANT", "UINTCONSTANT", "INT64CONSTANT",
  "UINT64CONSTANT", "INT16CONSTANT", "UINT16CONSTANT", "BOOLCONSTANT",
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
  "storage_qualifier", "type_name_list", "type_specifier",
  "array_specifier", "type_specifier_nonarray", "precision_qualifier",
  "struct_specifier", "$@3", "$@4", "struct_declaration_list",
  "struct_declaration", "struct_declarator_list", "struct_declarator",
  "initializer", "initializer_list", "declaration_statement", "statement",
  "simple_statement", "compound_statement", "$@5", "$@6",
  "statement_no_new_scope", "statement_scoped", "$@7", "$@8",
  "compound_statement_no_new_scope", "statement_list",
  "expression_statement", "selection_statement",
  "selection_rest_statement", "condition", "switch_statement", "$@9",
  "switch_statement_list", "case_label", "iteration_statement", "$@10",
  "$@11", "$@12", "for_init_statement", "conditionopt",
  "for_rest_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", "$@13", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
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
     545,   546,   547,   548,   549,   550,   551,   552
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   298,   299,   300,   300,   300,   300,   300,   300,   300,
     300,   300,   300,   300,   300,   301,   301,   301,   301,   301,
     301,   302,   303,   304,   305,   305,   306,   306,   307,   307,
     308,   309,   309,   310,   310,   310,   310,   311,   311,   311,
     311,   312,   312,   312,   312,   313,   313,   313,   314,   314,
     314,   315,   315,   315,   315,   315,   316,   316,   316,   317,
     317,   318,   318,   319,   319,   320,   320,   321,   321,   322,
     322,   323,   324,   323,   325,   325,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   327,   327,   328,
     329,   329,   329,   329,   329,   329,   329,   329,   329,   331,
     330,   332,   332,   333,   334,   334,   335,   335,   336,   337,
     337,   338,   338,   338,   338,   339,   340,   340,   340,   340,
     340,   341,   341,   341,   341,   341,   342,   342,   343,   344,
     344,   344,   344,   345,   346,   346,   347,   347,   347,   348,
     349,   349,   350,   350,   350,   350,   350,   350,   351,   351,
     351,   351,   351,   351,   351,   351,   351,   351,   351,   351,
     351,   351,   351,   351,   351,   351,   351,   352,   352,   353,
     353,   354,   354,   354,   354,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     356,   356,   356,   358,   357,   359,   357,   360,   360,   361,
     361,   362,   362,   363,   363,   364,   364,   364,   365,   365,
     366,   367,   367,   368,   368,   368,   368,   368,   368,   368,
     369,   370,   371,   369,   372,   372,   374,   373,   375,   373,
     376,   376,   377,   377,   378,   378,   379,   380,   380,   381,
     381,   383,   382,   384,   384,   385,   385,   387,   386,   388,
     386,   389,   386,   390,   390,   391,   391,   392,   392,   393,
     393,   393,   393,   393,   394,   394,   395,   395,   397,   396
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     4,     1,     3,     2,
       2,     1,     1,     1,     2,     2,     2,     1,     2,     3,
       2,     1,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       2,     2,     4,     2,     3,     4,     2,     3,     4,     0,
       6,     2,     3,     2,     1,     1,     2,     3,     3,     2,
       3,     2,     1,     2,     1,     1,     1,     3,     4,     6,
       5,     1,     2,     3,     5,     4,     1,     2,     1,     1,
       1,     1,     1,     4,     1,     3,     1,     3,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     3,     1,
       2,     2,     3,     3,     4,     1,     1,     1,     1,     1,
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
       1,     1,     1,     0,     6,     0,     5,     1,     2,     3,
       4,     1,     3,     1,     2,     1,     3,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     0,     0,     5,     1,     1,     0,     2,     0,     2,
       2,     3,     1,     2,     1,     2,     5,     3,     1,     1,
       4,     0,     8,     0,     1,     3,     2,     0,     6,     0,
       8,     0,     7,     1,     1,     1,     0,     2,     3,     2,
       2,     2,     3,     2,     1,     2,     1,     1,     0,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   149,   150,   148,   185,   176,   177,   179,   180,   181,
     182,   183,   184,   178,   165,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   207,   208,   209,   210,   211,   212,
     186,   187,   188,   216,   217,   218,   154,   152,   153,   151,
     157,   155,   156,   158,   159,   160,   161,   162,   163,   164,
     189,   190,   191,   228,   229,   230,   192,   193,   194,   240,
     241,   242,   204,   205,   206,   213,   214,   215,   131,   130,
     129,     0,   132,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   266,   267,   268,   269,   270,   271,   273,   274,
     275,   276,   277,   278,   280,   281,   282,   283,   284,   285,
     286,   264,   265,   272,   279,   287,   288,   289,   290,   291,
     292,   361,   293,   294,   295,   296,   297,   298,   299,   300,
     302,   303,   304,   305,   306,   307,   309,   310,   311,   312,
     313,   314,   316,   317,   318,   319,   320,   321,   301,   308,
     315,   322,   323,   324,   325,   326,   327,   362,   363,   364,
     365,   366,   367,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,     0,   175,   369,   128,
     139,   370,   371,   372,     0,   447,     0,   448,     0,   105,
     104,     0,   116,   121,   146,   145,   143,   147,     0,   140,
     142,   126,   169,   144,   368,     0,   444,   446,     0,     0,
       0,   375,     0,     0,    93,    90,     0,   103,     0,   112,
     106,   114,     0,   115,     0,    91,   122,     0,    96,   141,
     127,     0,   170,     1,   445,   167,     0,   138,   136,     0,
     134,   373,     0,     0,    94,     0,     0,   449,   107,   111,
     113,   109,   117,   108,     0,   123,    99,     0,    97,     0,
       2,    10,    11,     4,     5,     6,     7,     8,     9,    13,
      12,     0,     0,     0,   171,    39,    38,    40,    37,     3,
      15,    33,    17,    22,    23,     0,     0,    27,     0,    41,
       0,    45,    48,    51,    56,    59,    61,    63,    65,    67,
      69,    71,     0,    31,     0,   166,     0,     0,   133,     0,
       0,     0,     0,     0,   377,    92,    95,     0,     0,   429,
       0,     0,     0,     0,     0,     0,     0,     0,   401,   410,
     414,    41,    74,    87,     0,   390,     0,   126,   393,   412,
     392,   391,     0,   394,   395,   396,   397,   398,   399,   110,
       0,   118,     0,   385,   125,     0,     0,   101,     0,    98,
      34,    35,     0,    19,    20,     0,     0,    25,    24,     0,
     175,    28,    30,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    72,   172,   173,     0,   168,    89,   137,
     135,     0,     0,   383,     0,   381,   376,   378,   440,   439,
       0,   431,     0,   443,   441,     0,     0,     0,   426,   427,
     400,     0,    77,    78,    80,    79,    82,    83,    84,    85,
      86,    81,    76,     0,     0,   415,   411,   413,   120,     0,
     388,     0,   124,     0,   102,    14,     0,    21,    18,    29,
      42,    43,    44,    47,    46,    49,    50,    54,    55,    52,
      53,    57,    58,    60,    62,    64,    66,    68,    70,     0,
     174,   374,     0,   384,     0,   379,     0,     0,     0,   442,
       0,   425,     0,   402,    75,    88,   119,   386,     0,   100,
      16,     0,   380,   382,     0,   434,   433,   436,   408,   421,
     419,     0,     0,     0,     0,   387,   389,     0,     0,   435,
       0,     0,   418,     0,     0,   416,     0,     0,     0,   403,
      73,     0,   437,     0,   408,   407,   409,   423,     0,   405,
     428,   404,     0,   438,   432,   417,   424,     0,   420,   430,
     422
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   319,   320,   321,   486,   322,   323,   324,   325,   326,
     327,   328,   371,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   372,   509,   373,   473,   374,
     439,   375,   226,   396,   299,   376,   228,   229,   230,   259,
     260,   261,   231,   232,   233,   234,   235,   236,   279,   280,
     237,   238,   239,   240,   276,   343,   272,   242,   243,   244,
     350,   282,   353,   354,   444,   445,   394,   481,   378,   379,
     380,   381,   461,   544,   570,   552,   553,   554,   571,   382,
     383,   384,   555,   543,   385,   556,   577,   386,   387,   522,
     450,   517,   537,   550,   551,   388,   245,   246,   247,   256
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -522
static const yytype_int16 yypact[] =
{
    2618,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -224,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -217,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -214,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -261,  -522,  -215,  -213,  -184,  -182,
    4254,  -196,  -522,  -122,  -522,  -522,  -522,  -522,  3177,  -522,
    -522,  -522,  -129,  -522,  -522,   574,  -522,  -522,   -90,   -48,
    -125,  -522,  6375,  -232,  -522,  -522,  -117,  -522,  4254,  -522,
    -522,  -522,  4254,   -75,   -74,  -522,  -240,  -183,  -522,  -522,
    -522,  4759,  -108,  -522,  -522,  -522,  -179,  -522,  -114,  -175,
    -522,  -522,  4254,  -113,  -522,  -216,   866,  -522,  -522,  -522,
    -522,  -129,  -222,  -522,  5033,  -193,  -522,   -71,  -522,  -158,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  5855,  5855,  5855,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -227,  -522,  -522,  -522,  -102,  -164,  6115,  -100,  -522,
    5855,  -145,  -199,  -195,  -226,  -128,  -124,  -120,  -116,   -82,
     -83,  -225,   -96,  -522,  5307,  -522,   -59,  5855,  -522,   -48,
    4254,  4254,   -58,  3450,  -522,  -522,  -522,   -99,   -98,  -522,
     -87,   -86,   -95,  5581,   -84,  5855,   -88,   -79,   -80,  -522,
    -522,  -191,  -522,  -522,  -156,  -522,  -213,   -78,  -522,  -522,
    -522,  -522,  1158,  -522,  -522,  -522,  -522,  -522,  -522,  -108,
    5033,  -190,  5033,  -522,  -522,  5033,  4254,  -522,   -57,  -522,
    -522,  -522,  -163,  -522,  -522,  5855,   -41,  -522,  -522,  5855,
     -73,  -522,  -522,  -522,  5855,  5855,  5855,  5855,  5855,  5855,
    5855,  5855,  5855,  5855,  5855,  5855,  5855,  5855,  5855,  5855,
    5855,  5855,  5855,  -522,  -522,  -522,   -76,  -522,  -522,  -522,
    -522,  3718,   -58,  -129,  -143,  -522,  -522,  -522,  -522,  -522,
    1450,  -522,  5855,  -522,  -522,  -142,  5855,  -178,  -522,  -522,
    -522,  1450,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  5855,  5855,  -522,  -522,  -522,  -522,  5033,
    -522,  -131,  -522,  3986,  -522,  -522,   -72,   -77,  -522,  -522,
    -522,  -522,  -522,  -145,  -145,  -199,  -199,  -195,  -195,  -195,
    -195,  -226,  -226,  -128,  -124,  -120,  -116,   -82,   -83,  5855,
    -522,  -522,  -141,  -108,   -58,  -522,   -37,  2326,  -161,  -522,
    -160,  -522,  2886,  1450,  -522,  -522,  -522,  -522,  4485,  -522,
    -522,  -127,  -522,  -522,   -68,  -522,  -522,  2886,   -70,  -522,
     -77,   -30,  4254,   -63,   -66,  -522,  -522,  5855,  5855,  -522,
     -69,   -61,   188,   -55,  2034,  -522,   -54,   -64,  1742,  -522,
    -522,  -159,  5855,  1742,   -70,  -522,  -522,  1450,  5033,  -522,
    -522,  -522,   -56,   -77,  -522,  -522,  1450,   -53,  -522,  -522,
    -522
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -103,  -522,  -267,  -266,  -296,  -270,  -211,  -210,
    -218,  -209,  -208,  -212,  -522,  -259,  -522,  -291,  -522,  -309,
    -522,     5,  -522,  -522,  -522,     6,  -522,  -522,  -522,   -40,
     -34,   -36,  -522,  -522,  -498,  -522,  -522,  -522,  -522,  -118,
    -522,  -229,  -236,  -522,  -522,     0,  -245,  -522,     1,  -522,
    -522,  -522,  -335,  -343,  -207,  -285,  -379,  -522,  -284,  -375,
    -521,  -321,  -522,  -522,  -329,  -328,  -522,  -522,   -16,  -447,
    -275,  -522,  -522,  -294,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,     2,  -522,  -522
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -407
static const yytype_int16 yytable[] =
{
     241,   262,   269,   393,   402,   225,   227,   477,   285,   277,
     447,   478,   342,   480,   523,   441,   482,   253,   250,   403,
     404,   295,   421,   422,   541,   293,   269,   271,   432,   262,
     221,   222,   223,   566,   294,   271,   411,   569,   -32,   541,
     405,   248,   569,   284,   406,   271,   389,   391,   249,   419,
     420,   344,   390,   351,   455,   251,   457,   423,   424,   356,
     254,   483,   255,   433,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   344,   516,   264,   344,   417,   265,
     418,   395,   257,   472,   479,   436,   296,   345,   438,   297,
     258,   348,   298,   346,   474,   521,   487,   349,   447,   393,
     526,   393,   408,   485,   393,   538,   539,   572,   409,   474,
     266,   474,   474,   474,   398,   269,   474,   399,   489,   475,
     576,   351,   425,   426,   351,   497,   498,   499,   500,   514,
     474,   514,   515,   519,   532,   414,   415,   416,   271,   527,
     447,   528,   275,   518,   281,   474,   547,   520,   477,   546,
     493,   494,   286,   495,   496,   501,   502,   291,   292,   344,
     347,   397,   355,   427,   407,   412,   428,   351,   329,   429,
     430,   431,   434,   437,   443,   484,   448,   449,   451,   452,
     453,   456,   524,   525,   278,   458,   459,   -31,   393,   578,
     460,   488,   510,   -26,   534,   474,   530,   548,   513,  -406,
     531,   477,   557,   558,   559,   563,   562,   564,   400,   401,
     568,   505,   351,   540,   368,   567,   503,   580,   504,   579,
     508,   506,   289,   507,   288,   252,   290,   413,   540,   533,
     263,   440,   565,   535,   574,   512,   575,   393,   270,   561,
     287,   329,   536,   549,   329,   241,     0,   274,     0,     0,
     225,   227,   283,   573,   351,     0,   560,     0,   263,     0,
       0,     0,   263,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   393,     0,     0,
       0,     0,   352,     0,     0,     0,   377,     0,     0,     0,
       0,     0,     0,   542,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   269,     0,   542,     0,
       0,   490,   491,   492,   329,   329,   329,   329,   329,   329,
     329,   329,   329,   329,   329,   329,   329,   329,   329,   329,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     352,   442,     0,   352,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   377,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   352,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   352,     0,     0,     0,     0,     0,     0,     0,     0,
     377,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   377,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   352,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   377,     0,     0,
       0,     0,   377,   377,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   377,     0,     0,
       0,     0,   270,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   377,     0,     0,     0,   377,     0,
       0,     0,     0,   377,     0,     0,     0,   377,     0,     0,
       0,     0,     0,     0,   273,     0,   377,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
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
     213,   214,   215,   216,   217,     0,     0,   218,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   219,   220,   221,   222,   223,   224,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   357,   358,   359,     0,   360,   361,   362,   363,
     364,   365,   366,    14,    15,    16,    17,    18,    19,    20,
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
     211,   212,   213,   214,   215,   216,   217,   367,   300,   218,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
       0,     0,   311,   312,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   313,     0,     0,     0,   368,   369,     0,     0,     0,
       0,   370,   315,   316,   317,   318,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   219,   220,   221,   222,   223,
     224,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   357,   358,   359,     0,   360,   361,
     362,   363,   364,   365,   366,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
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
     209,   210,   211,   212,   213,   214,   215,   216,   217,   367,
     300,   218,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,     0,     0,   311,   312,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   313,     0,     0,     0,   368,   476,     0,
       0,     0,     0,   370,   315,   316,   317,   318,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   219,   220,   221,
     222,   223,   224,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   357,   358,   359,     0,
     360,   361,   362,   363,   364,   365,   366,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
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
     217,   367,   300,   218,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,     0,     0,   311,   312,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   313,     0,     0,     0,   368,
       0,     0,     0,     0,     0,   370,   315,   316,   317,   318,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   219,
     220,   221,   222,   223,   224,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,   357,   358,
     359,     0,   360,   361,   362,   363,   364,   365,   366,    14,
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
     215,   216,   217,   367,   300,   218,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,     0,     0,   311,   312,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   313,     0,     0,
       0,   286,     0,     0,     0,     0,     0,   370,   315,   316,
     317,   318,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   219,   220,   221,   222,   223,   224,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     357,   358,   359,     0,   360,   361,   362,   363,   364,   365,
     366,    14,    15,    16,    17,    18,    19,    20,    21,    22,
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
     213,   214,   215,   216,   217,   367,   300,   218,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,     0,     0,
     311,   312,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   313,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   370,
     315,   316,   317,   318,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   219,   220,   221,   222,   223,   224,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    14,    15,    16,    17,    18,    19,    20,
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
     211,   212,   213,   214,   215,   216,   217,     0,   300,   218,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
       0,     0,   311,   312,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   313,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   370,   315,   316,   317,   318,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   219,   220,   221,   222,   223,
     224,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
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
     209,   210,   211,   212,   213,   214,   215,   216,   217,     0,
       0,   218,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,   219,   220,   221,
     222,   223,   224,    14,    15,    16,    17,    18,    19,    20,
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
     211,   212,   213,   214,   215,   216,   217,     0,   300,   218,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
       0,     0,   311,   312,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   313,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   315,   316,   317,   318,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   219,   220,   221,   222,   223,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    14,    15,    16,    17,    18,    19,
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
     210,   211,   212,   213,   214,   215,   216,   217,     0,   267,
     218,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   268,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   219,   220,   221,   222,
     223,     0,     0,     0,     0,     0,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
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
     217,     0,     0,   218,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     446,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,     0,   219,
     220,   221,   222,   223,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
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
     209,   210,   211,   212,   213,   214,   215,   216,   217,     0,
       0,   218,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   511,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,   219,   220,   221,
     222,   223,     0,    14,    15,    16,    17,    18,    19,    20,
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
     211,   212,   213,   214,   215,   216,   217,     0,     0,   218,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   529,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,     0,   219,   220,   221,   222,   223,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
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
     213,   214,   215,   216,   217,     0,     0,   218,     0,     0,
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   219,   220,   221,   222,   223,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,    79,    80,    81,
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
     212,   213,   214,   215,   216,   217,     0,   300,   218,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,     0,
       0,   311,   312,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     313,     0,     0,     0,   392,   545,     0,     0,     0,     0,
       0,   315,   316,   317,   318,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     0,     0,     0,     0,    73,    74,    75,    76,    77,
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
       0,   300,   218,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,     0,     0,   311,   312,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   313,     0,     0,   314,     0,     0,
       0,     0,     0,     0,     0,   315,   316,   317,   318,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,     0,     0,     0,    73,
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
     214,   215,   216,   217,     0,   300,   218,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,     0,     0,   311,
     312,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   313,     0,
       0,     0,   392,     0,     0,     0,     0,     0,     0,   315,
     316,   317,   318,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     0,     0,
       0,     0,     0,    73,    74,    75,    76,    77,    78,    79,
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
     210,   211,   212,   213,   214,   215,   216,   217,     0,   300,
     218,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,     0,     0,   311,   312,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   313,     0,     0,   435,     0,     0,     0,     0,
       0,     0,     0,   315,   316,   317,   318,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,     0,     0,     0,     0,     0,    73,    74,    75,
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
     216,   217,     0,   300,   218,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,     0,     0,   311,   312,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   313,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   454,   315,   316,   317,
     318,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,    79,    80,    81,
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
     212,   213,   214,   215,   216,   217,     0,   300,   218,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,     0,
       0,   311,   312,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     313,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   315,   316,   317,   318,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,    79,    80,    81,
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
     212,   213,   214,   215,   216,   410,     0,   300,   218,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,     0,
       0,   311,   312,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     313,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   315,   316,   317,   318,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,    79,    80,    81,
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
     212,   213,   214,   215,   216,   217,     0,     0,   218
};

static const yytype_int16 yycheck[] =
{
       0,   230,   238,   294,   313,     0,     0,   382,   253,    57,
     353,   390,   271,   392,   461,   350,   395,   232,   232,   246,
     247,   266,   248,   249,   522,   265,   262,   267,   253,   258,
     291,   292,   293,   554,   274,   267,   327,   558,   265,   537,
     267,   265,   563,   275,   271,   267,   291,   292,   265,   244,
     245,   267,   274,   282,   363,   269,   365,   283,   284,   275,
     275,   396,   275,   288,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   267,   450,   272,   267,   277,   275,
     279,   274,   266,   274,   274,   344,   269,   266,   347,   272,
     272,   266,   275,   272,   272,   273,   405,   272,   441,   390,
     479,   392,   266,   266,   395,   266,   266,   266,   272,   272,
     232,   272,   272,   272,   272,   351,   272,   275,   409,   275,
     567,   350,   250,   251,   353,   421,   422,   423,   424,   272,
     272,   272,   275,   275,   275,   280,   281,   282,   267,   270,
     483,   272,   232,   452,   269,   272,   273,   456,   523,   528,
     417,   418,   269,   419,   420,   425,   426,   232,   232,   267,
     274,   232,   275,   287,   266,   265,   286,   396,   271,   285,
     252,   254,   268,   232,   232,   232,   275,   275,   265,   265,
     275,   265,   473,   474,   232,   273,   265,   265,   479,   568,
     270,   232,   268,   266,   231,   272,   268,   265,   443,   269,
     509,   576,   232,   266,   270,   266,   275,    19,   311,   312,
     274,   429,   441,   522,   269,   269,   427,   270,   428,   275,
     432,   430,   262,   431,   258,   224,   262,   330,   537,   514,
     230,   349,   553,   517,   563,   442,   564,   528,   238,   548,
     256,   344,   517,   537,   347,   245,    -1,   245,    -1,    -1,
     245,   245,   252,   562,   483,    -1,   547,    -1,   258,    -1,
      -1,    -1,   262,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   568,    -1,    -1,
      -1,    -1,   282,    -1,    -1,    -1,   286,    -1,    -1,    -1,
      -1,    -1,    -1,   522,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   542,    -1,   537,    -1,
      -1,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     350,   351,    -1,   353,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   382,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   396,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   441,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     450,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   461,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   483,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   517,    -1,    -1,
      -1,    -1,   522,   523,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   537,    -1,    -1,
      -1,    -1,   542,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   554,    -1,    -1,    -1,   558,    -1,
      -1,    -1,    -1,   563,    -1,    -1,    -1,   567,    -1,    -1,
      -1,    -1,    -1,    -1,     0,    -1,   576,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    28,    29,    30,    31,    32,    33,    34,    35,
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
     226,   227,   228,   229,   230,    -1,    -1,   233,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   289,   290,   291,   292,   293,   294,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    20,    21,    22,    23,
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
      -1,    -1,   246,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   265,    -1,    -1,    -1,   269,   270,    -1,    -1,    -1,
      -1,   275,   276,   277,   278,   279,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   289,   290,   291,   292,   293,
     294,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    20,    21,
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
     242,   243,    -1,    -1,   246,   247,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   265,    -1,    -1,    -1,   269,   270,    -1,
      -1,    -1,    -1,   275,   276,   277,   278,   279,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   289,   290,   291,
     292,   293,   294,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
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
     240,   241,   242,   243,    -1,    -1,   246,   247,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   265,    -1,    -1,    -1,   269,
      -1,    -1,    -1,    -1,    -1,   275,   276,   277,   278,   279,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   289,
     290,   291,   292,   293,   294,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
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
     238,   239,   240,   241,   242,   243,    -1,    -1,   246,   247,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,    -1,    -1,
      -1,   269,    -1,    -1,    -1,    -1,    -1,   275,   276,   277,
     278,   279,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   289,   290,   291,   292,   293,   294,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    20,    21,    22,    23,    24,    25,
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
     236,   237,   238,   239,   240,   241,   242,   243,    -1,    -1,
     246,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   275,
     276,   277,   278,   279,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   289,   290,   291,   292,   293,   294,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    29,    30,    31,    32,    33,
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
     224,   225,   226,   227,   228,   229,   230,    -1,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
      -1,    -1,   246,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   265,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   275,   276,   277,   278,   279,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   289,   290,   291,   292,   293,
     294,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    29,    30,    31,
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
     222,   223,   224,   225,   226,   227,   228,   229,   230,    -1,
      -1,   233,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,   289,   290,   291,
     292,   293,   294,    27,    28,    29,    30,    31,    32,    33,
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
     224,   225,   226,   227,   228,   229,   230,    -1,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
      -1,    -1,   246,   247,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   265,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   276,   277,   278,   279,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   289,   290,   291,   292,   293,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    31,    32,
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
     223,   224,   225,   226,   227,   228,   229,   230,    -1,   232,
     233,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   275,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,   289,   290,   291,   292,
     293,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,
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
     230,    -1,    -1,   233,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     270,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,   289,
     290,   291,   292,   293,    -1,    27,    28,    29,    30,    31,
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
     222,   223,   224,   225,   226,   227,   228,   229,   230,    -1,
      -1,   233,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   270,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,   289,   290,   291,
     292,   293,    -1,    27,    28,    29,    30,    31,    32,    33,
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
     224,   225,   226,   227,   228,   229,   230,    -1,    -1,   233,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   270,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,   289,   290,   291,   292,   293,
      -1,    27,    28,    29,    30,    31,    32,    33,    34,    35,
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
     226,   227,   228,   229,   230,    -1,    -1,   233,    -1,    -1,
      -1,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   289,   290,   291,   292,   293,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,    93,    94,
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
     225,   226,   227,   228,   229,   230,    -1,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,    -1,
      -1,   246,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     265,    -1,    -1,    -1,   269,   270,    -1,    -1,    -1,    -1,
      -1,   276,   277,   278,   279,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,    90,
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
      -1,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,    -1,    -1,   246,   247,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   265,    -1,    -1,   268,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   276,   277,   278,   279,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,    86,
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
     227,   228,   229,   230,    -1,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,    -1,    -1,   246,
     247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,    -1,
      -1,    -1,   269,    -1,    -1,    -1,    -1,    -1,    -1,   276,
     277,   278,   279,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,    92,
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
     223,   224,   225,   226,   227,   228,   229,   230,    -1,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,    -1,    -1,   246,   247,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   265,    -1,    -1,   268,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   276,   277,   278,   279,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,
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
     229,   230,    -1,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,    -1,    -1,   246,   247,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   265,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   275,   276,   277,   278,
     279,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,    93,    94,
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
     225,   226,   227,   228,   229,   230,    -1,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,    -1,
      -1,   246,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     265,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,   276,   277,   278,   279,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,    93,    94,
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
     225,   226,   227,   228,   229,   230,    -1,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,    -1,
      -1,   246,   247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     265,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,   276,   277,   278,   279,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,    93,    94,
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
     225,   226,   227,   228,   229,   230,    -1,    -1,   233
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    27,    28,    29,    30,    31,    32,
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
     223,   224,   225,   226,   227,   228,   229,   230,   233,   289,
     290,   291,   292,   293,   294,   329,   330,   333,   334,   335,
     336,   340,   341,   342,   343,   344,   345,   348,   349,   350,
     351,   353,   355,   356,   357,   394,   395,   396,   265,   265,
     232,   269,   356,   232,   275,   275,   397,   266,   272,   337,
     338,   339,   349,   353,   272,   275,   232,   232,   275,   350,
     353,   267,   354,     0,   395,   232,   352,    57,   232,   346,
     347,   269,   359,   353,   275,   354,   269,   376,   338,   337,
     339,   232,   232,   265,   274,   354,   269,   272,   275,   332,
     232,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   246,   247,   265,   268,   276,   277,   278,   279,   299,
     300,   301,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   353,   267,   266,   272,   274,   266,   272,
     358,   349,   353,   360,   361,   275,   275,    16,    17,    18,
      20,    21,    22,    23,    24,    25,    26,   231,   269,   270,
     275,   310,   323,   325,   327,   329,   333,   353,   366,   367,
     368,   369,   377,   378,   379,   382,   385,   386,   393,   354,
     274,   354,   269,   325,   364,   274,   331,   232,   272,   275,
     310,   310,   327,   246,   247,   267,   271,   266,   266,   272,
     230,   325,   265,   310,   280,   281,   282,   277,   279,   244,
     245,   248,   249,   283,   284,   250,   251,   287,   286,   285,
     252,   254,   253,   288,   268,   268,   323,   232,   323,   328,
     347,   360,   353,   232,   362,   363,   270,   361,   275,   275,
     388,   265,   265,   275,   275,   327,   265,   327,   273,   265,
     270,   370,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   274,   326,   272,   275,   270,   367,   364,   274,
     364,   365,   364,   360,   232,   266,   302,   327,   232,   325,
     310,   310,   310,   312,   312,   313,   313,   314,   314,   314,
     314,   315,   315,   316,   317,   318,   319,   320,   321,   324,
     268,   270,   362,   354,   272,   275,   367,   389,   327,   275,
     327,   273,   387,   377,   325,   325,   364,   270,   272,   270,
     268,   327,   275,   363,   231,   366,   378,   390,   266,   266,
     327,   342,   349,   381,   371,   270,   364,   273,   265,   381,
     391,   392,   373,   374,   375,   380,   383,   232,   266,   270,
     325,   327,   275,   266,    19,   369,   368,   269,   274,   368,
     372,   376,   266,   327,   372,   373,   377,   384,   364,   275,
     270
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (pParseContext, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, parseContext)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, pParseContext); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, pParseContext)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    glslang::TParseContext* pParseContext;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (pParseContext);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, glslang::TParseContext* pParseContext)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, pParseContext)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    glslang::TParseContext* pParseContext;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, pParseContext);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, glslang::TParseContext* pParseContext)
#else
static void
yy_reduce_print (yyvsp, yyrule, pParseContext)
    YYSTYPE *yyvsp;
    int yyrule;
    glslang::TParseContext* pParseContext;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , pParseContext);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, pParseContext); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, glslang::TParseContext* pParseContext)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, pParseContext)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    glslang::TParseContext* pParseContext;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (pParseContext);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (glslang::TParseContext* pParseContext);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (glslang::TParseContext* pParseContext)
#else
int
yyparse (pParseContext)
    glslang::TParseContext* pParseContext;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
		  (unsigned long int) yystacksize));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 253 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleVariable((yyvsp[(1) - (1)].lex).loc, (yyvsp[(1) - (1)].lex).symbol, (yyvsp[(1) - (1)].lex).string);
    ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 259 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 262 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).i, (yyvsp[(1) - (1)].lex).loc, true);
    ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 265 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "unsigned literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).u, (yyvsp[(1) - (1)].lex).loc, true);
    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 269 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).i64, (yyvsp[(1) - (1)].lex).loc, true);
    ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 273 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).u64, (yyvsp[(1) - (1)].lex).loc, true);
    ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 277 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[(1) - (1)].lex).loc, "16-bit integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((short)(yyvsp[(1) - (1)].lex).i, (yyvsp[(1) - (1)].lex).loc, true);
#endif
    ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 283 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[(1) - (1)].lex).loc, "16-bit unsigned integer literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((unsigned short)(yyvsp[(1) - (1)].lex).u, (yyvsp[(1) - (1)].lex).loc, true);
#endif
    ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 289 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).d, EbtFloat, (yyvsp[(1) - (1)].lex).loc, true);
    ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 292 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).d, EbtDouble, (yyvsp[(1) - (1)].lex).loc, true);
    ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 296 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float literal");
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).d, EbtFloat16, (yyvsp[(1) - (1)].lex).loc, true);
#endif
    ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 302 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion((yyvsp[(1) - (1)].lex).b, (yyvsp[(1) - (1)].lex).loc, true);
    ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 305 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(2) - (3)].interm.intermTypedNode);
        if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
            (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
    ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 313 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 316 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBracketDereference((yyvsp[(2) - (4)].lex).loc, (yyvsp[(1) - (4)].interm.intermTypedNode), (yyvsp[(3) - (4)].interm.intermTypedNode));
    ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 319 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 322 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleDotDereference((yyvsp[(3) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode), *(yyvsp[(3) - (3)].lex).string);
    ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 325 "glslang.y"
    {
        parseContext.variableCheck((yyvsp[(1) - (2)].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[(2) - (2)].lex).loc, "++", (yyvsp[(1) - (2)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[(2) - (2)].lex).loc, "++", EOpPostIncrement, (yyvsp[(1) - (2)].interm.intermTypedNode));
    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 330 "glslang.y"
    {
        parseContext.variableCheck((yyvsp[(1) - (2)].interm.intermTypedNode));
        parseContext.lValueErrorCheck((yyvsp[(2) - (2)].lex).loc, "--", (yyvsp[(1) - (2)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[(2) - (2)].lex).loc, "--", EOpPostDecrement, (yyvsp[(1) - (2)].interm.intermTypedNode));
    ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 338 "glslang.y"
    {
        parseContext.integerCheck((yyvsp[(1) - (1)].interm.intermTypedNode), "[]");
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 345 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleFunctionCall((yyvsp[(1) - (1)].interm).loc, (yyvsp[(1) - (1)].interm).function, (yyvsp[(1) - (1)].interm).intermNode);
        delete (yyvsp[(1) - (1)].interm).function;
    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 352 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);
    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 358 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (2)].interm);
        (yyval.interm).loc = (yyvsp[(2) - (2)].lex).loc;
    ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 362 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (2)].interm);
        (yyval.interm).loc = (yyvsp[(2) - (2)].lex).loc;
    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 369 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (2)].interm);
    ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 372 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);
    ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 378 "glslang.y"
    {
        TParameter param = { 0, new TType };
        param.type->shallowCopy((yyvsp[(2) - (2)].interm.intermTypedNode)->getType());
        (yyvsp[(1) - (2)].interm).function->addParameter(param);
        (yyval.interm).function = (yyvsp[(1) - (2)].interm).function;
        (yyval.interm).intermNode = (yyvsp[(2) - (2)].interm.intermTypedNode);
    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 385 "glslang.y"
    {
        TParameter param = { 0, new TType };
        param.type->shallowCopy((yyvsp[(3) - (3)].interm.intermTypedNode)->getType());
        (yyvsp[(1) - (3)].interm).function->addParameter(param);
        (yyval.interm).function = (yyvsp[(1) - (3)].interm).function;
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[(1) - (3)].interm).intermNode, (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).loc);
    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 395 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (2)].interm);
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 403 "glslang.y"
    {
        // Constructor
        (yyval.interm).intermNode = 0;
        (yyval.interm).function = parseContext.handleConstructorCall((yyvsp[(1) - (1)].interm.type).loc, (yyvsp[(1) - (1)].interm.type));
    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 408 "glslang.y"
    {
        //
        // Should be a method or subroutine call, but we haven't recognized the arguments yet.
        //
        (yyval.interm).function = 0;
        (yyval.interm).intermNode = 0;

        TIntermMethod* method = (yyvsp[(1) - (1)].interm.intermTypedNode)->getAsMethodNode();
        if (method) {
            (yyval.interm).function = new TFunction(&method->getMethodName(), TType(EbtInt), EOpArrayLength);
            (yyval.interm).intermNode = method->getObject();
        } else {
            TIntermSymbol* symbol = (yyvsp[(1) - (1)].interm.intermTypedNode)->getAsSymbolNode();
            if (symbol) {
                parseContext.reservedErrorCheck(symbol->getLoc(), symbol->getName());
                TFunction *function = new TFunction(&symbol->getName(), TType(EbtVoid));
                (yyval.interm).function = function;
            } else
                parseContext.error((yyvsp[(1) - (1)].interm.intermTypedNode)->getLoc(), "function call, method, or subroutine call expected", "", "");
        }

        if ((yyval.interm).function == 0) {
            // error recover
            TString empty("");
            (yyval.interm).function = new TFunction(&empty, TType(EbtVoid), EOpNull);
        }
    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 438 "glslang.y"
    {
        parseContext.variableCheck((yyvsp[(1) - (1)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
        if (TIntermMethod* method = (yyvsp[(1) - (1)].interm.intermTypedNode)->getAsMethodNode())
            parseContext.error((yyvsp[(1) - (1)].interm.intermTypedNode)->getLoc(), "incomplete method syntax", method->getMethodName().c_str(), "");
    ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 444 "glslang.y"
    {
        parseContext.lValueErrorCheck((yyvsp[(1) - (2)].lex).loc, "++", (yyvsp[(2) - (2)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[(1) - (2)].lex).loc, "++", EOpPreIncrement, (yyvsp[(2) - (2)].interm.intermTypedNode));
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 448 "glslang.y"
    {
        parseContext.lValueErrorCheck((yyvsp[(1) - (2)].lex).loc, "--", (yyvsp[(2) - (2)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[(1) - (2)].lex).loc, "--", EOpPreDecrement, (yyvsp[(2) - (2)].interm.intermTypedNode));
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 452 "glslang.y"
    {
        if ((yyvsp[(1) - (2)].interm).op != EOpNull) {
            char errorOp[2] = {0, 0};
            switch((yyvsp[(1) - (2)].interm).op) {
            case EOpNegative:   errorOp[0] = '-'; break;
            case EOpLogicalNot: errorOp[0] = '!'; break;
            case EOpBitwiseNot: errorOp[0] = '~'; break;
            default: break; // some compilers want this
            }
            (yyval.interm.intermTypedNode) = parseContext.handleUnaryMath((yyvsp[(1) - (2)].interm).loc, errorOp, (yyvsp[(1) - (2)].interm).op, (yyvsp[(2) - (2)].interm.intermTypedNode));
        } else {
            (yyval.interm.intermTypedNode) = (yyvsp[(2) - (2)].interm.intermTypedNode);
            if ((yyval.interm.intermTypedNode)->getAsConstantUnion())
                (yyval.interm.intermTypedNode)->getAsConstantUnion()->setExpression();
        }
    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 472 "glslang.y"
    { (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpNull; ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 473 "glslang.y"
    { (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpNegative; ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 474 "glslang.y"
    { (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpLogicalNot; ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 475 "glslang.y"
    { (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpBitwiseNot;
              parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bitwise not"); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 481 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 482 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "*", EOpMul, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 487 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "/", EOpDiv, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 492 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "%");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "%", EOpMod, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 501 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 502 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "+", EOpAdd, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 507 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "-", EOpSub, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 515 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 516 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "bit shift left");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "<<", EOpLeftShift, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 522 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "bit shift right");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, ">>", EOpRightShift, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 531 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 532 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "<", EOpLessThan, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 537 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, ">", EOpGreaterThan, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 542 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "<=", EOpLessThanEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 547 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, ">=", EOpGreaterThanEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 555 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 556 "glslang.y"
    {
        parseContext.arrayObjectCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "==");
        parseContext.specializationCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "==");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "==", EOpEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 564 "glslang.y"
    {
        parseContext.arrayObjectCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "array comparison");
        parseContext.opaqueCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "!=");
        parseContext.specializationCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "!=");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "!=", EOpNotEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 575 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 576 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "bitwise and");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "&", EOpAnd, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 585 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 586 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "bitwise exclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "^", EOpExclusiveOr, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 595 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 596 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(2) - (3)].lex).loc, "bitwise inclusive or");
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "|", EOpInclusiveOr, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 605 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 606 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "&&", EOpLogicalAnd, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 614 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 615 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "^^", EOpLogicalXor, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 623 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 624 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.handleBinaryMath((yyvsp[(2) - (3)].lex).loc, "||", EOpLogicalOr, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
        if ((yyval.interm.intermTypedNode) == 0)
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(false, (yyvsp[(2) - (3)].lex).loc);
    ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 632 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 633 "glslang.y"
    {
        ++parseContext.controlFlowNestingLevel;
    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 636 "glslang.y"
    {
        --parseContext.controlFlowNestingLevel;
        parseContext.boolCheck((yyvsp[(2) - (6)].lex).loc, (yyvsp[(1) - (6)].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[(2) - (6)].lex).loc, "?", (yyvsp[(1) - (6)].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[(5) - (6)].lex).loc, ":", (yyvsp[(4) - (6)].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[(5) - (6)].lex).loc, ":", (yyvsp[(6) - (6)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addSelection((yyvsp[(1) - (6)].interm.intermTypedNode), (yyvsp[(4) - (6)].interm.intermTypedNode), (yyvsp[(6) - (6)].interm.intermTypedNode), (yyvsp[(2) - (6)].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (6)].lex).loc, ":", (yyvsp[(4) - (6)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(6) - (6)].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[(6) - (6)].interm.intermTypedNode);
        }
    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 651 "glslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 652 "glslang.y"
    {
        parseContext.arrayObjectCheck((yyvsp[(2) - (3)].interm).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "array assignment");
        parseContext.opaqueCheck((yyvsp[(2) - (3)].interm).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "=");
        parseContext.specializationCheck((yyvsp[(2) - (3)].interm).loc, (yyvsp[(1) - (3)].interm.intermTypedNode)->getType(), "=");
        parseContext.lValueErrorCheck((yyvsp[(2) - (3)].interm).loc, "assign", (yyvsp[(1) - (3)].interm.intermTypedNode));
        parseContext.rValueErrorCheck((yyvsp[(2) - (3)].interm).loc, "assign", (yyvsp[(3) - (3)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addAssign((yyvsp[(2) - (3)].interm).op, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].interm).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.assignError((yyvsp[(2) - (3)].interm).loc, "assign", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 667 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpAssign;
    ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 671 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpMulAssign;
    ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 675 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpDivAssign;
    ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 679 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "%=");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpModAssign;
    ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 684 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpAddAssign;
    ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 688 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm).op = EOpSubAssign;
    ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 692 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bit-shift left assign");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpLeftShiftAssign;
    ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 696 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bit-shift right assign");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpRightShiftAssign;
    ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 700 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bitwise-and assign");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpAndAssign;
    ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 704 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bitwise-xor assign");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpExclusiveOrAssign;
    ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 708 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "bitwise-or assign");
        (yyval.interm).loc = (yyvsp[(1) - (1)].lex).loc; (yyval.interm).op = EOpInclusiveOrAssign;
    ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 715 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 718 "glslang.y"
    {
        parseContext.samplerConstructorLocationCheck((yyvsp[(2) - (3)].lex).loc, ",", (yyvsp[(3) - (3)].interm.intermTypedNode));
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addComma((yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).loc);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).loc, ",", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            (yyval.interm.intermTypedNode) = (yyvsp[(3) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 729 "glslang.y"
    {
        parseContext.constantValueCheck((yyvsp[(1) - (1)].interm.intermTypedNode), "");
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 736 "glslang.y"
    {
        parseContext.handleFunctionDeclarator((yyvsp[(1) - (2)].interm).loc, *(yyvsp[(1) - (2)].interm).function, true /* prototype */);
        (yyval.interm.intermNode) = 0;
        // TODO: 4.0 functionality: subroutines: make the identifier a user type for this signature
    ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 741 "glslang.y"
    {
        if ((yyvsp[(1) - (2)].interm).intermNode && (yyvsp[(1) - (2)].interm).intermNode->getAsAggregate())
            (yyvsp[(1) - (2)].interm).intermNode->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[(1) - (2)].interm).intermNode;
    ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 746 "glslang.y"
    {
        parseContext.profileRequires((yyvsp[(1) - (4)].lex).loc, ENoProfile, 130, 0, "precision statement");

        // lazy setting of the previous scope's defaults, has effect only the first time it is called in a particular scope
        parseContext.symbolTable.setPreviousDefaultPrecisions(&parseContext.defaultPrecision[0]);
        parseContext.setDefaultPrecision((yyvsp[(1) - (4)].lex).loc, (yyvsp[(3) - (4)].interm.type), (yyvsp[(2) - (4)].interm.type).qualifier.precision);
        (yyval.interm.intermNode) = 0;
    ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 754 "glslang.y"
    {
        parseContext.declareBlock((yyvsp[(1) - (2)].interm).loc, *(yyvsp[(1) - (2)].interm).typeList);
        (yyval.interm.intermNode) = 0;
    ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 758 "glslang.y"
    {
        parseContext.declareBlock((yyvsp[(1) - (3)].interm).loc, *(yyvsp[(1) - (3)].interm).typeList, (yyvsp[(2) - (3)].lex).string);
        (yyval.interm.intermNode) = 0;
    ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 762 "glslang.y"
    {
        parseContext.declareBlock((yyvsp[(1) - (4)].interm).loc, *(yyvsp[(1) - (4)].interm).typeList, (yyvsp[(2) - (4)].lex).string, (yyvsp[(3) - (4)].interm).arraySizes);
        (yyval.interm.intermNode) = 0;
    ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 766 "glslang.y"
    {
        parseContext.globalQualifierFixCheck((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier);
        parseContext.updateStandaloneQualifierDefaults((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type));
        (yyval.interm.intermNode) = 0;
    ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 771 "glslang.y"
    {
        parseContext.checkNoShaderLayouts((yyvsp[(1) - (3)].interm.type).loc, (yyvsp[(1) - (3)].interm.type).shaderQualifiers);
        parseContext.addQualifierToExisting((yyvsp[(1) - (3)].interm.type).loc, (yyvsp[(1) - (3)].interm.type).qualifier, *(yyvsp[(2) - (3)].lex).string);
        (yyval.interm.intermNode) = 0;
    ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 776 "glslang.y"
    {
        parseContext.checkNoShaderLayouts((yyvsp[(1) - (4)].interm.type).loc, (yyvsp[(1) - (4)].interm.type).shaderQualifiers);
        (yyvsp[(3) - (4)].interm.identifierList)->push_back((yyvsp[(2) - (4)].lex).string);
        parseContext.addQualifierToExisting((yyvsp[(1) - (4)].interm.type).loc, (yyvsp[(1) - (4)].interm.type).qualifier, *(yyvsp[(3) - (4)].interm.identifierList));
        (yyval.interm.intermNode) = 0;
    ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 785 "glslang.y"
    { parseContext.nestedBlockCheck((yyvsp[(1) - (3)].interm.type).loc); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 785 "glslang.y"
    {
        --parseContext.structNestingLevel;
        parseContext.blockName = (yyvsp[(2) - (6)].lex).string;
        parseContext.globalQualifierFixCheck((yyvsp[(1) - (6)].interm.type).loc, (yyvsp[(1) - (6)].interm.type).qualifier);
        parseContext.checkNoShaderLayouts((yyvsp[(1) - (6)].interm.type).loc, (yyvsp[(1) - (6)].interm.type).shaderQualifiers);
        parseContext.currentBlockQualifier = (yyvsp[(1) - (6)].interm.type).qualifier;
        (yyval.interm).loc = (yyvsp[(1) - (6)].interm.type).loc;
        (yyval.interm).typeList = (yyvsp[(5) - (6)].interm.typeList);
    ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 796 "glslang.y"
    {
        (yyval.interm.identifierList) = new TIdentifierList;
        (yyval.interm.identifierList)->push_back((yyvsp[(2) - (2)].lex).string);
    ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 800 "glslang.y"
    {
        (yyval.interm.identifierList) = (yyvsp[(1) - (3)].interm.identifierList);
        (yyval.interm.identifierList)->push_back((yyvsp[(3) - (3)].lex).string);
    ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 807 "glslang.y"
    {
        (yyval.interm).function = (yyvsp[(1) - (2)].interm.function);
        (yyval.interm).loc = (yyvsp[(2) - (2)].lex).loc;
    ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 814 "glslang.y"
    {
        (yyval.interm.function) = (yyvsp[(1) - (1)].interm.function);
    ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 817 "glslang.y"
    {
        (yyval.interm.function) = (yyvsp[(1) - (1)].interm.function);
    ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 824 "glslang.y"
    {
        // Add the parameter
        (yyval.interm.function) = (yyvsp[(1) - (2)].interm.function);
        if ((yyvsp[(2) - (2)].interm).param.type->getBasicType() != EbtVoid)
            (yyvsp[(1) - (2)].interm.function)->addParameter((yyvsp[(2) - (2)].interm).param);
        else
            delete (yyvsp[(2) - (2)].interm).param.type;
    ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 832 "glslang.y"
    {
        //
        // Only first parameter of one-parameter functions can be void
        // The check for named parameters not being void is done in parameter_declarator
        //
        if ((yyvsp[(3) - (3)].interm).param.type->getBasicType() == EbtVoid) {
            //
            // This parameter > first is void
            //
            parseContext.error((yyvsp[(2) - (3)].lex).loc, "cannot be an argument type except for '(void)'", "void", "");
            delete (yyvsp[(3) - (3)].interm).param.type;
        } else {
            // Add the parameter
            (yyval.interm.function) = (yyvsp[(1) - (3)].interm.function);
            (yyvsp[(1) - (3)].interm.function)->addParameter((yyvsp[(3) - (3)].interm).param);
        }
    ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 852 "glslang.y"
    {
        if ((yyvsp[(1) - (3)].interm.type).qualifier.storage != EvqGlobal && (yyvsp[(1) - (3)].interm.type).qualifier.storage != EvqTemporary) {
            parseContext.error((yyvsp[(2) - (3)].lex).loc, "no qualifiers allowed for function return",
                               GetStorageQualifierString((yyvsp[(1) - (3)].interm.type).qualifier.storage), "");
        }
        if ((yyvsp[(1) - (3)].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[(1) - (3)].interm.type).loc, *(yyvsp[(1) - (3)].interm.type).arraySizes);

        // Add the function as a prototype after parsing it (we do not support recursion)
        TFunction *function;
        TType type((yyvsp[(1) - (3)].interm.type));
        function = new TFunction((yyvsp[(2) - (3)].lex).string, type);
        (yyval.interm.function) = function;
    ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 870 "glslang.y"
    {
        if ((yyvsp[(1) - (2)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(1) - (2)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(1) - (2)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck((yyvsp[(1) - (2)].interm.type).loc, *(yyvsp[(1) - (2)].interm.type).arraySizes);
        }
        if ((yyvsp[(1) - (2)].interm.type).basicType == EbtVoid) {
            parseContext.error((yyvsp[(2) - (2)].lex).loc, "illegal use of type 'void'", (yyvsp[(2) - (2)].lex).string->c_str(), "");
        }
        parseContext.reservedErrorCheck((yyvsp[(2) - (2)].lex).loc, *(yyvsp[(2) - (2)].lex).string);

        TParameter param = {(yyvsp[(2) - (2)].lex).string, new TType((yyvsp[(1) - (2)].interm.type))};
        (yyval.interm).loc = (yyvsp[(2) - (2)].lex).loc;
        (yyval.interm).param = param;
    ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 885 "glslang.y"
    {
        if ((yyvsp[(1) - (3)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(1) - (3)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(1) - (3)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            parseContext.arraySizeRequiredCheck((yyvsp[(1) - (3)].interm.type).loc, *(yyvsp[(1) - (3)].interm.type).arraySizes);
        }
        parseContext.arrayDimCheck((yyvsp[(2) - (3)].lex).loc, (yyvsp[(1) - (3)].interm.type).arraySizes, (yyvsp[(3) - (3)].interm).arraySizes);

        parseContext.arraySizeRequiredCheck((yyvsp[(3) - (3)].interm).loc, *(yyvsp[(3) - (3)].interm).arraySizes);
        parseContext.reservedErrorCheck((yyvsp[(2) - (3)].lex).loc, *(yyvsp[(2) - (3)].lex).string);

        (yyvsp[(1) - (3)].interm.type).arraySizes = (yyvsp[(3) - (3)].interm).arraySizes;

        TParameter param = { (yyvsp[(2) - (3)].lex).string, new TType((yyvsp[(1) - (3)].interm.type))};
        (yyval.interm).loc = (yyvsp[(2) - (3)].lex).loc;
        (yyval.interm).param = param;
    ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 908 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(2) - (2)].interm);
        if ((yyvsp[(1) - (2)].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[(1) - (2)].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[(2) - (2)].interm).loc, (yyvsp[(1) - (2)].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier, *(yyval.interm).param.type);

    ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 919 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);

        parseContext.parameterTypeCheck((yyvsp[(1) - (1)].interm).loc, EvqIn, *(yyvsp[(1) - (1)].interm).param.type);
        parseContext.paramCheckFix((yyvsp[(1) - (1)].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 929 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(2) - (2)].interm);
        if ((yyvsp[(1) - (2)].interm.type).qualifier.precision != EpqNone)
            (yyval.interm).param.type->getQualifier().precision = (yyvsp[(1) - (2)].interm.type).qualifier.precision;
        parseContext.precisionQualifierCheck((yyvsp[(1) - (2)].interm.type).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());

        parseContext.checkNoShaderLayouts((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).shaderQualifiers);
        parseContext.parameterTypeCheck((yyvsp[(2) - (2)].interm).loc, (yyvsp[(1) - (2)].interm.type).qualifier.storage, *(yyval.interm).param.type);
        parseContext.paramCheckFix((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier, *(yyval.interm).param.type);
    ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 939 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);

        parseContext.parameterTypeCheck((yyvsp[(1) - (1)].interm).loc, EvqIn, *(yyvsp[(1) - (1)].interm).param.type);
        parseContext.paramCheckFix((yyvsp[(1) - (1)].interm).loc, EvqTemporary, *(yyval.interm).param.type);
        parseContext.precisionQualifierCheck((yyval.interm).loc, (yyval.interm).param.type->getBasicType(), (yyval.interm).param.type->getQualifier());
    ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 949 "glslang.y"
    {
        TParameter param = { 0, new TType((yyvsp[(1) - (1)].interm.type)) };
        (yyval.interm).param = param;
        if ((yyvsp[(1) - (1)].interm.type).arraySizes)
            parseContext.arraySizeRequiredCheck((yyvsp[(1) - (1)].interm.type).loc, *(yyvsp[(1) - (1)].interm.type).arraySizes);
    ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 958 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);
    ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 961 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (3)].interm);
        parseContext.declareVariable((yyvsp[(3) - (3)].lex).loc, *(yyvsp[(3) - (3)].lex).string, (yyvsp[(1) - (3)].interm).type);
    ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 965 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (4)].interm);
        parseContext.declareVariable((yyvsp[(3) - (4)].lex).loc, *(yyvsp[(3) - (4)].lex).string, (yyvsp[(1) - (4)].interm).type, (yyvsp[(4) - (4)].interm).arraySizes);
    ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 969 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (6)].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[(3) - (6)].lex).loc, *(yyvsp[(3) - (6)].lex).string, (yyvsp[(1) - (6)].interm).type, (yyvsp[(4) - (6)].interm).arraySizes, (yyvsp[(6) - (6)].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[(1) - (6)].interm).intermNode, initNode, (yyvsp[(5) - (6)].lex).loc);
    ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 974 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (5)].interm).type;
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[(3) - (5)].lex).loc, *(yyvsp[(3) - (5)].lex).string, (yyvsp[(1) - (5)].interm).type, 0, (yyvsp[(5) - (5)].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[(1) - (5)].interm).intermNode, initNode, (yyvsp[(4) - (5)].lex).loc);
    ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 982 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (1)].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareTypeDefaults((yyval.interm).loc, (yyval.interm).type);
    ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 987 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (2)].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[(2) - (2)].lex).loc, *(yyvsp[(2) - (2)].lex).string, (yyvsp[(1) - (2)].interm.type));
    ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 992 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (3)].interm.type);
        (yyval.interm).intermNode = 0;
        parseContext.declareVariable((yyvsp[(2) - (3)].lex).loc, *(yyvsp[(2) - (3)].lex).string, (yyvsp[(1) - (3)].interm.type), (yyvsp[(3) - (3)].interm).arraySizes);
    ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 997 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (5)].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[(2) - (5)].lex).loc, *(yyvsp[(2) - (5)].lex).string, (yyvsp[(1) - (5)].interm.type), (yyvsp[(3) - (5)].interm).arraySizes, (yyvsp[(5) - (5)].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[(4) - (5)].lex).loc);
    ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1002 "glslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (4)].interm.type);
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[(2) - (4)].lex).loc, *(yyvsp[(2) - (4)].lex).string, (yyvsp[(1) - (4)].interm.type), 0, (yyvsp[(4) - (4)].interm.intermTypedNode));
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate(0, initNode, (yyvsp[(3) - (4)].lex).loc);
    ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1011 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);

        parseContext.globalQualifierTypeCheck((yyvsp[(1) - (1)].interm.type).loc, (yyvsp[(1) - (1)].interm.type).qualifier, (yyval.interm.type));
        if ((yyvsp[(1) - (1)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(1) - (1)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(1) - (1)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        parseContext.precisionQualifierCheck((yyval.interm.type).loc, (yyval.interm.type).basicType, (yyval.interm.type).qualifier);
    ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1022 "glslang.y"
    {
        parseContext.globalQualifierFixCheck((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier);
        parseContext.globalQualifierTypeCheck((yyvsp[(1) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier, (yyvsp[(2) - (2)].interm.type));

        if ((yyvsp[(2) - (2)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(2) - (2)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(2) - (2)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
        }

        if ((yyvsp[(2) - (2)].interm.type).arraySizes && parseContext.arrayQualifierError((yyvsp[(2) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).qualifier))
            (yyvsp[(2) - (2)].interm.type).arraySizes = 0;

        parseContext.checkNoShaderLayouts((yyvsp[(2) - (2)].interm.type).loc, (yyvsp[(1) - (2)].interm.type).shaderQualifiers);
        (yyvsp[(2) - (2)].interm.type).shaderQualifiers.merge((yyvsp[(1) - (2)].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyvsp[(2) - (2)].interm.type).loc, (yyvsp[(2) - (2)].interm.type).qualifier, (yyvsp[(1) - (2)].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[(2) - (2)].interm.type).loc, (yyvsp[(2) - (2)].interm.type).basicType, (yyvsp[(2) - (2)].interm.type).qualifier);

        (yyval.interm.type) = (yyvsp[(2) - (2)].interm.type);

        if (! (yyval.interm.type).qualifier.isInterpolation() &&
            ((parseContext.language == EShLangVertex   && (yyval.interm.type).qualifier.storage == EvqVaryingOut) ||
             (parseContext.language == EShLangFragment && (yyval.interm.type).qualifier.storage == EvqVaryingIn)))
            (yyval.interm.type).qualifier.smooth = true;
    ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1049 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "invariant");
        parseContext.profileRequires((yyval.interm.type).loc, ENoProfile, 120, 0, "invariant");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.invariant = true;
    ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1058 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "smooth");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "smooth");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, EEsProfile, 300, 0, "smooth");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.smooth = true;
    ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1065 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "flat");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "flat");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, EEsProfile, 300, 0, "flat");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.flat = true;
    ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1072 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "noperspective");
        parseContext.requireProfile((yyvsp[(1) - (1)].lex).loc, ~EEsProfile, "noperspective");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "noperspective");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.nopersp = true;
    ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1079 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "__explicitInterpAMD");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ECoreProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ECompatibilityProfile, 450, E_GL_AMD_shader_explicit_vertex_parameter, "explicit interpolation");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.explicitInterp = true;
#endif
    ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1091 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(3) - (4)].interm.type);
    ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1097 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1100 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (3)].interm.type);
        (yyval.interm.type).shaderQualifiers.merge((yyvsp[(3) - (3)].interm.type).shaderQualifiers);
        parseContext.mergeObjectLayoutQualifiers((yyval.interm.type).qualifier, (yyvsp[(3) - (3)].interm.type).qualifier, false);
    ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1107 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[(1) - (1)].lex).loc, (yyval.interm.type), *(yyvsp[(1) - (1)].lex).string);
    ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1111 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (3)].lex).loc);
        parseContext.setLayoutQualifier((yyvsp[(1) - (3)].lex).loc, (yyval.interm.type), *(yyvsp[(1) - (3)].lex).string, (yyvsp[(3) - (3)].interm.intermTypedNode));
    ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1115 "glslang.y"
    { // because "shared" is both an identifier and a keyword
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        TString strShared("shared");
        parseContext.setLayoutQualifier((yyvsp[(1) - (1)].lex).loc, (yyval.interm.type), strShared);
    ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1123 "glslang.y"
    {
        parseContext.profileRequires((yyval.interm.type).loc, ECoreProfile | ECompatibilityProfile, 400, E_GL_ARB_gpu_shader5, "precise");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, EEsProfile, 320, Num_AEP_gpu_shader5, AEP_gpu_shader5, "precise");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.noContraction = true;
    ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1132 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1135 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (2)].interm.type);
        if ((yyval.interm.type).basicType == EbtVoid)
            (yyval.interm.type).basicType = (yyvsp[(2) - (2)].interm.type).basicType;

        (yyval.interm.type).shaderQualifiers.merge((yyvsp[(2) - (2)].interm.type).shaderQualifiers);
        parseContext.mergeQualifiers((yyval.interm.type).loc, (yyval.interm.type).qualifier, (yyvsp[(2) - (2)].interm.type).qualifier, false);
    ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1146 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1149 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1152 "glslang.y"
    {
        parseContext.checkPrecisionQualifier((yyvsp[(1) - (1)].interm.type).loc, (yyvsp[(1) - (1)].interm.type).qualifier.precision);
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1156 "glslang.y"
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1160 "glslang.y"
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1164 "glslang.y"
    {
        // allow inheritance of storage qualifier from block declaration
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1171 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqConst;  // will later turn into EvqConstReadOnly, if the initializer is not constant
    ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1175 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangVertex, "attribute");
        parseContext.checkDeprecated((yyvsp[(1) - (1)].lex).loc, ECoreProfile, 130, "attribute");
        parseContext.checkDeprecated((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, "attribute");
        parseContext.requireNotRemoved((yyvsp[(1) - (1)].lex).loc, ECoreProfile, 420, "attribute");
        parseContext.requireNotRemoved((yyvsp[(1) - (1)].lex).loc, EEsProfile, 300, "attribute");

        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "attribute");

        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqVaryingIn;
    ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1187 "glslang.y"
    {
        parseContext.checkDeprecated((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, "varying");
        parseContext.checkDeprecated((yyvsp[(1) - (1)].lex).loc, ECoreProfile, 130, "varying");
        parseContext.requireNotRemoved((yyvsp[(1) - (1)].lex).loc, ECoreProfile, 420, "varying");
        parseContext.requireNotRemoved((yyvsp[(1) - (1)].lex).loc, EEsProfile, 300, "varying");

        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "varying");

        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        if (parseContext.language == EShLangVertex)
            (yyval.interm.type).qualifier.storage = EvqVaryingOut;
        else
            (yyval.interm.type).qualifier.storage = EvqVaryingIn;
    ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1201 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "inout");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqInOut;
    ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1206 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "in");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        // whether this is a parameter "in" or a pipeline "in" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqIn;
    ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1212 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "out");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        // whether this is a parameter "out" or a pipeline "out" will get sorted out a bit later
        (yyval.interm.type).qualifier.storage = EvqOut;
    ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1218 "glslang.y"
    {
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 120, 0, "centroid");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, EEsProfile, 300, 0, "centroid");
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "centroid");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.centroid = true;
    ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1225 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "patch");
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, (EShLanguageMask)(EShLangTessControlMask | EShLangTessEvaluationMask), "patch");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.patch = true;
    ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1231 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "sample");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.sample = true;
    ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1236 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "uniform");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqUniform;
    ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1241 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "buffer");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqBuffer;
    ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1246 "glslang.y"
    {
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "shared");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ECoreProfile | ECompatibilityProfile, 430, E_GL_ARB_compute_shader, "shared");
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, EEsProfile, 310, 0, "shared");
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangCompute, "shared");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.storage = EvqShared;
    ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1254 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.coherent = true;
    ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1258 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.volatil = true;
    ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1262 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.restrict = true;
    ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1266 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.readonly = true;
    ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1270 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
        (yyval.interm.type).qualifier.writeonly = true;
    ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1274 "glslang.y"
    {
        parseContext.spvRemoved((yyvsp[(1) - (1)].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[(1) - (1)].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[(1) - (1)].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc);
    ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1280 "glslang.y"
    {
        parseContext.spvRemoved((yyvsp[(1) - (4)].lex).loc, "subroutine");
        parseContext.globalCheck((yyvsp[(1) - (4)].lex).loc, "subroutine");
        parseContext.unimplemented((yyvsp[(1) - (4)].lex).loc, "subroutine");
        (yyval.interm.type).init((yyvsp[(1) - (4)].lex).loc);
    ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1289 "glslang.y"
    {
        // TODO
    ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1292 "glslang.y"
    {
        // TODO: 4.0 semantics: subroutines
        // 1) make sure each identifier is a type declared earlier with SUBROUTINE
        // 2) save all of the identifiers for future comparison with the declared function
    ;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1300 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
    ;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1304 "glslang.y"
    {
        parseContext.arrayDimCheck((yyvsp[(2) - (2)].interm).loc, (yyvsp[(2) - (2)].interm).arraySizes, 0);
        (yyval.interm.type) = (yyvsp[(1) - (2)].interm.type);
        (yyval.interm.type).qualifier.precision = parseContext.getDefaultPrecision((yyval.interm.type));
        (yyval.interm.type).arraySizes = (yyvsp[(2) - (2)].interm).arraySizes;
    ;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1313 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (2)].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;
        (yyval.interm).arraySizes->addInnerSize();
    ;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1318 "glslang.y"
    {
        (yyval.interm).loc = (yyvsp[(1) - (3)].lex).loc;
        (yyval.interm).arraySizes = new TArraySizes;

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[(2) - (3)].interm.intermTypedNode)->getLoc(), (yyvsp[(2) - (3)].interm.intermTypedNode), size);
        (yyval.interm).arraySizes->addInnerSize(size);
    ;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1326 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (3)].interm);
        (yyval.interm).arraySizes->addInnerSize();
    ;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1330 "glslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (4)].interm);

        TArraySize size;
        parseContext.arraySizeCheck((yyvsp[(3) - (4)].interm.intermTypedNode)->getLoc(), (yyvsp[(3) - (4)].interm.intermTypedNode), size);
        (yyval.interm).arraySizes->addInnerSize(size);
    ;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1340 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtVoid;
    ;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1344 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
    ;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1348 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
    ;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1353 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
#endif
    ;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1360 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
    ;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1364 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "unsigned integer");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
    ;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1369 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
    ;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1374 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
    ;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1379 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[(1) - (1)].lex).loc, "16-bit integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
#endif
    ;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1386 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[(1) - (1)].lex).loc, "16-bit unsigned integer", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
#endif
    ;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1393 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
    ;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1397 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(2);
    ;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1402 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(3);
    ;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1407 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setVector(4);
    ;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1412 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(2);
    ;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1418 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(3);
    ;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1424 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setVector(4);
    ;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1430 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(2);
#endif
    ;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1438 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(3);
#endif
    ;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1446 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setVector(4);
#endif
    ;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1454 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(2);
    ;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1459 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(3);
    ;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1464 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtBool;
        (yyval.interm.type).setVector(4);
    ;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1469 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(2);
    ;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1474 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(3);
    ;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1479 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt;
        (yyval.interm.type).setVector(4);
    ;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1484 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(2);
    ;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1490 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(3);
    ;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1496 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt64;
        (yyval.interm.type).setVector(4);
    ;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1502 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[(1) - (1)].lex).loc, "16-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(2);
#endif
    ;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1510 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[(1) - (1)].lex).loc, "16-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(3);
#endif
    ;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1518 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[(1) - (1)].lex).loc, "16-bit integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtInt16;
        (yyval.interm.type).setVector(4);
#endif
    ;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1526 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(2);
    ;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1532 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(3);
    ;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1538 "glslang.y"
    {
        parseContext.fullIntegerCheck((yyvsp[(1) - (1)].lex).loc, "unsigned integer vector");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint;
        (yyval.interm.type).setVector(4);
    ;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1544 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(2);
    ;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1550 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(3);
    ;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1556 "glslang.y"
    {
        parseContext.int64Check((yyvsp[(1) - (1)].lex).loc, "64-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint64;
        (yyval.interm.type).setVector(4);
    ;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1562 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[(1) - (1)].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(2);
#endif
    ;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1570 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[(1) - (1)].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(3);
#endif
    ;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1578 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.int16Check((yyvsp[(1) - (1)].lex).loc, "16-bit unsigned integer vector", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtUint16;
        (yyval.interm.type).setVector(4);
#endif
    ;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1586 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    ;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1591 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    ;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1596 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    ;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1601 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 2);
    ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1606 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 3);
    ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1611 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(2, 4);
    ;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1616 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 2);
    ;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1621 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 3);
    ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1626 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(3, 4);
    ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1631 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 2);
    ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1636 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 3);
    ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1641 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat;
        (yyval.interm.type).setMatrix(4, 4);
    ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1646 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1652 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1658 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1664 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 2);
    ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1670 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 3);
    ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1676 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(2, 4);
    ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1682 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 2);
    ;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1688 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 3);
    ;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1694 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(3, 4);
    ;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1700 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 2);
    ;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1706 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 3);
    ;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1712 "glslang.y"
    {
        parseContext.doubleCheck((yyvsp[(1) - (1)].lex).loc, "double matrix");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtDouble;
        (yyval.interm.type).setMatrix(4, 4);
    ;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1718 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
#endif
    ;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 1726 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
#endif
    ;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1734 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
#endif
    ;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 1742 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 2);
#endif
    ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 1750 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 3);
#endif
    ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 1758 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(2, 4);
#endif
    ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 1766 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 2);
#endif
    ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1774 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 3);
#endif
    ;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 1782 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(3, 4);
#endif
    ;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1790 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 2);
#endif
    ;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1798 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 3);
#endif
    ;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 1806 "glslang.y"
    {
#ifdef AMD_EXTENSIONS
        parseContext.float16Check((yyvsp[(1) - (1)].lex).loc, "half float matrix", parseContext.symbolTable.atBuiltInLevel());
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtFloat16;
        (yyval.interm.type).setMatrix(4, 4);
#endif
    ;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 1814 "glslang.y"
    {
        parseContext.vulkanRemoved((yyvsp[(1) - (1)].lex).loc, "atomic counter types");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtAtomicUint;
    ;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 1819 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D);
    ;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 1824 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
    ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 1829 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd3D);
    ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 1834 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube);
    ;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 1839 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, false, true);
    ;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 1844 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, true);
    ;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 1849 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, false, true);
    ;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 1854 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true);
    ;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 1859 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true);
    ;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 1864 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd1D, true, true);
    ;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 1869 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, true);
    ;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 1874 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true);
    ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 1879 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdCube, true, true);
    ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 1884 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D);
    ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 1889 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D);
    ;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 1894 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd3D);
    ;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 1899 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube);
    ;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 1904 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd1D, true);
    ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 1909 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true);
    ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 1914 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdCube, true);
    ;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 1919 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D);
    ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 1924 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D);
    ;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 1929 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd3D);
    ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 1934 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube);
    ;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 1939 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd1D, true);
    ;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 1944 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true);
    ;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 1949 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdCube, true);
    ;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 1954 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect);
    ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 1959 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdRect, false, true);
    ;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 1964 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdRect);
    ;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 1969 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdRect);
    ;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 1974 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, EsdBuffer);
    ;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 1979 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, EsdBuffer);
    ;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 1984 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, EsdBuffer);
    ;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 1989 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, false, false, true);
    ;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 1994 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, false, false, true);
    ;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 1999 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, false, false, true);
    ;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 2004 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D, true, false, true);
    ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 2009 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtInt, Esd2D, true, false, true);
    ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 2014 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtUint, Esd2D, true, false, true);
    ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 2019 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(false);
    ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2024 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setPureSampler(true);
    ;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 2029 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D);
    ;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 2034 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D);
    ;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 2039 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd3D);
    ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 2044 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube);
    ;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 2049 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd1D, true);
    ;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 2054 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true);
    ;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 2059 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdCube, true);
    ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 2064 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D);
    ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 2069 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D);
    ;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 2074 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd3D);
    ;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 2079 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube);
    ;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 2084 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd1D, true);
    ;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 2089 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true);
    ;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 2094 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdCube, true);
    ;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 2099 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D);
    ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 2104 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D);
    ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 2109 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd3D);
    ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 2114 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube);
    ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 2119 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd1D, true);
    ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 2124 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true);
    ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 2129 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdCube, true);
    ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 2134 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdRect);
    ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 2139 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdRect);
    ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2144 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdRect);
    ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 2149 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, EsdBuffer);
    ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2154 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, EsdBuffer);
    ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 2159 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, EsdBuffer);
    ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2164 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, false, false, true);
    ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 2169 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, false, false, true);
    ;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 2174 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, false, false, true);
    ;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 2179 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtFloat, Esd2D, true, false, true);
    ;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 2184 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtInt, Esd2D, true, false, true);
    ;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 2189 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setTexture(EbtUint, Esd2D, true, false, true);
    ;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 2194 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D);
    ;}
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 2199 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D);
    ;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 2204 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D);
    ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2209 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D);
    ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2214 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D);
    ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2219 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D);
    ;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 2224 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd3D);
    ;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 2229 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd3D);
    ;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2234 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd3D);
    ;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2239 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdRect);
    ;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2244 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdRect);
    ;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2249 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdRect);
    ;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 2254 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube);
    ;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2259 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube);
    ;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 2264 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube);
    ;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 2269 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdBuffer);
    ;}
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 2274 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdBuffer);
    ;}
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 2279 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdBuffer);
    ;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 2284 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd1D, true);
    ;}
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 2289 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd1D, true);
    ;}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 2294 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd1D, true);
    ;}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 2299 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true);
    ;}
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 2304 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true);
    ;}
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 2309 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true);
    ;}
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 2314 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, EsdCube, true);
    ;}
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 2319 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, EsdCube, true);
    ;}
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 2324 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, EsdCube, true);
    ;}
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 2329 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, false, false, true);
    ;}
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 2334 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, false, false, true);
    ;}
    break;

  case 357:

/* Line 1455 of yacc.c  */
#line 2339 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, false, false, true);
    ;}
    break;

  case 358:

/* Line 1455 of yacc.c  */
#line 2344 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtFloat, Esd2D, true, false, true);
    ;}
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 2349 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtInt, Esd2D, true, false, true);
    ;}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 2354 "glslang.y"
    {
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setImage(EbtUint, Esd2D, true, false, true);
    ;}
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 2359 "glslang.y"
    {  // GL_OES_EGL_image_external
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.set(EbtFloat, Esd2D);
        (yyval.interm.type).sampler.external = true;
    ;}
    break;

  case 362:

/* Line 1455 of yacc.c  */
#line 2365 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat);
    ;}
    break;

  case 363:

/* Line 1455 of yacc.c  */
#line 2371 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtFloat, true);
    ;}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 2377 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt);
    ;}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 2383 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtInt, true);
    ;}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 2389 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint);
    ;}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 2395 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (1)].lex).loc, EShLangFragment, "subpass input");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        (yyval.interm.type).basicType = EbtSampler;
        (yyval.interm.type).sampler.setSubpass(EbtUint, true);
    ;}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 2401 "glslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
        (yyval.interm.type).qualifier.storage = parseContext.symbolTable.atGlobalLevel() ? EvqGlobal : EvqTemporary;
        parseContext.structTypeCheck((yyval.interm.type).loc, (yyval.interm.type));
    ;}
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 2406 "glslang.y"
    {
        //
        // This is for user defined type names.  The lexical phase looked up the
        // type.
        //
        if (const TVariable* variable = ((yyvsp[(1) - (1)].lex).symbol)->getAsVariable()) {
            const TType& structure = variable->getType();
            (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
            (yyval.interm.type).basicType = EbtStruct;
            (yyval.interm.type).userDef = &structure;
        } else
            parseContext.error((yyvsp[(1) - (1)].lex).loc, "expected type name", (yyvsp[(1) - (1)].lex).string->c_str(), "");
    ;}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2422 "glslang.y"
    {
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "highp precision qualifier");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[(1) - (1)].lex).loc, (yyval.interm.type).qualifier, EpqHigh);
    ;}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2427 "glslang.y"
    {
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "mediump precision qualifier");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[(1) - (1)].lex).loc, (yyval.interm.type).qualifier, EpqMedium);
    ;}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2432 "glslang.y"
    {
        parseContext.profileRequires((yyvsp[(1) - (1)].lex).loc, ENoProfile, 130, 0, "lowp precision qualifier");
        (yyval.interm.type).init((yyvsp[(1) - (1)].lex).loc, parseContext.symbolTable.atGlobalLevel());
        parseContext.handlePrecisionQualifier((yyvsp[(1) - (1)].lex).loc, (yyval.interm.type).qualifier, EpqLow);
    ;}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2440 "glslang.y"
    { parseContext.nestedStructCheck((yyvsp[(1) - (3)].lex).loc); ;}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2440 "glslang.y"
    {
        TType* structure = new TType((yyvsp[(5) - (6)].interm.typeList), *(yyvsp[(2) - (6)].lex).string);
        parseContext.structArrayCheck((yyvsp[(2) - (6)].lex).loc, *structure);
        TVariable* userTypeDef = new TVariable((yyvsp[(2) - (6)].lex).string, *structure, true);
        if (! parseContext.symbolTable.insert(*userTypeDef))
            parseContext.error((yyvsp[(2) - (6)].lex).loc, "redefinition", (yyvsp[(2) - (6)].lex).string->c_str(), "struct");
        (yyval.interm.type).init((yyvsp[(1) - (6)].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    ;}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2451 "glslang.y"
    { parseContext.nestedStructCheck((yyvsp[(1) - (2)].lex).loc); ;}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2451 "glslang.y"
    {
        TType* structure = new TType((yyvsp[(4) - (5)].interm.typeList), TString(""));
        (yyval.interm.type).init((yyvsp[(1) - (5)].lex).loc);
        (yyval.interm.type).basicType = EbtStruct;
        (yyval.interm.type).userDef = structure;
        --parseContext.structNestingLevel;
    ;}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2461 "glslang.y"
    {
        (yyval.interm.typeList) = (yyvsp[(1) - (1)].interm.typeList);
    ;}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2464 "glslang.y"
    {
        (yyval.interm.typeList) = (yyvsp[(1) - (2)].interm.typeList);
        for (unsigned int i = 0; i < (yyvsp[(2) - (2)].interm.typeList)->size(); ++i) {
            for (unsigned int j = 0; j < (yyval.interm.typeList)->size(); ++j) {
                if ((*(yyval.interm.typeList))[j].type->getFieldName() == (*(yyvsp[(2) - (2)].interm.typeList))[i].type->getFieldName())
                    parseContext.error((*(yyvsp[(2) - (2)].interm.typeList))[i].loc, "duplicate member name:", "", (*(yyvsp[(2) - (2)].interm.typeList))[i].type->getFieldName().c_str());
            }
            (yyval.interm.typeList)->push_back((*(yyvsp[(2) - (2)].interm.typeList))[i]);
        }
    ;}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 2477 "glslang.y"
    {
        if ((yyvsp[(1) - (3)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(1) - (3)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(1) - (3)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck((yyvsp[(1) - (3)].interm.type).loc, *(yyvsp[(1) - (3)].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[(2) - (3)].interm.typeList);

        parseContext.voidErrorCheck((yyvsp[(1) - (3)].interm.type).loc, (*(yyvsp[(2) - (3)].interm.typeList))[0].type->getFieldName(), (yyvsp[(1) - (3)].interm.type).basicType);
        parseContext.precisionQualifierCheck((yyvsp[(1) - (3)].interm.type).loc, (yyvsp[(1) - (3)].interm.type).basicType, (yyvsp[(1) - (3)].interm.type).qualifier);

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            parseContext.arrayDimCheck((yyvsp[(1) - (3)].interm.type).loc, (*(yyval.interm.typeList))[i].type, (yyvsp[(1) - (3)].interm.type).arraySizes);
            (*(yyval.interm.typeList))[i].type->mergeType((yyvsp[(1) - (3)].interm.type));
        }
    ;}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 2495 "glslang.y"
    {
        parseContext.globalQualifierFixCheck((yyvsp[(1) - (4)].interm.type).loc, (yyvsp[(1) - (4)].interm.type).qualifier);
        if ((yyvsp[(2) - (4)].interm.type).arraySizes) {
            parseContext.profileRequires((yyvsp[(2) - (4)].interm.type).loc, ENoProfile, 120, E_GL_3DL_array_objects, "arrayed type");
            parseContext.profileRequires((yyvsp[(2) - (4)].interm.type).loc, EEsProfile, 300, 0, "arrayed type");
            if (parseContext.profile == EEsProfile)
                parseContext.arraySizeRequiredCheck((yyvsp[(2) - (4)].interm.type).loc, *(yyvsp[(2) - (4)].interm.type).arraySizes);
        }

        (yyval.interm.typeList) = (yyvsp[(3) - (4)].interm.typeList);

        parseContext.checkNoShaderLayouts((yyvsp[(1) - (4)].interm.type).loc, (yyvsp[(1) - (4)].interm.type).shaderQualifiers);
        parseContext.voidErrorCheck((yyvsp[(2) - (4)].interm.type).loc, (*(yyvsp[(3) - (4)].interm.typeList))[0].type->getFieldName(), (yyvsp[(2) - (4)].interm.type).basicType);
        parseContext.mergeQualifiers((yyvsp[(2) - (4)].interm.type).loc, (yyvsp[(2) - (4)].interm.type).qualifier, (yyvsp[(1) - (4)].interm.type).qualifier, true);
        parseContext.precisionQualifierCheck((yyvsp[(2) - (4)].interm.type).loc, (yyvsp[(2) - (4)].interm.type).basicType, (yyvsp[(2) - (4)].interm.type).qualifier);

        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            parseContext.arrayDimCheck((yyvsp[(1) - (4)].interm.type).loc, (*(yyval.interm.typeList))[i].type, (yyvsp[(2) - (4)].interm.type).arraySizes);
            (*(yyval.interm.typeList))[i].type->mergeType((yyvsp[(2) - (4)].interm.type));
        }
    ;}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2519 "glslang.y"
    {
        (yyval.interm.typeList) = new TTypeList;
        (yyval.interm.typeList)->push_back((yyvsp[(1) - (1)].interm.typeLine));
    ;}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2523 "glslang.y"
    {
        (yyval.interm.typeList)->push_back((yyvsp[(3) - (3)].interm.typeLine));
    ;}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2529 "glslang.y"
    {
        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[(1) - (1)].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[(1) - (1)].lex).string);
    ;}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2534 "glslang.y"
    {
        parseContext.arrayDimCheck((yyvsp[(1) - (2)].lex).loc, (yyvsp[(2) - (2)].interm).arraySizes, 0);

        (yyval.interm.typeLine).type = new TType(EbtVoid);
        (yyval.interm.typeLine).loc = (yyvsp[(1) - (2)].lex).loc;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[(1) - (2)].lex).string);
        (yyval.interm.typeLine).type->newArraySizes(*(yyvsp[(2) - (2)].interm).arraySizes);
    ;}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2545 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2548 "glslang.y"
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[(1) - (3)].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[(1) - (3)].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[(2) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2554 "glslang.y"
    {
        const char* initFeature = "{ } style initializers";
        parseContext.requireProfile((yyvsp[(1) - (4)].lex).loc, ~EEsProfile, initFeature);
        parseContext.profileRequires((yyvsp[(1) - (4)].lex).loc, ~EEsProfile, 420, E_GL_ARB_shading_language_420pack, initFeature);
        (yyval.interm.intermTypedNode) = (yyvsp[(2) - (4)].interm.intermTypedNode);
    ;}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2563 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate(0, (yyvsp[(1) - (1)].interm.intermTypedNode), (yyvsp[(1) - (1)].interm.intermTypedNode)->getLoc());
    ;}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2566 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.growAggregate((yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode));
    ;}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2572 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2576 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2577 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2583 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2584 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2585 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2586 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 2587 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2588 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2589 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2593 "glslang.y"
    { (yyval.interm.intermNode) = 0; ;}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2594 "glslang.y"
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
    ;}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2598 "glslang.y"
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
    ;}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2602 "glslang.y"
    {
        if ((yyvsp[(3) - (5)].interm.intermNode) && (yyvsp[(3) - (5)].interm.intermNode)->getAsAggregate())
            (yyvsp[(3) - (5)].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[(3) - (5)].interm.intermNode);
    ;}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2610 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2611 "glslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2615 "glslang.y"
    {
        ++parseContext.controlFlowNestingLevel;
    ;}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 2618 "glslang.y"
    {
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[(2) - (2)].interm.intermNode);
    ;}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2622 "glslang.y"
    {
        parseContext.symbolTable.push();
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    ;}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2627 "glslang.y"
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
        (yyval.interm.intermNode) = (yyvsp[(2) - (2)].interm.intermNode);
    ;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2636 "glslang.y"
    {
        (yyval.interm.intermNode) = 0;
    ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2639 "glslang.y"
    {
        if ((yyvsp[(2) - (3)].interm.intermNode) && (yyvsp[(2) - (3)].interm.intermNode)->getAsAggregate())
            (yyvsp[(2) - (3)].interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        (yyval.interm.intermNode) = (yyvsp[(2) - (3)].interm.intermNode);
    ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2647 "glslang.y"
    {
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[(1) - (1)].interm.intermNode));
        if ((yyvsp[(1) - (1)].interm.intermNode) && (yyvsp[(1) - (1)].interm.intermNode)->getAsBranchNode() && ((yyvsp[(1) - (1)].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[(1) - (1)].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence(0, (yyvsp[(1) - (1)].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        }
    ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2655 "glslang.y"
    {
        if ((yyvsp[(2) - (2)].interm.intermNode) && (yyvsp[(2) - (2)].interm.intermNode)->getAsBranchNode() && ((yyvsp[(2) - (2)].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpCase ||
                                            (yyvsp[(2) - (2)].interm.intermNode)->getAsBranchNode()->getFlowOp() == EOpDefault)) {
            parseContext.wrapupSwitchSubsequence((yyvsp[(1) - (2)].interm.intermNode) ? (yyvsp[(1) - (2)].interm.intermNode)->getAsAggregate() : 0, (yyvsp[(2) - (2)].interm.intermNode));
            (yyval.interm.intermNode) = 0;  // start a fresh subsequence for what's after this case
        } else
            (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[(1) - (2)].interm.intermNode), (yyvsp[(2) - (2)].interm.intermNode));
    ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2666 "glslang.y"
    { (yyval.interm.intermNode) = 0; ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2667 "glslang.y"
    { (yyval.interm.intermNode) = static_cast<TIntermNode*>((yyvsp[(1) - (2)].interm.intermTypedNode)); ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2671 "glslang.y"
    {
        parseContext.boolCheck((yyvsp[(1) - (5)].lex).loc, (yyvsp[(3) - (5)].interm.intermTypedNode));
        (yyval.interm.intermNode) = parseContext.intermediate.addSelection((yyvsp[(3) - (5)].interm.intermTypedNode), (yyvsp[(5) - (5)].interm.nodePair), (yyvsp[(1) - (5)].lex).loc);
    ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2678 "glslang.y"
    {
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (3)].interm.intermNode);
        (yyval.interm.nodePair).node2 = (yyvsp[(3) - (3)].interm.intermNode);
    ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 2682 "glslang.y"
    {
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (1)].interm.intermNode);
        (yyval.interm.nodePair).node2 = 0;
    ;}
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 2690 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
        parseContext.boolCheck((yyvsp[(1) - (1)].interm.intermTypedNode)->getLoc(), (yyvsp[(1) - (1)].interm.intermTypedNode));
    ;}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 2694 "glslang.y"
    {
        parseContext.boolCheck((yyvsp[(2) - (4)].lex).loc, (yyvsp[(1) - (4)].interm.type));

        TType type((yyvsp[(1) - (4)].interm.type));
        TIntermNode* initNode = parseContext.declareVariable((yyvsp[(2) - (4)].lex).loc, *(yyvsp[(2) - (4)].lex).string, (yyvsp[(1) - (4)].interm.type), 0, (yyvsp[(4) - (4)].interm.intermTypedNode));
        if (initNode)
            (yyval.interm.intermTypedNode) = initNode->getAsTyped();
        else
            (yyval.interm.intermTypedNode) = 0;
    ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 2707 "glslang.y"
    {
        // start new switch sequence on the switch stack
        ++parseContext.controlFlowNestingLevel;
        ++parseContext.statementNestingLevel;
        parseContext.switchSequenceStack.push_back(new TIntermSequence);
        parseContext.switchLevel.push_back(parseContext.statementNestingLevel);
        parseContext.symbolTable.push();
    ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2715 "glslang.y"
    {
        (yyval.interm.intermNode) = parseContext.addSwitch((yyvsp[(1) - (8)].lex).loc, (yyvsp[(3) - (8)].interm.intermTypedNode), (yyvsp[(7) - (8)].interm.intermNode) ? (yyvsp[(7) - (8)].interm.intermNode)->getAsAggregate() : 0);
        delete parseContext.switchSequenceStack.back();
        parseContext.switchSequenceStack.pop_back();
        parseContext.switchLevel.pop_back();
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2727 "glslang.y"
    {
        (yyval.interm.intermNode) = 0;
    ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 2730 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
    ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2736 "glslang.y"
    {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[(1) - (3)].lex).loc, "cannot appear outside switch statement", "case", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[(1) - (3)].lex).loc, "cannot be nested inside control flow", "case", "");
        else {
            parseContext.constantValueCheck((yyvsp[(2) - (3)].interm.intermTypedNode), "case");
            parseContext.integerCheck((yyvsp[(2) - (3)].interm.intermTypedNode), "case");
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpCase, (yyvsp[(2) - (3)].interm.intermTypedNode), (yyvsp[(1) - (3)].lex).loc);
        }
    ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2748 "glslang.y"
    {
        (yyval.interm.intermNode) = 0;
        if (parseContext.switchLevel.size() == 0)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "cannot appear outside switch statement", "default", "");
        else if (parseContext.switchLevel.back() != parseContext.statementNestingLevel)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "cannot be nested inside control flow", "default", "");
        else
            (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpDefault, (yyvsp[(1) - (2)].lex).loc);
    ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2760 "glslang.y"
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "while loops not available", "limitation", "");
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 2768 "glslang.y"
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[(6) - (6)].interm.intermNode), (yyvsp[(4) - (6)].interm.intermTypedNode), 0, true, (yyvsp[(1) - (6)].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    ;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 2775 "glslang.y"
    {
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 2780 "glslang.y"
    {
        if (! parseContext.limits.whileLoops)
            parseContext.error((yyvsp[(1) - (8)].lex).loc, "do-while loops not available", "limitation", "");

        parseContext.boolCheck((yyvsp[(8) - (8)].lex).loc, (yyvsp[(6) - (8)].interm.intermTypedNode));

        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[(3) - (8)].interm.intermNode), (yyvsp[(6) - (8)].interm.intermTypedNode), 0, false, (yyvsp[(4) - (8)].lex).loc);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2791 "glslang.y"
    {
        parseContext.symbolTable.push();
        ++parseContext.loopNestingLevel;
        ++parseContext.statementNestingLevel;
        ++parseContext.controlFlowNestingLevel;
    ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 2797 "glslang.y"
    {
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[(4) - (7)].interm.intermNode), (yyvsp[(2) - (7)].lex).loc);
        TIntermLoop* forLoop = parseContext.intermediate.addLoop((yyvsp[(7) - (7)].interm.intermNode), reinterpret_cast<TIntermTyped*>((yyvsp[(5) - (7)].interm.nodePair).node1), reinterpret_cast<TIntermTyped*>((yyvsp[(5) - (7)].interm.nodePair).node2), true, (yyvsp[(1) - (7)].lex).loc);
        if (! parseContext.limits.nonInductiveForLoops)
            parseContext.inductiveLoopCheck((yyvsp[(1) - (7)].lex).loc, (yyvsp[(4) - (7)].interm.intermNode), forLoop);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyval.interm.intermNode), forLoop, (yyvsp[(1) - (7)].lex).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        --parseContext.loopNestingLevel;
        --parseContext.statementNestingLevel;
        --parseContext.controlFlowNestingLevel;
    ;}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 2812 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
    ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 2815 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
    ;}
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 2821 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 2824 "glslang.y"
    {
        (yyval.interm.intermTypedNode) = 0;
    ;}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 2830 "glslang.y"
    {
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (2)].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = 0;
    ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 2834 "glslang.y"
    {
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (3)].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = (yyvsp[(3) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 2841 "glslang.y"
    {
        if (parseContext.loopNestingLevel <= 0)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "continue statement only allowed in loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpContinue, (yyvsp[(1) - (2)].lex).loc);
    ;}
    break;

  case 440:

/* Line 1455 of yacc.c  */
#line 2846 "glslang.y"
    {
        if (parseContext.loopNestingLevel + parseContext.switchSequenceStack.size() <= 0)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "break statement only allowed in switch and loops", "", "");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpBreak, (yyvsp[(1) - (2)].lex).loc);
    ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 2851 "glslang.y"
    {
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpReturn, (yyvsp[(1) - (2)].lex).loc);
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid)
            parseContext.error((yyvsp[(1) - (2)].lex).loc, "non-void function must return a value", "return", "");
        if (parseContext.inMain)
            parseContext.postEntryPointReturn = true;
    ;}
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 2858 "glslang.y"
    {
        (yyval.interm.intermNode) = parseContext.handleReturnValue((yyvsp[(1) - (3)].lex).loc, (yyvsp[(2) - (3)].interm.intermTypedNode));
    ;}
    break;

  case 443:

/* Line 1455 of yacc.c  */
#line 2861 "glslang.y"
    {
        parseContext.requireStage((yyvsp[(1) - (2)].lex).loc, EShLangFragment, "discard");
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpKill, (yyvsp[(1) - (2)].lex).loc);
    ;}
    break;

  case 444:

/* Line 1455 of yacc.c  */
#line 2870 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
        parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
    ;}
    break;

  case 445:

/* Line 1455 of yacc.c  */
#line 2874 "glslang.y"
    {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[(1) - (2)].interm.intermNode), (yyvsp[(2) - (2)].interm.intermNode));
        parseContext.intermediate.setTreeRoot((yyval.interm.intermNode));
    ;}
    break;

  case 446:

/* Line 1455 of yacc.c  */
#line 2881 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
    ;}
    break;

  case 447:

/* Line 1455 of yacc.c  */
#line 2884 "glslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
    ;}
    break;

  case 448:

/* Line 1455 of yacc.c  */
#line 2890 "glslang.y"
    {
        (yyvsp[(1) - (1)].interm).function = parseContext.handleFunctionDeclarator((yyvsp[(1) - (1)].interm).loc, *(yyvsp[(1) - (1)].interm).function, false /* not prototype */);
        (yyvsp[(1) - (1)].interm).intermNode = parseContext.handleFunctionDefinition((yyvsp[(1) - (1)].interm).loc, *(yyvsp[(1) - (1)].interm).function);
    ;}
    break;

  case 449:

/* Line 1455 of yacc.c  */
#line 2894 "glslang.y"
    {
        //   May be best done as post process phase on intermediate code
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid && ! parseContext.functionReturnsValue)
            parseContext.error((yyvsp[(1) - (3)].interm).loc, "function does not return a value:", "", (yyvsp[(1) - (3)].interm).function->getName().c_str());
        parseContext.symbolTable.pop(&parseContext.defaultPrecision[0]);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[(1) - (3)].interm).intermNode, (yyvsp[(3) - (3)].interm.intermNode));
        parseContext.intermediate.setAggregateOperator((yyval.interm.intermNode), EOpFunction, (yyvsp[(1) - (3)].interm).function->getType(), (yyvsp[(1) - (3)].interm).loc);
        (yyval.interm.intermNode)->getAsAggregate()->setName((yyvsp[(1) - (3)].interm).function->getMangledName().c_str());

        // store the pragma information for debug and optimize and other vendor specific
        // information. This information can be queried from the parse tree
        (yyval.interm.intermNode)->getAsAggregate()->setOptimize(parseContext.contextPragma.optimize);
        (yyval.interm.intermNode)->getAsAggregate()->setDebug(parseContext.contextPragma.debug);
        (yyval.interm.intermNode)->getAsAggregate()->addToPragmaTable(parseContext.contextPragma.pragmaTable);
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 8703 "glslang_tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (pParseContext, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (pParseContext, yymsg);
	  }
	else
	  {
	    yyerror (pParseContext, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, pParseContext);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 2911 "glslang.y"


