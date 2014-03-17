cmake_minimum_required(VERSION 2.8)

include_directories(.)
if(WIN32)
    include_directories(${include_directories} ../glslang/OSDependent/Windows)
elseif(UNIX)
    include_directories(${include_directories} ../glslang/OSDependent/Linux)
else(WIN32)
    message("unkown platform")
endif(WIN32)

add_executable(glslangValidator StandAlone.cpp)

set(LIBRARIES
    glslang
    GenericCodeGen
    OSDependent
    Preprocessor
    OGLCompiler)

if(WIN32)
    set(LIBRARIES ${LIBRARIES} psapi)
elseif(UNIX)
    set(LIBRARIES ${LIBRARIES} pthread)
endif(WIN32)

target_link_libraries(glslangValidator ${LIBRARIES})

install(TARGETS glslangValidator
        RUNTIME DESTINATION bin)
