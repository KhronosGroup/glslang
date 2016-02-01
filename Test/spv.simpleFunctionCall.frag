#version 150

uniform vec4 bigColor;
in vec4 BaseColor;
uniform float d;

vec4 foo()
{
    return BaseColor;
}

void main()
{
    gl_FragColor = foo();
}
