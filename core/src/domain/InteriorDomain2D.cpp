#include "BaseDomain2D.hpp"
#include <functional>
#include <memory>

using namespace Empirical;
using namespace std;

namespace Empirical {
    
class InteriorDomain2D : public BaseDomain2D {
public:
    InteriorDomain2D(Boundary2D* bnd, Basis2D* bas, const bool normalDir, const Scalar index)
        : BaseDomain2D(bnd, bas, normalDir, index) {}

    virtual ~InteriorDomain2D() {
    }

    virtual bool isExterior() const {
        return false;
    }

    virtual bool isDomainPoint(const cScalar) const {
        return false;
    }

    virtual const Mesh2D* getInteriorPointSample(const int64_t, const int64_t) {
        Mesh2D* vector = nullptr;
        return vector;
    }
};

Domain2D* createInteriorDomain2D(Boundary2D* boundary, Basis2D* basis,
    bool domainInNormalDirection, Scalar indexOfRefraction) {
    return new InteriorDomain2D(boundary, basis, domainInNormalDirection, indexOfRefraction);
}

}
