#include <functional>
#include <Empirical/Quadrature>

using namespace empirical;
using namespace Eigen;
using namespace std;

const Scalar empirical::PI = 3.141592653589793238L;

TrapezoidQuadrature::TrapezoidQuadrature(const int N) : Quadrature(N) {
    this->points.setLinSpaced(0, 1);

    this->weights.setConstant(1 / (N - 1));
}

LegendreGaussLobatto::LegendreGaussLobatto(const int N) : Quadrature(N) {
    Array<Scalar, Dynamic, 1> x1 = Array<Scalar, Dynamic, 1>::LinSpaced(N, 0, PI).cos();
    Array<Scalar, Dynamic, 1> x2 = Array<Scalar, Dynamic, 1>::Constant(N, 1, Scalar(2));
    Array<Scalar, Dynamic, Dynamic> P = Array<Scalar, Dynamic, Dynamic>::Zero(N, N);

    while ((x1 - x2).abs().maxCoeff() > (1e-15)) {
        x2 = x1;
        P.col(0).setOnes();
        P.col(1) = x1;

        for (int k = 2; k < N; k++) {
            P.col(k) = (Scalar(2 * k - 1) * x1 * P.col(k - 1) - Scalar(k - 1) * P.col(k - 2)) / Scalar(k);
        }
        x1 = x2 - (x1 * P.col(N - 1) - P.col(N - 2)) / (Scalar(N) * P.col(N - 1));
    }

    // Populate x2 with the weights.
    x2 = 2.0 / ((N - 1) * Scalar(N) * P.col(N - 1).square());

    // Reverse the arrays and store them.
    this->points = 0.5 + x1.reverse();
    this->weights = 0.5 + 0.5 * x2.reverse();
}
