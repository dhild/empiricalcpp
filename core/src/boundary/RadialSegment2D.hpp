#ifndef EMPIRICAL_SRC_BOUNDARY_RADIAL_SEGMENT_2D_HPP_
#define EMPIRICAL_SRC_BOUNDARY_RADIAL_SEGMENT_2D_HPP_

#include "BaseFunctionalBoundary2D.hpp"

namespace Empirical {

class RadialSegment2D : public BaseFunctionalBoundary2D {
    Quadrature* quadrature;
public:

    RadialSegment2D(const QuadratureConversion& Z, const QuadratureConversion& ZPrime, const int64_t M);

    virtual ~RadialSegment2D();

    virtual const Vector& getWeights() const;
    virtual const Vector& getQuadraturePoints() const;

    virtual void resize(const int64_t M);
};

}

#endif /* EMPIRICAL_SRC_BOUNDARY_RADIAL_SEGMENT_2D_HPP_ */
