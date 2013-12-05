#include <cmath>
#include "test.h"
#include "config.h"
#include "quadrature.h"

using namespace empirical;

ScalarType function(ScalarType x) {
  return x * sin(30 * x) + cos(5 * x);
}

ScalarType function_integral(ScalarType x) {
  return (-(1.0 / 30.0) * x * cos(30 * x) +
	  (1.0 / 5.0) * sin(5 * x) +
	  (1.0 / 900.0) * sin(30 * x));
}

const ScalarType integration_value = function_integral(1) - function_integral(-1);
const IntegerType N = 250;

TEST(linear_quadrature) {
  Linear lin(N);

  CHECK_EQUAL(N, lin.getLength());
  CHECK_EQUAL(-1, lin.getA());
  CHECK_EQUAL(1, lin.getB());

  CHECK_CLOSE(integration_value, lin.integrate(&function), 1e-10);
}
