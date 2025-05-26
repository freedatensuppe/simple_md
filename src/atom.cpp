#include "atom.hpp"

void Atom::setName(const std::string& atomName) { _atomName = atomName; }

void Atom::setAtomType(double atomType) { _atomType = atomType; }
void Atom::setPosition(double x, double y, double z) { _position = {x, y, z}; }
void Atom::setVelocity(std::vector<double>& velocity) { _velocity = velocity; }
void Atom::setForce(double Fx, double Fy, double Fz) { _force = {Fx, Fy, Fz}; }

void Atom::addForce(std::vector<double>& force)
{
    for (auto i = 0; i < _force.size(); ++i)
    {
        _force[i] += force[i];
    }
}

void Atom::updatePosition(std::vector<double>& shift)
{
    for (auto i = 0; i < _force.size(); ++i)
    {
        _position[i] += shift[i];
    }
}

std::string         Atom::getName() { return _atomName; }
std::vector<double> Atom::getPosition() { return _position; }
std::vector<double> Atom::getVelocity() { return _velocity; }
std::vector<double> Atom::getForce() { return _force; }
