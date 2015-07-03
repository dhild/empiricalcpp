#include <empiricalcpp/src/interpolation.hpp>

using namespace empirical::interpolation;

namespace {
}

std::shared_ptr<ScalarInterpolator1D> empirical::interpolation::constructInterpolator(
    const Mesh1D&, const Mesh1D&,
    boost::const_multi_array_ref<Scalar, 2>,
    const size_t,
    const Scalar) {
    return std::shared_ptr<ScalarInterpolator1D>(nullptr);
}
