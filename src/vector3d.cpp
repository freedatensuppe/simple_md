
#include "vector3d.hpp"

#include <cmath>
#include <iostream>

Vector3D::Vector3D() : x(0), y(0), z(0) {}

Vector3D::Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

Vector3D Vector3D::operator+(const Vector3D& other)
{
    return Vector3D(x + other.x, y + other.y, z + other.z);
}
Vector3D& Vector3D::operator+=(const Vector3D& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D& other)
{
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D& Vector3D::operator-=(const Vector3D& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3D Vector3D::operator*(const double& scalar)
{
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::operator*(const Vector3D& other)
{
    x *= other.x;
    y *= other.y;
    y *= other.y;
    return *this;
}

Vector3D Vector3D::operator/(const double& scalar)
{
    // Optionally, you can add a check for division by zero
    if (scalar == 0)
    {
        std::cerr << "Error: Division by zero in Vector3D::operator/."
                  << std::endl;
        return Vector3D();   // Return zero vector or handle as needed
    }
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

Vector3D Vector3D::operator/(const Vector3D& other)
{
    x /= other.x;
    y /= other.y;
    y /= other.y;
    return *this;
}
Vector3D Vector3D::round()
{
    return Vector3D(std::round(x), std::round(y), std::round(z));
}

double Vector3D::dot(const Vector3D& other)
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D& other)
{
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

double Vector3D::magnitude() { return std::sqrt(x * x + y * y + z * z); }

Vector3D Vector3D::normalized()
{
    double mag = magnitude();
    if (mag == 0)
        return Vector3D();
    return Vector3D(x / mag, y / mag, z / mag);
}

double Vector3D::minElement() { return std::min(x, std::min(y, z)); }

void Vector3D::print()
{
    std::cout << "(" << x << ", " << y << ", " << z << ")\n";
}

Vector3D operator*(const double& scalar, const Vector3D& v)
{
    return Vector3D(v.x * scalar, v.y * scalar, v.z * scalar);
}

Vector3D round(const Vector3D& v)
{
    return Vector3D(std::round(v.x), std::round(v.y), std::round(v.z));
}

double magnitude(const Vector3D& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double magnitude_squared(const Vector3D& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}
