#ifndef EMPIRICAL_DOMAIN_RADIALSEGMENT_HPP_
#define EMPIRICAL_DOMAIN_RADIALSEGMENT_HPP_

#include <functional>
#include <Eigen/Dense>
#include "Empirical/src/domain/Domain2D.hpp"
#include "Empirical/src/config.h"

namespace empirical {

class Quadrature;

class RadialSegment2D : public DomainSegment2D {
 private:

  const std::function<cScalar(Scalar)>& radius;
  const std::function<cScalar(Scalar)>& radius_derivative;

  cScalar points(Scalar t) const;
  cScalar pointDerivative(Scalar t) const;

 public:

  RadialSegment2D(const std::function<cScalar(Scalar)>& radius_func,
                  const std::function<cScalar(Scalar)>& radius_derivative_func,
                  const int M);

  virtual ~RadialSegment2D();
};

}

#endif /* RADIALSEGMENT_HPP_ */
