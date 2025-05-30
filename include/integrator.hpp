#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include "box.hpp"

class Integrator
{
   private:
    double _timestep;

   public:
    void integrateVelocities(Atom *atom);
    void integratePositions(Atom *atom, Box &box);
    void firstStep(Box &box);
    void secondStep(Box &box);

    void setTimestep(double timestep);

    double getTimestep();
};

#endif
