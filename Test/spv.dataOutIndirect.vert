#version 130

attribute vec4 color;
varying vec4 colorOut[6];

void main()
{
    for (int i = 1; i < 5; ++i)
        colorOut[i] = color;

    gl_Position = colorOut[2];
}
