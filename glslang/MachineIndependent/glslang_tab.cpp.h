/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED
# define YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CONST = 258,                   /* CONST  */
    BOOL = 259,                    /* BOOL  */
    INT = 260,                     /* INT  */
    UINT = 261,                    /* UINT  */
    FLOAT = 262,                   /* FLOAT  */
    BVEC2 = 263,                   /* BVEC2  */
    BVEC3 = 264,                   /* BVEC3  */
    BVEC4 = 265,                   /* BVEC4  */
    IVEC2 = 266,                   /* IVEC2  */
    IVEC3 = 267,                   /* IVEC3  */
    IVEC4 = 268,                   /* IVEC4  */
    UVEC2 = 269,                   /* UVEC2  */
    UVEC3 = 270,                   /* UVEC3  */
    UVEC4 = 271,                   /* UVEC4  */
    VEC2 = 272,                    /* VEC2  */
    VEC3 = 273,                    /* VEC3  */
    VEC4 = 274,                    /* VEC4  */
    MAT2 = 275,                    /* MAT2  */
    MAT3 = 276,                    /* MAT3  */
    MAT4 = 277,                    /* MAT4  */
    MAT2X2 = 278,                  /* MAT2X2  */
    MAT2X3 = 279,                  /* MAT2X3  */
    MAT2X4 = 280,                  /* MAT2X4  */
    MAT3X2 = 281,                  /* MAT3X2  */
    MAT3X3 = 282,                  /* MAT3X3  */
    MAT3X4 = 283,                  /* MAT3X4  */
    MAT4X2 = 284,                  /* MAT4X2  */
    MAT4X3 = 285,                  /* MAT4X3  */
    MAT4X4 = 286,                  /* MAT4X4  */
    SAMPLER2D = 287,               /* SAMPLER2D  */
    SAMPLER3D = 288,               /* SAMPLER3D  */
    SAMPLERCUBE = 289,             /* SAMPLERCUBE  */
    SAMPLER2DSHADOW = 290,         /* SAMPLER2DSHADOW  */
    SAMPLERCUBESHADOW = 291,       /* SAMPLERCUBESHADOW  */
    SAMPLER2DARRAY = 292,          /* SAMPLER2DARRAY  */
    SAMPLER2DARRAYSHADOW = 293,    /* SAMPLER2DARRAYSHADOW  */
    ISAMPLER2D = 294,              /* ISAMPLER2D  */
    ISAMPLER3D = 295,              /* ISAMPLER3D  */
    ISAMPLERCUBE = 296,            /* ISAMPLERCUBE  */
    ISAMPLER2DARRAY = 297,         /* ISAMPLER2DARRAY  */
    USAMPLER2D = 298,              /* USAMPLER2D  */
    USAMPLER3D = 299,              /* USAMPLER3D  */
    USAMPLERCUBE = 300,            /* USAMPLERCUBE  */
    USAMPLER2DARRAY = 301,         /* USAMPLER2DARRAY  */
    SAMPLER = 302,                 /* SAMPLER  */
    SAMPLERSHADOW = 303,           /* SAMPLERSHADOW  */
    TEXTURE2D = 304,               /* TEXTURE2D  */
    TEXTURE3D = 305,               /* TEXTURE3D  */
    TEXTURECUBE = 306,             /* TEXTURECUBE  */
    TEXTURE2DARRAY = 307,          /* TEXTURE2DARRAY  */
    ITEXTURE2D = 308,              /* ITEXTURE2D  */
    ITEXTURE3D = 309,              /* ITEXTURE3D  */
    ITEXTURECUBE = 310,            /* ITEXTURECUBE  */
    ITEXTURE2DARRAY = 311,         /* ITEXTURE2DARRAY  */
    UTEXTURE2D = 312,              /* UTEXTURE2D  */
    UTEXTURE3D = 313,              /* UTEXTURE3D  */
    UTEXTURECUBE = 314,            /* UTEXTURECUBE  */
    UTEXTURE2DARRAY = 315,         /* UTEXTURE2DARRAY  */
    ATTRIBUTE = 316,               /* ATTRIBUTE  */
    VARYING = 317,                 /* VARYING  */
    FLOATE5M2_T = 318,             /* FLOATE5M2_T  */
    FLOATE4M3_T = 319,             /* FLOATE4M3_T  */
    BFLOAT16_T = 320,              /* BFLOAT16_T  */
    FLOAT16_T = 321,               /* FLOAT16_T  */
    FLOAT32_T = 322,               /* FLOAT32_T  */
    DOUBLE = 323,                  /* DOUBLE  */
    FLOAT64_T = 324,               /* FLOAT64_T  */
    FLOATE2M1_T = 325,             /* FLOATE2M1_T  */
    FLOATE3M2_T = 326,             /* FLOATE3M2_T  */
    FLOATE2M3_T = 327,             /* FLOATE2M3_T  */
    FLOATUE8M0_T = 328,            /* FLOATUE8M0_T  */
    FLOATMXINT8_T = 329,           /* FLOATMXINT8_T  */
    INT64_T = 330,                 /* INT64_T  */
    UINT64_T = 331,                /* UINT64_T  */
    INT32_T = 332,                 /* INT32_T  */
    UINT32_T = 333,                /* UINT32_T  */
    INT16_T = 334,                 /* INT16_T  */
    UINT16_T = 335,                /* UINT16_T  */
    INT8_T = 336,                  /* INT8_T  */
    UINT8_T = 337,                 /* UINT8_T  */
    I64VEC2 = 338,                 /* I64VEC2  */
    I64VEC3 = 339,                 /* I64VEC3  */
    I64VEC4 = 340,                 /* I64VEC4  */
    U64VEC2 = 341,                 /* U64VEC2  */
    U64VEC3 = 342,                 /* U64VEC3  */
    U64VEC4 = 343,                 /* U64VEC4  */
    I32VEC2 = 344,                 /* I32VEC2  */
    I32VEC3 = 345,                 /* I32VEC3  */
    I32VEC4 = 346,                 /* I32VEC4  */
    U32VEC2 = 347,                 /* U32VEC2  */
    U32VEC3 = 348,                 /* U32VEC3  */
    U32VEC4 = 349,                 /* U32VEC4  */
    I16VEC2 = 350,                 /* I16VEC2  */
    I16VEC3 = 351,                 /* I16VEC3  */
    I16VEC4 = 352,                 /* I16VEC4  */
    U16VEC2 = 353,                 /* U16VEC2  */
    U16VEC3 = 354,                 /* U16VEC3  */
    U16VEC4 = 355,                 /* U16VEC4  */
    I8VEC2 = 356,                  /* I8VEC2  */
    I8VEC3 = 357,                  /* I8VEC3  */
    I8VEC4 = 358,                  /* I8VEC4  */
    U8VEC2 = 359,                  /* U8VEC2  */
    U8VEC3 = 360,                  /* U8VEC3  */
    U8VEC4 = 361,                  /* U8VEC4  */
    DVEC2 = 362,                   /* DVEC2  */
    DVEC3 = 363,                   /* DVEC3  */
    DVEC4 = 364,                   /* DVEC4  */
    DMAT2 = 365,                   /* DMAT2  */
    DMAT3 = 366,                   /* DMAT3  */
    DMAT4 = 367,                   /* DMAT4  */
    BF16VEC2 = 368,                /* BF16VEC2  */
    BF16VEC3 = 369,                /* BF16VEC3  */
    BF16VEC4 = 370,                /* BF16VEC4  */
    FE5M2VEC2 = 371,               /* FE5M2VEC2  */
    FE5M2VEC3 = 372,               /* FE5M2VEC3  */
    FE5M2VEC4 = 373,               /* FE5M2VEC4  */
    FE4M3VEC2 = 374,               /* FE4M3VEC2  */
    FE4M3VEC3 = 375,               /* FE4M3VEC3  */
    FE4M3VEC4 = 376,               /* FE4M3VEC4  */
    FE2M1VEC2 = 377,               /* FE2M1VEC2  */
    FE2M1VEC3 = 378,               /* FE2M1VEC3  */
    FE2M1VEC4 = 379,               /* FE2M1VEC4  */
    FE3M2VEC2 = 380,               /* FE3M2VEC2  */
    FE3M2VEC3 = 381,               /* FE3M2VEC3  */
    FE3M2VEC4 = 382,               /* FE3M2VEC4  */
    FE2M3VEC2 = 383,               /* FE2M3VEC2  */
    FE2M3VEC3 = 384,               /* FE2M3VEC3  */
    FE2M3VEC4 = 385,               /* FE2M3VEC4  */
    FUE8M0VEC2 = 386,              /* FUE8M0VEC2  */
    FUE8M0VEC3 = 387,              /* FUE8M0VEC3  */
    FUE8M0VEC4 = 388,              /* FUE8M0VEC4  */
    FMXINT8VEC2 = 389,             /* FMXINT8VEC2  */
    FMXINT8VEC3 = 390,             /* FMXINT8VEC3  */
    FMXINT8VEC4 = 391,             /* FMXINT8VEC4  */
    F16VEC2 = 392,                 /* F16VEC2  */
    F16VEC3 = 393,                 /* F16VEC3  */
    F16VEC4 = 394,                 /* F16VEC4  */
    F16MAT2 = 395,                 /* F16MAT2  */
    F16MAT3 = 396,                 /* F16MAT3  */
    F16MAT4 = 397,                 /* F16MAT4  */
    F32VEC2 = 398,                 /* F32VEC2  */
    F32VEC3 = 399,                 /* F32VEC3  */
    F32VEC4 = 400,                 /* F32VEC4  */
    F32MAT2 = 401,                 /* F32MAT2  */
    F32MAT3 = 402,                 /* F32MAT3  */
    F32MAT4 = 403,                 /* F32MAT4  */
    F64VEC2 = 404,                 /* F64VEC2  */
    F64VEC3 = 405,                 /* F64VEC3  */
    F64VEC4 = 406,                 /* F64VEC4  */
    F64MAT2 = 407,                 /* F64MAT2  */
    F64MAT3 = 408,                 /* F64MAT3  */
    F64MAT4 = 409,                 /* F64MAT4  */
    DMAT2X2 = 410,                 /* DMAT2X2  */
    DMAT2X3 = 411,                 /* DMAT2X3  */
    DMAT2X4 = 412,                 /* DMAT2X4  */
    DMAT3X2 = 413,                 /* DMAT3X2  */
    DMAT3X3 = 414,                 /* DMAT3X3  */
    DMAT3X4 = 415,                 /* DMAT3X4  */
    DMAT4X2 = 416,                 /* DMAT4X2  */
    DMAT4X3 = 417,                 /* DMAT4X3  */
    DMAT4X4 = 418,                 /* DMAT4X4  */
    F16MAT2X2 = 419,               /* F16MAT2X2  */
    F16MAT2X3 = 420,               /* F16MAT2X3  */
    F16MAT2X4 = 421,               /* F16MAT2X4  */
    F16MAT3X2 = 422,               /* F16MAT3X2  */
    F16MAT3X3 = 423,               /* F16MAT3X3  */
    F16MAT3X4 = 424,               /* F16MAT3X4  */
    F16MAT4X2 = 425,               /* F16MAT4X2  */
    F16MAT4X3 = 426,               /* F16MAT4X3  */
    F16MAT4X4 = 427,               /* F16MAT4X4  */
    F32MAT2X2 = 428,               /* F32MAT2X2  */
    F32MAT2X3 = 429,               /* F32MAT2X3  */
    F32MAT2X4 = 430,               /* F32MAT2X4  */
    F32MAT3X2 = 431,               /* F32MAT3X2  */
    F32MAT3X3 = 432,               /* F32MAT3X3  */
    F32MAT3X4 = 433,               /* F32MAT3X4  */
    F32MAT4X2 = 434,               /* F32MAT4X2  */
    F32MAT4X3 = 435,               /* F32MAT4X3  */
    F32MAT4X4 = 436,               /* F32MAT4X4  */
    F64MAT2X2 = 437,               /* F64MAT2X2  */
    F64MAT2X3 = 438,               /* F64MAT2X3  */
    F64MAT2X4 = 439,               /* F64MAT2X4  */
    F64MAT3X2 = 440,               /* F64MAT3X2  */
    F64MAT3X3 = 441,               /* F64MAT3X3  */
    F64MAT3X4 = 442,               /* F64MAT3X4  */
    F64MAT4X2 = 443,               /* F64MAT4X2  */
    F64MAT4X3 = 444,               /* F64MAT4X3  */
    F64MAT4X4 = 445,               /* F64MAT4X4  */
    ATOMIC_UINT = 446,             /* ATOMIC_UINT  */
    ACCSTRUCTNV = 447,             /* ACCSTRUCTNV  */
    ACCSTRUCTEXT = 448,            /* ACCSTRUCTEXT  */
    RAYQUERYEXT = 449,             /* RAYQUERYEXT  */
    FCOOPMATNV = 450,              /* FCOOPMATNV  */
    ICOOPMATNV = 451,              /* ICOOPMATNV  */
    UCOOPMATNV = 452,              /* UCOOPMATNV  */
    COOPMAT = 453,                 /* COOPMAT  */
    COOPVECNV = 454,               /* COOPVECNV  */
    VECTOR = 455,                  /* VECTOR  */
    HITOBJECTNV = 456,             /* HITOBJECTNV  */
    HITOBJECTATTRNV = 457,         /* HITOBJECTATTRNV  */
    HITOBJECTEXT = 458,            /* HITOBJECTEXT  */
    HITOBJECTATTREXT = 459,        /* HITOBJECTATTREXT  */
    TENSORLAYOUTNV = 460,          /* TENSORLAYOUTNV  */
    TENSORVIEWNV = 461,            /* TENSORVIEWNV  */
    TENSORARM = 462,               /* TENSORARM  */
    AUTO = 463,                    /* AUTO  */
    SAMPLERCUBEARRAY = 464,        /* SAMPLERCUBEARRAY  */
    SAMPLERCUBEARRAYSHADOW = 465,  /* SAMPLERCUBEARRAYSHADOW  */
    ISAMPLERCUBEARRAY = 466,       /* ISAMPLERCUBEARRAY  */
    USAMPLERCUBEARRAY = 467,       /* USAMPLERCUBEARRAY  */
    SAMPLER1D = 468,               /* SAMPLER1D  */
    SAMPLER1DARRAY = 469,          /* SAMPLER1DARRAY  */
    SAMPLER1DARRAYSHADOW = 470,    /* SAMPLER1DARRAYSHADOW  */
    ISAMPLER1D = 471,              /* ISAMPLER1D  */
    SAMPLER1DSHADOW = 472,         /* SAMPLER1DSHADOW  */
    SAMPLER2DRECT = 473,           /* SAMPLER2DRECT  */
    SAMPLER2DRECTSHADOW = 474,     /* SAMPLER2DRECTSHADOW  */
    ISAMPLER2DRECT = 475,          /* ISAMPLER2DRECT  */
    USAMPLER2DRECT = 476,          /* USAMPLER2DRECT  */
    SAMPLERBUFFER = 477,           /* SAMPLERBUFFER  */
    ISAMPLERBUFFER = 478,          /* ISAMPLERBUFFER  */
    USAMPLERBUFFER = 479,          /* USAMPLERBUFFER  */
    SAMPLER2DMS = 480,             /* SAMPLER2DMS  */
    ISAMPLER2DMS = 481,            /* ISAMPLER2DMS  */
    USAMPLER2DMS = 482,            /* USAMPLER2DMS  */
    SAMPLER2DMSARRAY = 483,        /* SAMPLER2DMSARRAY  */
    ISAMPLER2DMSARRAY = 484,       /* ISAMPLER2DMSARRAY  */
    USAMPLER2DMSARRAY = 485,       /* USAMPLER2DMSARRAY  */
    SAMPLEREXTERNALOES = 486,      /* SAMPLEREXTERNALOES  */
    SAMPLEREXTERNAL2DY2YEXT = 487, /* SAMPLEREXTERNAL2DY2YEXT  */
    ISAMPLER1DARRAY = 488,         /* ISAMPLER1DARRAY  */
    USAMPLER1D = 489,              /* USAMPLER1D  */
    USAMPLER1DARRAY = 490,         /* USAMPLER1DARRAY  */
    F16SAMPLER1D = 491,            /* F16SAMPLER1D  */
    F16SAMPLER2D = 492,            /* F16SAMPLER2D  */
    F16SAMPLER3D = 493,            /* F16SAMPLER3D  */
    F16SAMPLER2DRECT = 494,        /* F16SAMPLER2DRECT  */
    F16SAMPLERCUBE = 495,          /* F16SAMPLERCUBE  */
    F16SAMPLER1DARRAY = 496,       /* F16SAMPLER1DARRAY  */
    F16SAMPLER2DARRAY = 497,       /* F16SAMPLER2DARRAY  */
    F16SAMPLERCUBEARRAY = 498,     /* F16SAMPLERCUBEARRAY  */
    F16SAMPLERBUFFER = 499,        /* F16SAMPLERBUFFER  */
    F16SAMPLER2DMS = 500,          /* F16SAMPLER2DMS  */
    F16SAMPLER2DMSARRAY = 501,     /* F16SAMPLER2DMSARRAY  */
    F16SAMPLER1DSHADOW = 502,      /* F16SAMPLER1DSHADOW  */
    F16SAMPLER2DSHADOW = 503,      /* F16SAMPLER2DSHADOW  */
    F16SAMPLER1DARRAYSHADOW = 504, /* F16SAMPLER1DARRAYSHADOW  */
    F16SAMPLER2DARRAYSHADOW = 505, /* F16SAMPLER2DARRAYSHADOW  */
    F16SAMPLER2DRECTSHADOW = 506,  /* F16SAMPLER2DRECTSHADOW  */
    F16SAMPLERCUBESHADOW = 507,    /* F16SAMPLERCUBESHADOW  */
    F16SAMPLERCUBEARRAYSHADOW = 508, /* F16SAMPLERCUBEARRAYSHADOW  */
    IMAGE1D = 509,                 /* IMAGE1D  */
    IIMAGE1D = 510,                /* IIMAGE1D  */
    UIMAGE1D = 511,                /* UIMAGE1D  */
    IMAGE2D = 512,                 /* IMAGE2D  */
    IIMAGE2D = 513,                /* IIMAGE2D  */
    UIMAGE2D = 514,                /* UIMAGE2D  */
    IMAGE3D = 515,                 /* IMAGE3D  */
    IIMAGE3D = 516,                /* IIMAGE3D  */
    UIMAGE3D = 517,                /* UIMAGE3D  */
    IMAGE2DRECT = 518,             /* IMAGE2DRECT  */
    IIMAGE2DRECT = 519,            /* IIMAGE2DRECT  */
    UIMAGE2DRECT = 520,            /* UIMAGE2DRECT  */
    IMAGECUBE = 521,               /* IMAGECUBE  */
    IIMAGECUBE = 522,              /* IIMAGECUBE  */
    UIMAGECUBE = 523,              /* UIMAGECUBE  */
    IMAGEBUFFER = 524,             /* IMAGEBUFFER  */
    IIMAGEBUFFER = 525,            /* IIMAGEBUFFER  */
    UIMAGEBUFFER = 526,            /* UIMAGEBUFFER  */
    IMAGE1DARRAY = 527,            /* IMAGE1DARRAY  */
    IIMAGE1DARRAY = 528,           /* IIMAGE1DARRAY  */
    UIMAGE1DARRAY = 529,           /* UIMAGE1DARRAY  */
    IMAGE2DARRAY = 530,            /* IMAGE2DARRAY  */
    IIMAGE2DARRAY = 531,           /* IIMAGE2DARRAY  */
    UIMAGE2DARRAY = 532,           /* UIMAGE2DARRAY  */
    IMAGECUBEARRAY = 533,          /* IMAGECUBEARRAY  */
    IIMAGECUBEARRAY = 534,         /* IIMAGECUBEARRAY  */
    UIMAGECUBEARRAY = 535,         /* UIMAGECUBEARRAY  */
    IMAGE2DMS = 536,               /* IMAGE2DMS  */
    IIMAGE2DMS = 537,              /* IIMAGE2DMS  */
    UIMAGE2DMS = 538,              /* UIMAGE2DMS  */
    IMAGE2DMSARRAY = 539,          /* IMAGE2DMSARRAY  */
    IIMAGE2DMSARRAY = 540,         /* IIMAGE2DMSARRAY  */
    UIMAGE2DMSARRAY = 541,         /* UIMAGE2DMSARRAY  */
    F16IMAGE1D = 542,              /* F16IMAGE1D  */
    F16IMAGE2D = 543,              /* F16IMAGE2D  */
    F16IMAGE3D = 544,              /* F16IMAGE3D  */
    F16IMAGE2DRECT = 545,          /* F16IMAGE2DRECT  */
    F16IMAGECUBE = 546,            /* F16IMAGECUBE  */
    F16IMAGE1DARRAY = 547,         /* F16IMAGE1DARRAY  */
    F16IMAGE2DARRAY = 548,         /* F16IMAGE2DARRAY  */
    F16IMAGECUBEARRAY = 549,       /* F16IMAGECUBEARRAY  */
    F16IMAGEBUFFER = 550,          /* F16IMAGEBUFFER  */
    F16IMAGE2DMS = 551,            /* F16IMAGE2DMS  */
    F16IMAGE2DMSARRAY = 552,       /* F16IMAGE2DMSARRAY  */
    I64IMAGE1D = 553,              /* I64IMAGE1D  */
    U64IMAGE1D = 554,              /* U64IMAGE1D  */
    I64IMAGE2D = 555,              /* I64IMAGE2D  */
    U64IMAGE2D = 556,              /* U64IMAGE2D  */
    I64IMAGE3D = 557,              /* I64IMAGE3D  */
    U64IMAGE3D = 558,              /* U64IMAGE3D  */
    I64IMAGE2DRECT = 559,          /* I64IMAGE2DRECT  */
    U64IMAGE2DRECT = 560,          /* U64IMAGE2DRECT  */
    I64IMAGECUBE = 561,            /* I64IMAGECUBE  */
    U64IMAGECUBE = 562,            /* U64IMAGECUBE  */
    I64IMAGEBUFFER = 563,          /* I64IMAGEBUFFER  */
    U64IMAGEBUFFER = 564,          /* U64IMAGEBUFFER  */
    I64IMAGE1DARRAY = 565,         /* I64IMAGE1DARRAY  */
    U64IMAGE1DARRAY = 566,         /* U64IMAGE1DARRAY  */
    I64IMAGE2DARRAY = 567,         /* I64IMAGE2DARRAY  */
    U64IMAGE2DARRAY = 568,         /* U64IMAGE2DARRAY  */
    I64IMAGECUBEARRAY = 569,       /* I64IMAGECUBEARRAY  */
    U64IMAGECUBEARRAY = 570,       /* U64IMAGECUBEARRAY  */
    I64IMAGE2DMS = 571,            /* I64IMAGE2DMS  */
    U64IMAGE2DMS = 572,            /* U64IMAGE2DMS  */
    I64IMAGE2DMSARRAY = 573,       /* I64IMAGE2DMSARRAY  */
    U64IMAGE2DMSARRAY = 574,       /* U64IMAGE2DMSARRAY  */
    TEXTURECUBEARRAY = 575,        /* TEXTURECUBEARRAY  */
    ITEXTURECUBEARRAY = 576,       /* ITEXTURECUBEARRAY  */
    UTEXTURECUBEARRAY = 577,       /* UTEXTURECUBEARRAY  */
    TEXTURE1D = 578,               /* TEXTURE1D  */
    ITEXTURE1D = 579,              /* ITEXTURE1D  */
    UTEXTURE1D = 580,              /* UTEXTURE1D  */
    TEXTURE1DARRAY = 581,          /* TEXTURE1DARRAY  */
    ITEXTURE1DARRAY = 582,         /* ITEXTURE1DARRAY  */
    UTEXTURE1DARRAY = 583,         /* UTEXTURE1DARRAY  */
    TEXTURE2DRECT = 584,           /* TEXTURE2DRECT  */
    ITEXTURE2DRECT = 585,          /* ITEXTURE2DRECT  */
    UTEXTURE2DRECT = 586,          /* UTEXTURE2DRECT  */
    TEXTUREBUFFER = 587,           /* TEXTUREBUFFER  */
    ITEXTUREBUFFER = 588,          /* ITEXTUREBUFFER  */
    UTEXTUREBUFFER = 589,          /* UTEXTUREBUFFER  */
    TEXTURE2DMS = 590,             /* TEXTURE2DMS  */
    ITEXTURE2DMS = 591,            /* ITEXTURE2DMS  */
    UTEXTURE2DMS = 592,            /* UTEXTURE2DMS  */
    TEXTURE2DMSARRAY = 593,        /* TEXTURE2DMSARRAY  */
    ITEXTURE2DMSARRAY = 594,       /* ITEXTURE2DMSARRAY  */
    UTEXTURE2DMSARRAY = 595,       /* UTEXTURE2DMSARRAY  */
    F16TEXTURE1D = 596,            /* F16TEXTURE1D  */
    F16TEXTURE2D = 597,            /* F16TEXTURE2D  */
    F16TEXTURE3D = 598,            /* F16TEXTURE3D  */
    F16TEXTURE2DRECT = 599,        /* F16TEXTURE2DRECT  */
    F16TEXTURECUBE = 600,          /* F16TEXTURECUBE  */
    F16TEXTURE1DARRAY = 601,       /* F16TEXTURE1DARRAY  */
    F16TEXTURE2DARRAY = 602,       /* F16TEXTURE2DARRAY  */
    F16TEXTURECUBEARRAY = 603,     /* F16TEXTURECUBEARRAY  */
    F16TEXTUREBUFFER = 604,        /* F16TEXTUREBUFFER  */
    F16TEXTURE2DMS = 605,          /* F16TEXTURE2DMS  */
    F16TEXTURE2DMSARRAY = 606,     /* F16TEXTURE2DMSARRAY  */
    SUBPASSINPUT = 607,            /* SUBPASSINPUT  */
    SUBPASSINPUTMS = 608,          /* SUBPASSINPUTMS  */
    ISUBPASSINPUT = 609,           /* ISUBPASSINPUT  */
    ISUBPASSINPUTMS = 610,         /* ISUBPASSINPUTMS  */
    USUBPASSINPUT = 611,           /* USUBPASSINPUT  */
    USUBPASSINPUTMS = 612,         /* USUBPASSINPUTMS  */
    F16SUBPASSINPUT = 613,         /* F16SUBPASSINPUT  */
    F16SUBPASSINPUTMS = 614,       /* F16SUBPASSINPUTMS  */
    SPIRV_INSTRUCTION = 615,       /* SPIRV_INSTRUCTION  */
    SPIRV_EXECUTION_MODE = 616,    /* SPIRV_EXECUTION_MODE  */
    SPIRV_EXECUTION_MODE_ID = 617, /* SPIRV_EXECUTION_MODE_ID  */
    SPIRV_DECORATE = 618,          /* SPIRV_DECORATE  */
    SPIRV_DECORATE_ID = 619,       /* SPIRV_DECORATE_ID  */
    SPIRV_DECORATE_STRING = 620,   /* SPIRV_DECORATE_STRING  */
    SPIRV_TYPE = 621,              /* SPIRV_TYPE  */
    SPIRV_STORAGE_CLASS = 622,     /* SPIRV_STORAGE_CLASS  */
    SPIRV_BY_REFERENCE = 623,      /* SPIRV_BY_REFERENCE  */
    SPIRV_LITERAL = 624,           /* SPIRV_LITERAL  */
    ATTACHMENTEXT = 625,           /* ATTACHMENTEXT  */
    IATTACHMENTEXT = 626,          /* IATTACHMENTEXT  */
    UATTACHMENTEXT = 627,          /* UATTACHMENTEXT  */
    LEFT_OP = 628,                 /* LEFT_OP  */
    RIGHT_OP = 629,                /* RIGHT_OP  */
    INC_OP = 630,                  /* INC_OP  */
    DEC_OP = 631,                  /* DEC_OP  */
    LE_OP = 632,                   /* LE_OP  */
    GE_OP = 633,                   /* GE_OP  */
    EQ_OP = 634,                   /* EQ_OP  */
    NE_OP = 635,                   /* NE_OP  */
    AND_OP = 636,                  /* AND_OP  */
    OR_OP = 637,                   /* OR_OP  */
    XOR_OP = 638,                  /* XOR_OP  */
    MUL_ASSIGN = 639,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 640,              /* DIV_ASSIGN  */
    ADD_ASSIGN = 641,              /* ADD_ASSIGN  */
    MOD_ASSIGN = 642,              /* MOD_ASSIGN  */
    LEFT_ASSIGN = 643,             /* LEFT_ASSIGN  */
    RIGHT_ASSIGN = 644,            /* RIGHT_ASSIGN  */
    AND_ASSIGN = 645,              /* AND_ASSIGN  */
    XOR_ASSIGN = 646,              /* XOR_ASSIGN  */
    OR_ASSIGN = 647,               /* OR_ASSIGN  */
    SUB_ASSIGN = 648,              /* SUB_ASSIGN  */
    STRING_LITERAL = 649,          /* STRING_LITERAL  */
    LEFT_PAREN = 650,              /* LEFT_PAREN  */
    RIGHT_PAREN = 651,             /* RIGHT_PAREN  */
    LEFT_BRACKET = 652,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 653,           /* RIGHT_BRACKET  */
    LEFT_BRACE = 654,              /* LEFT_BRACE  */
    RIGHT_BRACE = 655,             /* RIGHT_BRACE  */
    DOT = 656,                     /* DOT  */
    COMMA = 657,                   /* COMMA  */
    COLON = 658,                   /* COLON  */
    EQUAL = 659,                   /* EQUAL  */
    SEMICOLON = 660,               /* SEMICOLON  */
    BANG = 661,                    /* BANG  */
    DASH = 662,                    /* DASH  */
    TILDE = 663,                   /* TILDE  */
    PLUS = 664,                    /* PLUS  */
    STAR = 665,                    /* STAR  */
    SLASH = 666,                   /* SLASH  */
    PERCENT = 667,                 /* PERCENT  */
    LEFT_ANGLE = 668,              /* LEFT_ANGLE  */
    RIGHT_ANGLE = 669,             /* RIGHT_ANGLE  */
    VERTICAL_BAR = 670,            /* VERTICAL_BAR  */
    CARET = 671,                   /* CARET  */
    AMPERSAND = 672,               /* AMPERSAND  */
    QUESTION = 673,                /* QUESTION  */
    INVARIANT = 674,               /* INVARIANT  */
    HIGH_PRECISION = 675,          /* HIGH_PRECISION  */
    MEDIUM_PRECISION = 676,        /* MEDIUM_PRECISION  */
    LOW_PRECISION = 677,           /* LOW_PRECISION  */
    PRECISION = 678,               /* PRECISION  */
    PACKED = 679,                  /* PACKED  */
    RESOURCE = 680,                /* RESOURCE  */
    SUPERP = 681,                  /* SUPERP  */
    INLINE = 682,                  /* INLINE  */
    NOINLINE = 683,                /* NOINLINE  */
    FLOATCONSTANT = 684,           /* FLOATCONSTANT  */
    INTCONSTANT = 685,             /* INTCONSTANT  */
    UINTCONSTANT = 686,            /* UINTCONSTANT  */
    BOOLCONSTANT = 687,            /* BOOLCONSTANT  */
    IDENTIFIER = 688,              /* IDENTIFIER  */
    TYPE_NAME = 689,               /* TYPE_NAME  */
    CENTROID = 690,                /* CENTROID  */
    IN = 691,                      /* IN  */
    OUT = 692,                     /* OUT  */
    INOUT = 693,                   /* INOUT  */
    STRUCT = 694,                  /* STRUCT  */
    VOID = 695,                    /* VOID  */
    WHILE = 696,                   /* WHILE  */
    BREAK = 697,                   /* BREAK  */
    CONTINUE = 698,                /* CONTINUE  */
    DO = 699,                      /* DO  */
    ELSE = 700,                    /* ELSE  */
    FOR = 701,                     /* FOR  */
    IF = 702,                      /* IF  */
    DISCARD = 703,                 /* DISCARD  */
    RETURN = 704,                  /* RETURN  */
    SWITCH = 705,                  /* SWITCH  */
    CASE = 706,                    /* CASE  */
    DEFAULT = 707,                 /* DEFAULT  */
    TERMINATE_INVOCATION = 708,    /* TERMINATE_INVOCATION  */
    TERMINATE_RAY = 709,           /* TERMINATE_RAY  */
    IGNORE_INTERSECTION = 710,     /* IGNORE_INTERSECTION  */
    UNIFORM = 711,                 /* UNIFORM  */
    SHARED = 712,                  /* SHARED  */
    BUFFER = 713,                  /* BUFFER  */
    TILEIMAGEEXT = 714,            /* TILEIMAGEEXT  */
    FLAT = 715,                    /* FLAT  */
    SMOOTH = 716,                  /* SMOOTH  */
    LAYOUT = 717,                  /* LAYOUT  */
    DOUBLECONSTANT = 718,          /* DOUBLECONSTANT  */
    INT16CONSTANT = 719,           /* INT16CONSTANT  */
    UINT16CONSTANT = 720,          /* UINT16CONSTANT  */
    FLOAT16CONSTANT = 721,         /* FLOAT16CONSTANT  */
    INT32CONSTANT = 722,           /* INT32CONSTANT  */
    UINT32CONSTANT = 723,          /* UINT32CONSTANT  */
    FLOATE2M1CONSTANT = 724,       /* FLOATE2M1CONSTANT  */
    FLOATE3M2CONSTANT = 725,       /* FLOATE3M2CONSTANT  */
    FLOATE2M3CONSTANT = 726,       /* FLOATE2M3CONSTANT  */
    FLOATUE8M0CONSTANT = 727,      /* FLOATUE8M0CONSTANT  */
    FLOATMXINT8CONSTANT = 728,     /* FLOATMXINT8CONSTANT  */
    INT64CONSTANT = 729,           /* INT64CONSTANT  */
    UINT64CONSTANT = 730,          /* UINT64CONSTANT  */
    SUBROUTINE = 731,              /* SUBROUTINE  */
    DEMOTE = 732,                  /* DEMOTE  */
    FUNCTION = 733,                /* FUNCTION  */
    PAYLOADNV = 734,               /* PAYLOADNV  */
    PAYLOADINNV = 735,             /* PAYLOADINNV  */
    HITATTRNV = 736,               /* HITATTRNV  */
    CALLDATANV = 737,              /* CALLDATANV  */
    CALLDATAINNV = 738,            /* CALLDATAINNV  */
    PAYLOADEXT = 739,              /* PAYLOADEXT  */
    PAYLOADINEXT = 740,            /* PAYLOADINEXT  */
    HITATTREXT = 741,              /* HITATTREXT  */
    CALLDATAEXT = 742,             /* CALLDATAEXT  */
    CALLDATAINEXT = 743,           /* CALLDATAINEXT  */
    PATCH = 744,                   /* PATCH  */
    SAMPLE = 745,                  /* SAMPLE  */
    NONUNIFORM = 746,              /* NONUNIFORM  */
    RESOURCEHEAP = 747,            /* RESOURCEHEAP  */
    SAMPLERHEAP = 748,             /* SAMPLERHEAP  */
    COHERENT = 749,                /* COHERENT  */
    VOLATILE = 750,                /* VOLATILE  */
    RESTRICT = 751,                /* RESTRICT  */
    READONLY = 752,                /* READONLY  */
    WRITEONLY = 753,               /* WRITEONLY  */
    NONTEMPORAL = 754,             /* NONTEMPORAL  */
    DEVICECOHERENT = 755,          /* DEVICECOHERENT  */
    QUEUEFAMILYCOHERENT = 756,     /* QUEUEFAMILYCOHERENT  */
    WORKGROUPCOHERENT = 757,       /* WORKGROUPCOHERENT  */
    SUBGROUPCOHERENT = 758,        /* SUBGROUPCOHERENT  */
    NONPRIVATE = 759,              /* NONPRIVATE  */
    SHADERCALLCOHERENT = 760,      /* SHADERCALLCOHERENT  */
    NOPERSPECTIVE = 761,           /* NOPERSPECTIVE  */
    EXPLICITINTERPAMD = 762,       /* EXPLICITINTERPAMD  */
    PERVERTEXEXT = 763,            /* PERVERTEXEXT  */
    PERVERTEXNV = 764,             /* PERVERTEXNV  */
    PERPRIMITIVENV = 765,          /* PERPRIMITIVENV  */
    PERVIEWNV = 766,               /* PERVIEWNV  */
    PERTASKNV = 767,               /* PERTASKNV  */
    PERPRIMITIVEEXT = 768,         /* PERPRIMITIVEEXT  */
    TASKPAYLOADWORKGROUPEXT = 769, /* TASKPAYLOADWORKGROUPEXT  */
    PRECISE = 770                  /* PRECISE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 72 "MachineIndependent/glslang.y"

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
            glslang::TSpirvRequirement* spirvReq;
            glslang::TSpirvInstruction* spirvInst;
            glslang::TSpirvTypeParameters* spirvTypeParams;
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
        glslang::TTypeParameters* typeParameters;
        glslang::TType* deducedType;
    } interm;

#line 619 "MachineIndependent/glslang_tab.cpp.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (glslang::TParseContext* pParseContext);


#endif /* !YY_YY_MACHINEINDEPENDENT_GLSLANG_TAB_CPP_H_INCLUDED  */
