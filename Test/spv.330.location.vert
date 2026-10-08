#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(location = 0) out vec3 color;
layout(location = 1) out Block { vec4 a; vec2 b; } blk;

void main()
{
    gl_Position = vec4(position, 1.0);
    color = normal;
    blk.a = vec4(normal, 0.0);
    blk.b = position.xy;
}
