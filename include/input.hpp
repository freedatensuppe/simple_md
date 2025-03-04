#include <fstream>
#include <iostream>

#include "toml.hpp"

#ifndef INPUT_HPP
#define INPUT_HPP

class InputReader
{
   private:
    const std::string _configfile;
    toml::table       _config;

   public:
    void readConfigToml(const std::string _configfile);
    void printConfigToml();
    void readRestartFile();
};

#endif
