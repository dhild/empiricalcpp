#ifndef EMPIRICAL_MESH_HPP_
#define EMPIRICAL_MESH_HPP_

#include <Empirical/Quadrature.hpp>

namespace Empirical {

    class Mesh2D {
    protected:
        cMatrix points;
        cScalar min;
        cScalar max;

        virtual void recalc(const Index x, const Index y) = 0;
        Mesh2D(const Index x, const Index y) : points(x, y) {}
    public:
        virtual ~Mesh2D() {}

        void resize(const Index x, const Index y) {
            if (x == sizeX() && y == sizeY()) {
                return;
            }
            min = points.redux([](cScalar a, cScalar b)->cScalar {
                cScalar val = a;
                if (b.real() < a.real()) {
                    val.real(b.real());
                }
                if (b.imag() < a.imag()) {
                    val.imag(b.imag());
                }
                return val;
            });
            max = points.redux([](cScalar a, cScalar b)->cScalar {
                cScalar val = a;
                if (b.real() > a.real()) {
                    val.real(b.real());
                }
                if (b.imag() > a.imag()) {
                    val.imag(b.imag());
                }
                return val;
            });
        }

        Index sizeX() const {
            return points.cols();
        }

        Index sizeY() const {
            return points.rows();
        }

        cMatrix& getPoints() {
            return points;
        }

        const cMatrix& getPoints() const {
            return points;
        }

        Scalar minX() const { return min.real(); }
        Scalar maxX() const { return max.real(); }
        Scalar minY() const { return min.imag(); }
        Scalar maxY() const { return max.imag(); }
    };

    Mesh2D* createQuadratureMesh(QuadratureFunc xQuad, QuadratureFunc yQuad, const Index x, const Index y);

}

#endif /* EMPIRICAL_MESH_HPP_ */
