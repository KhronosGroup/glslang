#version 450 core
#extension GL_EXT_shader_explicit_arithmetic_types_float16 : require

// A float16_t constant has to be rounded to half precision when it is stored,
// not only when it is finally emitted.  Otherwise it keeps bits the declared
// type cannot hold and those bits take part in later constant folding.

const float16_t c0 = 1.000000001hf;          // rounds to exactly 1.0
const float     c1 = 1000000*(c0 - 1.0f);    // so this is 0.0, not 0.001

const float16_t pi    = 3.14159265358979hf;  // 3.140625
const float16_t tenth = 0.1hf;               // 0.0999755859375

// A double literal of the same value keeps full precision.
const double    lfpi  = 3.14159265358979LF;  // unchanged

void main()
{
}
