#ifndef DOMAIN2D_HPP_
#define DOMAIN2D_HPP_

#include <vector>
#include <functional>
#include <Eigen/Dense>
#include "Empirical/src/config.h"
#include "Empirical/src/quadrature/Quadrature.hpp"

namespace empirical {

typedef Eigen::Matrix<cScalar, Eigen::Dynamic, 1> Mesh1D;
typedef Eigen::Matrix<cScalar, Eigen::Dynamic, Eigen::Dynamic> Mesh2D;

class Quadrature;

class DomainSegment2D {
 protected:
  Quadrature* base_quadrature;
  
  std::function<cScalar(cScalar)> boundary_condition;
  std::function<cScalar(cScalar)> boundary_condition_normal;
  bool boundary_in_positive_normal_direction;

  DomainSegment2D();

 public:

  virtual ~DomainSegment2D();

  virtual const Mesh1D& getPoints() const = 0;
  virtual const Mesh1D& getPointDerivatives() const = 0;
  virtual const Mesh1D& getNormals() const = 0;

  virtual int size() const;
  virtual const QuadratureVector& getWeights() const;
  virtual const QuadratureVector& getT() const;

  virtual bool isBoundaryInPositiveNormalDirection() const;
  virtual void setBoundaryInPositiveNormalDirection(const bool bcPositive);
  
  virtual const Mesh1D getBoundaryCondition() const;
  virtual void setBoundaryCondition(const std::function<cScalar(cScalar)>& bc);
  
  virtual const Mesh1D getBoundaryConditionNormalDeriv() const;
  virtual void setBoundaryConditionNormal(const std::function<cScalar(cScalar)>& bcN);

};

class Basis2D;

class Domain2D {
 protected:
  std::vector<DomainSegment2D*> segments;
  std::vector<const Basis2D*> bases;
  bool is_exterior;
  Scalar refractive_index;

 public:

  Domain2D();

  virtual ~Domain2D();

  const bool isExterior() const {
    return is_exterior;
  }

  const Scalar getWavenumber() const {
    return wavenumber;
  }

  void addSegment(const DomainSegment2D& segment, NormalsReversed reversed = false);

  void addBasis(const Basis2D* basis);

  int sizeSegments() const;
  int sizeBases() const;

  const Mesh1D& getPoints() const;
  const Mesh1D& getPointNormals() const;
  const QuadratureVector& getWeights() const;

};

}

#endif /* DOMAIN2D_HPP_ */
