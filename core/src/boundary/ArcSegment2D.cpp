#include "Empirical/boundary/ArcSegment2D.hpp"

using namespace Eigen;
using namespace Empirical;

namespace {
    cScalar pointsFunc(const cScalar center, const Scalar radius, const Scalar t_scale, const Scalar t_offset, const Scalar t) {
        cScalar e = exp(cScalar(0, (t * t_scale) + t_offset));
        return center + radius * e;
    }

    cScalar pointDerivativesFunc(const Scalar radius, const Scalar t_scale, const Scalar t_offset, const Scalar t) {
        cScalar e = exp(cScalar(0, (t * t_scale) + t_offset));
        return cScalar(0, radius * t_scale) * e;
    }
}

FunctionalBoundary2D* Empirical::createArcSegment2D(const cScalar center, const Scalar R, const Scalar t0,
    const Scalar t1, const int64_t M) {
    const Scalar t_scale = (t1 - t0) / 2;
    const Scalar t_offset = (t1 + t0) / 2;
    auto z = std::bind(&pointsFunc, center, R, t_scale, t_offset, std::placeholders::_1);
    auto zPrime = std::bind(&pointDerivativesFunc, R, t_scale, t_offset, std::placeholders::_1);
    ArcSegment2D* p = new ArcSegment2D(z, zPrime, M);
    p->resize(M);
    return p;
}


ArcSegment2D::ArcSegment2D(const QuadratureConversion& Z, const QuadratureConversion& ZPrime, const int64_t M)
    : FunctionalBoundary2D(Z, ZPrime), quadrature(createLGL(M)){
}

ArcSegment2D::~ArcSegment2D() {
    delete quadrature;
}

const Vector& ArcSegment2D::getWeights() const {
    return quadrature->getWeights();
}

const Vector& ArcSegment2D::getQuadraturePoints() const {
    return quadrature->getPoints();
}
