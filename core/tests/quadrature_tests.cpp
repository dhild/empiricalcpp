#include <cmath>
#include <functional>
#include "test.h"
#include <Empirical/Quadrature>

using namespace std;
using namespace Eigen;
using namespace empirical;

Scalar one(Scalar x) {
  return x;
}

Scalar sinusoid(Scalar x) {
  return x * sin(30 * x) + cos(5 * x);
}

Scalar function_integral(Scalar x) {
  return (-(1.0 / 30.0) * x * cos(30 * x) +
           (1.0 / 5.0) * sin(5 * x) +
           (1.0 / 900.0) * sin(30 * x));
}

const Scalar sinusoid_integration_value = function_integral(1) - function_integral(-1);

void test_size(const Quadrature& q, const int N, const Scalar eps) {
  CHECK_EQUAL(N, q.size());

  Array<Scalar, Dynamic, 1> x = q.getPoints();
  Array<Scalar, Dynamic, 1> w = q.getWeights();

  CHECK(x.minCoeff() >= -1);
  CHECK(x.maxCoeff() <= 1);

  CHECK_CLOSE(2.0, w.sum(), eps);
}

void test_integration(const Quadrature& q, Scalar (&func)(Scalar), const Scalar expected, const Scalar eps) {
  Array<Scalar, Dynamic, 1> x = q.getPoints();
  Array<Scalar, Dynamic, 1> evals = x.unaryExpr(ptr_fun(func));
  Array<Scalar, Dynamic, 1> mult = evals * q.getWeights();
  Scalar integrated = mult.sum();
  CHECK_CLOSE(expected, integrated, eps);
}

#define TEST_QUADRATURE(Type, N, wEps, zeroEps, intEps)  \
  SUITE(Type ## _quadrature_suite) {                     \
    TEST(Type ## _createN) {                             \
      Type quadrature(N);                                \
      test_size(quadrature, N, wEps);                    \
    }                                                    \
    TEST(Type ## _resize) {                              \
      Type quadrature(N);                                \
      quadrature.resize(N + 50);                         \
      test_size(quadrature, N + 50, wEps);               \
    }                                                    \
    TEST(Type ## _integration_one) {                     \
      Type quadrature(N);                                \
      test_integration(quadrature, one, 0, zeroEps);     \
    }                                                    \
    TEST(Type ## _integration_sinusoid) {                \
      Type quadrature(N);                                \
      test_integration(quadrature, sinusoid,             \
                       sinusoid_integration_value,       \
                       intEps);                          \
    }                                                    \
  }

TEST_QUADRATURE(PeriodicTrapezoidQuadrature, 250, 1e-14, 1e-14, 1e-4);
TEST_QUADRATURE(TrapezoidQuadrature, 250, 1e-2, 1e-10, 1e-2);
TEST_QUADRATURE(LegendreGaussLobatto, 250, 1e-15, 1e-16, 1e-15);
