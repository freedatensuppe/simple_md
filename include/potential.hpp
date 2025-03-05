#ifndef INPUT_HPP
#define INPUT_HPP

#include "box.hpp"

class Potential
{
   private:
    double _energy;

   public:
    void calculate_energy_LJ(Box &box);
    void calculate_forces_LJ(Box &box);
};

#endif
