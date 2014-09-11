#include <functional>
#include <Empirical/Quadrature>

using namespace empirical;
using namespace Eigen;
using namespace std;

TrapezoidQuadrature::TrapezoidQuadrature(const int N) : Quadrature(N) {
  this->points.setLinSpaced(-1, 1);

  Scalar w = Scalar(1) / Scalar(N);
  this->weights.setConstant(2 * w);
  this->weights(0, 0) = w;
  this->weights(N - 1, 0) = w;
}

LegendreGaussLobatto::LegendreGaussLobatto(const int N1) : Quadrature(N1) {
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
