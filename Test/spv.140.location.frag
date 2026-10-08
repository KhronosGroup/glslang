#version 140

layout(location = 0) in vec4 color;
layout(location = 0) out vec4 fragColor;

void main()
{
    fragColor = color;
}
