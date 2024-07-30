#pragma once
#include "Sphere.h"
#include <vector>
class LSMSphereRecognition
{
public:
    LSMSphereRecognition();
    Sphere recognizeSphere(const std::vector<Vector<3>>&);
};

