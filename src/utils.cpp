#include "utils.hpp"

#include <cmath>
#include <vector>

double calculateDistance(
    std::vector<double> a,
    std::vector<double> b,
    std::vector<double> dimensions
)
{
    double distance = 0;
    double dist     = 0;
    for (size_t i = 0; i < a.size(); ++i)
    {
        double dist = (a[i] - b[i]) -
                      (dimensions[i] * round((a[i] - b[i]) / dimensions[i]));

        distance += dist * dist;
    }
    distance = std::sqrt(distance);
    return distance;
}
