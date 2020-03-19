#version 430
layout (std140) uniform Block
{
	mat4 uProj;
	mat4 uWorld;
};

out Vertex
{
	vec4 v1;
	vec4 v2;
};

layout (std140) uniform ColorBlock
{
	vec4 color1;
	vec4 color2;
};

vec4 getWorld();
vec4 getColor2();

out vec4 oColor;

void
main()
{
	oColor = color1 * getColor2();
	v1 = color1;

	gl_Position = uProj * getWorld();
}
