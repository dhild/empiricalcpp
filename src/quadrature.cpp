#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "quadrature.h"

using namespace quadrature;

Quadrature::Quadrature(IntegerType length) : length(length) {
  allocate();
}

Quadrature::~Quadrature() {
  deallocate();
}

void Quadrature::update(IntegerType length) {
  deallocate();
  allocate();
}

void Quadrature::allocate() {
  this->nodes = (ScalarType*) malloc(length * sizeof(ScalarType));
  this->weights = (ScalarType*) malloc(length * sizeof(ScalarType));
}

void Quadrature::deallocate() {
  free(this->nodes);
  free(this->weights);
}

Linear::Linear(IntegerType length) : Quadrature(length) {}
