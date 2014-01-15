#include "Empirical/src/problem/Scattering.hpp"

using namespace empirical;

void Problem::~Problem() {}

void Problem::fillQuadratureWeights() {

}

void Problem::fillRHS() {

}

void Problem::setupBasisDofs() {

}

void Problem::fillBCMatrix() {

}

void Problem::linsolve(const Parameters& parameters) {

}

void Problem::solve(const Parameters& parameters) {

}

void BVP::fillQuadratureWeights() {

}

void BVP::setupBasisDofs() {

}

void BVP::fillBCMatrix() {

}

BVP::~BVP() {
}

const Scalar BVP::bcResidualNorm() const {

}
