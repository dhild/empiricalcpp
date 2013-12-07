#ifndef EMPIRICAL_BOUNDARY_H
#define EMPIRICAL_BOUNDARY_H

#include <Eigen/Dense>
#include "quadrature.h"

namespace empirical {

  class BoundaryPoints {
  protected:
    Quadrature* quadrature;

  public:
    BoundaryPoints(Quadrature* quadrature);
    BoundaryPoints(const BoundaryPoints& bp);
    virtual ~BoundaryPoints();
  }

}

#endif
