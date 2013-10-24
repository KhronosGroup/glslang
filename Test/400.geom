#version 400 core

void main()
{
    EmitStreamVertex(1);
    EndStreamPrimitive(0);
    EmitVertex();
    EndPrimitive();

    int id = gl_InvocationID;
}

layout(invocations = 3) out outbn { int a; }; // ERROR, not on a block
layout(max_vertices = 127, invocations = 4) out;

#extension GL_ARB_separate_shader_objects : enable

in gl_PerVertex {      // testing input arrays with a block redeclaration, see 420.geom for without
    vec4 gl_Position;
} gl_in[];

void foo()
{
    gl_in.length();  // ERROR
    gl_in[1].gl_Position;
}

in vec4 color[];
in vec4 color2[];
in vec4 colorS[3];
in vec4 colorBad[4];

void foo2()
{
    color.length(); // ERROR
    colorS.length();
}

layout(triangles) in;  // give ERROR just for colorBad

in vec4 color[3];
in vec4 color2[3];
in vec4 colorbad2[2];  // ERROR

void foo3()
{
    gl_in.length();
    color.length();
    color2.length();
    colorS.length();
}
