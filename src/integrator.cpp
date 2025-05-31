#include "integrator.hpp"

#include "conversionFactors.hpp"
#include "vector3d.hpp"

void Integrator::integrateVelocities(Atom *atom)
{
    Vector3D velocity = atom->getVelocity();   // A/s
    auto     force    = atom->getForce();      // kcal/(mol A)
    auto     mass     = atom->getMass();       // u
    auto     dt       = _timestep * 1e-15;     // s

    velocity += force * _FORCE_TO_SI_ / (mass * _MASS_TO_SI_) * dt * 0.5 *
                _SI_TO_VELOCITY_;

    atom->setVelocity(velocity);
}

void Integrator::integratePositions(Atom *atom, Box &box)

{
    auto       position = atom->getPosition();
    const auto velocity = atom->getVelocity();
    const auto dt       = _timestep * 1e-15;

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
