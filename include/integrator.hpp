#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include "box.hpp"

class Integrator
{
   private:
   public:
    void integrateVelocities(Atom *atom);
    void updatePosition(Atom *atom);
    void firstStep(Box &box);
    void secondStep(Box &box);
};

#endif
