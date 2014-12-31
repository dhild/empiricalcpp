#ifndef EMPIRICAL_BOUNDARY_HPP_
#define EMPIRICAL_BOUNDARY_HPP_

#include "Empirical/Quadrature.hpp"

namespace Empirical {

class BoundarySegment2D {
protected:
    Quadrature* quadrature;
public:
    BoundarySegment2D(Quadrature* quad) : quadrature(quad) {}
    virtual ~BoundarySegment2D();

    virtual void recalculate(const int64_t M);

    virtual const cVector& getPoints() const;
    virtual const cVector& getPointDerivatives() const;
    virtual const cVector& getNormals() const;

    virtual int64_t size() const;
    virtual const Vector& getWeights() const;
    virtual const Vector& getT() const;

    virtual void setBoundaryCondition(const BoundaryCondition2D& condition);
    virtual const BoundaryCondition2D& getBoundaryCondition() const;
};

}

#endif /* EMPIRICAL_BOUNDARY_HPP_ */
