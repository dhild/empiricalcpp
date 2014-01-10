#include <cmath>
#include <complex>
#include <Empirical/Basis>
#include <boost/math/special_functions/hankel.hpp>

using namespace empirical;
using namespace Eigen;
using namespace std;

cScalar evaluateBasis(const Scalar k, const Scalar r) {
    if (k == 0) {
        return -log(r) / (2.0 * PI);
    }

    return cScalar(0.25j) * boost::math::cyl_hankel_1(0, k * r);
}

cScalar MFSBasis2D::operator()(const Scalar x, const Scalar y) const {
    return
}

/** Gets the result of applying this basis function to the given coordinates. */
cScalar MFSBasis2D::operator()(const Eigen::Array<Scalar, Eigen::Dynamic, 2> xy) const {}

/** For this operator, the matrix values are interpreted as points in the z plane.
 *
 * z = x + iy
 */
Eigen::Matrix<cScalar, Eigen::Dynamic, Eigen::Dynamic> MFSBasis2D::operator()(
        const Eigen::Matrix<cScalar, Eigen::Dynamic, Eigen::Dynamic> complexPoints) const {}

//complex MFSBasis::evaluate(const double k, const double px, const double py, const double qx, const double qy) const {
//    const double dx = px - qx;
//    const double dy = py - qy;
//    const double r = sqrt(dx * dx + dy * dy);
//
//    return evaluateHankel(k, r);
//}
//
//Matrix<complex, Dynamic, Dynamic> Basis::getMatrix(const double k, const Quadrature& points) const {
//    const unsigned long N = q.getN();
//    const unsigned long M = points.getN();
//
//    Matrix < complex, Dynamic, Dynamic > matrix;
//    matrix.resize(M, N);
//
//    for (int i = 0; i < M; i++) {
//        const double px = points.getPoints()(i, 0);
//        const double py = points.getPoints()(i, 1);
//
//        for (int j = 0; j < N; j++) {
//            const double qx = q.getPoints()(j, 0);
//            const double qy = q.getPoints()(j, 1);
//
//            matrix(i, j) = evaluate(k, px, py, qx, qy);
//        }
//    }
//}
