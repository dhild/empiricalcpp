#include <empiricalcpp/src/interpolation.hpp>

using namespace Empirical;
using namespace Empirical::Interpolation;

namespace {
}

ScalarInterpolator1D* Empirical::Interpolation::constructInterpolator(
    const Mesh1 mesh,
    std::vector<ScalarEvaluation1> computedSolutions,
    const size_t,
    const Scalar) {
    return nullptr;
}
