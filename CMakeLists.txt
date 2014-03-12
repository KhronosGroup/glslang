cmake_minimum_required(VERSION 2.8)

set(CMAKE_INSTALL_PREFIX "install" CACHE STRING "prefix" FORCE)

project(glslang)

if(WIN32)
    include(ChooseMSVCCRT.cmake)
    foreach(build_type ${CMAKE_CONFIGURATION_TYPES} ${CMAKE_BUILD_TYPE})
        string(TOUPPER "${build_type}" build)
        message("CMAKE_CXX_FLAGS_${build} are ${CMAKE_CXX_FLAGS_${build}}")
    endforeach(build_type)

    add_subdirectory(glslang/OSDependent/Windows)
elseif(UNIX)
    add_subdirectory(glslang/OSDependent/Linux)
else(WIN32)
    message("unkown platform")
endif(WIN32)

add_subdirectory(glslang/MachineIndependent)
add_subdirectory(glslang/MachineIndependent/preprocessor)
add_subdirectory(glslang/GenericCodeGen)
add_subdirectory(OGLCompilersDLL)
add_subdirectory(StandAlone)
