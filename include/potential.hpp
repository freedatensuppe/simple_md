#ifndef POTENTIAL_HPP
#define POTENTIAL_HPP

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
    void calculateEnergyForcesLJ(Box &box);
    //    void calculateForcesLJ(Box &box);

    void setLJCutoff(std::vector<double> dimensions);
    void setljEnergyCutoff(std::vector<double> dimensions);
    void setljForceCutoff(double ljForceCutoff);

    double getLJCutoff() { return _LJCutoff; }
};

#endif
