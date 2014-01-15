#ifndef SCATTERING_HPP_
#define SCATTERING_HPP_

#include "Empirical/src/problem/Problem.hpp"

namespace empirical {

    typedef const cScalar (*waveFunction)(const cScalar& z);

    class Scattering : public BVP {
    public:
        virtual ~BVP();

        virtual void setIncidentPlanewave(const Scalar& angle);
        virtual void setIncidentPointSource(const cScalar& point);
        virtual void setIncidentWave(const waveFunction ui, const waveFunction uix, const waveFunction uiy);

    };

}

#endif /* SCATTERING_HPP_ */
