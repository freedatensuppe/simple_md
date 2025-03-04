#include "input.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "atom.hpp"
#include "box.hpp"
#include "toml.hpp"

void InputReader::readConfigToml(const std::string _configfile)
{
    _config = toml::parse_file(_configfile);
}

void InputReader::printConfigToml() { std::cout << _config << std::endl; }

void InputReader::readRestartFile()
{
    std::string restartfile =
        _config["MDSettings"]["restart_file"].value_or("");

    double            box_x, box_y, box_z;
    std::string       atomName;
    int               index;
    double            atomType;
    double            x, y, z;
    double            vx, vy, vz;
    double            Fx, Fy, Fz;
    std::vector<Atom> atoms;
    std::ifstream     rstfile(restartfile);
    std::string       line;

    if (!rstfile.is_open())
    {
        std::cerr << "Error opening file: " << restartfile << std::endl;
    }

    rstfile >> atomName >> box_x >> box_y >> box_z;

    Box box({box_x, box_y, box_z});

    while (rstfile >> atomName >> index >> atomType >> x >> y >> z >> vx >>
           vy >> vz >> Fx >> Fy >> Fz)

    {
        Atom atom;
        atom.set_name(atomName);
        atom.set_atomType(atomType);
        atom.set_position(x, y, z);
        atom.set_velocity(vx, vy, vz);
        atom.set_force(Fx, Fy, Fz);
        // box.addAtom();
        atoms.push_back(atom);
    }

    rstfile.close();
}
