#version 460

float f;
float a1;

float foo();

void main()
{
    f = 10;
    float g = foo();
    f += g;
    f += gl_FragCoord.y;
}