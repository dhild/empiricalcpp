#ifndef DOMAIN2D_HPP_
#define DOMAIN2D_HPP_

#include <vector>
#include <functional>
#include <Eigen/Dense>
#include "Empirical/Constants.hpp"
#include "Empirical/quadrature/Quadrature.hpp"
#include "Empirical/domain/BoundaryCondition2D.hpp"

namespace Empirical {

typedef Eigen::Matrix<cScalar, Eigen::Dynamic, 1> Mesh1D;

class DomainSegment2D {
 protected:
  Quadrature* base_quadrature;

  const std::function<cScalar(const Scalar)> z;
  const std::function<cScalar(const Scalar)> z_prime;

  Mesh1D points;
  Mesh1D point_primes;
  Mesh1D normals;

  const BoundaryCondition2D* boundary_condition;

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

  virtual int64_t size() const;
  virtual const QuadratureVector& getWeights() const;
  virtual const QuadratureVector& getT() const;

  virtual void setBoundaryCondition(const BoundaryCondition2D& condition);
  virtual const BoundaryCondition2D& getBoundaryCondition() const;

};

class Basis2D;

class Domain2D {
 protected:
  std::vector<const DomainSegment2D*> segments;
  std::vector<const Basis2D*> bases;
  const bool is_exterior;
  Scalar refractive_index;

 public:

  Domain2D(const bool exterior = false, const Scalar refractive_index = 1);

  virtual ~Domain2D();

  bool isExterior() const {
    return is_exterior;
  }

  void setRefractiveIndex(const Scalar refractive_index) {
    this->refractive_index = refractive_index;
  }

  Scalar getRefractiveIndex() const {
    return refractive_index;
  }

  void addSegment(const DomainSegment2D* segment);

  void addBasis(const Basis2D* basis);

  int64_t sizeSegments() const;
  int64_t sizeBases() const;

  Mesh1D getPoints() const;
  Mesh1D getPointDerivatives() const;
  Mesh1D getNormals() const;
  QuadratureVector getWeights() const;
  const std::vector<const Basis2D*>& getBases() const;

};

}

#endif /* DOMAIN2D_HPP_ */
