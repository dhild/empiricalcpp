#ifndef EMPIRICAL_BASIS_H
#define EMPIRICAL_BASIS_H

#include <complex>
#include <Eigen/Dense>
#include "quadrature.h"

namespace empirical {

    template<typename Scalar>
    class MFSBasis2D {
    private:
        Eigen::Array<Scalar, Eigen::Dynamic, 2> q;

    public:
        MFSBasis2D(Eigen::Array<Scalar, Eigen::Dynamic, 2>& chargePoints)
                : q(chargePoints) {
        }

        /** Gets the result of applying this basis function to the given coordinates. */
        template<typename evalScalar>
        std::complex<evalScalar> operator()(const evalScalar x, const evalScalar y) const;

        /** Gets the result of applying this basis function to the given coordinates. */

        template<typename evalScalar>
        std::complex<evalScalar> operator()(const Eigen::Array<evalScalar, Eigen::Dynamic, 2> xy) const;

        /** For this operator, the matrix values are interpreted as points in the z plane.
         *
         * z = x + iy
         */
        template<typename cScalar>
        Eigen::Matrix<std::complex<cScalar>, Eigen::Dynamic, Eigen::Dynamic> operator()(
                const Eigen::Matrix<std::complex<cScalar>, Eigen::Dynamic, Eigen::Dynamic> complexPoints) const;

    private:
        MFSBasis2D(const MFSBasis2D& basis);

    };

    template<typename Scalar>
    std::complex<Scalar> hankel1(const std::complex<Scalar> v, const Scalar z);

}

#endif // EMPIRICAL_BASIS_H
