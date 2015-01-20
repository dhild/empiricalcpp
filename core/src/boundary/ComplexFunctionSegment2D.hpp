#ifndef EMPIRICAL_BOUNDARY_COMPLEX_FUNCTION_SEGMENT_2D_HPP_
#define EMPIRICAL_BOUNDARY_COMPLEX_FUNCTION_SEGMENT_2D_HPP_

#include "BaseFunctionalBoundary2D.hpp"

namespace Empirical {

class ComplexFunctionSegment2D : public BaseFunctionalBoundary2D {
    Quadrature* quadrature;

public:
    ComplexFunctionSegment2D(const QuadratureConversion& Z, const QuadratureConversion& ZPrime, const int64_t M);

    virtual ~ComplexFunctionSegment2D();

    virtual const Vector& getWeights() const;
    virtual const Vector& getQuadraturePoints() const;

    virtual void resize(const int64_t M);
};

}

#endif /* EMPIRICAL_BOUNDARY_COMPLEX_FUNCTION_SEGMENT_2D_HPP_ */
