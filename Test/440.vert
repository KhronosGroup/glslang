#version 440

// Note 'location' tests for enhanced layouts are in 330.frag

layout(location = 2, component = 2) in vec2 a; 
layout(location = 2, component = 1) in float b; 

layout(location = 3, component = 2) in vec3 c;      // ERROR: c overflows components 2 and 3

layout(location = 0, component = 3) in float d[4]; 

layout(location = 4, component = 0) in vec3 e[5];
layout(location = 4, component = 3) in float f[5];

layout(location = 9, component = 4) in float g[6];   // ERROR, component too big

layout(location = 4, component = 2) in vec2 h;       // component overlap okay for vertex in

layout(location = 3, component = 2) out vec2 i;
layout(location = 3, component = 0) out vec2 j;

layout(location = 4, component = 2) out vec2 k;
layout(location = 4, component = 2) out vec2 m;      // ERROR, component overlap

layout(location = 2, component = 2) out vec2 n;
layout(location = 2, component = 0) out vec3 p;      // ERROR, component overlap

layout(location = 10, component = 3) out float q[6]; 
layout(location = 10, component = 0) out vec3 r[6];

layout(location = 15, component = 3) out float s;    // ERROR, overlap
layout(location = 10, component = 1) out float t;    // ERROR, overlap

layout(location = 20, component = 2) out float u;
layout(location = 20, component = 0) out float v;
layout(location = 20, component = 3) out float w;
layout(location = 20, component = 1) out vec2 x;     // ERROR, overlap

layout(location = 30, component = 3) out vec2 y;     // ERROR, goes to component 4
layout(location = 31, component = 1) out vec4 z;     // ERROR, goes to component 4

layout(location = 32, component = 1) out mat4 ba;               // ERROR
layout(location = 33, component = 1) out struct S {int a;} Ss;  // ERROR
layout(location = 34, component = 1) out bn { int a;} bb;       // ERROR

layout(component = 1) out float bc;    // ERROR, no location

out blockname {
    layout(location = 40, component = 2) out float u;
    layout(location = 40, component = 0) out float v;
    layout(location = 40, component = 3) out float w;
    layout(location = 40, component = 1) out vec2 x;     // ERROR, overlap

    layout(location = 41, component = 3) out vec2 y;     // ERROR, goes to component 4
    layout(location = 42, component = 1) out vec4 z;     // ERROR, goes to component 4

    layout(location = 42, component = 1) out mat4 ba;    // ERROR
    layout(location = 43, component = 1) out S Ss;       // ERROR
} bd;

layout(location = 1, component = 1) out;                 // ERROR, no global setting

layout(location = 50, component = 3) out int be;
layout(location = 50, component = 0) out vec3 bf;

out bblck1 {
    vec4 bbv;
} bbinst1;

out bblck2 {
    layout(xfb_offset=16) vec4 bbv;
} bbinst2;

layout(xfb_buffer = 3, xfb_stride = 16) out;

out bblck3 {
    layout(xfb_offset=16) vec4 bbv;
} bbinst3;

uniform ubblck3 {
    layout(xfb_offset=16) vec4 bbv;  // ERROR
} ubbinst3;

layout(xfb_buffer=2, xfb_offset=32, xfb_stride=64) out vec4 bg;
layout(              xfb_offset=32, xfb_stride=64) out vec4 bh;

layout(xfb_offset=48) out; // ERROR

layout(xfb_stride=32, xfb_buffer=2, xfb_offset=16) out bblck4 {
    vec4 bbv1;
    vec4 bbv2;
} bbinst4;

out bblck5 {
    layout(xfb_offset=0) vec4 bbv1;
    layout(xfb_stride=32, xfb_buffer=3, xfb_offset=16) vec4 bbv2;
    layout(xfb_buffer=2) vec4 bbv3;                               // ERROR, wrong buffer
} bbinst5;
