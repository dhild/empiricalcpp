#include <empiricalcpp/src/mesh.hpp>

using empirical::Scalar;
using empirical::Quadrature;
using namespace empirical::mesh;

namespace {
    class QuadratureMesh1D : public Mesh1D {
        Quadrature* quad;
        const Scalar dist;
        const Scalar mid;

        QuadratureMesh1D(const QuadratureMesh1D& other) = delete;
        QuadratureMesh1D& operator=(const QuadratureMesh1D& other) = delete;

    protected:
        virtual void recalculatePoints() {
            const std::size_t N = points.size();
            quad->resize(N);
            for (std::size_t i = 0; i < N; i++) {
                points[i] = (dist * quad->points[i]) + mid;
            }
        }

    public:
        explicit QuadratureMesh1D(std::size_t N, Quadrature* original, Scalar min, Scalar max)
            : Mesh1D(N),
            quad(original->clone()),
            dist((max - min) / 2.0),
            mid(dist + min) {
            recalculatePoints();
        }
        virtual ~QuadratureMesh1D() {
            delete quad;
        }
    };
}

namespace empirical {
    namespace mesh {
        Mesh1D* createMesh(std::size_t N, MeshQuadrature xQuadrature) {
            return new QuadratureMesh1D(N, xQuadrature.quadrature, xQuadrature.min, xQuadrature.max);
        }
    }
}
