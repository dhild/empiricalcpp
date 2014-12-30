#include "Empirical/domain/Domain2D.hpp"
#include "Empirical/domain/ArcSegment2D.hpp"
#include "Empirical/domain/RadialSegment2D.hpp"
#include "Empirical/domain/ComplexFunctionSegment2D.hpp"
#include "Empirical/quadrature/Quadrature.hpp"

using namespace Eigen;
using namespace Empirical;

DomainSegment2D::DomainSegment2D(Quadrature* quadrature,
                                 const std::function<cScalar(Scalar)>& z,
                                 const std::function<cScalar(Scalar)>& zPrime)
    : base_quadrature(quadrature), z(z), z_prime(zPrime) {
}

DomainSegment2D::~DomainSegment2D() {
  delete base_quadrature;
}

void DomainSegment2D::recalculate(const int M) {
  base_quadrature->resize(M);
  points.resize(M, 1);
  point_primes.resize(M, 1);
  normals.resize(M, 1);
  const QuadratureVector t = base_quadrature->getPoints();

  for (int i = 0; i < M; i++) {
    const Scalar ti = t(i, 0);
    points(i, 0) = z(ti);
    cScalar zp = z_prime(ti);
    point_primes(i, 0) = zp;
    normals(i, 0) = normalFunc(zp);
  }
}

cScalar DomainSegment2D::normalFunc(const cScalar zp) const {
  const Scalar mag = abs(zp);
  return cScalar(imag(zp) / mag, -real(zp) / mag);
}

const Mesh1D& DomainSegment2D::getPoints() const {
  return points;
}

const Mesh1D& DomainSegment2D::getPointDerivatives() const {
  return point_primes;
}

const Mesh1D& DomainSegment2D::getNormals() const {
  return normals;
}

int64_t DomainSegment2D::size() const {
  return base_quadrature->size();
}

const QuadratureVector& DomainSegment2D::getWeights() const {
  return base_quadrature->getWeights();
}

const QuadratureVector& DomainSegment2D::getT() const {
  return base_quadrature->getPoints();
}

void DomainSegment2D::setBoundaryCondition(const BoundaryCondition2D& condition) {
  boundary_condition = &condition;
}
const BoundaryCondition2D& DomainSegment2D::getBoundaryCondition() const {
  return *boundary_condition;
}

ArcSegment2D::ArcSegment2D(const cScalar center, const Scalar R,
                           const Scalar t0, const Scalar t1, const int M)
    : DomainSegment2D(new LegendreGaussLobatto(M),
                      std::bind(&ArcSegment2D::pointsFunc, this,
                                std::placeholders::_1),
                      std::bind(&ArcSegment2D::pointDerivativesFunc, this,
                                std::placeholders::_1)),
      center(center), radius(R), t_scale((t1 - t0) / 2),
      t_offset((t1 + t0) / 2) {
  recalculate(M);
}

ArcSegment2D::~ArcSegment2D() {
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
    : DomainSegment2D(new PeriodicTrapezoidQuadrature(M),
                      std::bind(&RadialSegment2D::pointsFunc, this,
                                std::placeholders::_1),
                      std::bind(&RadialSegment2D::pointDerivativesFunc, this,
                                std::placeholders::_1)),
      radius(radius_func), radius_derivative(radius_derivative_func) {
  recalculate(M);
}

RadialSegment2D::~RadialSegment2D() {
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
    : DomainSegment2D(new LegendreGaussLobatto(M),
                      std::bind(&ComplexFunctionSegment2D::pointsFunc, this,
                                std::placeholders::_1),
                      std::bind(
                          &ComplexFunctionSegment2D::pointDerivativesFunc,
                          this, std::placeholders::_1)),
      offset(offset_val), scale(scale_val),
      z_complex(z_complex_func),
      z_complex_derivative(z_complex_derivative_func) {
  recalculate(M);
}

ComplexFunctionSegment2D::~ComplexFunctionSegment2D() {
}

cScalar ComplexFunctionSegment2D::pointsFunc(const Scalar t) const {
  const cScalar argument = scale * (t + offset);
  return z_complex(argument);
}

cScalar ComplexFunctionSegment2D::pointDerivativesFunc(const Scalar t) const {
  const cScalar argument = scale * (t + offset);
  return z_complex_derivative(argument);
}
