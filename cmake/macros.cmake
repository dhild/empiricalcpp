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