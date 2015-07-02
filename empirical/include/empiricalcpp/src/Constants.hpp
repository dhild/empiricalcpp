#ifndef EMPIRICALCPP_SRC_CONSTANTS_HPP_
#define EMPIRICALCPP_SRC_CONSTANTS_HPP_

#include <complex>
#include <cstdint>

#ifndef EMPIRICAL_SCALAR_TYPE
#define EMPIRICAL_SCALAR_TYPE double
#endif

#ifndef EMPIRICAL_COMPLEX_SCALAR_TYPE
#define EMPIRICAL_COMPLEX_SCALAR_TYPE std::complex<double>
#endif

namespace Empirical {

    /** Scalar value type. Should support your desired precision. */
    typedef EMPIRICAL_SCALAR_TYPE Scalar;

    /** Machine epsilon for the scalar type. */
    extern const Scalar epsScalar;

    /** Complex scalar value type. Should support your desired precision and complex numbers. */
    typedef EMPIRICAL_COMPLEX_SCALAR_TYPE cScalar;

    /** Value of PI, for convenience. */
    extern const Scalar PI;

}

#endif /* EMPIRICALCPP_SRC_CONSTANTS_HPP_ */
