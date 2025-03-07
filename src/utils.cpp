#include "utils.hpp"

#include <cmath>
#include <vector>

double calculateDistance(std::vector<double> a, std::vector<double> b)
{
    double distance = 0;
    for (size_t i = 0; i < a.size(); ++i)
    {
        distance += pow((a[i] - b[i]), 2);
    }
    distance = std::sqrt(distance);
    return distance;
}
