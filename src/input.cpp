#include "input.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "atom.hpp"
#include "box.hpp"
#include "toml.hpp"

void InputReader::readConfigToml(const std::string _configfile)
{
    _config = toml::parse_file(_configfile);
}

void InputReader::printConfigToml() { std::cout << _config << std::endl; }

void InputReader::readRestartFile(Box& box)
{
    std::string restartfile =
        _config["MDSettings"]["restart_file"].value_or("");

    double                             box_x, box_y, box_z;
    std::string                        atomName;
    int                                index;
    double                             atomType;
    double                             x, y, z;
    std::vector<double>                velocity(3);
    double                             vx, vy, vz;
    double                             Fx, Fy, Fz;
    std::vector<std::shared_ptr<Atom>> atoms;

    std::ifstream rstfile(restartfile);
    std::string   line;

    if (!rstfile.is_open())
    {
        std::cerr << "Error opening file: " << restartfile << std::endl;
    }

    rstfile >> atomName >> box_x >> box_y >> box_z;

    box.setDimensions({box_x, box_y, box_z});

    while (rstfile >> atomName >> index >> atomType >> x >> y >> z >> vx >>
           vy >> vz >> Fx >> Fy >> Fz)

    {
        auto atom = std::make_shared<Atom>();
        velocity  = {vx, vy, vz};
        atom->setName(atomName);
        atom->setAtomType(atomType);
        atom->setPosition(x, y, z);
        atom->setVelocity(velocity);
        atom->setForce(Fx, Fy, Fz);
        box.addAtom(atom);
    }

    rstfile.close();
}
