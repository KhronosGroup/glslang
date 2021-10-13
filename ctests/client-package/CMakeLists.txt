cmake_minimum_required(VERSION 3.0)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0074 NEW)
endif()

project(test-glslang)

find_package(glslang ${CHECK_VERSION} EXACT REQUIRED)

add_executable(test-glslang test-glslang.cpp)
target_link_libraries(test-glslang glslang)
install(TARGETS test-glslang DESTINATION bin)

include(FeatureSummary)
feature_summary(WHAT ALL)
