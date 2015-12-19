#version 450

// should get 3 SPV types: no layout, 140, and 430
struct S
{
	highp uvec3 a;
	mediump mat2 b[4];
	lowp uint c;
};

layout(set = 0, binding = 0, std140) uniform Block140
{
	mediump int u;
	S s[2][3];
	mediump vec2 v;
} inst140;

layout(set = 0, binding = 1, std430) buffer Block430
{
	mediump int u;
	S s[2][3];
	mediump vec2 v;
} inst430;

S s;

void main()
{
    s.c = inst140.u;
    gl_Position = vec4(s.c);
}
