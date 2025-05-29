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
    void   calculateTemperature(Box& box);
    void   applyThermostat(Box& box);
    double getTemperature();
};

#endif
