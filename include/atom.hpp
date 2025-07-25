#ifndef ATOM_HPP
#define ATOM_HPP

#include <string>
#include <vector>

#include "vector3d.hpp"

class Atom
{
   private:
    std::string _atomName;
    double      _atomType;
    double      _mass = 39.948;   // u
    Vector3D    _position;
    Vector3D    _positionPrev;
    Vector3D    _velocity;
    Vector3D    _force;

   public:
    void setName(const std::string& atomName);
    void setAtomType(double& atomType);
    void setPosition(Vector3D& position);
    void setVelocity(Vector3D& velocity);
    void setForce(Vector3D& force);

    void addForce(Vector3D& force);
    void updatePosition(Vector3D& shift);
    void scaleVelocity(double& tFactor);

    std::string getName() const;
    double      getMass() const;
    Vector3D    getPosition() const;
    Vector3D    getVelocity() const;
    Vector3D    getForce() const;
};

#endif
