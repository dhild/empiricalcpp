#include "gtest/gtest.h"

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

    void test_size(const Quadrature& q, const std::size_t N, const Scalar lowerBound = -1, const Scalar upperBound = 1) {
        SCOPED_TRACE("size test");
        SCOPED_TRACE(q);
        EXPECT_EQ(N, q.points.size());
        EXPECT_EQ(N, q.weights.size());

        Scalar minX = q.points[0];
        Scalar maxX = minX;
        for (Scalar s : q.points) {
            if (s <= minX) {
                minX = s;
            }
            if (s >= maxX) {
                maxX = s;
            }
        }

        EXPECT_TRUE(minX >= lowerBound);
        EXPECT_TRUE(maxX <= upperBound);

        Scalar sum = 0;
        for (Scalar s : q.weights) {
            sum += s;
        }

        EXPECT_NEAR(2.0, sum, N * epsScalar);
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
        std::size_t oldSize = q.points.size();
        std::size_t newSize = q.points.size() + 50;
        {
            SCOPED_TRACE("first resize tests");
            SCOPED_TRACE(q);
            q.resize(newSize);
            test_size(q, newSize, lowerBound, upperBound);
        }
        {
            SCOPED_TRACE("second resize tests");
            SCOPED_TRACE(q);
            q.resize(oldSize);
            test_size(q, oldSize, lowerBound, upperBound);
        }
    }

    void test_clone(Quadrature& q) {
        SCOPED_TRACE("clone tests");
        SCOPED_TRACE(q);
        std::unique_ptr<Quadrature> cloned(q.clone());
        std::size_t oldSize = q.points.size();
        std::size_t newSize = oldSize - 5;
        q.resize(newSize);
        EXPECT_NE(q.points.size(), cloned->points.size());
    }
}

TEST(QuadratureTest, PeriodicTrapezoidTests) {
    SCOPED_TRACE("PeriodicTrapezoidTests");
    Quadrature* quadrature = quadrature::periodicTrapezoid(250);
    test_size(*quadrature, 250, -1 + (1.0 / (2 * 250)), 1 - (1.0 / (2 * 250)));
    test_constant_integration(*quadrature, 1e-14);
    test_sinusoid_integration(*quadrature, 1e-2);
    test_resize(*quadrature, -1 + (1.0 / (2 * 300)), 1 - (1.0 / (2 * 300)));
    test_clone(*quadrature);
}

TEST(QuadratureTest, TrapezoidTests) {
    SCOPED_TRACE("TrapezoidTests");
    Quadrature* quadrature = quadrature::trapezoid(250);
    test_size(*quadrature, 250);
    test_constant_integration(*quadrature, 5e-5);
    test_sinusoid_integration(*quadrature, 2e-2);
    test_resize(*quadrature);
    test_clone(*quadrature);
}

TEST(QuadratureTest, LegendreGaussLobattoTests) {
    SCOPED_TRACE("LegendreGaussLobattoTests");
    Quadrature* quadrature = quadrature::legendreGaussLobatto(250);
    test_size(*quadrature, 250);
    test_constant_integration(*quadrature, 1e-16);
    test_sinusoid_integration(*quadrature, 1e-15);
    test_resize(*quadrature);
    test_clone(*quadrature);
}
