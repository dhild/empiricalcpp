#include "BaseBoundaryValueProblem2D.hpp"
#include <Eigen/Dense>
#include <cmath>
#include <functional>

using namespace Empirical;
using namespace Eigen;
using namespace std;

BoundaryValueSolution2D::BoundaryValueSolution2D(const cVector& coeffs, const std::vector<Domain2D*>& dom)
: coefficients(coeffs), domains(dom) {}

BoundaryValueSolution2D::~BoundaryValueSolution2D() {}

namespace {

function<cScalar(const cScalar)> evaluator(const std::vector<Domain2D*>& domains) {
    return [domains](const cScalar point) {
        cScalar solution = 0;
        for (const Domain2D* dom : domains) {
            const Basis2D& basis = dom->getBasis();
            const Scalar k = 1.0 / dom->getIndexOfRefraction();
            const cVector values = basis(k, point);
            solution += values.sum();
        }
        return solution;
    };
}

}

cScalar BoundaryValueSolution2D::operator()(const cScalar point) const {
    return evaluator(domains)(point);
}

cVector BoundaryValueSolution2D::operator()(const cVector& points) const {
    return points.unaryExpr(evaluator(domains));
}

cMatrix BoundaryValueSolution2D::operator()(const cMatrix& points) const {
    return points.unaryExpr(evaluator(domains));
}

BaseBoundaryValueProblem2D::BaseBoundaryValueProblem2D()
    : solution(nullptr), A(nullptr), rhs(nullptr), sqrtQuadratureWeights(nullptr) {}

BaseBoundaryValueProblem2D::~BaseBoundaryValueProblem2D() {
    delete solution;
    delete A;
    delete rhs;
    delete sqrtQuadratureWeights;
}

void BaseBoundaryValueProblem2D::fillBCMatrix() {
    if (A) {
        delete A;
        A = nullptr;
    }
}

void BaseBoundaryValueProblem2D::fillQuadratureWeights() {
    if (sqrtQuadratureWeights) {
        delete sqrtQuadratureWeights;
        sqrtQuadratureWeights = nullptr;
    }
}

void BaseBoundaryValueProblem2D::addDomain(Domain2D* domain) {
    domains.push_back(domain);
}

const BoundaryValueSolution2D& BaseBoundaryValueProblem2D::solve() {
    fillQuadratureWeights();
    fillBCMatrix();
    fillRHS();
    JacobiSVD<cMatrix> decomp = A->jacobiSvd(ComputeFullU | ComputeFullV);

    cVector result = decomp.solve(rhs->matrix());

    if (solution) {
        delete solution;
        solution = nullptr;
    }
    solution = new BoundaryValueSolution2D(result, domains);
    return *solution;
}

Scalar BaseBoundaryValueProblem2D::conditionNumber() const {
    return Scalar(nanl(""));
}

Scalar BaseBoundaryValueProblem2D::residualNorm() const {
    return solution->coefficients.norm();
}

const BoundaryValueSolution2D& BaseBoundaryValueProblem2D::getSolution() const {
    return *solution;
}
