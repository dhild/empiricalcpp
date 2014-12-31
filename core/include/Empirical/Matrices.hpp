#ifndef EMPIRICAL_MATRICES_HPP_
#define EMPIRICAL_MATRICES_HPP_

#include "Empirical/Constants.hpp"
#include <Eigen/Core>

namespace Empirical {

typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;
typedef Eigen::Matrix<cScalar, Eigen::Dynamic, 1> cVector;

typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> Matrix;
typedef Eigen::Matrix<cScalar, Eigen::Dynamic, Eigen::Dynamic> cMatrix;

}

#endif /* EMPIRICAL_MATRICES_HPP_ */
