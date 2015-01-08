#include "Empirical/boundary/ComplexFunctionSegment2D.hpp"

using namespace Eigen;
using namespace Empirical;

namespace {
cScalar pointsFunc(const std::function<cScalar(cScalar)>& z_complex, const cScalar scale, const cScalar offset, const Scalar t) {
    const cScalar argument = scale * (t + offset);
    return z_complex(argument);
}

cScalar pointDerivativesFunc(const std::function<cScalar(cScalar)>& z_complex_derivative, const cScalar scale, const cScalar offset,
                             const Scalar t) {
    const cScalar argument = scale * (t + offset);
    return z_complex_derivative(argument);
}
}

FunctionalBoundary2D* Empirical::createFunctionalSegment2D(const BoundaryFunc& z_complex_func,
        const BoundaryFunc& z_complex_derivative_func, const int64_t M,
        const cScalar offset, const cScalar scale) {
    auto z = std::bind(&pointsFunc, z_complex_func, scale, offset, std::placeholders::_1);
    auto zPrime = std::bind(&pointDerivativesFunc, z_complex_derivative_func, scale, offset, std::placeholders::_1);
    ComplexFunctionSegment2D* p = new ComplexFunctionSegment2D(z, zPrime, M);
    p->resize(M);
    return p;
}

ComplexFunctionSegment2D::ComplexFunctionSegment2D(const QuadratureConversion& Z, const QuadratureConversion& ZPrime,
        const int64_t M)
    : FunctionalBoundary2D(Z, ZPrime), quadrature(createLGL(M)) {
}

ComplexFunctionSegment2D::~ComplexFunctionSegment2D() {
    delete quadrature;
}

void ComplexFunctionSegment2D::resize(const int64_t M) {
    quadrature->resize(M);
    FunctionalBoundary2D::resize(M);
}

const Vector& ComplexFunctionSegment2D::getWeights() const {
    return quadrature->getWeights();
}

const Vector& ComplexFunctionSegment2D::getQuadraturePoints() const {
    return quadrature->getPoints();
}
