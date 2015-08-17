cmake_minimum_required(VERSION 2.8)

include_directories(.)
if(WIN32)
    include_directories(../glslang/OSDependent/Windows)
elseif(UNIX)
    include_directories(../glslang/OSDependent/Linux)
else(WIN32)
    message("unkown platform")
endif(WIN32)

set(SOURCES StandAlone.cpp)
set(REMAPPER_SOURCES spirv-remap.cpp)

add_executable(glslangValidator ${SOURCES})
add_executable(spirv-remap ${REMAPPER_SOURCES})

set(LIBRARIES
    glslang
    OGLCompiler
    OSDependent
    SPIRV)

if(WIN32)
    set(LIBRARIES ${LIBRARIES} psapi)
elseif(UNIX)
    if(NOT ANDROID)
        set(LIBRARIES ${LIBRARIES} pthread)
    endif()
endif(WIN32)

target_link_libraries(glslangValidator ${LIBRARIES})
target_link_libraries(spirv-remap ${LIBRARIES})

if(WIN32)
    source_group("Source" FILES ${SOURCES})
endif(WIN32)

install(TARGETS glslangValidator
        RUNTIME DESTINATION bin)

install(TARGETS spirv-remap
        RUNTIME DESTINATION bin)
