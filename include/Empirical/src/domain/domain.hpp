#ifndef DOMAIN_HPP_
#define DOMAIN_HPP_

#include "Empirical/src/config.h"

namespace empirical {

    class Domain2D {
    protected:

        virtual ~Domain2D();

    public:

        virtual const bool isExterior() const;

    };

    class ExteriorDomain2D {
    public:

        ExteriorDomain2D();
        virtual ~ExteriorDomain2D();

        virtual const bool isExterior() const;

    };

}

#endif /* DOMAIN_HPP_ */
