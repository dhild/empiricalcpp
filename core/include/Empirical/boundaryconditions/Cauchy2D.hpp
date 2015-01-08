#ifndef EMPIRICAL_BOUNDARY_CONDITIONS_CAUCHY_2D_HPP_
#define EMPIRICAL_BOUNDARY_CONDITIONS_CAUCHY_2D_HPP_

#include "Empirical/BoundaryCondition.hpp"

namespace Empirical {

class CauchyCondition2D : public BoundaryCondition2D {
protected:
    BoundaryFunc pointValues;
    BoundaryFunc normalValues;
public:
    CauchyCondition2D(const BoundaryFunc pointValues, const BoundaryFunc normalValues);

    virtual ~CauchyCondition2D();

    virtual bool requiresPoint() const;
    virtual bool requiresNormal() const;

    virtual cScalar operator()(const cScalar x) const;
    virtual cScalar normal(const cScalar x) const;
};

}

#endif /* EMPIRICAL_BOUNDARY_CONDITIONS_CAUCHY_2D_HPP_ */
