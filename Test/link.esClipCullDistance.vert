#version 320 es

out gl_PerVertex {
    highp vec4 gl_Position;
    highp float gl_PointSize;
};

void main()
{
    gl_Position = vec4(1.0);
    gl_PointSize = 1.0;
}
