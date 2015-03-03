cmake_minimum_required(VERSION 2.8)

include_directories(.. ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
    GlslangToSpv.cpp
    SpvBuilder.cpp)

set(HEADERS
    spirv.h
    GlslangToSpv.h
    SpvBuilder.h
    SpvIR.h)

add_library(SPIRV STATIC ${SOURCES} ${HEADERS})

if(WIN32)
    source_group("Source" FILES ${SOURCES} ${HEADERS})
endif(WIN32)

install(TARGETS SPIRV
        ARCHIVE DESTINATION lib)
