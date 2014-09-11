#include "Empirical/src/domain/DomainSegment2D.hpp"
#include "Empirical/src/domain/RadialSegment.hpp"
#include "Empirical/src/quadrature/Quadrature.hpp"

using namespace std;
using namespace Eigen;
using namespace empirical;

DomainSegment2D::DomainSegment2D() : boundaryInPositiveNormalDirection(true) {
}

void DomainSegment2D::setBoundaryInPositiveNormalDirection(const bool bcPositive) {
  this->boundaryInPositiveNormalDirection = bcPositive;
}

bool DomainSegment2D::isBoundaryInPositiveNormalDirection() const {
  return this->boundaryInPositiveNormalDirection;
}

cScalar normalFunc(cScalar val) {
  return cScalar(imag(val), -real(val)) / abs(val);
}

const Mesh1D& DomainSegment2D::getNormals() const {
  return this->getPoints().unaryExpr(ptr_fun(normalFunc));
}

const Mesh1D DomainSegment2D::getBoundaryCondition() const {
  return this->getPoints().unaryExpr(this->bc);
}

const Mesh1D DomainSegment2D::getBoundaryConditionNormalDeriv() const {
  return this->getPointDerivatives().unaryExpr(this->bcN);
}

void DomainSegment2D::setBoundaryCondition(const std::function<cScalar(cScalar) >& bc) {
  this->bc = bc;
}

void DomainSegment2D::setBoundaryConditionNormal(const std::function<cScalar(cScalar) >& bcN) {
  this->bcN = bcN;
}

RadialSegment2D::RadialSegment2D(const std::function<cScalar(cScalar)>& z,
                                 const std::function<cScalar(cScalar)>& zPrime,
                                 const int M)
    : z(z), zPrime(zPrime), t(nullptr), points(M), pointPrimes(M) {
  recalculate(M);
}

void RadialSegment2D::recalculateQuadratures(const int M) {
  recalculate(M);
}

void RadialSegment2D::recalculate(const int M) {
  delete t;
  t = new PeriodicTrapezoidQuadrature(M);
  
  points.resize(M);
  pointPrimes.resize(M);

  points = t->getPoints().unaryExpr(z);
  pointPrimes = t->getPoints().unaryExpr(zPrime);
}

RadialSegment2D::~RadialSegment2D() {
  delete t;
}

int RadialSegment2D::size() const {
  return this->points.rows();
}

const Mesh1D& RadialSegment2D::getPoints() const {
  return points;
}

const Mesh1D& RadialSegment2D::getPointDerivatives() const {
  return pointPrimes;
}
