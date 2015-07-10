#ifndef EMPIRICALCPP_SRC_QUADRATURE_HPP_
#define EMPIRICALCPP_SRC_QUADRATURE_HPP_

#include <empiricalcpp/src/constants.hpp>
#include <functional>
#include <vector>

namespace empirical {
    namespace quadrature {

        /** A Quadrature defines a set of points which lie in the region [-1, 1], and their corresponding weights.
         *
         * Ownership semantics
         * ===================
         * Because of the relatively low cost of creating a quadrature, any empirical class which uses a Quadrature
         * is expected to maintain ownership of a unique copy of the Quadrature. This allows the owner class to
         * control aspects such as resizing of the quadrature.
         */
        class Quadrature {
        public:
            typedef std::vector<Scalar> vector_type;
            typedef vector_type::size_type size_type;
            typedef vector_type::iterator iterator;
            typedef vector_type::const_iterator const_iterator;
            typedef std::pair<vector_type, vector_type> points_weights_type;
            typedef std::function<points_weights_type(const size_type, const Scalar, const Scalar)> generator_function;

        protected:
            Scalar minVal, maxVal;
            vector_type points, weights;
            generator_function generator;

        public:
            size_type size() const { return points.size(); }
            Scalar min() const { return minVal; }
            Scalar max() const { return maxVal; }

            iterator begin() { return points.begin(); }
            iterator end() { return points.end(); }
            const_iterator begin() const { return points.begin(); }
            const_iterator end() const { return points.end(); }

            vector_type getPoints() { return points; }
            vector_type getWeights() { return weights; }
            const vector_type getPoints() const { return points; }
            const vector_type getWeights() const { return weights; }

            Scalar operator[](const size_type i) const { return points[i]; }
            Scalar& operator[](const size_type i) { return points[i]; }

            Scalar operator()(const size_type i) const { return points[i]; }
            Scalar& operator()(const size_type i) { return points[i]; }

            void resize(const size_type N, const Scalar min, const Scalar max) {
                if (points.size() == N && min == minVal && max == maxVal) {
                    return;
                }
                minVal = min;
                maxVal = max;
                points_weights_type values = generator(N, min, max);
                points = values.first;
                weights = values.second;
            }

            void resize(const size_type N) {
                resize(N, minVal, maxVal);
            }

            Scalar integrate(std::function<Scalar(Scalar)> func) const {
                Scalar eval = 0;
                for (size_type i = 0; i < size(); i++) {
                    eval += weights[i] * func(points[i]);
                }
                return eval;
            }

            cScalar integrateComplex(std::function<cScalar(Scalar)> func) const {
                cScalar eval = 0;
                for (size_type i = 0; i < size(); i++) {
                    eval += weights[i] * func(points[i]);
                }
                return eval;
            }

            Quadrature(generator_function generator, const size_type N, const Scalar min = -1, const Scalar max = 1)
                : minVal(min), maxVal(max), points(1), weights(1), generator(generator) {
                resize(N, min, max);
            }
        };

        /** Evenly spaced points on [-1, 1].
         * Weights are evenly distributed, except at the endpoints (where they count for half).
         */
        Quadrature trapezoid(const Quadrature::size_type N, const Scalar min = -1, const Scalar max = 1);

        /** If you wrap around, where -1 == 1, then this quadrature maintains spacing across the boundary.
         * Weights are evenly distributed.
         * Otherwise, it behaves like trapezoid quadrature (evenly spaced points).
         */
        Quadrature periodicTrapezoid(const Quadrature::size_type N, const Scalar min = -1, const Scalar max = 1);

        Quadrature legendreGaussLobatto(const Quadrature::size_type N, const Scalar min = -1, const Scalar max = 1);


#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
        inline std::ostream& operator<<(std::ostream& os, const Quadrature& q) {
            os << "Quadrature {{ points:";
            os << std::fixed << std::setw(11) << std::setprecision(6);
            for (Scalar val : q.getPoints()) {
                os << val << ", ";
            }
            os << "}, { weights:";
            for (Scalar val : q.getWeights()) {
                os << val << ", ";
            }
            return os << "}}";
        }
#endif
    }

    typedef quadrature::Quadrature Quadrature;
}

#endif /* EMPIRICALCPP_SRC_QUADRATURE_HPP_ */
