#include "PlanePointsGenerator.h"

PlanePointsGenerator::PlanePointsGenerator(const Plane3D& plane, double distanceTolerance) : _plane{ plane }, _distanceTolerance{ distanceTolerance },
_unif{ -100.0, 100.0 }, _randomEngine(), _distanceDistribution(0.0, distanceTolerance), _randomEngineForDistances()
{
}

Vector<3> PlanePointsGenerator::generatePoint()
{
    Vector<3> normal = _plane.getNormal();

    double x = _unif(_randomEngine);
    double y = _unif(_randomEngine);
    double z = -_plane.getSignedDistanceFromPoint(Vector<3>()) - normal[0] * x - normal[1] * y;

    Vector<3> planePoint{ x, y, z };

    double randomOffset = _distanceDistribution(_randomEngineForDistances);

    return planePoint + normal * randomOffset;
}

std::vector<Vector<3>> PlanePointsGenerator::generatePoints(int count)
{
    std::vector<Vector<3>> result;
    result.reserve(count);

    for (int i = 0; i < count; i++) {
        result.push_back(generatePoint());
    }

    return result;
}
