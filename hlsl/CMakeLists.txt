cmake_minimum_required(VERSION 2.8)

set(SOURCES
    hlslParseHelper.cpp
    hlslScanContext.cpp
    hlslGrammar.cpp)

set(HEADERS
    hlslParseHelper.h
    hlslTokens.h
    hlslScanContext.h
    hlslGrammar.h)

add_library(HLSL STATIC ${SOURCES} ${HEADERS})

if(WIN32)
    source_group("Source" FILES ${SOURCES} ${HEADERS})
endif(WIN32)

install(TARGETS HLSL
        ARCHIVE DESTINATION lib)
