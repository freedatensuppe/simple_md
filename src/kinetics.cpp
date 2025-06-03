#include "kinetics.hpp"

#include "conversionFactors.hpp"

void Kinetics::calculateKineticEnergy(Box& box)
{
    double e_kin = 0.0;

    for (auto& atom : box.getAtoms())
    {
        double mass             = atom->getMass();
        auto   velocity         = atom->getVelocity();
        double velocitySquared  = magnitudeSquared(velocity);
        e_kin                  += mass * velocitySquared / 2;
    }

    e_kin *= _E_KIN_FACTOR_;   // kcal/mol
    setKineticEnergy(e_kin);
}
void   Kinetics::setKineticEnergy(double energy) { _kineticEnergy = energy; }
double Kinetics::getKineticEnergy() { return _kineticEnergy; }
