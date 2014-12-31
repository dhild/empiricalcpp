#ifndef EMPIRICAL_DOMAIN_BVP_HPP_
#define	EMPIRICAL_DOMAIN_BVP_HPP_

#include <vector>
#include "Empirical/Constants.hpp"
#include "Empirical/domain/Domain2D.hpp"
#include "Empirical/basis/Basis2D.hpp"

namespace Empirical {

class Solution2D {
protected:
    Solution2D();

public:
    virtual ~Solution2D();

    virtual cScalar operator()(const cScalar point) const;
    virtual Mesh1D operator()(const Mesh1D& points) const;
    virtual Mesh2D operator()(const Mesh2D& points) const;
};

class BoundaryValueProblem2D {
protected:
    std::vector<Domain2D*> domains;

    Mesh2D boundary_condition_matrix;
    Mesh1D right_hand_side;
    Mesh1D solution_coeficients;
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

#endif	/* EMPIRICAL_DOMAIN_BVP_HPP_ */

