set(SOURCES
    GlslangToSpv.cpp
    InReadableOrder.cpp
    Logger.cpp
    SpvBuilder.cpp
    SpvPostProcess.cpp
    doc.cpp
    SpvTools.cpp
    disassemble.cpp)

set(SPVREMAP_SOURCES
    SPVRemapper.cpp
    doc.cpp)

set(HEADERS
    bitutils.h
    spirv.hpp
    GLSL.std.450.h
    GLSL.ext.EXT.h
    GLSL.ext.KHR.h
    GlslangToSpv.h
    hex_float.h
    Logger.h
    SpvBuilder.h
    spvIR.h
    doc.h
    SpvTools.h
    disassemble.h)

set(SPVREMAP_HEADERS
    SPVRemapper.h
    doc.h)

if(ENABLE_AMD_EXTENSIONS)
    list(APPEND
         HEADERS
         GLSL.ext.AMD.h)
endif(ENABLE_AMD_EXTENSIONS)

if(ENABLE_NV_EXTENSIONS)
    list(APPEND
         HEADERS
         GLSL.ext.NV.h)
endif(ENABLE_NV_EXTENSIONS)

add_library(SPIRV ${LIB_TYPE} ${SOURCES} ${HEADERS})
set_property(TARGET SPIRV PROPERTY FOLDER glslang)
set_property(TARGET SPIRV PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(SPIRV PUBLIC ..)


set(SPIRV_NAME spirv)
set(SPIRV_VERSION 1.3)

if (ENABLE_SPVREMAPPER)
    add_library(SPVRemapper ${LIB_TYPE} ${SPVREMAP_SOURCES} ${SPVREMAP_HEADERS})
    set_property(TARGET SPVRemapper PROPERTY FOLDER glslang)
    set_property(TARGET SPVRemapper PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

if(WIN32 AND BUILD_SHARED_LIBS)
    set_target_properties(SPIRV PROPERTIES PREFIX "")
    if (ENABLE_SPVREMAPPER)
        set_target_properties(SPVRemapper PROPERTIES PREFIX "")
    endif()
endif()

target_include_directories(SPIRV PUBLIC ${SPIRV_TOOLS_INCLUDE_DIRS})
target_compile_options(SPIRV PUBLIC ${SPIRV_TOOLS_CFLAGS_OTHER})
target_link_libraries(SPIRV ${SPIRV_TOOLS_LIBRARIES})
if(BUILD_SHARED_LIBS)
    target_include_directories(SPIRV PUBLIC ${SPIRV_TOOLS_SHARED_INCLUDE_DIRS})
    target_compile_options(SPIRV PUBLIC ${SPIRV_TOOLS_SHARED_CFLAGS_OTHER})
    target_link_libraries(SPIRV ${SPIRV_TOOLS_SHARED_LIBRARIES})
endif(BUILD_SHARED_LIBS)

if(ENABLE_OPT)
    target_include_directories(SPIRV
        PRIVATE ${spirv-tools_SOURCE_DIR}/include
        PRIVATE ${spirv-tools_SOURCE_DIR}/source
    )
    target_link_libraries(SPIRV glslang)
else()
    target_link_libraries(SPIRV glslang)
endif(ENABLE_OPT)

if(WIN32)
    source_group("Source" FILES ${SOURCES} ${HEADERS})
    source_group("Source" FILES ${SPVREMAP_SOURCES} ${SPVREMAP_HEADERS})
endif(WIN32)

if(ENABLE_GLSLANG_INSTALL)
    if(BUILD_SHARED_LIBS)
        if (ENABLE_SPVREMAPPER)
            install(TARGETS SPVRemapper
                    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
        endif()
        install(TARGETS SPIRV
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    else()
        if (ENABLE_SPVREMAPPER)
            install(TARGETS SPVRemapper
                    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
        endif()
        install(TARGETS SPIRV
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
    endif()

    # spirv.pc Configuration
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/spirv.pc.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/pkgconfig/spirv.pc @ONLY)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pkgconfig/spirv.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
    install(FILES ${HEADERS} ${SPVREMAP_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SPIRV/)
endif(ENABLE_GLSLANG_INSTALL)
