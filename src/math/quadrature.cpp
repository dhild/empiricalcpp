#include <cstdlib>
#include "quadrature.h"

using namespace empirical;

Quadrature::Quadrature(IntegerType length, ScalarType a, ScalarType b) : length(length), a(a), b(b) {
  allocate();
}

Quadrature::~Quadrature() {
  deallocate();
}

void Quadrature::update(const IntegerType length) {
  this->update(length, this->a, this->b);
}

void Quadrature::update(const ScalarType a, const ScalarType b) {
  this->update(this->length, a, b);
}

void Quadrature::update(const IntegerType length, const ScalarType a, const ScalarType b) {
  this->length = length;
  this->a = a;
  this->b = b;
  deallocate();
  allocate();
  recalc();
}

void Quadrature::allocate() {
  this->nodes = new ScalarType[length];
  this->weights = new ScalarType[length];
}

void Quadrature::deallocate() {
  delete this->nodes;
  delete this->weights;
}

ScalarType Quadrature::integrate(const FunctionType f) {
  ScalarType sum = 0;

  for (int i = 0; i < this->length; i++) {
    sum += f(this->nodes[i]) * this->weights[i];
  }

  return sum;
}

Linear::Linear(const IntegerType length, const ScalarType a, const ScalarType b) : Quadrature(length, a, b) {
  recalc();
}

void Linear::recalc() {
  const ScalarType delta = (b - a) / (length - 1);

  for (int i = 0; i < this->length; i++) {
    this->nodes[i] = a + i * delta;
    this->weights[i] = delta;
  }
}
