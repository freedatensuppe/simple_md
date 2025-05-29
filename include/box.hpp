#ifndef BOX_HPP
#define BOX_HPP

#include <atom.hpp>
#include <memory>
#include <vector3d.hpp>
#include <vector>

class Box
{
   private:
    Vector3D                           _dimensions;
    std::vector<std::shared_ptr<Atom>> _atoms;
    double                             _energy;
    double                             _temperature;

   public:
    void setDimensions(Vector3D dimensions);
    void setEnergy(double energy);
    void setTemperature(double temperature);

    void  addAtom(const std::shared_ptr<Atom> atom);
    Atom& getAtom(const size_t index);
    std::vector<std::shared_ptr<Atom>> getAtoms();

    double x() { return _dimensions.x; }
    double y() { return _dimensions.y; }
    double z() { return _dimensions.z; }
    double getEnergy();

    double   getTemperature();
    Vector3D getDimensions();

    void applyPBC(Box& box, Vector3D& position);
};

#endif
