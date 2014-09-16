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

  const std::function<cScalar(const Scalar)> z;
  const std::function<cScalar(const Scalar)> z_prime;

  Mesh1D points;
  Mesh1D point_primes;
  Mesh1D normals;
  
  std::function<cScalar(const cScalar)> boundary_condition;
  std::function<cScalar(const cScalar)> boundary_condition_normal;
  bool boundary_in_positive_normal_direction;

  cScalar normalFunc(const cScalar zp) const;

  DomainSegment2D(Quadrature* quadrature,
                  const std::function<cScalar(const Scalar)>& z,
                  const std::function<cScalar(const Scalar)>& zPrime);

 public:

  virtual ~DomainSegment2D();

  void recalculate(const int M);

  virtual const Mesh1D& getPoints() const;
  virtual const Mesh1D& getPointDerivatives() const;
  virtual const Mesh1D& getNormals() const;

  virtual int size() const;
  virtual const QuadratureVector& getWeights() const;
  virtual const QuadratureVector& getT() const;

  virtual bool isBoundaryInPositiveNormalDirection() const;
  virtual void setBoundaryInPositiveNormalDirection(const bool bcPositive);
  
  virtual const Mesh1D getBoundaryCondition() const;
  virtual void setBoundaryCondition(
      const std::function<cScalar(const cScalar)>& bc);
  
  virtual const Mesh1D getBoundaryConditionNormalDeriv() const;
  virtual void setBoundaryConditionNormal(
      const std::function<cScalar(const cScalar)>& bcN);

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

  void addSegment(const DomainSegment2D& segment);

  void addBasis(const Basis2D* basis);

  int sizeSegments() const;
  int sizeBases() const;

  const Mesh1D& getPoints() const;
  const Mesh1D& getPointNormals() const;
  const QuadratureVector& getWeights() const;

};

}

#endif /* DOMAIN2D_HPP_ */
