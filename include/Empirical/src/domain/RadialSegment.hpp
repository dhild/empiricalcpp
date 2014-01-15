#ifndef EMPIRICAL_DOMAIN_RADIALSEGMENT_HPP_
#define EMPIRICAL_DOMAIN_RADIALSEGMENT_HPP_

#include <functional>
#include <Eigen/Dense>
#include "Empirical/src/domain/segments.hpp"
#include "Empirical/src/quadrature/Quadrature.hpp"
#include "Empirical/src/config.h"

namespace empirical {

    class RadialSegment2D: public DomainSegment2D {
    private:

        const std::function<cScalar(cScalar)>& z;
        const std::function<cScalar(cScalar)>& zPrime;

        Quadrature* points;
        Quadrature* pointPrimes;
        Quadrature* normals;

    public:

        RadialSegment2D(const std::function<cScalar(cScalar)>& z, const std::function<cScalar(cScalar)>& zPrime,
                const int M);

        virtual ~RadialSegment2D();

        virtual void recalculateQuadratures(const int M);

        virtual const Eigen::ArrayBase<cScalar> getNormals() const;
        virtual const Eigen::ArrayBase<cScalar> getPoints() const;
        virtual const Eigen::ArrayBase<cScalar> getFirstDerivative() const;

    };

}

#endif /* RADIALSEGMENT_HPP_ */
