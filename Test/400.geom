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
