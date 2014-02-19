cmake_minimum_required(VERSION 2.8)

include_directories(. ../glslang ../glslang/OSDependent/Linux)

add_library(OGLCompiler STATIC  InitializeDll.cpp)

