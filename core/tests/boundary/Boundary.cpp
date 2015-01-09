#include "Boundary.hpp"

using namespace std;

namespace Empirical {
void checkSizes(const FunctionalBoundary2D& segment, const int64_t N) {
    BOOST_CHECK_EQUAL(N, segment.size());
    BOOST_CHECK_EQUAL(N, segment.getPoints().rows());
    BOOST_CHECK_EQUAL(N, segment.getPointDerivatives().rows());
    BOOST_CHECK_EQUAL(N, segment.getNormals().rows());
    BOOST_CHECK_EQUAL(1, segment.getPoints().cols());
    BOOST_CHECK_EQUAL(1, segment.getPointDerivatives().cols());
    BOOST_CHECK_EQUAL(1, segment.getNormals().cols());
    BOOST_CHECK_EQUAL(N, segment.getWeights().size());
    BOOST_CHECK_EQUAL(N, segment.getQuadraturePoints().size());
}

void checkClose(const Vector& t_vec, const cVector& p_vec,
                const function<cScalar(const Scalar t)> points) {
    for (int i = 0; i < t_vec.rows(); i++) {
        cScalar expected = points(t_vec(i, 0));
        cScalar actual = p_vec(i, 0);
        BOOST_CHECK(abs(real(expected) - real(actual)) <= 10 * epsScalar);
        BOOST_CHECK(abs(imag(expected) - imag(actual)) <= 10 * epsScalar);
    }
}

typedef function<FunctionalBoundary2D*()> CreationFunction;

void testCreation(CreationFunction create, const int64_t N) {
    unique_ptr<FunctionalBoundary2D> boundary(create());
    checkSizes(*boundary, N);
}

void testRecalculation(CreationFunction create, const int64_t N) {
    FunctionalBoundary2D* ptr = create();
    ptr->resize(N + 50);
    checkSizes(*ptr, N + 50);
    delete ptr;
}

void testPoints(CreationFunction create, QuadratureConversion point) {
    unique_ptr<FunctionalBoundary2D> boundary(create());
    checkClose(boundary->getQuadraturePoints(), boundary->getPoints(), point);
}

void testPointDerivatives(CreationFunction create, QuadratureConversion deriv) {
    unique_ptr<FunctionalBoundary2D> boundary(create());
    checkClose(boundary->getQuadraturePoints(), boundary->getPointDerivatives(), deriv);
}

void testNormals(CreationFunction create, QuadratureConversion norm) {
    unique_ptr<FunctionalBoundary2D> boundary(create());
    checkClose(boundary->getQuadraturePoints(), boundary->getNormals(), norm);
}
}
