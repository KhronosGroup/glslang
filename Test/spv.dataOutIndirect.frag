#version 140 

in vec4 Color;

uniform int i;

void main()
{
    gl_FragData[i] = Color;
}
