#include <Empirical/Domain.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <cmath>
#include <complex>
#include <functional>
#include <iostream>

using namespace Empirical;
using namespace Eigen;
using namespace std;

namespace {
void checkSizes(const FunctionalBoundary2D& segment, const int N) {
    BOOST_CHECK_EQUAL(N, segment.size());
    BOOST_CHECK_EQUAL(N, segment.getPoints().rows());
    BOOST_CHECK_EQUAL(N, segment.getPointDerivatives().rows());
    BOOST_CHECK_EQUAL(N, segment.getNormals().rows());
    BOOST_CHECK_EQUAL(N, segment.getWeights().size());
    BOOST_CHECK_EQUAL(N, segment.getQuadraturePoints().size());
}

void checkClose(const Vector& t_vec,
                const cVector& p_vec,
                const std::function<cScalar(const Scalar t)> points) {
    for (int i = 0; i < t_vec.rows(); i++) {
	cScalar expected = points(t_vec(i, 0));
	cScalar actual = p_vec(i, 0);
        BOOST_CHECK_CLOSE(real(expected), real(actual), 10 * epsScalar);
	BOOST_CHECK_CLOSE(imag(expected), imag(actual), 10 * epsScalar);
    }
}

typedef function<FunctionalBoundary2D*()> CreationFunction;

void testCreation(CreationFunction create, const int64_t N) {
    unique_ptr<FunctionalBoundary2D> boundary(create());
    checkSizes(*boundary, N);
}

void testRecalculation(CreationFunction create, const int64_t N) {
    unique_ptr<FunctionalBoundary2D> boundary(create());
    boundary->resize(N + 50);
    checkSizes(*boundary, N + 50);
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

cScalar complexFunc(const cScalar t) {
  Scalar val = (imag(t) / PI) - 1;
  BOOST_CHECK(-1 <= val);
  BOOST_CHECK(val <= 1);
  BOOST_CHECK_CLOSE(0, real(t), epsScalar);
  return exp(t);
}

cScalar complexDerivFunc(const cScalar t) {
  Scalar val = (imag(t) / PI) - 1;
  BOOST_CHECK(-1 <= val);
  BOOST_CHECK(val <= 1);
  BOOST_CHECK_CLOSE(0, real(t), epsScalar);
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

BOOST_AUTO_TEST_CASE( ComplexFunctionSegment2DTests ) {
    CreationFunction boundCreate = bind(createFunctionalSegment2D, complexFunc, complexDerivFunc, 10, 1, cScalar(0, PI));
    testCreation(boundCreate, 10);
    testRecalculation(boundCreate, 10);
    testPoints(boundCreate, cfPoint);
    testPointDerivatives(boundCreate, cfDeriv);
    testNormals(boundCreate, cfNorm);
}

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

BOOST_AUTO_TEST_CASE( RadialSegment2DTests ) {
    CreationFunction boundCreate = bind(createRadialSegment2D, radialFunc, radialDerivFunc, 10);
    testCreation(boundCreate, 10);
    testRecalculation(boundCreate, 10);
    testPoints(boundCreate, rPoint);
    testPointDerivatives(boundCreate, rDeriv);
    testNormals(boundCreate, rNorm);
}

cScalar arcPoint(const Scalar t) {
  cScalar argument = cScalar(0, (t * PI / 2) + PI / 4);
  return cScalar(0.5, -0.5) + 1.5 * exp(argument);
}

cScalar arcDeriv(const Scalar t) {
  cScalar argument = cScalar(0, (t * PI / 2) + PI / 4);
  return cScalar(0, PI / 2) * 1.5 * exp(argument);
}

cScalar arcNorm(const Scalar t) {
  cScalar d = arcDeriv(t);
  Scalar mag = abs(d);
  return cScalar(imag(d) / mag, -real(d) / mag);
}

BOOST_AUTO_TEST_CASE( ArcSegment2DTests ) {
    CreationFunction boundCreate = bind(createArcSegment2D, cScalar(0.5, -0.5), 1.5, -PI / 4, 3 * PI / 4, 10);
    testCreation(boundCreate, 10);
    testRecalculation(boundCreate, 10);
    testPoints(boundCreate, arcPoint);
    testPointDerivatives(boundCreate, arcDeriv);
    testNormals(boundCreate, arcNorm);
}
}
