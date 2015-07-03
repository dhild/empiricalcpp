#ifndef EMPIRICALCPP_SRC_MESH_HPP_
#define EMPIRICALCPP_SRC_MESH_HPP_

#include <empiricalcpp/src/constants.hpp>
#include <empiricalcpp/src/quadrature.hpp>
#include <functional>
#include <memory>
#include <vector>
#include <tuple>
#include <boost/multi_array.hpp>

namespace empirical {
    namespace mesh {

        class Mesh1D : public std::enable_shared_from_this<Mesh1D> {
        protected:
            typedef std::vector<Scalar> mesh_type;
            mesh_type points;
            Mesh1D(std::size_t sizeX) : points(sizeX) {}

            virtual void recalculatePoints() = 0;

        public:
            virtual ~Mesh1D() {}

            Scalar operator()(const std::size_t i) const {
                return points[i];
            }
            Scalar operator[](const std::size_t i) const {
                return points[i];
            }
            const mesh_type mesh() const {
                return points;
            }
            void resize(const std::size_t sizeX) {
                points.resize(sizeX);
                this->recalculatePoints();
            }
        };

        class Mesh2D : public std::enable_shared_from_this<Mesh2D> {
        protected:
            typedef boost::multi_array<Scalar, 3> mesh_type;
            mesh_type points;
            Mesh2D(std::size_t sizeX, std::size_t sizeY) : points(boost::extents[sizeX][sizeY][2]) {}

            virtual void recalculatePoints() = 0;

        public:
            virtual ~Mesh2D() {}

            Scalar operator()(const std::size_t i, const std::size_t j, const std::size_t k) const {
                return points[i][j][k];
            }
            mesh_type::const_multi_array_ref mesh() const;
            void resize(const std::size_t sizeX, std::size_t sizeY);
        };

        typedef std::function<Scalar(std::size_t i, std::size_t N)> MeshFunction;
        typedef std::pair<Scalar, Scalar> MeshRange;
        typedef std::tuple<std::shared_ptr<Quadrature>, Scalar, Scalar> MeshQuadrature;

        MeshRange range(Scalar min, Scalar max);
        MeshQuadrature range(std::shared_ptr<Quadrature>& q, Scalar min, Scalar max);
        MeshQuadrature range(Quadrature& q, Scalar min, Scalar max);

        std::shared_ptr<Mesh1D> createMesh(std::size_t N, MeshFunction xFunction);
        std::shared_ptr<Mesh1D> createMesh(std::size_t N, MeshRange xRange);
        std::shared_ptr<Mesh1D> createMesh(std::size_t N, MeshQuadrature xQuadrature);

        std::shared_ptr<Mesh2D> createMesh(std::size_t N, MeshFunction xFunction, std::size_t M, MeshRange yFunction);
        std::shared_ptr<Mesh2D> createMesh(std::size_t N, MeshRange xRange, std::size_t M, MeshRange yRange);
        std::shared_ptr<Mesh2D> createMesh(std::size_t N, MeshQuadrature xQuadrature, std::size_t M, MeshQuadrature yQuadrature);

#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
        std::ostream& operator<<(std::ostream& os, const Mesh1D& m);
        std::ostream& operator<<(std::ostream& os, const Mesh2D& m);
#endif
    }

    typedef mesh::Mesh1D Mesh1D;
    typedef mesh::Mesh2D Mesh2D;
}

#endif /* EMPIRICALCPP_SRC_MESH_HPP_ */
