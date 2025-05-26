#include "integrator.hpp"

void Integrator::integrateVelocities(Atom *atom)
{
    auto       velocity = atom->getVelocity();
    const auto force    = atom->getForce();
    const auto mass     = 39.948;
    const auto dt       = 0.5;

    for (auto i = 0; i < velocity.size(); ++i)
    {
        velocity[i] += dt * force[i] / mass;
    }

    atom->setVelocity(velocity);
}

void Integrator::updatePosition(Atom *atom)
{
    //    auto       position = atom->getPosition();
    //    const auto velocity = atom->getVelocity();
    //
    //    position += 2.0 * velocity;
    //
    //    simBox.applyPBC(position);
    //
    //    atom->setPosition(position);
}

void Integrator::firstStep(Box &box) {}

void Integrator::secondStep(Box &box) {}
