#include "thermostat.hpp"

#include <cmath>

#include "vector3d.hpp"

void Thermostat::calculateTemperature(Box& box)
{
    double k_B               = 1.380649e-23;   // J/K
    double momentum          = 0.0;
    double A_to_m            = 1e-10;
    double u_to_kg           = 1.66053906892e-27;
    double conversion_factor = A_to_m * A_to_m * u_to_kg / k_B;

    for (auto& atom : box.getAtoms())
    {
        double mass             = atom->getMass();       // u to kg
        auto   velocity         = atom->getVelocity();   // A/s to m/s
        double velocitySquared  = magnitudeSquared(velocity);
        momentum               += mass * velocitySquared;
    }

    _temperature = momentum * conversion_factor / (3 * box.getAtoms().size());
    box.setTemperature(_temperature);
}

void Thermostat::applyThermostat(Box& box)
{
    auto dt        = 2.0;
    auto tempRatio = _targetTemperature / _temperature;

    auto tFactor = std::sqrt(1.0 - (dt / _tau) * (1.0 - tempRatio));

    for (const auto& atom : box.getAtoms()) atom->scaleVelocity(tFactor);
}

double Thermostat::getTemperature() { return _temperature; }
