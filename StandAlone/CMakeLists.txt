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

target_link_libraries(glslangValidator
                      glslang
                      GenericCodeGen
                      OSDependent
                      Preprocessor
                      OGLCompiler)
if(UNIX)
    target_link_libraries(${target_link_libraries} pthread)
endif(UNIX)

install(TARGETS glslangValidator
        RUNTIME DESTINATION bin)
