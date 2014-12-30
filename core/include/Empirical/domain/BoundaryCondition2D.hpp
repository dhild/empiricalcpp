#ifndef EMPIRICAL_BOUNDARY_CONDITION_2D_HPP_
#define EMPIRICAL_BOUNDARY_CONDITION_2D_HPP_

#include "Empirical/Constants.hpp"
#include <functional>

namespace Empirical {

class BoundaryCondition2D {
 protected:
  std::function<cScalar(const cScalar)> point;
  std::function<cScalar(const cScalar)> normal;

 public:
  BoundaryCondition2D(const std::function<cScalar(const cScalar)> point,
                      const std::function<cScalar(const cScalar)> normal);

  virtual ~BoundaryCondition2D();

  virtual bool requiresPoint() const;
  virtual bool requiresNormal() const;

  virtual cScalar boundary(const cScalar x) const;
  virtual cScalar boundaryNormal(const cScalar x) const;
};

cScalar zeroFunction(const cScalar);

class DirichletBoundary2D : public BoundaryCondition2D {
 public:
  DirichletBoundary2D(const std::function<cScalar(const cScalar)> point);

  virtual ~DirichletBoundary2D();

  virtual bool requiresPoint() const;
  virtual bool requiresNormal() const;
};

class NeumannBoundary2D : public BoundaryCondition2D {
 public:
  NeumannBoundary2D(const std::function<cScalar(const cScalar)> normal);

  virtual ~NeumannBoundary2D();

  virtual bool requiresPoint() const;
  virtual bool requiresNormal() const;
};

}

#endif /* EMPIRICAL_BOUNDARY_CONDITION_2D_HPP_ */
