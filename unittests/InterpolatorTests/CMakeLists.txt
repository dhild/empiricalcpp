file(GLOB test_srcs "*.cpp")

add_empirical_unittest(InterpolatorTests
  ${test_srcs}
)
