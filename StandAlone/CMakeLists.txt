cmake_minimum_required(VERSION 2.8)

include_directories(.)
if(WIN32)
    include_directories(${include_directories} ../glslang/OSDependent/Windows)
elseif(UNIX)
    include_directories(${include_directories} ../glslang/OSDependent/Linux)
else(WIN32)
    message("unkown platform")
endif(WIN32)

set(SOURCES StandAlone.cpp)

add_executable(glslangValidator ${SOURCES})

set(LIBRARIES
    glslang
    OGLCompiler
    OSDependent)

if(WIN32)
    set(LIBRARIES ${LIBRARIES} psapi)
elseif(UNIX)
    set(LIBRARIES ${LIBRARIES} pthread)
endif(WIN32)

target_link_libraries(glslangValidator ${LIBRARIES})

if(WIN32)
    source_group("Source" FILES ${SOURCES})
endif(WIN32)

install(TARGETS glslangValidator
        RUNTIME DESTINATION bin)
