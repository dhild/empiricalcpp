#ifndef EMPIRICAL_QUADRATURE_HPP_
#define EMPIRICAL_QUADRATURE_HPP_

#include "Empirical/Constants.hpp"
#include "Empirical/Matrices.hpp"

namespace Empirical {

class Quadrature {
protected:
    Vector points;
    Vector weights;

    Quadrature(const int64_t N) : points(N), weights(N) {}

    virtual void recalc(const int64_t N) = 0;
public:

    virtual ~Quadrature() {}

    void resize(const int64_t N) {
        if (N == size()) {
            return;
        }
        points.resize(N, 1);
        weights.resize(N, 1);
        this->recalc(N);
    }

    int64_t size() const {
        return points.rows();
    }

    const Vector& getPoints() const {
        return points;
    }

    const Vector& getWeights() const {
        return weights;
    }
};

typedef Quadrature* (*QuadratureFunc)(const int64_t);

Quadrature* createLGL(const int64_t N);
Quadrature* createTrapezoid(const int64_t N);
Quadrature* createPeriodicTrapezoid(const int64_t N);
}

#endif /* EMPIRICAL_QUADRATURE_HPP_ */
