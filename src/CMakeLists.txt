add_library(empiricalcpp ""
  Constants.cpp
  EmpiricalInterpolationScalar1D.cpp
  Quadrature.cpp
  Version.cpp
)

set_target_properties(empiricalcpp
    PROPERTIES
    COMPILE_FLAGS "${CMAKE_CXX_FLAGS} ${cxx_base_flags}")
