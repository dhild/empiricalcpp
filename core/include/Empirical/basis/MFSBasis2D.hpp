#ifndef EMPIRICAL_BASIS_MFS_BASIS_2D_HPP_
#define EMPIRICAL_BASIS_MFS_BASIS_2D_HPP_

#include "Empirical/Basis.hpp"

namespace Empirical {

/** An implementation of a 2D basis using the method of fundamental solutions.*/
class MFSBasis2D : public Basis2D {
protected:

    RefinableBoundary2D* chargePoints;

public:
    MFSBasis2D(RefinableBoundary2D* points);

    virtual ~MFSBasis2D();

    virtual void resize(const int64_t M);

    virtual int64_t degreesOfFreedom() const;

    virtual cScalar operator()(const Scalar k, const cScalar z, const cScalar x) const;
    virtual cScalar normal(const Scalar k, const cScalar z, const cScalar x) const;

    virtual cVector operator()(const Scalar k, const cScalar z) const;
    virtual cVector normal(const Scalar k, const cScalar z) const;

    virtual cMatrix operator()(const Scalar k, const cVector& z) const;
    virtual cMatrix normal(const Scalar k, const cVector& z) const;

    static cScalar hankel(const Scalar v, const Scalar x);
    static cScalar mfsBasis(const Scalar k, const cScalar dist);
    static cScalar mfsBasisNormalDerivative(const Scalar k, const cScalar dist);
};

}

#endif /* EMPIRICAL_BASIS_MFS_BASIS_2D_HPP_ */
