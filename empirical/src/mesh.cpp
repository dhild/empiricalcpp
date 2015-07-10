#include <empiricalcpp/src/mesh.hpp>

namespace empirical {
    namespace mesh {
        Mesh1D::Mesh1D(const Quadrature& quadrature) : points(1) {
            std::shared_ptr<Quadrature> localQuad = std::make_shared<Quadrature>(Quadrature(quadrature));
            generator = [localQuad](const size_type N, const Scalar a, const Scalar b)->vector_type {
                localQuad->resize(N, a, b);
                return localQuad->getPoints();
            };
            recalculate(quadrature.size(), quadrature.min(), quadrature.max());
        }
        Mesh1D::Mesh1D(std::function<Scalar(size_type i, size_type N, Scalar a, Scalar b)> pointFunction,
            const size_type N, const Scalar min, const Scalar max) : points(1) {
            generator = [pointFunction](const size_type N, const Scalar a, const Scalar b)->vector_type {
                std::vector<Scalar> vec(N);
                for (size_type i = 0; i < N; i++) {
                    vec[i] = pointFunction(i, N, a, b);
                }
                return vec;
            };
            recalculate(N, min, max);
        }

        void Mesh2D::recalculate(const element_index_type N, const point_type min, const point_type max) {
            minVal = min;
            maxVal = max;
            points = std::unique_ptr<array_type>(generator(N, min, max));
        }

        Mesh2D::Mesh2D(const Quadrature& xQuadrature, const Quadrature& yQuadrature) {
            std::shared_ptr<Quadrature> localQuadX = std::make_shared<Quadrature>(Quadrature(xQuadrature));
            std::shared_ptr<Quadrature> localQuadY = std::make_shared<Quadrature>(Quadrature(yQuadrature));
            generator = [localQuadX, localQuadY](const element_index_type N, const point_type a, const point_type b)->array_type* {
                array_type* mesh = new array_type(boost::extents[N[0]][N[1]][2]);
                localQuadX->resize(N[0], a[0], b[0]);
                localQuadY->resize(N[1], a[1], b[1]);
                for (size_type i = 0; i < N[0]; i++) {
                    for (size_type j = 0; j < N[1]; j++) {
                        (*mesh)[i][j][0] = localQuadX->getPoints()[i];
                        (*mesh)[i][j][1] = localQuadY->getPoints()[j];
                    }
                }
                return mesh;
            };

            recalculate({ { xQuadrature.size(), yQuadrature.size() } },
            { { xQuadrature.min(), yQuadrature.min() } },
            { { xQuadrature.max(), yQuadrature.max() } });
        }

        Mesh2D::Mesh2D(std::function<Scalar(size_type i, size_type N, Scalar a, Scalar b)> xFunction,
            std::function<Scalar(size_type i, size_type N, Scalar a, Scalar b)> yFunction,
            const element_index_type N, const point_type min, const point_type max) {

            generator = [xFunction, yFunction](const element_index_type N, const point_type a, const point_type b)->array_type* {
                std::vector<Scalar> x(N[0]);
                std::vector<Scalar> y(N[1]);
                for (size_type i = 0; i < N[0]; i++) {
                    x[i] = xFunction(i, N[0], a[0], b[0]);
                }
                for (size_type i = 0; i < N[1]; i++) {
                    x[i] = yFunction(i, N[1], a[1], b[1]);
                }
                array_type* mesh = new array_type(boost::extents[N[0]][N[1]][2]);
                for (size_type i = 0; i < N[0]; i++) {
                    for (size_type j = 0; j < N[1]; j++) {
                        (*mesh)[i][j][0] = x[i];
                        (*mesh)[i][j][1] = y[i];
                    }
                }
                return mesh;
            };

            recalculate(N, min, max);
        }

        std::ostream& operator<<(std::ostream& os, const Mesh2D& mesh) {
            os << "Mesh2D {";
            os << std::fixed << std::setw(11) << std::setprecision(6);
            for (auto subarray : mesh) {
                for (auto subarray2 : subarray) {
                    for (auto element : subarray2) {
                        os << element << ", ";
                    }
                }
            }
            return os << "}";
        }
    }
}
