#ifndef EMPIRICALCPP_SRC_QUADRATURE_HPP_
#define EMPIRICALCPP_SRC_QUADRATURE_HPP_

#include <empiricalcpp/src/Constants.hpp>
#include <functional>
#include <vector>

namespace Empirical {
    namespace quadrature {
        struct Quadrature {
            std::vector<Scalar> points;
            std::vector<Scalar> weights;

            Quadrature(const std::size_t N) : points(N), weights(N) {}
            virtual ~Quadrature() {}
            void resize(const std::size_t N);

        protected:
            virtual void recalculate(const std::size_t N) = 0;
        };

        struct TrapezoidQuadrature : public Quadrature {
            TrapezoidQuadrature(const std::size_t N);
            virtual ~TrapezoidQuadrature();

        protected:
            virtual void recalculate(const std::size_t N);
        };

        struct PeroidicTrapezoidQuadrature : public Quadrature {
            PeroidicTrapezoidQuadrature(const std::size_t N);
            virtual ~PeroidicTrapezoidQuadrature();

        protected:
            virtual void recalculate(const std::size_t N);
        };

        struct LGLQuadrature : public Quadrature {
            LGLQuadrature(const std::size_t N);
            virtual ~LGLQuadrature();

        protected:
            virtual void recalculate(const std::size_t N);
        };

        struct CustomQuadrature : public Quadrature {
            typedef std::function<Scalar(const std::size_t i, const std::size_t N)> customFunc;

            CustomQuadrature(customFunc xFunction, customFunc weightFunction, const std::size_t N);
            virtual ~CustomQuadrature();

        protected:
            virtual void recalculate(const std::size_t N);

            customFunc xFunction;
            customFunc weightFunction;
        };
    }
}

#endif /* EMPIRICALCPP_SRC_QUADRATURE_HPP_ */
