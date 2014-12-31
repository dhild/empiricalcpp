#include "Empirical/problem/ArcSegment2D.hpp"
#include "Empirical/problem/RadialSegment2D.hpp"
#include "Empirical/problem/ComplexFunctionSegment2D.hpp"

using namespace Eigen;
using namespace Empirical;

BoundarySegment2D::~BoundarySegment2D() {}

void BoundarySegment2D::recalculate(const int64_t M) {
    points.resize(M, 1);
    point_primes.resize(M, 1);
    normals.resize(M, 1);
    const Vector t = getQuadraturePoints();

    for (int i = 0; i < M; i++) {
        const Scalar ti = t(i, 0);
        points(i, 0) = z(ti);
        cScalar zp = zPrime(ti);
        point_primes(i, 0) = zp;
        normals(i, 0) = normalFunc(zp);
    }
}

cScalar BoundarySegment2D::normalFunc(const cScalar zp) const {
    const Scalar mag = abs(zp);
    return cScalar(imag(zp) / mag, -real(zp) / mag);
}

ArcSegment2D::ArcSegment2D(const cScalar center, const Scalar R,
                           const Scalar t0, const Scalar t1, const int M)
    : BoundarySegment2D(
          std::bind(&ArcSegment2D::pointsFunc, this, std::placeholders::_1),
          std::bind(&ArcSegment2D::pointDerivativesFunc, this, std::placeholders::_1)),
      quadrature(createLGL(M)),
      center(center), radius(R), t_scale((t1 - t0) / 2),
      t_offset((t1 + t0) / 2) {
    recalculate(M);
}

ArcSegment2D::~ArcSegment2D() {
    delete quadrature;
}

void ArcSegment2D::recalculate(const int64_t M) {
    quadrature->resize(M);
    BoundarySegment2D::recalculate(M);
}

cScalar ArcSegment2D::pointsFunc(const Scalar t) const {
    cScalar e = exp(cScalar(0, (t * t_scale) + t_offset));
    return center + radius * e;
}

cScalar ArcSegment2D::pointDerivativesFunc(const Scalar t) const {
    cScalar e = exp(cScalar(0, (t * t_scale) + t_offset));
    return cScalar(0, radius * t_scale) * e;
}

RadialSegment2D::RadialSegment2D(
    const std::function<cScalar(const Scalar)>& radius_func,
    const std::function<cScalar(const Scalar)>& radius_derivative_func,
    const int M)
    : BoundarySegment2D(
    std::bind(&RadialSegment2D::pointsFunc, this, std::placeholders::_1),
    std::bind(&RadialSegment2D::pointDerivativesFunc, this, std::placeholders::_1)),
    quadrature(createPeriodicTrapezoid(M)),
    radius(radius_func), radius_derivative(radius_derivative_func) {
    recalculate(M);
}

RadialSegment2D::~RadialSegment2D() {
    delete quadrature;
}

cScalar RadialSegment2D::pointsFunc(const Scalar t) const {
    const Scalar angle = PI * t;
    return radius(angle) * exp(cScalar(0, angle));
}

cScalar RadialSegment2D::pointDerivativesFunc(const Scalar t) const {
    const Scalar angle = PI * t;
    const cScalar e = exp(cScalar(0, angle));
    const cScalar r = radius(angle);
    const cScalar rp = radius_derivative(angle);
    return PI * ((cScalar(0, 1) * r * e) + (rp * e));
}

ComplexFunctionSegment2D::ComplexFunctionSegment2D(
    const std::function<cScalar(cScalar)>& z_complex_func,
    const std::function<cScalar(cScalar)>& z_complex_derivative_func,
    const int M, const cScalar offset_val, const cScalar scale_val)
    : BoundarySegment2D(
    std::bind(&ComplexFunctionSegment2D::pointsFunc, this, std::placeholders::_1),
    std::bind(&ComplexFunctionSegment2D::pointDerivativesFunc, this, std::placeholders::_1)),
    quadrature(createLGL(M)),
    offset(offset_val), scale(scale_val),
    z_complex(z_complex_func),
    z_complex_derivative(z_complex_derivative_func) {
    recalculate(M);
}

ComplexFunctionSegment2D::~ComplexFunctionSegment2D() {
    delete quadrature;
}

cScalar ComplexFunctionSegment2D::pointsFunc(const Scalar t) const {
    const cScalar argument = scale * (t + offset);
    return z_complex(argument);
}

cScalar ComplexFunctionSegment2D::pointDerivativesFunc(const Scalar t) const {
    const cScalar argument = scale * (t + offset);
    return z_complex_derivative(argument);
}
