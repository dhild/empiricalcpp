#include "Empirical/src/domain/Domain2D.hpp"
#include "Empirical/src/domain/ArcSegment2D.hpp"
#include "Empirical/src/domain/RadialSegment2D.hpp"
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

DomainSegment2D::~DomainSegment2D() {}

ArcSegment2D::ArcSegment2D(const std::function<cScalar(Scalar)>& z,
                                 const std::function<cScalar(Scalar)>& zPrime,
                                 const int M)
    : z(z), zPrime(zPrime), t(nullptr), points(M), pointPrimes(M) {
  recalculate(M);
}

void ArcSegment2D::recalculateQuadratures(const int M) {
  recalculate(M);
}

cScalar normalFunc(cScalar val) {
  return cScalar(imag(val), -real(val)) / abs(val);
}

cScalar arcZ(Scalar t, const function<cScalar(cScalar)>& z) {
  angle = 2 * PI * t;
  
}

void RadialSegment2D::recalculate(const int M) {
  delete t;
  t = new PeriodicTrapezoidQuadrature(M);
  
  points.resize(M);
  pointPrimes.resize(M);

  points = t->getPoints().unaryExpr(z);
  pointPrimes = t->getPoints().unaryExpr(zPrime);
  normals = t->getPoints().unaryExpr(ptr_fun(normalFunc));
}

RadialSegment2D::~RadialSegment2D() {
  delete t;
}

int RadialSegment2D::size() const {
  return points.rows();
}

const Quadrature& RadialSegment2D::getT() const {
  return *t;
}

const Mesh1D& RadialSegment2D::getPoints() const {
  return points;
}

const Mesh1D& RadialSegment2D::getPointDerivatives() const {
  return pointPrimes;
}

const Mesh1D& RadialSegment2D::getNormals() const {
  return normals;
}
