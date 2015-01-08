#include "Empirical/Mesh.hpp"
#include "Empirical/mesh/Quadrature.hpp"

using namespace Empirical;
using namespace Eigen;
using namespace std;

Mesh* Empirical::createQuadratureMesh(QuadratureFunc xQuad, QuadratureFunc yQuad, const int64_t x, const int64_t y) {
    QuadratureMesh* mesh = new QuadratureMesh(xQuad, yQuad, x, y);
    mesh->recalc(x, y);
    return mesh;
}

QuadratureMesh::QuadratureMesh(QuadratureFunc xQuad, QuadratureFunc yQuad, const int64_t X, const int64_t Y)
    : Mesh(X, Y), x(xQuad(X)), y(yQuad(Y)) {}

void QuadratureMesh::recalc(const int64_t X, const int64_t Y) {
    x->resize(X);
    y->resize(Y);

    Vector xpts = x->getPoints();
    Vector ypts = y->getPoints();

    for (int64_t i = 0; i < X; i++) {
        for (int64_t j = 0; j < Y; j++) {
            points(i, j) = cScalar(xpts(i), ypts(j));
        }
    }
}

QuadratureMesh::~QuadratureMesh() {
    delete x;
    delete y;
}

