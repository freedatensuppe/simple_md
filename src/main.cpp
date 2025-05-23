#include <iostream>
#include <string>

#include "box.hpp"
#include "input.hpp"
#include "potential.hpp"

int main(int argc, char* argv[])
{
    const std::string configfile = argv[1];

    InputReader inputreader;
    inputreader.readConfigToml(configfile);
    inputreader.printConfigToml();

    Box       box;
    Potential potential;

    std::cout << "here";

    inputreader.readRestartFile(box);
    potential.setLJCutoff(box.getDimensions());
    std::cout << potential.getLJCutoff() << std::endl;
    potential.calculateEnergyForcesLJ(box);

    return 0;
}
