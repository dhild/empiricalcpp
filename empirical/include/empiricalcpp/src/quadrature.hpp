#ifndef EMPIRICALCPP_SRC_QUADRATURE_HPP_
#define EMPIRICALCPP_SRC_QUADRATURE_HPP_

#include <empiricalcpp/src/constants.hpp>
#include <functional>
#include <memory>
#include <vector>

namespace empirical {
    namespace quadrature {
        class Quadrature : public std::enable_shared_from_this<Quadrature> {
        public:
            std::vector<Scalar> points;
            std::vector<Scalar> weights;

            Quadrature(const std::size_t N) : points(N), weights(N) {}
            virtual ~Quadrature() {}
            void resize(const std::size_t N);

            Scalar integrate(std::function<Scalar(Scalar)> func) const {
                Scalar eval = 0;
                for (std::size_t i = 0; i < points.size(); i++) {
                    eval += weights[i] * func(points[i]);
                }
                return eval;
            }

            cScalar integrateComplex(std::function<cScalar(Scalar)> func) const {
                cScalar eval = 0;
                for (std::size_t i = 0; i < points.size(); i++) {
                    eval += weights[i] * func(points[i]);
                }
                return eval;
            }

        protected:
            virtual void recalculate(const std::size_t N) = 0;
        };

        /** Evenly spaced points on [-1, 1].
         * Weights are evenly distributed, except at the endpoints (where they count for half).
         */
        std::shared_ptr<Quadrature> trapezoid(const std::size_t N);

        /** If you wrap around, where -1 == 1, then this quadrature maintains spacing across the boundary.
         * Weights are evenly distributed.
         * Otherwise, it behaves like trapezoid quadrature (evenly spaced points).
         */
        std::shared_ptr<Quadrature> periodicTrapezoid(const std::size_t N);
        std::shared_ptr<Quadrature> legendreGaussLobatto(const std::size_t N);

        typedef std::function<Scalar(const std::size_t i, const std::size_t N)> customFunc;
        std::shared_ptr<Quadrature> custom(const std::size_t N, customFunc xFunction, customFunc weightFunction);
    }

    typedef quadrature::Quadrature Quadrature;
}

#endif /* EMPIRICALCPP_SRC_QUADRATURE_HPP_ */
