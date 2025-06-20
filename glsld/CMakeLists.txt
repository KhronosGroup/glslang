find_package(nlohmann_json REQUIRED)

add_executable(compile_compute_shader compile_compute_shader.cc) 
target_link_libraries(compile_compute_shader PUBLIC MachineIndependent)

add_library(lsp STATIC doc.cc workspace.cc protocol.cc)
target_link_libraries(lsp PUBLIC MachineIndependent nlohmann_json::nlohmann_json)
target_include_directories(lsp PUBLIC ${nlohmann_json_DIR}/../../../include)

add_executable(glsld glsld.cc)
add_executable(test_protocol test_protocol.cc)
target_link_libraries(glsld PUBLIC lsp)
target_link_libraries(test_protocol PUBLIC lsp)
