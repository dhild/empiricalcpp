#ifndef EMPIRICAL_SRC_BOUNDARY_CONDITIONS_DIRICHLET_2D_HPP_
#define EMPIRICAL_SRC_BOUNDARY_CONDITIONS_DIRICHLET_2D_HPP_

#include <Empirical/BoundaryCondition.hpp>

namespace Empirical {

class DirichletCondition2D : public BoundaryCondition2D {
protected:
    BoundaryFunc pointValues;
public:
    DirichletCondition2D(const BoundaryFunc pointValues);

    virtual ~DirichletCondition2D();

    virtual bool requiresPoint() const;
    virtual bool requiresNormal() const;

    virtual cScalar operator()(const cScalar x) const;
    virtual cScalar normal(const cScalar x) const;
};

}

#endif /* EMPIRICAL_SRC_BOUNDARY_CONDITIONS_DIRICHLET_2D_HPP_ */
