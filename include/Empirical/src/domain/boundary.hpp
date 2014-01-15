#ifndef BOUNDARY_HPP_
#define BOUNDARY_HPP_

#include "Empirical/src/quadrature/Quadrature.hpp"

namespace empirical {

    class BoundaryCondition {
    protected:
        BoundaryCondition();
        BoundaryCondition(const BoundaryCondition& other);
        virtual const BoundaryCondition& operator=(const BoundaryCondition& other);

    public:

        virtual const bool requiresPoint() const;
        virtual const bool requiresNormal() const;
        virtual const bool hasNonZeroRHS() const;
        virtual const bool applyToPositiveNormalSide() const;

        virtual const cScalar operator()(const cScalar& point, const cScalar& normal) const;

        /**
         * @param t A value in [0,1] that indicates the
         * @return
         */
        virtual const cScalar rhs(const Scalar& t) const;

        virtual ~BoundaryCondition();

    };

}

#endif /* BOUNDARY_HPP_ */
