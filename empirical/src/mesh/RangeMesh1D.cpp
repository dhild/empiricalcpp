#include <empiricalcpp/src/mesh.hpp>

using empirical::Scalar;
using namespace empirical::mesh;

namespace {
    class RangeMesh1D : public Mesh1D {
        MeshRange xRange;

    protected:
        virtual void recalculatePoints() {
            const std::size_t N = points.size();
            const Scalar dist = xRange.second - xRange.first;
            for (std::size_t i = 0; i < N; i++) {
                points[i] = ((dist * i) / N) + xRange.first;
            }
        }

    public:
        RangeMesh1D(std::size_t N, MeshRange xRange) : Mesh1D(N), xRange(xRange) {
            recalculatePoints();
        }
        virtual ~RangeMesh1D() {}
    };
}

namespace empirical {
    namespace mesh {
        Mesh1D* createMesh(std::size_t N, MeshRange xRange) {
            return new RangeMesh1D(N, xRange);
        }
    }
}
