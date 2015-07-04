#ifndef EMPIRICALCPP_SRC_QUADRATURE_HPP_
#define EMPIRICALCPP_SRC_QUADRATURE_HPP_

#include <empiricalcpp/src/constants.hpp>
#include <functional>
#include <vector>

namespace empirical {
    namespace quadrature {
        class Quadrature {
        public:
            std::vector<Scalar> points;
            std::vector<Scalar> weights;

            Quadrature(const std::size_t N) : points(N), weights(N) {}
            virtual ~Quadrature() {}
            void resize(const std::size_t N);
            /** Returns a new Quadrature, which is initialized to the same values as this. */
            virtual Quadrature* clone() const = 0;

            Scalar integrate(std::function<Scalar(Scalar)> func) const;
            cScalar integrateComplex(std::function<cScalar(Scalar)> func) const;

        protected:
            virtual void recalculate(const std::size_t N) = 0;
        };

        /** Evenly spaced points on [-1, 1].
         * Weights are evenly distributed, except at the endpoints (where they count for half).
         */
        Quadrature* trapezoid(const std::size_t N);

        /** If you wrap around, where -1 == 1, then this quadrature maintains spacing across the boundary.
         * Weights are evenly distributed.
         * Otherwise, it behaves like trapezoid quadrature (evenly spaced points).
         */
        Quadrature* periodicTrapezoid(const std::size_t N);
        Quadrature* legendreGaussLobatto(const std::size_t N);

        typedef std::function<Scalar(const std::size_t i, const std::size_t N)> customFunc;
        Quadrature* custom(const std::size_t N, customFunc xFunction, customFunc weightFunction);

#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
        std::ostream& operator<<(std::ostream& os, const Quadrature& q);
#endif
    }

    typedef quadrature::Quadrature Quadrature;
}

#endif /* EMPIRICALCPP_SRC_QUADRATURE_HPP_ */
