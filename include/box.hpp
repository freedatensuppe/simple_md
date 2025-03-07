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
    void              setDimensions(std::vector<double> dimensions);
    void              addAtom(Atom &);
    std::vector<Atom> getAtoms();

    double              x() { return _dimensions[0]; }
    double              y() { return _dimensions[1]; }
    double              z() { return _dimensions[2]; }
    std::vector<double> getDimensions() { return _dimensions; }
};

#endif
