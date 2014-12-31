#ifndef EMPIRICAL_PROBLEM_ARC_SEGMENT_2D_HPP_
#define EMPIRICAL_PROBLEM_ARC_SEGMENT_2D_HPP_

#include "Empirical/Boundary.hpp"

namespace Empirical {

class ArcSegment2D : public BoundarySegment2D {
private:
    Quadrature* quadrature;
    const cScalar center;
    const Scalar radius;
    const Scalar t_scale;
    const Scalar t_offset;

    cScalar pointsFunc(const Scalar t) const;
    cScalar pointDerivativesFunc(const Scalar t) const;
public:
    ArcSegment2D(const cScalar center, const Scalar R, const Scalar t0,
                 const Scalar t1, const int M);

    virtual ~ArcSegment2D();

    virtual void recalculate(const int64_t M);
};

}

#endif /* EMPIRICAL_PROBLEM_ARC_SEGMENT_2D_HPP_ */
