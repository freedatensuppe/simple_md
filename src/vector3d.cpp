#include "vector3d.hpp"

#include <cmath>
#include <iostream>

Vector3D::Vector3D() : x(0), y(0), z(0) {}

Vector3D::Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

Vector3D Vector3D::operator-() const { return Vector3D(-x, -y, -z); }

/* inplace operatos */

/* inplace operatos */

Vector3D& Vector3D::operator+=(const Vector3D& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3D& Vector3D::operator+=(const double& rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const double& rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
    return *this;
}

Vector3D& Vector3D::operator*=(const Vector3D& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

Vector3D& Vector3D::operator*=(const double& rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

Vector3D& Vector3D::operator/=(const Vector3D& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
}

Vector3D& Vector3D::operator/=(const double& rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

Vector3D Vector3D::round() const
{
    return Vector3D(std::round(x), std::round(y), std::round(z));
}

double Vector3D::magnitude() const { return std::sqrt(x * x + y * y + z * z); }

double Vector3D::min() const { return std::min(x, std::min(y, z)); }

/* outside class methods */

Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs)
{
    return Vector3D(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs)
{
    return Vector3D(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector3D operator*(const Vector3D& lhs, const Vector3D& rhs)
{
    return Vector3D(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

Vector3D operator/(const Vector3D& lhs, const Vector3D& rhs)
{
    return Vector3D(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

Vector3D operator+(const Vector3D& lhs, const double& rhs)
{
    return Vector3D(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}
Vector3D operator+(const double& rhs, const Vector3D& lhs)
{
    return Vector3D(rhs + lhs.x, rhs + lhs.y, rhs + lhs.z);
}

Vector3D operator-(const Vector3D& lhs, const double& rhs)
{
    return Vector3D(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
}
Vector3D operator-(const double& rhs, const Vector3D& lhs)
{
    return Vector3D(rhs - lhs.x, rhs - lhs.y, rhs - lhs.z);
}

Vector3D operator*(const Vector3D& lhs, const double& rhs)
{
    return Vector3D(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}
Vector3D operator*(const double& rhs, const Vector3D& lhs)
{
    return Vector3D(rhs * lhs.x, rhs * lhs.y, rhs * lhs.z);
}

Vector3D operator/(const Vector3D& lhs, const double& rhs)
{
    return Vector3D(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}
Vector3D operator/(const double& rhs, const Vector3D& lhs)
{
    return Vector3D(rhs / lhs.x, rhs / lhs.y, rhs / lhs.z);
}

void Vector3D::print() const
{
    std::cout << "(" << x << ", " << y << ", " << z << ")\n";
}

Vector3D round(const Vector3D& v)
{
    return Vector3D(std::round(v.x), std::round(v.y), std::round(v.z));
}

double magnitude(const Vector3D& v) { return std::sqrt(magnitudeSquared(v)); }

double magnitudeSquared(const Vector3D& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}
