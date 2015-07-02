#ifndef EMPIRICAL_DOMAIN_HPP_
#define EMPIRICAL_DOMAIN_HPP_

#include <Empirical/Basis.hpp>
#include <Empirical/Boundary.hpp>
#include <Empirical/Mesh.hpp>

namespace Empirical {

struct Domain2D {
    virtual ~Domain2D() {}

    virtual const Boundary2D& getBoundary() const = 0;
    virtual Boundary2D& getBoundary() = 0;

    virtual const Basis2D& getBasis() const = 0;
    virtual Basis2D& getBasis() = 0;

    virtual Scalar getIndexOfRefraction() const = 0;
    virtual void setIndexOfRefraction(Scalar index) = 0;

    virtual bool isDomainInNormalDirection() const = 0;

    /** Exterior domains cover the full infinite plane. */
    virtual bool isExterior() const = 0;

    virtual bool isDomainPoint(const cScalar point) const = 0;

    /** Creates a mesh of points which are interior to the domain.
     * If the point is inside the domain, then it has an x,y value.
     * If the point is outside the domain, then is has a NaN value.
     */
    virtual const Mesh2D* getInteriorPointSample(const Index x_size, const Index y_size) = 0;
};

Domain2D* createInteriorDomain2D(Boundary2D* boundary, Basis2D* basis,
                                 bool domainInNormalDirection = false,
                                 Scalar indexOfRefraction = 1.0);
Domain2D* createExteriorDomain2D(Boundary2D* boundary, Basis2D* basis,
                                 bool domainInNormalDirection = false,
                                 Scalar indexOfRefraction = 1.0);

}

#endif /* EMPIRICAL_DOMAIN_HPP_ */
