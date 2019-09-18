add_executable(glslang.js "glslang.js.cpp")
glslang_set_link_args(glslang.js)
target_link_libraries(glslang.js glslang SPIRV)
if(EMSCRIPTEN)
    set_target_properties(glslang.js PROPERTIES
        OUTPUT_NAME "glslang"
        SUFFIX ".js"
        LINK_FLAGS "--bind -s EXPORT_NAME=\"glslangModule\"")
    em_link_pre_js(glslang.js "${CMAKE_CURRENT_SOURCE_DIR}/glslang.pre.js")
endif(EMSCRIPTEN)
