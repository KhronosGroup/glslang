#version 150 core

void main()
{
    EmitVertex();
    EndPrimitive();
    EmitStreamVertex(1);    // ERROR
    EndStreamPrimitive(0);  // ERROR
}
