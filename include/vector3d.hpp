#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

class Vector3D
{
   public:
    double x, y, z;

    Vector3D();
    Vector3D(double x_, double y_, double z_);

    Vector3D  operator+(const Vector3D& other);
    Vector3D& operator+=(const Vector3D& other);
    Vector3D  operator-(const Vector3D& other);
    Vector3D& operator-=(const Vector3D& other);
    Vector3D  operator*(const Vector3D& other);
    Vector3D  operator*(const double& scalar);
    Vector3D  operator*=(const double& scalar);
    Vector3D  operator/(const double& scalar);
    Vector3D  operator/(const Vector3D& other);

    Vector3D round();

    double   dot(const Vector3D& other);
    Vector3D cross(const Vector3D& other);

    double   magnitude();
    Vector3D normalized();

    double minElement();

    void print();
};

Vector3D operator*(const double& scalar, const Vector3D& v);

Vector3D round(const Vector3D& v);

double magnitude(const Vector3D& v);
double magnitudeSquared(const Vector3D& v);

#endif   // VECTOR3D_HPP
