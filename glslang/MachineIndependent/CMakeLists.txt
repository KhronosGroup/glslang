cmake_minimum_required(VERSION 2.8)

include_directories(. ../../OGLCompilersDLL ${CMAKE_CURRENT_BINARY_DIR})
if(WIN32)
    include_directories(${include_directories} ../OSDependent/Windows)
elseif(UNIX)
    include_directories(${include_directories} ../OSDependent/Linux)
else(WIN32)
    message("unkown platform")
endif(WIN32)

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

set(HEADERS
    ../Public/ShaderLang.h
    gl_types.h
    Initialize.h
    localintermediate.h
    ParseHelper.h
    reflection.h
    RemoveTree.h
    Scan.h
    ScanContext.h
    SymbolTable.h
    unistd.h
    Versions.h)

find_package(BISON)
if(BISON_FOUND)
    message("bison found")
    BISON_TARGET(GLSLParser glslang.y ${CMAKE_CURRENT_BINARY_DIR}/gen_glslang_tab.cpp
                 COMPILE_FLAGS
                 "--defines=${CMAKE_CURRENT_BINARY_DIR}/glslang_tab.cpp.h")
else(BISON_FOUND)
    message("using custom command for bison on glslang.y")
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/glslang_tab.cpp ${CMAKE_CURRENT_BINARY_DIR}/glslang_tab.cpp.h
                       COMMAND ../../tools/bison.exe --defines=${CMAKE_CURRENT_BINARY_DIR}/glslang_tab.cpp.h -t glslang.y -o ${CMAKE_CURRENT_BINARY_DIR}/glslang_tab.cpp
                       MAIN_DEPENDENCY glslang.y
                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    set(BISON_GLSLParser_OUTPUT_SOURCE glslang_tab.cpp)
endif(BISON_FOUND)

add_library(glslang STATIC ${BISON_GLSLParser_OUTPUT_SOURCE} ${SOURCES} ${HEADERS})

install(TARGETS glslang 
        ARCHIVE DESTINATION lib)
