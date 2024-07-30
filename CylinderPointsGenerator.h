#pragma once

#include "Cylinder.h"
#include <random>
#include <vector>
#include "Utils.h"

class CylinderPointsGenerator
{
    Cylinder _cylinder;

public:
    CylinderPointsGenerator(const Cylinder& cylinder);
    std::vector<Vector<3>> generatePoints(int count, double offsetTolerance = 1e-4);
};

