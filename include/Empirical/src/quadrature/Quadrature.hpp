#ifndef QUADRATURE_HPP_
#define QUADRATURE_HPP_

#include <utility>
#include <Eigen/Core>
#include "Empirical/src/config.h"

namespace empirical {

typedef Eigen::Array<Scalar, Eigen::Dynamic, 1> quadratureVector;

class Quadrature {
 protected:
  quadratureVector points;
  quadratureVector weights;

  Quadrature(const int N) : points(N), weights(N) {}

 public:

  int size() const {
    return points.rows();
  }

  const quadratureVector& getPoints() const {
    return points;
  }

  const quadratureVector& getWeights() const {
    return weights;
  }
};

class LegendreGaussLobatto : public Quadrature {
 public:
  LegendreGaussLobatto(const int N);
};

class TrapezoidQuadrature : public Quadrature {
 public:
  TrapezoidQuadrature(const int N);
};
}

#endif /* QUADRATURE_HPP_ */
