#ifndef TESTS_BOUNDARY_BOUNDARY_HPP_
#define TESTS_BOUNDARY_BOUNDARY_HPP_
#include <Empirical/Boundary.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <cmath>
#include <complex>
#include <functional>
#include <iostream>

namespace Empirical {
void checkSizes(const FunctionalBoundary2D& segment, const int N);

void checkClose(const Vector& t_vec, const cVector& p_vec,
                const std::function<cScalar(const Scalar t)> points);

typedef std::function<FunctionalBoundary2D*()> CreationFunction;

void testCreation(CreationFunction create, const int64_t N);

void testRecalculation(CreationFunction create, const int64_t N);

void testPoints(CreationFunction create, QuadratureConversion point);

void testPointDerivatives(CreationFunction create, QuadratureConversion deriv);

void testNormals(CreationFunction create, QuadratureConversion norm);
}

#endif /* TESTS_BOUNDARY_BOUNDARY_HPP_ */
