#include "potential.hpp"

#include <bits/stdc++.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "box.hpp"
#include "utils.hpp"
#include "vector3d.hpp"

void Potential::setLJCutoff(Vector3D dimensions)
{
    _LJCutoff = dimensions.minElement() / 2;
}

void Potential::calculateEnergyForcesLJ(Box& box)
{
    double total_energy = 0.00;
    double distance     = 0.00;

    double epsilon = 0.997;   // kJ / mol
    double sigma   = 3.4;     // 3.4 angs

    Vector3D dimensions = box.getDimensions();
    double   LJCutoff   = getLJCutoff();

    double   F = 0.0;
    Vector3D F_vector;
    Vector3D distanceVector;

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

            //            std::cout << i << std::endl;
            //            box.getAtom(i).getPosition().print();
            //            std::cout << j << std::endl;
            //            box.getAtom(j).getPosition().print();

            if (i < 10 && j < 10)
            {
                std::cout << i << " " << j << " | distance: " << std::setw(10)
                          << distance << std::endl;
            }
            if (distance < LJCutoff)
            {
                //                total_energy +=
                //                    4 * epsilon *
                //                    (pow(sigma / distance, 12) - pow(sigma /
                //                    distance, 6));
                double sr6    = pow(sigma / distance, 6);
                total_energy += 4.0 * epsilon * (sr6 * sr6 - sr6);

                //                F = 4 * epsilon *
                //                    (12 * ((pow(sigma / distance, 12) /
                //                    distance) - (6 * pow(sigma / distance, 6))
                //                    /
                //                           distance));
                F = 24.0 * epsilon * (2 * sr6 * sr6 - sr6) / distance;

                F_vector = F * distanceVector / distance;

                box.getAtom(i).addForce(F_vector);
            }
        }
    }

    box.setEnergy(total_energy);
    std::cout << "Total LJ Energy:" << box.getEnergy() / 6.022e+23 << "kJ/mol"
              << std::endl;
}
