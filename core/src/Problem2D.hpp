#ifndef EMPIRICAL_LIBMATH_PROBLEM2D_HPP_
#define EMPIRICAL_LIBMATH_PROBLEM2D_HPP_

#include "Empirical/problem/BoundaryValueProblem2D.hpp"
#include <vector>

namespace Empirical {

class BoundaryValueSolution2D : public Solution2D {
protected:
    std::vector<std::function<cScalar(const cScalar)>> components;

public:
    BoundaryValueSolution2D(const int N);

    virtual ~BoundaryValueSolution2D();

    virtual void addBasis(const std::function<cScalar(const cScalar)>& basis,
                          const cScalar coefficient);

    virtual cScalar operator()(const cScalar point) const;
    virtual cVector operator()(const cVector& points) const;
    virtual cMatrix operator()(const cMatrix& points) const;
};

}

#endif /* EMPIRICAL_LIBMATH_PROBLEM2D_HPP_ */
