#version 140

layout(location = 0) in vec4 position;
layout(location = 0) out vec4 color;

void main()
{
    gl_Position = position;
    color = position;
}
