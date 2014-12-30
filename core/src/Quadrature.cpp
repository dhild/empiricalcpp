#include "Empirical/Quadrature.hpp"
#include <functional>

using namespace Empirical;
using namespace Eigen;
using namespace std;

Quadrature::~Quadrature() {}

void Quadrature::resize(const int N) {
  points.resize(N, 1);
  weights.resize(N, 1);
}

TrapezoidQuadrature::TrapezoidQuadrature(const int N) : Quadrature(N) {
  recalc(N);
}

TrapezoidQuadrature::~TrapezoidQuadrature() {}

void TrapezoidQuadrature::resize(const int N) {
  if (N == size()) {
    return;
  }
  Quadrature::resize(N);
  recalc(N);
}

void TrapezoidQuadrature::recalc(const int N) {
  points.setLinSpaced(-1, 1);

  Scalar w = Scalar(1) / Scalar(N);
  weights.setConstant(2 * w);
  weights(0, 0) = w;
  weights(N - 1, 0) = w;
}

PeriodicTrapezoidQuadrature::PeriodicTrapezoidQuadrature(const int N) : Quadrature(N) {
  recalc(N);
}

PeriodicTrapezoidQuadrature::~PeriodicTrapezoidQuadrature() {}

void PeriodicTrapezoidQuadrature::resize(const int N) {
  if (N == size()) {
    return;
  }
  Quadrature::resize(N);
  recalc(N);
}

void PeriodicTrapezoidQuadrature::recalc(const int N) {
  Scalar shift = Scalar(1) / Scalar(N);
  points.setLinSpaced(-1 + shift, 1 - shift);

  weights.setConstant(Scalar(2) / Scalar(N));
}

LegendreGaussLobatto::LegendreGaussLobatto(const int N1) : Quadrature(N1) {
  recalc(N1);
}

LegendreGaussLobatto::~LegendreGaussLobatto() {}

void LegendreGaussLobatto::resize(const int N) {
  if (N == size()) {
    return;
  }
  Quadrature::resize(N);
  recalc(N);
}

void LegendreGaussLobatto::recalc(const int N1) {
  const int N = N1 - 1;
  
  Array<Scalar, Dynamic, 1> x = Array<Scalar, Dynamic, 1>::LinSpaced(N1, 0, PI).cos();
  Array<Scalar, Dynamic, 1> xold = Array<Scalar, Dynamic, 1>::Constant(N1, 1, Scalar(2));
  Array<Scalar, Dynamic, Dynamic> P = Array<Scalar, Dynamic, Dynamic>::Zero(N1, N1);

  while ((x - xold).abs().maxCoeff() > epsScalar) {
    xold = x;
    P.col(0).setOnes();
    P.col(1) = x;

    for (int k = 2; k < N1; k++) {
      P.col(k) = (Scalar(2 * k - 1) * x * P.col(k - 1) - Scalar(k - 1) * P.col(k - 2)) / Scalar(k);
    }
    x = xold - (x * P.col(N) - P.col(N - 1)) / (Scalar(N1) * P.col(N));
  }

  // Populate x2 with the weights.
  xold = Scalar(2.0) / (Scalar(N) * Scalar(N1) * P.col(N).square());

  // Reverse the arrays and store them.
  this->points = x.reverse();
  this->weights = xold.reverse();
}
