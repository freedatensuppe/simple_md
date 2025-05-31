
#include "thermostat.hpp"

#include <cmath>

#include "conversionFactors.hpp"

void Thermostat::calculateTemperature(Box& box)
{
    double e_kin = 0.0;

    for (auto& atom : box.getAtoms())
    {
        double mass             = atom->getMass();       // u to kg
        auto   velocity         = atom->getVelocity();   // A/s to m/s
        double velocitySquared  = magnitudeSquared(velocity);
        e_kin                  += mass * velocitySquared;
    }

    _temperature = e_kin * _TEMPERATURE_FACTOR_ / (3 * box.getAtoms().size());
    box.setTemperature(_temperature);
}

void Thermostat::applyBerendsenThermostat(Box& box)
{
    auto dt        = 2.0;
    auto tempRatio = _targetTemperature / _temperature;

    auto lambda = std::sqrt(1.0 + dt / _tau * (tempRatio - 1.0));
    for (const auto& atom : box.getAtoms()) atom->scaleVelocity(lambda);
}

double Thermostat::getTemperature() { return _temperature; }

void   Thermostat::setTargetTemperature(double T) { _targetTemperature = T; }
double Thermostat::getTargetTemperature() { return _targetTemperature; }
