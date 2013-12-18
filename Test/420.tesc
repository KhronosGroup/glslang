#version 400 core

#extension GL_ARB_separate_shader_objects : enable

layout(vertices = 4) out;

out gl_PerVertex {
    vec4 gl_Position;
} gl_out[3];                 // ERROR, wrong size

out int a[gl_out.length()];
out int outb[5];             // ERROR, wrong size
out int outc[];

void main()
{
    vec4 p = gl_in[1].gl_Position;
    float ps = gl_in[1].gl_PointSize;
    float cd = gl_in[1].gl_ClipDistance[2];

    int pvi = gl_PatchVerticesIn;
    int pid = gl_PrimitiveID;
    int iid = gl_InvocationID;

    gl_out[1].gl_Position = p;
    gl_out[1].gl_PointSize = ps;        // ERROR
}

out float outf;  // ERROR, no array
