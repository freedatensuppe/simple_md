#ifndef POTENTIAL_HPP
#define POTENTIAL_HPP

#include "box.hpp"
#include "linkedCellList.hpp"

class Potential
{
   private:
    double _potentialEnergy;
    double _c6;
    double _c12;

    double _LJCutoff;
    double _LJEnergyCutoff;
    double _LJForceCutoff;

   public:
    void calculateEnergyForcesLJ(Box& box);

    void calculateEnergyForcesLJCellList(
        Box&                   box,
        std::vector<AtomPair>& atomPairs
    );

    //    void calculateForcesLJ(Box &box);

    void setLJCutoff(double sigma);
    void setljEnergyCutoff(std::vector<double> dimensions);
    void setljForceCutoff(double ljForceCutoff);

    double getLJCutoff();

    double getPotentialEnergy();
};

#endif
