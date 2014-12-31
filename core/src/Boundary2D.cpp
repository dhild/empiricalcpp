#include "Empirical/problem/BoundaryConditions2D.hpp"

using namespace Empirical;

namespace Empirical {
const BoundaryFunc zeroFunction = [](const cScalar) {
    return 0;
};
}

CauchyCondition2D::CauchyCondition2D(const BoundaryFunc pointFunc, const BoundaryFunc normalFunc)
    : pointValues(pointFunc), normalValues(normalFunc) {}

CauchyCondition2D::~CauchyCondition2D() {}

bool CauchyCondition2D::requiresPoint() const {
    return true;
}

bool CauchyCondition2D::requiresNormal() const {
    return true;
}

cScalar CauchyCondition2D::operator()(const cScalar x) const {
    return pointValues(x);
}

cScalar CauchyCondition2D::normal(const cScalar x) const {
    return normalValues(x);
}

DirichletCondition2D::DirichletCondition2D(const BoundaryFunc pointFunc)
    : pointValues(pointFunc) {}

DirichletCondition2D::~DirichletCondition2D() {}

bool DirichletCondition2D::requiresPoint() const {
    return true;
}

bool DirichletCondition2D::requiresNormal() const {
    return false;
}

cScalar DirichletCondition2D::operator()(const cScalar x) const {
    return pointValues(x);
}

cScalar DirichletCondition2D::normal(const cScalar) const {
    return 0;
}

NeumannCondition2D::NeumannCondition2D(const BoundaryFunc normalFunc)
    : normalValues(normalFunc) {}

NeumannCondition2D::~NeumannCondition2D() {}

bool NeumannCondition2D::requiresPoint() const {
    return false;
}

bool NeumannCondition2D::requiresNormal() const {
    return true;
}

cScalar NeumannCondition2D::operator()(const cScalar) const {
    return 0;
}

cScalar NeumannCondition2D::normal(const cScalar x) const {
    return normalValues(x);
}
