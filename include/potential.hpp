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

    double _VCut;
    double _FCut;

    double _LJCutoff;
    double _LJEnergyCutoff;
    double _LJForceCutoff;

    double _epsilon;
    double _sigma;

   public:
    //    void calculateEnergyForcesLJ(Box& box);
    void calculateEnergyForcesLJCellList(
        Box&                   box,
        std::vector<AtomPair>& atomPairs
    );
    void resetForces(Box& box);

    void setEpsilon(double epsilon);
    void setSigma(double sigma);

    void setc6(double epsilon, double sigma);
    void setc12(double epsilon, double sigma);

    void setVCut();
    void setFCut();

    void setLJCutoff(double sigma);

    double getEpsilon();
    double getSigma();
    double getc6();
    double getc12();
    double getLJCutoff();
    double getPotentialEnergy();
};

#endif
