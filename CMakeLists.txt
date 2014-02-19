cmake_minimum_required(VERSION 2.8)

add_subdirectory(glslang/MachineIndependent)
add_subdirectory(glslang/MachineIndependent/preprocessor)
add_subdirectory(glslang/GenericCodeGen)
add_subdirectory(glslang/OSDependent/Linux)
add_subdirectory(OGLCompilersDLL)
add_subdirectory(StandAlone)

