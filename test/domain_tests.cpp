#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include "test.h"
#include <Empirical/Domain>
#include <Empirical/Basis>

using namespace Eigen;
using namespace empirical;

namespace domain_test {

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

SUITE(Domain2D) {
  TEST(Domain2D_construction) {
    Domain2D domain(true, 3.5);
    CHECK(domain.isExterior());
    CHECK(domain.getRefractiveIndex() == 3.5);
    CHECK(domain.sizeSegments() == 0);
    CHECK(domain.sizeBases() == 0);
    CHECK(domain.getPoints().rows() == 0);
    CHECK(domain.getPointDerivatives().rows() == 0);
    CHECK(domain.getNormals().rows() == 0);
    CHECK(domain.getWeights().rows() == 0);
    CHECK(domain.getBases().size() == 0);
  }
  TEST(Domain2D_add_segment) {
    RadialSegment2D segment(radialFunc, radialDerivFunc, 10);
    Domain2D domain(false, 1);
    
    domain.addSegment(&segment);
    CHECK(domain.sizeSegments() == 10);
    CHECK_CLOSE((domain.getPoints() - segment.getPoints()).norm(), 0,
                epsScalar);
    CHECK_CLOSE((domain.getPointDerivatives() - segment.getPointDerivatives())
                .norm(), 0, epsScalar);
    CHECK_CLOSE((domain.getNormals() - segment.getNormals()).norm(), 0,
                epsScalar);
    CHECK_CLOSE((domain.getWeights() - segment.getWeights()).matrix().norm(), 0,
                epsScalar);
  }
  TEST(Domain2D_add_segment_modify_segment) {
    RadialSegment2D segment(radialFunc, radialDerivFunc, 10);
    Domain2D domain(false, 1);
    
    domain.addSegment(&segment);
    segment.recalculate(20);
    
    CHECK(domain.sizeSegments() == 20);
    CHECK_CLOSE((domain.getPoints() - segment.getPoints()).norm(), 0,
                epsScalar);
    CHECK_CLOSE((domain.getPointDerivatives() - segment.getPointDerivatives())
                .norm(), 0, epsScalar);
    CHECK_CLOSE((domain.getNormals() - segment.getNormals()).norm(), 0,
                epsScalar);
    CHECK_CLOSE((domain.getWeights() - segment.getWeights()).matrix().norm(), 0,
                epsScalar);
  }
  TEST(Domain2D_add_two_segments) {
    RadialSegment2D segment(radialFunc, radialDerivFunc, 10);
    Domain2D domain(false, 1);
    
    domain.addSegment(&segment);
    domain.addSegment(&segment);
    
    CHECK(domain.sizeSegments() == 20);
  }
  TEST(Domain2D_add_basis) {
    RadialSegment2D segment(radialFunc, radialDerivFunc, 15);
    MFSBasis2D basis(segment.getPoints());
    Domain2D domain(false, 1);
    
    domain.addBasis(&basis);
    
    CHECK(domain.sizeBases() == 15);
    CHECK(domain.getBases().size() == 1);
    CHECK(domain.getBases()[0]->size() == 15);
  }
  TEST(Domain2D_add_basis_and_segment) {
    RadialSegment2D segment(radialFunc, radialDerivFunc, 15);
    RadialSegment2D segment2(radialFunc, radialDerivFunc, 20);
    MFSBasis2D basis(segment.getPoints());
    Domain2D domain(false, 1);
    
    domain.addBasis(&basis);
    domain.addSegment(&segment2);
    
    CHECK(domain.sizeSegments() == 20);
    CHECK(domain.sizeBases() == 15);
  }
}
}
