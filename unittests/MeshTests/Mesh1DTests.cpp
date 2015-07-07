#include "gtest/gtest.h"

#include <empiricalcpp/empirical.hpp>
#include <cmath>
#include <functional>

using namespace empirical;

namespace {
    class Mesh1DTest : public ::testing::Test {
    public:
        Mesh1D* testMesh;
        mesh::MeshFunction calc;
        std::size_t size;

        void elementTest() {
            const Mesh1D& m = *testMesh;
            SCOPED_TRACE("elementTest");
#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
            SCOPED_TRACE(m);
#endif
            EXPECT_EQ(size, m.mesh().size());
            for (std::size_t i = 0; i < size; i++) {
                EXPECT_NEAR(calc(i, size), m(i), epsScalar);
            }
        }

        void accessorsAreEquivalent() {
            const Mesh1D& m = *testMesh;
            SCOPED_TRACE("accessorsAreEquivalent");
#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
            SCOPED_TRACE(m);
#endif
            for (std::size_t i = 0; i < size; i++) {
                EXPECT_NEAR(calc(i, size), m(i), epsScalar);
                EXPECT_NEAR(calc(i, size), m[i], epsScalar);
                EXPECT_NEAR(calc(i, size), m.mesh()[i], epsScalar);
            }
        }

        void resizeAlsoRecalculates() {
            Mesh1D& m = *testMesh;
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

        virtual void TearDown() {
            delete testMesh;
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

        virtual void TearDown() {
            delete testMesh;
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
        Quadrature* quad;

        virtual void SetUp() {
            size = 25;
            quad = quadrature::legendreGaussLobatto(25);
            testMesh = mesh::createMesh(size, mesh::MeshQuadrature(quad, -3.0, 5.0));

            const Quadrature* q = quad;
            const Mesh1D* m = testMesh;
            calc = [q, m](const std::size_t i, const std::size_t N)->Scalar {
                EXPECT_EQ(N, q->points.size());
                EXPECT_EQ(N, m->mesh().size());
                return 1.0 + 4.0 * q->points[i];
            };
        }

        virtual void TearDown() {
            delete testMesh;
            delete quad;
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
        SCOPED_TRACE("resizeAlsoRecalculates");
        size += 25;
        quad->resize(size); // Necessary because this quadrature is not owned by the mesh.
        testMesh->resize(size);
        elementTest();

        size = 30;
        quad->resize(size); // Necessary because this quadrature is not owned by the mesh.
        testMesh->resize(size);
        elementTest();
    }

    TEST_F(QuadratureMesh1DTest, quadratureDoesNotReferenceOriginalObject) {
        SCOPED_TRACE("QuadratureMesh1DTest");
        SCOPED_TRACE("quadratureReferencesOriginalObject");
        testMesh->resize(size + 25);
        EXPECT_EQ(size, quad->points.size());
        EXPECT_EQ(size + 25, testMesh->mesh().size());
    }
}
