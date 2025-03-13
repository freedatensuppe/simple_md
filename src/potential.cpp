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

void Potential::calculateEnergyLJ(Box &box)
{
    double total_energy = 0.00;
    double distance     = 0.00;

    double epsilon = 0.23806458033;   // kJ / mol
    double sigma   = 3.4;             // 3.4 angs

    std::vector<Atom>   atoms      = box.getAtoms();
    std::vector<double> dimensions = box.getDimensions();
    double              LJCutoff   = getLJCutoff();

    for (size_t i = 0; i <= atoms.size(); ++i)
    {
        for (size_t j = i + 1; j <= atoms.size() - 1; ++j)
        {
            double distance = calculateDistance(
                atoms[i].get_position(),
                atoms[j].get_position(),
                dimensions
            );

            std::cout << i << " " << j << " " << distance << std::endl;
            if (distance < LJCutoff)
            {
                total_energy +=
                    4 * epsilon *
                    (pow(sigma / distance, 12) - pow(sigma / distance, 6));
            }
        }
    }

    std::cout << "Total LJ Energy:" << total_energy << "kJ/mol" << std::endl;
}

// void Potential::calculateForcesLJ(Box &box, double ljEnergyCutoff) {}
