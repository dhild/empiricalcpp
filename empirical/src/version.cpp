#include <empiricalcpp/src/version.hpp>

namespace empirical {
    namespace version {
        namespace {
            static const std::string versionConst(EMPIRICAL_VERSION_STRING);
            static const std::string typeConst(EMPIRICAL_VERSION_TYPE);
            static const std::string revisionConst("$Id$");
        }

        uint8_t major() {
            return EMPIRICAL_VERSION_MAJOR;
        }

        uint8_t minor() {
            return EMPIRICAL_VERSION_MINOR;
        }

        uint8_t patch() {
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
