#include "Empirical/domain/Domain2D.hpp"
#include "Empirical/basis/Basis2D.hpp"

using namespace Eigen;
using namespace Empirical;

Domain2D::Domain2D(const bool exterior, const Scalar n)
    : is_exterior(exterior), refractive_index(n) {
}

Domain2D::~Domain2D() {
}

void Domain2D::addSegment(const DomainSegment2D* segment) {
    segments.push_back(segment);
}

void Domain2D::addBasis(const Basis2D* basis) {
    bases.push_back(basis);
}

int64_t Domain2D::sizeSegments() const {
    int64_t size = 0;

    auto it = segments.cbegin();
    auto end_it = segments.cend();

    while (it != end_it) {
        size += (*it)->size();
        it++;
    }

    return size;
}

int64_t Domain2D::sizeBases() const {
    int64_t size = 0;

    auto it = bases.cbegin();
    auto end_it = bases.cend();

    while (it != end_it) {
        size += (*it)->size();
        it++;
    }

    return size;
}

Mesh1D Domain2D::getPoints() const {
    Mesh1D mesh(sizeSegments());

    auto it = segments.cbegin();
    auto end_it = segments.cend();

    int64_t i = 0;
    while (it != end_it) {
        mesh.block(i, 0, (*it)->size(), 1) = (*it)->getPoints();

        i += (*it)->size();
        it++;
    }

    return mesh;
}

Mesh1D Domain2D::getPointDerivatives() const {
    Mesh1D mesh(sizeSegments());

    auto it = segments.cbegin();
    auto end_it = segments.cend();

    int64_t i = 0;
    while (it != end_it) {
        mesh.block(i, 0, (*it)->size(), 1) = (*it)->getPointDerivatives();

        i += (*it)->size();
        it++;
    }

    return mesh;
}

Mesh1D Domain2D::getNormals() const {
    Mesh1D mesh(sizeSegments());

    auto it = segments.cbegin();
    auto end_it = segments.cend();

    int64_t i = 0;
    while (it != end_it) {
        mesh.block(i, 0, (*it)->size(), 1) = (*it)->getNormals();

        i += (*it)->size();
        it++;
    }

    return mesh;
}

QuadratureVector Domain2D::getWeights() const {
    QuadratureVector weights(sizeSegments());

    auto it = segments.cbegin();
    auto end_it = segments.cend();

    int64_t i = 0;
    while (it != end_it) {
        weights.block(i, 0, (*it)->size(), 1) = (*it)->getWeights();

        i += (*it)->size();
        it++;
    }

    return weights;
}

const std::vector<const Basis2D*>& Domain2D::getBases() const {
    return bases;
}
