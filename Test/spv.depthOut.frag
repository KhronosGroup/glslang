#version 450

in vec4 Color;
in float Depth;

layout(depth_any) out float gl_FragDepth;

void main()
{
    gl_FragDepth = Depth;
    gl_FragColor = Color;
}
