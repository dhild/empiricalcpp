#ifndef EMPIRICAL_SRC_QUADRATURE_LEGENDRE_GAUSS_LOBATTO_HPP_
#define EMPIRICAL_SRC_QUADRATURE_LEGENDRE_GAUSS_LOBATTO_HPP_

#include <Empirical/Quadrature.hpp>

namespace Empirical {

class LegendreGaussLobatto : public Quadrature {
private:
    virtual void recalc(const int64_t N);
public:
    LegendreGaussLobatto(const int64_t N);
    virtual ~LegendreGaussLobatto();
};
}

#endif /* EMPIRICAL_SRC_QUADRATURE_LEGENDRE_GAUSS_LOBATTO_HPP_ */
