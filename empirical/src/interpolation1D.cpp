#include <empiricalcpp/src/interpolation.hpp>
#include <Eigen/Dense>

using empirical::Scalar;
using empirical::Mesh1D;
using namespace empirical::interpolation;

namespace {
    class EigenBasedScalarInterpolator1D : public ScalarInterpolator1D {

        std::vector<const Scalar> solutionPoints;
        std::vector<std::weak_ptr<evaluation_type>> originalBasisFunctions;

    public:
        EigenBasedScalarInterpolator1D(const Mesh1D&) {

        }

        virtual ~EigenBasedScalarInterpolator1D() {}

        void addBasis(evaluation_type&) {

        }

        virtual size_t N() const {
            return solutionPoints.size();
        }

        virtual Scalar getMaximumNorm() const {
            return std::numeric_limits<Scalar>::infinity();
        }

        virtual Scalar getLastCorrectionScale() const {
            return std::numeric_limits<Scalar>::infinity();
        }

        virtual interpolation_function operator()(interpolation_function testFunction) const {
            return testFunction;
        }

        virtual const std::vector<const Scalar>& exactSolutionPoints() const {
            return solutionPoints;
        }

        virtual const std::vector<std::weak_ptr<evaluation_type>>& basisEvaluations() const {
            return originalBasisFunctions;
        }

        virtual Scalar maxError(evaluation_type&) const {
            return std::numeric_limits<Scalar>::infinity();
        }

        virtual void addBasis(std::shared_ptr<evaluation_type>&) {

        }
    };
}

namespace empirical {
    namespace interpolation {

        ScalarInterpolator1D* ScalarInterpolator1D::create(const Mesh1D& points) {
            return new EigenBasedScalarInterpolator1D(points);
        }

#ifndef EMPIRICAL_NO_OSTREAM_DEFINITIONS
        std::ostream& operator<<(std::ostream& os, const ScalarInterpolator1D& interp) {
            os << "ScalarInterpolator1D {";
            os << std::fixed << std::setw(11) << std::setprecision(6);
            os << " N: " << interp.N() << ", ";
            os << " correctionScale: " << interp.getLastCorrectionScale() << ", ";
            os << " maximumNorm: " << interp.getMaximumNorm();
            return os << "}";
        }
#endif
    }
}

