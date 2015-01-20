#ifndef EMPIRICAL_SRC_PROBLEM_BASE_BOUNDARY_VALUE_PROBLEM_2D_HPP_
#define EMPIRICAL_SRC_PROBLEM_BASE_BOUNDARY_VALUE_PROBLEM_2D_HPP_

#include <Empirical/Problem.hpp>
#include <vector>

namespace Empirical {

class BaseBoundaryValueProblem2D;

class BoundaryValueSolution2D : public Solution2D {
    friend class BaseBoundaryValueProblem2D;
    const cVector coefficients;
    const std::vector<Domain2D*> domains;
public:
    BoundaryValueSolution2D(const cVector& coeffs, const std::vector<Domain2D*>& domains);

    BoundaryValueSolution2D(const BoundaryValueSolution2D&) = delete;
    BoundaryValueSolution2D& operator=(const BoundaryValueSolution2D&) = delete;

    virtual ~BoundaryValueSolution2D();

    virtual cScalar operator()(const cScalar point) const;
    virtual cVector operator()(const cVector& points) const;
    virtual cMatrix operator()(const cMatrix& points) const;
};

class BaseBoundaryValueProblem2D : public BoundaryValueProblem2D {
protected:
    friend class BoundaryValueSolution2D;

    std::vector<Domain2D*> domains;

    cMatrix* A;
    cVector* rhs;
    Vector* sqrtQuadratureWeights;
    BoundaryValueSolution2D* solution;

    virtual void fillRHS() = 0;
    virtual void fillQuadratureWeights();
    virtual void fillBCMatrix();
public:
    BaseBoundaryValueProblem2D();
    virtual ~BaseBoundaryValueProblem2D();

    BaseBoundaryValueProblem2D(const BaseBoundaryValueProblem2D&) = delete;
    BaseBoundaryValueProblem2D& operator=(const BaseBoundaryValueProblem2D&) = delete;

    virtual void addDomain(Domain2D* domain);

    virtual const BoundaryValueSolution2D& solve();

    virtual Scalar conditionNumber() const;
    virtual Scalar residualNorm() const;

    virtual const BoundaryValueSolution2D& getSolution() const;
};

}

#endif /* EMPIRICAL_SRC_PROBLEM_BASE_BOUNDARY_VALUE_PROBLEM_2D_HPP_ */
