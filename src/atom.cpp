#include "atom.hpp"

#include "vector3d.hpp"

void Atom::setName(const std::string& atomName) { _atomName = atomName; }

void Atom::setAtomType(double atomType) { _atomType = atomType; }
void Atom::setPosition(Vector3D& position) { _position = position; }
void Atom::setVelocity(Vector3D& velocity) { _velocity = velocity; }
void Atom::setForce(Vector3D& force) { _force = force; }

void Atom::addForce(Vector3D& force) { _force += force; }

void Atom::updatePosition(Vector3D& shift) { _position += shift; }

std::string Atom::getName() { return _atomName; }
Vector3D    Atom::getPosition() { return _position; }
Vector3D    Atom::getVelocity() { return _velocity; }
Vector3D    Atom::getForce() { return _force; }
