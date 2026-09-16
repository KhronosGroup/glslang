#version 320 es
#extension all : warn

void main()
{
    gl_Position = vec4(1.0);
    gl_ClipDistance[0] = 0.5;
    gl_CullDistance[0] = 0.25;
}
