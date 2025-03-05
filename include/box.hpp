#ifndef BOX_HPP
#define BOX_HPP

#include <atom.hpp>
#include <vector>

class Box
{
   private:
    std::vector<double> _dimensions;
    std::vector<Atom>   _atoms;
    double              _energy;

   public:
    void              set_dimensions(std::vector<double> dimensions);
    void              addAtom(Atom &);
    std::vector<Atom> get_atoms();

    double x() { return _dimensions[0]; }
    double y() { return _dimensions[1]; }
    double z() { return _dimensions[2]; }

    double calculate_energy(Box &box, std::vector<Atom> atoms);
};

#endif
