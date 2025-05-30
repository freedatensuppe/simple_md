#ifndef UTILS_HPP
#define UTILS_HPP

#include "vector3d.hpp"

double calculateDistance(Vector3D& a, Vector3D& b, Vector3D& dimensions);
double calculateDistanceSquared(Vector3D& a, Vector3D& b, Vector3D& dimensions);

Vector3D calculateDistanceVector(
    Vector3D& a,
    Vector3D& b,
    Vector3D& dimensions
);

#endif
