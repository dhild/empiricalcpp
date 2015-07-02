#include <empiricalcpp/src/Version.hpp>

namespace Empirical {
    namespace Version {
        namespace {
            static const std::string versionConst(EMPIRICAL_VERSION_STRING);
            static const std::string typeConst(EMPIRICAL_VERSION_TYPE);
            static const std::string revisionConst("$Id$");
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

        const std::string& typeString() {
            return typeConst;
        }

        const std::string& versionString() {
            return versionConst;
        }

        const std::string& revisionString() {
            return revisionConst;
        }

    }
}
