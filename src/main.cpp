#include <iostream>
#include <string>

#include "box.hpp"
#include "input.hpp"
#include "integrator.hpp"
#include "kinetics.hpp"
#include "linkedCellList.hpp"
#include "output.hpp"
#include "potential.hpp"
#include "setup.hpp"
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
    Setup       setup;

    setup.setupSystem(
        box,
        configfile,
        inputreader,
        integrator,
        potential,
        thermostat
    );

    toml::table config = inputreader.getConfig();

    int nsteps = config["MDSettings"]["nsteps"].value_or(0);

    std::cout << std::endl;
    std::cout << "Settings chosen for the Simulation:" << std::endl;
    std::cout << std::endl;
    std::cout << "Natoms: " << box.getAtoms().size() << std::endl;
    std::cout << "nsteps: " << nsteps << std::endl;
    std::cout << "timestep: " << integrator.getTimestep() << std::endl;
    std::cout << "temperature: " << thermostat.getTargetTemperature()
              << std::endl;
    std::cout << "LJ Cutoff: " << potential.getLJCutoff() << std::endl;
    std::cout << "epsilon: " << potential.getEpsilon() << std::endl;
    std::cout << "sigma: " << potential.getSigma() << std::endl;
    std::cout << "c6: " << potential.getc6() << std::endl;
    std::cout << "c12: " << potential.getc12() << std::endl;
    std::cout << std::endl;
    std::cout << "Starting MD ... " << std::endl;

    for (int i = 0; i < nsteps; ++i)
    {
        CellList cellList = createLinkedCellList(box, potential.getLJCutoff());
        std::vector<AtomPair> atomPairs = createNeighborAtomPairs(cellList);

        integrator.firstStep(box);

        potential.resetForces(box);
        potential.calculateEnergyForcesLJCellList(box, atomPairs);

        integrator.secondStep(box);

        thermostat.calculateTemperature(box);
        thermostat.applyBerendsenThermostat(box);

        kinetics.calculateKineticEnergy(box);
        box.setEnergy(
            potential.getPotentialEnergy() + kinetics.getKineticEnergy()
        );
        if (i % 2 == 0)
        {
            output.writeAllOutput(box);
            std::cout << "Step: " << i << " T: " << thermostat.getTemperature()
                      << " Ekin: " << kinetics.getKineticEnergy() << " kcal/mol"
                      << " Epot: " << potential.getPotentialEnergy()
                      << " kcal/mol"
                      << " Etot: " << box.getEnergy() << " kcal/mol"
                      << std::endl;
        }
    }

    std::cout << "SUCCESS" << std::endl;

    return 0;
}
