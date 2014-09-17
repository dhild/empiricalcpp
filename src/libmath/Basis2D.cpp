#include "Empirical/src/basis/MFSBasis2D.hpp"
#include <boost/math/special_functions/bessel.hpp>
#include <functional>

using namespace Eigen;
using namespace boost::math;
using namespace empirical;

namespace empirical {

/** Evaluates the Hankel function. */
cScalar hankel(const Scalar v, const Scalar x) {
  return cyl_bessel_j(v, x) + cScalar(0, 1) * cyl_neumann(v, x);
}

cScalar mfsBasis(const Scalar k, const cScalar dist) {
  if (k == 0) {
    return -log(abs(dist)) / (2 * PI);
  }
  return cScalar(0, 0.25) * hankel(0, k * abs(dist));
}

cScalar mfsBasisNormalDerivative(const Scalar k, const cScalar dist) {
  if (k == 0) {
    return -1 / (2 * PI * abs(dist));
  }
  return cScalar(-k, 0.25) * hankel(1, k * abs(dist));
}

}

MFSBasis2D::MFSBasis2D(const Mesh1D& points)
    : charge_points(points) {}

MFSBasis2D::~MFSBasis2D() {}

int MFSBasis2D::size() const {
  return charge_points.rows();
}

cScalar MFSBasis2D::basis(const Scalar k, const cScalar z, const cScalar x) const {
  return mfsBasis(k, z - x);
}

cScalar MFSBasis2D::basisNormalDerivative(const Scalar k, const cScalar z,
                                          const cScalar x) const {
  return mfsBasisNormalDerivative(k, z - x);
}

Mesh1D MFSBasis2D::basis(const Scalar k, const cScalar z) const {
  Mesh1D dist = Mesh1D::Constant(charge_points.rows(), 1, z) - charge_points;
  
  auto func = std::bind(mfsBasis, k, std::placeholders::_1);
  return dist.unaryExpr(func);
}

Mesh1D MFSBasis2D::basisNormalDerivative(const Scalar k, const cScalar z) const {
  Mesh1D dist = Mesh1D::Constant(charge_points.rows(), 1, z) - charge_points;

  auto func = std::bind(mfsBasisNormalDerivative, k, std::placeholders::_1);
  return dist.unaryExpr(func);
}

Mesh2D MFSBasis2D::basis(const Scalar k, const Mesh1D& z) const {
  const int M = z.rows();
  const int N = charge_points.rows();
  Mesh2D dist = charge_points.transpose().replicate(M, 1) - z.replicate(1, N);
  auto func = std::bind(mfsBasis, k, std::placeholders::_1);
  return dist.unaryExpr(func);
}

Mesh2D MFSBasis2D::basisNormalDerivative(const Scalar k, const Mesh1D& z) const {
  const int M = z.rows();
  const int N = charge_points.rows();
  Mesh2D dist = charge_points.transpose().replicate(M, 1) - z.replicate(1, N);
  auto func = std::bind(mfsBasisNormalDerivative, k, std::placeholders::_1);
  return dist.unaryExpr(func);
}
