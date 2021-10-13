cmake_minimum_required(VERSION 3.0)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0074 NEW)
endif()

project(test-glslang)

#
# target glslang
#
find_package(glslang ${CHECK_VERSION} EXACT REQUIRED)

add_executable(test-glslang test-glslang.cpp)
target_link_libraries(test-glslang glslang)
install(TARGETS test-glslang DESTINATION bin)

#
# target hlsl
#
find_package(HLSL ${CHECK_VERSION} EXACT REQUIRED)
# linking could not be tested as the HLSL library does not export any symbol

include(FeatureSummary)
feature_summary(WHAT ALL)
