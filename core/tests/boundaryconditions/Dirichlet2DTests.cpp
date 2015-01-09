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

BOOST_AUTO_TEST_SUITE(BoundaryConditions)

BOOST_AUTO_TEST_CASE(Dirichlet2DRequirements) {
    BoundaryCondition2D* bc = createDirichlet(BoundaryFunc(point));
    BOOST_CHECK(bc->requiresPoint());
    BOOST_CHECK(!bc->requiresNormal());
    delete bc;
}

BOOST_AUTO_TEST_CASE(Dirichlet2DFunctions) {
    BoundaryCondition2D* bc = createDirichlet(BoundaryFunc(point));
    BOOST_CHECK_CLOSE(real(bc->operator()(4.0)), 8.0, epsScalar);
    BOOST_CHECK_CLOSE(imag(bc->operator()(4.0)), 0.0, epsScalar);
    BOOST_CHECK_CLOSE(real(bc->operator()(-3.0)), -6.0, epsScalar);
    BOOST_CHECK_CLOSE(imag(bc->operator()(-3.0)), 0.0, epsScalar);
    delete bc;
}

BOOST_AUTO_TEST_SUITE_END()
}
