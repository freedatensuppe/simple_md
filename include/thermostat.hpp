#ifndef THERMOSTAT_HPP
#define THERMOSTAT_HPP

#include "box.hpp"

class Thermostat
{
   private:
    double _temperature       = 0.0;
    double _targetTemperature = 77;      // K
    double _tau               = 250.0;   // fs

   public:
    void calculateTemperature(Box& box);
    void applyBerendsenThermostat(Box& box);

    void   applyBussiThermostat(Box& box);
    double getTemperature();

    void   setTargetTemperature(double T);
    double getTargetTemperature();
};

#endif
