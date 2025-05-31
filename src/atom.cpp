#include "atom.hpp"

#include "vector3d.hpp"

void Atom::setName(const std::string& atomName) { _atomName = atomName; }

void Atom::setAtomType(double& atomType) { _atomType = atomType; }
void Atom::setPosition(Vector3D& position) { _position = position; }
void Atom::setVelocity(Vector3D& velocity) { _velocity = velocity; }
void Atom::setForce(Vector3D& force) { _force = force; }

void Atom::addForce(Vector3D& force) { _force += force; }
void Atom::updatePosition(Vector3D& shift) { _position += shift; }
void Atom::scaleVelocity(double& tFactor) { _velocity *= tFactor; }

std::string Atom::getName() const { return _atomName; }
double      Atom::getMass() const { return _mass; }
Vector3D    Atom::getPosition() const { return _position; }
Vector3D    Atom::getVelocity() const { return _velocity; }
Vector3D    Atom::getForce() const { return _force; }
