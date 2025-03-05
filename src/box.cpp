#include "box.hpp"

#include "atom.hpp"

void Box::set_dimensions(std::vector<double> dimensions)
{
    _dimensions = dimensions;
}

void Box::addAtom(Atom& atom) { _atoms.push_back(atom); }

std::vector<Atom> Box::get_atoms() { return _atoms; }
