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
    LEFT_OP = 316,
    RIGHT_OP = 317,
    INC_OP = 318,
    DEC_OP = 319,
    LE_OP = 320,
    GE_OP = 321,
    EQ_OP = 322,
    NE_OP = 323,
    AND_OP = 324,
    OR_OP = 325,
    XOR_OP = 326,
    MUL_ASSIGN = 327,
    DIV_ASSIGN = 328,
    ADD_ASSIGN = 329,
    MOD_ASSIGN = 330,
    LEFT_ASSIGN = 331,
    RIGHT_ASSIGN = 332,
    AND_ASSIGN = 333,
    XOR_ASSIGN = 334,
    OR_ASSIGN = 335,
    SUB_ASSIGN = 336,
    LEFT_PAREN = 337,
    RIGHT_PAREN = 338,
    LEFT_BRACKET = 339,
    RIGHT_BRACKET = 340,
    LEFT_BRACE = 341,
    RIGHT_BRACE = 342,
    DOT = 343,
    COMMA = 344,
    COLON = 345,
    EQUAL = 346,
    SEMICOLON = 347,
    BANG = 348,
    DASH = 349,
    TILDE = 350,
    PLUS = 351,
    STAR = 352,
    SLASH = 353,
    PERCENT = 354,
    LEFT_ANGLE = 355,
    RIGHT_ANGLE = 356,
    VERTICAL_BAR = 357,
    CARET = 358,
    AMPERSAND = 359,
    QUESTION = 360,
    INVARIANT = 361,
    HIGH_PRECISION = 362,
    MEDIUM_PRECISION = 363,
    LOW_PRECISION = 364,
    PRECISION = 365,
    PACKED = 366,
    RESOURCE = 367,
    SUPERP = 368,
    FLOATCONSTANT = 369,
    INTCONSTANT = 370,
    UINTCONSTANT = 371,
    BOOLCONSTANT = 372,
    IDENTIFIER = 373,
    TYPE_NAME = 374,
    CENTROID = 375,
    IN = 376,
    OUT = 377,
    INOUT = 378,
    STRUCT = 379,
    VOID = 380,
    WHILE = 381,
    BREAK = 382,
    CONTINUE = 383,
    DO = 384,
    ELSE = 385,
    FOR = 386,
    IF = 387,
    DISCARD = 388,
    RETURN = 389,
    SWITCH = 390,
    CASE = 391,
    DEFAULT = 392,
    UNIFORM = 393,
    SHARED = 394,
    FLAT = 395,
    SMOOTH = 396,
    LAYOUT = 397
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 96 "MachineIndependent/glslang.y" /* yacc.c:1909  */

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

#line 233 "MachineIndependent/glslang_tab.cpp.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (glslang::TParseContext* pParseContext);

#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */
