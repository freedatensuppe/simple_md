#include "integrator.hpp"

#include "vector3d.hpp"

void Integrator::integrateVelocities(Atom *atom)
{
    Vector3D velocity = atom->getVelocity();
    auto     force    = atom->getForce();
    auto     mass     = 39.948;
    auto     dt       = 2.0E-15;

    velocity += dt * force / mass;
    atom->setVelocity(velocity);
}

void Integrator::integratePositions(Atom *atom, Box &box)

{
    auto position = atom->getPosition();
    auto velocity = atom->getVelocity();
    auto dt       = 2.0E-15;

    position += dt * velocity;

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
