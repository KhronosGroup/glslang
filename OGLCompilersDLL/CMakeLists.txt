cmake_minimum_required(VERSION 2.8)

include_directories(. ../glslang)
if(WIN32)
    include_directories(${include_directories} ../glslang/OSDependent/Windows)
elseif(UNIX)
    include_directories(${include_directories} ../glslang/OSDependent/Linux)
else(WIN32)
    message("unkown platform")
endif(WIN32)

add_library(OGLCompiler STATIC  InitializeDll.cpp InitializeDll.h)

install(TARGETS OGLCompiler 
        ARCHIVE DESTINATION lib)
