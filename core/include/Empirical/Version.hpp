#ifndef EMPIRICAL_VERSION_HPP_
#define EMPIRICAL_VERSION_HPP_

#include <boost/preprocessor/stringize.hpp>
#include <string>

#define EMPIRICAL_VERSION_MAJOR 0
#define EMPIRICAL_VERSION_MINOR 0
#define EMPIRICAL_VERSION_PATCH 1
#define EMPIRICAL_VERSION_TYPE "RELEASE"
#define EMPIRICAL_VERSION_STRING ("" BOOST_PP_STRINGIZE(EMPIRICAL_VERSION_MAJOR) \
                                  "." BOOST_PP_STRINGIZE(EMPIRICAL_VERSION_MINOR) \
                                  "." BOOST_PP_STRINGIZE(EMPIRICAL_VERSION_PATCH) \
                                  "-" EMPIRICAL_VERSION_TYPE)

namespace Empirical {
namespace Version {

extern int major();
extern int minor();
extern int patch();
extern const std::string& typeString();
extern const std::string& versionString();
extern const std::string& revisionString();

}
}

#endif /* EMPIRICAL_VERSION_HPP_ */
