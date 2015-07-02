#ifndef EMPIRICALCPP_SRC_QUADRATURE_HPP_
#define EMPIRICALCPP_SRC_QUADRATURE_HPP_

#include <empiricalcpp/src/constants.hpp>
#include <functional>
#include <memory>
#include <vector>

namespace empirical {
    namespace quadrature {
        struct Quadrature : public std::enable_shared_from_this<Quadrature> {
            std::vector<Scalar> points;
            std::vector<Scalar> weights;

            Quadrature(const std::size_t N) : points(N), weights(N) {}
            virtual ~Quadrature() {}
            void resize(const std::size_t N);

        protected:
            virtual void recalculate(const std::size_t N) = 0;
        };

        std::shared_ptr<Quadrature> trapezoid(const std::size_t N);
        std::shared_ptr<Quadrature> periodicTrapezoid(const std::size_t N);
        std::shared_ptr<Quadrature> legendreGaussLobatto(const std::size_t N);

        typedef std::function<Scalar(const std::size_t i, const std::size_t N)> customFunc;
        std::shared_ptr<Quadrature> custom(const std::size_t N, customFunc xFunction, customFunc weightFunction);
    }

    typedef quadrature::Quadrature Quadrature;
}

#endif /* EMPIRICALCPP_SRC_QUADRATURE_HPP_ */
