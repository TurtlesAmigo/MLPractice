#pragma once

#include "Vector.h"
#include "Plane3D.h"
#include <vector>

class LSMPlaneRecognizer
{
public:
    LSMPlaneRecognizer();
    Plane3D recognizePlane(const std::vector<Vector<3>>&);
};

