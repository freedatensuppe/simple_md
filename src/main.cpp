#include <iostream>
#include <string>

#include "box.hpp"
#include "input.hpp"
#include "integrator.hpp"
#include "linkedCellList.hpp"
#include "output.hpp"
#include "potential.hpp"
#include "thermostat.hpp"

int main(int argc, char* argv[])
{
    const std::string configfile = argv[1];

    InputReader inputreader;

    inputreader.readConfigToml(configfile);
    inputreader.printConfigToml();

    Box        box;
    Potential  potential;
    Integrator integrator;
    Thermostat thermostat;

    inputreader.readRestartFile(box);
    Output output;

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

    for (int i = 0; i < 10000; ++i)
    {
        CellList cellList = createLinkedCellList(box);
        //    printLinkedCellList(cellList, box);
        std::vector<AtomPair> atomPairs = createNeighborAtomPairs(cellList);
        potential.calculateEnergyForcesLJCellList(box, atomPairs);

        if (i % 1000 == 0)
        {
            std::cout << "Step: " << i << " T: " << thermostat.getTemperature()
                      << " E: " << box.getEnergy() << " kcal/mol" << std::endl;
        }
        output.writeAllOutput(box);
        integrator.firstStep(box);
        integrator.secondStep(box);
        thermostat.calculateTemperature(box);
        thermostat.applyThermostat(box);
    }

    std::cout << "SUCCESS" << std::endl;

    return 0;
}
