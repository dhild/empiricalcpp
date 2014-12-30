#ifndef EMPIRICAL_DOMAIN_RADIALSEGMENT_HPP_
#define EMPIRICAL_DOMAIN_RADIALSEGMENT_HPP_

#include <functional>
#include <Eigen/Dense>
#include "Empirical/domain/Domain2D.hpp"
#include "Empirical/Constants.hpp"

namespace Empirical {

class Quadrature;

class RadialSegment2D : public DomainSegment2D {
 private:

  const std::function<cScalar(const Scalar)> radius;
  const std::function<cScalar(const Scalar)> radius_derivative;

  cScalar pointsFunc(const Scalar t) const;
  cScalar pointDerivativesFunc(const Scalar t) const;

 public:

  RadialSegment2D(const std::function<cScalar(const Scalar)>& radius_func,
                  const std::function<cScalar(const Scalar)>&
                  radius_derivative_func,
                  const int M);

  virtual ~RadialSegment2D();
};

}

#endif /* RADIALSEGMENT_HPP_ */
