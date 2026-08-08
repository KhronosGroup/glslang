#version 450 core
#extension GL_EXT_shader_explicit_arithmetic_types_float16 : require

// A float16_t constant has to be rounded to half precision when it is stored,
// not only when it is finally emitted.  Otherwise it keeps bits the declared
// type cannot hold and those bits take part in later constant folding.

const float16_t c0 = 1.000000001hf;          // rounds to exactly 1.0
const float     c1 = 1000000*(c0 - 1.0f);    // so this is 0.0, not 0.001

const float16_t pi    = 3.14159265358979hf;  // 3.140625
const float16_t tenth = 0.1hf;               // 0.0999755859375

// Values the compiler computes have to be rounded too, not just literals.
const float16_t third = 1.0hf/3.0hf;         // 0.333251953125, not 0.33333333
const float16_t sum   = 0.1hf + 0.2hf;       // rounded at each step
const float16_t root  = sqrt(2.0hf);         // 1.4140625

// A double literal of the same value keeps full precision.
const double    lfpi  = 3.14159265358979LF;  // unchanged

// Now that a stored constant carries its declared type, every fold has to set
// that type.  A fold that leaves the default behind produces a value that
// compares unequal to a literal of the same number, so each of these is true.
const float bitsToFloat = intBitsToFloat(1065353216);  // 1.0
const bool  okBits      = bitsToFloat == 1.0;
const float clamped     = clamp(2.0, 0.0, 1.0);        // 1.0
const bool  okClamp     = clamped == 1.0;
const float lerped      = mix(0.0, 2.0, 0.5);          // 1.0
const bool  okMix       = lerped == 1.0;
const float picked      = mix(3.0, 7.0, true);         // 7.0
const bool  okPick      = picked == 7.0;

void main()
{
}
