#ifndef EMPIRICAL_BOUNDARY_HPP_
#define EMPIRICAL_BOUNDARY_HPP_

#include "Empirical/BoundaryCondition.hpp"
#include "Empirical/Quadrature.hpp"

namespace Empirical {

class Boundary2D {
public:
    virtual ~Boundary2D() {}

    virtual int64_t size() const = 0;
    virtual const cVector& getPoints() const = 0;
    virtual const cVector& getPointDerivatives() const = 0;
    virtual const cVector& getNormals() const = 0;
    virtual const Vector& getWeights() const = 0;

    virtual void setBoundaryCondition(const BoundaryCondition2D& condition) = 0;
    virtual const BoundaryCondition2D& getBoundaryCondition() const = 0;
};

class RefinableBoundary2D : public Boundary2D {
public:
    virtual ~RefinableBoundary2D() {}

    virtual void resize(const int64_t M) = 0;
};

class CompositeBoundary2D : public Boundary2D {
public:
    virtual ~CompositeBoundary2D() {}
    virtual void addSegment(const Boundary2D& boundary) = 0;

    virtual void recalculate() = 0;
};

typedef std::function<cScalar(const Scalar)> QuadratureConversion;

class FunctionalBoundary2D : public RefinableBoundary2D {
protected:
    const BoundaryCondition2D* boundaryCondition;

    const std::function<cScalar(const Scalar)> z;
    const std::function<cScalar(const Scalar)> zPrime;

    cVector points;
    cVector point_primes;
    cVector normals;

    cScalar normalFunc(const cScalar zp) const;

    explicit FunctionalBoundary2D(const QuadratureConversion& Z, const QuadratureConversion& ZPrime)
        : boundaryCondition(nullptr), z(Z), zPrime(ZPrime) {}
public:
    virtual ~FunctionalBoundary2D() {}

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

FunctionalBoundary2D* createRadialSegment2D(const QuadratureConversion& radius_func,
        const QuadratureConversion& radius_derivative_func, const int M);
FunctionalBoundary2D* createArcSegment2D(const cScalar center, const Scalar R, const Scalar t0,
                                      const Scalar t1, const int M);
FunctionalBoundary2D* createFunctionalSegment2D(const BoundaryFunc& z_complex_func,
        const BoundaryFunc& z_complex_derivative_func, const int M,
        const cScalar offset = 0, const cScalar scale = 1);

CompositeBoundary2D* createCompositeBoundary2D(Boundary2D** children, int count);

}

#endif /* EMPIRICAL_BOUNDARY_HPP_ */
