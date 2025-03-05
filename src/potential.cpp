#include "potential.hpp"

#include "box.hpp"

void Potential::calculate_energy_LJ(Box &box) {}

void Potential::calculate_forces_LJ(Box &box)
{
    for (auto &atom : box.get_atoms())
    {
    }
}
