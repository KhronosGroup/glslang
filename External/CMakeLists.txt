# Suppress all warnings from external projects.
set_property(DIRECTORY APPEND PROPERTY COMPILE_OPTIONS -w)

if (TARGET gmock)
  message(STATUS "Google Mock already configured - use it")
elseif(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/googletest)
  # We need to make sure Google Test does not mess up with the
  # global CRT settings on Windows.
  if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  endif(WIN32)
  add_subdirectory(googletest)
else()
  message(STATUS
    "Google Mock was not found - tests based on that will not build")
endif()
