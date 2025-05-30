#ifndef SETUP_HPP
#define SETUP_HPP

#include "box.hpp"
#include "input.hpp"
#include "integrator.hpp"
#include "potential.hpp"
#include "thermostat.hpp"

class Setup
{
   private:
   public:
    void setupInput(
        Box&               box,
        InputReader&       inputReader,
        const std::string& configfile
    );
    void setupSystem(
        Box&         box,
        std::string  configfile,
        InputReader& inputreader,
        Integrator&  integrator,
        Potential&   potential,
        Thermostat&  thermostat
    );
    void setupPotential(Potential& potential, toml::table config);
    void setupIntegrator(Integrator& integrator, toml::table config);
    void setupThermostat(Thermostat& thermostat, toml::table config);
};

#endif
