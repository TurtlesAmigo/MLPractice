#include "CylinderPointsGenerator.h"

CylinderPointsGenerator::CylinderPointsGenerator(const Cylinder& cylinder) : _cylinder(cylinder)
{
}

std::vector<Vector<3>> CylinderPointsGenerator::generatePoints(int count, double offsetTolerance)
{
    std::vector<Vector<3>> points;
    points.reserve(count);

    std::normal_distribution<double> normalDistribution(0.0, offsetTolerance);
    std::default_random_engine randomEngine;

    for (int i = 0; i < count; ++i)
    {
        double theta = 2 * M_PI * rand() / RAND_MAX;
        double randomOffset = normalDistribution(randomEngine);
        double modifiedRadius = _cylinder.getRadius() + randomOffset;

        double x = _cylinder.getCenter()[0] + modifiedRadius * cos(theta);
        double y = _cylinder.getCenter()[1] + modifiedRadius * sin(theta);
        double z = _cylinder.getCenter()[2] + _cylinder.getHeight() * rand() / RAND_MAX;

        points.push_back(Vector<3>{x, y, z});
    }

    return points;
}
