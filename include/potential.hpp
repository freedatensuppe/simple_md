#ifndef INPUT_HPP
#define INPUT_HPP

#include "box.hpp"

class Potential
{
   private:
    double _totalEnergy;
    double _c6;
    double _c12;

    double _LJCutoff;
    double _LJEnergyCutoff;
    double _LJForceCutoff;

   public:
    void calculateEnergyLJ(Box &box, double ljEnergyCutoff);
    void calculateForcesLJ(Box &box, double ljForceCutoff);

    void setLJCutoff(std::vector<double> dimensions);
    void setljEnergyCutoff(std::vector<double> dimensions);
    void setljForceCutoff(double ljForceCutoff);
};

#endif
