#include "box.hpp"

#include <cmath>

#include "atom.hpp"
#include "vector3d.hpp"

void Box::setDimensions(Vector3D dimensions) { _dimensions = dimensions; }

void Box::setEnergy(double energy) { _energy = energy; }
void Box::setTemperature(double temperature) { _temperature = temperature; }

void Box::addAtom(const std::shared_ptr<Atom> atom) { _atoms.push_back(atom); }

std::vector<std::shared_ptr<Atom>> &Box::getAtoms() { return _atoms; }

Atom &Box::getAtom(const size_t index) { return *(_atoms[index]); }

double Box::getEnergy() { return _energy; }
double Box::getTemperature() { return _temperature; }

Vector3D Box::getDimensions() { return _dimensions; }

void Box::applyPBC(Box &box, Vector3D &position)
{
    position -= box.getDimensions() * round(position / box.getDimensions());
}
