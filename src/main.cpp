#include <string>

#include "input.hpp"

int main(int argc, char* argv[])
{
    const std::string configfile = argv[1];
    InputReader       inputreader;
    inputreader.readConfigToml(configfile);
    inputreader.printConfigToml();
    inputreader.readRestartFile();
    return 0;
}
