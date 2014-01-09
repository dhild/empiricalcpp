#include <cmath>
#include <complex>
#include "basis.h"
#include "config.h"

using namespace empirical;
using namespace Eigen;
using namespace std;


template<typename Scalar>
complex<Scalar> evaluateHankel(const Scalar k, const Scalar r) {
    if (k == 0) {
        return -log(r) / (2.0 * PI);
    }

    return complex<Scalar>(0.25j) * hankel1(0, k * r);
}

template<typename Scalar>
template<typename evalScalar>
complex<evalScalar> MFSBasis2D<Scalar>::operator()(const evalScalar x, const evalScalar y) const {

}

template<typename Scalar>
template<typename evalScalar>
complex<evalScalar> MFSBasis2D<Scalar>::operator()(const Array<evalScalar, Dynamic, 2> xy) const {
}

template<typename Scalar>
template<typename cScalar>
Matrix<complex<cScalar>, Dynamic, Dynamic> MFSBasis2D<Scalar>::operator()(
        const Matrix<complex<cScalar>, Dynamic, Dynamic> complexPoints) const {
}

template<typename Scalar>
complex<Scalar> hankel1(const complex<Scalar> v, const Scalar z) {
    return 1.0;
}

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
