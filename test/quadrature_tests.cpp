#include <cmath>
#include "test.h"
#include "config.h"
#include "quadrature.h"

using namespace empirical;

typedef long double Scalar;

Scalar one(const Scalar x) {
  return x;
}

Scalar function(const Scalar x) {
  return x * sin(30 * x) + cos(5 * x);
}

Scalar function_integral(Scalar x) {
  return (-(1.0 / 30.0) * x * cos(30 * x) +
	  (1.0 / 5.0) * sin(5 * x) +
	  (1.0 / 900.0) * sin(30 * x));
}

const Scalar integration_value = function_integral(1) - function_integral(-1);
const int N = 250;

void test_quadrature(Quadrature<Scalar>& q, const Scalar zeroEps, const Scalar intEps) {
  CHECK_EQUAL(N, q.getN());
  CHECK_EQUAL(-1, q.getA());
  CHECK_EQUAL(1, q.getB());

  CHECK_CLOSE(0, q.integrate(&one), zeroEps);
  CHECK_CLOSE(integration_value, q.integrate(&function), intEps);
}

TEST(periodic_trapezoid_quadrature) {
  PeriodicTrapezoid<Scalar> pt(N);

  test_quadrature(pt, 1e-10, 1e-4);
}

TEST(trapezoid_quadrature) {
  TrapezoidQuadrature<Scalar> t(N);
  test_quadrature(t, 1e-10, 1e-3);
}

TEST(lgl_quadrature) {
  LegendreGaussLobatto<Scalar> lgl(N);
  test_quadrature(lgl, 1e-10, 1e-9);
}
