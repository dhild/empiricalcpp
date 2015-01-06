#ifndef EMPIRICAL_PROBLEM_RADIAL_SEGMENT_2D_HPP_
#define EMPIRICAL_PROBLEM_RADIAL_SEGMENT_2D_HPP_

#include "Empirical/Boundary.hpp"

namespace Empirical {

class Quadrature;

class RadialSegment2D : public FunctionalBoundary2D {
private:
    Quadrature* quadrature;
public:

    RadialSegment2D(const QuadratureConversion& Z, const QuadratureConversion& ZPrime, const int64_t M);

    virtual ~RadialSegment2D();

    virtual const Vector& getWeights() const;
    virtual const Vector& getQuadraturePoints() const;
};

}

#endif /* EMPIRICAL_PROBLEM_RADIAL_SEGMENT_2D_HPP_ */
