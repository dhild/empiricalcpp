#ifndef EMPIRICAL_BASIS_HPP_
#define EMPIRICAL_BASIS_HPP_

#include <Empirical/Boundary.hpp>

namespace Empirical {

class Basis2D {
public:
    virtual ~Basis2D() {}

    virtual void resize(const int64_t M) = 0;

    virtual int64_t degreesOfFreedom() const = 0;

    virtual cScalar operator()(const Scalar k, const cScalar z, const cScalar x) const = 0;
    virtual cScalar normal(const Scalar k, const cScalar z, const cScalar x) const = 0;

    virtual cVector operator()(const Scalar k, const cScalar z) const = 0;
    virtual cVector normal(const Scalar k, const cScalar z) const = 0;

    virtual cMatrix operator()(const Scalar k, const cVector& z) const = 0;
    virtual cMatrix normal(const Scalar k, const cVector& z) const = 0;

};

Basis2D* createMFSBasis(RefinableBoundary2D* chargePoints);
}

#endif /* EMPIRICAL_BASIS_HPP_ */
