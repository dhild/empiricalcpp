#ifndef EMPIRICAL_SRC_QUADRATURE_HPP_
#define EMPIRICAL_SRC_QUADRATURE_HPP_

#include <Empirical/src/Constants.hpp>
#include <functional>
#include <vector>

namespace Empirical {
    namespace quadrature {
        struct Quadrature {
            std::vector<Scalar> points;
            std::vector<Scalar> weights;

            Quadrature(const std::size_t N) : points(N), weights(N) {}
            virtual void resize(const std::size_t N);
        };

        struct LinearQuadrature : public Quadrature {
            LinearQuadrature(const std::size_t N);
            virtual void resize(const std::size_t N);
        };

        struct TrapezoidQuadrature : public Quadrature {
            TrapezoidQuadrature(const std::size_t N);
            virtual void resize(const std::size_t N);
        };

        struct PeroidicTrapezoidQuadrature : public Quadrature {
            PeroidicTrapezoidQuadrature(const std::size_t N);
            virtual void resize(const std::size_t N);
        };

        struct LGLQuadrature : public Quadrature {
            LGLQuadrature(const std::size_t N);
            virtual void resize(const std::size_t N);
        };

        struct CustomQuadrature : public Quadrature {
            typedef std::function<Scalar(const std::size_t i, const std::size_t N)> customFunc;

            CustomQuadrature(customFunc xFunction, customFunc weightFunction, std::size_t N);
            virtual void resize(const std::size_t N);

        protected:
            customFunc xFunction;
            customFunc weightFunction;
        };
    }
}

#endif /* EMPIRICAL_SRC_QUADRATURE_HPP_ */
