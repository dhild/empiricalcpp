#ifndef EMPIRICAL_SRC_DOMAIN_BASE_DOMAIN_2D_HPP_
#define EMPIRICAL_SRC_DOMAIN_BASE_DOMAIN_2D_HPP_

#include <Empirical/Domain.hpp>

namespace Empirical {

class BaseDomain2D : public Domain2D {
protected:
    Boundary2D* boundary;
    Basis2D* basis;
    const bool domainInNormalDirection;
    Scalar indexOfRefraction;

    BaseDomain2D(Boundary2D* bnd, Basis2D* bas, const bool normalDir, const Scalar index)
        : boundary(bnd), basis(bas), domainInNormalDirection(normalDir), indexOfRefraction(index) {}
public:
    virtual ~BaseDomain2D() {}

    BaseDomain2D(const BaseDomain2D&) = delete;
    BaseDomain2D& operator=(const BaseDomain2D&) = delete;

    virtual const Boundary2D& getBoundary() const;
    virtual Boundary2D& getBoundary();

    virtual const Basis2D& getBasis() const;
    virtual Basis2D& getBasis();

    virtual Scalar getIndexOfRefraction() const;
    virtual void setIndexOfRefraction(Scalar index);

    virtual bool isDomainInNormalDirection() const;

    /** Exterior domains cover the full infinite plane. */
    virtual bool isExterior() const = 0;

    virtual bool isDomainPoint(const cScalar point) const = 0;

    /** Creates a mesh of points which are interior to the domain.
    * If the point is inside the domain, then it has an x,y value.
    * If the point is outside the domain, then is has a NaN value.
    */
    virtual const Mesh2D* getInteriorPointSample(const int64_t x_size, const int64_t y_size) = 0;
};

}

#endif /* EMPIRICAL_SRC_DOMAIN_BASE_DOMAIN_2D_HPP_ */
