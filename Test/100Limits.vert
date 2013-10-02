#version 100

int ga, gb;
float f;

uniform sampler2D fsa[3];
uniform float fua[10];
attribute mat3 am3;
attribute vec2 av2;
varying vec4 va[4];

const mat2 m2 = mat2(1.0);
const vec3 v3 = vec3(2.0);

void foo(inout float a) {}

void main()
{
    while (ga < gb) { }

    do { } while (false);
    
    for (     ga = 0;              ;         );
    for ( bool a = false;          ;         );
    for (float a = 0.0; a == sin(f);         );
    for (  int a = 0;       a  < 10;   a *= 2);
    for (  int a = 0;       a <= 20;      ++a)  --a;
    for (float a = 0.0;   a <= 20.0; a += 2.0);
    for (float a = 0.0;   a <= 20.0; a += 2.0) foo(a);

    int ia[9];

    fsa[ga];
    fua[ga];
    am3[ga];
    av2[ga];
    va[ga];
    m2[ga];
    v3[ga];
    ia[ga];

    for (  int a = 3; a >= 0; --a) {
        fsa[a];
        fua[a+2];
        am3[3*a];
        av2[3*a];
        va[a-1];
        m2[a/2];
        v3[a];
        ia[a];
    }

}
