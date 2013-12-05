cmake_minimum_required (VERSION 2.6)
project (EmpiricalCpp)

set (EmpiricalCpp_VERSION_MAJOR 1)
set (EmpiricalCpp_VERSION_MINOR 0)
set (EmpiricalCpp_VERSION_TYPE SNAPSHOT)
set (EmpiricalCpp_VERSION_BUILD DEV)
set (EmpiricalCpp_VERSION_STRING "${EmpiricalCpp_VERSION_MAJOR}.${EmpiricalCpp_VERSION_MINOR}.${EmpiricalCpp_VERSION_TYPE}-${EmpiricalCpp_VERSION_BUILD}")

set (CMAKE_VERBOSE_MAKEFILE 1) # Use 1 for debugging, 0 for release

set (MAINFOLDER ${PROJECT_SOURCE_DIR})
set (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
set (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

list (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
list (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/thirdparty")

set (CMAKE_MODULE_PATH "${MAINFOLDER}/thirdparty/cmake")
include (DocumentationTargets)

find_package(UnitTestPlusPlus REQUIRED)
include_directories(${UnitTestPlusPlus_INCLUDE_DIRS})
link_directories(${UnitTestPlusPlus_LIBRARY_DIRS})

include_directories ("${MAINFOLDER}/thirdparty/include")
include_directories ("${MAINFOLDER}/include")

file (GLOB_RECURSE CONFIGINPUTS1 include/*.h.in)
file (GLOB_RECURSE CONFIGINPUTS2 src/*.h.in)
file (GLOB_RECURSE CONFIGINPUTS3 test/*.h.in)
list (APPEND CONFIGINPUTS "${CONFIGINPUTS1}")
list (APPEND CONFIGINPUTS "${CONFIGINPUTS2}")
list (APPEND CONFIGINPUTS "${CONFIGINPUTS3}")
foreach (CONFIGINPUT ${CONFIGINPUTS})
  string (REPLACE ".h.in" ".h" CONFIGOUTPUT "${CONFIGINPUT}")
  configure_file ("${CONFIGINPUT}" "${CONFIGOUTPUT}")
endforeach (CONFIGINPUT ${CONFIGINPUTS})

add_subdirectory(src)
add_subdirectory(test)
