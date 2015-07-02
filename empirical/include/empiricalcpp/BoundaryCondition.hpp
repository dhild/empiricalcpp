#ifndef EMPIRICAL_BOUNDARY_CONDITION_HPP_
#define EMPIRICAL_BOUNDARY_CONDITION_HPP_

#include <Empirical/Constants.hpp>
#include <functional>

namespace Empirical {

typedef std::function<cScalar(const cScalar)> BoundaryFunc;

extern const BoundaryFunc zeroFunction;

class BoundaryCondition2D {
protected:
    BoundaryCondition2D() {}

public:
    virtual ~BoundaryCondition2D() {}

    virtual bool requiresPoint() const = 0;
    virtual bool requiresNormal() const = 0;

    virtual cScalar operator()(const cScalar x) const = 0;
    virtual cScalar normal(const cScalar x) const = 0;
};

BoundaryCondition2D* createDirichlet(const BoundaryFunc pointValues);
BoundaryCondition2D* createNeumann(const BoundaryFunc normalValues);
BoundaryCondition2D* createCauchy(const BoundaryFunc pointValues, const BoundaryFunc normalValues);

}

#endif /* EMPIRICAL_BOUNDARY_CONDITION_HPP_ */
