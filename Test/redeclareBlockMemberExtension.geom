#version 450

layout(points) in;
layout(points, max_vertices = 1) out;

// Dropping gl_PointSize must not move gl_SecondaryPositionNV onto its
// extension list: GL_NV_stereo_view_rendering is still required below.
in gl_PerVertex {
    vec4 gl_Position;
    vec4 gl_SecondaryPositionNV;
} gl_in[];

void main()
{
    gl_Position = gl_in[0].gl_Position + gl_in[0].gl_SecondaryPositionNV;  // ERROR, requires GL_NV_stereo_view_rendering
    EmitVertex();
}
