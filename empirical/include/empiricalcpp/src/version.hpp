#ifndef EMPIRICALCPP_SRC_VERSION_HPP_
#define EMPIRICALCPP_SRC_VERSION_HPP_

#include <boost/preprocessor/stringize.hpp>
#include <cstdint>
#include <string>

#define EMPIRICAL_VERSION_MAJOR 0
#define EMPIRICAL_VERSION_MINOR 0
#define EMPIRICAL_VERSION_PATCH 2
#define EMPIRICAL_VERSION_TYPE "SNAPSHOT"
#define EMPIRICAL_VERSION_STRING ("" BOOST_PP_STRINGIZE(EMPIRICAL_VERSION_MAJOR) \
                                  "." BOOST_PP_STRINGIZE(EMPIRICAL_VERSION_MINOR) \
                                  "." BOOST_PP_STRINGIZE(EMPIRICAL_VERSION_PATCH) \
                                  "-" EMPIRICAL_VERSION_TYPE)

namespace empirical {
namespace version {

extern uint8_t major();
extern uint8_t minor();
extern uint8_t patch();
extern const std::string& typeString();
extern const std::string& versionString();
extern const std::string& revisionString();

}
}

#endif /* EMPIRICALCPP_SRC_VERSION_HPP_ */
