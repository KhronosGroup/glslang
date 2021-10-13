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

#
# target SPIRV
#
find_package(SPIRV ${CHECK_VERSION} EXACT REQUIRED)

add_executable(test-spirv test-spirv.cpp)
target_link_libraries(test-spirv SPIRV)
install(TARGETS test-spirv DESTINATION bin)

#
# target SPVRemapper
#
find_package(SPVRemapper ${CHECK_VERSION} EXACT REQUIRED)

add_executable(test-spvremapper test-spvremapper.cpp)
target_link_libraries(test-spvremapper SPVRemapper)
install(TARGETS test-spvremapper DESTINATION bin)

#
# target glslang-default-resource-limits
#
find_package(glslang-default-resource-limits ${CHECK_VERSION} EXACT REQUIRED)

add_executable(test-glslang-default-resource-limits test-glslang-default-resource-limits.cpp)
target_link_libraries(test-glslang-default-resource-limits glslang-default-resource-limits)
install(TARGETS test-glslang-default-resource-limits DESTINATION bin)

#
# target spirv-remap
#
find_package(spirv-remap ${CHECK_VERSION} EXACT REQUIRED)

#
# target glslangvalidator
#
find_package(glslangValidator ${CHECK_VERSION} EXACT REQUIRED)

include(FeatureSummary)
feature_summary(WHAT ALL)
