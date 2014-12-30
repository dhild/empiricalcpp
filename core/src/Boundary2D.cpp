#include <functional>
#include "Empirical/src/domain/BoundaryCondition2D.hpp"

using namespace empirical;

BoundaryCondition2D::BoundaryCondition2D(
    const std::function<cScalar(const cScalar)> pointFunc,
    const std::function<cScalar(const cScalar)> normalFunc)
    : point(pointFunc), normal(normalFunc) {}

BoundaryCondition2D::~BoundaryCondition2D() {}

bool BoundaryCondition2D::requiresPoint() const {
  return true;
}

bool BoundaryCondition2D::requiresNormal() const {
  return true;
}

cScalar BoundaryCondition2D::boundary(const cScalar x) const {
  return point(x);
}

cScalar BoundaryCondition2D::boundaryNormal(const cScalar x) const {
  return normal(x);
}

cScalar zeroFunction(const cScalar) {
  return 0;
}

DirichletBoundary2D::DirichletBoundary2D(
    const std::function<cScalar(const cScalar)> pointFunc)
    : BoundaryCondition2D(pointFunc, zeroFunction) {}

DirichletBoundary2D::~DirichletBoundary2D() {}

bool DirichletBoundary2D::requiresPoint() const {
  return true;
}

bool DirichletBoundary2D::requiresNormal() const {
  return false;
}

NeumannBoundary2D::NeumannBoundary2D(
    const std::function<cScalar(const cScalar)> normalFunc)
    : BoundaryCondition2D(zeroFunction, normalFunc) {}

NeumannBoundary2D::~NeumannBoundary2D() {}

bool NeumannBoundary2D::requiresPoint() const {
  return false;
}

bool NeumannBoundary2D::requiresNormal() const {
  return true;
}
