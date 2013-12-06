add_subdirectory(math)

file (GLOB project_SRCS *.cpp *.c *.h)

add_executable(EmpiricalCpp ${project_SRCS})
target_link_libraries(EmpiricalCpp EmpiricalCpp_math)

set_target_properties(EmpiricalCpp PROPERTIES VERSION "${EmpiricalCpp_VERSION_MAJOR}.${EmpiricalCpp_VERSION_MINOR}" OUTPUT_NAME EmpiricalCpp CLEAN_DIRECT_OUTPUT 1)

install (TARGETS EmpiricalCpp DESTINATION bin)
