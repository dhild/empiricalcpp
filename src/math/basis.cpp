#include <cmath>
#include <complex>
#include "basis.h"
#include "config.h"

using namespace empirical;
using namespace Eigen;
using namespace std;

Basis::Basis(Quadrature& q) : q(q) {}

unsigned long Basis::size() const {
  return q.getN();
}

MFSBasis::MFSBasis(Quadrature& quadrature) : Basis(quadrature) {}

MFSBasis::~MFSBasis() {}

cdouble MFSBasis::hankel1(const double v, const cdouble z) const {
  return 1.0;
}

cdouble MFSBasis::evaluateHankel(const double k, const double r) const {
  if (k == 0) {
    return - log(r) / (2.0 * PI);
  }

  return cdouble(0.25j) * hankel1(0, k * r);
}

cdouble MFSBasis::evaluate(const double k, const double px, const double py, const double qx, const double qy) const {
  const double dx = px - qx;
  const double dy = py - qy;
  const double r = sqrt(dx * dx + dy * dy);

  return evaluateHankel(k, r);
}

Matrix<cdouble, Dynamic, Dynamic> Basis::getMatrix(const double k, const Quadrature& points) const {
  const unsigned long N = q.getN();
  const unsigned long M = points.getN();

  Matrix<cdouble, Dynamic, Dynamic> matrix;
  matrix.resize(M, N);

  for (int i = 0; i < M; i++) {
    const double px = points.getPoints()(i, 0);
    const double py = points.getPoints()(i, 1);

    for (int j = 0; j < N; j++) {
      const double qx = q.getPoints()(j, 0);
      const double qy = q.getPoints()(j, 1);

      matrix(i, j) = evaluate(k, px, py, qx, qy);
    }
  }
}
