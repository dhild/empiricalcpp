#ifndef EMPIRICAL_MESH_HPP_
#define EMPIRICAL_MESH_HPP_

#include <Empirical/Quadrature.hpp>

namespace Empirical {

class Mesh2D {
protected:
    cMatrix points;

    virtual void recalc(const int64_t x, const int64_t y) = 0;
    Mesh2D(const int64_t x, const int64_t y) : points(x, y) {}
public:
    virtual ~Mesh2D() {}

    void resize(const int64_t x, const int64_t y) {
        if (x == sizeX() && y == sizeY()) {
            return;
        }
        points.resize(x, y);
        this->recalc(x, y);
    }

    int64_t sizeX() const {
        return points.cols();
    }

    int64_t sizeY() const {
        return points.rows();
    }

    cMatrix& getPoints() {
        return points;
    }

    const cMatrix& getPoints() const {
        return points;
    }
};

Mesh2D* createQuadratureMesh(QuadratureFunc xQuad, QuadratureFunc yQuad, const int64_t x, const int64_t y);

}

#endif /* EMPIRICAL_MESH_HPP_ */
