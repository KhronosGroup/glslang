#version 120

in vec4 i;
out vec4 o;

attribute vec2 attv2;
attribute vec4 attv4;
uniform sampler2D s2D;
invariant varying vec2 centTexCoord;
invariant gl_Position;
centroid gl_Position;
centroid centroid foo;
invariant gl_Position, gl_PointSize;

void main()
{
    centTexCoord = attv2; 
    gl_Position = attv4;

    vec3[12] a;
    vec4[a.length()] b;
    gl_Position = b[b.length()-1];

    float f[];
    int a = f.length();

    gl_PointSize = 3.8;
}

uniform float initted = 3.4;

const float concall = sin(0.3);
