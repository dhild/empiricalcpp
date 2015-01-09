#ifndef EMPIRICAL_SRC_MESH_QUADRATURE_MESH_HPP_
#define EMPIRICAL_SRC_MESH_QUADRATURE_MESH_HPP_

#include <Empirical/Mesh.hpp>

namespace Empirical {

class QuadratureMesh : public Mesh {
protected:
    Quadrature* x;
    Quadrature* y;
public:
    QuadratureMesh(QuadratureFunc xQuad, QuadratureFunc yQuad, const int64_t x, const int64_t y);
    virtual ~QuadratureMesh();
    virtual void recalc(const int64_t x, const int64_t y);
};

}

#endif /* EMPIRICAL_SRC_MESH_QUADRATURE_MESH_HPP_ */