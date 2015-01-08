#include "Empirical/domain/InteriorDomain2D.hpp"
#include "Empirical/domain/ExteriorDomain2D.hpp"

using namespace Empirical;
using namespace Eigen;

InteriorDomain2D::~InteriorDomain2D() {}

bool InteriorDomain2D::isExterior() const {
    return false;
}

ExteriorDomain2D::~ExteriorDomain2D() {}

bool ExteriorDomain2D::isExterior() const {
    return true;
}
