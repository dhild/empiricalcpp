#include <Empirical/BoundaryCondition.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <cmath>

using namespace std;
using namespace Empirical;

namespace {

cScalar point(const cScalar x) {
    return x * 2.0;
}

cScalar normals(const cScalar x) {
    return x + 5.0;
}

BOOST_AUTO_TEST_SUITE( BoundaryConditions )

BOOST_AUTO_TEST_CASE(Cauchy2DRequirements) {
    BoundaryCondition2D* bc = createCauchy(BoundaryFunc(point), BoundaryFunc(normals));
    BOOST_CHECK(bc->requiresPoint());
    BOOST_CHECK(bc->requiresNormal());
    delete bc;
}

BOOST_AUTO_TEST_CASE(Cauchy2DReals) {
    BoundaryCondition2D* bc = createCauchy(BoundaryFunc(point), BoundaryFunc(normals));
    BOOST_CHECK_CLOSE(real(bc->operator()(4.0)), 8.0, epsScalar);
    BOOST_CHECK_CLOSE(imag(bc->operator()(4.0)), 0.0, epsScalar);
    BOOST_CHECK_CLOSE(real(bc->operator()(-3.0)), -6.0, epsScalar);
    BOOST_CHECK_CLOSE(imag(bc->operator()(-3.0)), 0.0, epsScalar);
    delete bc;
}

BOOST_AUTO_TEST_CASE(Cauchy2DNormals) {
    BoundaryCondition2D* bc = createCauchy(BoundaryFunc(point), BoundaryFunc(normals));
    BOOST_CHECK_CLOSE(real(bc->normal(4.0)), 9.0, epsScalar);
    BOOST_CHECK_CLOSE(imag(bc->normal(4.0)), 0.0, epsScalar);
    BOOST_CHECK_CLOSE(real(bc->normal(-3.0)), 2.0, epsScalar);
    BOOST_CHECK_CLOSE(imag(bc->normal(-3.0)), 0.0, epsScalar);
    delete bc;
}

BOOST_AUTO_TEST_SUITE_END()
}
