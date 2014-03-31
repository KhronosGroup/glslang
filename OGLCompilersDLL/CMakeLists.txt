cmake_minimum_required(VERSION 2.8)

include_directories(. ../glslang)
if(WIN32)
    include_directories(${include_directories} ../glslang/OSDependent/Windows)
elseif(UNIX)
    include_directories(${include_directories} ../glslang/OSDependent/Linux)
else(WIN32)
    message("unknown platform")
endif(WIN32)

set(SOURCES InitializeDll.cpp InitializeDll.h)

add_library(OGLCompiler STATIC ${SOURCES})

if(WIN32)
    source_group("Source" FILES ${SOURCES})
endif(WIN32)

install(TARGETS OGLCompiler 
        ARCHIVE DESTINATION lib)
