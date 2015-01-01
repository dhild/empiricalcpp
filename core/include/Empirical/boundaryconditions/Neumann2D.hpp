#ifndef EMPIRICAL_BOUNDARY_CONDITIONS_NEUMANN_2D_HPP_
#define EMPIRICAL_BOUNDARY_CONDITIONS_NEUMANN_2D_HPP_

#include "Empirical/BoundaryCondition.hpp"

namespace Empirical {

class NeumannCondition2D : public BoundaryCondition2D {
protected:
    BoundaryFunc normalValues;
public:
    NeumannCondition2D(const BoundaryFunc normalValues);

    virtual ~NeumannCondition2D();

    virtual bool requiresPoint() const;
    virtual bool requiresNormal() const;

    virtual cScalar operator()(const cScalar x) const;
    virtual cScalar normal(const cScalar x) const;
};

}

#endif /* EMPIRICAL_BOUNDARY_CONDITIONS_NEUMANN_2D_HPP_ */
