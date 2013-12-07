/* 
 * File:   quadrature.h
 * Author: D. Ryan Hild <d.ryan.hild@gmail.com>
 *
 * Created on December 5, 2013, 4:18 AM
 */

#ifndef QUADRATURE_H
#define	QUADRATURE_H

#include <Eigen/Dense>

namespace empirical {

  class Quadrature {
  protected:
    unsigned long N;
    double a;
    double b;
    Eigen::ArrayXd x;
    Eigen::ArrayXd w;
    
    Quadrature(const unsigned long N, const double a, const double b);

    virtual void recalc() = 0;
    
  public:
    virtual ~Quadrature();

    virtual void update(const unsigned long N);
    virtual void update(const double a, const double b);
    virtual void update(const unsigned long N, const double a, const double b);

    unsigned long getN() const { return N; }
    double getA() const { return a; }
    double getB() const { return b; }

    const Eigen::ArrayXd getPoints() const { return x; }
    const Eigen::ArrayXd getWeights() const { return w; }

    virtual double integrate(double (*f)(const double)) const;
  };

  class PeriodicTrapezoid : public Quadrature {
  public:
    PeriodicTrapezoid(const unsigned long N, const double a = -1, const double b = 1);

  protected:
    virtual void recalc();
  };

  class TrapezoidQuadrature : public Quadrature {
  public:
    TrapezoidQuadrature(const unsigned long N, const double a = -1, const double b = 1);

  protected:
    virtual void recalc();
  };

  class LegendreGaussLobatto : public Quadrature {
  public:
    LegendreGaussLobatto(const unsigned long N, const double a = -1, const double b = 1);

  protected:
    virtual void recalc();
  };

}

#endif	/* QUADRATURE_H */

