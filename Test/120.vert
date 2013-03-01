#version 120

in vec4 i;
out vec4 o;

attribute vec2 attv2;
attribute vec4 attv4;
uniform sampler2D s2D;
invariant varying vec2 centTexCoord;
invariant gl_Position;

centroid centroid foo;

void main()
{
    centTexCoord = attv2; 
    gl_Position = attv4;
}
