#include <Empirical/Quadrature.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <cmath>
#include <functional>

using namespace std;
using namespace Eigen;
using namespace Empirical;

namespace {
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
    BOOST_CHECK_EQUAL(N, q.size());

    Vector x = q.getPoints();
    Vector w = q.getWeights();

    BOOST_CHECK(x.minCoeff() >= -1);
    BOOST_CHECK(x.maxCoeff() <= 1);

    BOOST_CHECK_CLOSE(2.0, w.sum(), eps);
}

void test_integration(const Quadrature& q, Scalar (&func)(Scalar), const Scalar expected, const Scalar eps) {
    Vector x = q.getPoints();
    Vector evals = x.unaryExpr(ptr_fun(func));
    Vector mult = evals.array() * q.getWeights().array();
    Scalar integrated = mult.sum();
    BOOST_CHECK_CLOSE(expected, integrated, eps);
}

void testCreation(QuadratureFunc qfunc, const Scalar tolerance) {
    Quadrature* q = qfunc(250);
    test_size(*q, 250, tolerance);
    delete q;
}

void testResize(QuadratureFunc qfunc, const Scalar tolerance) {
    Quadrature* q = qfunc(250);
    q->resize(300);
    test_size(*q, 300, tolerance);
    delete q;
}

void testIntegration1(QuadratureFunc qfunc, const Scalar tolerance) {
    Quadrature* q = qfunc(250);
    test_integration(*q, one, 0, tolerance);
    delete q;
}

void testIntegration2(QuadratureFunc qfunc, const Scalar tolerance) {
    Quadrature* q = qfunc(250);
    test_integration(*q, sinusoid, sinusoid_integration_value, tolerance);
    delete q;
}

BOOST_AUTO_TEST_CASE( PeriodicTrapezoid ) {
    testCreation(&createPeriodicTrapezoid, 1e-14);
    testResize(&createPeriodicTrapezoid, 1e-14);
    testIntegration1(&createPeriodicTrapezoid, 1e-14);
    testIntegration2(&createPeriodicTrapezoid, 1e-4);
}

BOOST_AUTO_TEST_CASE( TrapezoidQuadrature ) {
    testCreation(&createTrapezoid, 1e-2);
    testResize(&createTrapezoid, 1e-2);
    testIntegration1(&createTrapezoid, 1e-10);
    testIntegration2(&createTrapezoid, 1e-2);
}

BOOST_AUTO_TEST_CASE( LegendreGaussLobatto ) {
    testCreation(&createLGL, 1e-15);
    testResize(&createLGL, 1e-15);
    testIntegration1(&createLGL, 1e-16);
    testIntegration2(&createLGL, 1e-15);
}
}
