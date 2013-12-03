#version 300 es

// this file cont\
ains no errors other than the #error which are there to see if line numbering for errors is correct

#error e1

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
