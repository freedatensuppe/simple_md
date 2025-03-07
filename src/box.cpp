#include "box.hpp"

#include "atom.hpp"

void Box::setDimensions(std::vector<double> dimensions)
{
    _dimensions = dimensions;
}

void Box::addAtom(Atom& atom) { _atoms.push_back(atom); }

std::vector<Atom> Box::getAtoms() { return _atoms; }
