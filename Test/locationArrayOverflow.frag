#version 450

// The number of locations a multi-dimensional array consumes is counted by
// multiplying its declared dimensions. Here 65536 * 65536 overflows the 32-bit
// product, so the count must be kept bounded before it feeds signed
// location-range arithmetic. bigArray therefore occupies the whole location
// space and 'other' at location 1 is reported as overlapping.
layout(location = 0) in float bigArray[65536][65536];
layout(location = 1) in float other;

void main()
{
}
