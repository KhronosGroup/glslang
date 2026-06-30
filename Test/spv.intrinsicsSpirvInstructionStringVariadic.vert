#version 460

#extension GL_EXT_spirv_intrinsics : enable
#extension GL_EXT_spirv_intrinsics_variadic : enable
#extension GL_EXT_spirv_intrinsics_string : enable

// With GL_EXT_spirv_intrinsics_string and GL_EXT_spirv_intrinsics_variadic
// together, NonSemantic.DebugPrintf can be expressed. It is named differently
// here to avoid a naming conflict.
spirv_instruction(extensions = ["SPV_KHR_non_semantic_info"],
                  set = "NonSemantic.DebugPrintf", id = 1)
void printfStr(spirv_string format, ...);

void main()
{
    float x = 1.0;
    int n = 3;

    printfStr("no arguments\n");          // format only, empty tail
    printfStr("x = %f\n", x);             // one trailing argument
    printfStr("x = %f, n = %d\n", x, n);  // two trailing arguments
    printfStr("tail string = %s\n", "ok");
}
