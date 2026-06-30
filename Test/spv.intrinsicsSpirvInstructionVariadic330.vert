#version 330

// Same as spv.intrinsicsSpirvInstructionVariadic / ...Overload, but at a version
// that uses the findFunction120 overload resolver instead of findFunction400, to
// cover the variadic tail on that path. Implicit conversions are limited to those
// valid in GLSL 330 (e.g. int->float, but not int->uint).

#extension GL_EXT_spirv_intrinsics : enable
#extension GL_EXT_spirv_intrinsics_variadic : enable

// Literal tail: each trailing argument is encoded as a literal operand.
spirv_instruction(id = 81) // OpCompositeExtract
float extractComp(vec4 composite, spirv_literal ...);

// Default (by-id) tail: each trailing argument is encoded by <id>.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 1)
void byId(uint base, ...);

// By-reference tail: each trailing argument is passed as a SPIR-V pointer.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 2)
void byRef(spirv_by_reference ...);

// A trailing variadic tail does not participate in overload resolution: a call is
// resolved on its fixed (leading) parameters. An exact match on the fixed
// parameter beats a match through implicit conversion.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 10) void pick(int x, ...);
spirv_instruction(set = "Fictional.TestExtInstSet", id = 20) void pick(float x, ...);

// A fixed-arity overload alongside a variadic one of the same name. When the two
// tie on the fixed parameter, the non-variadic is preferred; the variadic is
// selected only when the call supplies more arguments than the fixed form accepts.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 30) void pickArity(int x);
spirv_instruction(set = "Fictional.TestExtInstSet", id = 40) void pickArity(int x, ...);

// A fixed parameter still receives the ordinary implicit conversion when the
// call also supplies arguments for the variadic tail.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 50) void convertFirst(float x, ...);

// Best-match ranking is still applied to fixed parameters shared by variadic
// overloads. The tail does not participate.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 60) void rank(float x, int y, ...);
spirv_instruction(set = "Fictional.TestExtInstSet", id = 70) void rank(float x, float y, ...);

in vec4 vec4In;
out float floatOut;

void main()
{
    // OpCompositeExtract with literal index 2.
    floatOut = extractComp(vec4In, 2);

    uint base = 1u;
    uint arg = 7u;
    byId(base, arg);  // two trailing arguments, by id
    byId(base);       // zero trailing arguments

    float p = 1.0;
    float q = 2.0;
    byRef(p, q);      // trailing arguments passed by pointer
    byRef(p);         // single trailing argument: no fixed params, one operand

    int i = 1;
    float f = 1.0;
    pick(i);          // pick(int, ...)   exact int beats int->float
    pick(f);          // pick(float, ...)
    pick(i, i, i);    // pick(int, ...)   trailing arguments ignored by resolution

    pickArity(i);     // pickArity(int)        exact match, non-variadic preferred
    pickArity(i, i);  // pickArity(int, ...)   only the variadic accepts two arguments

    convertFirst(i, i);  // fixed argument converted, tail argument left as-is
    rank(i, i, i);       // rank(float, int, ...) wins on the second fixed arg
}
