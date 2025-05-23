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

void Potential::calculateEnergyForcesLJ(Box &box)
{
    double total_energy = 0.00;
    double distance     = 0.00;

    double epsilon = 0.23806458033;   // kJ / mol
    double sigma   = 3.4;             // 3.4 angs

    // std::vector<Atom>   atoms      = box.getAtoms();
    std::vector<double> dimensions = box.getDimensions();
    double              LJCutoff   = getLJCutoff();

    double V_Cut =
        4 * epsilon * (pow(sigma / LJCutoff, 12) - pow(sigma / LJCutoff, 6));

    for (size_t i = 0; i <= box.getAtoms().size(); ++i)
    {
        for (size_t j = i + 1; j <= box.getAtoms().size() - 1; ++j)
        {
            double distance = calculateDistance(
                box.getAtom(i).get_position(),
                box.getAtom(j).get_position(),
                dimensions
            );

            std::cout << i << " " << j << " " << distance << std::endl;
            if (distance < _LJCutoff)
            {
                total_energy +=
                    4 * epsilon *
                    (pow(sigma / distance, 12) - pow(sigma / distance, 6));
            }
        }
    }

    std::cout << "Total LJ Energy:" << total_energy << "kJ/mol" << std::endl;
}
