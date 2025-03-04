#ifndef ATOM_HPP
#define ATOM_HPP

#include <string>
#include <vector>

class Atom
{
   private:
    std::string         _atomName;
    double              _atomType;
    std::vector<double> _position;
    std::vector<double> _positionPrev;
    std::vector<double> _velocity;
    std::vector<double> _force;

   public:
    void set_name(std::string atomName);
    void set_atomType(double atomType);
    void set_position(double x, double y, double z);
    void set_velocity(double vx, double vy, double vz);
    void set_force(double Fx, double Fy, double Fz);

    std::string         get_name() { return _atomName; }
    std::vector<double> get_position() { return _position; }
    std::vector<double> get_velocity() { return _velocity; }
    std::vector<double> get_force() { return _force; }
};

#endif
