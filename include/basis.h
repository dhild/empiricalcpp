#ifndef EMPIRICAL_BASIS_H
#define EMPIRICAL_BASIS_H

#include <complex>
#include <Eigen/Dense>
#include "quadrature.h"

namespace empirical {

  typedef std::complex<double> cdouble;
  
  class Basis {
  protected:
    Quadrature& q;

    Basis(Quadrature& quadrature);
    Basis(const Basis& b);

  public:
    virtual ~Basis() = 0;

    unsigned long size() const;

    virtual cdouble evaluate(const double k, const double px, const double py, const double qx, const double qy) const = 0;

    Eigen::Matrix<cdouble, Eigen::Dynamic, Eigen::Dynamic> getMatrix(const double k, const Quadrature& points) const;
  };

  class MFSBasis : public Basis {
  private:
    cdouble hankel1(const double v, const cdouble z) const;
    cdouble evaluateHankel(const double v, const double z) const;

  protected:
    MFSBasis(const MFSBasis& basis);

  public:
    MFSBasis(Quadrature& quadrature);

    virtual ~MFSBasis();

    virtual cdouble evaluate(const double k, const double px, const double py, const double qx, const double qy) const;
  };

}

#endif // EMPIRICAL_BASIS_H
