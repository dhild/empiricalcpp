/*#include "test.h"
#include <Empirical/Basis>
#include <Empirical/Domain>

using namespace empirical;

namespace basis_test {

cScalar complexFunc(const cScalar t) {
  return exp(t);
}

cScalar complexDerivFunc(const cScalar t) {
  return cScalar(0, PI) * exp(t);
}

const int M = 15;
const int N = 10;

SUITE(MFSBasis2D_tests) {
  TEST(size) {
    ComplexFunctionSegment2D segment(complexFunc, complexDerivFunc,
                                     M, 1, cScalar(0, PI));
    MFSBasis2D basis(segment.getPoints());

    CHECK(basis.size() == M);
  }
  TEST(basis_is_mfsBasis_0) {
    ComplexFunctionSegment2D segment(complexFunc, complexDerivFunc,
                                     M, 1, cScalar(0, PI));
    MFSBasis2D basis(segment.getPoints());

    const cScalar x = cScalar(0.5, 0.75);
    const cScalar z = cScalar(-0.2, 3);
    cScalar expected = mfsBasis(0, abs(x - z));
    cScalar actual = basis.basis(0, x, z);
    CHECK_CLOSE(real(expected), real(actual), epsScalar);
    CHECK_CLOSE(imag(expected), imag(actual), epsScalar);
  }
  TEST(basis_is_mfsBasis_3) {
    ComplexFunctionSegment2D segment(complexFunc, complexDerivFunc,
                                     M, 1, cScalar(0, PI));
    MFSBasis2D basis(segment.getPoints());

    const cScalar x = cScalar(0.5, 0.75);
    const cScalar z = cScalar(-0.2, 3);
    cScalar expected = mfsBasis(3, abs(x - z));
    cScalar actual = basis.basis(3, x, z);
    CHECK_CLOSE(real(expected), real(actual), epsScalar);
    CHECK_CLOSE(imag(expected), imag(actual), epsScalar);
  }
  TEST(basis_Mesh1D_size) {
    ComplexFunctionSegment2D segment(complexFunc, complexDerivFunc,
                                     M, 1, cScalar(0, PI));
    MFSBasis2D basis(segment.getPoints());

    Mesh1D actual = basis.basis(0, cScalar(0.2, -0.1));
    CHECK(actual.rows() == basis.size());
  }
  TEST(basis_Mesh2D_size) {
    ComplexFunctionSegment2D segment(complexFunc, complexDerivFunc,
                                     M, 1, cScalar(0, PI));
    MFSBasis2D basis(segment.getPoints());
    ComplexFunctionSegment2D mesh(complexFunc, complexDerivFunc,
                                  N, 3, cScalar(0, PI));

    Mesh2D actual = basis.basis(0, mesh.getPoints());
    CHECK(actual.rows() == mesh.size());
    CHECK(actual.cols() == basis.size());
  }
}

} // namespace basis_test
*/
