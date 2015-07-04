#include <empiricalcpp/src/mesh.hpp>

using empirical::Scalar;
using namespace empirical::mesh;

namespace {
    class RangeMesh2D : public Mesh2D {
        MeshRange xRange;
        MeshRange yRange;

    protected:
        virtual void recalculatePoints() {
            const mesh_type::index N = points->shape()[0];
            const mesh_type::index M = points->shape()[1];
            const Scalar distX = xRange.second - xRange.first;
            const Scalar distY = yRange.second - yRange.first;

            for (mesh_type::index i = 0; i < N; i++) {
                for (mesh_type::index j = 0; j < M; j++) {
                    (*points)[i][j][0] = ((distX * i) / N) + xRange.first;
                    (*points)[i][j][1] = ((distY * j) / M) + yRange.first;
                }
            }
        }

    public:
        RangeMesh2D(std::size_t N, MeshRange xRange, std::size_t M, MeshRange yRange)
            : Mesh2D(N, M), xRange(xRange), yRange(yRange) {
            recalculatePoints();
        }
        virtual ~RangeMesh2D() {}
    };
}

namespace empirical {
    namespace mesh {
        Mesh2D* createMesh(std::size_t N, MeshRange xRange, std::size_t M, MeshRange yRange) {
            return new RangeMesh2D(N, xRange, M, yRange);
        }
    }
}
