#version 140
#extension GL_ARB_texture_multisample : enable

out float result;

uniform sampler2DMS data;
uniform sampler2DMSArray data1;
void main()
{
result = texelFetch(data, ivec2(0), 3).r;
ivec2 temp = textureSize(data);
result = texelFetch(data1, ivec3(0), 3).r;
ivec3 temp1 = textureSize(data1);
}
