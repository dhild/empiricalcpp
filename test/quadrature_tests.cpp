#include <cmath>
#include "test.h"
#include "config.h"
#include "quadrature.h"

using namespace empirical;

double one(const double x) {
  return x;
}

double function(const double x) {
  return x * sin(30 * x) + cos(5 * x);
}

double function_integral(double x) {
  return (-(1.0 / 30.0) * x * cos(30 * x) +
	  (1.0 / 5.0) * sin(5 * x) +
	  (1.0 / 900.0) * sin(30 * x));
}

const double integration_value = function_integral(1) - function_integral(-1);
const unsigned long N = 250;

void test_quadrature(Quadrature& q, const double zeroEps, const double intEps) {
  CHECK_EQUAL(N, q.getN());
  CHECK_EQUAL(-1, q.getA());
  CHECK_EQUAL(1, q.getB());

  CHECK_CLOSE(0, q.integrate(&one), zeroEps);
  CHECK_CLOSE(integration_value, q.integrate(&function), intEps);
}

TEST(periodic_trapezoid_quadrature) {
  PeriodicTrapezoid pt(N);

  test_quadrature(pt, 1e-10, 1e-4);
}

TEST(trapezoid_quadrature) {
  TrapezoidQuadrature t(N);
  test_quadrature(t, 1e-10, 1e-3);
}

TEST(lgl_quadrature) {
  LegendreGaussLobatto lgl(N);
  test_quadrature(lgl, 1e-10, 1e-10);
}
