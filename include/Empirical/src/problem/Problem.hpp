#ifndef PROBLEM_DEFINITION_HPP_
#define PROBLEM_DEFINITION_HPP_

#import<boost/any.hpp>
#import<tuple>

namespace empirical 

    typedef std::tuple<boost::any>> Parameters;

    class Problem {
    protected:
        
        virtual void fillQuadratureWeights();
        virtual void fillRHS();
        virtual void setupBasisDofs();
        virtual void fillBCMatrix();
        virtual void linsolve(const Parameters& parameters);
        
    public:
        
        virtual ~Problem();
        
        virtual void solve(const Parameters& parameters);
        
    };

}

#endif /* PROBLEM_DEFINITION_HPP_ */
