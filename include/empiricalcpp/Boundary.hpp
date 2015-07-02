#ifndef EMPIRICAL_BOUNDARY_HPP_
#define EMPIRICAL_BOUNDARY_HPP_

#include <Empirical/BoundaryCondition.hpp>
#include <Empirical/Quadrature.hpp>

namespace Empirical {

struct Boundary2D {
    virtual ~Boundary2D() {}

    virtual Index size() const = 0;
    virtual const cVector& getPoints() const = 0;
    virtual const cVector& getPointDerivatives() const = 0;
    virtual const cVector& getNormals() const = 0;
    virtual const Vector& getWeights() const = 0;

    virtual void setBoundaryCondition(const BoundaryCondition2D& condition) = 0;
    virtual const BoundaryCondition2D& getBoundaryCondition() const = 0;
};

struct RefinableBoundary2D : public Boundary2D {
    virtual ~RefinableBoundary2D() {}

    virtual void resize(const Index M) = 0;
};

typedef std::function<cScalar(const Scalar)> QuadratureConversion;

struct FunctionalBoundary2D : public RefinableBoundary2D {
    virtual ~FunctionalBoundary2D() {}

    virtual const Vector& getWeights() const = 0;
    virtual const Vector& getQuadraturePoints() const = 0;

    virtual void resize(const Index M) = 0;

    virtual Index size() const = 0;
    virtual const cVector& getPoints() const = 0;
    virtual const cVector& getPointDerivatives() const = 0;
    virtual const cVector& getNormals() const = 0;

    virtual void setBoundaryCondition(const BoundaryCondition2D& condition) = 0;
    virtual const BoundaryCondition2D& getBoundaryCondition() const = 0;
};

FunctionalBoundary2D* createRadialSegment2D(const QuadratureConversion& radius_func,
        const QuadratureConversion& radius_derivative_func, const Index M);
FunctionalBoundary2D* createArcSegment2D(const cScalar center, const Scalar R, const Scalar t0,
        const Scalar t1, const Index M);
FunctionalBoundary2D* createFunctionalSegment2D(const BoundaryFunc& z_complex_func,
        const BoundaryFunc& z_complex_derivative_func, const Index M,
        const cScalar offset = 0, const cScalar scale = 1);

}

#endif /* EMPIRICAL_BOUNDARY_HPP_ */
