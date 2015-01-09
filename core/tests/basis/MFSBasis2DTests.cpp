#include <Empirical/Basis.hpp>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <cmath>
#include <memory>

using namespace std;
using namespace Empirical;
using namespace boost::math;

namespace {

cScalar radialFunc(const Scalar) {
    return 1;
}

cScalar radialDerivFunc(const Scalar) {
    return 0;
}

cScalar hankel(const Scalar v, const Scalar x) {
    return cyl_bessel_j(v, x) + cScalar(0, 1) * cyl_neumann(v, x);
}

#define CHECK_CLOSE(x, y, eps) BOOST_CHECK_CLOSE(real(x), real(y), eps); \
BOOST_CHECK_CLOSE(imag(x), imag(y), eps)

BOOST_AUTO_TEST_SUITE(MFSBasis2DTests)

BOOST_AUTO_TEST_CASE(Basis2DCreation) {
    auto boundary = unique_ptr<RefinableBoundary2D>(createRadialSegment2D(radialFunc, radialDerivFunc, 50));
    auto basis = unique_ptr<Basis2D>(createMFSBasis(boundary.get()));

    BOOST_CHECK_EQUAL(basis.get()->degreesOfFreedom(), 50);
    BOOST_CHECK_EQUAL(boundary.get()->size(), 50);
}

BOOST_AUTO_TEST_CASE(Basis2DResize) {
    auto boundary = unique_ptr<RefinableBoundary2D>(createRadialSegment2D(radialFunc, radialDerivFunc, 50));
    auto basis = unique_ptr<Basis2D>(createMFSBasis(boundary.get()));

    basis->resize(65);

    BOOST_CHECK_EQUAL(basis.get()->degreesOfFreedom(), 65);
    BOOST_CHECK_EQUAL(boundary.get()->size(), 65);
}

BOOST_AUTO_TEST_CASE(Basis2DBasisFunction) {
    auto boundary = unique_ptr<RefinableBoundary2D>(createRadialSegment2D(radialFunc, radialDerivFunc, 50));
    auto basis = unique_ptr<Basis2D>(createMFSBasis(boundary.get()));

    cScalar z = cScalar(5, 0.5);
    cScalar x = cScalar(-2.8, 580);
    cScalar dist = abs(z - x);
    cScalar expected = -log(dist) / (2 * PI);
    cScalar value = basis.get()->operator()(0.0, z, x);
    CHECK_CLOSE(expected, value, epsScalar);

    Scalar k = 450;
    expected = cScalar(0, 0.25) * hankel(0, k * abs(dist));
    value = basis.get()->operator()(k, z, x);
    CHECK_CLOSE(expected, value, epsScalar);
}

BOOST_AUTO_TEST_SUITE_END()
}
