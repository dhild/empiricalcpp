#include <empiricalcpp/src/quadrature.hpp>
#include <cassert>

#include <boost/multi_array.hpp>

namespace empirical {
    namespace quadrature {

        void Quadrature::resize(const std::size_t N) {
            assert(N > 2);
            points.resize(N);
            weights.resize(N);
            this->recalculate(N);
        }

        class TrapezoidQuadrature : public Quadrature {
        protected:
            virtual void recalculate(const std::size_t N) {
                const Scalar weight = 2.0 / N;
                for (std::size_t i = 0; i < N; i++) {
                    points[i] = (2.0 * i - N) / N;
                    weights[i] = weight;
                }
                weights[0] = 1.0 / N;
                weights[N - 1] = 1.0 / N;
            }

        public:
            TrapezoidQuadrature(const std::size_t N) : Quadrature(N) {
                recalculate(N);
            }
            virtual ~TrapezoidQuadrature() {}
        };

        class PeriodicTrapezoidQuadrature : public Quadrature {
        protected:
            virtual void recalculate(const std::size_t N) {
                const Scalar size = Scalar(2 * N - 2) / N;
                const Scalar weight = 2.0 / N;
                for (std::size_t i = 0; i < N; i++) {
                    points[i] = (size * i - N) / N;
                    weights[i] = weight;
                }
            }

        public:
            PeriodicTrapezoidQuadrature(const std::size_t N) : Quadrature(N) {
                recalculate(N);
            }
            virtual ~PeriodicTrapezoidQuadrature() {}
        };

        class LGLQuadrature : public Quadrature {
        protected:
            virtual void recalculate(const std::size_t N1) {
                const std::size_t N = N1 - 1;

                std::vector<Scalar> x(N1);
                std::vector<Scalar> xold(N1);
                boost::multi_array<Scalar, 2> P(boost::extents[N1][N1]);

                for (std::size_t i = 0; i < N1; i++) {
                    x[i] = cos((PI * i - N1) / N1);
                    xold[i] = 2;
                    for (std::size_t j = 0; j < N1; j++) {
                        P[i][j] = 0;
                    }
                }

                Scalar maxDiff = 2;
                while (maxDiff > epsScalar) {
                    xold = x;

                    for (std::size_t i = 0; i < N1; i++) {
                        P[i][0] = 1;
                        P[i][1] = x[i];
                    }

                    for (std::size_t k = 2; k < N1; k++) {
                        for (std::size_t i = 0; i < N1; i++) {
                            P[i][k] = (Scalar(2 * k - 1) * x[i] * P[i][k - 1] - Scalar(k - 1) * P[i][k - 2]) / Scalar(k);
                        }
                    }

                    maxDiff = 0;
                    for (std::size_t i = 0; i < N1; i++) {
                        Scalar diff = (x[i] * P[i][N] - P[i][N - 1]) / (Scalar(N1) * P[i][N]);
                        x[i] = xold[i] - diff;
                        if (abs(diff) > maxDiff) {
                            maxDiff = abs(diff);
                        }
                    }
                }

                for (std::size_t i = 0; i < N1; i++) {
                    points[i] = x[N - i];
                    weights[i] = Scalar(2.0) / (Scalar(N) * Scalar(N1) * P[N - i][N] * P[N - i][N]);
                }
            }

        public:
            LGLQuadrature(const std::size_t N) : Quadrature(N) {
                recalculate(N);
            }
            virtual ~LGLQuadrature() {}
        };

        class CustomQuadrature : public Quadrature {
            customFunc xFunction;
            customFunc weightFunction;

        protected:
            virtual void recalculate(const std::size_t N) {
                for (std::size_t i = 0; i < N; i++) {
                    points[i] = xFunction(i, N);
                    weights[i] = weightFunction(i, N);
                }
            }

        public:
            CustomQuadrature(customFunc xFunction, customFunc weightFunction, const std::size_t N)
                : Quadrature(N), xFunction(xFunction), weightFunction(weightFunction) {
                recalculate(N);
            }
            virtual ~CustomQuadrature() {}
        };

        std::shared_ptr<Quadrature> trapezoid(const std::size_t N) {
            return std::make_shared<TrapezoidQuadrature>(N);
        }

        std::shared_ptr<Quadrature> periodicTrapezoid(const std::size_t N) {
            return std::make_shared<PeriodicTrapezoidQuadrature>(N);
        }

        std::shared_ptr<Quadrature> legendreGaussLobatto(const std::size_t N) {
            return std::make_shared<LGLQuadrature>(N);
        }

        std::shared_ptr<Quadrature> custom(const std::size_t N, customFunc xFunction, customFunc weightFunction) {
            return std::make_shared<CustomQuadrature>(xFunction, weightFunction, N);
        }
    }
}
