#version 460

#extension GL_EXT_spirv_intrinsics : enable
#extension GL_EXT_spirv_intrinsics_variadic : enable

// A trailing variadic tail does not participate in overload resolution: a call
// is resolved on its fixed (leading) parameters using the ordinary rules.

// Distinct leading parameter types are separated by the ordinary conversion
// rules; the tail plays no part.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 10) void pick(int x, ...);
spirv_instruction(set = "Fictional.TestExtInstSet", id = 20) void pick(float x, ...);

// A fixed-arity overload alongside a variadic one of the same name. When the two
// tie on the fixed parameter, the non-variadic is preferred -- whether the call's
// argument matches exactly or through an implicit conversion. The variadic is
// selected only when the call supplies more arguments than the fixed form accepts.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 30) void pickArity(uint x);
spirv_instruction(set = "Fictional.TestExtInstSet", id = 40) void pickArity(uint x, ...);

void main()
{
    int i = 1;
    float f = 1.0;
    pick(i);        // pick(int, ...)   exact int beats int->float
    pick(f);        // pick(float, ...)
    pick(i, i, i);  // pick(int, ...)   trailing arguments ignored by resolution

    uint u = 2u;
    pickArity(u);         // pickArity(uint)        exact match, non-variadic preferred
    pickArity(i);         // pickArity(uint)        int->uint conversion, non-variadic still preferred
    pickArity(u, u);      // pickArity(uint, ...)   only the variadic accepts two arguments
}
