#version 140

uniform vec4 bigColor;
in vec4 BaseColor;
uniform float d;

void main()
{
    vec4 color = BaseColor;

    do {
        color += bigColor;
    } while (color.x < d);

    gl_FragColor = color;
}
