#ifndef EMPIRICAL_DOMAIN_HPP_
#define EMPIRICAL_DOMAIN_HPP_

#include <Empirical/Basis.hpp>
#include <Empirical/Boundary.hpp>
#include <Empirical/Mesh.hpp>

namespace Empirical {

class Domain2D {
protected:
    Boundary2D* boundary;
    Basis2D* basis;
    const bool domainInNormalDirection;
    Scalar indexOfRefraction;

    Domain2D(Boundary2D* bnd, Basis2D* bas, const bool normalDir, const Scalar index)
        : boundary(bnd), basis(bas), domainInNormalDirection(normalDir), indexOfRefraction(index) {}
public:
    virtual ~Domain2D() {}

    virtual const Boundary2D& getBoundary() const {
        return *boundary;
    }

    virtual Boundary2D& getBoundary() {
        return *boundary;
    }

    virtual const Basis2D& getBasis() const {
        return *basis;
    }

    virtual Basis2D& getBasis() {
        return *basis;
    }

    Scalar getIndexOfRefraction() const {
        return indexOfRefraction;
    }

    void setIndexOfRefraction(Scalar index) {
        indexOfRefraction = index;
    }

    bool isDomainInNormalDirection() const {
        return domainInNormalDirection;
    }

    /** Exterior domains cover the full infinite plane. */
    virtual bool isExterior() const = 0;

    virtual bool isDomainPoint(const cScalar point) const = 0;

    /** Creates a mesh of points which are interior to the domain.
     * If the point is inside the domain, then it has an x,y value.
     * If the point is outside the domain, then is has a NaN value.
     */
    virtual const Mesh2D* getInteriorPointSample(const int64_t x_size, const int64_t y_size) = 0;
};

Domain2D* createInteriorDomain2D(Boundary2D* boundary, Basis2D* basis,
                                 bool domainInNormalDirection = false,
                                 Scalar indexOfRefraction = 1.0);
Domain2D* createExteriorDomain2D(Boundary2D* boundary, Basis2D* basis,
                                 bool domainInNormalDirection = false,
                                 Scalar indexOfRefraction = 1.0);

}

#endif /* EMPIRICAL_DOMAIN_HPP_ */
