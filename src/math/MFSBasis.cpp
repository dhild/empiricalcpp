#include <cmath>
#include <complex>
#include <Empirical/Basis>
#include <boost/math/special_functions/hankel.hpp>

using namespace empirical;
using namespace Eigen;
using namespace std;

MFSBasis2D::MFSBasis2D(Array<Scalar, Dynamic, 2>& chargePoints)
        : q(chargePoints.rows()) {
    q = (chargePoints.cast<cScalar>().col(0) + 1j * chargePoints.cast<cScalar>().col(1));
}

MFSBasis2D::MFSBasis2D(Array<cScalar, Dynamic, 1>& chargePoints)
        : q(chargePoints) {
}

cScalar evaluateBasis(const Scalar k, const Scalar r) {
    if (k == 0) {
        return -log(r) / (2.0 * PI);
    }

    return cScalar(0.25j) * boost::math::cyl_hankel_1(0, k * r);
}

class BasisEvaluator {
private:
    const Scalar k;

public:
    BasisEvaluator(const Scalar& kValue)
            : k(kValue) {
    }

    const cScalar operator()(const cScalar& x) const {
        return evaluateBasis(k, abs(x));
    }
};

class CombinedBasisEvaluator {
private:
    const BasisEvaluator basis;
    const Array<cScalar, Dynamic, 1>& q;

public:
    CombinedBasisEvaluator(const Scalar& k, const Array<cScalar, Dynamic, 1>& chargePoints)
            : basis(k), q(chargePoints) {
    }

    const cScalar operator()(const cScalar& x) const {
        return (q - x).unaryExpr(basis).sum();
    }
};

const cScalar MFSBasis2D::operator()(const Scalar& k, const cScalar& z) const {
    CombinedBasisEvaluator functor(k, q);

    return functor(z);
}

const cScalar MFSBasis2D::operator()(const Scalar& k, const Scalar& x, const Scalar& y) const {
    CombinedBasisEvaluator functor(k, q);

    return functor(x + 1j * y);
}

const Matrix<cScalar, Dynamic, Dynamic> MFSBasis2D::operator()(const Scalar& k,
        const Matrix<cScalar, Dynamic, Dynamic>& z) const {
    CombinedBasisEvaluator functor(k, q);

    return z.unaryExpr(functor);
}

const Array<cScalar, Dynamic, Dynamic> MFSBasis2D::operator()(const Scalar& k,
        const Array<cScalar, Dynamic, Dynamic>& z) const {
    CombinedBasisEvaluator functor(k, q);

    return z.unaryExpr(functor);
}
