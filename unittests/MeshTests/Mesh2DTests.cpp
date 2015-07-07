#include "gtest/gtest.h"

#include <empiricalcpp/empirical.hpp>
#include <cmath>
#include <functional>

using namespace empirical;

namespace {
    class Mesh2DTest : public ::testing::Test {
    public:
        Mesh2D* testMesh;
        mesh::MeshFunction calcX;
        mesh::MeshFunction calcY;
        std::size_t sizeX;
        std::size_t sizeY;

        void elementTest() {
            const Mesh2D& m = *testMesh;
            SCOPED_TRACE("elementTest");
#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
            SCOPED_TRACE(m);
#endif
            EXPECT_EQ(sizeX, m.mesh().shape()[0]);
            EXPECT_EQ(sizeY, m.mesh().shape()[1]);
            EXPECT_EQ(2, m.mesh().shape()[2]);
            for (std::size_t i = 0; i < sizeX; i++) {
                for (std::size_t j = 0; j < sizeY; j++) {
                    ASSERT_NEAR(calcX(i, sizeX), m(i, j, 0), epsScalar);
                    ASSERT_NEAR(calcY(j, sizeY), m(i, j, 1), epsScalar);
                }
            }
        }

        void accessorsAreEquivalent() {
            const Mesh2D& m = *testMesh;
            SCOPED_TRACE("accessorsAreEquivalent");
#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
            SCOPED_TRACE(m);
#endif
            for (std::size_t i = 0; i < sizeX; i++) {
                for (std::size_t j = 0; j < sizeY; j++) {
                    ASSERT_NEAR(calcX(i, sizeX), m(i, j, 0), epsScalar);
                    ASSERT_NEAR(calcX(i, sizeX), m.mesh()[i][j][0], epsScalar);
                    ASSERT_NEAR(calcY(j, sizeY), m(i, j, 1), epsScalar);
                    ASSERT_NEAR(calcY(j, sizeY), m.mesh()[i][j][1], epsScalar);
                }
            }
        }

        void resizeAlsoRecalculates() {
            Mesh2D& m = *testMesh;
            SCOPED_TRACE("resizeAlsoRecalculates");
            sizeX += 5;
            sizeY -= 5;
            m.resize(sizeX, sizeY);
            elementTest();

            sizeX = 5;
            sizeY = 5;
            m.resize(sizeX, sizeY);
            elementTest();
        }
    };

    Scalar linear(const std::size_t i, const std::size_t N) {
        return Scalar(i) / N;
    }
    Scalar squared(const std::size_t i, const std::size_t) {
        return Scalar(i) * Scalar(i);
    }

    class FunctionMesh2DTest : public Mesh2DTest {
    public:
        virtual void SetUp() {
            sizeX = 15;
            sizeY = 15;
            calcX = linear;
            calcY = squared;
            testMesh = mesh::createMesh(sizeX, calcX, sizeY, calcY);
        }
    };

    TEST_F(FunctionMesh2DTest, elementTest) {
        SCOPED_TRACE("FunctionMesh2DTest");
        elementTest();
    }

    TEST_F(FunctionMesh2DTest, accessorsAreEquivalent) {
        SCOPED_TRACE("FunctionMesh2DTest");
        accessorsAreEquivalent();
    }

    TEST_F(FunctionMesh2DTest, resizeAlsoRecalculates) {
        SCOPED_TRACE("FunctionMesh2DTest");
        resizeAlsoRecalculates();
    }

    Scalar rangeFunctionX(const std::size_t i, const std::size_t N) {
        return ((8 * Scalar(i)) / N) - 3;
    }

    Scalar rangeFunctionY(const std::size_t i, const std::size_t N) {
        return ((2 * Scalar(i)) / N) + 0.5;
    }

    class RangeMesh2DTest : public Mesh2DTest {
    public:
        virtual void SetUp() {
            sizeX = 15;
            sizeY = 15;
            calcX = rangeFunctionX;
            calcY = rangeFunctionY;
            testMesh = mesh::createMesh(sizeX, mesh::range(-3, 5), sizeY, mesh::range(0.5, 2.5));
        }
    };

    TEST_F(RangeMesh2DTest, elementTest) {
        SCOPED_TRACE("RangeMesh2DTest");
        elementTest();
    }

    TEST_F(RangeMesh2DTest, accessorsAreEquivalent) {
        SCOPED_TRACE("RangeMesh2DTest");
        accessorsAreEquivalent();
    }

    TEST_F(RangeMesh2DTest, resizeAlsoRecalculates) {
        SCOPED_TRACE("RangeMesh2DTest");
        resizeAlsoRecalculates();
    }

    class QuadratureMesh2DTest : public Mesh2DTest {
    public:
        Quadrature* quadX;
        Quadrature* quadY;

        virtual void SetUp() {
            sizeX = 15;
            sizeY = 15;
            quadX = quadrature::legendreGaussLobatto(15);
            quadY = quadrature::trapezoid(15);
            testMesh = mesh::createMesh(sizeX, mesh::MeshQuadrature(quadX, -3, 5), sizeY, mesh::MeshQuadrature(quadY, 0.5, 2.5));

            const Quadrature* qx = quadX;
            const Quadrature* qy = quadY;
            const Mesh2D* m = testMesh;
            calcX = [qx, m](const std::size_t i, const std::size_t N)->Scalar {
                EXPECT_EQ(N, qx->points.size());
                EXPECT_EQ(N, m->mesh().shape()[0]);
                return 1.0 + 4.0 * qx->points[i];
            };
            calcY = [qy, m](const std::size_t i, const std::size_t M)->Scalar {
                EXPECT_EQ(M, qy->points.size());
                EXPECT_EQ(M, m->mesh().shape()[1]);
                return 1.5 + qy->points[i];
            };
        }
    };

    TEST_F(QuadratureMesh2DTest, elementTest) {
        SCOPED_TRACE("QuadratureMesh2DTest");
        elementTest();
    }

    TEST_F(QuadratureMesh2DTest, accessorsAreEquivalent) {
        SCOPED_TRACE("QuadratureMesh2DTest");
        accessorsAreEquivalent();
    }

    TEST_F(QuadratureMesh2DTest, resizeAlsoRecalculates) {
        SCOPED_TRACE("QuadratureMesh2DTest");
        SCOPED_TRACE("resizeAlsoRecalculates");
        sizeX += 5;
        sizeY -= 5;
        quadX->resize(sizeX); // Necessary because this quadrature is not owned by the mesh.
        quadY->resize(sizeY); // Necessary because this quadrature is not owned by the mesh.
        testMesh->resize(sizeX, sizeY);
        elementTest();

        sizeX = 5;
        sizeY = 5;
        quadX->resize(sizeX); // Necessary because this quadrature is not owned by the mesh.
        quadY->resize(sizeY); // Necessary because this quadrature is not owned by the mesh.
        testMesh->resize(sizeX, sizeY);
        elementTest();
    }

    TEST_F(QuadratureMesh2DTest, quadratureDoesNotReferenceOriginalObject) {
        SCOPED_TRACE("QuadratureMesh2DTest");
        SCOPED_TRACE("quadratureReferencesOriginalObject");
        testMesh->resize(sizeX + 5, sizeY + 5);
        EXPECT_EQ(sizeX, quadX->points.size());
        EXPECT_EQ(sizeY, quadY->points.size());
        EXPECT_EQ(sizeX + 5, testMesh->mesh().shape()[0]);
        EXPECT_EQ(sizeY + 5, testMesh->mesh().shape()[1]);
    }
}
