#version 460

#extension GL_EXT_spirv_intrinsics : enable
#extension GL_EXT_spirv_intrinsics_variadic : enable
#extension GL_EXT_spirv_intrinsics_string : enable

// ERROR: 'spirv_string' is only valid as a parameter of a 'spirv_instruction'
// function, never of an ordinary function.
void userFunc(spirv_string s);

// ERROR: 'spirv_string' cannot be a function return type.
spirv_instruction(id = 1) spirv_string makeString();

// ERROR: a 'spirv_string' parameter may only be unqualified or 'in'.
spirv_instruction(id = 2) void outParam(out spirv_string s);

// ERROR: there is no array of 'spirv_string'.
spirv_instruction(id = 3) void arrParam(spirv_string s[2]);

// ERROR: 'spirv_by_reference' is not a permitted qualifier on 'spirv_string'.
spirv_instruction(id = 4) void byRefParam(spirv_by_reference spirv_string s);

// Valid declarations whose variadic tails are abused at the call sites below.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 5) void litTail(spirv_literal ...);
spirv_instruction(set = "Fictional.TestExtInstSet", id = 6) void refTail(spirv_by_reference ...);
spirv_instruction(set = "Fictional.TestExtInstSet", id = 7) void stringArg(spirv_string s);

void main()
{
    // ERROR: a literal string cannot be encoded into a 'spirv_literal' tail.
    litTail("oops");

    // ERROR: a literal string cannot be passed by SPIR-V pointer.
    refTail("oops");

    // ERROR: embedded NULs are not valid string literal contents.
    stringArg("bad\000string");
}
