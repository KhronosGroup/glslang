#version 330 core

layout(location = 0) in vec3 color;
layout(location = 1) in Block { vec4 a; vec2 b; } blk;

layout(location = 0) out vec4 fragColor;

void main()
{
    fragColor = vec4(color, 1.0) + blk.a + vec4(blk.b, 0.0, 0.0);
}
