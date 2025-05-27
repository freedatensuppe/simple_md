#include "box.hpp"

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

class Output
{
   private:
   public:
    void writeAllOutput(Box& box);
    void writeXYZTrajectory(Box& box);
    void writeEnergyFile(Box& box);
};

#endif
