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

    Vector3D dimensions = box.getDimensions();
    double   LJCutoff   = getLJCutoff();

    double epsilon = 0.23806458033;   // kcal / mol
    double sigma   = 3.4;             // 3.4 angs

    double sigma_6  = sigma * sigma * sigma * sigma * sigma * sigma;
    double sigma_12 = sigma_6 * sigma_6;

    double LJCutoff_6 =
        LJCutoff * LJCutoff * LJCutoff * LJCutoff * LJCutoff * LJCutoff;
    double LJCutoff_12 = LJCutoff_6 * LJCutoff_6;

    double   F = 0.0;
    Vector3D F_vector;

    double r    = 0.00;
    double r_sq = 0.00;
    double r_6  = 0.00;
    double r_12 = 0.00;

    Vector3D rVector;

    double V_Cut =
        4 * epsilon * (sigma_12 / LJCutoff_12) - (sigma_6 / LJCutoff_6);
    double F_cut = 4 * epsilon * (12 * sigma_12 / (LJCutoff_12 * LJCutoff)) -
                   (6 * sigma_6 / (LJCutoff_6 * LJCutoff));

    for (size_t i = 0; i <= box.getAtoms().size(); ++i)
    {
        for (size_t j = i + 1; j <= box.getAtoms().size() - 1; ++j)
        {
            r_sq = calculateDistanceSquared(
                box.getAtom(i).getPosition(),
                box.getAtom(j).getPosition(),
                dimensions
            );

            //            std::cout << i << std::endl;
            //            box.getAtom(i).getPosition().print();
            //            std::cout << j << std::endl;
            //            box.getAtom(j).getPosition().print();

            if (r < LJCutoff)
            {
                r    = sqrt(r_sq);
                r_6  = r_sq * r_sq * r_sq;
                r_12 = r_6 * r_6;

                rVector = calculateDistanceVector(
                    box.getAtom(i).getPosition(),
                    box.getAtom(j).getPosition(),
                    dimensions
                );

                total_energy += 4 * epsilon * sigma_12 / r_12 - sigma_6 / r_6;

                F = 4 * epsilon *
                    (12 * sigma_12 / (r_12 * r) - 6 * sigma_6 / (r_6 * r));

                F_vector = F * rVector / r;

                box.getAtom(i).addForce(F_vector);
            }
        }
    }

    box.setEnergy(total_energy);
}
