# BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
# make it prominent in the GUI.
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

option(empirical_build_tests "Build all of empirical's tests." OFF)
option(empirical_define_ostream_operators "Compiles in std::ostream operators for printing" ON)

set(empirical_compile_options ""
    CACHE STRING "Command line options to add to the compilation")

# Name of the project.
#
# CMake files in this project can refer to the root source directory
# as ${empirical_SOURCE_DIR} and to the root binary directory as
# ${empirical_BINARY_DIR}.
project(empirical CXX)
cmake_minimum_required(VERSION 3.0)

include(cmake/macros.cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

config_compiler_and_linker()  # Defined in macros.cmake.

if (empirical_build_tests)
  # This must be set in the root directory for the tests to be run by
  # 'make test' or ctest.
  enable_testing()
  
  # use add_test()
  
endif()

add_subdirectory(empirical)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/empirical/include)
add_subdirectory(unittests)
