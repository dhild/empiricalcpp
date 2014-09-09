#ifndef SEGMENTS_HPP_
#define SEGMENTS_HPP_

#include <functional>
#include <Eigen/Dense>
#include "Empirical/src/config.h"

namespace empirical {

    typedef Eigen::Matrix<cScalar, Eigen::Dynamic, 1> Mesh1D;

    class DomainSegment2D {
    protected:
        std::function<cScalar(cScalar) > bc;
        std::function<cScalar(cScalar) > bcN;
        bool boundaryInPositiveNormalDirection;

        DomainSegment2D();

    public:

        virtual int size() const = 0;
        virtual const Mesh1D getNormals() const;
        virtual const Mesh1D getPoints() const = 0;
        virtual const Mesh1D getPointDerivatives() const = 0;
        virtual const Mesh1D getBoundaryCondition() const;
        virtual const Mesh1D getBoundaryConditionNormalDeriv() const;
        virtual bool isBoundaryInPositiveNormalDirection() const;

        virtual void setBoundaryInPositiveNormalDirection(const bool bcPositive);
        virtual void setBoundaryCondition(const std::function<cScalar(cScalar) >& bc);
        virtual void setBoundaryConditionNormal(const std::function<cScalar(cScalar) >& bcN);

        virtual ~DomainSegment2D() = 0;
    };

}

#endif /* SEGMENTS_HPP_ */
