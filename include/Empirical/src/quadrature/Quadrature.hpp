#ifndef QUADRATURE_HPP_
#define QUADRATURE_HPP_

#include <Eigen/Dense>
#include "Empirical/src/config.h"

namespace empirical {

    class Quadrature {
    protected:
        int N;
        Scalar a;
        Scalar b;
        Eigen::Array<Scalar, Eigen::Dynamic, 1> x;
        Eigen::Array<Scalar, Eigen::Dynamic, 1> w;

        Quadrature(const int N, const Scalar a, const Scalar b)
                : x(N), w(N) {
            update(N, a, b);
        }

        virtual void recalc();

        virtual ~Quadrature() = 0;

    public:
        void update(const int N, const Scalar a, const Scalar b);
        void update(const int N) {
            update(N, a, b);
        }
        void update(const Scalar a, const Scalar b) {
            update(N, a, b);
        }

        int getN() const {
            return N;
        }
        Scalar getA() const {
            return a;
        }
        Scalar getB() const {
            return b;
        }

        const Eigen::Array<Scalar, Eigen::Dynamic, 1> getPoints() const {
            return x;
        }
        const Eigen::Array<Scalar, Eigen::Dynamic, 1> getWeights() const {
            return w;
        }

        Scalar integrate(const Scalar (*f)(const Scalar)) const;
    };
    
    /** Type that should create a Quadrature object of the desired type.
     * 
     * This type of function should emulate the new operator; delete should
     * always be called by the owner of the constructed object.
     */
    typedef Quadrature* (*quadratureFactory)(const int M, const Scalar& a, const Scalar& b);
    
    class LegendreGaussLobatto: public Quadrature {
    public:
        LegendreGaussLobatto(const int N, const Scalar a = -1, const Scalar b = 1)
                : Quadrature(N, a, b) {
            recalc();
        }

        virtual ~LegendreGaussLobatto();

    protected:
        virtual void recalc();
    };

    class PeriodicTrapezoid: public Quadrature {
    public:
        PeriodicTrapezoid(const int N, const Scalar a = -1, const Scalar b = 1)
                : Quadrature(N, a, b) {
            recalc();
        }

        virtual ~PeriodicTrapezoid();

    protected:
        virtual void recalc();
    };

    class TrapezoidQuadrature: public Quadrature {
    public:
        TrapezoidQuadrature(const int N, const Scalar a = -1, const Scalar b = 1)
                : Quadrature(N, a, b) {
            recalc();
        }

        virtual ~TrapezoidQuadrature();

    protected:
        virtual void recalc();
    };
}

#endif /* QUADRATURE_HPP_ */
