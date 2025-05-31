#include "utils.hpp"

#include <cmath>

#include "box.hpp"
#include "vector3d.hpp"

Vector3D calculateDistanceVector(Vector3D a, Vector3D b, Box& box)
{
    Vector3D distanceVector;
    distanceVector.x =
        (b.x - a.x) -
        (box.getDimensions().x * round((b.x - a.x) / box.getDimensions().x));
    distanceVector.y =
        (b.y - a.y) -
        (box.getDimensions().y * round((b.y - a.y) / box.getDimensions().y));
    distanceVector.z =
        (b.z - a.z) -
        (box.getDimensions().z * round((b.z - a.z) / box.getDimensions().z));

    return distanceVector;
}
