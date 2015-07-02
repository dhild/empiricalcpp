add_custom_target(UnitTests)
set_target_properties(UnitTests PROPERTIES FOLDER "Tests")

include_directories(googletest/include googletest)
add_empirical_library(gtest ${CMAKE_CURRENT_SOURCE_DIR}/googletest/src/gtest-all.cc)

function(add_empirical_unittest test_dirname)
  add_unittest(UnitTests ${test_dirname} ${ARGN})
endfunction()

add_subdirectory(QuadratureTests)
