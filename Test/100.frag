// okay
#version 100
int a[3] = { 2, 3, 4, };  // ERROR

int uint;

attribute vec4 v[3];     // ERROR

float f = 2;             // ERROR

uniform block {          // ERROR
    int x;
};

void foo(float);

void main()
{
    foo(3);              // ERROR
    int s = 1 << 4;      // ERROR
    s = 16 >> 2;         // ERROR
    if (a == a);         // ERROR
    int b, c;
    b = c & 4;           // ERROR
    b = c % 4;           // ERROR
    b = c | 4;           // ERROR
    b >>= 2;             // ERROR
    b <<= 2;             // ERROR
    b %= 3;              // ERROR

    struct S {
        float f;
        float a[10];
    } s1, s2;

    s1 = s2;             // ERROR
    if (s1 == s2);       // ERROR
    if (s1 != s2);       // ERROR

    switch(b) {          // ERROR
    }
}

invariant gl_FragColor;
float fa[];              // ERROR
float f13;
invariant f13;           // ERROR
struct S { int a; };
invariant S;
invariant float fi;      // ERROR
varying vec4 av;
invariant av;            // okay in v100

void foo10()
{
    invariant f;         // ERROR
    invariant float f2;  // ERROR
    float f3;
    invariant f3;        // ERROR
}

uniform vec2 uv2;
invariant uv2;              // ERROR
invariant uniform vec3 uv3; // ERROR

sampler2D glob2D;           // ERROR
void f11(sampler2D p2d)
{
    sampler2D v2D;          // ERROR
}
varying sampler2D vary2D;   // ERROR

struct sp {
    highp float f;
    in float g;             // ERROR
    uniform float h;        // ERROR
    invariant float i;      // ERROR
};
