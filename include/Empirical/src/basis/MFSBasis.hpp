#ifndef EMPIRICAL_BASIS_MFSBASIS_HPP_
#define EMPIRICAL_BASIS_MFSBASIS_HPP_

#include <Eigen/Dense>
#include "Empirical/src/config.h"
#include "Empirical/src/basis/Basis.hpp"

namespace empirical {

    class MFSBasis2D : public Basis2D {
    private:
        Mesh1D q;

    public:
        MFSBasis2D(const Mesh1D& chargePoints);

        virtual cScalar operator()(const Scalar& k, const cScalar& z) const;

        virtual cScalar operator()(const Scalar& k, const Scalar& x, const Scalar& y) const;

        virtual const Mesh2D matrix(const Scalar& k, const Mesh2D& z) const;
        virtual const Mesh2D matrix1(const Scalar& k, const Mesh2D& z) const;

        virtual int pointCounts() const;

        virtual void updateN(const int N);

        virtual ~MFSBasis2D();

    private:
        MFSBasis2D(const MFSBasis2D& basis);

    };

}

#endif /* EMPIRICAL_BASIS_MFSBASIS_HPP_ */
