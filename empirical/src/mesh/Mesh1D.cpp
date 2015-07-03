#include <empiricalcpp/src/mesh.hpp>

#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
#  include <iomanip>
#endif
namespace empirical {
    namespace mesh {
        MeshRange range(Scalar min, Scalar max) {
            return std::make_pair(min, max);
        }
        MeshQuadrature range(std::shared_ptr<Quadrature>& q, Scalar min, Scalar max) {
            return std::make_tuple(q, min, max);
        }
        MeshQuadrature range(Quadrature& q, Scalar min, Scalar max) {
            return std::make_tuple(q.shared_from_this(), min, max);
        }

#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
        std::ostream& operator<<(std::ostream& os, const Mesh1D& mesh) {
            os << "Mesh1D {";
            os << std::fixed << std::setw(11) << std::setprecision(6);
            for (Scalar val : mesh.mesh()) {
                os << val << ", ";
            }
            return os << "}";
        }
#endif
    }
}
