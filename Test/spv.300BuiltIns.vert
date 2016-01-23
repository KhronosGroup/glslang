#version 310 es

in mediump float ps;

invariant gl_Position;

void main()
{
    mediump int i = (4 * gl_VertexID - 10);
    mediump int j = (4 * gl_VertexID - 10);

    gl_Position = vec4(ps);
    gl_Position *= float(i);

    gl_PointSize = ps; 
    gl_PointSize *= float(j);
}
