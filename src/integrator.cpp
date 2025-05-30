#include "integrator.hpp"

#include <iostream>

#include "vector3d.hpp"

void Integrator::integrateVelocities(Atom *atom)
{
    Vector3D velocity = atom->getVelocity();
    auto     force    = atom->getForce();
    auto     mass     = atom->getMass();
    auto     dt       = _timestep * 1e-15;

    velocity += (force / mass) * dt;
    atom->setVelocity(velocity);
}

void Integrator::integratePositions(Atom *atom, Box &box)

{
    auto position = atom->getPosition();
    auto velocity = atom->getVelocity();
    auto dt       = _timestep * 1e-15;

    position += velocity * dt;

    box.applyPBC(box, position);

    atom->setPosition(position);
}

void Integrator::firstStep(Box &box)
{
    for (auto &atom : box.getAtoms())
    {
        integrateVelocities(atom.get());
        integratePositions(atom.get(), box);
    }
}

void Integrator::secondStep(Box &box)
{
    for (auto &atom : box.getAtoms())
    {
        integrateVelocities(atom.get());
    }
}

void Integrator::setTimestep(double timestep) { _timestep = timestep; }

double Integrator::getTimestep() { return _timestep; }
