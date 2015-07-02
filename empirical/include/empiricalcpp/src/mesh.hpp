#ifndef EMPIRICALCPP_SRC_MESH_HPP_
#define EMPIRICALCPP_SRC_MESH_HPP_

#include <empiricalcpp/src/constants.hpp>
#include <empiricalcpp/src/quadrature.hpp>
#include <array>
#include <functional>
#include <memory>
#include <tuple>
#include <vector>
#include <boost/multi_array.hpp>

namespace empirical {
    namespace mesh {

        class Mesh2D {
        protected:
            Mesh2D();
        public:
            virtual ~Mesh2D() {}

            typedef boost::multi_array<Scalar, 3> mesh_type;

            mesh_type points;
            std::tuple<std::shared_ptr<Quadrature>, std::shared_ptr<Quadrature>> quadratures;

            Mesh2D(Quadrature* qx, Quadrature* qy);
            Mesh2D(std::shared_ptr<Quadrature>& qx, std::shared_ptr<Quadrature>& qy);
        };

        class QuadratureMesh2D : public Mesh2D {

        };

    }

    typedef mesh::Mesh2D Mesh2D;

    template<std::size_t _Dimension>
    using Mesh = boost::multi_array<Scalar, _Dimension>;

    typedef Mesh<1> Mesh1;
    typedef Mesh<2> Mesh2;
    typedef Mesh<3> Mesh3;

    template<typename _Scalar, std::size_t _Dimension>
    using EvaluationsType = boost::multi_array<_Scalar, _Dimension>;

    template<std::size_t _Dimension>
    using ScalarEvaluation = EvaluationsType<Scalar, _Dimension>;

    template<std::size_t _Dimension>
    using ComplexEvaluation = EvaluationsType<cScalar, _Dimension>;

    typedef ScalarEvaluation<1> ScalarEvaluation1;
    typedef ScalarEvaluation<2> ScalarEvaluation2;
    typedef ScalarEvaluation<3> ScalarEvaluation3;

    typedef ComplexEvaluation<1> ComplexEvaluation1;
    typedef ComplexEvaluation<2> ComplexEvaluation2;
    typedef ComplexEvaluation<3> ComplexEvaluation3;

    namespace Interpolation {
        typedef std::function<Scalar(const Scalar)> scalarFunction1;
        typedef std::function<cScalar(const Scalar)> complexFunction1;
        typedef std::function<Scalar(const Scalar, const Scalar)> scalarFunction2;
        typedef std::function<cScalar(const Scalar, const Scalar)> complexFunction2;
        typedef std::function<Scalar(const Scalar, const Scalar, const Scalar)> scalarFunction3;
        typedef std::function<cScalar(const Scalar, const Scalar, const Scalar)> complexFunction3;

        struct Interpolator {
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

        struct ScalarInterpolator1D : public Interpolator {
            virtual ~ScalarInterpolator1D() {}

            /** Calculates N() test points using the given function for the desired solution, then returns a function to interpolate the rest. */
            virtual scalarFunction1 operator()(scalarFunction1 testFunction) const = 0;
        };

        /** Constructs an interpolator, stoping when either of the given limits has been reached. */
        ScalarInterpolator1D* constructInterpolator(
            const Mesh1 mesh,
            std::vector<ScalarEvaluation1> computedSolutions,
            const size_t maxBasisSize = 50,
            const Scalar correctionScaleBound = epsScalar * 4e10);
    }
}

#endif /* EMPIRICALCPP_SRC_MESH_HPP_ */
