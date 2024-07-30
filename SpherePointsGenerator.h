#pragma once
#include "Sphere.h"
#include <vector>
#include <cmath>
#include <random>
#include "Utils.h"

class SpherePointsGenerator
{
    Sphere _sphere;

public:
    SpherePointsGenerator(const Sphere& sphere) : _sphere(sphere) {}

    std::vector<Vector<3>> generatePoints(int numPoints, double offsetTolerance = 1e-4) const
    {
        std::vector<Vector<3>> points;
        points.reserve(numPoints);

        std::normal_distribution<double> normalDistribution(0.0, offsetTolerance);
        std::default_random_engine randomEngine;

        for (int i = 0; i < numPoints; ++i)
        {
            double theta = 2 * M_PI * rand() / RAND_MAX;
            double phi = M_PI * rand() / RAND_MAX;
            double randomOffset = normalDistribution(randomEngine);
            double modifiedRadius = _sphere.getRadius() + randomOffset;

            double x = _sphere.getCenter()[0] + modifiedRadius * sin(phi) * cos(theta);
            double y = _sphere.getCenter()[1] + modifiedRadius * sin(phi) * sin(theta);
            double z = _sphere.getCenter()[2] + modifiedRadius * cos(phi);

            points.push_back(Vector<3>{x, y, z});
        }

        return points;
    }
};

