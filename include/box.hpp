#ifndef BOX_HPP
#define BOX_HPP

#include <atom.hpp>
#include <vector>

class Box
{
   private:
    std::vector<double> _dimensions;
    std::vector<Atom>   _atoms;

   public:
    Box(std::vector<double> dimensions) : _dimensions(dimensions) {}
    void   addAtom(Atom &);
    double x() { return _dimensions[0]; }
    double y() { return _dimensions[1]; }
    double z() { return _dimensions[2]; }
};

#endif
