#include "box.hpp"

#include "atom.hpp"

void Box::setDimensions(std::vector<double> dimensions)
{
    _dimensions = dimensions;
}

void Box::addAtom(const std::shared_ptr<Atom> atom) { _atoms.push_back(atom); }

std::vector<std::shared_ptr<Atom>> Box::getAtoms() { return _atoms; }

Atom &Box::getAtom(const size_t index) { return *(_atoms[index]); }
