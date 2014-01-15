#ifndef EMPIRICAL_DOMAIN_BASICDOMAINSEGMENT2D_HPP_
#define EMPIRICAL_DOMAIN_BASICDOMAINSEGMENT2D_HPP_

#include "Empirical/src/domain/segments.hpp"
#include "Empirical/src/quadrature/Quadrature.hpp"

namespace empirical {

    class BasicDomainSegment2D : public DomainSegment2D {
    private:

        Quadrature& z;
        Quadrature& zPrime;
        Eigen::Array<cScalar, Eigen::Dynamic, 1> normals;

        void updateNormals();

    public:

        BasicDomainSegment2D(Quadrature& points, Quadrature& pointPrimes);

        virtual ~BasicDomainSegment2D();

        virtual void recalculateQuadratures(const int M);

        virtual const Eigen::Array<cScalar, Eigen::Dynamic, 1>& getNormals() const;
        virtual const Eigen::Array<cScalar, Eigen::Dynamic, 1>& getPoints() const;
        virtual const Eigen::Array<cScalar, Eigen::Dynamic, 1>& getFirstDerivative() const = 0;

    };

}

#endif /* EMPIRICAL_DOMAIN_BASICDOMAINSEGMENT2D_HPP_ */
