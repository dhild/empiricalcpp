#ifndef EMPIRICAL_DOMAIN_FUNCTION_SEGMENT_2D_HPP_
#define EMPIRICAL_DOMAIN_FUNCTION_SEGMENT_2D_HPP_

#include <functional>
#include <Eigen/Dense>
#include "Empirical/domain/Domain2D.hpp"
#include "Empirical/Constants.hpp"

namespace Empirical {

class Quadrature;

class ComplexFunctionSegment2D : public DomainSegment2D {
 private:

  const cScalar offset;
  const cScalar scale;
  const std::function<cScalar(const cScalar)>& z_complex;
  const std::function<cScalar(const cScalar)>& z_complex_derivative;

  cScalar pointsFunc(const Scalar t) const;
  cScalar pointDerivativesFunc(const Scalar t) const;

 public:

  ComplexFunctionSegment2D(
      const std::function<cScalar(const cScalar)>& z_complex_func,
      const std::function<cScalar(const cScalar)>& z_complex_derivative_func,
      const int M, const cScalar offset = 0, const cScalar scale = 1);

  virtual ~ComplexFunctionSegment2D();
};

}

#endif /* EMPIRICAL_DOMAIN_FUNCTION_SEGMENT_2D_HPP_ */
