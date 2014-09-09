#ifndef EMPIRICAL_DOMAIN_BVP_HPP
#define	EMPIRICAL_DOMAIN_BVP_HPP

#include "Empirical/src/quadrature/Quadrature.hpp"
#include "Empirical/src/problem/Problem.hpp"

namespace empirical {

    class BVP2D : public Problem2D {
    protected:

        Vector2D rhs;

        virtual void fillQuadratureWeights();
        virtual void setupBasisDofs();
        virtual void fillBCMatrix();

    public:

        virtual ~BVP2D();

        virtual const Scalar bcResidualNorm() const;

    };

}

#endif	/* EMPIRICAL_DOMAIN_BVP_HPP */

