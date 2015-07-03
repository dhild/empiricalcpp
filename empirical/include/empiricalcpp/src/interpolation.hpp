#ifndef EMPIRICALCPP_SRC_INTERPOLATION_HPP_
#define EMPIRICALCPP_SRC_INTERPOLATION_HPP_

#include <empiricalcpp/src/constants.hpp>
#include <empiricalcpp/src/quadrature.hpp>
#include <empiricalcpp/src/mesh.hpp>
#include <functional>
#include <vector>
#include <boost/multi_array.hpp>

namespace empirical {
    namespace interpolation {
        typedef std::function<Scalar(const Scalar)> scalarFunction1;
        typedef std::function<cScalar(const Scalar)> complexFunction1;
        typedef std::function<Scalar(const Scalar, const Scalar)> scalarFunction2;
        typedef std::function<cScalar(const Scalar, const Scalar)> complexFunction2;
        typedef std::function<Scalar(const Scalar, const Scalar, const Scalar)> scalarFunction3;
        typedef std::function<cScalar(const Scalar, const Scalar, const Scalar)> complexFunction3;

        class Interpolator {
        public:
            virtual ~Interpolator() {}

            /** Returns the number of basis functions that compose this interpolator. */
            virtual size_t N() const = 0;

            /** Returns the L^\infty norm of the interpolator. */
            virtual Scalar getMaximumNorm() const = 0;

            /**
            * The correction scale is the scale of the last basis relative to the first basis.
            * With one basis, this returns 1.
            * With two bases, this returns scale_1 / scale_2.
            */
            virtual Scalar getLastCorrectionScale() const = 0;
        };

        class ScalarInterpolator1D : public Interpolator, public std::enable_shared_from_this<ScalarInterpolator1D> {
        public:
            virtual ~ScalarInterpolator1D() {}

            /** Calculates N() test points using the given function for the desired solution, then returns a function to interpolate the rest. */
            virtual scalarFunction1 operator()(scalarFunction1 testFunction) const = 0;
        };

        /** Constructs an interpolator, stoping when either of the given limits has been reached. */
        std::shared_ptr<ScalarInterpolator1D> constructInterpolator(
            const Mesh1D& points, const Mesh1D& parameters,
            boost::const_multi_array_ref<Scalar, 2> computedSolutions,
            const size_t maxBasisSize = 50,
            const Scalar correctionScaleBound = epsScalar * 4e10);
    }

    typedef interpolation::Interpolator Interpolator;
    typedef interpolation::ScalarInterpolator1D ScalarInterpolator1D;
}

#endif /* EMPIRICALCPP_SRC_INTERPOLATION_HPP_ */
