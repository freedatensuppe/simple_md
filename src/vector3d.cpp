
#include "vector3d.hpp"

#include <cmath>
#include <iostream>

Vector3D::Vector3D() : x(0), y(0), z(0) {}

Vector3D::Vector3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(float scalar) const
{
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

float Vector3D::dot(const Vector3D& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D& other) const
{
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

float Vector3D::magnitude() const { return std::sqrt(x * x + y * y + z * z); }

Vector3D Vector3D::normalized() const
{
    float mag = magnitude();
    if (mag == 0)
        return Vector3D();
    return Vector3D(x / mag, y / mag, z / mag);
}

void Vector3D::print() const
{
    std::cout << "(" << x << ", " << y << ", " << z << ")\n";
}
