file (GLOB_RECURSE project_SRCS *.cpp *.c *.h)

add_executable(EmpiricalCpp ${project_SRCS})

set_target_properties(EmpiricalCpp PROPERTIES VERSION "${EmpiricalCpp_VERSION_MAJOR}.${EmpiricalCpp_VERSION_MINOR}" OUTPUT_NAME EmpiricalCpp CLEAN_DIRECT_OUTPUT 1)

install (TARGETS EmpiricalCpp DESTINATION bin)
