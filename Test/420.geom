#version 150 core

// testing input arrays without a gl_in[] block redeclaration, see 400.geom for with

int i;

void foo()
{
    gl_in.length();  // ERROR
    gl_in[1].gl_Position;
    gl_in[i].gl_Position;  // ERROR
}

layout(triangles) in;

in vec4 color3[3];

void foo3()
{
    gl_in.length();
    gl_in[i].gl_Position;
    color3.length();
}
