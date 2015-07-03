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
            typedef boost::multi_array<Scalar, 2> mesh_type;
            mesh_type points;
            Mesh1D(std::size_t sizeX) : points(boost::extents[sizeX][2]) {}

            virtual void recalculatePoints() = 0;

        public:
            virtual ~Mesh1D() {}

            mesh_type::const_multi_array_ref mesh() const;
            void resize(std::size_t sizeX);
        };

        class Mesh2D : public std::enable_shared_from_this<Mesh2D> {
        protected:
            typedef boost::multi_array<Scalar, 3> mesh_type;
            mesh_type points;
            Mesh2D(std::size_t sizeX, std::size_t sizeY) : points(boost::extents[sizeX][sizeY][2]) {}

            virtual void recalculatePoints() = 0;

        public:
            virtual ~Mesh2D() {}

            mesh_type::const_multi_array_ref mesh() const;
            void resize(std::size_t sizeX, std::size_t sizeY);
        };

        typedef std::tuple<std::size_t, Scalar, Scalar> MeshRange;
        typedef std::tuple<std::shared_ptr<Quadrature>, Scalar, Scalar> MeshQuadrature;

        MeshRange range(std::size_t size, Scalar min, Scalar max) {
            return std::make_tuple(size, min, max);
        }
        MeshQuadrature range(std::shared_ptr<Quadrature>& q, Scalar min, Scalar max) {
            return std::make_tuple(q, min, max);
        }
        MeshQuadrature range(Quadrature& q, Scalar min, Scalar max) {
            return std::make_tuple(q.shared_from_this(), min, max);
        }

        std::shared_ptr<Mesh1D> createMesh(MeshRange xRange);
        std::shared_ptr<Mesh1D> createMesh(MeshQuadrature xQuadrature);

        std::shared_ptr<Mesh2D> createMesh(MeshRange xRange, MeshRange yRange);
        std::shared_ptr<Mesh2D> createMesh(MeshQuadrature xQuadrature, MeshQuadrature yQuadrature);

    }

    typedef mesh::Mesh1D Mesh1D;
    typedef mesh::Mesh2D Mesh2D;
}

#endif /* EMPIRICALCPP_SRC_MESH_HPP_ */
