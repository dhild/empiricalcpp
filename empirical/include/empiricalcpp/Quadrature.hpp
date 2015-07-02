#ifndef EMPIRICAL_QUADRATURE_HPP_
#define EMPIRICAL_QUADRATURE_HPP_

#include <Empirical/Constants.hpp>
#include <Empirical/Matrices.hpp>
#include <vector>

namespace Empirical {

    namespace quadrature {

        struct Quadrature {
            std::vector<Scalar> points;
            std::vector<Scalar> weights;

            Quadrature(const std::size_t N) : points(N), weights(N) {}
            virtual void resize(const std::size_t N);
        };

        struct LGLQuadrature : public Quadrature {
            LGLQuadrature(const std::size_t N);
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

    }

class Quadrature {
protected:
    Vector points;
    Vector weights;

    Quadrature(const Index N) : points(N), weights(N) {}

    virtual void recalc(const Index N) = 0;
public:

    virtual ~Quadrature() {}

    void resize(const Index N) {
        if (N == size()) {
            return;
        }
        points.resize(N, 1);
        weights.resize(N, 1);
        this->recalc(N);
    }

    Index size() const {
        return points.rows();
    }

    const Vector& getPoints() const {
        return points;
    }

    const Vector& getWeights() const {
        return weights;
    }
};

typedef Quadrature* (*QuadratureFunc)(const Index);

Quadrature* createLGL(const Index N);
Quadrature* createTrapezoid(const Index N);
Quadrature* createPeriodicTrapezoid(const Index N);
}

#endif /* EMPIRICAL_QUADRATURE_HPP_ */
