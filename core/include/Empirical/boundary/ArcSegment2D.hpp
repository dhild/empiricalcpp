#ifndef EMPIRICAL_BOUNDARY_ARC_SEGMENT_2D_HPP_
#define EMPIRICAL_BOUNDARY_ARC_SEGMENT_2D_HPP_

#include "Empirical/Boundary.hpp"

namespace Empirical {

class ArcSegment2D : public FunctionalBoundary2D {
private:
    Quadrature* quadrature;
public:
    ArcSegment2D(const QuadratureConversion& Z, const QuadratureConversion& ZPrime, const int64_t M);

    virtual ~ArcSegment2D();

    virtual const Vector& getWeights() const;
    virtual const Vector& getQuadraturePoints() const;
};

}

#endif /* EMPIRICAL_BOUNDARY_ARC_SEGMENT_2D_HPP_ */
