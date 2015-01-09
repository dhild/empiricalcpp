#include <Empirical/BoundaryCondition.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <cmath>

using namespace std;
using namespace Empirical;

namespace {

cScalar normals(const cScalar x) {
    return x + 5.0;
}

BOOST_AUTO_TEST_SUITE(BoundaryConditions)

BOOST_AUTO_TEST_CASE(Neumann2DRequirements) {
    BoundaryCondition2D* bc = createNeumann(BoundaryFunc(normals));
    BOOST_CHECK(!bc->requiresPoint());
    BOOST_CHECK(bc->requiresNormal());
    delete bc;
}

BOOST_AUTO_TEST_CASE(Neumann2DFunctions) {
    BoundaryCondition2D* bc = createNeumann(BoundaryFunc(normals));
    BOOST_CHECK_CLOSE(real(bc->normal(4.0)), 9.0, epsScalar);
    BOOST_CHECK_CLOSE(imag(bc->normal(4.0)), 0.0, epsScalar);
    BOOST_CHECK_CLOSE(real(bc->normal(-3.0)), 2.0, epsScalar);
    BOOST_CHECK_CLOSE(imag(bc->normal(-3.0)), 0.0, epsScalar);
    delete bc;
}

BOOST_AUTO_TEST_SUITE_END()
}
