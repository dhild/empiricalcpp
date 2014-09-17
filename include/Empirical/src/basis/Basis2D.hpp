#ifndef EIGEN_BASIS_BASIS_HPP_
#define EIGEN_BASIS_BASIS_HPP_

#include <functional>
#include <Eigen/Dense>
#include "Empirical/src/config.h"
#include "Empirical/src/domain/Domain2D.hpp"

namespace empirical {

typedef Eigen::Matrix<cScalar, Eigen::Dynamic, Eigen::Dynamic> Mesh2D;

class Basis2D {

 public:

  virtual ~Basis2D() = 0;

  virtual int size() const = 0;

  virtual cScalar basis(const Scalar k, const cScalar z, const cScalar x) const = 0;
  virtual cScalar basisNormalDerivative(const Scalar k, const cScalar z,
                                        const cScalar x) const = 0;

  virtual Mesh1D basis(const Scalar k, const cScalar z) const = 0;
  virtual Mesh1D basisNormalDerivative(const Scalar k, const cScalar z) const = 0;

  virtual Mesh2D basis(const Scalar k, const Mesh1D& z) const = 0;
  virtual Mesh2D basisNormalDerivative(const Scalar k, const Mesh1D& z) const = 0;

};

}

#endif /* EIGEN_BASIS_BASIS_HPP_ */
