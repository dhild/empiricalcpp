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

        Array<Scalar, Dynamic, 1> x = q.getPoints();
        Array<Scalar, Dynamic, 1> w = q.getWeights();

        TS_ASSERT(x.minCoeff() >= -1);
        TS_ASSERT(x.maxCoeff() <= 1);

        TS_ASSERT_DELTA(2.0, w.sum(), eps);
    }

    void test_integration(const Quadrature& q, Scalar (&func)(Scalar), const Scalar expected, const Scalar eps) {
        Array<Scalar, Dynamic, 1> x = q.getPoints();
        Array<Scalar, Dynamic, 1> evals = x.unaryExpr(ptr_fun(func));
        Array<Scalar, Dynamic, 1> mult = evals * q.getWeights();
        Scalar integrated = mult.sum();
        TS_ASSERT_DELTA(expected, integrated, eps);
    }

public:

    void testPeriodicTrapeziod() {
        {
            //Create
            PeriodicTrapezoidQuadrature quadrature(250);
            test_size(quadrature, 250, 1e-14);
        }
        {
            //Resize
            PeriodicTrapezoidQuadrature quadrature(250);
            quadrature.resize(300);
            test_size(quadrature, 300, 1e-14);
        }
        {
            //Integration of 1
            PeriodicTrapezoidQuadrature quadrature(250);
            test_integration(quadrature, one, 0, 1e-14);
        }
        {
            //Integration of sinusoid
            PeriodicTrapezoidQuadrature quadrature(250);
            test_integration(quadrature, sinusoid, sinusoid_integration_value, 1e-4);
        }
    }

    void testTrapezoidQuadrature() {
        {
            //Create
            TrapezoidQuadrature quadrature(250);
            test_size(quadrature, 250, 1e-2);
        }
        {
            //Resize
            TrapezoidQuadrature quadrature(250);
            quadrature.resize(300);
            test_size(quadrature, 300, 1e-2);
        }
        {
            //Integration of 1
            TrapezoidQuadrature quadrature(250);
            test_integration(quadrature, one, 0, 1e-10);
        }
        {
            //Integration of sinusoid
            TrapezoidQuadrature quadrature(250);
            test_integration(quadrature, sinusoid, sinusoid_integration_value, 1e-2);
        }
    }

    void testLegendreGaussLobatto() {
        {
            //Create
            LegendreGaussLobatto quadrature(250);
            test_size(quadrature, 250, 1e-15);
        }
        {
            //Resize
            LegendreGaussLobatto quadrature(250);
            quadrature.resize(300);
            test_size(quadrature, 300, 1e-15);
        }
        {
            //Integration of 1
            LegendreGaussLobatto quadrature(250);
            test_integration(quadrature, one, 0, 1e-16);
        }
        {
            //Integration of sinusoid
            LegendreGaussLobatto quadrature(250);
            test_integration(quadrature, sinusoid, sinusoid_integration_value, 1e-15);
        }
    }
};
