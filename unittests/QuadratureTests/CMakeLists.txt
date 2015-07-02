file(GLOB test_srcs "*.cpp")

add_empirical_unittest(QuadratureTests
  ${test_srcs}
)
