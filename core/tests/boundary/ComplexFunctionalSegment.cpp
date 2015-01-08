#include "Boundary.hpp"

using namespace Empirical;
using namespace std;

namespace {

cScalar complexFunc(const cScalar t) {
    Scalar val = (imag(t) / PI) - 1;
    BOOST_CHECK(-1 <= val);
    BOOST_CHECK(val <= 1);
    BOOST_CHECK(abs(0 - real(t)) <= epsScalar);
    return exp(t);
}

cScalar complexDerivFunc(const cScalar t) {
    Scalar val = (imag(t) / PI) - 1;
    BOOST_CHECK(-1 <= val);
    BOOST_CHECK(val <= 1);
    BOOST_CHECK(abs(0 - real(t)) <= epsScalar);
    return cScalar(0, PI) * exp(t);
}

cScalar cfPoint(const Scalar t) {
    return exp(cScalar(0, PI * (t + 1)));
}

cScalar cfDeriv(const Scalar t) {
    return cScalar(0, PI) * exp(cScalar(0, PI * (t + 1)));
}

cScalar cfNorm(const Scalar t) {
    cScalar d = cfDeriv(t);
    Scalar mag = abs(d);
    return cScalar(imag(d) / mag, -real(d) / mag);
}

BOOST_AUTO_TEST_CASE( ComplexFunctionSegment2DCreation ) {
    CreationFunction boundCreate = bind(createFunctionalSegment2D, complexFunc, complexDerivFunc, 10, 1, cScalar(0, PI));
    testCreation(boundCreate, 10);
}

BOOST_AUTO_TEST_CASE( ComplexFunctionSegment2DRecalculation ) {
    CreationFunction boundCreate = bind(createFunctionalSegment2D, complexFunc, complexDerivFunc, 10, 1, cScalar(0, PI));
    testRecalculation(boundCreate, 10);
}

BOOST_AUTO_TEST_CASE( ComplexFunctionSegment2DPoints ) {
    CreationFunction boundCreate = bind(createFunctionalSegment2D, complexFunc, complexDerivFunc, 10, 1, cScalar(0, PI));
    testPoints(boundCreate, cfPoint);
}

BOOST_AUTO_TEST_CASE( ComplexFunctionSegment2DPointDerivatives ) {
    CreationFunction boundCreate = bind(createFunctionalSegment2D, complexFunc, complexDerivFunc, 10, 1, cScalar(0, PI));
    testPointDerivatives(boundCreate, cfDeriv);
}

BOOST_AUTO_TEST_CASE( ComplexFunctionSegment2DNormals ) {
    CreationFunction boundCreate = bind(createFunctionalSegment2D, complexFunc, complexDerivFunc, 10, 1, cScalar(0, PI));
    testNormals(boundCreate, cfNorm);
}
}
