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

  const std::function<cScalar(Scalar)>& z;
  const std::function<cScalar(Scalar)>& zPrime;

  Quadrature* t;
  Mesh1D points;
  Mesh1D pointPrimes;
  Mesh1D normals;

  void recalculate(const int M);

 public:

  RadialSegment2D(const std::function<cScalar(Scalar)>& z,
                  const std::function<cScalar(Scalar)>& zPrime,
                  const int M);

  virtual ~RadialSegment2D();

  virtual void recalculateQuadratures(const int M);
  
  virtual int size() const;
  virtual const Quadrature& getT() const;
  virtual const Mesh1D& getPoints() const;
  virtual const Mesh1D& getPointDerivatives() const;
  virtual const Mesh1D& getNormals() const;
};

}

#endif /* RADIALSEGMENT_HPP_ */
