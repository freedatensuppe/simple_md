#include "potential.hpp"

#include <bits/stdc++.h>

#include <cmath>
#include <vector>

#include "box.hpp"
#include "linkedCellList.hpp"
#include "utils.hpp"
#include "vector3d.hpp"

void Potential::calculateEnergyForcesLJCellList(
    Box&                   box,
    std::vector<AtomPair>& atomPairs
)
{
    double total_energy = 0.00;

    Vector3D dimensions = box.getDimensions();
    double   LJCutoff   = getLJCutoff();
    double   LJCutoff_6 =
        LJCutoff * LJCutoff * LJCutoff * LJCutoff * LJCutoff * LJCutoff;
    double LJCutoff_12 = LJCutoff_6 * LJCutoff_6;

    double   F = 0.0;
    Vector3D F_vector;

    double r    = 0.00;
    double r_sq = 0.00;
    double r_6  = 0.00;
    double r_12 = 0.00;

    Vector3D rVector(0.0, 0.0, 0.0);

    double V_Cut = _c12 / LJCutoff_12 - _c6 / LJCutoff_6;
    double F_cut = 12 * _c12 / (LJCutoff_12 * LJCutoff) -
                   6 * _c6 / (LJCutoff_6 * LJCutoff);

    for (auto& atom : box.getAtoms())
    {
        atom->setForce(rVector);
    }

    for (auto& atomPair : atomPairs)
    {
        r_sq = calculateDistanceSquared(
            box.getAtoms()[atomPair.first]->getPosition(),
            box.getAtoms()[atomPair.second]->getPosition(),
            dimensions
        );

        if (r_sq < LJCutoff * LJCutoff)
        {
            r    = sqrt(r_sq);
            r_6  = r_sq * r_sq * r_sq;
            r_12 = r_6 * r_6;

            Vector3D F_vector(0.0, 0.0, 0.0);

            rVector = calculateDistanceVector(
                box.getAtoms()[atomPair.first]->getPosition(),
                box.getAtoms()[atomPair.second]->getPosition(),
                dimensions
            );

            total_energy += _c12 / r_12 - _c6 / r_6 - V_Cut;

            F = 12 * _c12 / (r_12 * r) - 6 * _c6 / (r_6 * r) - F_cut;

            F_vector = F * rVector / r;

            //            std::cout << " i: " << atomPair.first << " j: " <<
            //            atomPair.second
            //                      << " r: " << r << " r_sq: " << r_sq
            //                      << " rVector: " << rVector.x << " " <<
            //                      rVector.y << " "
            //                      << rVector.z << " F_VectoF_: " << F_vector.x
            //                      << " "
            //                      << F_vector.y << " " << F_vector.z << " E  "
            //                      << 4 * epsilon * (sigma_12 / r_12 - sigma_6
            //                      / r_6) - V_Cut
            //                      << " F: " << F << std::endl;

            box.getAtoms()[atomPair.first]->addForce(F_vector);
            box.getAtoms()[atomPair.second]->addForce(F_vector *= -1.0);
        }
    }
    _potentialEnergy = total_energy / 6.02214076e23;
}

void Potential::setc6(double epsilon, double sigma)
{
    _c6 = 4 * epsilon * (pow(sigma, 6));
}
void Potential::setc12(double epsilon, double sigma)
{
    _c12 = 4 * epsilon * (pow(sigma, 12));
}

void Potential::setLJCutoff(double sigma) { _LJCutoff = 2.5 * sigma; }

double Potential::getc6() { return _c6; }
double Potential::getc12() { return _c12; }
double Potential::getLJCutoff() { return _LJCutoff; }
double Potential::getPotentialEnergy() { return _potentialEnergy; }

// void Potential::calculateEnergyForcesLJ(Box& box)
//{
//     double total_energy = 0.00;
//
//     Vector3D dimensions = box.getDimensions();
//     double   LJCutoff   = getLJCutoff();
//
//     double epsilon = 0.23806458033;   // kcal / mol
//     double sigma   = 3.4;             // 3.4 angs
//
//     double sigma_6  = sigma * sigma * sigma * sigma * sigma * sigma;
//     double sigma_12 = sigma_6 * sigma_6;
//
//     double LJCutoff_6 =
//         LJCutoff * LJCutoff * LJCutoff * LJCutoff * LJCutoff * LJCutoff;
//     double LJCutoff_12 = LJCutoff_6 * LJCutoff_6;
//
//     double   F = 0.0;
//     Vector3D F_vector;
//
//     double r    = 0.00;
//     double r_sq = 0.00;
//     double r_6  = 0.00;
//     double r_12 = 0.00;
//
//     Vector3D rVector;
//
//     double V_Cut =
//         4 * epsilon * (sigma_12 / LJCutoff_12) - (sigma_6 / LJCutoff_6);
//     double F_cut = 4 * epsilon * (12 * sigma_12 / (LJCutoff_12 * LJCutoff)) -
//                    (6 * sigma_6 / (LJCutoff_6 * LJCutoff));
//
//     for (size_t i = 0; i <= box.getAtoms().size(); ++i)
//     {
//         for (size_t j = i + 1; j <= box.getAtoms().size() - 1; ++j)
//         {
//             r_sq = calculateDistanceSquared(
//                 box.getAtom(i).getPosition(),
//                 box.getAtom(j).getPosition(),
//                 dimensions
//             );
//
//             if (r_sq < LJCutoff * LJCutoff)
//             {
//                 r    = sqrt(r_sq);
//                 r_6  = r_sq * r_sq * r_sq;
//                 r_12 = r_6 * r_6;
//
//                 rVector = calculateDistanceVector(
//                     box.getAtom(i).getPosition(),
//                     box.getAtom(j).getPosition(),
//                     dimensions
//                 );
//
//                 total_energy += 4 * epsilon * sigma_12 / r_12 - sigma_6 /
//                 r_6;
//
//                 F = 4 * epsilon *
//                     (12 * sigma_12 / (r_12 * r) - 6 * sigma_6 / (r_6 * r));
//
//                 F_vector = F * rVector / r;
//
//                 box.getAtom(i).addForce(F_vector);
//             }
//         }
//     }
//
//     box.setEnergy(total_energy);
// }
