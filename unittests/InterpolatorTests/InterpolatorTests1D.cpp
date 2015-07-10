#include "gtest/gtest.h"

#include <empiricalcpp/empirical.hpp>
#include <cmath>
#include <functional>

using namespace empirical;

namespace {
    class ScalarInterpolator1DTest : public ::testing::Test {
    public:
        std::auto_ptr<Mesh1D> points;
        std::vector<std::shared_ptr<EvaluationScalar1D>> computedSolutions;
        std::auto_ptr<ScalarInterpolator1D> testInterp;
    };

    Scalar rungeFunction(const Scalar x, const Scalar mu) {
        return Scalar(1) / (Scalar(1) + (x * mu * x * mu));
    }

    class RungeFunctionInterpolatorTest : public ScalarInterpolator1DTest {
    public:
        virtual void SetUp() {
            auto lglPoints = std::auto_ptr<Quadrature>(quadrature::legendreGaussLobatto(151));
            points = std::auto_ptr<Mesh1D>(mesh::createMesh(mesh::MeshQuadrature(lglPoints.get(), -1, 1)));
            for (Scalar i = 0; i < 100; i++) {
                const Scalar mu = 1 + (4 * i / 99);
                auto eval = std::shared_ptr<EvaluationScalar1D>(new EvaluationScalar1D(151));
                for (std::size_t j = 0; j < (*points).mesh().size(); j++) {
                    (*eval)[j] = rungeFunction((*points)(j), mu);
                }
                computedSolutions.push_back(eval);
            }
            auto solutions = interpolation::getSolutions(computedSolutions.begin(), computedSolutions.end());
            testInterp = std::auto_ptr<ScalarInterpolator1D>(interpolation::constructInterpolator(*points, solutions));
        }
    };

    TEST_F(RungeFunctionInterpolatorTest, solutionUsesSaneValues) {
        SCOPED_TRACE("RungeFunctionInterpolatorTest");
        SCOPED_TRACE("solutionUsesSaneValues");
        const ScalarInterpolator1D& interp = *testInterp;
#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
        SCOPED_TRACE(interp);
#endif
        EXPECT_EQ(interp.N(), interp.computedSolutionPoints().size());
        EXPECT_EQ(interp.N(), interp.computedSolutionsUsedInBasis().size());
        EXPECT_LT(points->mesh().size(), interp.N());
        EXPECT_LE(epsScalar * 4e10, interp.getLastCorrectionScale());
    }

}
