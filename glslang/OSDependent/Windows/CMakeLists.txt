cmake_minimum_required(VERSION 2.8)

include_directories(. ../../../OGLCompilersDLL)

add_library(OSDependent STATIC ossource.cpp osinclude.h)

install(TARGETS OSDependent 
        ARCHIVE DESTINATION lib)
