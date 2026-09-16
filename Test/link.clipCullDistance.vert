#version 440 core

out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[1];
};

void main()
{
    gl_Position = vec4(1.0);
    gl_ClipDistance[0] = 0.5;
}
