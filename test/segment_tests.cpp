#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include "test.h"
#include <Empirical/Domain>

using namespace std;
using namespace Eigen;
using namespace empirical;

cScalar unitCircle(Scalar t) {
  return 1;
}

cScalar unitCirclePrime(Scalar t) {
  return 0;
}

const int M = 125;

SUITE(segment_DomainSegment2D_RadialSegment2D) {
  TEST(size) {
    RadialSegment2D segment(unitCircle, unitCirclePrime, M);
    CHECK(M == segment.size());
  }
  TEST(recalculateQuadratures) {
    RadialSegment2D segment(unitCircle, unitCirclePrime, M);
    segment.recalculate(50);
    CHECK(50 == segment.size());
  }
  TEST(getPoints) {
    RadialSegment2D segment(unitCircle, unitCirclePrime, M);

    const Mesh1D points = segment.getPoints();

    for (int i = 0; i < M; i++) {
      CHECK_CLOSE(1, abs(points(i, 0)), 10 * epsScalar);
    }
  }
  TEST(getPointDerivatives) {
    RadialSegment2D segment(unitCircle, unitCirclePrime, M);

    const QuadratureVector t = segment.getT() * PI;
    const Mesh1D points = segment.getPointDerivatives();

    for (int i = 0; i < M; i++) {
      Scalar x = -sin(t(i, 0));
      Scalar y = cos(t(i, 0));
      CHECK_CLOSE(x, real(points(i, 0)), 10 * epsScalar);
      CHECK_CLOSE(y, imag(points(i, 0)), 10 * epsScalar);
    }
  }
  TEST(getNormals) {
    RadialSegment2D segment(unitCircle, unitCirclePrime, M);

    const QuadratureVector t = segment.getT() * PI;
    const Mesh1D normals = segment.getPointDerivatives();

    for (int i = 0; i < M; i++) {
      
      cScalar val = cScalar(0, 1) * t(i, 0);
      CHECK_CLOSE(real(val), real(normals(i, 0)), 10 * epsScalar);
      CHECK_CLOSE(imag(val), imag(normals(i, 0)), 10 * epsScalar);
    }
  }
}
