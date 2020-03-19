#version 430
layout (std140) uniform Block
{
	mat4 uProj;
} uD;

out Vertex
{
	vec4 v1;
} oV;

layout (std140) uniform ColorBlock
{
	vec4 color1;
} uC;

vec4 getWorld();
vec4 getColor2();

out vec4 oColor;

void
main()
{
	oColor = uC.color1 * getColor2();
	oV.v1 = uC.color1;

	gl_Position = uD.uProj * getWorld();
}
