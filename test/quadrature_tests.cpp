#include <cmath>
#include "test.h"
#include <Empirical/Quadrature>

using namespace Eigen;
using namespace empirical;

Scalar one(const Scalar x) {
    return x;
}

Scalar function(const Scalar x) {
    return x * sin(30 * x) + cos(5 * x);
}

Scalar function_integral(const Scalar x) {
    return (-(1.0 / 30.0) * x * cos(30 * x) + //
            (1.0 / 5.0) * sin(5 * x) + //
            (1.0 / 900.0) * sin(30 * x));
}

const Scalar integration_value = function_integral(1) - function_integral(-1);
const int N = 250;

void test_size(const Quadrature& q, const int N, const Scalar a, const Scalar b) {
    CHECK_EQUAL(N, q.getN());
    CHECK_EQUAL(a, q.getA());
    CHECK_EQUAL(b, q.getB());

    Array<Scalar, Dynamic, 1> x = q.getPoints();
    Array<Scalar, Dynamic, 1> w = q.getPoints();

    CHECK(x.minCoeff() >= a);
    CHECK(x.maxCoeff() >= a);

    CHECK(x.minCoeff() <= b);
    CHECK(x.maxCoeff() <= b);

    CHECK(x.minCoeff() < x.maxCoeff());

    CHECK(w.minCoeff() < w.maxCoeff());
}

void test_update(Quadrature& q) {
    q.update(N, -1, 1);
    test_size(q, N, -1, 1);

    q.update(N + 25);
    test_size(q, N + 25, -1, 1);

    q.update(-1.2, 5);
    test_size(q, N + 25, -1.2, 5);

    q.update(N, 2.2, 2.5);
    test_size(q, N, 2.2, 2.5);
}

void test_integration(Quadrature& q, const Scalar zeroEps, const Scalar intEps) {
    q.update(N, -1, 1);
    CHECK_CLOSE(0, q.integrate(&one), zeroEps);
    CHECK_CLOSE(integration_value, q.integrate(&function), intEps);
}

#define TEST_QUADRATURE(Type, zeroEps, intEps) \
  SUITE(Type ## _quadrature_suite) { \
      TEST(Type ## _createNAB) { \
          Type quadrature(N, -2.2, 2.5);\
          test_size(quadrature, N, -2.2, 2.5);\
      }\
      TEST(Type ## _updateNAB) { \
          Type quadrature(N, -1, 1);\
          quadrature.update(N + 5, 2.2, 2.5);\
          test_size(quadrature, N + 5, 2.2, 2.5);\
      }\
      TEST(Type ## _updateAB) { \
          Type quadrature(N, -1, 1);\
          quadrature.update(-1.2, 5);\
          test_size(quadrature, N, -1.2, 5);\
      }\
      TEST(Type ## _updateN) { \
          Type quadrature(N, -1, 1);\
          quadrature.update(N + 25);\
          test_size(quadrature, N + 25, -1, 1);\
      }\
      TEST(Type ## _integration_one) {\
          Type quadrature(N, -1, 1);\
          CHECK_CLOSE(integration_value, quadrature.integrate(&function), intEps);\
      }\
      TEST(Type ## _integration_complicated) {\
          Type quadrature(N, -1, 1);\
          CHECK_CLOSE(integration_value, quadrature.integrate(&function), intEps);\
      }\
  }

TEST_QUADRATURE(PeriodicTrapezoid, 1e-10, 1e-4);
TEST_QUADRATURE(TrapezoidQuadrature, 1e-10, 1e-3);
TEST_QUADRATURE(LegendreGaussLobatto, 1e-10, 1e-9);
