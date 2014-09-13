#ifndef EMPIRICAL_DOMAIN_BVP_HPP_
#define	EMPIRICAL_DOMAIN_BVP_HPP_

#include <vector>
#include "Empirical/src/config.h"
#include "Empirical/src/domain/Domain2D.hpp"

namespace empirical {

class Solution {
 protected:
  std::vector<const Basis2D*> bases;
  Mesh1D solution_coeficients;

 public:
  virtual ~Solution();

  virtual cScalar operator()(const cScalar point) const;
  virtual cScalar operator()(const cScalar point) const;
  virtual cScalar operator()(const cScalar point) const;
};

class BoundaryValueProblem2D {
 protected:
  std::vector<Domain2D*> domains;

  Mesh2D boundary_condition_matrix;
  Mesh1D right_hand_side;
  Mesh1D solution_coeficients;
  Solution* solution;

  bool boundary_condition_dirty;
  bool right_hand_side_dirty;
  bool solved;

 public:

  virtual ~BoundaryValueProblem2D();

  virtual const Solution& solve();

  virtual Scalar conditionNumber() const;
  virtual Scalar residualNorm() const;
  
  virtual const Solution& getSolution() const;
};

}

#endif	/* EMPIRICAL_DOMAIN_BVP_HPP_ */

