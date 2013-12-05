/* 
 * File:   quadrature.h
 * Author: D. Ryan Hild <d.ryan.hild@gmail.com>
 *
 * Created on December 5, 2013, 4:18 AM
 */

#ifndef QUADRATURE_H
#define	QUADRATURE_H

#include "config.h"

namespace quadrature {

  class Quadrature {
  protected:
    IntegerType length;
    ScalarType* nodes;
    ScalarType* weights;
    
    Quadrature(IntegerType length);
    
  public:
    virtual ~Quadrature();
    
    virtual void update(IntegerType length);

  private:
    void allocate();
    void deallocate();
  };

  class Linear : Quadrature {
  public:
    Linear(IntegerType length);
  };

}

#endif	/* QUADRATURE_H */

