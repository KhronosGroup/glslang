#version 450

// Both buffers capture 32-bit floats, but each reaches them through an array.
// The spec requires the stride of a buffer holding 32-bit components to be a
// multiple of 4, so both of these are errors. Before the fix the array hid the
// 32-bit-ness of its elements and neither error was reported.
layout(xfb_buffer = 0, xfb_stride = 6) out;
layout(location = 0, xfb_buffer = 0, xfb_offset = 0) out float arr[1];

layout(xfb_buffer = 1, xfb_stride = 18) out;
layout(location = 1, xfb_buffer = 1, xfb_offset = 0) out float nested[2][2];

void main()
{
    arr[0] = 1.0;
    nested[0][0] = 2.0;
}
