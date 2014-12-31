#ifndef EMPIRICAL_QUADRATURE_TRAPEZOID_HPP_
#define EMPIRICAL_QUADRATURE_TRAPEZOID_HPP_

#include "Empirical/Quadrature.hpp"

namespace Empirical {

class TrapezoidQuadrature : public Quadrature {
private:
    virtual void recalc(const int64_t N);
public:
    TrapezoidQuadrature(const int64_t N);
    virtual ~TrapezoidQuadrature();
};
}

#endif /* EMPIRICAL_QUADRATURE_TRAPEZOID_HPP_ */
