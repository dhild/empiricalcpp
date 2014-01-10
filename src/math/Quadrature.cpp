#include <Empirical/Quadrature>

using namespace empirical;
using namespace Eigen;

const Scalar empirical::PI = 3.141592653589793238L;

Quadrature::~Quadrature() {
}

void Quadrature::recalc() {
}

void Quadrature::update(const int N, const Scalar a, const Scalar b) {
    this->N = N;
    this->a = a;
    this->b = b;
    x.resize(N);
    w.resize(N);
    this->recalc();
}

TrapezoidQuadrature::~TrapezoidQuadrature() {
}

void TrapezoidQuadrature::recalc() {
    const int N = this->N;
    Scalar dist = this->b - this->a;
    Scalar delta = dist / (N - 1);

    for (int i = 0; i < N; i++) {
        this->x(i) = this->a + i * delta;
        this->w(i) = delta;
    }

    this->w(0) *= 0.5;
    this->w(N - 1) *= 0.5;
}

PeriodicTrapezoid::~PeriodicTrapezoid() {
}

void PeriodicTrapezoid::recalc() {
    const int N = this->N;
    Scalar dist = this->b - this->a;
    Scalar shift = dist / (2 * N);

    Scalar x0 = this->a + shift;
    Scalar x1 = this->b - shift;

    Scalar delta = (x1 - x0) / Scalar(N - 1);

    for (int i = 0; i < N; i++) {
        this->x(i) = x0 + i * delta;
    }
    this->w.setConstant(delta);
}

LegendreGaussLobatto::~LegendreGaussLobatto() {
}

void LegendreGaussLobatto::recalc() {
    const int N = this->N;
    Array<Scalar, Dynamic, 1> x1;
    Array<Scalar, Dynamic, 1> x2;
    Array<Scalar, Dynamic, Dynamic> P;

    x1.resize(N, 1);
    x2.resize(N, 1);
    P.resize(N, N);

    for (int i = 0; i < N; i++) {
        x1(i) = PI * i / Scalar(N - 1);
    }

    x1 = x1.cos();
    x2.array().setConstant(2);
    P.array().setZero();

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
    const Scalar delta = (this->b - this->a) / 2.0;
    const Scalar middle = this->a + delta;
    this->x = middle + (delta * x1.reverse());
    this->w = middle + (delta * x2.reverse());
}
