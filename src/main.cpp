#include <iostream>
#include <string>

#include "box.hpp"
#include "input.hpp"
#include "integrator.hpp"
#include "kinetics.hpp"
#include "linkedCellList.hpp"
#include "output.hpp"
#include "potential.hpp"
#include "thermostat.hpp"

int main(int argc, char* argv[])
{
    const std::string configfile = argv[1];

    InputReader inputreader;
    Box         box;
    Potential   potential;
    Kinetics    kinetics;
    Integrator  integrator;
    Thermostat  thermostat;
    Output      output;

    inputreader.readConfigToml(configfile);
    inputreader.printConfigToml();
    inputreader.readRestartFile(box);

    double sigma = 3.4;   // 3.4 angs

    potential.setLJCutoff(sigma);
    std::cout << "\nLJ Cutoff:" << potential.getLJCutoff() << std::endl;
    std::cout << "Natoms:" << box.getAtoms().size() << std::endl;

    toml::table config      = inputreader.get_config();
    int         nsteps      = config["MDSettings"]["nsteps"].value_or(0);
    double      timestep    = config["MDSettings"]["nsteps"].value_or(0.5);
    double      temperature = config["MDSettings"]["nsteps"].value_or(0.0);

    std::cout << "numcellsX:" << std::floor(box.getDimensions().min() / 8.5)
              << std::endl;

    thermostat.calculateTemperature(box);

    for (int i = 0; i < 1000; ++i)
    {
        CellList cellList = createLinkedCellList(box);
        //    printLinkedCellList(cellList, box);
        std::vector<AtomPair> atomPairs = createNeighborAtomPairs(cellList);
        potential.calculateEnergyForcesLJCellList(box, atomPairs);
        kinetics.calculateKineticEnergy(box);
        box.setEnergy(
            potential.getPotentialEnergy() + kinetics.getKineticEnergy()
        );

        std::cout << "Step: " << i << " T: " << thermostat.getTemperature()
                  << " Ekin: " << kinetics.getKineticEnergy() << " kcal"
                  << " Epot: " << potential.getPotentialEnergy() << " kcal"
                  << std::endl;
        //        std::cout << "Force: " << box.getAtoms()[0]->getForce().x << "
        //        "
        //                  << box.getAtoms()[0]->getForce().y << " "
        //                  << box.getAtoms()[0]->getForce().z << std::endl;
        //        std::cout << "Velocity: " <<
        //        box.getAtoms()[0]->getVelocity().x << " "
        //                  << box.getAtoms()[0]->getVelocity().y << " "
        //                  << box.getAtoms()[0]->getVelocity().z << std::endl;
        if (i % 2 == 0)
        {
            output.writeAllOutput(box);
        }
        integrator.firstStep(box);
        integrator.secondStep(box);
        thermostat.calculateTemperature(box);
        thermostat.applyBussiThermostat(box);
    }

    std::cout << "SUCCESS" << std::endl;

    return 0;
}
