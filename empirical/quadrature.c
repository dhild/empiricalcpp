#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "quadrature.h"

using namespace quadrature;

Quadrature::Quadrature(long length) : length(length) {
    this->nodes = malloc(length * sizeof(double_t));
}
