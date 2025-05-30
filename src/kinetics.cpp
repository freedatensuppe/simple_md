#include "kinetics.hpp"

void Kinetics::calculateKineticEnergy(Box& box)
{
    double e_kin_total       = 0.0;
    double e_kin             = 0.0;
    double A_to_m            = 1e-10;
    double u_to_kg           = 1.66053906892e-27;
    double J_to_kcal         = 0.000239006;
    double conversion_factor = A_to_m * A_to_m * u_to_kg * J_to_kcal;

    for (auto& atom : box.getAtoms())
    {
        double mass             = atom->getMass();
        auto   velocity         = atom->getVelocity();
        double velocitySquared  = magnitudeSquared(velocity);
        e_kin                  += mass * velocitySquared / 2;
    }

    e_kin_total = e_kin * conversion_factor;   // kcal
    setKineticEnergy(e_kin_total);
}
void   Kinetics::setKineticEnergy(double energy) { _kineticEnergy = energy; }
double Kinetics::getKineticEnergy() { return _kineticEnergy; }
