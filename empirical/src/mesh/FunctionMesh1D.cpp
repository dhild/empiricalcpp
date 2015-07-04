#include <empiricalcpp/src/mesh.hpp>

using namespace empirical::mesh;

namespace {
    class FunctionMesh1D : public Mesh1D {
        MeshFunction xFunction;

    protected:
        virtual void recalculatePoints() {
            const std::size_t N = points.size();
            for (std::size_t i = 0; i < N; i++) {
                points[i] = xFunction(i, N);
            }
        }

    public:
        FunctionMesh1D(std::size_t N, MeshFunction xFunction) : Mesh1D(N), xFunction(xFunction) {
            recalculatePoints();
        }
        virtual ~FunctionMesh1D() {}
    };
}

namespace empirical {
    namespace mesh {
        Mesh1D* createMesh(std::size_t N, MeshFunction xFunction) {
            return new FunctionMesh1D(N, xFunction);
        }
    }
}
