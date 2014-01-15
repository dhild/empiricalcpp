#ifndef EMPIRICAL_DOMAIN_BVP_HPP
#define	EMPIRICAL_DOMAIN_BVP_HPP

#include "Empirical/src/problem/Problem.hpp"

namespace empirical {

    class BVP : public Problem {
    protected:
        
        virtual void fillQuadratureWeights();
        virtual void setupBasisDofs();
        virtual void fillBCMatrix();
        
    public:
        
        virtual ~BVP();
        
        virtual const Scalar bcResidualNorm() const;
        
    };
    
}

#endif	/* EMPIRICAL_DOMAIN_BVP_HPP */

