add_library(OSDependent STATIC ossource.cpp ../osinclude.h)
set_property(TARGET OSDependent PROPERTY FOLDER glslang POSITION_INDEPENDENT_CODE ON)

if(ENABLE_GLSLANG_INSTALL)
    install(TARGETS OSDependent
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif(ENABLE_GLSLANG_INSTALL)
