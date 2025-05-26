#ifndef BOX_HPP
#define BOX_HPP

#include <atom.hpp>
#include <memory>
#include <vector>

class Box
{
   private:
    std::vector<double>                _dimensions;
    std::vector<std::shared_ptr<Atom>> _atoms;
    double                             _energy;

   public:
    void  setDimensions(std::vector<double> dimensions);
    void  setEnergy(double energy);
    void  addAtom(const std::shared_ptr<Atom> atom);
    Atom& getAtom(const size_t index);
    std::vector<std::shared_ptr<Atom>> getAtoms();

    double              x() { return _dimensions[0]; }
    double              y() { return _dimensions[1]; }
    double              z() { return _dimensions[2]; }
    std::vector<double> getDimensions() { return _dimensions; }
    double              getEnergy();

    void applyPBC(std::vector<double>& position);
};

#endif
