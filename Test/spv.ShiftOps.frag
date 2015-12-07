#version 450

uniform int   i1;
uniform uint  u1;

uniform ivec3 i3;
uniform uvec3 u3;

out ivec3 icolor;
out uvec3 ucolor;

void main()
{
    icolor = i3 << u1;
    icolor <<= 4u;

    ucolor = u3 >> i1;
    ucolor >>= 5;
}
