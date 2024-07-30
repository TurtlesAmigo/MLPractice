#pragma once

#include "Plane3D.h"
#include "Vector.h"
#include <random>
#include <vector>

class PlanePointsGenerator
{
    Plane3D _plane;
    double _distanceTolerance;
    std::uniform_real_distribution<double> _unif;
    std::default_random_engine _randomEngine;

    std::normal_distribution<double> _distanceDistribution;
    std::default_random_engine _randomEngineForDistances;
public:
    PlanePointsGenerator(const Plane3D& plane, double distanceTolerance = 1e-4);
    Vector<3> generatePoint();
    std::vector<Vector<3>> generatePoints(int count);
};

