#include <iostream>
#include <string>

#include "box.hpp"
#include "input.hpp"
#include "integrator.hpp"
#include "output.hpp"
#include "potential.hpp"

int main(int argc, char* argv[])
{
    const std::string configfile = argv[1];

    InputReader inputreader;

    inputreader.readConfigToml(configfile);
    inputreader.printConfigToml();

    Box        box;
    Potential  potential;
    Integrator integrator;

    inputreader.readRestartFile(box);
    Output output;

    potential.setLJCutoff(box.getDimensions());
    std::cout << "LJ Cutoff:" << potential.getLJCutoff() << std::endl;

    toml::table config      = inputreader.get_config();
    int         nsteps      = config["MDSettings"]["nsteps"].value_or(0);
    double      timestep    = config["MDSettings"]["nsteps"].value_or(0.5);
    double      temperature = config["MDSettings"]["nsteps"].value_or(0.0);

    //    Atom atom0 = box.getAtom(0);
    //    Atom atom1 = box.getAtom(1);
    //
    //    Vector3D pos0 = atom0.getPosition();
    //    Vector3D pos1 = atom1.getPosition();
    //
    //    pos0.print();
    //    pos1.print();

    for (int i = 0; i < 100; ++i)
    {
        potential.calculateEnergyForcesLJ(box);

        std::cout << "Step:" << i << "Total LJ Energy:" << box.getEnergy()
                  << "kcal/mol" << std::endl;
        output.writeAllOutput(box);
        integrator.firstStep(box);
        integrator.secondStep(box);
    }
    //    Vector3D v1 = {0.0, 0.0, 0.0};
    //    Vector3D v2 = {13.478100, -17.733801, -10.077600};
    //    Vector3D v3 = v1 - v2;
    //    v3.print();
    // std::cout << v3.magnitude() << std::endl;

    std::cout << "SUCCESS" << std::endl;

    return 0;
}
