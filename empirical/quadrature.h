/* 
 * File:   quadrature.h
 * Author: D. Ryan Hild <d.ryan.hild@gmail.com>
 *
 * Created on December 5, 2013, 4:18 AM
 */

#ifndef QUADRATURE_H
#define	QUADRATURE_H

namespace quadrature {

    class Quadrature {
    protected:
        long length;
        double* nodes;
        double* weights;
        
        Quadrature(long length);
        
    public:
        virtual ~Quadrature();

        long getLength();
        double* getNodes();
        double* getWeights();
        
        virtual void update(long length);
    };

    class Linear : Quadrature {
    public:
        Linear(long length);
    };

}

#endif	/* QUADRATURE_H */

