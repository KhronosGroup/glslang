#version 400

#define ON

float sum = 0.0;

void main()
{

#ifdef ON
//yes
sum += 1.0;
#endif

#ifdef OFF
//no
sum += 20.0;
#endif

#if defined(ON)
//yes
sum += 300.0;
#endif

#if defined(OFF)
//no
sum += 4000.0;
#endif

#if !defined(ON)
//no
sum += 50000.0;
#endif

#ifndef OFF
//yes
sum += 600000.0;
#else
//no
sum += 0.6;
#endif

#if defined(ON) && defined(OFF)
//no
sum += 0.7;
#elif !defined(OFF)
//yes
sum += 7000000.0;
#endif

#if defined(ON) && !defined(OFF)
//yes
sum += 80000000.0;
#endif

#if defined(OFF) || defined(ON)
//yes
sum += 900000000.0;
#endif

#if NEVER_DEFINED
//no
sum += 0.04;
#else
sum += 0.05;
#endif

// sum should be 987600301.7
    gl_Position = vec4(sum);
}

#define A 0
#define B 0
#define C 0

#if (A == B) || (A == C)
#error good1
#endif

#if A == B || (A == C)
#error good2
#endif

#if (A == B || (A == C))
#error good3
#endif

#if (AA == BB) || (AA == CC)
#error good4
#endif

#if AA == BB || (AA == CC)
#error good5
#endif

#if ((AA == BB || (AA == CC)))
#error good6
#endif

#if (A == B || (A == C)
#error bad1
#endif

#if A == B || A == C)
#error bad2
#endif

#if (A == B || (A == C)
#error bad3
#endif

#if AA == BB) || (AA == CC)
#error bad4
#endif

#if AA == BB || (AA == CC
#error bad5
#endif

#if ((AA == BB || (AA == CC))))
#error bad6
#endif extra tokens

int linenumber = __LINE__;
int filenumber = __FILE__;
int version = __VERSION__;

#define PI (3.14)
#define TWOPI (2.0 * PI)
float twoPi = TWOPI;

//#define PASTE(a,b) a ## b
//float PASTE(tod, ay) = 17;

"boo" // ERROR
int a = length("aoenatuh");  // ERROR

'int';  // ERROR

// ERROR: all the following are reserved
#define GL_
#define GL_Macro 1
#define __M 
#define M__
#define ABC__DE abc

#if 4
#else extra
#elif
// ERROR elif after else
#endif

#if blah
  #if 0
  #else extra
    #ifdef M
    #else
    #else
    // ERROR else after else
    #endif  extra
  #endif
#endif

#define m1(a,a)  // ERROR
#define m2(a,b)

// okay
#define m3 (a)
#define m3 (a)

// ERROR
#define m4(b)
#define m4 (b)

// ERROR
#define m5 (b)
#define m5(b)

// ERROR
#define m6(a)
#define m6

// ERROR (whitespace)
#define m7 (a)
#define m7 ( a)

#define m80(a,b) is + exactly m3 the same
#define m80(a,b) is + exactly m3 the same

// ERROR
#define m8(a,b) almost + exactly m3 the same
#define m8(a,b) almost + exactly m3 thee same

// ERROR
#define m9(a,b,c) aoe
#define m9(a,d,c) aoe

#define n1 0xf
int n = n1;

#define f1 .08e-2Lf
double f = f1;

#if 1
#else
// ERROR, missing #endif