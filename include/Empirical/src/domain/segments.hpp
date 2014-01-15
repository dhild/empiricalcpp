#ifndef SEGMENTS_HPP_
#define SEGMENTS_HPP_

#include <tuple>
#include <Eigen/Dense>
#include "Empirical/src/config.h"

namespace empirical {

    class DomainSegment2D {
    protected:
        DomainSegment2D();
        DomainSegment2D(const DomainSegment2D& other);
        virtual const DomainSegment2D& operator=(const DomainSegment2D& other);

    public:

        virtual void recalculateQuadratures(const int M) = 0;

        virtual const Eigen::ArrayBase<cScalar> getNormals() const = 0;
        virtual const Eigen::ArrayBase<cScalar> getPoints() const = 0;
        virtual const Eigen::ArrayBase<cScalar> getFirstDerivative() const = 0;

        virtual ~DomainSegment2D() = 0;
    };

}

#endif /* SEGMENTS_HPP_ */
