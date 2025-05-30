#include "thermostat.hpp"

#include <cmath>
#include <iostream>
#include <random>

#include "vector3d.hpp"

void Thermostat::calculateTemperature(Box& box)
{
    double k_B               = 1.380649e-23;   // J/K
    double e_kin             = 0.0;
    double A_to_m            = 1e-10;
    double u_to_kg           = 1.66053906892e-27;
    double conversion_factor = A_to_m * A_to_m * u_to_kg / k_B;

    for (auto& atom : box.getAtoms())
    {
        double mass             = atom->getMass();       // u to kg
        auto   velocity         = atom->getVelocity();   // A/s to m/s
        double velocitySquared  = magnitudeSquared(velocity);
        e_kin                  += mass * velocitySquared;
    }

    _temperature = e_kin * conversion_factor / (3 * box.getAtoms().size());
    box.setTemperature(_temperature);
}

void Thermostat::applyBerendsenThermostat(Box& box)
{
    auto dt        = 2.0;
    auto tempRatio = _targetTemperature / _temperature;

    auto tFactor = ::sqrt(1.0 + dt / _tau * (tempRatio - 1.0));
    std::cout << tFactor;
    for (const auto& atom : box.getAtoms()) atom->scaleVelocity(tFactor);
}

void Thermostat::applyBussiThermostat(Box& box)
{
    auto dt = 2.0;   // fs, or your actual timestep

    int N   = box.getAtoms().size();
    int dof = 3 * N;

    static std::mt19937                   rng(std::random_device{}());
    std::normal_distribution<double>      normal(0.0, 1.0);
    std::chi_squared_distribution<double> chi2(dof - 1);

    double c         = std::exp(-dt / _tau);
    double tempRatio = _targetTemperature / _temperature;

    double r = normal(rng);
    double s = chi2(rng);

    double factor = c + (1.0 - c) * tempRatio * (s + r * r) / dof +
                    2.0 * r * std::sqrt(c * (1.0 - c) * tempRatio / dof);

    double lambda = std::sqrt(factor);

    for (auto& atom : box.getAtoms())
    {
        atom->scaleVelocity(lambda);
    }
}

double Thermostat::getTemperature() { return _temperature; }
