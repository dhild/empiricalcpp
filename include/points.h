#ifndef EMPIRICAL_POINTS_H
#define EMPIRICAL_POINTS_H

#include <Eigen/Dense>
#include "quadrature.h"

namespace empirical {

  class BoundaryPoints {
  protected:
    Quadrature* quadrature;
  }

}

#endif // EMPIRICAL_POINTS_H
