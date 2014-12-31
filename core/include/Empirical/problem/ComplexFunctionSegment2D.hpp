#ifndef EMPIRICAL_PROBLEM_COMPLEX_FUNCTION_SEGMENT_2D_HPP_
#define EMPIRICAL_PROBLEM_COMPLEX_FUNCTION_SEGMENT_2D_HPP_

#include "Empirical/Boundary.hpp"

namespace Empirical {

class ComplexFunctionSegment2D : public BoundarySegment2D {
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

    virtual void recalculate(const int64_t M);

    virtual ~ComplexFunctionSegment2D();
};

}

#endif /* EMPIRICAL_PROBLEM_COMPLEX_FUNCTION_SEGMENT_2D_HPP_ */
