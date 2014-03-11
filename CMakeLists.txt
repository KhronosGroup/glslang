cmake_minimum_required(VERSION 2.8)

project(glslang)

add_subdirectory(glslang/MachineIndependent)
add_subdirectory(glslang/MachineIndependent/preprocessor)
add_subdirectory(glslang/GenericCodeGen)
add_subdirectory(OGLCompilersDLL)
add_subdirectory(StandAlone)

if(WIN32)
    add_subdirectory(glslang/OSDependent/Windows)
elseif(UNIX)
    add_subdirectory(glslang/OSDependent/Linux)
else(WIN32)
    message("unkown platform")
endif(WIN32)
