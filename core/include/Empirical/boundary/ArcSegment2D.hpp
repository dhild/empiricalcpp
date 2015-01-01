#ifndef EMPIRICAL_BOUNDARY_ARC_SEGMENT_2D_HPP_
#define EMPIRICAL_BOUNDARY_ARC_SEGMENT_2D_HPP_

#include "Empirical/Boundary.hpp"

namespace Empirical {

class ArcSegment2D : public FunctionalBoundary2D {
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

    virtual const Vector& getWeights() const;
    virtual const Vector& getQuadraturePoints() const;
};

}

#endif /* EMPIRICAL_BOUNDARY_ARC_SEGMENT_2D_HPP_ */
