add_library(OSDependent ${LIB_TYPE} ossource.cpp ../osinclude.h)
set_property(TARGET OSDependent PROPERTY FOLDER glslang)
set_property(TARGET OSDependent PROPERTY POSITION_INDEPENDENT_CODE ON)

if(ENABLE_GLSLANG_INSTALL)
    if(BUILD_SHARED_LIBS)
        install(TARGETS OSDependent
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    else()
        install(TARGETS OSDependent
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
    endif()
endif(ENABLE_GLSLANG_INSTALL)
