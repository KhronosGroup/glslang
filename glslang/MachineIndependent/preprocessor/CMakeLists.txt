cmake_minimum_required(VERSION 2.8)

include_directories(. ..)
set(SOURCES 
    Pp.cpp
    PpAtom.cpp
    PpContext.cpp
    PpMemory.cpp
    PpScanner.cpp
    PpSymbols.cpp
    PpTokens.cpp)

set(HEADERS
    PpContext.h
    PpTokens.h)

add_library(Preprocessor STATIC ${SOURCES} ${HEADERS})

install(TARGETS Preprocessor
        ARCHIVE DESTINATION lib)
