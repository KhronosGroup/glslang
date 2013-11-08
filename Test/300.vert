#version 300 es

uniform mat4x3 m43;
uniform mat3x3 m33;
uniform mat4x4 m44;

in vec3 v3;
varying vec2 v2;               // ERROR, varying reserved
in vec4 bad[10];               // ERROR, no arrayed inputs
highp in vec4 badorder;        // ERROR, incorrect qualifier order
out invariant vec4 badorder2;  // ERROR, incorrect qualifier order
in centroid vec4 badorder4;    // ERROR, incorrect qualifier order
out flat vec4 badorder3;       // ERROR, incorrect qualifier order
void bar(in const float a);    // ERROR, incorrect qualifier order
void bar2(highp in float b);   // ERROR, incorrect qualifier order
smooth flat out vec4 rep;      // ERROR, replicating interpolation qualification
centroid sample out vec4 rep2; // ERROR, replicating auxiliary qualification
in uniform vec4 rep3;          // ERROR, replicating storage qualification

struct S {
    vec3 c;
    float f;
};

out S s;

void main()
{
    int id = gl_VertexID + gl_InstanceID;

    int c0 = gl_MaxVertexAttribs;
    int c1 = gl_MaxVertexUniformVectors;
    int c2 = gl_MaxVertexOutputVectors;
    int c3 = gl_MaxFragmentInputVectors;
    int c4 = gl_MaxVertexTextureImageUnits;
    int c5 = gl_MaxCombinedTextureImageUnits;
    int c6 = gl_MaxTextureImageUnits;
    int c7 = gl_MaxFragmentUniformVectors;
    int c8 = gl_MaxDrawBuffers;
    int c9 = gl_MinProgramTexelOffset;
    int c10 = gl_MaxProgramTexelOffset;

    mat3x4 tm = transpose(m43);
    highp float dm = determinant(m44);
    mat3x3 im = inverse(m33);

    mat3x2 op = outerProduct(v2, v3);

    gl_Position = m44[2];
    gl_PointSize = v2.y;

     s.c = v3;
     s.f = dm;

#ifdef GL_ES
#error GL_ES is set
#else
#error GL_ES is not set
#endif
}

float badsize[];    // ERROR
float[] badsize2;   // ERROR
uniform ub {
    int a[];        // ERROR
} ubInst[];         // ERROR
void foo(int a[]);  // ERROR
float okayA[] = float[](3.0, 4.0);  // Okay

out vec3 newV;
void newVFun()
{
    newV = v3;
}

invariant newV;  // ERROR, variable already used
in vec4 invIn;
invariant invIn; // ERROR, in v300
out S s2;
invariant s2;
invariant out S s3;
flat out int;
