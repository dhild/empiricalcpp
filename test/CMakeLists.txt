file (GLOB_RECURSE test_SRCS *.cpp *.c *.h)

add_executable(EmpiricalCpp-unittests ${test_SRCS})

add_custom_target(test ALL "${MAINFOLDER}/bin/EmpiricalCpp-unittests" DEPENDS EmpiricalCpp-unittests COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS})
