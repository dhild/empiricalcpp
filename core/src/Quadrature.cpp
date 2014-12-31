#include "Empirical/Quadrature.hpp"
#include "Empirical/quadrature/LegendreGaussLobatto.hpp"
#include "Empirical/quadrature/PeriodicTrapezoid.hpp"
#include "Empirical/quadrature/Trapezoid.hpp"
#include <functional>

using namespace Empirical;
using namespace Eigen;
using namespace std;

namespace Empirical {
Quadrature* createLGL(const int64_t N) {
    return new LegendreGaussLobatto(N);
}
Quadrature* createTrapezoid(const int64_t N) {
    return new TrapezoidQuadrature(N);
}
Quadrature* createPeriodicTrapezoid(const int64_t N) {
    return new PeriodicTrapezoidQuadrature(N);
}
}

TrapezoidQuadrature::TrapezoidQuadrature(const int64_t N) : Quadrature(N) {
    recalc(N);
}

TrapezoidQuadrature::~TrapezoidQuadrature() {}

void TrapezoidQuadrature::recalc(const int64_t N) {
    points.setLinSpaced(-1, 1);

    Scalar w = Scalar(1) / Scalar(N);
    weights.setConstant(2 * w);
    weights(0, 0) = w;
    weights(N - 1, 0) = w;
}

PeriodicTrapezoidQuadrature::PeriodicTrapezoidQuadrature(const int64_t N) : Quadrature(N) {
    recalc(N);
}

PeriodicTrapezoidQuadrature::~PeriodicTrapezoidQuadrature() {}

void PeriodicTrapezoidQuadrature::recalc(const int64_t N) {
    Scalar shift = Scalar(1) / Scalar(N);
    points.setLinSpaced(-1 + shift, 1 - shift);

    weights.setConstant(Scalar(2) / Scalar(N));
}

LegendreGaussLobatto::LegendreGaussLobatto(const int64_t N1) : Quadrature(N1) {
    recalc(N1);
}

LegendreGaussLobatto::~LegendreGaussLobatto() {}

void LegendreGaussLobatto::recalc(const int64_t N1) {
    const int64_t N = N1 - 1;

    Array<Scalar, Dynamic, 1> x = Array<Scalar, Dynamic, 1>::LinSpaced(N1, 0, PI).cos();
    Array<Scalar, Dynamic, 1> xold = Array<Scalar, Dynamic, 1>::Constant(N1, 1, Scalar(2));
    Array<Scalar, Dynamic, Dynamic> P = Array<Scalar, Dynamic, Dynamic>::Zero(N1, N1);

    while ((x - xold).abs().maxCoeff() > epsScalar) {
        xold = x;
        P.col(0).setOnes();
        P.col(1) = x;

        for (int64_t k = 2; k < N1; k++) {
            P.col(k) = (Scalar(2 * k - 1) * x * P.col(k - 1) - Scalar(k - 1) * P.col(k - 2)) / Scalar(k);
        }
        x = xold - (x * P.col(N) - P.col(N - 1)) / (Scalar(N1) * P.col(N));
    }

    // Populate x2 with the weights.
    xold = Scalar(2.0) / (Scalar(N) * Scalar(N1) * P.col(N).square());

    // Reverse the arrays and store them.
    this->points = x.reverse();
    this->weights = xold.reverse();
}
