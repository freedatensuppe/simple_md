#ifndef KINETICS_HPP
#define KINETICS_HPP

#include "box.hpp"

class Kinetics
{
   private:
    double _kineticEnergy;

   public:
    void   calculateKineticEnergy(Box& box);
    void   setKineticEnergy(double energy);
    double getKineticEnergy();
};

#endif
