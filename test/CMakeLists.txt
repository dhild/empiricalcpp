file (GLOB_RECURSE test_SRCS *.cpp *.c *.h)
set (test_LIBS ${UnitTestPlusPlus_LIBRARIES})

add_executable(EmpiricalCpp-unittests ${test_SRCS})
target_link_libraries(EmpiricalCpp-unittests ${test_LIBS} EmpiricalCpp_math)

add_custom_target(test ALL "${MAINFOLDER}/bin/EmpiricalCpp-unittests" DEPENDS EmpiricalCpp-unittests COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS})
