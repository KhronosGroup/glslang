#version 450
#extension GL_EXT_shader_explicit_arithmetic_types_float16 : require

// No xfb_stride is stated, so the compiler computes it and emits it as the
// XfbStride decoration. The buffer holds a 32-bit type reached through an
// array, so the stride must round up to a multiple of 4.
//
// arr[0] occupies bytes 0..3, h occupies bytes 4..5, so the natural size is 6
// and the correct emitted stride is 8. Before the fix the array hid the
// 32-bit-ness of its element, the rounding used the 16-bit rule instead, and
// the compiler emitted a stride of 6. That is a valid shader compiled to a
// layout the application reads back wrong, with no diagnostic.
layout(location = 0, xfb_buffer = 0, xfb_offset = 0) out float arr[1];
layout(location = 1, xfb_buffer = 0, xfb_offset = 4) out float16_t h;

void main()
{
    arr[0] = 1.0;
    h = float16_t(2.0);
}
