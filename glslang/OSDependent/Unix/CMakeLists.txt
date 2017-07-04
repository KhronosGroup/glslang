add_library(OSDependent STATIC ossource.cpp ../osinclude.h)
set_property(TARGET OSDependent PROPERTY FOLDER glslang)
set_property(TARGET OSDependent PROPERTY POSITION_INDEPENDENT_CODE ON)

install(TARGETS OSDependent
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
