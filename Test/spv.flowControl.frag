#version 140

uniform float d;
uniform vec4 bigColor, smallColor;
uniform vec4 otherColor;

in float c;
in vec4 BaseColor;

void main()
{
    vec4 color = BaseColor;
    vec4 color2;

    color2 = otherColor;

    if (c > d)
        color += bigColor;
    else
        color += smallColor;

    gl_FragColor = color * color2;
}
