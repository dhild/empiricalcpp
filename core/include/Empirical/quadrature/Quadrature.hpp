#ifndef QUADRATURE_HPP_
#define QUADRATURE_HPP_

#include "Empirical/Constants.hpp"
#include <Eigen/Core>
#include <utility>

namespace Empirical {

    typedef Eigen::Array<Scalar, Eigen::Dynamic, 1> QuadratureVector;

    class Quadrature {
    protected:
        QuadratureVector points;
        QuadratureVector weights;

        Quadrature(const int N) : points(N), weights(N) {}

   public:

        virtual ~Quadrature();
        virtual void resize(const int N);

        int64_t size() const {
            return points.rows();
        }

        const QuadratureVector& getPoints() const {
            return points;
        }

        const QuadratureVector& getWeights() const {
            return weights;
        }
    };

    class LegendreGaussLobatto : public Quadrature {
     private:
      void recalc(const int N);
     public:
      LegendreGaussLobatto(const int N);
      virtual ~LegendreGaussLobatto();
      virtual void resize(const int N);
    };

    class TrapezoidQuadrature : public Quadrature {
     private:
      void recalc(const int N);
     public:
      TrapezoidQuadrature(const int N);
      virtual ~TrapezoidQuadrature();
      virtual void resize(const int N);
    };

    class PeriodicTrapezoidQuadrature : public Quadrature {
     private:
      void recalc(const int N);
     public:
      PeriodicTrapezoidQuadrature(const int N);
      virtual ~PeriodicTrapezoidQuadrature();
      virtual void resize(const int N);
    };

    Quadrature* createLGL(const int N);
    Quadrature* createTrapezoid(const int N);
    Quadrature* createPeriodicTrapezoid(const int N);
}

#endif /* QUADRATURE_HPP_ */
