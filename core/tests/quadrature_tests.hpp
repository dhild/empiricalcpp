#include <Empirical/Quadrature.hpp>
#include <cxxtest/TestSuite.h>
#include <cmath>
#include <functional>

using namespace std;
using namespace Eigen;
using namespace Empirical;

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

class QuadratureTests : public CxxTest::TestSuite {
private:
    void test_size(const Quadrature& q, const int N, const Scalar eps) {
        TS_ASSERT_EQUALS(N, q.size());

        Vector x = q.getPoints();
        Vector w = q.getWeights();

        TS_ASSERT(x.minCoeff() >= -1);
        TS_ASSERT(x.maxCoeff() <= 1);

        TS_ASSERT_DELTA(2.0, w.sum(), eps);
    }

    void test_integration(const Quadrature& q, Scalar (&func)(Scalar), const Scalar expected, const Scalar eps) {
        Vector x = q.getPoints();
        Vector evals = x.unaryExpr(ptr_fun(func));
        Vector mult = evals.array() * q.getWeights().array();
        Scalar integrated = mult.sum();
        TS_ASSERT_DELTA(expected, integrated, eps);
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

public:

    void testPeriodicTrapeziod() {
        testCreation(&createPeriodicTrapezoid, 1e-14);
        testResize(&createPeriodicTrapezoid, 1e-14);
        testIntegration1(&createPeriodicTrapezoid, 1e-14);
        testIntegration2(&createPeriodicTrapezoid, 1e-4);
    }

    void testTrapezoidQuadrature() {
        testCreation(&createTrapezoid, 1e-2);
        testResize(&createTrapezoid, 1e-2);
        testIntegration1(&createTrapezoid, 1e-10);
        testIntegration2(&createTrapezoid, 1e-2);
    }

    void testLegendreGaussLobatto() {
        testCreation(&createLGL, 1e-15);
        testResize(&createLGL, 1e-15);
        testIntegration1(&createLGL, 1e-16);
        testIntegration2(&createLGL, 1e-15);
    }
};
