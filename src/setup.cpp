#include "setup.hpp"

#include <iostream>

#include "integrator.hpp"
#include "potential.hpp"
#include "toml.hpp"

void Setup::setupSystem(
    Box&         box,
    std::string  configfile,
    InputReader& inputreader,
    Integrator&  integrator,
    Potential&   potential,
    Thermostat&  thermostat
)
{
    setupInput(box, inputreader, configfile);

    toml::table config = inputreader.getConfig();
    setupPotential(potential, config);
    setupIntegrator(integrator, config);
    setupThermostat(thermostat, config);
}

void Setup::setupInput(
    Box&               box,
    InputReader&       inputreader,
    const std::string& configfile
)
{
    inputreader.readConfigToml(configfile);
    inputreader.printConfigToml();
    inputreader.readRestartFile(box);
}

void Setup::setupPotential(Potential& potential, toml::table config)
{
    double epsilon = config["FF"]["epsilon"].value_or(0.0);
    double sigma   = config["FF"]["sigma"].value_or(0.0);

    potential.setLJCutoff(sigma);
    potential.setSigma(sigma);
    potential.setEpsilon(epsilon);
    potential.setc6(epsilon, sigma);
    potential.setc12(epsilon, sigma);

    potential.setVCut();
    potential.setFCut();
}

void Setup::setupIntegrator(Integrator& integrator, toml::table config)
{
    double timestep = config["MDSettings"]["timestep"].value_or(0.5);
    integrator.setTimestep(timestep);
}

void Setup::setupThermostat(Thermostat& thermostat, toml::table config)
{
    double temperature = config["MDSettings"]["temperature"].value_or(298.15);
    thermostat.setTargetTemperature(temperature);
}
