#include "BaseDomain2D.hpp"

using namespace Empirical;

const Boundary2D& BaseDomain2D::getBoundary() const {
    return *boundary;
}

Boundary2D& BaseDomain2D::getBoundary() {
    return *boundary;
}

const Basis2D& BaseDomain2D::getBasis() const {
    return *basis;
}

Basis2D& BaseDomain2D::getBasis() {
    return *basis;
}

Scalar BaseDomain2D::getIndexOfRefraction() const {
    return indexOfRefraction;
}

void BaseDomain2D::setIndexOfRefraction(Scalar index) {
    indexOfRefraction = index;
}

bool BaseDomain2D::isDomainInNormalDirection() const {
    return domainInNormalDirection;
}