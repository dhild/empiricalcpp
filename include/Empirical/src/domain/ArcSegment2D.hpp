#ifndef EMPIRICAL_DOMAIN_ARCSEGMENT2D_HPP_
#define EMPIRICAL_DOMAIN_ARCSEGMENT2D_HPP_

#include "Empirical/src/domain/segments.hpp"
#include "Empirical/src/quadrature/Quadrature.hpp"

namespace empirical {

    class ArcSegment2D: public DomainSegment2D {
    private:

        Quadrature& z;
        Quadrature* zPrime;
        Quadrature* normals;

    public:

        ArcSegment2D(const Quadrature& points, const Quadrature& pointsPrime);

        virtual ~ArcSegment2D();

        virtual void recalculateQuadratures(const int M);

        virtual const Eigen::ArrayBase<cScalar> getNormals() const;
        virtual const Eigen::ArrayBase<cScalar> getPoints() const;
        virtual const Eigen::ArrayBase<cScalar> getFirstDerivative() const;

    };

    const ArcSegment2D createArcSegment2D(const cScalar& center, const Scalar& radius, const Scalar& theta0,
            const Scalar& theta1);

}

#endif /* EMPIRICAL_DOMAIN_ARCSEGMENT2D_HPP_ */
