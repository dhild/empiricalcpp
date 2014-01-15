#include <Empirical/src/domain/BasicDomainSegment2D.hpp>
#include <Empirical/Quadrature>

using namespace std;
using namespace Eigen;
using namespace empirical;

BasicDomainSegment2D::BasicDomainSegment2D(Quadrature& points,
        Quadrature& pointPrimes)
        : z(points), zPrime(pointPrimes), normals(points.getN()) {
    updateNormals();
}

BasicDomainSegment2D::~BasicDomainSegment2D() {
}

void BasicDomainSegment2D::updateNormals() {
    Array<cScalar, Dynamic, 1>& zp = this->zPrime;
    this->normals = zp.conjugate() / zp.abs();
}

void BasicDomainSegment2D::recalculateQuadratures(const int M) {
    this->z.update(M);
    this->zPrime.update(M);
    this->normals->update(M);
    updateNormals();
}

const ArrayBase<cScalar> BasicDomainSegment2D::getPoints() const {
    return this->z.getPoints();
}

const ArrayBase<cScalar> BasicDomainSegment2D::getFirstDerivative() const {
    return this->zPrime.getPoints();
}

const ArrayBase<cScalar> BasicDomainSegment2D::getNormals() const {
    return this->normals.getPoints();
}
