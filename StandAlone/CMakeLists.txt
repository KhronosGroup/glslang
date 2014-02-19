cmake_minimum_required(VERSION 2.8)

include_directories(. ../glslang/OSDependent/Linux)

add_executable(glslangValidator StandAlone.cpp)
target_link_libraries(glslangValidator
                      glslang
                      GenericCodeGen
                      OSDependent
                      Preprocessor
                      OGLCompiler
                      pthread)

