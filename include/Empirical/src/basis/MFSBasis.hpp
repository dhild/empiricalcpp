#ifndef MFSBASIS_HPP_
#define MFSBASIS_HPP_

#include <Eigen/Dense>
#include "Empirical/src/config.h"

namespace empirical {

    class MFSBasis2D {
    private:
        Eigen::Array<cScalar, Eigen::Dynamic, 1> q;

    public:
        MFSBasis2D(Eigen::Array<Scalar, Eigen::Dynamic, 2>& chargePoints);
        MFSBasis2D(Eigen::Array<cScalar, Eigen::Dynamic, 1>& chargePoints);

        /** Gets the result of applying this basis function to the given complex coordinate. */
        const cScalar operator()(const Scalar& k, const cScalar& z) const;

        /** Gets the result of applying this basis function to the given coordinates. */
        const cScalar operator()(const Scalar& k, const Scalar& x, const Scalar& y) const;

        const Eigen::Matrix<cScalar, Eigen::Dynamic, Eigen::Dynamic> operator()(const Scalar& k,
                const Eigen::Matrix<cScalar, Eigen::Dynamic, Eigen::Dynamic>& z) const;

        const Eigen::Array<cScalar, Eigen::Dynamic, Eigen::Dynamic> operator()(const Scalar& k,
                const Eigen::Array<cScalar, Eigen::Dynamic, Eigen::Dynamic>& z) const;

    private:
        MFSBasis2D(const MFSBasis2D& basis);

    };

}

#endif /* MFSBASIS_HPP_ */
