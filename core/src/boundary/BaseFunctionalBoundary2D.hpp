#ifndef EMPIRICAL_SRC_BASE_FUNCTIONAL_BOUNDARY_2D_HPP_
#define EMPIRICAL_SRC_BASE_FUNCTIONAL_BOUNDARY_2D_HPP_

#include <Empirical/Boundary.hpp>

namespace Empirical {

class BaseFunctionalBoundary2D : public FunctionalBoundary2D {
protected:
    const BoundaryCondition2D* boundaryCondition;

    const std::function<cScalar(const Scalar)> z;
    const std::function<cScalar(const Scalar)> zPrime;

    cVector points;
    cVector point_primes;
    cVector normals;

    cScalar normalFunc(const cScalar zp) const;

    BaseFunctionalBoundary2D(const QuadratureConversion& Z, const QuadratureConversion& ZPrime)
        : boundaryCondition(nullptr), z(Z), zPrime(ZPrime) {}
public:
    virtual ~BaseFunctionalBoundary2D() {}

    BaseFunctionalBoundary2D(const BaseFunctionalBoundary2D&) = delete;
    BaseFunctionalBoundary2D& operator=(const BaseFunctionalBoundary2D&) = delete;

    virtual const Vector& getWeights() const = 0;
    virtual const Vector& getQuadraturePoints() const = 0;

    virtual void resize(const int64_t M);

    virtual int64_t size() const;
    virtual const cVector& getPoints() const;
    virtual const cVector& getPointDerivatives() const;
    virtual const cVector& getNormals() const;

    virtual void setBoundaryCondition(const BoundaryCondition2D& condition);
    virtual const BoundaryCondition2D& getBoundaryCondition() const;
};

}

#endif /* EMPIRICAL_SRC_BASE_FUNCTIONAL_BOUNDARY_2D_HPP_ */
