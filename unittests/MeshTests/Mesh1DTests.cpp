#include "gtest/gtest.h"

#include <empiricalcpp/empirical.hpp>
#include <cmath>
#include <functional>

using namespace empirical;

namespace {
    class Mesh1DTest : public ::testing::Test {
    public:
        std::shared_ptr<Mesh1D> testMesh;
        mesh::MeshFunction calc;
        std::size_t size;

        void elementTest() {
            const Mesh1D& m = *testMesh.get();
            SCOPED_TRACE("elementTest");
            SCOPED_TRACE(m);
            EXPECT_EQ(size, m.mesh().size());
            for (std::size_t i = 0; i < size; i++) {
                EXPECT_NEAR(calc(i, size), m(i), epsScalar);
            }
        }

        void accessorsAreEquivalent() {
            const Mesh1D& m = *testMesh.get();
            SCOPED_TRACE("accessorsAreEquivalent");
            SCOPED_TRACE(m);
            for (std::size_t i = 0; i < size; i++) {
                EXPECT_NEAR(calc(i, size), m(i), epsScalar);
                EXPECT_NEAR(calc(i, size), m[i], epsScalar);
                EXPECT_NEAR(calc(i, size), m.mesh()[i], epsScalar);
            }
        }

        void resizeAlsoRecalculates() {
            Mesh1D& m = *testMesh.get();
            SCOPED_TRACE("resizeAlsoRecalculates");
            size += 25;
            m.resize(size);
            elementTest();

            size = 30;
            m.resize(size);
            elementTest();
        }
    };

    Scalar linear(const std::size_t i, const std::size_t N) {
        return Scalar(i) / N;
    }

    class FunctionMesh1DTest : public Mesh1DTest {
    public:
        virtual void SetUp() {
            size = 25;
            calc = linear;
            testMesh = mesh::createMesh(size, linear);
        }
    };

    TEST_F(FunctionMesh1DTest, elementTest) {
        SCOPED_TRACE("FunctionMesh1DTest");
        elementTest();
    }

    TEST_F(FunctionMesh1DTest, accessorsAreEquivalent) {
        SCOPED_TRACE("FunctionMesh1DTest");
        accessorsAreEquivalent();
    }

    TEST_F(FunctionMesh1DTest, resizeAlsoRecalculates) {
        SCOPED_TRACE("FunctionMesh1DTest");
        resizeAlsoRecalculates();
    }

    Scalar rangeFunction(const std::size_t i, const std::size_t N) {
        return ((8 * Scalar(i)) / N) - 3;
    }

    class RangeMesh1DTest : public Mesh1DTest {
    public:
        virtual void SetUp() {
            size = 25;
            calc = rangeFunction;
            testMesh = mesh::createMesh(size, mesh::range(-3, 5));
        }
    };

    TEST_F(RangeMesh1DTest, elementTest) {
        SCOPED_TRACE("RangeMesh1DTest");
        elementTest();
    }

    TEST_F(RangeMesh1DTest, accessorsAreEquivalent) {
        SCOPED_TRACE("RangeMesh1DTest");
        accessorsAreEquivalent();
    }

    TEST_F(RangeMesh1DTest, resizeAlsoRecalculates) {
        SCOPED_TRACE("RangeMesh1DTest");
        resizeAlsoRecalculates();
    }
}
