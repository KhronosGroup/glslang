#version 300 es

uniform mat4x3 m43;
uniform mat3x3 m33;
uniform mat4x4 m44;

in vec3 v3;
in vec2 v2;

in vec4 bad[10];  // ERROR

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

#ifdef GL_ES
#error GL_ES is set
#else
#error GL_ES is not set
#endif
}
