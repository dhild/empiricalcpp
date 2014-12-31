#include "Empirical/problem/BoundaryValueProblem2D.hpp"
#include "Problem2D.hpp"
#include <cstddef>
#include <limits>
#include <vector>
#include <functional>

using namespace Empirical;
using namespace Eigen;

BoundaryValueSolution2D::BoundaryValueSolution2D(const int N)
    : components(N) {}

BoundaryValueSolution2D::~BoundaryValueSolution2D() {}

cScalar componentFunction(const cScalar coeff,
                          const std::function<cScalar(const cScalar)>& func,
                          const cScalar point) {
    return coeff * func(point);
}

void BoundaryValueSolution2D::addBasis(
    const std::function<cScalar(const cScalar)>& basis,
    const cScalar coefficient) {
    auto func = std::bind(componentFunction, coefficient, basis,
                          std::placeholders::_1);
    components.emplace_back(basis);
}

cScalar BoundaryValueSolution2D::operator()(const cScalar point) const {
    cScalar sum = 0;
    auto it = components.begin();
    auto end = components.end();
    while (it != end) {
        sum += (*it)(point);
        it++;
    }
    return sum;
}

Mesh1D BoundaryValueSolution2D::operator()(const Mesh1D& points) const {
    Mesh1D sum = Mesh1D::Zero(points.rows());

    auto it = components.begin();
    auto end = components.end();
    while (it != end) {
        sum += points.unaryExpr(*it);
        it++;
    }

    return sum;
}

Mesh2D BoundaryValueSolution2D::operator()(const Mesh2D& points) const {
    Mesh2D sum = Mesh2D::Zero(points.rows(), points.cols());

    auto it = components.begin();
    auto end = components.end();
    while (it != end) {
        sum += points.unaryExpr(*it);
        it++;
    }

    return sum;
}

BoundaryValueProblem2D::BoundaryValueProblem2D()
    : solution(NULL) {}

BoundaryValueProblem2D::~BoundaryValueProblem2D() {
    delete solution;
}

void BoundaryValueProblem2D::addDomain(Domain2D* domain) {
    domains.push_back(domain);
}

const Solution2D& BoundaryValueProblem2D::solve() {
    throw new std::runtime_error("Not implemented yet");
}

const Solution2D& BoundaryValueProblem2D::getSolution() const {
    return *solution;
}

Scalar BoundaryValueProblem2D::conditionNumber() const {
    if (solution == NULL) {
        return std::numeric_limits<Scalar>::quiet_NaN();
    }
    return std::numeric_limits<Scalar>::quiet_NaN();
}

Scalar BoundaryValueProblem2D::residualNorm() const {
    if (solution == NULL) {
        return std::numeric_limits<Scalar>::quiet_NaN();
    }
    return solution_coeficients.norm();
}
