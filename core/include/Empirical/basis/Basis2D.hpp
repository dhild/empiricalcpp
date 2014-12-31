#ifndef EIGEN_BASIS_BASIS_HPP_
#define EIGEN_BASIS_BASIS_HPP_

#include "Empirical/Constants.hpp"
#include "Empirical/domain/Domain2D.hpp"
#include <functional>
#include <Eigen/Dense>

namespace Empirical {

class Basis2D {

public:

    virtual ~Basis2D();

    virtual int64_t size() const = 0;

    virtual cScalar basis(const Scalar k, const cScalar z, const cScalar x) const = 0;
    virtual cScalar basisNormalDerivative(const Scalar k, const cScalar z,
                                          const cScalar x) const = 0;

    virtual cVector basis(const Scalar k, const cScalar z) const = 0;
    virtual cVector basisNormalDerivative(const Scalar k, const cScalar z) const = 0;

    virtual cMatrix basis(const Scalar k, const cVector& z) const = 0;
    virtual cMatrix basisNormalDerivative(const Scalar k, const cVector& z) const = 0;

};

}

#endif /* EIGEN_BASIS_BASIS_HPP_ */
