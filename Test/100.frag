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
