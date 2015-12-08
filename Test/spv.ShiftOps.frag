#version 450

uniform int   i1;
uniform ivec3 i3;

uniform uint  u1;
uniform uvec3 u3;

out ivec3 color;

void main()
{
    color = i3 << 1;
    color = i3 >> 2u;
    color = i3 << ivec3(2);
    color = i3 >> uvec3(5);

    color <<= i1;
    color >>= u1;
    color <<= i3;
    color >>= u3;
}
