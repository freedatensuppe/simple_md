#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

class Vector3D
{
   public:
    double x, y, z;

    Vector3D();
    Vector3D(double x_, double y_, double z_);
    Vector3D operator-() const;

    Vector3D operator+(const Vector3D& rhs);
    Vector3D operator-(const Vector3D& rhs);
    Vector3D operator*(const Vector3D& rhs);
    Vector3D operator/(const Vector3D& rhs);

    Vector3D& operator+=(const Vector3D& rhs);
    Vector3D& operator+=(const double& rhs);
    Vector3D& operator-=(const Vector3D& rhs);
    Vector3D& operator-=(const double& rhs);
    Vector3D& operator*=(const Vector3D& rhs);
    Vector3D& operator*=(const double& rhs);
    Vector3D& operator/=(const Vector3D& rhs);
    Vector3D& operator/=(const double& rhs);

    Vector3D round();

    double magnitude();

    double min();

    void print();
};

Vector3D operator+(const Vector3D& lhs, const double& rhs);
Vector3D operator+(const double& rhs, const Vector3D& lhs);

Vector3D operator-(const Vector3D& lhs, const double& rhs);
Vector3D operator-(const double& rhs, const Vector3D& lhs);

Vector3D operator*(const Vector3D& lhs, const double& rhs);
Vector3D operator*(const double& rhs, const Vector3D& lhs);

Vector3D operator/(const Vector3D& lhs, const double& rhs);
Vector3D operator/(const double& rhs, const Vector3D& lhs);

Vector3D round(const Vector3D& v);

double magnitude(const Vector3D& v);
double magnitudeSquared(const Vector3D& v);

#endif
