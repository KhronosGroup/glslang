#version 460

#extension GL_EXT_spirv_intrinsics : enable
#extension GL_EXT_spirv_intrinsics_string : enable

// Made-up instruction taking a 'spirv_string' parameter.
spirv_instruction(extensions = ["SPV_KHR_non_semantic_info"],
                  set = "NonSemantic.EXAMPLE.DebugMarker", id = 1)
void debugMarker(spirv_string label);

// 'spirv_string' is a distinct type for overload resolution: a literal string
// selects this overload, an integer selects the other.
spirv_instruction(set = "Fictional.TestExtInstSet", id = 2)
void tag(spirv_string s);
spirv_instruction(set = "Fictional.TestExtInstSet", id = 3)
void tag(int i);

void main()
{
    debugMarker("begin");
    debugMarker("begin");  // identical string: the OpString may be reused
    debugMarker("end");
    debugMarker("");       // empty string: OpString with only the NUL terminator

    tag("named");          // selects tag(spirv_string)
    tag(42);               // selects tag(int)
}
