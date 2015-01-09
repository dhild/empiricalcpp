#ifndef EMPIRICAL_QUADRATURE_PERIODIC_TRAPEZOID_HPP_
#define EMPIRICAL_QUADRATURE_PERIODIC_TRAPEZOID_HPP_

#include <Empirical/Quadrature.hpp>

namespace Empirical {

class PeriodicTrapezoidQuadrature : public Quadrature {
private:
    virtual void recalc(const int64_t N);
public:
    PeriodicTrapezoidQuadrature(const int64_t N);
    virtual ~PeriodicTrapezoidQuadrature();
};
}

#endif /* EMPIRICAL_QUADRATURE_PERIODIC_TRAPEZOID_HPP_ */
