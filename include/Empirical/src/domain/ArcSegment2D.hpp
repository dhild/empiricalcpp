#ifndef EMPIRICAL_DOMAIN_ARCSEGMENT2D_HPP_
#define EMPIRICAL_DOMAIN_ARCSEGMENT2D_HPP_

#include <functional>
#include <Eigen/Dense>
#include "Empirical/src/domain/Domain2D.hpp"
#include "Empirical/src/config.h"

namespace empirical {

class Quadrature;

class ArcSegment2D : public ArcSegment2D {
 private:

  const std::function<cScalar(Scalar)>& z;
  const std::function<cScalar(Scalar)>& zPrime;

  Quadrature* t;
  Mesh1D points;
  Mesh1D pointPrimes;
  Mesh1D normals;

  void recalculate(const int M);

 public:

  ArcSegment2D(const std::function<cScalar(Scalar)>& z,
                  const std::function<cScalar(Scalar)>& zPrime,
                  const int M);

  virtual ~ArcSegment2D();

  virtual void recalculateQuadratures(const int M);
  
  virtual int size() const;
  virtual const Quadrature& getT() const;
  virtual const Mesh1D& getPoints() const;
  virtual const Mesh1D& getPointDerivatives() const;
  virtual const Mesh1D& getNormals() const;
};

}

#endif /* EMPIRICAL_DOMAIN_ARCSEGMENT2D_HPP_ */
