#version 400 core

layout(vertices = 4) out; // ERROR
layout(quads, cw) in;
layout(triangles) in;     // ERROR
layout(isolines) in;      // ERROR

layout(cw) in;
layout(ccw) in;           // ERROR

layout(fractional_odd_spacing) in;    
layout(equal_spacing) in;              // ERROR
layout(fractional_even_spacing) in;    // ERROR

layout(point_mode) in;

void main()
{
    barrier(); // ERROR

    int a = gl_MaxTessEvaluationInputComponents +
            gl_MaxTessEvaluationOutputComponents +
            gl_MaxTessEvaluationTextureImageUnits +
            gl_MaxTessEvaluationUniformComponents +
            gl_MaxTessPatchComponents +
            gl_MaxPatchVertices +
            gl_MaxTessGenLevel;

    vec4 p = gl_in[1].gl_Position;
    float ps = gl_in[1].gl_PointSize;
    float cd = gl_in[1].gl_ClipDistance[2];

    int pvi = gl_PatchVerticesIn;
    int pid = gl_PrimitiveID;
    vec3 tc = gl_TessCoord;
    float tlo = gl_TessLevelOuter[3];
    float tli = gl_TessLevelInner[1];

    gl_Position = p;
    gl_PointSize = ps;
    gl_ClipDistance[2] = cd;
}
