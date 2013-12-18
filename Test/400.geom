#version 400 core

void main()
{
    EmitStreamVertex(1);
    EndStreamPrimitive(0);
    EmitVertex();
    EndPrimitive();
    int id = gl_InvocationID;
}

layout(invocations = 4) in outbn { int a; } bn[]; // ERROR, not on a block
layout(max_vertices = 127) out;
layout(invocations = 4) in;

#extension GL_ARB_separate_shader_objects : enable

in gl_PerVertex {      // testing input arrays with a block redeclaration, see 420.geom for without
    vec4 gl_Position;
    layout(std140, location = 3) patch float gl_PointSize; // ERRORs...
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

layout(location = 4) in vec4 cva[3];
layout(location = 5) in vec4 cvb[3];
layout(location = 2) in mat3 cmc[3];  // ERROR, collision

patch in vec4 patchIn[];            // ERROR
patch out vec4 patchOut;            // ERROR

in float scalar;  // ERROR, no array

layout(max_vertices = 127, invocations = 4) out;      // ERROR
layout(invocations = 4, max_vertices = 127) in;       // ERROR
layout(max_vertices = 127, invocations = 4) uniform;  // 2 ERRORs

in inblockscalar {
    int a;
} inbls;  // ERROR, not an array

in inblocka {
    int a;
} inbla[17];  // ERROR, wrong array size
