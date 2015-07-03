file(GLOB test_srcs "*.cpp")

add_empirical_unittest(MeshTests
  ${test_srcs}
)
