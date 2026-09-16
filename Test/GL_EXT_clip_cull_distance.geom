#version 320 es
#extension GL_EXT_clip_cull_distance : enable

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

// gl_PointSize is dropped on purpose: the remaining members must keep their own
// extension requirements after the redeclaration.
in gl_PerVertex {
    highp vec4 gl_Position;
    highp float gl_ClipDistance[4];
    highp float gl_CullDistance[2];
} gl_in[];

out gl_PerVertex {
    highp vec4 gl_Position;
    highp float gl_ClipDistance[4];
    highp float gl_CullDistance[2];
};

void main()
{
    for (int i = 0; i < 3; ++i) {
        gl_Position = gl_in[i].gl_Position;
        gl_ClipDistance[0] = gl_in[i].gl_ClipDistance[0];
        gl_CullDistance[1] = gl_in[i].gl_CullDistance[1];
        EmitVertex();
    }
    EndPrimitive();
}
