#ifndef EMPIRICAL_BASIS_H
#define EMPIRICAL_BASIS_H

#include <Eigen/Dense>

namespace empirical {
  
  class Basis {
  protected:
    unsigned long N;
    bool realOnly;

    Eigen::ArrayXXd q;

    Basis(const unsigned long N, const bool realOnly);
    Basis(const Basis& b);

    virtual updateQ() = 0;

  public:
    virtual ~Basis() = 0;

    unsigned long getN() const { return N; }
    bool isRealOnly() const { return realOnly; }

    void updateN(const unsigned long N) {
      this->N = N;
      updateQ();
    }
  }

  class MFSBasis : public Basis {
  public:
    MFSBasis(const unsigned long N
  }

}

#endif // EMPIRICAL_BASIS_H
