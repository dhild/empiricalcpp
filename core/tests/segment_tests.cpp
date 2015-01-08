/*
#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include "test.h"
#include <Empirical/Domain>

using namespace std;
using namespace Eigen;
using namespace empirical;

void checkSizes(const DomainSegment2D& segment, const int N) {
  CHECK(N == segment.size());
  CHECK(N == segment.getPoints().rows());
  CHECK(N == segment.getPointDerivatives().rows());
  CHECK(N == segment.getNormals().rows());
  CHECK(N == segment.getWeights().size());
  CHECK(N == segment.getT().size());
}

void checkClose(const QuadratureVector& t_vec,
                const Mesh1D& p_vec,
                const std::function<cScalar(const Scalar t)> points) {
  for (int i = 0; i < t_vec.rows(); i++) {
    cScalar expected = points(t_vec(i, 0));
    cScalar actual = p_vec(i, 0);
    CHECK_CLOSE(real(expected), real(actual), 10 * epsScalar);
    CHECK_CLOSE(imag(expected), imag(actual), 10 * epsScalar);
  }
}

#define TEST_SEGMENT(Type, N, point, deriv, norm, ...)                  \
  SUITE(Type ## _segment_suite) {                                       \
    TEST(Type ## _createN) {                                            \
      Type segment(__VA_ARGS__);                                        \
      checkSizes(segment, N);                                           \
    }                                                                   \
    TEST(Type ## _recalculate) {                                        \
      Type segment(__VA_ARGS__);                                        \
      segment.recalculate(N + 50);                                      \
      checkSizes(segment, N + 50);                                      \
    }                                                                   \
    TEST(Type ## _getPoints) {                                          \
      Type segment(__VA_ARGS__);                                        \
      checkClose(segment.getT(), segment.getPoints(), point);           \
    }                                                                   \
    TEST(Type ## _getPointDerivatives) {                                \
      Type segment(__VA_ARGS__);                                        \
      checkClose(segment.getT(), segment.getPointDerivatives(), deriv); \
    }                                                                   \
    TEST(Type ## _getNormals) {                                         \
      Type segment(__VA_ARGS__);                                        \
      checkClose(segment.getT(), segment.getNormals(), norm);           \
    }                                                                   \
  }


cScalar complexFunc(const cScalar t) {
  Scalar val = (imag(t) / PI) - 1;
  CHECK(-1 <= val);
  CHECK(val <= 1);
  CHECK_CLOSE(0, real(t), epsScalar);
  return exp(t);
}

cScalar complexDerivFunc(const cScalar t) {
  Scalar val = (imag(t) / PI) - 1;
  CHECK(-1 <= val);
  CHECK(val <= 1);
  CHECK_CLOSE(0, real(t), epsScalar);
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

TEST_SEGMENT(ComplexFunctionSegment2D, 10, cfPoint, cfDeriv, cfNorm,
             complexFunc, complexDerivFunc, 10, 1, cScalar(0, PI))


cScalar radialFunc(const Scalar angle) {
  CHECK(-PI <= angle);
  CHECK(angle <= PI);
  return 1;
}

cScalar radialDerivFunc(const Scalar angle) {
  CHECK(-PI <= angle);
  CHECK(angle <= PI);
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

TEST_SEGMENT(RadialSegment2D, 10, rPoint, rDeriv, rNorm,
             radialFunc, radialDerivFunc, 10);


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

TEST_SEGMENT(ArcSegment2D, 10, arcPoint, arcDeriv, arcNorm,
             cScalar(0.5, -0.5), 1.5, -PI / 4, 3 * PI / 4, 10);
*/
