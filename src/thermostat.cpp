#include "thermostat.hpp"

#include <cmath>

#include "vector3d.hpp"

void Thermostat::calculateTemperature(Box& box)
{
    double k_B      = 1.380649e-23;   // J/K
    double momentum = 0.0;

    for (auto& atom : box.getAtoms())
    {
        double mass     = atom->getMass() * 1.66053906892e-27;   // u to kg
        auto   velocity = atom->getVelocity() * 10e-10;          // A/s to m/s
        double velocitySquared  = magnitudeSquared(velocity);
        momentum               += mass * velocitySquared;
    }

    _temperature = momentum / (3 * box.getAtoms().size() * k_B * 1000);
}

void Thermostat::applyThermostat(Box& box)
{
    auto dt        = 2.0;
    auto tempRatio = _targetTemperature / _temperature;

    auto tFactor = std::sqrt(1.0 - (dt / _tau) * (1.0 - tempRatio));

    for (const auto& atom : box.getAtoms()) atom->scaleVelocity(tFactor);
}

double Thermostat::getTemperature() { return _temperature; }
