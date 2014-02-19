cmake_minimum_required(VERSION 2.8)

include_directories(. ..)
set(SOURCES CodeGen.cpp Link.cpp)

add_library(GenericCodeGen STATIC ${SOURCES}) 

