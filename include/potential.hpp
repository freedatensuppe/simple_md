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
    //    void calculateEnergyForcesLJ(Box& box);
    void calculateEnergyForcesLJCellList(
        Box&                   box,
        std::vector<AtomPair>& atomPairs
    );

    void setc6(double epsilon, double sigma);
    void setc12(double epsilon, double sigma);
    void setLJCutoff(double sigma);

    double getc6();
    double getc12();
    double getLJCutoff();
    double getPotentialEnergy();
};

#endif
