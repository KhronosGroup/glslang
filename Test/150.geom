#version 150 core

in fromVertex {
    vec3 color;
} fromV;

out toFragment {
    vec3 color;
} toF;

out fromVertex {  // okay to reuse a block name for another block name
    vec3 color;
};

out fooB {
    vec2 color;
} fromVertex;     // ERROR, cannot reuse block name as block instance

int fromVertex;   // ERROR, cannot reuse a block name for something else

out fooC {
    vec2 color;
} fooC;           // ERROR, cannot have same name for block and instance name

void main()
{
    EmitVertex();
    EndPrimitive();
    EmitStreamVertex(1);    // ERROR
    EndStreamPrimitive(0);  // ERROR

    color = fromV.color;
    gl_ClipDistance[3] = gl_in[1].gl_ClipDistance[2];
    gl_Position = gl_in[0].gl_Position;
    gl_PointSize = gl_in[3].gl_PointSize;
    gl_PrimitiveID = gl_PrimitiveIDIn;
    gl_Layer = 2;
}
