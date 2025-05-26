#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

double calculateDistance(
    std::vector<double> a,
    std::vector<double> b,
    std::vector<double> dimensions
);

std::vector<double> calculateDistanceVector(
    std::vector<double> a,
    std::vector<double> b,
    std::vector<double> dimensions
);

#endif
