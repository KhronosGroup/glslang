cmake_minimum_required(VERSION 2.8)

include_directories(.. ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
    GlslangToBil.cpp
    BilBuilder.cpp
    BilDisassemble.cpp)

set(HEADERS
    GlslangToBil.h
    BilBuilder.h
    Bir.h
    BilDisassemble.h)

add_library(BIL STATIC ${SOURCES} ${HEADERS})

if(WIN32)
    source_group("Source" FILES ${SOURCES} ${HEADERS})
endif(WIN32)

install(TARGETS BIL
        ARCHIVE DESTINATION lib)
