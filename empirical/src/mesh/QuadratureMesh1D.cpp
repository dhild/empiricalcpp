#include <empiricalcpp/src/mesh.hpp>

using empirical::Scalar;
using empirical::Quadrature;
using namespace empirical::mesh;

namespace {
    class QuadratureMesh1D : public Mesh1D {
        MeshQuadrature xQuadrature;

    protected:
        virtual void recalculatePoints() {
            const std::size_t N = points.size();
            Quadrature& quad = xQuadrature.quad();
            quad.resize(N);
            const Scalar dist = (xQuadrature.max() - xQuadrature.min()) / 2.0;
            const Scalar mid = dist + xQuadrature.min();
            for (std::size_t i = 0; i < N; i++) {
                points[i] = (dist * quad.points[i]) + mid;
            }
        }

    public:
        QuadratureMesh1D(std::size_t N, MeshQuadrature xQuadrature) : Mesh1D(N), xQuadrature(xQuadrature) {
            recalculatePoints();
        }
        virtual ~QuadratureMesh1D() {}
    };
}

namespace empirical {
    namespace mesh {
        std::shared_ptr<Mesh1D> createMesh(std::size_t N, MeshQuadrature xQuadrature) {
            return std::make_shared<QuadratureMesh1D>(N, xQuadrature);
        }
    }
}
