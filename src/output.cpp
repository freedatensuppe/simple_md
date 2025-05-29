#include "output.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>

#include "vector3d.hpp"

void Output::writeAllOutput(Box& box)
{
    writeXYZTrajectory(box);
    writeEnergyFile(box);
}

void Output::writeXYZTrajectory(Box& box)
{
    std::ofstream outxyz("output_trajectory.xyz", std::ios_base::app);
    outxyz << box.getAtoms().size();
    outxyz << std::endl << std::endl;
    for (size_t i = 0; i < box.getAtoms().size(); ++i)
    {
        std::string type = box.getAtom(i).getName();
        Vector3D    p    = box.getAtom(i).getPosition();
        outxyz << type << " " << p.x << " " << p.y << " " << p.z << std::endl;
    }
    outxyz.close();
}
void Output::writeEnergyFile(Box& box)
{
    std::ofstream outenergy("output_energy.dat", std::ios_base::app);
    outenergy << box.getEnergy() << " " << box.getTemperature() << std::endl;
    outenergy.close();
}
