#include "Empirical/src/domain/DomainSegment2D.hpp"

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

const Mesh1D DomainSegment2D::getNormals() const {
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
