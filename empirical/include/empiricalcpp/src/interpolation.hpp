#ifndef EMPIRICALCPP_SRC_INTERPOLATION_HPP_
#define EMPIRICALCPP_SRC_INTERPOLATION_HPP_

#include <empiricalcpp/src/constants.hpp>
#include <empiricalcpp/src/mesh.hpp>
#include <empiricalcpp/src/quadrature.hpp>
#include <functional>
#include <limits>
#include <vector>

namespace empirical {
    namespace interpolation {

        class Interpolator {
        public:
            virtual ~Interpolator() {}

            /** Returns the number of basis functions that compose this interpolator. */
            virtual size_t N() const = 0;

            /** Returns the L^\infty norm of the interpolator. */
            virtual Scalar getMaximumNorm() const = 0;

            /**
            * The correction scale is the scale of the last basis relative to the first basis.
            * With one basis, this returns 1.
            * With two bases, this returns scale_1 / scale_2.
            */
            virtual Scalar getLastCorrectionScale() const = 0;
        };

        class ScalarInterpolator1D : public Interpolator {
        public:
            typedef const std::vector<Scalar> evaluation_type;
            typedef std::function<Scalar(const Scalar)> interpolation_function;

            /** Calculates the given function for its solution at the exact solution points.
             * Returns a function to interpolate all other solutions.
             */
            virtual interpolation_function operator()(interpolation_function testFunction) const = 0;

            virtual const std::vector<const Scalar>& exactSolutionPoints() const = 0;

            virtual ~ScalarInterpolator1D() {}

            virtual Scalar maxError(evaluation_type& evaluation) const = 0;
            virtual const std::vector<std::weak_ptr<evaluation_type>>& basisEvaluations() const = 0;
            virtual void addBasis(std::shared_ptr<evaluation_type>& basis) = 0;

            static ScalarInterpolator1D* create(const Mesh1D& points);
        };

        /** Constructs an interpolator, stoping when either of the given limits has been reached.
         * An internal copy of the given points and a derived version of the given solutions will be stored internally.
         * Additionally, the evaluations that were used to form the basis will be available from the result.
         */
        template<typename ValueType, typename MeshType, typename InterpolatorType, typename SolutionContainer>
        InterpolatorType* constructInterpolator(const MeshType& points, const SolutionContainer& computedSolutions,
            const size_t maxBasisSize = 50, const ValueType correctionScaleBound = std::numeric_limits<ValueType>::epsilon() * 4e10) {
            InterpolatorType* interp = InterpolatorType::create(points);
            do {
                ValueType maxError = 0;
                SolutionContainer::const_iterator maxSolution = std::cbegin(computedSolutions);
                SolutionContainer::const_iterator it = std::cbegin(computedSolutions);
                while (it != std::cend(computedSolutions)) {
                    ValueType error = interp->maxError(*it);
                    if (error > maxError) {
                        maxError = error;
                        maxSolution = it;
                    }
                }
                if (maxError == 0) {
                    break; // All solutions added; no interpolation available
                }
                std::shared_ptr<evaluation_type> maxEval(*maxSolution);
                interp->addBasis(maxEval);
            } while (maxBasisSize <= interp->N() && correctionScaleBound <= interp->getLastCorrectionScale());
            return interp;
        }

#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
        std::ostream& operator<<(std::ostream& os, const ScalarInterpolator1D& q);
#endif
    }

    typedef interpolation::Interpolator Interpolator;
    typedef interpolation::ScalarInterpolator1D ScalarInterpolator1D;
}

#endif /* EMPIRICALCPP_SRC_INTERPOLATION_HPP_ */
