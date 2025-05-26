#include "potential.hpp"

#include <bits/stdc++.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
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

    double              F = 0.0;
    std::vector<double> F_vector(3);
    std::vector<double> distanceVector(3);

    double V_Cut =
        4 * epsilon * (pow(sigma / LJCutoff, 12) - pow(sigma / LJCutoff, 6));
    double F_cut = 4 * epsilon *
                   (12 * ((pow(sigma / LJCutoff, 12) / LJCutoff) -
                          (6 * pow(sigma / LJCutoff, 6)) / LJCutoff));

    for (size_t i = 0; i <= box.getAtoms().size(); ++i)
    {
        for (size_t j = i + 1; j <= box.getAtoms().size() - 1; ++j)
        {
            distance = calculateDistance(
                box.getAtom(i).getPosition(),
                box.getAtom(j).getPosition(),
                dimensions
            );

            distanceVector = calculateDistanceVector(
                box.getAtom(i).getPosition(),
                box.getAtom(j).getPosition(),
                dimensions
            );

            std::cout << i << " " << j << " distance " << distance
                      << " LJC: " << LJCutoff << std::endl;

            if (distance < LJCutoff)
            {
                total_energy +=
                    4 * epsilon *
                    (pow(sigma / distance, 12) - pow(sigma / distance, 6));

                F = 4 * epsilon *
                    (12 * ((pow(sigma / distance, 12) / distance) -
                           (6 * pow(sigma / distance, 6)) / distance));

                for (auto k = 0; k < distanceVector.size(); ++k)
                {
                    F_vector[k] += F / distance * distanceVector[k];
                }

                box.getAtom(i).addForce(F_vector);
            }
        }
    }

    box.setEnergy(total_energy);
    std::cout << "Total LJ Energy:" << box.getEnergy() << "kJ/mol" << std::endl;
}
