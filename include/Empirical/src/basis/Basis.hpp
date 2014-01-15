#ifndef EIGEN_BASIS_BASIS_HPP_
#define EIGEN_BASIS_BASIS_HPP_

#include <Eigen/Dense>
#include "Empirical/src/config.h"
#include "Empirical/src/quadrature/Quadrature.hpp"

namespace empirical {

    class Basis2D {
    protected:
        Basis2D();

    public:

        /** Gets the result of applying this basis function to the given complex coordinate. */
        virtual cScalar operator()(const Scalar& k, const cScalar& z) const;

        virtual cScalar operator()(const Scalar& k, const Scalar& x, const Scalar& y) const;

        virtual const Mesh2D matrix(const Scalar& k, const Mesh2D& z) const;
        virtual const Mesh2D matrix1(const Scalar& k, const Mesh2D& z) const;

        virtual int pointCounts() const;

        virtual void updateN(const int N);

        virtual ~Basis2D() = 0;

    };

}

#endif /* EIGEN_BASIS_BASIS_HPP_ */
