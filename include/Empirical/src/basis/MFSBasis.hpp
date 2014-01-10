#ifndef MFSBASIS_HPP_
#define MFSBASIS_HPP_

#include <Eigen/Dense>
#include "Empirical/src/config.h"

namespace empirical {

    class MFSBasis2D {
    private:
        Eigen::Array<Scalar, Eigen::Dynamic, 2> q;

    public:
        MFSBasis2D(Eigen::Array<Scalar, Eigen::Dynamic, 2>& chargePoints)
                : q(chargePoints) {
        }

        /** Gets the result of applying this basis function to the given coordinates. */
        cScalar operator()(const Scalar x, const Scalar y) const;

        /** Gets the result of applying this basis function to the given coordinates. */
        cScalar operator()(const Eigen::Array<Scalar, Eigen::Dynamic, 2> xy) const;

        /** For this operator, the matrix values are interpreted as points in the z plane.
         *
         * z = x + iy
         */
        Eigen::Matrix<cScalar, Eigen::Dynamic, Eigen::Dynamic> operator()(
                const Eigen::Matrix<cScalar, Eigen::Dynamic, Eigen::Dynamic> complexPoints) const;

    private:
        MFSBasis2D(const MFSBasis2D& basis);

    };

}

#endif /* MFSBASIS_HPP_ */
