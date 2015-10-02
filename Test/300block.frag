#version 300 es

precision mediump float;

struct S {
    vec4 u;
    uvec4 v;
    lowp isampler3D samp3d;  //?? parser bug having non-active keyword as struct member
    vec3 w;
    struct T1 {           // ERROR
        int a;
    } t;
};

uniform S s;

uniform fooBlock {
    uvec4 bv;
    uniform mat2 bm2;
    lowp isampler2D samp2D;    // ERROR
    struct T2 {                // ERROR
        int a;
    } t;
    S fbs;                     // ERROR, contains a sampler
};

uniform barBlock {
    uvec4 nbv;
    int ni;
} inst;

uniform barBlockArray {
    uvec4 nbv;
    int ni;
} insts[4];

uniform unreferenced {
    float f;
    uint u;
};

void main()
{
    texture(s.samp3d, vec3(inst.ni, bv.y, insts[2].nbv.z));
    insts[s.v.x];         // ERROR
    fooBlock;             // ERROR
    mat4(s);              // ERROR
    int insts;
    float barBlock;
    mat4(barBlock);
    mat4(unreferenced);   // ERROR, bad type
    ++s;                  // ERROR
    inst - 1;             // ERROR
    ++barBlock;
    2 * barBlockArray;    // ERROR
}

int fooBlock;             // ERROR, redef.
