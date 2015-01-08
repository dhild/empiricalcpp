#include <Empirical/Version.hpp>
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace Empirical;

namespace {
BOOST_AUTO_TEST_CASE( VersionMajor ) {
    BOOST_CHECK_EQUAL(EMPIRICAL_VERSION_MAJOR, Version::major());
}
BOOST_AUTO_TEST_CASE( VersionMinor ) {
    BOOST_CHECK_EQUAL(EMPIRICAL_VERSION_MINOR, Version::minor());
}
BOOST_AUTO_TEST_CASE( VersionPatch ) {
    BOOST_CHECK_EQUAL(EMPIRICAL_VERSION_PATCH, Version::patch());
}
BOOST_AUTO_TEST_CASE( VersionType ) {
    BOOST_CHECK(Version::typeString() == EMPIRICAL_VERSION_TYPE);
    BOOST_CHECK(Version::typeString() == "RELEASE" || Version::typeString() == "SNAPSHOT");
}
BOOST_AUTO_TEST_CASE( VersionRevision ) {
    string idPrefix = "$Id: ";
    BOOST_CHECK_NE(string::npos, Version::revisionString().find(idPrefix));
}
BOOST_AUTO_TEST_CASE( VersionString ) {
    BOOST_CHECK(Version::versionString() == EMPIRICAL_VERSION_STRING);
    BOOST_CHECK_NE(string::npos, Version::versionString().find(to_string(Version::major())));
    BOOST_CHECK_NE(string::npos, Version::versionString().find(to_string(Version::minor())));
    BOOST_CHECK_NE(string::npos, Version::versionString().find(to_string(Version::patch())));
    BOOST_CHECK_NE(string::npos, Version::versionString().find(Version::typeString()));
    BOOST_CHECK_EQUAL(string::npos, Version::versionString().find(Version::revisionString()));
}
}
