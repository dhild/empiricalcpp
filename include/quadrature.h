/* 
 * File:   quadrature.h
 * Author: D. Ryan Hild <d.ryan.hild@gmail.com>
 *
 * Created on December 5, 2013, 4:18 AM
 */

#ifndef QUADRATURE_H
#define	QUADRATURE_H

#include "config.h"

namespace empirical {

  class Quadrature {
  protected:
    IntegerType length;
    ScalarType a;
    ScalarType b;
    ScalarType* nodes;
    ScalarType* weights;
    
    Quadrature(const IntegerType length, const ScalarType a, const ScalarType b);

    virtual void recalc() = 0;
    
  public:
    virtual ~Quadrature() = 0;

    virtual void update(const IntegerType length);
    virtual void update(const ScalarType a, const ScalarType b);
    virtual void update(const IntegerType length, const ScalarType a, const ScalarType b);

    IntegerType getLength() { return this->length; }
    ScalarType getA() { return this->a; }
    ScalarType getB() { return this->b; }

    virtual ScalarType integrate(const FunctionType f);

  private:
    void allocate();
    void deallocate();
  };

  class Linear : public Quadrature {
  public:
    Linear(const IntegerType length, const ScalarType a = -1, const ScalarType b = 1);

  protected:
    virtual void recalc();
  };

}

#endif	/* QUADRATURE_H */

