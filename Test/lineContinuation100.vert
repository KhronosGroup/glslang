#version 100

// non-line continuation comment \
#error good error



float f\
oo;  // same as 'float foo;'

#error e2

#define MAIN void main() \
   {                     \
gl_Position = vec4(foo); \
} 

#error e3

MAIN

vec4 foo2(vec4 a)
{                                
  vec4 b = a;       \
  return b;                   
}

// aoeuntheo unatehutna \ antaehnathe 
// anteonuth $ natohe " '
// anteonuth     natohe
/*@*/
/* *@/*/
//@
