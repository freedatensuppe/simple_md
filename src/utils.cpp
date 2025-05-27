#include "utils.hpp"

#include <cmath>

#include "vector3d.hpp"

double calculateDistance(Vector3D a, Vector3D b, Vector3D dimensions)
{
    double distance = magnitude(b - a);
    return distance;
}

double calculateDistanceSquared(Vector3D a, Vector3D b, Vector3D dimensions)
{
    double distance = magnitudeSquared(b - a);
    return distance;
}

Vector3D calculateDistanceVector(Vector3D a, Vector3D b, Vector3D dimensions)
{
    Vector3D distanceVector;
    distanceVector.x =
        (b.x - a.x) - (dimensions.x * round((b.x - a.x) / dimensions.x));
    distanceVector.y =
        (b.y - a.y) - (dimensions.y * round((b.y - a.y) / dimensions.y));
    distanceVector.z =
        (b.z - a.z) - (dimensions.z * round((b.z - a.z) / dimensions.z));

    return distanceVector;
}
