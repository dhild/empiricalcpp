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

    cVector charge_points;

public:
    MFSBasis2D(const cVector& points);

    virtual ~MFSBasis2D();

    virtual int64_t size() const;

    virtual cScalar basis(const Scalar k, const cScalar z, const cScalar x) const;
    virtual cScalar basisNormalDerivative(const Scalar k, const cScalar z,
                                          const cScalar x) const;

    virtual cVector basis(const Scalar k, const cScalar z) const;
    virtual cVector basisNormalDerivative(const Scalar k, const cScalar z) const;

    virtual cMatrix basis(const Scalar k, const cVector& z) const;
    virtual cMatrix basisNormalDerivative(const Scalar k, const cVector& z) const;

};

}

#endif /* EMPIRICAL_BASIS_MFSBASIS_HPP_ */
