#ifndef EMPIRICAL_DOMAIN_EXTERIOR_DOMAIN_2D_HPP_
#define EMPIRICAL_DOMAIN_EXTERIOR_DOMAIN_2D_HPP_

#include "Empirical/Domain.hpp"

namespace Empirical {

class ExteriorDomain2D : public Domain2D {
public:
    ExteriorDomain2D(Boundary2D* bnd, Basis2D* bas, const bool normalDir, const Scalar index)
        : Domain2D(bnd, bas, normalDir, index) {}
    virtual ~ExteriorDomain2D();

    virtual bool isExterior() const;

    virtual const cVector& getInteriorPointSample();
};
}

#endif /* EMPIRICAL_DOMAIN_EXTERIOR_DOMAIN_2D_HPP_ */
