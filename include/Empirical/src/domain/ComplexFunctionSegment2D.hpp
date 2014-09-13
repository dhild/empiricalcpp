#ifndef EMPIRICAL_DOMAIN_FUNCTION_SEGMENT_2D_HPP_
#define EMPIRICAL_DOMAIN_FUNCTION_SEGMENT_2D_HPP_

#include <functional>
#include <Eigen/Dense>
#include "Empirical/src/domain/Domain2D.hpp"
#include "Empirical/src/config.h"

namespace empirical {

class Quadrature;

class ComplexFunctionSegment2D : public DomainSegment2D {
 private:

  const std::function<cScalar(cScalar)>& z_complex;
  const std::function<cScalar(cScalar)>& z_complex_derivative;

  cScalar points(Scalar t) const;
  cScalar pointDerivative(Scalar t) const;

 public:

  ComplexFunctionSegment2D(const std::function<cScalar(cScalar)>& z_complex_func,
                           const std::function<cScalar(cScalar)>& z_complex_derivative_func,
                           const int M);

  virtual ~ComplexFunctionSegment2D();
};

}

#endif /* EMPIRICAL_DOMAIN_FUNCTION_SEGMENT_2D_HPP_ */
