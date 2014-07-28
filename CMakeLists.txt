cmake_minimum_required(VERSION 2.8)

set(CMAKE_INSTALL_PREFIX "install" CACHE STRING "prefix" FORCE)

project(glslang)

if(WIN32)
    set(CMAKE_GENERATOR_TOOLSET "v110" CACHE STRING "Platform Toolset" FORCE)
    include(ChooseMSVCCRT.cmake)
elseif(UNIX)
    add_definitions(-fPIC)
else(WIN32)
    message("unkown platform")
endif(WIN32)

add_subdirectory(glslang)
add_subdirectory(OGLCompilersDLL)
add_subdirectory(StandAlone)
add_subdirectory(BIL)
