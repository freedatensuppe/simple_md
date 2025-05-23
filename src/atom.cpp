#include "atom.hpp"

#include <vector>

void Atom::set_name(const std::string& atomName) { _atomName = atomName; }

void Atom::set_atomType(double atomType) { _atomType = atomType; }
void Atom::set_position(double x, double y, double z) { _position = {x, y, z}; }
void Atom::set_velocity(double vx, double vy, double vz)
{
    _velocity = {vx, vy, vz};
}
void Atom::set_force(double Fx, double Fy, double Fz) { _force = {Fx, Fy, Fz}; }
