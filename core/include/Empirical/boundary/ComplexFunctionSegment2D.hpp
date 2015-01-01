#ifndef EMPIRICAL_BOUNDARY_COMPLEX_FUNCTION_SEGMENT_2D_HPP_
#define EMPIRICAL_BOUNDARY_COMPLEX_FUNCTION_SEGMENT_2D_HPP_

#include "Empirical/Boundary.hpp"

namespace Empirical {

class ComplexFunctionSegment2D : public FunctionalBoundary2D {
private:
    Quadrature* quadrature;
    const cScalar offset;
    const cScalar scale;
    const std::function<cScalar(const cScalar)>& z_complex;
    const std::function<cScalar(const cScalar)>& z_complex_derivative;

    cScalar pointsFunc(const Scalar t) const;
    cScalar pointDerivativesFunc(const Scalar t) const;

public:
    ComplexFunctionSegment2D(
        const std::function<cScalar(const cScalar)>& z_complex_func,
        const std::function<cScalar(const cScalar)>& z_complex_derivative_func,
        const int M, const cScalar offset = 0, const cScalar scale = 1);

    virtual ~ComplexFunctionSegment2D();

    virtual const Vector& getWeights() const;
    virtual const Vector& getQuadraturePoints() const;
};

}

#endif /* EMPIRICAL_BOUNDARY_COMPLEX_FUNCTION_SEGMENT_2D_HPP_ */
