#include "box.hpp"
#include "toml.hpp"

#ifndef INPUT_HPP
#define INPUT_HPP

class InputReader
{
   private:
    const std::string _configfile;
    toml::table       _config;

   public:
    toml::table getConfig();
    void        readConfigToml(const std::string _configfile);
    void        printConfigToml();
    void        readRestartFile(Box &box);
};

#endif
