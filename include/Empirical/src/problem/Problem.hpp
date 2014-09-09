#ifndef EMPIRICAL_PROBLEM_PROBLEM_HPP_
#define EMPIRICAL_PROBLEM_PROBLEM_HPP_

#include <tuple>
#include <vector>
#include <boost/any.hpp>
#include "Empirical/src/quadrature/Quadrature.hpp"

namespace empirical {

    typedef std::tuple<boost::any> Parameters;

    class Problem2D {
    protected:

        std::vector<Domain2D&> domains;
        Scalar overallWavenumber;

        Eigen::Matrix<cScalar, Eigen::Dynamic, Eigen::Dynamic> A;

        virtual void fillQuadratureWeights();
        virtual void fillRHS();
        virtual void setupBasisDofs();
        virtual makeBCMatrix();
        virtual void linsolve(const Parameters& parameters);

        virtual Vector2D getPoints() const;
        virtual Vector2D getNormals() const;
        virtual Vector2D getWeights() const;

    public:

        virtual ~Problem2D();

        virtual void solve(const Parameters& parameters);

        const int getM() const;
        const int getN() const;
        const Scalar getOverallWavenumber() const {
            return this->overallWavenumber;
        }

        /** Calculates the solution at the given point.
         *
         * Solution points must lie in the exterior of all domains for this problem.
         */
        virtual cScalar operator()(const cScalar& point) const;

        /** Calculates the solution at the given set of points.
         *
         * Solution points must lie in the exterior of all domains for this problem.
         */
        virtual Vector2D operator()(const Vector2D& points) const;

        /** Calculates the solution at the given set of points.
         *
         * Solution points must lie in the exterior of all domains for this problem.
         */
        virtual Mesh2D operator()(const Mesh2D& points) const;

    };

}

#endif /* EMPIRICAL_PROBLEM_PROBLEM_HPP_ */
