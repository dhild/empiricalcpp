#ifndef SEGMENTS_HPP_
#define SEGMENTS_HPP_

#include <tuple>
#include <Eigen/Dense>
#include "Empirical/src/config.h"

namespace empirical {

    class DomainSegment2D {
    protected:
        DomainSegment2D();

    public:

        virtual int size() const = 0;
        virtual const Mesh1D getNormals() const = 0;
        virtual const Mesh1D getPoints() const = 0;
        virtual const Mesh1D getPointDerivatives() const = 0;
        virtual const Mesh1D getA() const = 0;
        virtual const Mesh1D getB() const = 0;
        virtual const Mesh1D getF(const Mesh1D& points) const = 0;
        virtual bool isBoundaryPositiveNormal() const = 0;

        virtual ~DomainSegment2D() = 0;
    };

}

#endif /* SEGMENTS_HPP_ */
