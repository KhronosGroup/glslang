#version 120

in vec4 i;                // ERROR
out vec4 o;               // ERROR

attribute vec2 attv2;
attribute vec4 attv4;
uniform sampler2D s2D;
invariant varying vec2 centTexCoord;
invariant gl_Position;
centroid gl_Position;     // ERROR
centroid centroid foo;    // ERROR
invariant gl_Position, gl_PointSize;

void main()
{
    centTexCoord = attv2; 
    gl_Position = attv4;

    vec3[12] a;
    vec4[a.length()] b;
    gl_Position = b[b.length()-1];

    float f[];
    int a1 = f.length();  // ERROR
    float f[7];
    int aa = f.length();
    int a2 = f.length;    // ERROR
    int a3 = f.length(a); // ERROR
    int a4 = f.flizbit;   // ERROR
    int a4 = f.flizbit(); // ERROR
    float md[2][4];       // ERROR
    float[2] md2[4];      // ERROR
    float[2][4] md3;      // ERROR
    float md5, md6[2][3]; // ERROR
    float[2] md4, md7[4]; // ERROR
    float md9[2][3] = float[2][3](1, 2, 3, 4, 5, 6);  // ERROR
    float md10, md11[2][3] = float[2][3](1, 2, 3, 4, 5, 6);  // ERROR

    gl_PointSize = 3.8;
}

uniform float initted = 3.4;   // okay

const float concall = sin(0.3);

int[2][3] foo(                 // ERROR
              float[2][3] a,   // ERROR
              float[2] b[3],   // ERROR
              float c[2][3]);  // ERROR
