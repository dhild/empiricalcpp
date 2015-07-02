include_directories(${empirical_SOURCE_DIR}/include)

add_subdirectory(include)
add_subdirectory(src)

get_directory_property(empirical_main_headers
    DIRECTORY ${CMAKE_SOURCE_DIR}/empirical/include/empiricalcpp
    DEFINITION empirical_header_files)
get_directory_property(empirical_main_src_headers
    DIRECTORY ${CMAKE_SOURCE_DIR}/empirical/include/empiricalcpp/src
    DEFINITION empirical_header_files)
get_directory_property(empirical_src_files
    DIRECTORY ${CMAKE_SOURCE_DIR}/empirical/src
    DEFINITION empirical_src_files)
get_directory_property(empirical_src_interpolation_files
    DIRECTORY ${CMAKE_SOURCE_DIR}/empirical/src
    DEFINITION empirical_src_interpolation_files)

add_library(empiricalcpp ""
  ${empirical_main_headers}
  ${empirical_main_src_headers}
  ${empirical_src_files}
  ${empirical_src_interpolation_files}
)

set_target_properties(empiricalcpp
    PROPERTIES
    COMPILE_FLAGS "${CMAKE_CXX_FLAGS} ${cxx_base_flags}")

source_group("empiricalcpp" FILES ${empirical_main_headers})
source_group("empiricalcpp\\src" FILES ${empirical_main_src_headers})
source_group("src" FILES ${empirical_src_files})
source_group("src\\interpolation" FILES ${empirical_src_interpolation_files})
