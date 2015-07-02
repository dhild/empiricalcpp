#ifndef EMPIRICAL_PROBLEM_HPP_
#define EMPIRICAL_PROBLEM_HPP_

#include <Empirical/Domain.hpp>
#include <Empirical/Basis.hpp>

namespace Empirical {

struct Solution2D {
    virtual ~Solution2D() {}

    virtual cScalar operator()(const cScalar point) const = 0;
    virtual cVector operator()(const cVector& points) const = 0;
    virtual cMatrix operator()(const cMatrix& points) const = 0;
};

struct BoundaryValueProblem2D {
    virtual ~BoundaryValueProblem2D() {}

    virtual void addDomain(Domain2D* domain) = 0;

    virtual const Solution2D& solve() = 0;

    virtual Scalar conditionNumber() const = 0;
    virtual Scalar residualNorm() const = 0;

    virtual const Solution2D& getSolution() const = 0;
};

typedef const cScalar(*WaveFunction)(const cScalar& z);

struct ScatteringProblem2D : public BoundaryValueProblem2D {
    virtual ~ScatteringProblem2D() {}

    virtual void setIncidentPlanewave(const Scalar& angle) = 0;
    virtual void setIncidentPointSource(const cScalar& point) = 0;
    virtual void setIncidentWave(const WaveFunction ui, const WaveFunction uix, const WaveFunction uiy) = 0;
};

ScatteringProblem2D* createScatteringProblem2D();

}

#endif  /* EMPIRICAL_PROBLEM_HPP_ */
