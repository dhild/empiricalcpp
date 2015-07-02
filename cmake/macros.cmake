# This must be a macro(), as inside a function string() can only
# update variables in the function scope.

macro(config_compiler_and_linker)
  if (MSVC)
    # This replacement code is taken from sample in the CMake Wiki at
    # http://www.cmake.org/Wiki/CMake_FAQ#Dynamic_Replace.
    foreach (flag_var
             CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
             CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
      # We prefer more strict warning checking.
      # Replaces /W3 with /W4 in defaults.
      string(REPLACE "/W3" "-W4" ${flag_var} "${${flag_var}}")
    endforeach()
    set(cxx_base_flags "-GS -W4 -WX -nologo -J -Zi")
    set(cxx_base_flags "${cxx_base_flags} -D_UNICODE -DUNICODE -DWIN32 -D_WIN32")
    set(cxx_base_flags "${cxx_base_flags} -DSTRICT -DWIN32_LEAN_AND_MEAN")
    # Disable warnings about copy-assignments; they don't indicate actual issues
    set(cxx_base_flags "${cxx_base_flags} -D_SCL_SECURE_NO_WARNINGS")
    set(cxx_base_flags "${cxx_base_flags} -EHsc")
  elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(cxx_base_flags "-Wall -Wshadow -Wextra")
    set(cxx_base_flags "${cxx_base_flags} -fexceptions")
  endif()


  # For building empirical's tests and samples.
  set(cxx_exception "${CMAKE_CXX_FLAGS} ${cxx_base_flags} ${cxx_exception_flags}")
  set(cxx_no_exception
    "${CMAKE_CXX_FLAGS} ${cxx_base_flags} ${cxx_no_exception_flags}")
  set(cxx_default "${cxx_exception}")
  set(cxx_no_rtti "${cxx_default} ${cxx_no_rtti_flags}")

  # For building the empirical libraries.
  set(cxx_strict "${cxx_default} ${cxx_strict_flags}")
endmacro()

macro(add_empirical_library name)
  if( BUILD_SHARED_LIBS )
    add_library(${name} SHARED ${ARGN})
  else()
    add_library(${name} ${ARGN})
  endif()

  if( NOT empirical_build_tests )
    set_target_properties(${name} PROPERTIES EXCLUDE_FROM_ALL ON)
  endif()
  set_target_properties(${name} PROPERTIES FOLDER "Libraries")
endmacro(add_empirical_library name)

function(add_unittest test_suite test_name)
  if( empirical_build_tests )
    add_executable(${test_name} ${ARGN})
  else()
    add_executable(${test_name} EXCLUDE_FROM_ALL ${ARGN})
  endif()
  
  set(outdir ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR})
  if(NOT "${CMAKE_CFG_INTDIR}" STREQUAL ".")
    foreach(build_mode ${CMAKE_CONFIGURATION_TYPES})
      string(TOUPPER "${build_mode}" CONFIG_SUFFIX)
      string(REPLACE ${CMAKE_CFG_INTDIR} ${build_mode} outdir_config ${outdir})
      set_target_properties(${test_name} PROPERTIES "RUNTIME_OUTPUT_DIRECTORY_${CONFIG_SUFFIX}" ${outdir_config})
      set_target_properties(${test_name} PROPERTIES "ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_SUFFIX}" ${outdir_config})
      set_target_properties(${test_name} PROPERTIES "LIBRARY_OUTPUT_DIRECTORY_${CONFIG_SUFFIX}" ${outdir_config})
    endforeach()
  else()
    set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${outdir})
    set_target_properties(${test_name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${outdir})
    set_target_properties(${test_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${outdir})
  endif()
  
  target_link_libraries(${test_name}
    gtest
    epmiricalcpp
    )

  add_dependencies(${test_suite} ${test_name})
  get_target_property(test_suite_folder ${test_suite} FOLDER)
  if (NOT ${test_suite_folder} STREQUAL "NOTFOUND")
    set_property(TARGET ${test_name} PROPERTY FOLDER "${test_suite_folder}")
  endif ()
endfunction()
