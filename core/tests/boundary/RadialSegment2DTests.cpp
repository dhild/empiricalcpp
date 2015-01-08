#include "Boundary.hpp"

using namespace Empirical;
using namespace std;

namespace {

cScalar radialFunc(const Scalar angle) {
    BOOST_CHECK(-PI <= angle);
    BOOST_CHECK(angle <= PI);
    return 1;
}

cScalar radialDerivFunc(const Scalar angle) {
    BOOST_CHECK(-PI <= angle);
    BOOST_CHECK(angle <= PI);
    return 0;
}

cScalar rPoint(const Scalar t) {
    return exp(cScalar(0, PI * t));
}

cScalar rDeriv(const Scalar t) {
    return cScalar(0, PI) * exp(cScalar(0, PI * t));
}

cScalar rNorm(const Scalar t) {
    cScalar d = rDeriv(t);
    Scalar mag = abs(d);
    return cScalar(imag(d) / mag, -real(d) / mag);
}

BOOST_AUTO_TEST_CASE( RadialSegment2DTestsCreation ) {
    CreationFunction boundCreate = bind(createRadialSegment2D, radialFunc, radialDerivFunc, 10);
    testCreation(boundCreate, 10);
}

BOOST_AUTO_TEST_CASE( RadialSegment2DTestsRecalculation ) {
    CreationFunction boundCreate = bind(createRadialSegment2D, radialFunc, radialDerivFunc, 10);
    testRecalculation(boundCreate, 10);
}

BOOST_AUTO_TEST_CASE( RadialSegment2DTestsPoints ) {
    CreationFunction boundCreate = bind(createRadialSegment2D, radialFunc, radialDerivFunc, 10);
    testPoints(boundCreate, rPoint);
}

BOOST_AUTO_TEST_CASE( RadialSegment2DTestsPointDerivatives ) {
    CreationFunction boundCreate = bind(createRadialSegment2D, radialFunc, radialDerivFunc, 10);
    testPointDerivatives(boundCreate, rDeriv);
}

BOOST_AUTO_TEST_CASE( RadialSegment2DTestsNormals ) {
    CreationFunction boundCreate = bind(createRadialSegment2D, radialFunc, radialDerivFunc, 10);
    testNormals(boundCreate, rNorm);
}

}
