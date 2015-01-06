#ifndef EMPIRICAL_DOMAIN_INTERIOR_DOMAIN_2D_HPP_
#define EMPIRICAL_DOMAIN_INTERIOR_DOMAIN_2D_HPP_

#include "Empirical/Domain.hpp"

namespace Empirical {

class InteriorDomain2D : public Domain2D {
public:
    InteriorDomain2D(Boundary2D* bnd, Basis2D* bas, const bool normalDir, const Scalar index)
        : Domain2D(bnd, bas, normalDir, index) {}
    virtual ~InteriorDomain2D();

    virtual bool isExterior() const;

    virtual const cVector& getInteriorPointSample();
};
}

#endif /* EMPIRICAL_DOMAIN_INTERIOR_DOMAIN_2D_HPP_ */
