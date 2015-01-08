#include <Empirical/Version.hpp>

using namespace std;

namespace Empirical {
namespace Version {
namespace {
static const string versionConst(EMPIRICAL_VERSION_STRING);
static const string typeConst(EMPIRICAL_VERSION_TYPE);
static const string revisionConst("$Id$");
}


int major() {
    return EMPIRICAL_VERSION_MAJOR;
}

int minor() {
    return EMPIRICAL_VERSION_MINOR;
}

int patch() {
    return EMPIRICAL_VERSION_PATCH;
}

const string& typeString() {
    return typeConst;
}

const string& versionString() {
    return versionConst;
}

const string& revisionString() {
    return revisionConst;
}

}
}
