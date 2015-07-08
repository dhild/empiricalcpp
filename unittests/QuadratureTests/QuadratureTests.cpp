#include "gtest/gtest.h"

#undef EMPIRICAL_NO_OSTREAM_DEFINITIONS
#include <empiricalcpp/empirical.hpp>
#include <cmath>
#include <functional>

using namespace empirical;

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

    void test_size(const Quadrature& q, const Quadrature::size_type N) {
        SCOPED_TRACE("size test");
        SCOPED_TRACE(q);
        EXPECT_EQ(N, q.size());
        EXPECT_EQ(N, q.getPoints().size());
        EXPECT_EQ(N, q.getWeights().size());

        Scalar minX = q[0];
        Scalar maxX = minX;
        for (Scalar s : q) {
            if (s <= minX) {
                minX = s;
            }
            if (s >= maxX) {
                maxX = s;
            }
        }

        EXPECT_GE(minX, q.min());
        EXPECT_LE(maxX, q.max());

        auto weights = q.getWeights();
        Scalar sum = std::accumulate(weights.begin(), weights.end(), Scalar(0));
        Scalar size = q.max() - q.min();
        SCOPED_TRACE(size);
        EXPECT_NEAR(size, sum, N * epsScalar * size);
    }

    void test_constant_integration(const Quadrature& q, const Scalar eps) {
        SCOPED_TRACE("constant integration");
        SCOPED_TRACE(q);
        Scalar integrated = q.integrate(one);
        EXPECT_NEAR(0, integrated, eps);
    }

    void test_sinusoid_integration(const Quadrature& q, const Scalar eps) {
        SCOPED_TRACE("sinusoid integration");
        SCOPED_TRACE(q);
        Scalar integrated = q.integrate(sinusoid);
        EXPECT_NEAR(sinusoid_integration_value, integrated, eps);
    }

    void test_resize(Quadrature& q, const Scalar lowerBound = -1, const Scalar upperBound = 1) {
        Quadrature::size_type oldSize = q.size();
        Quadrature::size_type newSize = q.size() + 50;
        {
            SCOPED_TRACE("first resize tests");
            SCOPED_TRACE(q);
            q.resize(newSize, lowerBound, upperBound);
            test_size(q, newSize);
        }
        {
            SCOPED_TRACE("second resize tests");
            SCOPED_TRACE(q);
            q.resize(oldSize, lowerBound, upperBound);
            test_size(q, oldSize);
        }
    }
}

TEST(QuadratureTest, PeriodicTrapezoidTests) {
    SCOPED_TRACE("PeriodicTrapezoidTests");
    Quadrature quadrature = quadrature::periodicTrapezoid(250);
    test_size(quadrature, 250);
    test_constant_integration(quadrature, 1e-14);
    test_sinusoid_integration(quadrature, 1e-2);
    test_resize(quadrature, -1 + (1.0 / (2 * 300)), 1 - (1.0 / (2 * 300)));
    {
        SCOPED_TRACE("Resize 2, 3");
        test_resize(quadrature, 2, 3);
    }
    {
        SCOPED_TRACE("Resize -5, 10");
        test_resize(quadrature, -5, 10);
    }
}

TEST(QuadratureTest, TrapezoidTests) {
    SCOPED_TRACE("TrapezoidTests");
    Quadrature quadrature = quadrature::trapezoid(250);
    test_size(quadrature, 250);
    test_constant_integration(quadrature, 5e-5);
    test_sinusoid_integration(quadrature, 2e-2);
    test_resize(quadrature);
    {
        SCOPED_TRACE("Resize 2, 3");
        test_resize(quadrature, 2, 3);
    }
    {
        SCOPED_TRACE("Resize -5, 10");
        test_resize(quadrature, -5, 10);
    }
}

TEST(QuadratureTest, LegendreGaussLobattoTests) {
    SCOPED_TRACE("LegendreGaussLobattoTests");
    Quadrature quadrature = quadrature::legendreGaussLobatto(250);
    test_size(quadrature, 250);
    test_constant_integration(quadrature, 1e-16);
    test_sinusoid_integration(quadrature, 1e-15);
    test_resize(quadrature);
    {
        SCOPED_TRACE("Resize 2, 3");
        test_resize(quadrature, 2, 3);
    }
    {
        SCOPED_TRACE("Resize -5, 10");
        test_resize(quadrature, -5, 10);
    }
}
