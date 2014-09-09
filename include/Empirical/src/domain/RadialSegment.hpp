#ifndef EMPIRICAL_DOMAIN_RADIALSEGMENT_HPP_
#define EMPIRICAL_DOMAIN_RADIALSEGMENT_HPP_

#include <functional>
#include <Eigen/Dense>
#include "Empirical/src/domain/DomainSegment2D.hpp"
#include "Empirical/src/quadrature/Quadrature.hpp"
#include "Empirical/src/config.h"

namespace empirical {

    class RadialSegment2D : public DomainSegment2D {
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

        virtual int size() const = 0;
        virtual const Mesh1D getNormals() const = 0;
        virtual const Mesh1D getPoints() const = 0;
        virtual const Mesh1D getPointDerivatives() const = 0;
        virtual const Mesh1D getBoundaryCondition() const = 0;
        virtual const Mesh1D getBoundaryConditionNormalDeriv() const = 0;
        virtual const Mesh1D applyBoundaryCondition(const Mesh1D& points) const = 0;
        virtual bool isBoundaryPositiveNormal() const = 0;

    };

}

#endif /* RADIALSEGMENT_HPP_ */
