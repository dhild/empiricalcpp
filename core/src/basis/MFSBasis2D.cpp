#include "MFSBasis2D.hpp"
#include <boost/math/special_functions/bessel.hpp>
#include <functional>

using namespace Eigen;
using namespace boost::math;
using namespace Empirical;

namespace {
cScalar hankel(const Scalar v, const Scalar x) {
    return cyl_bessel_j(v, x) + cScalar(0, 1) * cyl_neumann(v, x);
}

cScalar mfsBasis(const Scalar k, const cScalar dist) {
    if (k == 0) {
        return -log(abs(dist)) / (2 * PI);
    }
    return cScalar(0, 0.25) * hankel(0, k * abs(dist));
}

cScalar mfsBasisNormalDerivative(const Scalar k, const cScalar dist) {
    if (k == 0) {
        return -1 / (2 * PI * abs(dist));
    }
    return cScalar(-k, 0.25) * hankel(1, k * abs(dist));
}
}

Basis2D* Empirical::createMFSBasis(RefinableBoundary2D* points) {
    return new MFSBasis2D(points);
}

MFSBasis2D::MFSBasis2D(RefinableBoundary2D* points)
    : chargePoints(points) {}

MFSBasis2D::~MFSBasis2D() {}

void MFSBasis2D::resize(const int64_t M) {
    chargePoints->resize(M);
}

int64_t MFSBasis2D::degreesOfFreedom() const {
    return chargePoints->getPoints().rows();
}

cScalar MFSBasis2D::operator()(const Scalar k, const cScalar z, const cScalar x) const {
    return mfsBasis(k, z - x);
}

cScalar MFSBasis2D::normal(const Scalar k, const cScalar z, const cScalar x) const {
    return mfsBasisNormalDerivative(k, z - x);
}

cVector MFSBasis2D::operator()(const Scalar k, const cScalar z) const {
    cVector dist = cVector::Constant(chargePoints->getPoints().rows(), 1, z) - chargePoints->getPoints();

    auto func = [k](const cScalar x) {
        return mfsBasis(k, x);
    };
    return dist.unaryExpr(func);
}

cVector MFSBasis2D::normal(const Scalar k, const cScalar z) const {
    cVector dist = cVector::Constant(chargePoints->getPoints().rows(), 1, z) - chargePoints->getPoints();

    auto func = [k](const cScalar x) {
        return mfsBasisNormalDerivative(k, x);
    };
    return dist.unaryExpr(func);
}

cMatrix MFSBasis2D::operator()(const Scalar k, const cVector& z) const {
    const int64_t M = z.rows();
    const int64_t N = chargePoints->getPoints().rows();
    cMatrix dist = chargePoints->getPoints().transpose().replicate(M, 1) - z.replicate(1, N);
    auto func = [k](const cScalar x) {
        return mfsBasis(k, x);
    };
    return dist.unaryExpr(func);
}

cMatrix MFSBasis2D::normal(const Scalar k, const cVector& z) const {
    const int64_t M = z.rows();
    const int64_t N = chargePoints->getPoints().rows();
    cMatrix dist = chargePoints->getPoints().transpose().replicate(M, 1) - z.replicate(1, N);
    auto func = [k](const cScalar x) {
        return mfsBasisNormalDerivative(k, x);
    };
    return dist.unaryExpr(func);
}
