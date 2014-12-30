#ifndef EMPIRICAL_LIBMATH_PROBLEM2D_HPP_
#define EMPIRICAL_LIBMATH_PROBLEM2D_HPP_

#include <vector>
#include <functional>
#include "Empirical/src/problem/BoundaryValueProblem2D.hpp"

namespace empirical {

class BoundaryValueSolution2D : public Solution2D {
 protected:
  std::vector<std::function<cScalar(const cScalar)>> components;

 public:
  BoundaryValueSolution2D(const int N);

  virtual ~BoundaryValueSolution2D();

  virtual void addBasis(const std::function<cScalar(const cScalar)>& basis,
                        const cScalar coefficient);

  virtual cScalar operator()(const cScalar point) const;
  virtual Mesh1D operator()(const Mesh1D& points) const;
  virtual Mesh2D operator()(const Mesh2D& points) const;
};

}

#endif /* EMPIRICAL_LIBMATH_PROBLEM2D_HPP_ */
