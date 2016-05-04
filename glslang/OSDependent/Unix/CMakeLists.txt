add_library(OSDependent STATIC ossource.cpp ../osinclude.h)

install(TARGETS OSDependent 
        ARCHIVE DESTINATION lib)
