#ifndef DOMAIN_HPP_
#define DOMAIN_HPP_

#include <vector>
#include <pair>
#include "Empirical/src/config.h"
#include "Empirical/src/basis/Basis.hpp"
#include "Empirical/src/domain/DomainSegment2D.hpp"

namespace empirical {

    enum NormalDirection {
        UNCHANGED, REVERSED
    };

    class Domain2D {
    protected:

        /** Segments and their normal sense */
        std::vector<std::pair<DomainSegment2D, NormalDirection> > segments;
        std::vector<Basis2D> bases;
        bool isExterior;
        Scalar wavenumber;
        Scalar refractiveIndex;

    public:

        Domain2D();
        
        virtual ~Domain2D();

        const bool isExterior() const {
            return this->isExterior;
        }
        const Scalar getWavenumber() const {
            return this->wavenumber;
        }
        const Scalar getRefractiveIndex() const {
            return this->refractiveIndex;
        }

    };

}

#endif /* DOMAIN_HPP_ */
