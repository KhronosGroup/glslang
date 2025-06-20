find_package(nlohmann_json REQUIRED)

add_executable(compile_compute_shader compile_compute_shader.cc) 
target_link_libraries(compile_compute_shader PUBLIC MachineIndependent)

add_executable(glsld glsld.cc doc.cc workspace.cc protocol.cc)
target_link_libraries(glsld PRIVATE MachineIndependent nlohmann_json::nlohmann_json)
target_include_directories(glsld PRIVATE ${nlohmann_json_DIR}/../../../include)
