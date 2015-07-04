#include <empiricalcpp/src/mesh.hpp>

using namespace empirical::mesh;

namespace {
    class FunctionMesh2D : public Mesh2D {
        MeshFunction xFunction;
        MeshFunction yFunction;

    protected:
        virtual void recalculatePoints() {
            const mesh_type::index N = points->shape()[0];
            const mesh_type::index M = points->shape()[1];
            for (mesh_type::index i = 0; i < N; i++) {
                for (mesh_type::index j = 0; j < M; j++) {
                    (*points)[i][j][0] = xFunction(i, N);
                    (*points)[i][j][1] = yFunction(j, M);
                }
            }
        }

    public:
        FunctionMesh2D(std::size_t N, MeshFunction xFunction, std::size_t M, MeshFunction yFunction)
            : Mesh2D(N, M), xFunction(xFunction), yFunction(yFunction) {
            recalculatePoints();
        }
        virtual ~FunctionMesh2D() {}
    };
}

namespace empirical {
    namespace mesh {
        Mesh2D* createMesh(std::size_t N, MeshFunction xFunction, std::size_t M, MeshFunction yFunction) {
            return new FunctionMesh2D(N, xFunction, M, yFunction);
        }
    }
}
