#include "gtest/gtest.h"

#include <empiricalcpp/empirical.hpp>
#include <cmath>
#include <functional>

using namespace empirical;

namespace {
    class Mesh2DTest : public ::testing::Test {
    public:
        std::shared_ptr<Mesh2D> testMesh;
        mesh::MeshFunction calcX;
        mesh::MeshFunction calcY;
        std::size_t sizeX;
        std::size_t sizeY;

        void elementTest() {
            const Mesh2D& m = *testMesh.get();
            SCOPED_TRACE("elementTest");
            SCOPED_TRACE(m);
            EXPECT_EQ(size, m.mesh().size());
            for (std::size_t i = 0; i < sizeX; i++) {
                for (std::size_t j = 0; j < sizeY; j++) {
                    EXPECT_NEAR(calcX(i, size), m(i), epsScalar);
                    EXPECT_NEAR(calcY(j, size), m(i), epsScalar);
                }
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

    class QuadratureMesh1DTest : public Mesh1DTest {
    public:
        std::shared_ptr<Quadrature> quad;

        virtual void SetUp() {
            size = 25;
            quad = quadrature::legendreGaussLobatto(25);
            testMesh = mesh::createMesh(size, mesh::range(quad, -3, 5));

            const Quadrature* q = quad.get();
            const Mesh1D* m = testMesh.get();
            calc = [q, m](const std::size_t i, const std::size_t N)->Scalar {
                EXPECT_EQ(N, q->points.size());
                EXPECT_EQ(N, m->mesh().size());
                return 1.0 + 4.0 * q->points[i];
            };
        }
    };

    TEST_F(QuadratureMesh1DTest, elementTest) {
        SCOPED_TRACE("QuadratureMesh1DTest");
        elementTest();
    }

    TEST_F(QuadratureMesh1DTest, accessorsAreEquivalent) {
        SCOPED_TRACE("QuadratureMesh1DTest");
        accessorsAreEquivalent();
    }

    TEST_F(QuadratureMesh1DTest, resizeAlsoRecalculates) {
        SCOPED_TRACE("QuadratureMesh1DTest");
        resizeAlsoRecalculates();
    }

    TEST_F(QuadratureMesh1DTest, quadratureReferencesOriginalObject) {
        SCOPED_TRACE("QuadratureMesh1DTest");
        SCOPED_TRACE("quadratureReferencesOriginalObject");
        EXPECT_EQ(size, quad->points.size());
        const std::size_t original = size;
        resizeAlsoRecalculates();
        EXPECT_NE(original, size);
        EXPECT_EQ(size, quad->points.size());
    }
}
