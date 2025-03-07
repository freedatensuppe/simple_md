#include "potential.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "box.hpp"
#include "utils.hpp"

void Potential::setLJCutoff(std::vector<double> dimensions)
{
    _LJCutoff = *std::min_element(dimensions.begin(), dimensions.end()) / 2;
}

void Potential::calculateEnergyLJ(Box &box, double ljEnergyCutoff)
{
    double r_cut        = ljEnergyCutoff;
    double total_energy = 0;
    double distance     = 0;

    double epsilon = 0.23806458033;   // kJ / mol
    double sigma   = 3.4;             // 3.4 angs

    for (size_t i = 0; i < box.getAtoms().size(); ++i)
    {
        for (size_t j = i + 1; i < box.getAtoms().size() - 1; ++j)
        {
            double distance = calculateDistance(
                box.getAtoms()[i].get_position(),
                box.getAtoms()[j].get_position()
            );
            if (distance < ljEnergyCutoff)
            {
                total_energy +=
                    4 * epsilon *
                    (pow(sigma / distance, 12) - pow(sigma / distance, 6));
            }
        }
    }
    std::print(total_energy);
}

void Potential::calculateForcesLJ(Box &box, double ljEnergyCutoff) {}
