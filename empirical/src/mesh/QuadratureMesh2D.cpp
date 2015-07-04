#include <empiricalcpp/src/mesh.hpp>

using empirical::Scalar;
using empirical::Quadrature;
using namespace empirical::mesh;

namespace {
    class QuadratureMesh2D : public Mesh2D {
        Quadrature* quadX;
        const Scalar distX;
        const Scalar midX;

        Quadrature* quadY;
        const Scalar distY;
        const Scalar midY;

        QuadratureMesh2D(const QuadratureMesh2D& other) = delete;
        QuadratureMesh2D& operator=(const QuadratureMesh2D& other) = delete;

    protected:
        virtual void recalculatePoints() {
            const mesh_type::index N = points->shape()[0];
            const mesh_type::index M = points->shape()[1];

            quadX->resize(N);
            quadY->resize(M);

            for (mesh_type::index i = 0; i < N; i++) {
                for (mesh_type::index j = 0; j < M; j++) {
                    (*points)[i][j][0] = (distX * quadX->points[i]) + midX;
                    (*points)[i][j][1] = (distY * quadY->points[j]) + midY;
                }
            }
        }

    public:
        explicit QuadratureMesh2D(
            std::size_t N, Quadrature* originalX, Scalar minX, Scalar maxX,
            std::size_t M, Quadrature* originalY, Scalar minY, Scalar maxY)
            : Mesh2D(N, M),
            quadX(originalX->clone()),
            distX((maxX - minX) / 2.0),
            midX(distX + minX),
            quadY(originalY->clone()),
            distY((maxY - minY) / 2.0),
            midY(distY + minY) {
            recalculatePoints();
        }
        virtual ~QuadratureMesh2D() {
            delete quadX;
            delete quadY;
        }
    };
}

namespace empirical {
    namespace mesh {
        Mesh2D* createMesh(std::size_t N, MeshQuadrature xQuadrature, std::size_t M, MeshQuadrature yQuadrature) {
            return new QuadratureMesh2D(
                N, xQuadrature.quadrature, xQuadrature.min, xQuadrature.max,
                M, yQuadrature.quadrature, yQuadrature.min, yQuadrature.max);
        }
    }
}
