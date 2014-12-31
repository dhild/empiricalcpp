#ifndef EMPIRICAL_BOUNDARY_HPP_
#define EMPIRICAL_BOUNDARY_HPP_

#include "Empirical/BoundaryCondition.hpp"
#include "Empirical/Quadrature.hpp"

namespace Empirical {

typedef std::function<cScalar(const Scalar)> QuadratureConversion;

class BoundarySegment2D {
protected:
    const BoundaryCondition2D* boundaryCondition;

    const std::function<cScalar(const Scalar)> z;
    const std::function<cScalar(const Scalar)> zPrime;

    cVector points;
    cVector point_primes;
    cVector normals;

    cScalar normalFunc(const cScalar zp) const;

    explicit BoundarySegment2D(const QuadratureConversion& Z, const QuadratureConversion& ZPrime)
        : boundaryCondition(nullptr), z(Z), zPrime(ZPrime) {}
public:
    virtual ~BoundarySegment2D();

    virtual void recalculate(const int64_t M);

    const cVector& getPoints() const {
        return points;
    }
    const cVector& getPointDerivatives() const {
        return point_primes;
    }
    const cVector& getNormals() const {
        return normals;
    }

    int64_t size() const {
        return points.rows();
    }
    virtual const Vector& getWeights() const = 0;
    virtual const Vector& getQuadraturePoints() const = 0;

    void setBoundaryCondition(const BoundaryCondition2D& condition) {
        boundaryCondition = &condition;
    }
    const BoundaryCondition2D& getBoundaryCondition() const {
        return *boundaryCondition;
    }
};

BoundarySegment2D* createRadialSegment2D(const QuadratureConversion& radius_func,
    const QuadratureConversion& radius_derivative_func, const int M);
BoundarySegment2D* createArcSegment2D(const cScalar center, const Scalar R, const Scalar t0,
                                      const Scalar t1, const int M);
BoundarySegment2D* createFunctionalSegment2D(const BoundaryFunc& z_complex_func,
        const BoundaryFunc& z_complex_derivative_func, const int M,
        const cScalar offset = 0, const cScalar scale = 1);

class Boundary2D {
public:
    virtual ~Boundary2D();
    virtual void addSegment(const BoundarySegment2D& boundary);

    virtual void recalculate();

    virtual int64_t getPointCount();
    virtual const cVector& getPoints() const;
    virtual const cVector& getPointDerivatives() const;
    virtual const cVector& getNormals() const;
    virtual const Vector& getWeights() const;
};

}

#endif /* EMPIRICAL_BOUNDARY_HPP_ */
