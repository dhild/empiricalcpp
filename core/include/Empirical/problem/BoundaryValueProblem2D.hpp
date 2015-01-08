#ifndef EMPIRICAL_DOMAIN_BVP_HPP_
#define EMPIRICAL_DOMAIN_BVP_HPP_

#include "Empirical/Domain.hpp"
#include "Empirical/Basis.hpp"
#include <vector>

namespace Empirical {

class Solution2D {
protected:
    Solution2D();

public:
    virtual ~Solution2D();

    virtual cScalar operator()(const cScalar point) const;
    virtual cVector operator()(const cVector& points) const;
    virtual cMatrix operator()(const cMatrix& points) const;
};

class BoundaryValueProblem2D {
protected:
    std::vector<Domain2D*> domains;

    cMatrix boundary_condition_matrix;
    cVector right_hand_side;
    cVector solution_coeficients;
    Solution2D* solution;

    bool boundary_condition_dirty;
    bool right_hand_side_dirty;

public:

    BoundaryValueProblem2D();

    virtual ~BoundaryValueProblem2D();

    virtual void addDomain(Domain2D* domain);

    virtual const Solution2D& solve();

    virtual Scalar conditionNumber() const;
    virtual Scalar residualNorm() const;

    virtual const Solution2D& getSolution() const;
};

}

#endif  /* EMPIRICAL_DOMAIN_BVP_HPP_ */

