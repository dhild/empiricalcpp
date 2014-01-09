/*
 * File:   quadrature.h
 * Author: D. Ryan Hild <d.ryan.hild@gmail.com>
 *
 * Created on December 5, 2013, 4:18 AM
 */

#ifndef QUADRATURE_H
#define	QUADRATURE_H

#include <Eigen/Dense>

namespace empirical {

    template<typename Scalar> class Quadrature {
    protected:
        int N;
        Scalar a;
        Scalar b;
        Eigen::Array<Scalar, Eigen::Dynamic, 1> x;
        Eigen::Array<Scalar, Eigen::Dynamic, 1> w;

        Quadrature(const int N, const Scalar a, const Scalar b)
                : N(N), a(a), b(b), x(), w() {
            x.resize(N);
            w.resize(N);
        }

        void recalc();

    public:
        void update(const int N, const Scalar a, const Scalar b) {
            this->N = N;
            this->a = a;
            this->b = b;
            x.resize(N);
            w.resize(N);
            recalc();
        }
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

        Scalar integrate(Scalar (*f)(const Scalar)) const {
            Scalar sum = 0;

            for (int i = 0; i < N; i++) {
                sum += f(x(i)) * w(i);
            }

            return sum;
        }
    };

    template<typename Scalar> class PeriodicTrapezoid: public Quadrature<Scalar> {
    public:
        PeriodicTrapezoid(const int N, const Scalar a = -1, const Scalar b = 1)
                : Quadrature<Scalar>(N, a, b) {
        }

    protected:
        void recalc() {
            Scalar dist = this->b - this->a;
            Scalar shift = dist / (2 * this->N);

            Scalar x0 = this->a + shift;
            Scalar x1 = this->b - shift;

            Scalar delta = (x1 - x0) / Scalar(this->N - 1);

            for (int i = 0; i < this->N; i++) {
                this->x(i) = x0 + i * delta;
                this->w(i) = delta;
            }
        }
    };

    template<typename Scalar> class TrapezoidQuadrature: public Quadrature<Scalar> {
    public:
        TrapezoidQuadrature(const int N, const Scalar a = -1, const Scalar b = 1)
                : Quadrature<Scalar>(N, a, b) {
        }

    protected:
        void recalc(){
            Scalar dist = this->b - this->a;
            Scalar delta = dist / (this->N - 1);

            for (int i = 0; i < this->N; i++) {
                this->x(i) = this->a + i * delta;
                this->w(i) = delta;
            }

            this->w(0) *= 0.5;
            this->w(this->N - 1) *= 0.5;
        }
    };

    template<typename Scalar> class LegendreGaussLobatto: public Quadrature<Scalar> {
    public:
        LegendreGaussLobatto(const int N, const Scalar a = -1, const Scalar b = 1)
                : Quadrature<Scalar>(N, a, b) {
        }

    protected:
        void recalc();
    };

}

#endif	/* QUADRATURE_H */

