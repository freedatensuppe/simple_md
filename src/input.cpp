#include "input.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

#include "atom.hpp"
#include "box.hpp"
#include "toml.hpp"
#include "vector3d.hpp"

toml::table InputReader::getConfig() { return _config; }

void InputReader::readConfigToml(const std::string _configfile)
{
    _config = toml::parse_file(_configfile);
}

void InputReader::printConfigToml()
{
    std::cout << "Provided TOML input file:" << std::endl;
    std::cout << _config << std::endl;
}

void InputReader::readRestartFile(Box& box)
{
    std::string restartfile =
        _config["MDSettings"]["restart_file"].value_or("");

    std::string                        atomName;
    std::vector<std::shared_ptr<Atom>> atoms;
    int                                index;
    double                             box_x, box_y, box_z;
    double                             atomType;
    double                             x, y, z;
    double                             vx, vy, vz;
    double                             Fx, Fy, Fz;
    Vector3D                           position;
    Vector3D                           velocity;
    Vector3D                           Force;

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
        atom->setName(atomName);
        atom->setAtomType(atomType);
        position = {x, y, z};
        velocity = {vx, vy, vz};
        Force    = {Fx, Fy, Fz};
        atom->setPosition(position);
        atom->setVelocity(velocity);
        atom->setForce(Force);
        box.addAtom(atom);
    }

    rstfile.close();
}
