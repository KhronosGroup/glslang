#version 450
#extension GL_EXT_shader_explicit_arithmetic_types_float16 : require

// Each buffer below captures a type through an array and states a stride that
// is illegal for that type's width. All four must be diagnosed.

// 32-bit through a flat array: stride must be a multiple of 4.
layout(xfb_buffer = 0, xfb_stride = 6) out;
layout(location = 0, xfb_buffer = 0, xfb_offset = 0) out float arr[1];

// 32-bit through a nested array: same rule, one more level of recursion.
layout(xfb_buffer = 1, xfb_stride = 18) out;
layout(location = 1, xfb_buffer = 1, xfb_offset = 0) out float nested[2][2];

// 64-bit through an array: stride must be a multiple of 8.
layout(xfb_buffer = 2, xfb_stride = 12) out;
layout(location = 5, xfb_buffer = 2, xfb_offset = 0) out double darr[1];

// 16-bit through an array: stride must be a multiple of 2.
layout(xfb_buffer = 3, xfb_stride = 3) out;
layout(location = 7, xfb_buffer = 3, xfb_offset = 0) out float16_t harr[1];

void main()
{
    arr[0] = 1.0;
    nested[0][0] = 2.0;
    darr[0] = 3.0LF;
    harr[0] = float16_t(4.0);
}
