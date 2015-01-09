#include "RadialSegment2D.hpp"

using namespace Eigen;
using namespace Empirical;

namespace {
cScalar pointsFunc(const QuadratureConversion& radius, const Scalar t) {
    const Scalar angle = PI * t;
    return radius(angle) * exp(cScalar(0, angle));
}

cScalar pointDerivativesFunc(const QuadratureConversion& radius, const QuadratureConversion& radius_derivative, const Scalar t) {
    const Scalar angle = PI * t;
    const cScalar e = exp(cScalar(0, angle));
    const cScalar r = radius(angle);
    const cScalar rp = radius_derivative(angle);
    return PI * ((cScalar(0, 1) * r * e) + (rp * e));
}
}

FunctionalBoundary2D* Empirical::createRadialSegment2D(const QuadratureConversion& radius_func,
        const QuadratureConversion& radius_derivative_func, const int64_t M) {
    auto z = std::bind(&pointsFunc, radius_func, std::placeholders::_1);
    auto zPrime = std::bind(&pointDerivativesFunc, radius_func, radius_derivative_func, std::placeholders::_1);
    RadialSegment2D* p = new RadialSegment2D(z, zPrime, M);
    p->resize(M);
    return p;
}

RadialSegment2D::RadialSegment2D(const QuadratureConversion& Z, const QuadratureConversion& ZPrime, const int64_t M)
    : FunctionalBoundary2D(Z, ZPrime), quadrature(createPeriodicTrapezoid(M)) {
}

RadialSegment2D::~RadialSegment2D() {
    delete quadrature;
}

void RadialSegment2D::resize(const int64_t M) {
    quadrature->resize(M);
    FunctionalBoundary2D::resize(M);
}

const Vector& RadialSegment2D::getWeights() const {
    return quadrature->getWeights();
}

const Vector& RadialSegment2D::getQuadraturePoints() const {
    return quadrature->getPoints();
}
