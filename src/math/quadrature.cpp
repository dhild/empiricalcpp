#include "config.h"
#include "quadrature.h"

using namespace empirical;
using namespace Eigen;

Quadrature::Quadrature(const unsigned long N, const double a, const double b) : N(N), a(a), b(b), x(), w() {
  x.resize(N);
  w.resize(N);
}

Quadrature::~Quadrature() {
}

void Quadrature::update(const unsigned long N) {
  update(N, a, b);
}

void Quadrature::update(const double a, const double b) {
  update(N, a, b);
}

void Quadrature::update(const unsigned long N, const double a, const double b) {
  this->N = N;
  this->a = a;
  this->b = b;
  x.resize(N);
  w.resize(N);
  recalc();
}

double Quadrature::integrate(double (*f)(const double)) const {
  double_t sum = 0;

  for (int i = 0; i < N; i++) {
    sum += f(x(i)) * w(i);
  }

  return sum;
}

PeriodicTrapezoid::PeriodicTrapezoid(const unsigned long N, const double a, const double b) : Quadrature(N, a, b) {
  recalc();
}

void PeriodicTrapezoid::recalc() {
  const double dist = b - a;
  const double shift = dist / (2 * N);

  const double x0 = a + shift;
  const double x1 = b - shift;

  const double delta = (x1 - x0) / double(N - 1);

  for (int i = 0; i < N; i++) {
    x(i) = x0 + i * delta;
    w(i) = delta;
  }
}

TrapezoidQuadrature::TrapezoidQuadrature(const unsigned long N, const double a, const double b) : Quadrature(N, a, b) {
  recalc();
}

void TrapezoidQuadrature::recalc() {
  const double dist = b - a;
  const double delta = dist / (N - 1);

  for (int i = 0; i < N; i++) {
    x(i) = a + i * delta;
    w(i) = delta;
  }

  w(0) *= 0.5;
  w(N - 1) *= 0.5;
}

LegendreGaussLobatto::LegendreGaussLobatto(const unsigned long N, const double a, const double b) : Quadrature(N, a, b) {
  recalc();
}

void LegendreGaussLobatto::recalc() {
  ArrayXd x1;
  ArrayXd x2;
  ArrayXXd P;

  x1.resize(N, 1);
  x2.resize(N, 1);
  P.resize(N, N);

  for (int i = 0; i < N; i++) {
    x1(i) = PI * i / double(N - 1);
  }

  x1 = x1.cos();
  x2.array().setConstant(2);
  P.array().setZero();

  while ((x1 - x2).abs().maxCoeff() > (1e-15)) {
    x2 = x1;
    P.col(0).setOnes();
    P.col(1) = x1;

    for (int k = 2; k < N; k++) {
      P.col(k) = (double(2 * k - 1) * x1 * P.col(k-1) -
		  double(k-1) * P.col(k-2)) / double(k);
    }
    x1 = x2 - (x1 * P.col(N-1) - P.col(N-2)) / (double(N) * P.col(N-1));
  }

  // Populate x2 with the weights.
  x2 = 2.0 / ((N-1) * double(N) * P.col(N-1).square());

  // Reverse the arrays and store them.
  for (int i = 0; i < N; i++) {
    x(N-i-1) = x1(i);
    w(N-i-1) = x2(i);
  }
}
