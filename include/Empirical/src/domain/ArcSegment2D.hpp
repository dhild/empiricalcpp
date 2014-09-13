#ifndef EMPIRICAL_DOMAIN_ARCSEGMENT2D_HPP_
#define EMPIRICAL_DOMAIN_ARCSEGMENT2D_HPP_

#include <functional>
#include <Eigen/Dense>
#include "Empirical/src/domain/Domain2D.hpp"
#include "Empirical/src/config.h"

namespace empirical {

class Quadrature;

class ArcSegment2D : public DomainSegment2D {
 private:

  const cScalar center;
  const Scalar radius;
  const Scalar t0;
  const Scalar t1;

  cScalar points(Scalar t) const;
  cScalar pointDerivative(Scalar t) const;

 public:

  ArcSegment2D(const cScalar center, const Scalar R, const Scalar t0,
               const Scalar t1, const int M);

  virtual ~ArcSegment2D();
};

}

#endif /* EMPIRICAL_DOMAIN_ARCSEGMENT2D_HPP_ */
