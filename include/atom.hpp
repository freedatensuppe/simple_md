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
    void setName(const std::string& atomName);
    void setAtomType(double atomType);
    void setPosition(double x, double y, double z);
    void setVelocity(std::vector<double>& velocity);
    void setForce(double Fx, double Fy, double Fz);

    void addForce(std::vector<double>& force);
    void updatePosition(std::vector<double>& shift);

    std::string         getName();
    std::vector<double> getPosition();
    std::vector<double> getVelocity();
    std::vector<double> getForce();
};

#endif
