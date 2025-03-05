#include <iostream>
#include <string>

#include "box.hpp"
#include "input.hpp"

int main(int argc, char* argv[])
{
    const std::string configfile = argv[1];

    InputReader inputreader;
    inputreader.readConfigToml(configfile);
    inputreader.printConfigToml();

    Box box;

    inputreader.readRestartFile(box);

    std::cout << box.x();

    return 0;
}
