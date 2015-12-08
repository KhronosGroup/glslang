#version 450

const bool condition = false;

uniform vec4 color;

out vec4 fragColor;

void main()
{
    fragColor = condition ? color : color + vec4(0.5);
}
