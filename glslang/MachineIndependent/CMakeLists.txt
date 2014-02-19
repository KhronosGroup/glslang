cmake_minimum_required(VERSION 2.8)

include_directories(. ../OSDependent/Linux ../../OGLCompilersDLL ${CMAKE_CURRENT_BINARY_DIR})
set(SOURCES
    Constant.cpp
    InfoSink.cpp
    Initialize.cpp
    IntermTraverse.cpp
    Intermediate.cpp
    ParseHelper.cpp
    PoolAlloc.cpp
    RemoveTree.cpp
    Scan.cpp
    ShaderLang.cpp
    SymbolTable.cpp
    Versions.cpp
    intermOut.cpp
    limits.cpp
    linkValidate.cpp
    parseConst.cpp
    reflection.cpp)

find_package(BISON)
BISON_TARGET(GLSLParser glslang.y ${CMAKE_CURRENT_BINARY_DIR}/gen_glslang_tab.cpp
             COMPILE_FLAGS
			 "--defines=${CMAKE_CURRENT_BINARY_DIR}/glslang_tab.cpp.h")

add_library(glslang STATIC ${BISON_GLSLParser_OUTPUT_SOURCE} ${SOURCES})

