#include "integrator.hpp"

#include <iostream>
#include <ostream>

#include "potential.hpp"
#include "vector3d.hpp"

void Integrator::integrateVelocities(Atom *atom)
{
    Vector3D velocity = atom->getVelocity();   // A/s
    auto     force    = atom->getForce();      // kcal/(mol A)
    auto     mass     = atom->getMass();       // u
    auto     dt       = _timestep * 1e-15;     // s

    double u_to_kg           = 1.66053906892e-27;
    double kcal_to_J         = 4183.995381;
    double avogadro_constant = 6.02214076e23;
    double A_to_m            = 1e-10;

    double force_to_si = kcal_to_J / avogadro_constant / A_to_m;
    //    std::cout << force_to_si << std::endl;
    double mass_to_si     = u_to_kg;
    double si_to_velocity = 1 / A_to_m;

    //    Vector3D vel =
    //        force * force_to_si / (mass * mass_to_si) * dt * 0.5 *
    //        si_to_velocity;
    //    std::cout << " mass: " << mass << std::endl;
    //    std::cout << " vatom: " << velocity.x << " " << velocity.y << " "
    //              << velocity.z << std::endl;
    //
    //    std::cout << " Force: " << force.x << " " << force.y << " " << force.z
    //              << std::endl;
    //    std::cout << " add v: " << vel.x << " " << vel.y << " " << vel.z
    //              << std::endl;

    velocity +=
        force * force_to_si / (mass * mass_to_si) * dt * 0.5 * si_to_velocity;

    //    std::cout << " added: " << velocity.x << " " << velocity.y << " "
    //              << velocity.z << std::endl;

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
