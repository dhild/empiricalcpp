cmake_minimum_required (VERSION 2.6)
project (EmpiricalCpp)

set (PROJECT_VERSION_MAJOR 1)
set (PROJECT_VERSION_MINOR 0)
set (PROJECT_VERSION_TYPE SNAPSHOT)
set (PROJECT_VERSION_BUILD DEV)
set (PROJECT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_TYPE}-${PROJECT_VERSION_BUILD}")

set (CMAKE_VERBOSE_MAKEFILE 1) # Use 1 for debugging, 0 for release

add_definitions(-std=c++11)

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

find_package(Boost 1.35 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

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
