
#
# cmake install test
#
set(TEMP_INSTALL_DIR ${CMAKE_BINARY_DIR}/tmp)

# on native windows CMAKE_INSTALL_PREFIX is an absolute path an cannot be appended to another path
if(MSVC)
    set(INSTALL_DIR ${TEMP_INSTALL_DIR})
else()
    set(INSTALL_DIR ${TEMP_INSTALL_DIR}${CMAKE_INSTALL_PREFIX})
endif()

option(ENABLE_CLIENT_PACKAGE_TEST "Enable the test for cmake support with a client package" ON)

set(FIND_ROOT_PATH ${INSTALL_DIR})

if(CMAKE_CROSSCOMPILING)
    # detect target prefix
    get_filename_component(COMPILER_BASE_NAME ${CMAKE_C_COMPILER} NAME_WE)
    if(COMPILER_BASE_NAME MATCHES ".*-.*-.*-.*")
        string(REGEX REPLACE "^([0-9a-z_]+)-([0-9a-z]+)-([0-9a-z]+)-([-0-9a-z]+)$" "\\1-\\2-\\3" TARGET_PREFIX ${COMPILER_BASE_NAME})
        string(REGEX REPLACE "^([0-9a-z_]+)-([0-9a-z]+)-([0-9a-z]+)-([-0-9a-z]+)$" "\\1" TARGET_ARCH ${COMPILER_BASE_NAME})
    endif()

    # detect target sysroot
    if(NOT TARGET_SYSROOT)
        execute_process(
            COMMAND ${CMAKE_C_COMPILER} --print-sysroot
            OUTPUT_VARIABLE TARGET_SYSROOT
            ERROR_VARIABLE ERROR
            RESULT_VARIABLE RESULT
        )
        if(RESULT)
            set(ENABLE_CLIENT_PACKAGE_TEST 0)
            message(WARNING "disabled client package build, because sysroot could not be fetched from compiler - error is ${ERROR_VARIABLE}")
        else()
            string(REPLACE "\n" "/${TARGET_PREFIX}" TARGET_SYSROOT "${TARGET_SYSROOT}")
            set(FIND_ROOT_PATH ${TARGET_SYSROOT}${INSTALL_DIR})
        endif()
    endif()
endif()

# handle missing DESTDIR support in MSVC
if(MSVC AND NOT CMAKE_VERSION VERSION_LESS 3.15)
    set(INSTALL_COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --prefix ${INSTALL_DIR})
elseif(NOT MSVC)
    set(INSTALL_COMMAND ${CMAKE_MAKE_PROGRAM} install DESTDIR=${TEMP_INSTALL_DIR})
else(ENABLE_CLIENT_PACKAGE_TEST AND ENABLE_GLSLANG_INSTALL)
    message(WARNING "Client package test requested but cannot be enabled because the cmake version used is too old (required is at least version 3.15)")
endif()

if(ENABLE_CLIENT_PACKAGE_TEST AND ENABLE_GLSLANG_INSTALL AND INSTALL_COMMAND)
    # clean local install directories used by client build/install test
    add_test(
        NAME test-install-local-clean
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${TEMP_INSTALL_DIR}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    # install in local directoy for client build/install test
    add_test(
        NAME test-install-local
        COMMAND ${INSTALL_COMMAND}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    # build/install a client package using cmake package support from this build
    add_test(
        NAME test-install-build-client-package
        COMMAND ${CMAKE_CTEST_COMMAND}
            --build-and-test
                ${CMAKE_CURRENT_SOURCE_DIR}/client-package
                ${TEMP_INSTALL_DIR}
            --build-config "${CMAKE_BUILD_TYPE}"
            --build-generator ${CMAKE_GENERATOR}
            --build-makeprogram ${CMAKE_MAKE_PROGRAM}
            --build-target install
            --build-options
                #--trace-expand
                -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
                -Dglslang_DIR=${INSTALL_DIR}/${INSTALL_CMAKE_DIR}
                -DCHECK_VERSION=${GLSLANG_VERSION}
                -DCMAKE_CROSSCOMPILING=${CMAKE_CROSSCOMPILING}
                -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
                -DCMAKE_INSTALL_PREFIX:PATH=${INSTALL_DIR}
                -DCMAKE_FIND_ROOT_PATH:PATH=${FIND_ROOT_PATH}
                -DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER
                -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY
                -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY
                -DCMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}
                -DCMAKE_SYSTEM_PROCESSOR=${CMAKE_SYSTEM_PROCESSOR}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    set_property(TEST test-install-build-client-package APPEND PROPERTY DEPENDS test-install-local-clean test-install-local)
endif()
