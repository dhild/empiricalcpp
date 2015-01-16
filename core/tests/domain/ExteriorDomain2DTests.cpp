#include <Empirical/Domain.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <cmath>

using namespace std;
using namespace Empirical;

namespace {

cScalar basisRadialFunc(const Scalar) {
    return 1.75;
}

cScalar basisRadialDerivFunc(const Scalar) {
    return 0;
}

cScalar radialFunc(const Scalar angle) {
    return 5 + 2 * cos(angle);
}

cScalar radialDerivFunc(const Scalar angle) {
    return 2 * angle * sin(angle);
}

BOOST_AUTO_TEST_SUITE(ExteriorDomain2DTests)

BOOST_AUTO_TEST_CASE(ExteriorDomain2DCreation) {
    auto boundary = unique_ptr<RefinableBoundary2D>(createRadialSegment2D(radialFunc, radialDerivFunc, 125));
    auto mfsBoundary = unique_ptr<RefinableBoundary2D>(createRadialSegment2D(basisRadialFunc, basisRadialDerivFunc, 125));
    auto basis = unique_ptr<Basis2D>(createMFSBasis(mfsBoundary.get()));
    auto domain = unique_ptr<Domain2D>(createExteriorDomain2D(boundary.get(), basis.get(), false, 1.75));

    BOOST_CHECK(domain->isExterior());
    BOOST_CHECK(!domain->isDomainInNormalDirection());
    BOOST_CHECK_CLOSE(domain->getIndexOfRefraction(), 1.75, epsScalar);
    BOOST_CHECK(&(domain->getBasis()) == basis.get());
    BOOST_CHECK(&(domain->getBoundary()) == boundary.get());
}

BOOST_AUTO_TEST_CASE(ExteriorDomain2DSetIndex) {
    auto boundary = unique_ptr<RefinableBoundary2D>(createRadialSegment2D(radialFunc, radialDerivFunc, 125));
    auto mfsBoundary = unique_ptr<RefinableBoundary2D>(createRadialSegment2D(basisRadialFunc, basisRadialDerivFunc, 125));
    auto basis = unique_ptr<Basis2D>(createMFSBasis(mfsBoundary.get()));
    auto domain = unique_ptr<Domain2D>(createExteriorDomain2D(boundary.get(), basis.get(), false, 1.75));

    BOOST_CHECK_CLOSE(domain->getIndexOfRefraction(), 1.75, epsScalar);

    domain->setIndexOfRefraction(0.2);

    BOOST_CHECK_CLOSE(domain->getIndexOfRefraction(), 0.2, epsScalar);
}

BOOST_AUTO_TEST_SUITE_END()
}
