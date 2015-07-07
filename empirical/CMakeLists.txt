include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE empirical_sources "*.cpp")
file(GLOB_RECURSE empirical_headers "*.hpp")

add_library(empiricalcpp ""
  ${empirical_sources}
  ${empirical_headers}
)

foreach (_file ${empirical_sources} ${empirical_headers})
  get_filename_component(_dir ${_file} DIRECTORY)
  string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" _group_dir_tmp ${_dir})
  string(REPLACE "/" "\\" _group_dir ${_group_dir_tmp})
  source_group(${_group_dir} FILES ${_file})
endforeach()

set_target_properties(empiricalcpp
    PROPERTIES
    COMPILE_FLAGS "${CMAKE_CXX_FLAGS} ${cxx_base_flags}")
