#version 300 es

struct S {
    vec4 u;
    uvec4 v;
    isampler3D sampler;
    vec3 w;
    struct T1 {           // ERROR
        int a;
    } t;
};

uniform S s;

uniform fooBlock {
    uvec4 bv;
    mat2 bm2;
    isampler2D sampler;   // ERROR
    struct T2 {           // ERROR
        int a;
    } t;
    S fbs;
};

uniform barBlock {
    uvec4 nbv;
    int ni;
} inst;

uniform barBlockArray {
    uvec4 nbv;
    int ni;
} insts[4];

void main()
{
    texture(s.sampler, vec3(inst.ni, bv.y, insts[2].nbv.z));
    insts[s.v.x];  // ERROR
}
