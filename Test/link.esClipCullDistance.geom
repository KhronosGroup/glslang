#version 320 es

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

void main()
{
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
}
