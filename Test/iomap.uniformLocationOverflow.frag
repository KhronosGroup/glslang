#version 450

// The number of uniform locations a multi-dimensional array consumes is
// counted by multiplying its declared dimensions. Here 65536 * 65536
// overflows the 32-bit product, so the count must be kept bounded before it
// feeds the location-range overlap check. bigArray therefore occupies the
// remaining location space and 'other' at location 2 is reported as
// overlapping.
layout(location = 1) uniform float bigArray[65536][65536];
layout(location = 2) uniform float other;

layout(location = 0) out vec4 Output;

void main()
{
    Output = vec4(1.0);
}
