#version 450

// side test verifies multiple rounds of argument expansion
#define bear SecondExpansion
#define mmmB bear
#define mmmA(a) a
int mmmA(mmmB);                    // mmmB -> bear, and then in mmmA(), bear -> SecondExpansion

// pasting skips the first round of expansion
#define mmcatmmdog PostPasteExpansion
#define mmcat cat
#define mmdog dog
#define mmp(a,b) a## b
int mmp(mmcat, mmdog);             // mmcat/mmdog not expanded, mmcatmmdog -> PostPasteExpansion

// multi-token pre
#define mmtokpastepre(a) a##27
mmtokpastepre(float foo);          // should declare "float foo27;"

// multi-token post
#define mmtokpastepost(a) uni ##a
mmtokpastepost(form float foo155); // should declare "uniform float foo155;"

// non-first argument
#define foo ShouldntExpandToThis
#define semi ;
#define bothpaste(a,b) a##b
float bothpaste(foo, 719);          // should declare "float foo719;"
#define secpaste(a,b) a bar ## b
secpaste(uniform float, foo semi)   // should declare "uniform float barfoo;"

// no args
#define noArg fl##oat
noArg argless;

// bad location
#define bad1 ## float
bad1 dc1;
#define bad2 float ##
bad2 dc2;

// multiple ##
#define multiPaste(a, b, c) a##or##b flo##at foo##c
multiPaste(unif, m, 875);

// too long
#define simplePaste(a,b) a##b
// 1020 + 5 characters
float simplePaste(ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF012345, 12345);

// non-identifiers
int a = simplePaste(11,12);
