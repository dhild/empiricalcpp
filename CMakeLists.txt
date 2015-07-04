# BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
# make it prominent in the GUI.
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

option(empirical_build_tests "Build all of empirical's tests." OFF)

# Name of the project.
#
# CMake files in this project can refer to the root source directory
# as ${empirical_SOURCE_DIR} and to the root binary directory as
# ${empirical_BINARY_DIR}.
project(empirical CXX)
cmake_minimum_required(VERSION 2.6.2)

include(cmake/macros.cmake)

config_compiler_and_linker()  # Defined in macros.cmake.

include_directories(${empirical_SOURCE_DIR}/include)

# Where empirical's libraries can be found.
link_directories(${empirical_BINARY_DIR}/src)

add_subdirectory(src)

if (empirical_build_tests)
  # This must be set in the root directory for the tests to be run by
  # 'make test' or ctest.
  enable_testing()
  
  # use add_test()
  
endif()
