#ifndef EMPIRICAL_BASIS_MFSBASIS_HPP_
#define EMPIRICAL_BASIS_MFSBASIS_HPP_

#include "Empirical/Constants.hpp"
#include "Empirical/basis/Basis2D.hpp"
#include <Eigen/Dense>

namespace Empirical {

cScalar hankel(const Scalar v, const Scalar x);
cScalar mfsBasis(const Scalar k, const cScalar dist);
cScalar mfsBasisNormalDerivative(const Scalar k, const cScalar dist);

/** An implementation of a 2D basis using the method of fundamental solutions.*/
class MFSBasis2D : public Basis2D {
 protected:

  Mesh1D charge_points;

 public:
  MFSBasis2D(const Mesh1D& points);
  
  virtual ~MFSBasis2D();

  virtual int64_t size() const;

  virtual cScalar basis(const Scalar k, const cScalar z, const cScalar x) const;
  virtual cScalar basisNormalDerivative(const Scalar k, const cScalar z,
                                        const cScalar x) const;

  virtual Mesh1D basis(const Scalar k, const cScalar z) const;
  virtual Mesh1D basisNormalDerivative(const Scalar k, const cScalar z) const;

  virtual Mesh2D basis(const Scalar k, const Mesh1D& z) const;
  virtual Mesh2D basisNormalDerivative(const Scalar k, const Mesh1D& z) const;

};

}

#endif /* EMPIRICAL_BASIS_MFSBASIS_HPP_ */
