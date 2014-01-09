#include "config.h"
#include "quadrature.h"

using namespace empirical;
using namespace Eigen;

template<typename Scalar>
void LegendreGaussLobatto<Scalar>::recalc() {
    Array<Scalar, Dynamic, 1> x1;
    Array<Scalar, Dynamic, 1> x2;
    Array<Scalar, Dynamic, Dynamic> P;

    x1.resize(this->N, 1);
    x2.resize(this->N, 1);
    P.resize(this->N, this->N);

    for (int i = 0; i < this->N; i++) {
        x1(i) = PI * i / Scalar(this->N - 1);
    }

    x1 = x1.cos();
    x2.array().setConstant(2);
    P.array().setZero();

    while ((x1 - x2).abs().maxCoeff() > (1e-15)) {
        x2 = x1;
        P.col(0).setOnes();
        P.col(1) = x1;

        for (int k = 2; k < this->N; k++) {
            P.col(k) = (Scalar(2 * k - 1) * x1 * P.col(k - 1) - Scalar(k - 1) * P.col(k - 2)) / Scalar(k);
        }
        x1 = x2 - (x1 * P.col(this->N - 1) - P.col(this->N - 2)) / (Scalar(this->N) * P.col(this->N - 1));
    }

    // Populate x2 with the weights.
    x2 = 2.0 / ((this->N - 1) * Scalar(this->N) * P.col(this->N - 1).square());

    // Reverse the arrays and store them.
    for (int i = 0; i < this->N; i++) {
        x(this->N - i - 1) = x1(i);
        w(this->N - i - 1) = x2(i);
    }
}
