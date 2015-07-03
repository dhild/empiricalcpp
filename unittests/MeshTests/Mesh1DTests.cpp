#include "gtest/gtest.h"

#include <empiricalcpp/empirical.hpp>
#include <cmath>
#include <functional>

using namespace empirical;

TEST(Mesh1DTest, CreateFromFunction) {
    std::shared_ptr<Mesh1D> mesh = mesh::createMesh(25, [](const std::size_t i, const std::size_t N)->Scalar { return Scalar(i) / (N - 1); });
    Mesh1D& m = *mesh.get();
    SCOPED_TRACE("CreateFromFunction");
    SCOPED_TRACE(m);
    for (std::size_t i = 0; i < 25; i++) {
        EXPECT_NEAR(Scalar(i) / 24, m(i), epsScalar);
    }
}

TEST(Mesh1DTest, AccessorsAreEquivalent) {
    std::shared_ptr<Mesh1D> mesh = mesh::createMesh(25, [](const std::size_t i, const std::size_t N)->Scalar { return Scalar(i) / (N - 1); });
    Mesh1D& m = *mesh.get();
    SCOPED_TRACE("AccessorsAreEquivalent");
    SCOPED_TRACE(m);
    for (std::size_t i = 0; i < 25; i++) {
        EXPECT_NEAR(m[i], m(i), epsScalar);
        EXPECT_NEAR(m[i], m.mesh()[i], epsScalar);
    }
}
