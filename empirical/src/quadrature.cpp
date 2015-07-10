#include <empiricalcpp/src/quadrature.hpp>
#include <cassert>
#include <boost/multi_array.hpp>
#include <Eigen/Dense>

using empirical::Scalar;
using empirical::epsScalar;
using empirical::PI;
using namespace empirical::quadrature;

namespace {

    Quadrature::points_weights_type trapezoid_gen(const Quadrature::size_type N1, const Scalar min, const Scalar max) {
        Quadrature::vector_type points(N1), weights(N1);
        const Quadrature::size_type N = N1 - 1;
        const Scalar step = (max - min) / N;
        const Scalar weight = (max - min) / N;
        for (Quadrature::size_type i = 0; i < N1; i++) {
            points[i] = min + i * step;
            weights[i] = weight;
        }
        weights[0] = weight / 2.0;
        weights[N - 1] = weight / 2.0;
        return Quadrature::points_weights_type({ points, weights });
    }

    Quadrature::points_weights_type periodic_trapezoid_gen(const Quadrature::size_type N1, const Scalar min, const Scalar max) {
        Quadrature::vector_type points(N1), weights(N1);
        const Scalar step = (max - min) / N1;
        const Scalar weight = (max - min) / N1;
        for (Quadrature::size_type i = 0; i < N1; i++) {
            points[i] = (2 * min + step * (2 * i + 1)) / 2;
            weights[i] = weight;
        }
        return Quadrature::points_weights_type({ points, weights });
    }

    Quadrature::points_weights_type lgl_gen(const Quadrature::size_type N1, const Scalar min, const Scalar max) {
        using namespace Eigen;
        typedef Array<Scalar, Dynamic, 1> Vector;
        const int64_t N = N1 - 1;

        Vector x = Vector::LinSpaced(N1, 0, PI).cos();
        Vector xold = Vector::Constant(N1, 1, Scalar(2));
        Array<Scalar, Dynamic, Dynamic> P = Array<Scalar, Dynamic, Dynamic>::Zero(N1, N1);

        while ((x - xold).abs().maxCoeff() > epsScalar) {
            xold = x;
            P.col(0).setOnes();
            P.col(1) = x;

            for (Quadrature::size_type k = 2; k < N1; k++) {
                P.col(k) = (Scalar(2 * k - 1) * x * P.col(k - 1) - Scalar(k - 1) * P.col(k - 2)) / Scalar(k);
            }
            x = xold - (x * P.col(N) - P.col(N - 1)) / (Scalar(N1) * P.col(N));
        }

        // Populate x2 with the weights.
        xold = Scalar(max - min) / (Scalar(N) * Scalar(N1) * P.col(N).square());

        // Reverse the arrays and store them.
        Quadrature::vector_type points(N1);
        Quadrature::vector_type weights(N1);

        const Scalar scale = (max - min) / 2.0;
        const Scalar mid = min + scale;
        for (Quadrature::size_type i = 0; i < N1; i++) {
            points[i] = mid + (x(N - i, 0) * scale);
            weights[i] = xold(N - i, 0);
        }
        return Quadrature::points_weights_type({ points, weights });
    }

}

namespace empirical {
    namespace quadrature {

        Quadrature trapezoid(const Quadrature::size_type N, const Scalar min, const Scalar max) {
            return Quadrature(trapezoid_gen, N, min, max);
        }

        Quadrature periodicTrapezoid(const Quadrature::size_type N, const Scalar min, const Scalar max) {
            return Quadrature(periodic_trapezoid_gen, N, min, max);
        }

        Quadrature legendreGaussLobatto(const Quadrature::size_type N, const Scalar min, const Scalar max) {
            return Quadrature(lgl_gen, N, min, max);
        }
    }
}
