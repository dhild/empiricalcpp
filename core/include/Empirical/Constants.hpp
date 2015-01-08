#ifndef EMPIRICAL_MATRIX_HPP_
#define EMPIRICAL_MATRIX_HPP_

#include <complex>
#include <cstdint>

namespace Empirical {

/** Scalar value type. Should support your desired precision. */
typedef double Scalar;

/** Machine epsilon for the scalar type. */
extern const Scalar epsScalar;

/** Complex scalar value type. Should support your desired precision and complex numbers. */
typedef std::complex<Scalar> cScalar;

/** Value of PI, for convenience. */
extern const Scalar PI;

}

#endif /* EMPIRICAL_MATRIX_HPP_ */
