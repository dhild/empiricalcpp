#ifndef EMPIRICALCPP_SRC_MESH_HPP_
#define EMPIRICALCPP_SRC_MESH_HPP_

#include <empiricalcpp/src/constants.hpp>
#include <empiricalcpp/src/quadrature.hpp>
#include <array>
#include <functional>
#include <vector>
#include <tuple>
#include <boost/multi_array.hpp>

namespace empirical {
    namespace mesh {

        class Mesh1D {
        public:
            typedef std::vector<Scalar> vector_type;
            typedef vector_type::size_type size_type;
            typedef std::function<vector_type(const size_type, const Scalar, const Scalar)> generator_function;

        protected:
            Scalar minVal, maxVal;
            vector_type points;
            generator_function generator;

            void recalculate(const size_type N, const Scalar min, const Scalar max) {
                minVal = min;
                maxVal = max;
                points = generator(N, min, max);
            }

        public:
            Mesh1D(generator_function generator, const size_type N, const Scalar min = -1, const Scalar max = 1)
                : minVal(min), maxVal(max), points(1), generator(generator) {
                recalculate(N, min, max);
            }
            Mesh1D(const Quadrature& quadrature);
            Mesh1D(std::function<Scalar(size_type i, size_type N, Scalar a, Scalar b)> pointFunction,
                const size_type N, const Scalar min = -1, const Scalar max = 1);

            size_type size() const { return points.size(); }
            Scalar min() const { return minVal; }
            Scalar max() const { return maxVal; }

            vector_type::iterator begin() { return points.begin(); }
            vector_type::iterator end() { return points.end(); }
            vector_type::const_iterator begin() const { return points.begin(); }
            vector_type::const_iterator end() const { return points.end(); }

            vector_type getPoints() { return points; }
            const vector_type getPoints() const { return points; }

            Scalar operator[](const size_type i) const { return points[i]; }
            Scalar& operator[](const size_type i) { return points[i]; }

            Scalar operator()(const size_type i) const { return points[i]; }
            Scalar& operator()(const size_type i) { return points[i]; }

            void resize(const size_type N, const Scalar min, const Scalar max) {
                if (points.size() == N && min == minVal && max == maxVal) {
                    return;
                }
                recalculate(N, min, max);
            }

            void resize(const size_type N) {
                resize(N, minVal, maxVal);
            }
        };

        class Mesh2D {
        public:
            typedef boost::multi_array<Scalar, 3> array_type;
            typedef array_type::size_type size_type;
            typedef std::array<size_type, 2> element_index_type;
            typedef std::array<Scalar, 2> point_type;
            typedef std::function<array_type*(const element_index_type, const point_type, const point_type)> generator_function;

        protected:
            point_type minVal, maxVal;
            std::unique_ptr<array_type> points;
            generator_function generator;

            void recalculate(const element_index_type N, const point_type min, const point_type max);

        public:
            Mesh2D(generator_function generator, const element_index_type N, const point_type min, const point_type max)
                : minVal(min), maxVal(max), generator(generator) {
                recalculate(N, min, max);
            }
            Mesh2D(generator_function generator, const element_index_type N) : generator(generator) {
                minVal[0] = minVal[1] = -1;
                maxVal[0] = maxVal[1] = 1;
                recalculate(N, minVal, maxVal);
            }
            Mesh2D(const Quadrature& xQuadrature, const Quadrature& yQuadrature);
            Mesh2D(std::function<Scalar(size_type i, size_type N, Scalar a, Scalar b)> xFunction,
                std::function<Scalar(size_type i, size_type N, Scalar a, Scalar b)> yFunction,
                const element_index_type N, const point_type min, const point_type max);

            size_type sizeX() const { return points->shape()[0]; }
            size_type sizeY() const { return points->shape()[1]; }
            point_type min() const { return minVal; }
            point_type max() const { return maxVal; }

            array_type::iterator begin();// { return points.begin(); }
            array_type::iterator end();// { return points.end(); }
            array_type::const_iterator begin() const;// { return points.begin(); }
            array_type::const_iterator end() const;// { return points.end(); }

            array_type getPoints() { return *points; }
            const array_type getPoints() const { return *points; }

            array_type::const_reference operator[](const size_type i) const { return (*points)[i]; }
            array_type::reference operator[](const size_type i) { return (*points)[i]; }

            point_type operator()(const size_type i, const size_type j) const { return{ { (*points)[i][j][0], (*points)[i][j][1] } }; }

            void resize(const element_index_type N, const point_type min, const point_type max) {
                if (points->shape()[0] == N[0] && points->shape()[1] == N[1] &&
                    min[0] == minVal[0] && min[1] == minVal[1] &&
                    max[0] == maxVal[0] && max[1] == maxVal[1]) {
                    return;
                }
                recalculate(N, min, max);
            }

            void resize(const element_index_type N) {
                resize(N, minVal, maxVal);
            }
        };
        
#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
        inline std::ostream& operator<<(std::ostream& os, const Mesh1D& mesh) {
            os << "Mesh1D {";
            os << std::fixed << std::setw(11) << std::setprecision(6);
            for (Scalar val : mesh) {
                os << val << ", ";
            }
            return os << "}";
        }
        std::ostream& operator<<(std::ostream& os, const Mesh2D& mesh);
#endif
    }

    typedef mesh::Mesh1D Mesh1D;
}

#endif /* EMPIRICALCPP_SRC_MESH_HPP_ */
