#version 330

in vec4 inVar;
out vec4 outVar;

const int constInt = 3;

uniform int uniformInt;

void main()
{
    const int a1 = 2;          // okay
    const int a2 = constInt;   // okay
    const int a3 = uniformInt; // error

    vec4 c[constInt];              // okay
    vec4 d[uniformInt];            // error
    vec4 e[constInt + uniformInt]; // error
    vec4 f[uniformInt + constInt]; // error

    vec4 g[int(sin(0.3)) + 1];     // okay
}
