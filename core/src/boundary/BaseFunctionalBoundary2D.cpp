#include "BaseFunctionalBoundary2D.hpp"

using namespace Eigen;
using namespace Empirical;

void BaseFunctionalBoundary2D::resize(const int64_t M) {
    points.resize(M, 1);
    point_primes.resize(M, 1);
    normals.resize(M, 1);
    const Vector t = getQuadraturePoints();

    for (int i = 0; i < M; i++) {
        const Scalar ti = t(i, 0);
        points(i, 0) = z(ti);
        cScalar zp = zPrime(ti);
        point_primes(i, 0) = zp;
        normals(i, 0) = normalFunc(zp);
    }
}

cScalar BaseFunctionalBoundary2D::normalFunc(const cScalar zp) const {
    const Scalar mag = abs(zp);
    return cScalar(imag(zp) / mag, -real(zp) / mag);
}

int64_t BaseFunctionalBoundary2D::size() const {
    return points.rows();
}

const cVector& BaseFunctionalBoundary2D::getPoints() const {
    return points;
}

const cVector& BaseFunctionalBoundary2D::getPointDerivatives() const {
    return point_primes;
}

const cVector& BaseFunctionalBoundary2D::getNormals() const {
    return normals;
}

void BaseFunctionalBoundary2D::setBoundaryCondition(const BoundaryCondition2D& condition) {
    boundaryCondition = &condition;
}

const BoundaryCondition2D& BaseFunctionalBoundary2D::getBoundaryCondition() const {
    return *boundaryCondition;
}
