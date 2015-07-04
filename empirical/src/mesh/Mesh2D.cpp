#include <empiricalcpp/src/mesh.hpp>

#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
#  include <iomanip>
#endif

namespace empirical {
    namespace mesh {
        Mesh2D::Mesh2D(std::size_t sizeX, std::size_t sizeY)
            : points(new mesh_type(boost::extents[sizeX][sizeY][2])) {
        }

        Mesh2D::~Mesh2D() {
            delete points;
        }

        void Mesh2D::resize(const std::size_t sizeX, std::size_t sizeY) {
            delete points;
            points = new mesh_type(boost::extents[sizeX][sizeY][2]);
            this->recalculatePoints();
        }

#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
        std::ostream& operator<<(std::ostream& os, const Mesh2D& mesh) {
            os << "Mesh2D {";
            os << std::fixed << std::setw(11) << std::setprecision(6);

            auto points = mesh.mesh();
            Mesh2D::mesh_type::index N = points.shape()[0];
            Mesh2D::mesh_type::index M = points.shape()[1];

            for (Mesh2D::mesh_type::index i = 0; i < N; i++) {
                for (Mesh2D::mesh_type::index j = 0; j < M; j++) {
                    os << "(" << points[i][j][0] << "," << points[i][j][1] << "), ";
                }
            }
            return os << "}";
        }
#endif
    }
}