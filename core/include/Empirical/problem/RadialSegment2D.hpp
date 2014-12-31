#ifndef EMPIRICAL_PROBLEM_RADIAL_SEGMENT_2D_HPP_
#define EMPIRICAL_PROBLEM_RADIAL_SEGMENT_2D_HPP_

#include "Empirical/Boundary.hpp"

namespace Empirical {

class Quadrature;

class RadialSegment2D : public BoundarySegment2D {
private:
    Quadrature* quadrature;

    const std::function<cScalar(const Scalar)> radius;
    const std::function<cScalar(const Scalar)> radius_derivative;

    cScalar pointsFunc(const Scalar t) const;
    cScalar pointDerivativesFunc(const Scalar t) const;

public:

    RadialSegment2D(const std::function<cScalar(const Scalar)>& radius_func,
                    const std::function<cScalar(const Scalar)>&
                    radius_derivative_func,
                    const int M);

    virtual void recalculate(const int64_t M);

    virtual ~RadialSegment2D();
};

}

#endif /* EMPIRICAL_PROBLEM_RADIAL_SEGMENT_2D_HPP_ */
