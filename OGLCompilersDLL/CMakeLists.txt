set(SOURCES InitializeDll.cpp InitializeDll.h)

add_library(OGLCompiler ${LIB_TYPE} ${SOURCES})
set_property(TARGET OGLCompiler PROPERTY FOLDER glslang)
set_property(TARGET OGLCompiler PROPERTY POSITION_INDEPENDENT_CODE ON)

if(WIN32)
    source_group("Source" FILES ${SOURCES})
endif(WIN32)

if(ENABLE_GLSLANG_INSTALL)
    if(BUILD_SHARED_LIBS)
        install(TARGETS OGLCompiler
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    else()
        install(TARGETS OGLCompiler
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
    endif()
endif(ENABLE_GLSLANG_INSTALL)
